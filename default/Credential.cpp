/*
**
** Copyright 2018, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#define LOG_TAG "android.hardware.credential@1.0-impl"
#include <log/log.h>

#include "Credential.h"

namespace android {
namespace hardware {
namespace credential {
namespace V1_0 {
namespace implementation {

// Methods from ::android::hardware::credential::V1_0::ICredential follow.
Return<void> Credential::del(del_cb _hidl_cb) {
    // TODO implement
    _hidl_cb(ErrorCode::OK, NULL);

    return Void();
}

Return<void> Credential::getEntries(const hidl_vec<hidl_vec<uint8_t>>& accessControlDescriptors, const hidl_vec<hidl_vec<uint8_t>>& entryBlobs, const ::android::hardware::keymaster::capability::V1_0::KeymasterCapability& authToken, const hidl_vec<uint8_t>& sessionTranscript, const hidl_vec<uint8_t>& readerSignature, const hidl_vec<uint8_t>& signingKeyBlob, getEntries_cb _hidl_cb) {

    // TODO implement
    _hidl_cb(ErrorCode::OK, NULL, NULL);

    for(const auto &entry : entryBlobs){
        ALOGD("%zu", entry.size());
        ALOGD("Bla");
    }
    ALOGD("%zu", accessControlDescriptors.size());
    ALOGD("%zu", sizeof(authToken));
    ALOGD("%zu", sessionTranscript.size());
    ALOGD("%zu", readerSignature.size());
    ALOGD("%zu", signingKeyBlob.size());
    return Void();
}

Return<void> Credential::generateSigningKeyPair(generateSigningKeyPair_cb _hidl_cb) {
    _hidl_cb(ErrorCode::OK, NULL, NULL);

    // TODO implement
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//ICredential* HIDL_FETCH_ICredential(const char* /* name */) {
    //return new Credential();
//}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace credential
}  // namespace hardware
}  // namespace android
