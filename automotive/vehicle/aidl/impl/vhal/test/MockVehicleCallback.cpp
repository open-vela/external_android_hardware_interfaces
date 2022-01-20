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

#include "MockVehicleCallback.h"

namespace android {
namespace hardware {
namespace automotive {
namespace vehicle {

namespace {

using ::aidl::android::hardware::automotive::vehicle::GetValueResults;
using ::aidl::android::hardware::automotive::vehicle::SetValueResults;
using ::aidl::android::hardware::automotive::vehicle::VehiclePropErrors;
using ::aidl::android::hardware::automotive::vehicle::VehiclePropValues;
using ::ndk::ScopedAStatus;
using ::ndk::ScopedFileDescriptor;

template <class T>
std::optional<T> pop(std::list<T>& items) {
    if (items.size() > 0) {
        auto item = std::move(items.front());
        items.pop_front();
        return item;
    }
    return std::nullopt;
}

template <class T>
static ScopedAStatus storeResults(const T& results, std::list<T>* storedResults) {
    T resultsCopy{
            .payloads = results.payloads,
    };
    int fd = results.sharedMemoryFd.get();
    if (fd != -1) {
        resultsCopy.sharedMemoryFd = ScopedFileDescriptor(dup(fd));
    }
    storedResults->push_back(std::move(resultsCopy));
    return ScopedAStatus::ok();
}

}  // namespace

ScopedAStatus MockVehicleCallback::onGetValues(const GetValueResults& results) {
    std::scoped_lock<std::mutex> lockGuard(mLock);
    return storeResults(results, &mGetValueResults);
}

ScopedAStatus MockVehicleCallback::onSetValues(const SetValueResults& results) {
    std::scoped_lock<std::mutex> lockGuard(mLock);
    return storeResults(results, &mSetValueResults);
}

ScopedAStatus MockVehicleCallback::onPropertyEvent(const VehiclePropValues&, int32_t) {
    return ScopedAStatus::ok();
}

ScopedAStatus MockVehicleCallback::onPropertySetError(const VehiclePropErrors&) {
    return ScopedAStatus::ok();
}

std::optional<GetValueResults> MockVehicleCallback::nextGetValueResults() {
    std::scoped_lock<std::mutex> lockGuard(mLock);
    return pop(mGetValueResults);
}

std::optional<SetValueResults> MockVehicleCallback::nextSetValueResults() {
    std::scoped_lock<std::mutex> lockGuard(mLock);
    return pop(mSetValueResults);
}

}  // namespace vehicle
}  // namespace automotive
}  // namespace hardware
}  // namespace android
