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
///////////////////////////////////////////////////////////////////////////////
// THIS FILE IS IMMUTABLE. DO NOT EDIT IN ANY CASE.                          //
///////////////////////////////////////////////////////////////////////////////

// This file is a snapshot of an AIDL file. Do not edit it manually. There are
// two cases:
// 1). this is a frozen version file - do not edit this in any case.
// 2). this is a 'current' file. If you make a backwards compatible change to
//     the interface (from the latest frozen version), the build system will
//     prompt you to update this file with `m <name>-update-api`.
//
// You must not make a backward incompatible change to any AIDL file built
// with the aidl_interface module type with versions property set. The module
// type is used to build AIDL files in a way that they can be used across
// independently updatable components of the system. If a device is shipped
// with such a backward incompatible change, it has a high risk of breaking
// later when a module using the interface is updated, e.g., Mainline modules.

package android.hardware.radio.data;
@VintfStability
interface IRadioData {
  oneway void allocatePduSessionId(in int serial);
  oneway void cancelHandover(in int serial, in int callId);
  oneway void deactivateDataCall(in int serial, in int cid, in android.hardware.radio.data.DataRequestReason reason);
  oneway void getDataCallList(in int serial);
  oneway void getSlicingConfig(in int serial);
  oneway void releasePduSessionId(in int serial, in int id);
  oneway void responseAcknowledgement();
  oneway void setDataAllowed(in int serial, in boolean allow);
  oneway void setDataProfile(in int serial, in android.hardware.radio.data.DataProfileInfo[] profiles);
  oneway void setDataThrottling(in int serial, in android.hardware.radio.data.DataThrottlingAction dataThrottlingAction, in long completionDurationMillis);
  oneway void setInitialAttachApn(in int serial, in android.hardware.radio.data.DataProfileInfo dataProfileInfo);
  oneway void setResponseFunctions(in android.hardware.radio.data.IRadioDataResponse radioDataResponse, in android.hardware.radio.data.IRadioDataIndication radioDataIndication);
  oneway void setupDataCall(in int serial, in android.hardware.radio.AccessNetwork accessNetwork, in android.hardware.radio.data.DataProfileInfo dataProfileInfo, in boolean roamingAllowed, in android.hardware.radio.data.DataRequestReason reason, in android.hardware.radio.data.LinkAddress[] addresses, in String[] dnses, in int pduSessionId, in @nullable android.hardware.radio.data.SliceInfo sliceInfo, in @nullable android.hardware.radio.data.TrafficDescriptor trafficDescriptor, in boolean matchAllRuleAllowed);
  oneway void startHandover(in int serial, in int callId);
  oneway void startKeepalive(in int serial, in android.hardware.radio.data.KeepaliveRequest keepalive);
  oneway void stopKeepalive(in int serial, in int sessionHandle);
}
