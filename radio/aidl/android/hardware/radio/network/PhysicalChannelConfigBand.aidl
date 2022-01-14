/*
 * Copyright (C) 2021 The Android Open Source Project
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

package android.hardware.radio.network;

import android.hardware.radio.network.EutranBands;
import android.hardware.radio.network.GeranBands;
import android.hardware.radio.network.NgranBands;
import android.hardware.radio.network.UtranBands;

@VintfStability
union PhysicalChannelConfigBand {
    boolean noinit;
    /**
     * Valid only if radioAccessNetwork = GERAN.
     */
    GeranBands geranBand;
    /**
     * Valid only if radioAccessNetwork = UTRAN.
     */
    UtranBands utranBand;
    /**
     * Valid only if radioAccessNetwork = EUTRAN.
     */
    EutranBands eutranBand;
    /**
     * Valid only if radioAccessNetwork = NGRAN.
     */
    NgranBands ngranBand;
}
