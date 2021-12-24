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
#pragma once

#include <android-base/logging.h>

namespace android::hardware::radio::compat {

namespace debug {

static constexpr bool kSuperVerbose = true;

#define LOG_CALL \
    if constexpr (debug::kSuperVerbose) LOG(VERBOSE) << (RADIO_MODULE ".") << __func__ << ' '

#define CHECK_CB(field)                     \
    if (!field) {                           \
        LOG(WARNING) << "Callback not set"; \
        return {};                          \
    }

}  // namespace debug

inline std::ostream& operator<<(std::ostream& os, const V1_0::RadioIndicationType& type) {
    return os << static_cast<int>(type);
}

}  // namespace android::hardware::radio::compat
