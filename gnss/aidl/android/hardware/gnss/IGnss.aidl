/*
 * Copyright (C) 2020 The Android Open Source Project
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

package android.hardware.gnss;

import android.hardware.gnss.IAGnss;
import android.hardware.gnss.IGnssBatching;
import android.hardware.gnss.IGnssCallback;
import android.hardware.gnss.IGnssConfiguration;
import android.hardware.gnss.IGnssDebug;
import android.hardware.gnss.IGnssGeofence;
import android.hardware.gnss.IGnssMeasurementInterface;
import android.hardware.gnss.IGnssNavigationMessageInterface;
import android.hardware.gnss.IGnssPowerIndication;
import android.hardware.gnss.IGnssPsds;
import android.hardware.gnss.visibility_control.IGnssVisibilityControl;

/**
 * Represents the standard GNSS (Global Navigation Satellite System) interface.
 */
@VintfStability
interface IGnss {
    /**
     * All GNSS binder calls may return a ServiceSpecificException with the following error
     * codes.
     */
    const int ERROR_INVALID_ARGUMENT = 1;

    /** A callback has already been registered. */
    const int ERROR_ALREADY_INIT = 2;

    /** Any other error. */
    const int ERROR_GENERIC = 3;

    /**
     * Opens the interface and provides the callback routines to the implementation of this
     * interface.
     *
     * The framework calls this method to instruct the GPS engine to prepare for serving requests
     * from the framework. The GNSS HAL implementation must respond to all GNSS requests from the
     * framework upon successful return from this method until cleanup() method is called to
     * close this interface.
     *
     * @param callback Callback interface for IGnss.
     */
    void setCallback(in IGnssCallback callback);

    /**
     * Closes the interface.
     *
     * The close() method is called by the framework to tell the GNSS HAL implementation to
     * clear the callback and not expect any GNSS requests in the immediate future - e.g. this may
     * be called when location is disabled by a user setting or low battery conditions. The GNSS HAL
     * implementation must immediately stop responding to any existing requests until the
     * setCallback() method is called again and the requests are re-initiated by the framework.
     *
     * After this method is called, the GNSS HAL implementation may choose to modify GNSS hardware
     * states to save power. It is expected that when setCallback() method is called again to
     * reopen this interface, to serve requests, there may be some minor delays in GNSS response
     * requests as hardware readiness states are restored, not to exceed those that occur on normal
     * device boot up.
     */
    void close();

    /**
     * This method returns the IGnssPsds interface.
     *
     * @return The IGnssPsds interface.
     */
    @nullable IGnssPsds getExtensionPsds();

    /**
     * This method returns the IGnssConfiguration interface.
     *
     * This method must return non-null.
     *
     * @return The IGnssConfiguration interface.
     */
    IGnssConfiguration getExtensionGnssConfiguration();

    /**
     * This method returns the IGnssMeasurementInterface interface.
     *
     * This method must return non-null.
     *
     * @return The IGnssMeasurementInterface interface.
     */
    IGnssMeasurementInterface getExtensionGnssMeasurement();

    /**
     * This method returns the IGnssPowerIndication interface.
     *
     * This method must return non-null.
     *
     * @return The IGnssPowerIndication interface.
     */
    IGnssPowerIndication getExtensionGnssPowerIndication();

    /**
     * This method returns the IGnssBatching interface.
     *
     * @return The IGnssBatching interface.
     */
    @nullable IGnssBatching getExtensionGnssBatching();

    /**
     * This method returns the IGnssGeofence interface.
     *
     * @return The IGnssGeofence interface.
     */
    @nullable IGnssGeofence getExtensionGnssGeofence();

    /**
     * This method returns the IGnssNavigationMessageInterface.
     *
     * @return The IGnssNavigationMessageInterface.
     */
    @nullable IGnssNavigationMessageInterface getExtensionGnssNavigationMessage();

    /**
     * This method returns the IAGnss interface.
     *
     * @return The IAGnss interface.
     */
    IAGnss getExtensionAGnss();

    /**
     * This method returns the IGnssDebug interface.
     *
     * This method must return non-null.
     *
     * @return Handle to the IGnssDebug interface.
     */
    IGnssDebug getExtensionGnssDebug();

    /**
     * This method returns the IGnssVisibilityControl.
     *
     * @return Handle to the IGnssVisibilityControl.
     */
    IGnssVisibilityControl getExtensionGnssVisibilityControl();
}
