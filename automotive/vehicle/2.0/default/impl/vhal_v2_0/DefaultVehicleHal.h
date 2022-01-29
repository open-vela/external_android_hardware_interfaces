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

#ifndef android_hardware_automotive_vehicle_V2_0_impl_DefaultVehicleHal_H_
#define android_hardware_automotive_vehicle_V2_0_impl_DefaultVehicleHal_H_

#include <vhal_v2_0/RecurrentTimer.h>
#include <vhal_v2_0/VehicleHal.h>
#include <vhal_v2_0/VehiclePropertyStore.h>

#include "FakeUserHal.h"
#include "VehicleHalClient.h"

namespace android {
namespace hardware {
namespace automotive {
namespace vehicle {
namespace V2_0 {

namespace impl {

/** Implementation of VehicleHal that connected to emulator instead of real vehicle network. */
class DefaultVehicleHal : public VehicleHal {
  public:
    DefaultVehicleHal(VehiclePropertyStore* propStore, VehicleHalClient* client);
    ~DefaultVehicleHal();

    // Initialize VHAL. Should always call registerHeartBeatEvent() during onCreate.
    void onCreate() override;
    std::vector<VehiclePropConfig> listProperties() override;
    VehiclePropValuePtr get(const VehiclePropValue& requestedPropValue,
                            StatusCode* outStatus) override;
    StatusCode set(const VehiclePropValue& propValue) override;
    StatusCode subscribe(int32_t property, float sampleRate) override;
    StatusCode unsubscribe(int32_t property) override;
    bool dump(const hidl_handle& fd, const hidl_vec<hidl_string>& options) override;

  protected:
    constexpr std::chrono::nanoseconds hertzToNanoseconds(float hz) const {
        return std::chrono::nanoseconds(static_cast<int64_t>(1000000000L / hz));
    }

    VehiclePropertyStore* mPropStore;
    RecurrentTimer mRecurrentTimer;
    VehicleHalClient* mVehicleClient;
    FakeUserHal mFakeUserHal;

    // The callback that would be called when a property value is updated. This function could
    // be extended to handle specific property update event.
    virtual void onPropertyValue(const VehiclePropValue& value, bool updateStatus);
    // Do an internal health check, vendor should add health check logic in this function.
    virtual VehicleHal::VehiclePropValuePtr doInternalHealthCheck();

    // The callback that would be called for every event generated by 'subscribe' or heartbeat.
    // Properties contains a list of properties that need to be handled.
    void onContinuousPropertyTimer(const std::vector<int32_t>& properties);
    // Initiate config for all properties, would be called during onCreate().
    void initStaticConfig();
    // Whether the property is a continuous property.
    bool isContinuousProperty(int32_t propId) const;
    // Returns a lambda that could be used in mRecurrentTimer.
    RecurrentTimer::Action getTimerAction();
    // Check whether a propValue is valid according to its type.
    StatusCode checkPropValue(const VehiclePropValue& propValue, const VehiclePropConfig* config);
    // Check whether the property value is within the range according to area config.
    StatusCode checkValueRange(const VehiclePropValue& propValue,
                               const VehicleAreaConfig* areaConfig);
    // Register the heart beat event to be sent every 3s. This is required to inform watch dog that
    // VHAL is alive. Subclasses should always calls this function during onCreate.
    void registerHeartBeatEvent();
    // Get a user HAL property.
    VehiclePropValuePtr getUserHalProp(const VehiclePropValue& requestedPropValue,
                                       StatusCode* outStatus);
    // Set a user HAL property.
    StatusCode setUserHalProp(const VehiclePropValue& propValue);
    // Create a VHAL heart beat property.
    VehicleHal::VehiclePropValuePtr createVhalHeartBeatProp();

  private:
    // Check whether a vendor mixed value property is valid according to its config array.
    // See 'VehiclePropertyType' documentation in 'types.hal' for detail.
    StatusCode checkVendorMixedPropValue(const VehiclePropValue& value,
                                         const VehiclePropConfig* config);
    // Read the override properties from a config file.
    void getAllPropertiesOverride();
};

}  // namespace impl

}  // namespace V2_0
}  // namespace vehicle
}  // namespace automotive
}  // namespace hardware
}  // namespace android

#endif  // android_hardware_automotive_vehicle_V2_0_impl_DefaultVehicleHal_H_
