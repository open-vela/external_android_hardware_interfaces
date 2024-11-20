/*
 * Copyright 2021 The Android Open Source Project
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

#define LOG_TAG "BTAudioProviderSessionCodecsDB_2_2"

#include "BluetoothAudioSupportedCodecsDB_2_2.h"

#include <android-base/logging.h>

namespace android {
namespace bluetooth {
namespace audio {

using ::android::hardware::bluetooth::audio::V2_0::BitsPerSample;
using ::android::hardware::bluetooth::audio::V2_1::CodecType;
using ::android::hardware::bluetooth::audio::V2_1::Lc3FrameDuration;
using ::android::hardware::bluetooth::audio::V2_1::Lc3Parameters;
using ::android::hardware::bluetooth::audio::V2_1::SampleRate;
using ::android::hardware::bluetooth::audio::V2_2::AudioLocation;
using ::android::hardware::bluetooth::audio::V2_2::BroadcastCapability;
using ::android::hardware::bluetooth::audio::V2_2::
    LeAudioCodecCapabilitiesSetting;
using ::android::hardware::bluetooth::audio::V2_2::UnicastCapability;
using SessionType_2_1 =
    ::android::hardware::bluetooth::audio::V2_1::SessionType;

// Stores the list of offload supported capability
std::vector<LeAudioCodecCapabilitiesSetting> kDefaultOffloadLeAudioCapabilities;

static const UnicastCapability kInvalidUnicastCapability = {
    .codecType = CodecType::UNKNOWN};

static const BroadcastCapability kInvalidBroadcastCapability = {
    .codecType = CodecType::UNKNOWN};

// Default Supported Codecs
// LC3 16_1: sample rate: 16 kHz, frame duration: 7.5 ms, octets per frame: 30
static const Lc3Parameters kLc3Capability_16_1 = {
    .samplingFrequency = SampleRate::RATE_16000,
    .frameDuration = Lc3FrameDuration::DURATION_7500US,
    .octetsPerFrame = 30};

// Default Supported Codecs
// LC3 16_2: sample rate: 16 kHz, frame duration: 10 ms, octets per frame: 40
static const Lc3Parameters kLc3Capability_16_2 = {
    .samplingFrequency = SampleRate::RATE_16000,
    .frameDuration = Lc3FrameDuration::DURATION_10000US,
    .octetsPerFrame = 40};

// Default Supported Codecs
// LC3 48_4: sample rate: 48 kHz, frame duration: 10 ms, octets per frame: 120
static const Lc3Parameters kLc3Capability_48_4 = {
    .samplingFrequency = SampleRate::RATE_48000,
    .frameDuration = Lc3FrameDuration::DURATION_10000US,
    .octetsPerFrame = 120};

static const std::vector<Lc3Parameters> supportedLc3CapabilityList = {
    kLc3Capability_48_4, kLc3Capability_16_2, kLc3Capability_16_1};

static AudioLocation stereoAudio = static_cast<AudioLocation>(
    AudioLocation::FRONT_LEFT | AudioLocation::FRONT_RIGHT);
static AudioLocation monoAudio = AudioLocation::UNKNOWN;

// Stores the supported setting of audio location, connected device, and the
// channel count for each device
std::vector<std::tuple<AudioLocation, uint8_t, uint8_t>>
    supportedDeviceSetting = {
        // Stereo, two connected device, one for L one for R
        std::make_tuple(stereoAudio, 2, 1),
        // Stereo, one connected device for both L and R
        std::make_tuple(stereoAudio, 1, 2),
        // Mono
        std::make_tuple(monoAudio, 1, 1)};

bool IsOffloadLeAudioConfigurationValid(
    const ::android::hardware::bluetooth::audio::V2_1::SessionType&
        session_type,
    const ::android::hardware::bluetooth::audio::V2_2::LeAudioConfiguration&) {
  if (session_type !=
          SessionType_2_1::LE_AUDIO_HARDWARE_OFFLOAD_ENCODING_DATAPATH &&
      session_type !=
          SessionType_2_1::LE_AUDIO_HARDWARE_OFFLOAD_DECODING_DATAPATH) {
    return false;
  }

  // TODO: perform checks on le_audio_codec_config once we know supported
  // parameters

  return true;
}

UnicastCapability composeUnicastLc3Capability(AudioLocation audioLocation,
                                              uint8_t deviceCnt,
                                              uint8_t channelCount,
                                              Lc3Parameters capability) {
  return UnicastCapability{.codecType = CodecType::LC3,
                           .supportedChannel = audioLocation,
                           .deviceCount = deviceCnt,
                           .channelCountPerDevice = channelCount,
                           .capabilities = capability};
}

std::vector<LeAudioCodecCapabilitiesSetting> GetLeAudioOffloadCodecCapabilities(
    const SessionType_2_1& session_type) {
  if (session_type !=
          SessionType_2_1::LE_AUDIO_HARDWARE_OFFLOAD_ENCODING_DATAPATH &&
      session_type !=
          SessionType_2_1::LE_AUDIO_HARDWARE_OFFLOAD_DECODING_DATAPATH) {
    return std::vector<LeAudioCodecCapabilitiesSetting>(0);
  }

  if (kDefaultOffloadLeAudioCapabilities.empty()) {
    for (auto [audioLocation, deviceCnt, channelCount] :
         supportedDeviceSetting) {
      for (auto capability : supportedLc3CapabilityList) {
        UnicastCapability lc3Capability = composeUnicastLc3Capability(
            audioLocation, deviceCnt, channelCount, capability);
        UnicastCapability lc3MonoDecodeCapability =
            composeUnicastLc3Capability(monoAudio, 1, 1, capability);

        // Adds the capability for encode only
        kDefaultOffloadLeAudioCapabilities.push_back(
            {.unicastEncodeCapability = lc3Capability,
             .unicastDecodeCapability = kInvalidUnicastCapability,
             .broadcastCapability = kInvalidBroadcastCapability});

        // Adds the capability for decode only
        kDefaultOffloadLeAudioCapabilities.push_back(
            {.unicastEncodeCapability = kInvalidUnicastCapability,
             .unicastDecodeCapability = lc3Capability,
             .broadcastCapability = kInvalidBroadcastCapability});

        // Adds the capability for the case that encode and decode exist at the
        // same time
        kDefaultOffloadLeAudioCapabilities.push_back(
            {.unicastEncodeCapability = lc3Capability,
             .unicastDecodeCapability = lc3MonoDecodeCapability,
             .broadcastCapability = kInvalidBroadcastCapability});
      }
    }
  }

  return kDefaultOffloadLeAudioCapabilities;
}

}  // namespace audio
}  // namespace bluetooth
}  // namespace android
