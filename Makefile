#
# Copyright (C) 2023 Xiaomi Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

include $(APPDIR)/Make.defs

CXXEXT = .cpp

CXXSRCS += android/hardware/confirmationui/1.0/ConfirmationUIAll.cpp
CXXSRCS += android/hardware/confirmationui/1.0/ConfirmationResultCallbackAll.cpp
CXXSRCS += keymaster/4.0/support/authorization_set.cpp
CXXSRCS += keymaster/4.0/support/keymaster_utils.cpp
CXXSRCS += keymaster/4.1/support/Keymaster.cpp
CXXSRCS += keymaster/4.1/support/Keymaster3.cpp
CXXSRCS += keymaster/android/hardware/keymaster/3.0/KeymasterDeviceAll.cpp
CXXSRCS += keymaster/android/hardware/keymaster/4.0/KeymasterDeviceAll.cpp
CXXSRCS += keymaster/android/hardware/keymaster/4.1/KeymasterDeviceAll.cpp
CXXSRCS += android/tests/binder/IBenchmark.cpp

# ignore update-makefiles.sh error for some hal dependent on framework
context::
	ANDROID_BUILD_TOP=$(CURDIR)/../.. ./update-makefiles.sh > /dev/null 2>&1 || true

AIDLFLAGS = --lang=cpp -h. -o.
AIDLSRCS += tests/libhwbinder/aidl/android/tests/binder/IBenchmark.aidl

include $(APPDIR)/Application.mk
