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
#ifndef ANDROID_HARDWARE_IDENTITY_CREDENTIAL_V1_0_WRITABLEIDENTITYCREDENTIAL_H
#define ANDROID_HARDWARE_IDENTITY_CREDENTIAL_V1_0_WRITABLEIDENTITYCREDENTIAL_H

#include "AppletConnection.h"

#include <android/hardware/identity_credential/1.0/IWritableIdentityCredential.h>
#include <android/hardware/secure_element/1.0/ISecureElement.h>
#include <android/hardware/secure_element/1.0/ISecureElementHalCallback.h>
#include <android/hardware/secure_element/1.0/types.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace identity_credential {
namespace V1_0 {
namespace implementation {

using ::android::hardware::secure_element::V1_0::ISecureElement;
using ::android::hardware::secure_element::V1_0::ISecureElementHalCallback;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct WritableIdentityCredential : public IWritableIdentityCredential {
    WritableIdentityCredential() { resetPersonalizationState(); }
    ~WritableIdentityCredential();

    ResultCode initializeCredential(const hidl_string& credentialType, bool testCredential);

    // Methods from ::android::hardware::identity_credential::V1_0::IWritableIdentityCredential follow.
    Return<void> startPersonalization(const hidl_vec<uint8_t>& attestationApplicationId, const hidl_vec<uint8_t>& attestationChallenge, 
                            uint8_t accessControlProfileCount, uint16_t entryCount, startPersonalization_cb _hidl_cb) override;
    Return<void> addAccessControlProfile(uint8_t id, const hidl_vec<uint8_t>& readerAuthPubKey, uint64_t capabilityId,
                            const ::android::hardware::keymaster::capability::V1_0::CapabilityType capabilityType, uint32_t timeout, 
                            addAccessControlProfile_cb _hidl_cb) override;
    Return<void> addEntry(const EntryData& entry, const hidl_vec<uint8_t>& accessControlProfileIds, addEntry_cb _hidl_cb) override;
        
private:
    void resetPersonalizationState();

    std::vector<uint8_t> mCredentialBlob = {};

    AppletConnection mAppletConnection;
    bool mPersonalizationStarted;

    uint16_t mEntryCount;
    uint16_t mEntriesPersonalized;

    uint8_t mAccessControlProfileCount;
    uint8_t mAccessControlProfilesPersonalized;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace identity_credential
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_IDENTITY_CREDENTIAL_V1_0_WRITABLEIDENTITYCREDENTIAL_H
