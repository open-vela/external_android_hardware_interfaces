/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <HadamardUtils.h>

#include <limits>

#include <android-base/logging.h>

namespace aidl {
namespace android {
namespace hardware {
namespace rebootescrow {
namespace hadamard {

static inline uint8_t read_bit(const std::vector<uint8_t>& input, size_t bit) {
    return (input[bit >> 3] >> (bit & 7)) & 1u;
}

// Apply an error correcting encoding.
//
// The error correcting code used is an augmented Hadamard code with
// k=15, so it takes a 16-bit input and produces a 2^15-bit output.
// We break the 32-byte key into 16 16-bit codewords and encode
// each codeword to a 2^15-bit output.
//
// To better defend against clustered errors, we stripe together the encoded
// codewords. Thus if a single 512-byte DRAM line is lost, instead of losing
// 2^11 bits from the encoding of a single code word, we lose 2^7 bits
// from the encoding of each of the 16 codewords.
std::vector<uint8_t> EncodeKey(const std::vector<uint8_t>& input) {
    CHECK_EQ(input.size(), KEY_SIZE_IN_BYTES);
    std::vector<uint8_t> result(OUTPUT_SIZE_BYTES, 0);
    static_assert(OUTPUT_SIZE_BYTES == 64 * 1024);
    // Transpose the key so that each row contains one bit from each codeword
    uint16_t wordmatrix[CODEWORD_BITS];
    for (size_t i = 0; i < CODEWORD_BITS; i++) {
        uint16_t word = 0;
        for (size_t j = 0; j < KEY_CODEWORDS; j++) {
            word |= read_bit(input, i + j * CODEWORD_BITS) << j;
        }
        wordmatrix[i] = word;
    }
    // Fill in the encodings in Gray code order for speed.
    uint16_t val = wordmatrix[CODEWORD_BITS - 1];
    size_t ix = 0;
    for (size_t i = 0; i < ENCODE_LENGTH; i++) {
        for (size_t b = 0; b < CODEWORD_BITS; b++) {
            if (i & (1 << b)) {
                ix ^= (1 << b);
                val ^= wordmatrix[b];
                break;
            }
        }
        result[ix * KEY_CODEWORD_BYTES] = val & 0xffu;
        result[ix * KEY_CODEWORD_BYTES + 1] = val >> 8u;
    }
    return result;
}

// Decode a single codeword. Because of the way codewords are striped together
// this takes the entire input, plus an offset telling it which word to decode.
static uint16_t DecodeWord(size_t word, const std::vector<uint8_t>& encoded) {
    std::vector<int32_t> scores;
    scores.reserve(ENCODE_LENGTH);
    // Convert x -> -1^x in the encoded bits. e.g [1, 0, 0, 1] -> [-1, 1, 1, -1]
    for (uint32_t i = 0; i < ENCODE_LENGTH; i++) {
        scores.push_back(1 - 2 * read_bit(encoded, i * KEY_CODEWORDS + word));
    }

    // Multiply the hadamard matrix by the transformed input.
    // |1  1  1  1|     |-1|     | 0|
    // |1 -1  1 -1|  *  | 1|  =  | 0|
    // |1  1 -1 -1|     | 1|     | 0|
    // |1 -1 -1  1|     |-1|     |-4|
    for (uint32_t i = 0; i < CODE_K; i++) {
        uint16_t step = 1u << i;
        for (uint32_t j = 0; j < ENCODE_LENGTH; j += 2 * step) {
            for (uint32_t k = j; k < j + step; k++) {
                auto a0 = scores[k];
                auto a1 = scores[k + step];
                scores[k] = a0 + a1;
                scores[k + step] = a0 - a1;
            }
        }
    }
    auto hiscore = std::numeric_limits<int32_t>::min();
    uint16_t winner;
    // TODO(b/146520538): this needs to be constant time
    for (size_t i = 0; i < ENCODE_LENGTH; i++) {
        if (scores[i] > hiscore) {
            winner = i;
            hiscore = scores[i];

        } else if (-scores[i] > hiscore) {
            winner = i | (1 << CODE_K);
            hiscore = -scores[i];
        }
    }
    return winner;
}

std::vector<uint8_t> DecodeKey(const std::vector<uint8_t>& encoded) {
    CHECK_EQ(OUTPUT_SIZE_BYTES, encoded.size());
    std::vector<uint8_t> result(KEY_SIZE_IN_BYTES, 0);
    for (size_t i = 0; i < KEY_CODEWORDS; i++) {
        uint16_t val = DecodeWord(i, encoded);
        result[i * CODEWORD_BYTES] = val & 0xffu;
        result[i * CODEWORD_BYTES + 1] = val >> 8u;
    }
    return result;
}

}  // namespace hadamard
}  // namespace rebootescrow
}  // namespace hardware
}  // namespace android
}  // namespace aidl
