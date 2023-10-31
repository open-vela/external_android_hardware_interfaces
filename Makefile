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

distclean::
	$(call DELDIR, android/hardware/atrace/)
	$(call DELDIR, android/hardware/audio/)
	$(call DELDIR, android/hardware/authsecret/)
	$(call DELDIR, android/hardware/automotive/)
	$(call DELDIR, android/hardware/biometrics/)
	$(call DELDIR, android/hardware/bluetooth/)
	$(call DELDIR, android/hardware/boot/)
	$(call DELDIR, android/hardware/broadcastradio/)
	$(call DELDIR, android/hardware/camera/)
	$(call DELDIR, android/hardware/cas/)
	$(call DELDIR, android/hardware/configstore/)
	$(call DELDIR, android/hardware/contexthub/)
	$(call DELFILE, android/hardware/confirmationui/1.0/*.h)
	$(call DELDIR, android/hardware/drm/)
	$(call DELDIR, android/hardware/dumpstate/)
	$(call DELDIR, android/hardware/fastboot/)
	$(call DELDIR, android/hardware/gatekeeper/)
	$(call DELDIR, android/hardware/gnss/)
	$(call DELDIR, android/hardware/graphics/)
	$(call DELDIR, android/hardware/health/)
	$(call DELDIR, android/hardware/input/)
	$(call DELDIR, android/hardware/ir/)
	$(call DELDIR, android/hardware/keymaster/)
	$(call DELDIR, android/hardware/light/)
	$(call DELDIR, android/hardware/media/)
	$(call DELDIR, android/hardware/memtrack/)
	$(call DELDIR, android/hardware/neuralnetworks/)
	$(call DELDIR, android/hardware/nfc/)
	$(call DELDIR, android/hardware/oemlock/)
	$(call DELDIR, android/hardware/power/)
	$(call DELDIR, android/hardware/radio/)
	$(call DELDIR, android/hardware/renderscript/)
	$(call DELDIR, android/hardware/secure_element/)
	$(call DELDIR, android/hardware/sensors/)
	$(call DELDIR, android/hardware/soundtrigger/)
	$(call DELDIR, android/hardware/tests/)
	$(call DELDIR, android/hardware/tetheroffload/)
	$(call DELDIR, android/hardware/thermal/)
	$(call DELDIR, android/hardware/tv/)
	$(call DELDIR, android/hardware/usb/)
	$(call DELDIR, android/hardware/vibrator/)
	$(call DELDIR, android/hardware/vr/)
	$(call DELDIR, android/hardware/weaver/)
	$(call DELDIR, android/hardware/wifi/)
	$(call DELDIR, android/tests/)

include $(APPDIR)/Application.mk
