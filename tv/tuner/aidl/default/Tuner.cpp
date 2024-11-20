/*
 * Copyright 2021 The Android Open Source Project
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

//#define LOG_NDEBUG 0
#define LOG_TAG "android.hardware.tv.tuner-service.example-Tuner"

#include <aidl/android/hardware/tv/tuner/Result.h>
#include <utils/Log.h>

#include "Demux.h"
#include "Descrambler.h"
#include "Frontend.h"
#include "Lnb.h"
#include "Tuner.h"

namespace aidl {
namespace android {
namespace hardware {
namespace tv {
namespace tuner {

Tuner::Tuner() {}

void Tuner::init() {
    // Static Frontends array to maintain local frontends information
    // Array index matches their FrontendId in the default impl
    mFrontendSize = 10;
    mFrontends[0] = ndk::SharedRefBase::make<Frontend>(FrontendType::ISDBS, 0, this->ref<Tuner>());
    mFrontends[1] = ndk::SharedRefBase::make<Frontend>(FrontendType::ATSC3, 1, this->ref<Tuner>());
    mFrontends[2] = ndk::SharedRefBase::make<Frontend>(FrontendType::DVBC, 2, this->ref<Tuner>());
    mFrontends[3] = ndk::SharedRefBase::make<Frontend>(FrontendType::DVBS, 3, this->ref<Tuner>());
    mFrontends[4] = ndk::SharedRefBase::make<Frontend>(FrontendType::DVBT, 4, this->ref<Tuner>());
    mFrontends[5] = ndk::SharedRefBase::make<Frontend>(FrontendType::ISDBT, 5, this->ref<Tuner>());
    mFrontends[6] = ndk::SharedRefBase::make<Frontend>(FrontendType::ANALOG, 6, this->ref<Tuner>());
    mFrontends[7] = ndk::SharedRefBase::make<Frontend>(FrontendType::ATSC, 7, this->ref<Tuner>());
    mFrontends[8] = ndk::SharedRefBase::make<Frontend>(FrontendType::ISDBS3, 8, this->ref<Tuner>());
    mFrontends[9] = ndk::SharedRefBase::make<Frontend>(FrontendType::DTMB, 9, this->ref<Tuner>());

    vector<FrontendStatusType> statusCaps;

    FrontendCapabilities capsIsdbs;
    capsIsdbs.set<FrontendCapabilities::Tag::isdbsCaps>(FrontendIsdbsCapabilities());
    mFrontendCaps[0] = capsIsdbs;
    statusCaps = {
            FrontendStatusType::DEMOD_LOCK,
            FrontendStatusType::SNR,
            FrontendStatusType::FEC,
            FrontendStatusType::MODULATION,
            FrontendStatusType::MODULATIONS,
            FrontendStatusType::ROLL_OFF,
            FrontendStatusType::STREAM_ID_LIST,
    };
    mFrontendStatusCaps[0] = statusCaps;
    mMaxUsableFrontends[FrontendType::ISDBS] = 1;

    FrontendCapabilities capsAtsc3;
    capsAtsc3.set<FrontendCapabilities::Tag::atsc3Caps>(FrontendAtsc3Capabilities());
    mFrontendCaps[1] = capsAtsc3;
    statusCaps = {
            FrontendStatusType::BER,
            FrontendStatusType::PER,
            FrontendStatusType::ATSC3_PLP_INFO,
            FrontendStatusType::MODULATIONS,
            FrontendStatusType::BERS,
            FrontendStatusType::INTERLEAVINGS,
            FrontendStatusType::BANDWIDTH,
    };
    mFrontendStatusCaps[1] = statusCaps;
    mMaxUsableFrontends[FrontendType::ATSC3] = 1;

    FrontendCapabilities capsDvbc;
    capsDvbc.set<FrontendCapabilities::Tag::dvbcCaps>(FrontendDvbcCapabilities());
    mFrontendCaps[2] = capsDvbc;
    statusCaps = {
            FrontendStatusType::PRE_BER,       FrontendStatusType::SIGNAL_QUALITY,
            FrontendStatusType::MODULATION,    FrontendStatusType::SPECTRAL,
            FrontendStatusType::MODULATIONS,   FrontendStatusType::CODERATES,
            FrontendStatusType::INTERLEAVINGS, FrontendStatusType::BANDWIDTH,
    };
    mFrontendStatusCaps[2] = statusCaps;
    mMaxUsableFrontends[FrontendType::DVBC] = 1;

    FrontendCapabilities capsDvbs;
    capsDvbs.set<FrontendCapabilities::Tag::dvbsCaps>(FrontendDvbsCapabilities());
    mFrontendCaps[3] = capsDvbs;
    statusCaps = {
            FrontendStatusType::SIGNAL_STRENGTH, FrontendStatusType::SYMBOL_RATE,
            FrontendStatusType::MODULATION,      FrontendStatusType::MODULATIONS,
            FrontendStatusType::ROLL_OFF,        FrontendStatusType::IS_MISO,
    };
    mFrontendStatusCaps[3] = statusCaps;
    mMaxUsableFrontends[FrontendType::DVBS] = 1;

    FrontendCapabilities capsDvbt;
    capsDvbt.set<FrontendCapabilities::Tag::dvbtCaps>(FrontendDvbtCapabilities());
    mFrontendCaps[4] = capsDvbt;
    statusCaps = {
            FrontendStatusType::EWBS,
            FrontendStatusType::PLP_ID,
            FrontendStatusType::HIERARCHY,
            FrontendStatusType::MODULATIONS,
            FrontendStatusType::BANDWIDTH,
            FrontendStatusType::GUARD_INTERVAL,
            FrontendStatusType::TRANSMISSION_MODE,
            FrontendStatusType::T2_SYSTEM_ID,
            FrontendStatusType::DVBT_CELL_IDS,
    };
    mFrontendStatusCaps[4] = statusCaps;
    mMaxUsableFrontends[FrontendType::DVBT] = 1;

    FrontendCapabilities capsIsdbt;
    FrontendIsdbtCapabilities isdbtCaps{
            .modeCap = (int)FrontendIsdbtMode::MODE_1 | (int)FrontendIsdbtMode::MODE_2,
            .bandwidthCap = (int)FrontendIsdbtBandwidth::BANDWIDTH_6MHZ,
            .modulationCap = (int)FrontendIsdbtModulation::MOD_16QAM,
            .coderateCap = (int)FrontendIsdbtCoderate::CODERATE_4_5 |
                           (int)FrontendIsdbtCoderate::CODERATE_6_7,
            .guardIntervalCap = (int)FrontendIsdbtGuardInterval::INTERVAL_1_128,
            .timeInterleaveCap = (int)FrontendIsdbtTimeInterleaveMode::AUTO |
                                 (int)FrontendIsdbtTimeInterleaveMode::INTERLEAVE_1_0,
            .isSegmentAuto = true,
            .isFullSegment = true,
    };
    capsIsdbt.set<FrontendCapabilities::Tag::isdbtCaps>(isdbtCaps);
    mFrontendCaps[5] = capsIsdbt;
    statusCaps = {
            FrontendStatusType::AGC,
            FrontendStatusType::LNA,
            FrontendStatusType::MODULATION,
            FrontendStatusType::MODULATIONS,
            FrontendStatusType::BANDWIDTH,
            FrontendStatusType::GUARD_INTERVAL,
            FrontendStatusType::TRANSMISSION_MODE,
            FrontendStatusType::ISDBT_SEGMENTS,
            FrontendStatusType::ISDBT_MODE,
            FrontendStatusType::ISDBT_PARTIAL_RECEPTION_FLAG,
            FrontendStatusType::INTERLEAVINGS,
    };
    mFrontendStatusCaps[5] = statusCaps;
    mMaxUsableFrontends[FrontendType::ISDBT] = 1;

    FrontendCapabilities capsAnalog;
    capsAnalog.set<FrontendCapabilities::Tag::analogCaps>(FrontendAnalogCapabilities());
    mFrontendCaps[6] = capsAnalog;
    statusCaps = {
            FrontendStatusType::LAYER_ERROR,
            FrontendStatusType::MER,
            FrontendStatusType::UEC,
            FrontendStatusType::TS_DATA_RATES,
    };
    mFrontendStatusCaps[6] = statusCaps;
    mMaxUsableFrontends[FrontendType::ANALOG] = 1;

    FrontendCapabilities capsAtsc;
    capsAtsc.set<FrontendCapabilities::Tag::atscCaps>(FrontendAtscCapabilities());
    mFrontendCaps[7] = capsAtsc;
    statusCaps = {
            FrontendStatusType::FREQ_OFFSET,
            FrontendStatusType::RF_LOCK,
            FrontendStatusType::MODULATIONS,
            FrontendStatusType::IS_LINEAR,
    };
    mFrontendStatusCaps[7] = statusCaps;
    mMaxUsableFrontends[FrontendType::ATSC] = 1;

    FrontendCapabilities capsIsdbs3;
    capsIsdbs3.set<FrontendCapabilities::Tag::isdbs3Caps>(FrontendIsdbs3Capabilities());
    mFrontendCaps[8] = capsIsdbs3;
    statusCaps = {
            FrontendStatusType::DEMOD_LOCK,      FrontendStatusType::MODULATION,
            FrontendStatusType::MODULATIONS,     FrontendStatusType::ROLL_OFF,
            FrontendStatusType::IS_SHORT_FRAMES, FrontendStatusType::STREAM_ID_LIST,
    };
    mFrontendStatusCaps[8] = statusCaps;
    mMaxUsableFrontends[FrontendType::ISDBS3] = 1;

    FrontendCapabilities capsDtmb;
    capsDtmb.set<FrontendCapabilities::Tag::dtmbCaps>(FrontendDtmbCapabilities());
    mFrontendCaps[9] = capsDtmb;
    statusCaps = {
            FrontendStatusType::MODULATIONS,       FrontendStatusType::INTERLEAVINGS,
            FrontendStatusType::BANDWIDTH,         FrontendStatusType::GUARD_INTERVAL,
            FrontendStatusType::TRANSMISSION_MODE,
    };
    mFrontendStatusCaps[9] = statusCaps;
    mMaxUsableFrontends[FrontendType::DTMB] = 1;

    mLnbs.resize(2);
    mLnbs[0] = ndk::SharedRefBase::make<Lnb>(0);
    mLnbs[1] = ndk::SharedRefBase::make<Lnb>(1);
}

Tuner::~Tuner() {}

::ndk::ScopedAStatus Tuner::getFrontendIds(std::vector<int32_t>* _aidl_return) {
    ALOGV("%s", __FUNCTION__);

    _aidl_return->resize(mFrontendSize);
    for (int i = 0; i < mFrontendSize; i++) {
        (*_aidl_return)[i] = mFrontends[i]->getFrontendId();
    }

    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus Tuner::openFrontendById(int32_t in_frontendId,
                                             std::shared_ptr<IFrontend>* _aidl_return) {
    ALOGV("%s", __FUNCTION__);

    if (in_frontendId >= mFrontendSize || in_frontendId < 0) {
        ALOGW("[   WARN   ] Frontend with id %d isn't available", in_frontendId);
        *_aidl_return = nullptr;
        return ::ndk::ScopedAStatus::fromServiceSpecificError(
                static_cast<int32_t>(Result::INVALID_ARGUMENT));
    }

    *_aidl_return = mFrontends[in_frontendId];
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus Tuner::openDemux(std::vector<int32_t>* out_demuxId,
                                      std::shared_ptr<IDemux>* _aidl_return) {
    ALOGV("%s", __FUNCTION__);

    mLastUsedId += 1;
    mDemuxes[mLastUsedId] = ndk::SharedRefBase::make<Demux>(mLastUsedId, this->ref<Tuner>());

    out_demuxId->push_back(mLastUsedId);
    *_aidl_return = mDemuxes[mLastUsedId];

    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus Tuner::getDemuxCaps(DemuxCapabilities* _aidl_return) {
    ALOGV("%s", __FUNCTION__);

    // IP filter can be an MMTP filter's data source.
    _aidl_return->linkCaps = {0x00, 0x00, 0x02, 0x00, 0x00};
    // Support time filter testing
    _aidl_return->bTimeFilter = true;

    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus Tuner::openDescrambler(std::shared_ptr<IDescrambler>* _aidl_return) {
    ALOGV("%s", __FUNCTION__);

    *_aidl_return = ndk::SharedRefBase::make<Descrambler>();

    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus Tuner::getFrontendInfo(int32_t in_frontendId, FrontendInfo* _aidl_return) {
    ALOGV("%s", __FUNCTION__);

    if (in_frontendId >= mFrontendSize) {
        return ::ndk::ScopedAStatus::fromServiceSpecificError(
                static_cast<int32_t>(Result::INVALID_ARGUMENT));
    }

    // assign randomly selected values for testing.
    *_aidl_return = {
            .type = mFrontends[in_frontendId]->getFrontendType(),
            .minFrequency = 139000000,
            .maxFrequency = 1139000000,
            .minSymbolRate = 45,
            .maxSymbolRate = 1145,
            .acquireRange = 30,
            .exclusiveGroupId = 57,
            .statusCaps = mFrontendStatusCaps[in_frontendId],
            .frontendCaps = mFrontendCaps[in_frontendId],
    };

    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus Tuner::getLnbIds(std::vector<int32_t>* _aidl_return) {
    ALOGV("%s", __FUNCTION__);

    _aidl_return->resize(mLnbs.size());
    for (int i = 0; i < mLnbs.size(); i++) {
        (*_aidl_return)[i] = mLnbs[i]->getId();
    }

    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus Tuner::openLnbById(int32_t in_lnbId, std::shared_ptr<ILnb>* _aidl_return) {
    ALOGV("%s", __FUNCTION__);

    if (in_lnbId >= mLnbs.size()) {
        *_aidl_return = nullptr;
        return ::ndk::ScopedAStatus::fromServiceSpecificError(
                static_cast<int32_t>(Result::INVALID_ARGUMENT));
    }

    *_aidl_return = mLnbs[in_lnbId];
    return ::ndk::ScopedAStatus::ok();
}

std::shared_ptr<Frontend> Tuner::getFrontendById(int32_t frontendId) {
    ALOGV("%s", __FUNCTION__);

    return mFrontends[frontendId];
}

::ndk::ScopedAStatus Tuner::openLnbByName(const std::string& /* in_lnbName */,
                                          std::vector<int32_t>* out_lnbId,
                                          std::shared_ptr<ILnb>* _aidl_return) {
    ALOGV("%s", __FUNCTION__);

    out_lnbId->push_back(1234);
    *_aidl_return = ndk::SharedRefBase::make<Lnb>();

    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus Tuner::setLna(bool /* in_bEnable */) {
    ALOGV("%s", __FUNCTION__);

    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus Tuner::setMaxNumberOfFrontends(FrontendType in_frontendType,
                                                    int32_t in_maxNumber) {
    ALOGV("%s", __FUNCTION__);

    // In the default implementation, every type only has one frontend.
    if (in_maxNumber < 0 || in_maxNumber > 1) {
        return ::ndk::ScopedAStatus::fromServiceSpecificError(
                static_cast<int32_t>(Result::INVALID_ARGUMENT));
    }
    mMaxUsableFrontends[in_frontendType] = in_maxNumber;
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus Tuner::getMaxNumberOfFrontends(FrontendType in_frontendType,
                                                    int32_t* _aidl_return) {
    *_aidl_return = mMaxUsableFrontends[in_frontendType];
    return ::ndk::ScopedAStatus::ok();
}

binder_status_t Tuner::dump(int fd, const char** args, uint32_t numArgs) {
    ALOGV("%s", __FUNCTION__);
    {
        dprintf(fd, "Frontends:\n");
        for (int i = 0; i < mFrontendSize; i++) {
            mFrontends[i]->dump(fd, args, numArgs);
            for (int j = 0; j < mFrontendStatusCaps[i].size(); j++) {
                dprintf(fd, "    statusCap: %d\n", mFrontendStatusCaps[i][j]);
            }
        }
    }
    {
        dprintf(fd, "Demuxs:\n");
        map<int32_t, std::shared_ptr<Demux>>::iterator it;
        for (it = mDemuxes.begin(); it != mDemuxes.end(); it++) {
            it->second->dump(fd, args, numArgs);
        }
    }
    {
        dprintf(fd, "Lnbs:\n");
        for (int i = 0; i < mLnbs.size(); i++) {
            mLnbs[i]->dump(fd, args, numArgs);
        }
    }
    return STATUS_OK;
}

void Tuner::setFrontendAsDemuxSource(int32_t frontendId, int32_t demuxId) {
    mFrontendToDemux[frontendId] = demuxId;
    if (mFrontends[frontendId] != nullptr && mFrontends[frontendId]->isLocked()) {
        mDemuxes[demuxId]->startFrontendInputLoop();
    }
}

void Tuner::removeDemux(int32_t demuxId) {
    map<int32_t, int32_t>::iterator it;
    for (it = mFrontendToDemux.begin(); it != mFrontendToDemux.end(); it++) {
        if (it->second == demuxId) {
            it = mFrontendToDemux.erase(it);
            break;
        }
    }
    mDemuxes.erase(demuxId);
}

void Tuner::removeFrontend(int32_t frontendId) {
    map<int32_t, int32_t>::iterator it = mFrontendToDemux.find(frontendId);
    if (it != mFrontendToDemux.end()) {
        mDemuxes.erase(it->second);
    }
    mFrontendToDemux.erase(frontendId);
}

void Tuner::frontendStopTune(int32_t frontendId) {
    map<int32_t, int32_t>::iterator it = mFrontendToDemux.find(frontendId);
    int32_t demuxId;
    if (it != mFrontendToDemux.end()) {
        demuxId = it->second;
        mDemuxes[demuxId]->stopFrontendInput();
    }
}

void Tuner::frontendStartTune(int32_t frontendId) {
    map<int32_t, int32_t>::iterator it = mFrontendToDemux.find(frontendId);
    int32_t demuxId;
    if (it != mFrontendToDemux.end()) {
        demuxId = it->second;
        mDemuxes[demuxId]->startFrontendInputLoop();
    }
}

}  // namespace tuner
}  // namespace tv
}  // namespace hardware
}  // namespace android
}  // namespace aidl
