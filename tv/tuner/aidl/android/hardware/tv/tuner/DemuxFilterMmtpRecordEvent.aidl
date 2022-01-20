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

package android.hardware.tv.tuner;

/**
 * Filter Event for MMTP Record data.
 * @hide
 */
@VintfStability
parcelable DemuxFilterMmtpRecordEvent {
    /**
     * Indexes defined by DemuxScHevcIndex.
     */
    int scHevcIndexMask;

    /**
     * Byte number from beginning of the filter's output
     */
    long byteNumber;

    /**
     * The Presentation Time Stamp(PTS) for the audio or video frame. It is based on 90KHz
     * and has the same format as the PTS in ISO/IEC 13818-1.
     */
    long pts;

    /**
     * MPU sequence number of the filtered data. This is only used for MMTP.
     */
    int mpuSequenceNumber;

    /**
     * Specifies the address of the first macroblock in the slice defined in ITU-T Rec. H.264.
     */
    int firstMbInSlice;

    /**
     * TS index mask defined by DemuxTsIndex.
     */
    int tsIndexMask;
}
