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
 *//*
 * Autogenerated from camera metadata definitions in
 * /system/media/camera/docs/metadata_definitions.xml
 * *** DO NOT EDIT BY HAND ***
 */
///////////////////////////////////////////////////////////////////////////////
// THIS FILE IS IMMUTABLE. DO NOT EDIT IN ANY CASE.                          //
///////////////////////////////////////////////////////////////////////////////

// This file is a snapshot of an AIDL file. Do not edit it manually. There are
// two cases:
// 1). this is a frozen version file - do not edit this in any case.
// 2). this is a 'current' file. If you make a backwards compatible change to
//     the interface (from the latest frozen version), the build system will
//     prompt you to update this file with `m <name>-update-api`.
//
// You must not make a backward incompatible change to any AIDL file built
// with the aidl_interface module type with versions property set. The module
// type is used to build AIDL files in a way that they can be used across
// independently updatable components of the system. If a device is shipped
// with such a backward incompatible change, it has a high risk of breaking
// later when a module using the interface is updated, e.g., Mainline modules.

package android.hardware.camera.metadata;
@Backing(type="int") @VintfStability
enum CameraMetadataTag {
  ANDROID_COLOR_CORRECTION_MODE = 0,
  ANDROID_COLOR_CORRECTION_TRANSFORM = 1,
  ANDROID_COLOR_CORRECTION_GAINS = 2,
  ANDROID_COLOR_CORRECTION_ABERRATION_MODE = 3,
  ANDROID_COLOR_CORRECTION_AVAILABLE_ABERRATION_MODES = 4,
  ANDROID_CONTROL_AE_ANTIBANDING_MODE = 65536,
  ANDROID_CONTROL_AE_EXPOSURE_COMPENSATION = 65537,
  ANDROID_CONTROL_AE_LOCK = 65538,
  ANDROID_CONTROL_AE_MODE = 65539,
  ANDROID_CONTROL_AE_REGIONS = 65540,
  ANDROID_CONTROL_AE_TARGET_FPS_RANGE = 65541,
  ANDROID_CONTROL_AE_PRECAPTURE_TRIGGER = 65542,
  ANDROID_CONTROL_AF_MODE = 65543,
  ANDROID_CONTROL_AF_REGIONS = 65544,
  ANDROID_CONTROL_AF_TRIGGER = 65545,
  ANDROID_CONTROL_AWB_LOCK = 65546,
  ANDROID_CONTROL_AWB_MODE = 65547,
  ANDROID_CONTROL_AWB_REGIONS = 65548,
  ANDROID_CONTROL_CAPTURE_INTENT = 65549,
  ANDROID_CONTROL_EFFECT_MODE = 65550,
  ANDROID_CONTROL_MODE = 65551,
  ANDROID_CONTROL_SCENE_MODE = 65552,
  ANDROID_CONTROL_VIDEO_STABILIZATION_MODE = 65553,
  ANDROID_CONTROL_AE_AVAILABLE_ANTIBANDING_MODES = 65554,
  ANDROID_CONTROL_AE_AVAILABLE_MODES = 65555,
  ANDROID_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES = 65556,
  ANDROID_CONTROL_AE_COMPENSATION_RANGE = 65557,
  ANDROID_CONTROL_AE_COMPENSATION_STEP = 65558,
  ANDROID_CONTROL_AF_AVAILABLE_MODES = 65559,
  ANDROID_CONTROL_AVAILABLE_EFFECTS = 65560,
  ANDROID_CONTROL_AVAILABLE_SCENE_MODES = 65561,
  ANDROID_CONTROL_AVAILABLE_VIDEO_STABILIZATION_MODES = 65562,
  ANDROID_CONTROL_AWB_AVAILABLE_MODES = 65563,
  ANDROID_CONTROL_MAX_REGIONS = 65564,
  ANDROID_CONTROL_SCENE_MODE_OVERRIDES = 65565,
  ANDROID_CONTROL_AE_PRECAPTURE_ID = 65566,
  ANDROID_CONTROL_AE_STATE = 65567,
  ANDROID_CONTROL_AF_STATE = 65568,
  ANDROID_CONTROL_AF_TRIGGER_ID = 65569,
  ANDROID_CONTROL_AWB_STATE = 65570,
  ANDROID_CONTROL_AVAILABLE_HIGH_SPEED_VIDEO_CONFIGURATIONS = 65571,
  ANDROID_CONTROL_AE_LOCK_AVAILABLE = 65572,
  ANDROID_CONTROL_AWB_LOCK_AVAILABLE = 65573,
  ANDROID_CONTROL_AVAILABLE_MODES = 65574,
  ANDROID_CONTROL_POST_RAW_SENSITIVITY_BOOST_RANGE = 65575,
  ANDROID_CONTROL_POST_RAW_SENSITIVITY_BOOST = 65576,
  ANDROID_CONTROL_ENABLE_ZSL = 65577,
  ANDROID_CONTROL_AF_SCENE_CHANGE = 65578,
  ANDROID_CONTROL_AVAILABLE_EXTENDED_SCENE_MODE_MAX_SIZES = 65579,
  ANDROID_CONTROL_AVAILABLE_EXTENDED_SCENE_MODE_ZOOM_RATIO_RANGES = 65580,
  ANDROID_CONTROL_EXTENDED_SCENE_MODE = 65581,
  ANDROID_CONTROL_ZOOM_RATIO_RANGE = 65582,
  ANDROID_CONTROL_ZOOM_RATIO = 65583,
  ANDROID_CONTROL_AVAILABLE_HIGH_SPEED_VIDEO_CONFIGURATIONS_MAXIMUM_RESOLUTION = 65584,
  ANDROID_DEMOSAIC_MODE = 131072,
  ANDROID_EDGE_MODE = 196608,
  ANDROID_EDGE_STRENGTH = 196609,
  ANDROID_EDGE_AVAILABLE_EDGE_MODES = 196610,
  ANDROID_FLASH_FIRING_POWER = 262144,
  ANDROID_FLASH_FIRING_TIME = 262145,
  ANDROID_FLASH_MODE = 262146,
  ANDROID_FLASH_COLOR_TEMPERATURE = 262147,
  ANDROID_FLASH_MAX_ENERGY = 262148,
  ANDROID_FLASH_STATE = 262149,
  ANDROID_FLASH_INFO_AVAILABLE = 327680,
  ANDROID_FLASH_INFO_CHARGE_DURATION = 327681,
  ANDROID_FLASH_INFO_STRENGTH_MAXIMUM_LEVEL = 327682,
  ANDROID_FLASH_INFO_STRENGTH_DEFAULT_LEVEL = 327683,
  ANDROID_HOT_PIXEL_MODE = 393216,
  ANDROID_HOT_PIXEL_AVAILABLE_HOT_PIXEL_MODES = 393217,
  ANDROID_JPEG_GPS_COORDINATES = 458752,
  ANDROID_JPEG_GPS_PROCESSING_METHOD = 458753,
  ANDROID_JPEG_GPS_TIMESTAMP = 458754,
  ANDROID_JPEG_ORIENTATION = 458755,
  ANDROID_JPEG_QUALITY = 458756,
  ANDROID_JPEG_THUMBNAIL_QUALITY = 458757,
  ANDROID_JPEG_THUMBNAIL_SIZE = 458758,
  ANDROID_JPEG_AVAILABLE_THUMBNAIL_SIZES = 458759,
  ANDROID_JPEG_MAX_SIZE = 458760,
  ANDROID_JPEG_SIZE = 458761,
  ANDROID_LENS_APERTURE = 524288,
  ANDROID_LENS_FILTER_DENSITY = 524289,
  ANDROID_LENS_FOCAL_LENGTH = 524290,
  ANDROID_LENS_FOCUS_DISTANCE = 524291,
  ANDROID_LENS_OPTICAL_STABILIZATION_MODE = 524292,
  ANDROID_LENS_FACING = 524293,
  ANDROID_LENS_POSE_ROTATION = 524294,
  ANDROID_LENS_POSE_TRANSLATION = 524295,
  ANDROID_LENS_FOCUS_RANGE = 524296,
  ANDROID_LENS_STATE = 524297,
  ANDROID_LENS_INTRINSIC_CALIBRATION = 524298,
  ANDROID_LENS_RADIAL_DISTORTION = 524299,
  ANDROID_LENS_POSE_REFERENCE = 524300,
  ANDROID_LENS_DISTORTION = 524301,
  ANDROID_LENS_DISTORTION_MAXIMUM_RESOLUTION = 524302,
  ANDROID_LENS_INTRINSIC_CALIBRATION_MAXIMUM_RESOLUTION = 524303,
  ANDROID_LENS_INFO_AVAILABLE_APERTURES = 589824,
  ANDROID_LENS_INFO_AVAILABLE_FILTER_DENSITIES = 589825,
  ANDROID_LENS_INFO_AVAILABLE_FOCAL_LENGTHS = 589826,
  ANDROID_LENS_INFO_AVAILABLE_OPTICAL_STABILIZATION = 589827,
  ANDROID_LENS_INFO_HYPERFOCAL_DISTANCE = 589828,
  ANDROID_LENS_INFO_MINIMUM_FOCUS_DISTANCE = 589829,
  ANDROID_LENS_INFO_SHADING_MAP_SIZE = 589830,
  ANDROID_LENS_INFO_FOCUS_DISTANCE_CALIBRATION = 589831,
  ANDROID_NOISE_REDUCTION_MODE = 655360,
  ANDROID_NOISE_REDUCTION_STRENGTH = 655361,
  ANDROID_NOISE_REDUCTION_AVAILABLE_NOISE_REDUCTION_MODES = 655362,
  ANDROID_QUIRKS_METERING_CROP_REGION = 720896,
  ANDROID_QUIRKS_TRIGGER_AF_WITH_AUTO = 720897,
  ANDROID_QUIRKS_USE_ZSL_FORMAT = 720898,
  ANDROID_QUIRKS_USE_PARTIAL_RESULT = 720899,
  ANDROID_QUIRKS_PARTIAL_RESULT = 720900,
  ANDROID_REQUEST_FRAME_COUNT = 786432,
  ANDROID_REQUEST_ID = 786433,
  ANDROID_REQUEST_INPUT_STREAMS = 786434,
  ANDROID_REQUEST_METADATA_MODE = 786435,
  ANDROID_REQUEST_OUTPUT_STREAMS = 786436,
  ANDROID_REQUEST_TYPE = 786437,
  ANDROID_REQUEST_MAX_NUM_OUTPUT_STREAMS = 786438,
  ANDROID_REQUEST_MAX_NUM_REPROCESS_STREAMS = 786439,
  ANDROID_REQUEST_MAX_NUM_INPUT_STREAMS = 786440,
  ANDROID_REQUEST_PIPELINE_DEPTH = 786441,
  ANDROID_REQUEST_PIPELINE_MAX_DEPTH = 786442,
  ANDROID_REQUEST_PARTIAL_RESULT_COUNT = 786443,
  ANDROID_REQUEST_AVAILABLE_CAPABILITIES = 786444,
  ANDROID_REQUEST_AVAILABLE_REQUEST_KEYS = 786445,
  ANDROID_REQUEST_AVAILABLE_RESULT_KEYS = 786446,
  ANDROID_REQUEST_AVAILABLE_CHARACTERISTICS_KEYS = 786447,
  ANDROID_REQUEST_AVAILABLE_SESSION_KEYS = 786448,
  ANDROID_REQUEST_AVAILABLE_PHYSICAL_CAMERA_REQUEST_KEYS = 786449,
  ANDROID_REQUEST_CHARACTERISTIC_KEYS_NEEDING_PERMISSION = 786450,
  ANDROID_REQUEST_AVAILABLE_DYNAMIC_RANGE_PROFILES_MAP = 786451,
  ANDROID_REQUEST_RECOMMENDED_TEN_BIT_DYNAMIC_RANGE_PROFILE = 786452,
  ANDROID_SCALER_CROP_REGION = 851968,
  ANDROID_SCALER_AVAILABLE_FORMATS = 851969,
  ANDROID_SCALER_AVAILABLE_JPEG_MIN_DURATIONS = 851970,
  ANDROID_SCALER_AVAILABLE_JPEG_SIZES = 851971,
  ANDROID_SCALER_AVAILABLE_MAX_DIGITAL_ZOOM = 851972,
  ANDROID_SCALER_AVAILABLE_PROCESSED_MIN_DURATIONS = 851973,
  ANDROID_SCALER_AVAILABLE_PROCESSED_SIZES = 851974,
  ANDROID_SCALER_AVAILABLE_RAW_MIN_DURATIONS = 851975,
  ANDROID_SCALER_AVAILABLE_RAW_SIZES = 851976,
  ANDROID_SCALER_AVAILABLE_INPUT_OUTPUT_FORMATS_MAP = 851977,
  ANDROID_SCALER_AVAILABLE_STREAM_CONFIGURATIONS = 851978,
  ANDROID_SCALER_AVAILABLE_MIN_FRAME_DURATIONS = 851979,
  ANDROID_SCALER_AVAILABLE_STALL_DURATIONS = 851980,
  ANDROID_SCALER_CROPPING_TYPE = 851981,
  ANDROID_SCALER_AVAILABLE_RECOMMENDED_STREAM_CONFIGURATIONS = 851982,
  ANDROID_SCALER_AVAILABLE_RECOMMENDED_INPUT_OUTPUT_FORMATS_MAP = 851983,
  ANDROID_SCALER_AVAILABLE_ROTATE_AND_CROP_MODES = 851984,
  ANDROID_SCALER_DEFAULT_SECURE_IMAGE_SIZE = 851985,
  ANDROID_SCALER_PHYSICAL_CAMERA_MULTI_RESOLUTION_STREAM_CONFIGURATIONS = 851986,
  ANDROID_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_MAXIMUM_RESOLUTION = 851987,
  ANDROID_SCALER_AVAILABLE_MIN_FRAME_DURATIONS_MAXIMUM_RESOLUTION = 851988,
  ANDROID_SCALER_AVAILABLE_STALL_DURATIONS_MAXIMUM_RESOLUTION = 851989,
  ANDROID_SCALER_AVAILABLE_INPUT_OUTPUT_FORMATS_MAP_MAXIMUM_RESOLUTION = 851990,
  ANDROID_SCALER_MULTI_RESOLUTION_STREAM_SUPPORTED = 851991,
  ANDROID_SCALER_AVAILABLE_STREAM_USE_CASES = 851992,
  ANDROID_SENSOR_EXPOSURE_TIME = 917504,
  ANDROID_SENSOR_FRAME_DURATION = 917505,
  ANDROID_SENSOR_SENSITIVITY = 917506,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1 = 917507,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT2 = 917508,
  ANDROID_SENSOR_CALIBRATION_TRANSFORM1 = 917509,
  ANDROID_SENSOR_CALIBRATION_TRANSFORM2 = 917510,
  ANDROID_SENSOR_COLOR_TRANSFORM1 = 917511,
  ANDROID_SENSOR_COLOR_TRANSFORM2 = 917512,
  ANDROID_SENSOR_FORWARD_MATRIX1 = 917513,
  ANDROID_SENSOR_FORWARD_MATRIX2 = 917514,
  ANDROID_SENSOR_BASE_GAIN_FACTOR = 917515,
  ANDROID_SENSOR_BLACK_LEVEL_PATTERN = 917516,
  ANDROID_SENSOR_MAX_ANALOG_SENSITIVITY = 917517,
  ANDROID_SENSOR_ORIENTATION = 917518,
  ANDROID_SENSOR_PROFILE_HUE_SAT_MAP_DIMENSIONS = 917519,
  ANDROID_SENSOR_TIMESTAMP = 917520,
  ANDROID_SENSOR_TEMPERATURE = 917521,
  ANDROID_SENSOR_NEUTRAL_COLOR_POINT = 917522,
  ANDROID_SENSOR_NOISE_PROFILE = 917523,
  ANDROID_SENSOR_PROFILE_HUE_SAT_MAP = 917524,
  ANDROID_SENSOR_PROFILE_TONE_CURVE = 917525,
  ANDROID_SENSOR_GREEN_SPLIT = 917526,
  ANDROID_SENSOR_TEST_PATTERN_DATA = 917527,
  ANDROID_SENSOR_TEST_PATTERN_MODE = 917528,
  ANDROID_SENSOR_AVAILABLE_TEST_PATTERN_MODES = 917529,
  ANDROID_SENSOR_ROLLING_SHUTTER_SKEW = 917530,
  ANDROID_SENSOR_OPTICAL_BLACK_REGIONS = 917531,
  ANDROID_SENSOR_DYNAMIC_BLACK_LEVEL = 917532,
  ANDROID_SENSOR_DYNAMIC_WHITE_LEVEL = 917533,
  ANDROID_SENSOR_OPAQUE_RAW_SIZE = 917534,
  ANDROID_SENSOR_OPAQUE_RAW_SIZE_MAXIMUM_RESOLUTION = 917535,
  ANDROID_SENSOR_PIXEL_MODE = 917536,
  ANDROID_SENSOR_RAW_BINNING_FACTOR_USED = 917537,
  ANDROID_SENSOR_INFO_ACTIVE_ARRAY_SIZE = 983040,
  ANDROID_SENSOR_INFO_SENSITIVITY_RANGE = 983041,
  ANDROID_SENSOR_INFO_COLOR_FILTER_ARRANGEMENT = 983042,
  ANDROID_SENSOR_INFO_EXPOSURE_TIME_RANGE = 983043,
  ANDROID_SENSOR_INFO_MAX_FRAME_DURATION = 983044,
  ANDROID_SENSOR_INFO_PHYSICAL_SIZE = 983045,
  ANDROID_SENSOR_INFO_PIXEL_ARRAY_SIZE = 983046,
  ANDROID_SENSOR_INFO_WHITE_LEVEL = 983047,
  ANDROID_SENSOR_INFO_TIMESTAMP_SOURCE = 983048,
  ANDROID_SENSOR_INFO_LENS_SHADING_APPLIED = 983049,
  ANDROID_SENSOR_INFO_PRE_CORRECTION_ACTIVE_ARRAY_SIZE = 983050,
  ANDROID_SENSOR_INFO_ACTIVE_ARRAY_SIZE_MAXIMUM_RESOLUTION = 983051,
  ANDROID_SENSOR_INFO_PIXEL_ARRAY_SIZE_MAXIMUM_RESOLUTION = 983052,
  ANDROID_SENSOR_INFO_PRE_CORRECTION_ACTIVE_ARRAY_SIZE_MAXIMUM_RESOLUTION = 983053,
  ANDROID_SENSOR_INFO_BINNING_FACTOR = 983054,
  ANDROID_SHADING_MODE = 1048576,
  ANDROID_SHADING_STRENGTH = 1048577,
  ANDROID_SHADING_AVAILABLE_MODES = 1048578,
  ANDROID_STATISTICS_FACE_DETECT_MODE = 1114112,
  ANDROID_STATISTICS_HISTOGRAM_MODE = 1114113,
  ANDROID_STATISTICS_SHARPNESS_MAP_MODE = 1114114,
  ANDROID_STATISTICS_HOT_PIXEL_MAP_MODE = 1114115,
  ANDROID_STATISTICS_FACE_IDS = 1114116,
  ANDROID_STATISTICS_FACE_LANDMARKS = 1114117,
  ANDROID_STATISTICS_FACE_RECTANGLES = 1114118,
  ANDROID_STATISTICS_FACE_SCORES = 1114119,
  ANDROID_STATISTICS_HISTOGRAM = 1114120,
  ANDROID_STATISTICS_SHARPNESS_MAP = 1114121,
  ANDROID_STATISTICS_LENS_SHADING_CORRECTION_MAP = 1114122,
  ANDROID_STATISTICS_LENS_SHADING_MAP = 1114123,
  ANDROID_STATISTICS_PREDICTED_COLOR_GAINS = 1114124,
  ANDROID_STATISTICS_PREDICTED_COLOR_TRANSFORM = 1114125,
  ANDROID_STATISTICS_SCENE_FLICKER = 1114126,
  ANDROID_STATISTICS_HOT_PIXEL_MAP = 1114127,
  ANDROID_STATISTICS_LENS_SHADING_MAP_MODE = 1114128,
  ANDROID_STATISTICS_OIS_DATA_MODE = 1114129,
  ANDROID_STATISTICS_OIS_TIMESTAMPS = 1114130,
  ANDROID_STATISTICS_OIS_X_SHIFTS = 1114131,
  ANDROID_STATISTICS_OIS_Y_SHIFTS = 1114132,
  ANDROID_STATISTICS_INFO_AVAILABLE_FACE_DETECT_MODES = 1179648,
  ANDROID_STATISTICS_INFO_HISTOGRAM_BUCKET_COUNT = 1179649,
  ANDROID_STATISTICS_INFO_MAX_FACE_COUNT = 1179650,
  ANDROID_STATISTICS_INFO_MAX_HISTOGRAM_COUNT = 1179651,
  ANDROID_STATISTICS_INFO_MAX_SHARPNESS_MAP_VALUE = 1179652,
  ANDROID_STATISTICS_INFO_SHARPNESS_MAP_SIZE = 1179653,
  ANDROID_STATISTICS_INFO_AVAILABLE_HOT_PIXEL_MAP_MODES = 1179654,
  ANDROID_STATISTICS_INFO_AVAILABLE_LENS_SHADING_MAP_MODES = 1179655,
  ANDROID_STATISTICS_INFO_AVAILABLE_OIS_DATA_MODES = 1179656,
  ANDROID_TONEMAP_CURVE_BLUE = 1245184,
  ANDROID_TONEMAP_CURVE_GREEN = 1245185,
  ANDROID_TONEMAP_CURVE_RED = 1245186,
  ANDROID_TONEMAP_MODE = 1245187,
  ANDROID_TONEMAP_MAX_CURVE_POINTS = 1245188,
  ANDROID_TONEMAP_AVAILABLE_TONE_MAP_MODES = 1245189,
  ANDROID_TONEMAP_GAMMA = 1245190,
  ANDROID_TONEMAP_PRESET_CURVE = 1245191,
  ANDROID_LED_TRANSMIT = 1310720,
  ANDROID_LED_AVAILABLE_LEDS = 1310721,
  ANDROID_INFO_SUPPORTED_HARDWARE_LEVEL = 1376256,
  ANDROID_INFO_VERSION = 1376257,
  ANDROID_INFO_SUPPORTED_BUFFER_MANAGEMENT_VERSION = 1376258,
  ANDROID_INFO_DEVICE_STATE_ORIENTATIONS = 1376259,
  ANDROID_BLACK_LEVEL_LOCK = 1441792,
  ANDROID_SYNC_FRAME_NUMBER = 1507328,
  ANDROID_SYNC_MAX_LATENCY = 1507329,
  ANDROID_REPROCESS_EFFECTIVE_EXPOSURE_FACTOR = 1572864,
  ANDROID_REPROCESS_MAX_CAPTURE_STALL = 1572865,
  ANDROID_DEPTH_MAX_DEPTH_SAMPLES = 1638400,
  ANDROID_DEPTH_AVAILABLE_DEPTH_STREAM_CONFIGURATIONS = 1638401,
  ANDROID_DEPTH_AVAILABLE_DEPTH_MIN_FRAME_DURATIONS = 1638402,
  ANDROID_DEPTH_AVAILABLE_DEPTH_STALL_DURATIONS = 1638403,
  ANDROID_DEPTH_DEPTH_IS_EXCLUSIVE = 1638404,
  ANDROID_DEPTH_AVAILABLE_RECOMMENDED_DEPTH_STREAM_CONFIGURATIONS = 1638405,
  ANDROID_DEPTH_AVAILABLE_DYNAMIC_DEPTH_STREAM_CONFIGURATIONS = 1638406,
  ANDROID_DEPTH_AVAILABLE_DYNAMIC_DEPTH_MIN_FRAME_DURATIONS = 1638407,
  ANDROID_DEPTH_AVAILABLE_DYNAMIC_DEPTH_STALL_DURATIONS = 1638408,
  ANDROID_DEPTH_AVAILABLE_DEPTH_STREAM_CONFIGURATIONS_MAXIMUM_RESOLUTION = 1638409,
  ANDROID_DEPTH_AVAILABLE_DEPTH_MIN_FRAME_DURATIONS_MAXIMUM_RESOLUTION = 1638410,
  ANDROID_DEPTH_AVAILABLE_DEPTH_STALL_DURATIONS_MAXIMUM_RESOLUTION = 1638411,
  ANDROID_DEPTH_AVAILABLE_DYNAMIC_DEPTH_STREAM_CONFIGURATIONS_MAXIMUM_RESOLUTION = 1638412,
  ANDROID_DEPTH_AVAILABLE_DYNAMIC_DEPTH_MIN_FRAME_DURATIONS_MAXIMUM_RESOLUTION = 1638413,
  ANDROID_DEPTH_AVAILABLE_DYNAMIC_DEPTH_STALL_DURATIONS_MAXIMUM_RESOLUTION = 1638414,
  ANDROID_LOGICAL_MULTI_CAMERA_PHYSICAL_IDS = 1703936,
  ANDROID_LOGICAL_MULTI_CAMERA_SENSOR_SYNC_TYPE = 1703937,
  ANDROID_LOGICAL_MULTI_CAMERA_ACTIVE_PHYSICAL_ID = 1703938,
  ANDROID_DISTORTION_CORRECTION_MODE = 1769472,
  ANDROID_DISTORTION_CORRECTION_AVAILABLE_MODES = 1769473,
  ANDROID_HEIC_AVAILABLE_HEIC_STREAM_CONFIGURATIONS = 1835008,
  ANDROID_HEIC_AVAILABLE_HEIC_MIN_FRAME_DURATIONS = 1835009,
  ANDROID_HEIC_AVAILABLE_HEIC_STALL_DURATIONS = 1835010,
  ANDROID_HEIC_AVAILABLE_HEIC_STREAM_CONFIGURATIONS_MAXIMUM_RESOLUTION = 1835011,
  ANDROID_HEIC_AVAILABLE_HEIC_MIN_FRAME_DURATIONS_MAXIMUM_RESOLUTION = 1835012,
  ANDROID_HEIC_AVAILABLE_HEIC_STALL_DURATIONS_MAXIMUM_RESOLUTION = 1835013,
  ANDROID_HEIC_INFO_SUPPORTED = 1900544,
  ANDROID_HEIC_INFO_MAX_JPEG_APP_SEGMENTS_COUNT = 1900545,
  ANDROID_AUTOMOTIVE_LOCATION = 1966080,
  ANDROID_AUTOMOTIVE_LENS_FACING = 2031616,
}
