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

#ifndef android_hardware_automotive_vehicle_aidl_impl_vhal_include_DefaultVehicleHal_H_
#define android_hardware_automotive_vehicle_aidl_impl_vhal_include_DefaultVehicleHal_H_

#include "ConnectedClient.h"
#include "ParcelableUtils.h"
#include "PendingRequestPool.h"
#include "SubscriptionManager.h"

#include <IVehicleHardware.h>
#include <VehicleUtils.h>
#include <aidl/android/hardware/automotive/vehicle/BnVehicle.h>
#include <android-base/expected.h>
#include <android-base/thread_annotations.h>
#include <android/binder_auto_utils.h>

#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace android {
namespace hardware {
namespace automotive {
namespace vehicle {

class DefaultVehicleHal final : public ::aidl::android::hardware::automotive::vehicle::BnVehicle {
  public:
    using CallbackType =
            std::shared_ptr<::aidl::android::hardware::automotive::vehicle::IVehicleCallback>;

    explicit DefaultVehicleHal(std::unique_ptr<IVehicleHardware> hardware);

    ~DefaultVehicleHal();

    ::ndk::ScopedAStatus getAllPropConfigs(
            ::aidl::android::hardware::automotive::vehicle::VehiclePropConfigs* returnConfigs)
            override;
    ::ndk::ScopedAStatus getValues(
            const CallbackType& callback,
            const ::aidl::android::hardware::automotive::vehicle::GetValueRequests& requests)
            override;
    ::ndk::ScopedAStatus setValues(
            const CallbackType& callback,
            const ::aidl::android::hardware::automotive::vehicle::SetValueRequests& requests)
            override;
    ::ndk::ScopedAStatus getPropConfigs(
            const std::vector<int32_t>& props,
            ::aidl::android::hardware::automotive::vehicle::VehiclePropConfigs* returnConfigs)
            override;
    ::ndk::ScopedAStatus subscribe(
            const CallbackType& callback,
            const std::vector<::aidl::android::hardware::automotive::vehicle::SubscribeOptions>&
                    options,
            int32_t maxSharedMemoryFileCount) override;
    ::ndk::ScopedAStatus unsubscribe(const CallbackType& callback,
                                     const std::vector<int32_t>& propIds) override;
    ::ndk::ScopedAStatus returnSharedMemory(const CallbackType& callback,
                                            int64_t sharedMemoryId) override;

    IVehicleHardware* getHardware();

  private:
    // friend class for unit testing.
    friend class DefaultVehicleHalTest;

    using GetValuesClient =
            GetSetValuesClient<::aidl::android::hardware::automotive::vehicle::GetValueResult,
                               ::aidl::android::hardware::automotive::vehicle::GetValueResults>;
    using SetValuesClient =
            GetSetValuesClient<::aidl::android::hardware::automotive::vehicle::SetValueResult,
                               ::aidl::android::hardware::automotive::vehicle::SetValueResults>;

    // A thread safe class to maintain an increasing request ID for each subscribe client. This
    // class is safe to pass to async callbacks.
    class SubscribeIdByClient {
      public:
        int64_t getId(const CallbackType& callback);

      private:
        std::mutex mLock;
        std::unordered_map<const AIBinder*, int64_t> mIds GUARDED_BY(mLock);
    };

    // A thread safe class to store all subscribe clients. This class is safe to pass to async
    // callbacks.
    class SubscriptionClients {
      public:
        SubscriptionClients(std::shared_ptr<PendingRequestPool> pool) : mPendingRequestPool(pool) {}

        std::shared_ptr<SubscriptionClient> getClient(const CallbackType& callback);

        void removeClient(const AIBinder* clientId);

        size_t countClients();

      private:
        std::mutex mLock;
        std::unordered_map<const AIBinder*, std::shared_ptr<SubscriptionClient>> mClients
                GUARDED_BY(mLock);
        // PendingRequestPool is thread-safe.
        std::shared_ptr<PendingRequestPool> mPendingRequestPool;
    };

    // A wrapper for linkToDeath to enable stubbing for test.
    class ILinkToDeath {
      public:
        virtual ~ILinkToDeath() = default;

        virtual binder_status_t linkToDeath(AIBinder* binder, AIBinder_DeathRecipient* recipient,
                                            void* cookie) = 0;
    };

    // A real implementation for ILinkToDeath.
    class AIBinderLinkToDeathImpl final : public ILinkToDeath {
      public:
        binder_status_t linkToDeath(AIBinder* binder, AIBinder_DeathRecipient* recipient,
                                    void* cookie) override;
    };

    // OnBinderDiedContext is a type used as a cookie passed deathRecipient. The deathRecipient's
    // onBinderDied function takes only a cookie as input and we have to store all the contexts
    // as the cookie.
    struct OnBinderDiedContext {
        DefaultVehicleHal* vhal;
        const AIBinder* clientId;
    };

    // The default timeout of get or set value requests is 30s.
    // TODO(b/214605968): define TIMEOUT_IN_NANO in IVehicle and allow getValues/setValues/subscribe
    // to specify custom timeouts.
    static constexpr int64_t TIMEOUT_IN_NANO = 30'000'000'000;
    // heart beat event interval: 3s
    static constexpr int64_t HEART_BEAT_INTERVAL_IN_NANO = 3'000'000'000;
    const std::shared_ptr<IVehicleHardware> mVehicleHardware;

    // mConfigsByPropId and mConfigFile are only modified during initialization, so no need to
    // lock guard them.
    std::unordered_map<int32_t, ::aidl::android::hardware::automotive::vehicle::VehiclePropConfig>
            mConfigsByPropId;
    // Only modified in constructor, so thread-safe.
    std::unique_ptr<::ndk::ScopedFileDescriptor> mConfigFile;
    // PendingRequestPool is thread-safe.
    std::shared_ptr<PendingRequestPool> mPendingRequestPool;
    // SubscriptionManager is thread-safe.
    std::shared_ptr<SubscriptionManager> mSubscriptionManager;

    std::mutex mLock;
    std::unordered_map<const AIBinder*, std::unique_ptr<OnBinderDiedContext>> mOnBinderDiedContexts
            GUARDED_BY(mLock);
    std::unordered_map<const AIBinder*, std::shared_ptr<GetValuesClient>> mGetValuesClients
            GUARDED_BY(mLock);
    std::unordered_map<const AIBinder*, std::shared_ptr<SetValuesClient>> mSetValuesClients
            GUARDED_BY(mLock);
    // SubscriptionClients is thread-safe.
    std::shared_ptr<SubscriptionClients> mSubscriptionClients;
    // mLinkToDeathImpl is only going to be changed in test.
    std::unique_ptr<ILinkToDeath> mLinkToDeathImpl;

    // RecurrentTimer is thread-safe.
    RecurrentTimer mRecurrentTimer;

    ::ndk::ScopedAIBinder_DeathRecipient mDeathRecipient;

    ::android::base::Result<void> checkProperty(
            const ::aidl::android::hardware::automotive::vehicle::VehiclePropValue& propValue);

    ::android::base::Result<std::vector<int64_t>> checkDuplicateRequests(
            const std::vector<::aidl::android::hardware::automotive::vehicle::GetValueRequest>&
                    requests);

    ::android::base::Result<std::vector<int64_t>> checkDuplicateRequests(
            const std::vector<::aidl::android::hardware::automotive::vehicle::SetValueRequest>&
                    requests);

    ::android::base::Result<void> checkSubscribeOptions(
            const std::vector<::aidl::android::hardware::automotive::vehicle::SubscribeOptions>&
                    options);

    ::android::base::Result<void> checkReadPermission(
            const ::aidl::android::hardware::automotive::vehicle::VehiclePropValue& value) const;

    ::android::base::Result<void> checkWritePermission(
            const ::aidl::android::hardware::automotive::vehicle::VehiclePropValue& value) const;

    ::android::base::Result<
            const ::aidl::android::hardware::automotive::vehicle::VehiclePropConfig*>
    getConfig(int32_t propId) const;

    void onBinderDiedWithContext(const AIBinder* clientId);

    void onBinderUnlinkedWithContext(const AIBinder* clientId);

    void monitorBinderLifeCycle(const CallbackType& callback);

    template <class T>
    static std::shared_ptr<T> getOrCreateClient(
            std::unordered_map<const AIBinder*, std::shared_ptr<T>>* clients,
            const CallbackType& callback, std::shared_ptr<PendingRequestPool> pendingRequestPool);

    static void getValueFromHardwareCallCallback(
            std::weak_ptr<IVehicleHardware> vehicleHardware,
            std::shared_ptr<SubscribeIdByClient> subscribeIdByClient,
            std::shared_ptr<SubscriptionClients> subscriptionClients, const CallbackType& callback,
            const ::aidl::android::hardware::automotive::vehicle::VehiclePropValue& value);

    static void onPropertyChangeEvent(
            std::weak_ptr<SubscriptionManager> subscriptionManager,
            const std::vector<::aidl::android::hardware::automotive::vehicle::VehiclePropValue>&
                    updatedValues);

    static void checkHealth(std::weak_ptr<IVehicleHardware> hardware,
                            std::weak_ptr<SubscriptionManager> subscriptionManager);

    static void onBinderDied(void* cookie);

    static void onBinderUnlinked(void* cookie);

    // Test-only
    // Set the default timeout for pending requests.
    void setTimeout(int64_t timeoutInNano);

    // Test-only
    void setLinkToDeathImpl(std::unique_ptr<ILinkToDeath> impl);
};

}  // namespace vehicle
}  // namespace automotive
}  // namespace hardware
}  // namespace android

#endif  // android_hardware_automotive_vehicle_aidl_impl_vhal_include_DefaultVehicleHal_H_
