/*
 * Copyright (C) 2022 The Android Open Source Project
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

/*
 * Autogenerated from camera metadata definitions in
 * /system/media/camera/docs/metadata_definitions.xml
 * *** DO NOT EDIT BY HAND ***
 */

package android.hardware.camera.metadata;

/*
 * Enumeration definitions for the various entries that need them
 *
 *
 * android.colorCorrection.mode enumeration values
 * @see ANDROID_COLOR_CORRECTION_MODE
 */
@VintfStability
@Backing(type="int")
enum ColorCorrectionMode {
    ANDROID_COLOR_CORRECTION_MODE_TRANSFORM_MATRIX,
    ANDROID_COLOR_CORRECTION_MODE_FAST,
    ANDROID_COLOR_CORRECTION_MODE_HIGH_QUALITY,
}
