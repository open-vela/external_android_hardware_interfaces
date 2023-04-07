#include <android/hardware/keymaster/3.0/IKeymasterDevice.h>

namespace android {
namespace hardware {
namespace keymaster {
namespace V3_0 {

const char* IKeymasterDevice::descriptor("android.hardware.keymaster@3.0::IKeymasterDevice");

::android::hardware::Return<void> IKeymasterDevice::interfaceChain(interfaceChain_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IKeymasterDevice::debug(const ::android::hardware::hidl_handle &fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string> &options) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IKeymasterDevice::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IKeymasterDevice::getHashChain(getHashChain_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IKeymasterDevice::setHALInstrumentation() {
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IKeymasterDevice::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient> &recipient, uint64_t cookie) {
    return false;
}

::android::hardware::Return<void> IKeymasterDevice::ping() {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IKeymasterDevice::getDebugInfo(getDebugInfo_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IKeymasterDevice::notifySyspropsChanged() {
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IKeymasterDevice::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient> &recipient) {
    return false;
}

}  // namespace V3_0
}  // namespace keymaster
}  // namespace hardware
}  // namespace android