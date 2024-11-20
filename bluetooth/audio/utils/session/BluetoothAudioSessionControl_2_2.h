/*
 * Copyright 2018 The Android Open Source Project
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

#pragma once

#include "BluetoothAudioSession_2_2.h"

namespace android {
namespace bluetooth {
namespace audio {

class BluetoothAudioSessionControl_2_2 {
  using SessionType_2_1 =
      ::android::hardware::bluetooth::audio::V2_1::SessionType;
  using AudioConfiguration_2_2 =
      ::android::hardware::bluetooth::audio::V2_2::AudioConfiguration;

 public:
  // The control API helps to check if session is ready or not
  // @return: true if the Bluetooth stack has started th specified session
  static bool IsSessionReady(const SessionType_2_1& session_type) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      return session_ptr->IsSessionReady();
    }
    return false;
  }

  // The control API helps the bluetooth_audio module to register
  // PortStatusCallbacks
  // @return: cookie - the assigned number to this bluetooth_audio output
  static uint16_t RegisterControlResultCback(
      const SessionType_2_1& session_type, const PortStatusCallbacks& cbacks) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      PortStatusCallbacks_2_2 cb = {
          .control_result_cb_ = cbacks.control_result_cb_,
          .session_changed_cb_ = cbacks.session_changed_cb_,
          .audio_configuration_changed_cb_ = nullptr};
      return session_ptr->RegisterStatusCback(cb);
    }
    return kObserversCookieUndefined;
  }

  // The control API helps the bluetooth_audio module to register
  // PortStatusCallbacks_2_2
  // @return: cookie - the assigned number to this bluetooth_audio output
  static uint16_t RegisterControlResultCback(
      const SessionType_2_1& session_type,
      const PortStatusCallbacks_2_2& cbacks) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      return session_ptr->RegisterStatusCback(cbacks);
    }
    return kObserversCookieUndefined;
  }

  // The control API helps the bluetooth_audio module to unregister
  // PortStatusCallbacks and PortStatusCallbacks_2_2
  // @param: cookie - indicates which bluetooth_audio output is
  static void UnregisterControlResultCback(const SessionType_2_1& session_type,
                                           uint16_t cookie) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      session_ptr->UnregisterStatusCback(cookie);
    }
  }

  // The control API for the bluetooth_audio module to get current
  // AudioConfiguration
  static const AudioConfiguration_2_2 GetAudioConfig(
      const SessionType_2_1& session_type) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      return session_ptr->GetAudioConfig();
    } else if (session_type ==
               SessionType_2_1::A2DP_HARDWARE_OFFLOAD_DATAPATH) {
      return BluetoothAudioSession_2_2::kInvalidOffloadAudioConfiguration;
    } else if (
        session_type ==
            SessionType_2_1::LE_AUDIO_HARDWARE_OFFLOAD_ENCODING_DATAPATH ||
        session_type ==
            SessionType_2_1::LE_AUDIO_HARDWARE_OFFLOAD_DECODING_DATAPATH) {
      return BluetoothAudioSession_2_2::kInvalidLeOffloadAudioConfiguration;
    } else {
      return BluetoothAudioSession_2_2::kInvalidSoftwareAudioConfiguration;
    }
  }

  // Those control APIs for the bluetooth_audio module to start / suspend / stop
  // stream, to check position, and to update metadata.
  static bool StartStream(const SessionType_2_1& session_type) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      return session_ptr->StartStream();
    }
    return false;
  }

  static bool SuspendStream(const SessionType_2_1& session_type) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      return session_ptr->SuspendStream();
    }
    return false;
  }

  static void StopStream(const SessionType_2_1& session_type) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      session_ptr->StopStream();
    }
  }

  static bool GetPresentationPosition(const SessionType_2_1& session_type,
                                      uint64_t* remote_delay_report_ns,
                                      uint64_t* total_bytes_readed,
                                      timespec* data_position) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      return session_ptr->GetAudioSession()->GetPresentationPosition(
          remote_delay_report_ns, total_bytes_readed, data_position);
    }
    return false;
  }

  static void UpdateTracksMetadata(
      const SessionType_2_1& session_type,
      const struct source_metadata* source_metadata) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      session_ptr->GetAudioSession()->UpdateTracksMetadata(source_metadata);
    }
  }

  static void UpdateSinkMetadata(const SessionType_2_1& session_type,
                                 const struct sink_metadata* sink_metadata) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      session_ptr->UpdateSinkMetadata(sink_metadata);
    }
  }

  // The control API writes stream to FMQ
  static size_t OutWritePcmData(const SessionType_2_1& session_type,
                                const void* buffer, size_t bytes) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      return session_ptr->GetAudioSession()->OutWritePcmData(buffer, bytes);
    }
    return 0;
  }

  // The control API reads stream from FMQ
  static size_t InReadPcmData(const SessionType_2_1& session_type, void* buffer,
                              size_t bytes) {
    std::shared_ptr<BluetoothAudioSession_2_2> session_ptr =
        BluetoothAudioSessionInstance_2_2::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      return session_ptr->GetAudioSession()->InReadPcmData(buffer, bytes);
    }
    return 0;
  }
};

}  // namespace audio
}  // namespace bluetooth
}  // namespace android
