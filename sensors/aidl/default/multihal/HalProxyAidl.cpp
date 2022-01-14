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

#include "HalProxyAidl.h"
#include <aidlcommonsupport/NativeHandle.h>
#include <fmq/AidlMessageQueue.h>
#include <hidl/Status.h>
#include "ConvertUtils.h"
#include "EventMessageQueueWrapperAidl.h"
#include "ISensorsCallbackWrapperAidl.h"
#include "WakeLockMessageQueueWrapperAidl.h"
#include "convertV2_1.h"

using ::aidl::android::hardware::common::fmq::MQDescriptor;
using ::aidl::android::hardware::common::fmq::SynchronizedReadWrite;
using ::aidl::android::hardware::sensors::ISensors;
using ::aidl::android::hardware::sensors::ISensorsCallback;
using ::android::hardware::sensors::V2_1::implementation::convertToOldEvent;

namespace aidl {
namespace android {
namespace hardware {
namespace sensors {
namespace implementation {

static binder_status_t resultToBinderStatus(::android::hardware::sensors::V1_0::Result result) {
    switch (result) {
        case ::android::hardware::sensors::V1_0::Result::OK:
            return STATUS_OK;
        case ::android::hardware::sensors::V1_0::Result::PERMISSION_DENIED:
            return STATUS_PERMISSION_DENIED;
        case ::android::hardware::sensors::V1_0::Result::NO_MEMORY:
            return STATUS_NO_MEMORY;
        case ::android::hardware::sensors::V1_0::Result::BAD_VALUE:
            return STATUS_BAD_VALUE;
        case ::android::hardware::sensors::V1_0::Result::INVALID_OPERATION:
            return STATUS_INVALID_OPERATION;
    }
}

static ::android::hardware::sensors::V1_0::RateLevel convertRateLevel(
        ISensors::RateLevel rateLevel) {
    switch (rateLevel) {
        case ISensors::RateLevel::STOP:
            return ::android::hardware::sensors::V1_0::RateLevel::STOP;
        case ISensors::RateLevel::NORMAL:
            return ::android::hardware::sensors::V1_0::RateLevel::NORMAL;
        case ISensors::RateLevel::FAST:
            return ::android::hardware::sensors::V1_0::RateLevel::FAST;
        case ISensors::RateLevel::VERY_FAST:
            return ::android::hardware::sensors::V1_0::RateLevel::VERY_FAST;
    }
}

static ::android::hardware::sensors::V1_0::OperationMode convertOperationMode(
        ISensors::OperationMode operationMode) {
    switch (operationMode) {
        case ISensors::OperationMode::NORMAL:
            return ::android::hardware::sensors::V1_0::OperationMode::NORMAL;
        case ISensors::OperationMode::DATA_INJECTION:
            return ::android::hardware::sensors::V1_0::OperationMode::DATA_INJECTION;
    }
}

static ::android::hardware::sensors::V1_0::SharedMemType convertSharedMemType(
        ISensors::SharedMemInfo::SharedMemType sharedMemType) {
    switch (sharedMemType) {
        case ISensors::SharedMemInfo::SharedMemType::ASHMEM:
            return ::android::hardware::sensors::V1_0::SharedMemType::ASHMEM;
        case ISensors::SharedMemInfo::SharedMemType::GRALLOC:
            return ::android::hardware::sensors::V1_0::SharedMemType::GRALLOC;
    }
}

static ::android::hardware::sensors::V1_0::SharedMemFormat convertSharedMemFormat(
        ISensors::SharedMemInfo::SharedMemFormat sharedMemFormat) {
    switch (sharedMemFormat) {
        case ISensors::SharedMemInfo::SharedMemFormat::SENSORS_EVENT:
            return ::android::hardware::sensors::V1_0::SharedMemFormat::SENSORS_EVENT;
    }
}

static ::android::hardware::sensors::V1_0::SharedMemInfo convertSharedMemInfo(
        const ISensors::SharedMemInfo& sharedMemInfo) {
    ::android::hardware::sensors::V1_0::SharedMemInfo v1SharedMemInfo;
    v1SharedMemInfo.type = convertSharedMemType(sharedMemInfo.type);
    v1SharedMemInfo.format = convertSharedMemFormat(sharedMemInfo.format);
    v1SharedMemInfo.size = sharedMemInfo.size;
    v1SharedMemInfo.memoryHandle =
            ::android::hardware::hidl_handle(::android::makeFromAidl(sharedMemInfo.memoryHandle));
    return v1SharedMemInfo;
}

::ndk::ScopedAStatus HalProxyAidl::activate(int32_t in_sensorHandle, bool in_enabled) {
    return ndk::ScopedAStatus::fromStatus(
            resultToBinderStatus(HalProxy::activate(in_sensorHandle, in_enabled)));
}

::ndk::ScopedAStatus HalProxyAidl::batch(int32_t in_sensorHandle, int64_t in_samplingPeriodNs,
                                         int64_t in_maxReportLatencyNs) {
    return ndk::ScopedAStatus::fromStatus(resultToBinderStatus(
            HalProxy::batch(in_sensorHandle, in_samplingPeriodNs, in_maxReportLatencyNs)));
}

::ndk::ScopedAStatus HalProxyAidl::configDirectReport(int32_t in_sensorHandle,
                                                      int32_t in_channelHandle,
                                                      ISensors::RateLevel in_rate,
                                                      int32_t* _aidl_return) {
    binder_status_t binderStatus;
    HalProxy::configDirectReport(
            in_sensorHandle, in_channelHandle, convertRateLevel(in_rate),
            [&binderStatus, _aidl_return](::android::hardware::sensors::V1_0::Result result,
                                          int32_t reportToken) {
                binderStatus = resultToBinderStatus(result);
                *_aidl_return = reportToken;
            });
    return ndk::ScopedAStatus::fromStatus(binderStatus);
}

::ndk::ScopedAStatus HalProxyAidl::flush(int32_t in_sensorHandle) {
    return ndk::ScopedAStatus::fromStatus(resultToBinderStatus(HalProxy::flush(in_sensorHandle)));
}

::ndk::ScopedAStatus HalProxyAidl::getSensorsList(
        std::vector<::aidl::android::hardware::sensors::SensorInfo>* _aidl_return) {
    for (const auto& sensor : HalProxy::getSensors()) {
        _aidl_return->push_back(convertSensorInfo(sensor.second));
    }
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus HalProxyAidl::initialize(
        const MQDescriptor<::aidl::android::hardware::sensors::Event, SynchronizedReadWrite>&
                in_eventQueueDescriptor,
        const MQDescriptor<int32_t, SynchronizedReadWrite>& in_wakeLockDescriptor,
        const std::shared_ptr<ISensorsCallback>& in_sensorsCallback) {
    ::android::sp<::android::hardware::sensors::V2_1::implementation::ISensorsCallbackWrapperBase>
            dynamicCallback = new ISensorsCallbackWrapperAidl(in_sensorsCallback);

    auto aidlEventQueue =
            std::make_unique<::android::AidlMessageQueue<::aidl::android::hardware::sensors::Event,
                                                         SynchronizedReadWrite>>(
                    in_eventQueueDescriptor, true /* resetPointers */);
    std::unique_ptr<
            ::android::hardware::sensors::V2_1::implementation::EventMessageQueueWrapperBase>
            eventQueue = std::make_unique<EventMessageQueueWrapperAidl>(aidlEventQueue);

    auto aidlWakeLockQueue =
            std::make_unique<::android::AidlMessageQueue<int32_t, SynchronizedReadWrite>>(
                    in_wakeLockDescriptor, true /* resetPointers */);
    std::unique_ptr<
            ::android::hardware::sensors::V2_1::implementation::WakeLockMessageQueueWrapperBase>
            wakeLockQueue = std::make_unique<WakeLockMessageQueueWrapperAidl>(aidlWakeLockQueue);

    return ndk::ScopedAStatus::fromStatus(
            resultToBinderStatus(initializeCommon(eventQueue, wakeLockQueue, dynamicCallback)));
}

::ndk::ScopedAStatus HalProxyAidl::injectSensorData(
        const ::aidl::android::hardware::sensors::Event& in_event) {
    ::android::hardware::sensors::V2_1::Event hidlEvent;
    convertToHidlEvent(in_event, &hidlEvent);
    return ndk::ScopedAStatus::fromStatus(
            resultToBinderStatus(HalProxy::injectSensorData(convertToOldEvent(hidlEvent))));
}

::ndk::ScopedAStatus HalProxyAidl::registerDirectChannel(const ISensors::SharedMemInfo& in_mem,
                                                         int32_t* _aidl_return) {
    binder_status_t binderStatus;
    ::android::hardware::sensors::V1_0::SharedMemInfo sharedMemInfo = convertSharedMemInfo(in_mem);

    HalProxy::registerDirectChannel(
            sharedMemInfo,
            [&binderStatus, _aidl_return](::android::hardware::sensors::V1_0::Result result,
                                          int32_t reportToken) {
                binderStatus = resultToBinderStatus(result);
                *_aidl_return = reportToken;
            });

    native_handle_delete(
            const_cast<native_handle_t*>(sharedMemInfo.memoryHandle.getNativeHandle()));
    return ndk::ScopedAStatus::fromStatus(binderStatus);
}

::ndk::ScopedAStatus HalProxyAidl::setOperationMode(
        ::aidl::android::hardware::sensors::ISensors::OperationMode in_mode) {
    return ndk::ScopedAStatus::fromStatus(
            resultToBinderStatus(HalProxy::setOperationMode(convertOperationMode(in_mode))));
}

::ndk::ScopedAStatus HalProxyAidl::unregisterDirectChannel(int32_t in_channelHandle) {
    return ndk::ScopedAStatus::fromStatus(
            resultToBinderStatus(HalProxy::unregisterDirectChannel(in_channelHandle)));
}

}  // namespace implementation
}  // namespace sensors
}  // namespace hardware
}  // namespace android
}  // namespace aidl