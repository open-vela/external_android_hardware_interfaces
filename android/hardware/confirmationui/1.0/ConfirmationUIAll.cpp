#include <android/hardware/confirmationui/1.0/IConfirmationUI.h>

namespace android {
namespace hardware {
namespace confirmationui {
namespace V1_0 {

const char* IConfirmationUI::descriptor("android.hardware.confirmationui@1.0::IConfirmationUI");

::android::hardware::Return<void> IConfirmationUI::interfaceChain(interfaceChain_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationUI::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationUI::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationUI::getHashChain(getHashChain_cb _hidl_cb) {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationUI::setHALInstrumentation() {
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IConfirmationUI::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) {
    return false;
}

::android::hardware::Return<void> IConfirmationUI::ping() {
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationUI::getDebugInfo(getDebugInfo_cb _hidl_cb) {

    return ::android::hardware::Void();
}

::android::hardware::Return<void> IConfirmationUI::notifySyspropsChanged() {
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IConfirmationUI::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) {
    return false;
}

::android::sp<IConfirmationUI> IConfirmationUI::tryGetService(const std::string& serviceName, const bool getStub) {
    return nullptr;
}

::android::sp<IConfirmationUI> IConfirmationUI::getService(const std::string& serviceName, const bool getStub) {
    return nullptr;
}

::android::status_t IConfirmationUI::registerAsService(const std::string& serviceName) {
    return ::android::OK;
}

bool IConfirmationUI::registerForNotifications(
        const std::string& serviceName,
        const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& notification) {
    return ::android::OK;
}

}  // namespace V1_0
}  // namespace confirmationui
}  // namespace hardware
}  // namespace android
