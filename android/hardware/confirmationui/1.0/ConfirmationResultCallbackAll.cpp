#include <android/hardware/confirmationui/1.0/IConfirmationResultCallback.h>

namespace android {
namespace hardware {
namespace confirmationui {
namespace V1_0 {

const char* IConfirmationResultCallback::descriptor("android.hardware.confirmationui@1.0::IConfirmationResultCallback");

::android::hardware::Return<void> IConfirmationResultCallback::interfaceChain(interfaceChain_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationResultCallback::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationResultCallback::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationResultCallback::getHashChain(getHashChain_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationResultCallback::setHALInstrumentation() {
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IConfirmationResultCallback::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) {
    return false;
}

::android::hardware::Return<void> IConfirmationResultCallback::ping() {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationResultCallback::getDebugInfo(getDebugInfo_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationResultCallback::notifySyspropsChanged() {
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IConfirmationResultCallback::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) {
    return false;
}

::android::sp<IConfirmationResultCallback> IConfirmationResultCallback::tryGetService(const std::string& serviceName, const bool getStub) {
    return nullptr;
}

::android::sp<IConfirmationResultCallback> IConfirmationResultCallback::getService(const std::string& serviceName, const bool getStub) {
    return nullptr;
}

::android::status_t IConfirmationResultCallback::registerAsService(const std::string& serviceName) {
    return ::android::OK;
}

bool IConfirmationResultCallback::registerForNotifications(
        const std::string& serviceName,
        const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& notification) {
    return ::android::OK;
}

}  // namespace V1_0
}  // namespace confirmationui
}  // namespace hardware
}  // namespace android
