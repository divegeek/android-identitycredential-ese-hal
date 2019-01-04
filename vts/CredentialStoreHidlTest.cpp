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
#define LOG_TAG "identity_credential_hidl_test"

#include <log/log.h>
#include <android/hardware/identity_credential/1.0/IIdentityCredentialStore.h>
#include <android/hardware/identity_credential/1.0/types.h>
#include <VtsHalHidlTargetTestBase.h>
#include <VtsHalHidlTargetTestEnvBase.h>

using ::android::hardware::keymaster::capability::V1_0::CapabilityType;
using ::testing::VtsHalHidlTargetTestEnvBase;

namespace android {
namespace hardware {
namespace identity_credential {
namespace V1_0 {
namespace test {
 class IdentityCredentialStoreHidlEnvironment : public VtsHalHidlTargetTestEnvBase {
    public:
        // get the test environment singleton
        static IdentityCredentialStoreHidlEnvironment* Instance() {
            static IdentityCredentialStoreHidlEnvironment* instance = new IdentityCredentialStoreHidlEnvironment;
            return instance;
        }
         virtual void registerTestServices() override { registerTestService<IIdentityCredentialStore>(); }
     private:
        IdentityCredentialStoreHidlEnvironment() {}
};
 // The main test class credential HIDL HAL.
class IdentityCredentialStoreHidlTest : public ::testing::VtsHalHidlTargetTestBase {
 public:
    virtual void SetUp() override {
        std::string serviceName =
            IdentityCredentialStoreHidlEnvironment::Instance()->getServiceName<IIdentityCredentialStore>("default");
        ASSERT_FALSE(serviceName.empty());

        credentialstore_ = ::testing::VtsHalHidlTargetTestBase::getService<IIdentityCredentialStore>(serviceName);

        ASSERT_NE(credentialstore_, nullptr);
    }
    sp<IIdentityCredentialStore> credentialstore_;
};

/******************************
 * TEST DATA FOR PROVISIONING *
 ******************************/
const EntryData testEntry1 = {
    "PersonalData",
    "Last name",
    "Turing",
    false
};

const EntryData testEntry2 = {
    "PersonalData",
    "Birth date",
    "19120623",
    false
};

const EntryData testEntry3 = {
    "PersonalData",
    "First name",
    "Alan",
    false
};

const EntryData testEntry4 = {
    "PersonalData",
    "Home address",
    "Maida Vale, London, England",
    false
};

const std::vector<std::pair<EntryData, hidl_vec<uint8_t>>> testEntries{
    {testEntry1, {1}},
    {testEntry2, {2}},
    {testEntry3, {3}},
    {testEntry4, {0, 1}}
};

struct TestProfile{
    uint8_t id;
    hidl_vec<uint8_t> readerAuthPubKey;
    uint64_t capabilityId;
    CapabilityType capabilityType;
    uint64_t timeout;
};

// Profile 1 (reader authentication)
const TestProfile testProfile1 = {0u,
                                  {0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F,
                                   0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F,
                                   0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F},
                                  0u,
                                  CapabilityType::NOT_APPLICABLE,
                                  0u};

// Profile 2 (user authentication)
const TestProfile testProfile2 = {1u, {}, 0x1234567890ABCDEF, CapabilityType::ANY, 100u};

// Profile 3 (user + reader authentication)
const TestProfile testProfile3 = {2u,
                                  {0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F,
                                   0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F,
                                   0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F},
                                  0x1234567890ABCDEF,
                                  CapabilityType::ANY,
                                  100u};

// Profile 4 (no authentication)
const TestProfile testProfile4 = {3u, {}, 0u, CapabilityType::NOT_APPLICABLE, 0u};

const std::vector<TestProfile> testProfiles {testProfile1, testProfile2, testProfile3, testProfile4};

// Credential Blob with test keys
const hidl_vec<uint8_t> testCredentialBlob{
        0x58, 0x50, 0xDF, 0x0D, 0xE3, 0xA1, 0x9E, 0xEB, 0x7D, 0x27, 0x35, 0xE0, 0x0E, 0x23,
        0xA2, 0x2B, 0x9D, 0x2F, 0x74, 0xBC, 0x9B, 0x9F, 0x2C, 0xED, 0xC9, 0x82, 0xDA, 0xCF,
        0x9B, 0x2E, 0x56, 0xFC, 0xDC, 0xD3, 0x52, 0xAF, 0x85, 0xBD, 0x07, 0x67, 0x68, 0xC5,
        0x02, 0xE2, 0x2B, 0x21, 0x8B, 0x53, 0xA4, 0x15, 0x00, 0xFF, 0x34, 0x5C, 0xE8, 0x6A,
        0x7A, 0xD1, 0x95, 0xBE, 0xFF, 0xD7, 0xDB, 0xFB, 0x47, 0x80, 0x4A, 0x91, 0xD0, 0x1F,
        0x85, 0x19, 0x46, 0xC6, 0x84, 0xCC, 0xE4, 0x33, 0x40, 0x82, 0xA2, 0xF9};

/*************************************************** 
 *                  TEST CASES                     *
 ***************************************************/
TEST_F(IdentityCredentialStoreHidlTest, HardwareConfiguration) {
    ALOGD("Test HardwareInformation");

    credentialstore_->getHardwareInformation([&](const hidl_string& credentialStoreName, const hidl_string& credentialStoreAuthorName, uint32_t chunkSize){
        ASSERT_GT(credentialStoreName.size(), 0u);
        ASSERT_GT(credentialStoreAuthorName.size(), 0u);
        ASSERT_GE(chunkSize, 256u); // Chunk sizes smaller than APDU buffer won't be supported
    }
    );
}

TEST_F(IdentityCredentialStoreHidlTest, CreateCredential) {
    ALOGD("Test CreateCredential");
    credentialstore_->createCredential("NewCredential", false,
            [&](ResultCode hidl_error, const sp<IWritableIdentityCredential>& newCredential) {
                ASSERT_EQ(ResultCode::OK, hidl_error);
                ASSERT_NE(newCredential, nullptr);
                }
    );
}


TEST_F(IdentityCredentialStoreHidlTest, ProvisionTestCredential) {
    ALOGD("Test Provisioning Credential");

    sp<IWritableIdentityCredential> credential;
    hidl_vec<uint8_t> empty{0};

    credentialstore_->createCredential(
        "TestCredential", true,
        [&](ResultCode hidl_error, const sp<IWritableIdentityCredential>& newCredential) {
            ASSERT_EQ(ResultCode::OK, hidl_error);
            credential = newCredential;
        });

    ASSERT_NE(credential, nullptr);

    credential->startPersonalization(
        empty, empty, testProfiles.size(), testEntries.size(),
        [&](ResultCode hidl_error, const hidl_vec<uint8_t>& certificate,
            const hidl_vec<uint8_t>& credentialBlob, AuditLogHash auditLogHash) {
            ASSERT_EQ(ResultCode::OK, hidl_error);
            ASSERT_EQ(180u, certificate.size());    // TODO: what is the correct certificate size?
            ASSERT_EQ(98u, credentialBlob.size());  // 128-bit AES key + 256-bit EC key encrypted
            ASSERT_EQ(32u, auditLogHash.hashValue.size());

            // TODO: check the content of credentialBlob and auditLogHash
        });

    for (const auto& testProfile : testProfiles) {
        credential->addAccessControlProfile(
            testProfile.id, testProfile.readerAuthPubKey, testProfile.capabilityId,
            testProfile.capabilityType, testProfile.timeout,
            [&](ResultCode hidl_error, SecureAccessControlProfile profile) {
                ASSERT_EQ(ResultCode::OK, hidl_error);

                ASSERT_EQ(testProfile.id, profile.id);
                ASSERT_EQ(testProfile.readerAuthPubKey, profile.readerAuthPubKey);
                ASSERT_EQ(testProfile.capabilityId, profile.capabilityId);
                ASSERT_EQ(testProfile.capabilityType, profile.capabilityType);
                ASSERT_EQ(testProfile.timeout, profile.timeout);
                // TODO check mac
            });
    }

    for (const auto& entry : testEntries) {
        credential->addEntry(
            entry.first, entry.second,
            [&](ResultCode hidl_error, SecureEntry secEntry, hidl_vec<uint8_t> signedData) {
                ASSERT_EQ(ResultCode::OK, hidl_error);
                
                ASSERT_EQ(entry.first.nameSpace, secEntry.nameSpace);
                ASSERT_EQ(entry.first.name, secEntry.name);
                ASSERT_EQ(entry.second, secEntry.accessControlProfileIds);

                // TODO check the encrypted data

                // The last entry should have the signature
                if(entry.first == testEntries.back().first){ 
                    ASSERT_NE(0u, signedData.size());
                } else {
                    ASSERT_EQ(0u, signedData.size());
                }
                 
            });
    }
}



// TEST_F(IdentityCredentialStoreHidlTest, GetCredential) {
//     ALOGD("GetCredentialTest ");
//     sp<IIdentityCredential> credential;

//     credentialstore_->getCredential(
//         testCredentialBlob,
//         [&](ResultCode hidl_error, const sp<IIdentityCredential>& loadedCredential) {
//             ASSERT_EQ(ResultCode::OK, hidl_error);
//             ASSERT_NE(loadedCredential, nullptr);
//             credential = loadedCredential;
//         });
// } 

}  // namespace test
}  // namespace V1_0
}  // namespace identity_credential
}  // namespace hardware
}  // namespace android