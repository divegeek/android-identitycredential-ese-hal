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

    Result initializeCredential(const hidl_string& docType, bool testCredential);

    // Methods from ::android::hardware::identity_credential::V1_0::IWritableIdentityCredential follow.
    Return<void> getAttestationCertificate(const hidl_vec<uint8_t>& attestationChallenge,
                                           getAttestationCertificate_cb _hidl_cb) override;
    Return<void> startPersonalization(uint8_t accessControlProfileCount,
                                      const hidl_vec<uint16_t>& entryCounts,
                                      startPersonalization_cb _hidl_cb) override;
    Return<void> addAccessControlProfile(
        uint8_t id, const hidl_vec<uint8_t>& readerAuthPubKey, uint64_t capabilityId,
        const ::android::hardware::keymaster::capability::V1_0::CapabilityType capabilityType,
        uint32_t timeout, addAccessControlProfile_cb _hidl_cb) override;
    Return<void> beginAddEntry(const hidl_vec<uint8_t>& accessControlProfiles,
                               const hidl_string& nameSpace, const hidl_string& name,
                               bool directlyAvailable, uint32_t entrySize,
                               beginAddEntry_cb _hidl_cb) override;
    Return<void> addEntryValue(const EntryValue& value, addEntryValue_cb _hidl_cb) override;
    Return<void> finishAddingEntries(finishAddingEntries_cb _hidl_cb) override;

private:
    /**
     * Resets the internal state of the writable identity credential.
     */
    void resetPersonalizationState();

    /**
     * Verifies that the personalization has already started
     * 
     * @return Boolean indicating if personalization has starte
     */
    bool verifyAppletPersonalizationStatus();

    std::vector<uint8_t> mCredentialBlob = {};

    AppletConnection mAppletConnection;

    hidl_string mDocType;
    bool mIsTestCredential;
    bool mPersonalizationStarted;

    std::vector<uint16_t> mNamespaceEntries;
    std::string mCurrentNamespaceName;
    
    uint16_t mCurrentNamespaceId;
    uint16_t mCurrentNamespaceEntryCount;
    
    uint32_t mCurrentValueEntrySize;
    uint32_t mCurrentValueEncryptedContent;
    bool mCurrentValueDirectlyAvailable;
    
    uint8_t mAccessControlProfileCount;
    uint8_t mAccessControlProfilesPersonalized;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace identity_credential
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_IDENTITY_CREDENTIAL_V1_0_WRITABLEIDENTITYCREDENTIAL_H
