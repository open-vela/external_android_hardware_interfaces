#
# Copyright (C) 2023 Xiaomi Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.
#

if(CONFIG_ANDROID_HARDWARE_INTERFACES)

  target_sources(
    android
    PRIVATE
      android/hardware/confirmationui/1.0/ConfirmationUIAll.cpp
      android/hardware/confirmationui/1.0/ConfirmationResultCallbackAll.cpp
      keymaster/4.0/support/authorization_set.cpp
      keymaster/4.0/support/keymaster_utils.cpp
      keymaster/4.1/support/Keymaster.cpp
      keymaster/4.1/support/Keymaster3.cpp
      keymaster/android/hardware/keymaster/3.0/KeymasterDeviceAll.cpp
      keymaster/android/hardware/keymaster/4.0/KeymasterDeviceAll.cpp
      keymaster/android/hardware/keymaster/4.1/KeymasterDeviceAll.cpp)

  set(HIDL_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

  set_property(
    TARGET nuttx
    APPEND
    PROPERTY NUTTX_CXX_INCLUDE_DIRECTORIES
             ${CMAKE_CURRENT_LIST_DIR}/keymaster/4.1/support/include
             ${CMAKE_CURRENT_LIST_DIR}/keymaster/4.0/support/include
             ${CMAKE_CURRENT_LIST_DIR}
             ${HIDL_OUTPUT_DIR})

  add_custom_target(
    interface_hidl_out
    COMMAND ANDROID_BUILD_TOP=${NUTTX_APPS_DIR}/external/android
            ./update-makefiles.sh ${HIDL_OUTPUT_DIR} 2>&1 || true
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "HIDL:Gen HIDL INTERFACE")

  add_dependencies(android interface_hidl_out)

  nuttx_add_aidl(
    TARGET
    android
    AIDL_BASE_DIR
    ${CMAKE_CURRENT_LIST_DIR}
    AIDL_INCLUDE_DIR
    ${CMAKE_CURRENT_LIST_DIR}/tests/libhwbinder
    AIDL_HEADER_DIR
    ${CMAKE_CURRENT_BINARY_DIR}
    AIDL_OUT_DIR
    ${CMAKE_CURRENT_BINARY_DIR}
    AIDL_FLAGS
    --lang=cpp
    AIDLS
    tests/libhwbinder/aidl/android/tests/binder/IBenchmark.aidl)

endif()
