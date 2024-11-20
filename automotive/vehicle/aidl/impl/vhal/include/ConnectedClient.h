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

#ifndef android_hardware_automotive_vehicle_aidl_impl_vhal_include_ConnectedClient_H_
#define android_hardware_automotive_vehicle_aidl_impl_vhal_include_ConnectedClient_H_

#include <VehicleHalTypes.h>

#include <aidl/android/hardware/automotive/vehicle/IVehicleCallback.h>
#include <android-base/result.h>

#include <memory>
#include <unordered_set>
#include <vector>

namespace android {
namespace hardware {
namespace automotive {
namespace vehicle {

// A class to represent a binder client with a callback interface. Each callback function, e.g.
// GetValues or SetValues for a specific binder client is a separate {@code ConnectedClient}.
// For one {@code ConnectedClient}, we use one pending request pool to manage all pending requests,
// so the request IDs must be unique for one client. We also manage a set of callback functions
// for one client, e.g. timeoutCallback which could be passed to hardware.
// This class is thread-safe.
class ConnectedClient {
  public:
    ConnectedClient(
            std::shared_ptr<::aidl::android::hardware::automotive::vehicle::IVehicleCallback>
                    callback);

    virtual ~ConnectedClient() = default;

  protected:
    const std::shared_ptr<::aidl::android::hardware::automotive::vehicle::IVehicleCallback>
            mCallback;
};

// A class to represent a client that calls {@code IVehicle.setValues} or {@code
// IVehicle.getValues}.
template <class ResultType, class ResultsType>
class GetSetValuesClient final : public ConnectedClient {
  public:
    GetSetValuesClient(
            std::shared_ptr<::aidl::android::hardware::automotive::vehicle::IVehicleCallback>
                    callback);

    // Sends the results to this client.
    void sendResults(const std::vector<ResultType>& results);

    // Sends each result separately to this client. Each result would be sent through one callback
    // invocation.
    void sendResultsSeparately(const std::vector<ResultType>& results);

    // Gets the callback to be called when the request for this client has finished.
    std::shared_ptr<const std::function<void(std::vector<ResultType>)>> getResultCallback();

  private:
    // The following members are only initialized during construction.
    std::shared_ptr<const std::function<void(std::vector<ResultType>)>> mResultCallback;
};

}  // namespace vehicle
}  // namespace automotive
}  // namespace hardware
}  // namespace android

#endif  // android_hardware_automotive_vehicle_aidl_impl_vhal_include_ConnectedClient_H_
