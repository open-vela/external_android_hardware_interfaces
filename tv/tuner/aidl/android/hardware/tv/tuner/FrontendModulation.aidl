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

import android.hardware.tv.tuner.FrontendAtsc3Modulation;
import android.hardware.tv.tuner.FrontendAtscModulation;
import android.hardware.tv.tuner.FrontendDvbcModulation;
import android.hardware.tv.tuner.FrontendDvbsModulation;
import android.hardware.tv.tuner.FrontendIsdbs3Modulation;
import android.hardware.tv.tuner.FrontendIsdbsModulation;
import android.hardware.tv.tuner.FrontendIsdbtModulation;
import android.hardware.tv.tuner.FrontendDtmbModulation;
import android.hardware.tv.tuner.FrontendDvbtConstellation;

/**
 * @hide
 */
@VintfStability
union FrontendModulation {
    FrontendDvbcModulation dvbc = FrontendDvbcModulation.UNDEFINED;

    FrontendDvbsModulation dvbs;

    FrontendDvbtConstellation dvbt;

    FrontendIsdbsModulation isdbs;

    FrontendIsdbs3Modulation isdbs3;

    FrontendIsdbtModulation isdbt;

    FrontendAtscModulation atsc;

    FrontendAtsc3Modulation atsc3;

    FrontendDtmbModulation dtmb;
}
