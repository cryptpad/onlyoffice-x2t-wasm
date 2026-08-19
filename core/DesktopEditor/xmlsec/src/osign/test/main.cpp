#include "gtest/gtest.h"
#include "../lib/include/osign.h"
#include "../../../../common/File.h"

class COSignTest : public testing::Test
{
public:
	std::wstring WorkiDirectory;
public:
	virtual void SetUp() override
	{
		WorkiDirectory = NSFile::GetProcessDirectory();
	}

	virtual void TearDown() override
	{
	}
};

// aes encryption
TEST_F(COSignTest, crypt_storage_aes_gcm_random_password)
{
	// create a random password 100 characters long
	OSign::CStorageBuffer oPassword = OSign::Crypt::GeneratePassword(100);
	EXPECT_EQ(100, oPassword.GetLength());

	// encryption buffer
	std::string sDataCrypt = "Hello, world!";
	OSign::CStorageBuffer oBuffer;
	oBuffer.Add((const unsigned char*)sDataCrypt.c_str(), sDataCrypt.length());

	// encrypt the buffer, the salt is generated randomly and appended to the result
	OSign::CStorageBuffer oCryptBuffer = OSign::Crypt::Encrypt(oBuffer, oPassword);

	// decrypt the buffer
	OSign::CStorageBuffer oDecryptBuffer = OSign::Crypt::Decrypt(oCryptBuffer, oPassword);

	// compare with the source
	std::string sDecryptData((char*)oDecryptBuffer.GetData(), oDecryptBuffer.GetLength());
	EXPECT_EQ(sDecryptData, sDataCrypt);
}

TEST_F(COSignTest, crypt_storage_aes_gcm_string_password)
{
	// create a random password from a string
	std::string sPassword = "password";
	OSign::CStorageBuffer oPassword;
	oPassword.Add((unsigned char*)sPassword.c_str(), sPassword.length());

	// encryption buffer
	std::string sDataCrypt = "Hello, world!";
	OSign::CStorageBuffer oBuffer;
	oBuffer.Add((const unsigned char*)sDataCrypt.c_str(), sDataCrypt.length());

	// encrypt the buffer, the salt is generated randomly and appended to the result
	OSign::CStorageBuffer oCryptBuffer = OSign::Crypt::Encrypt(oBuffer, oPassword);

	// decrypt the buffer
	OSign::CStorageBuffer oDecryptBuffer = OSign::Crypt::Decrypt(oCryptBuffer, oPassword);

	// compare with the source
	std::string sDecryptData((char*)oDecryptBuffer.GetData(), oDecryptBuffer.GetLength());
	EXPECT_EQ(sDecryptData, sDataCrypt);
}

// buffer serialization
TEST_F(COSignTest, serialize_buffer_string)
{
	std::string sBuffer = "Hello, world";
	OSign::CStorageBuffer oBuffer;
	oBuffer.Add((unsigned char*)sBuffer.c_str(), sBuffer.length());

	std::string sBase64 = oBuffer.ToBase64();
	OSign::CStorageBuffer oDecodeBuffer;
	oDecodeBuffer.FromBase64(sBase64);

	std::string sDecodeBuffer((char*)oDecodeBuffer.GetData(), oDecodeBuffer.GetLength());

	EXPECT_EQ(sBuffer, sDecodeBuffer);
}

// signature
TEST_F(COSignTest, sign_buffer_string)
{
	// generate a new certificate
	OSign::CCertificate* pCert = new OSign::CCertificate();
	pCert->Generate();

	// signature buffer
	std::string sDataBuffer = "Hello, world!";
	OSign::CStorageBuffer oBuffer;
	oBuffer.Add((const unsigned char*)sDataBuffer.c_str(), sDataBuffer.length());

	// sign
	OSign::CStorageBuffer oBufferSign = pCert->Sign(oBuffer);
	// checking
	bool bIsValid = pCert->Verify(oBuffer, oBufferSign);
	delete pCert;

	EXPECT_EQ(bIsValid, true);
}

// storage serialization test via signature/verification
TEST_F(COSignTest, serialize_storage_by_sign)
{
	// generate a new certificate
	OSign::CCertificate* pCert = new OSign::CCertificate();
	pCert->Generate();

	// create a storage and add a certificate (the storage itself monitors the removal of the certificate)
	OSign::CStorage oStorage;
	oStorage.Add(pCert);

	// save storage
	OSign::CStorageBuffer oStorageBuffer;
	oStorage.Save(&oStorageBuffer);

	OSign::CStorage oStorageLoad;
	oStorageLoad.Load(&oStorageBuffer);

	// signature buffer
	std::string sDataBuffer = "Hello, world!";
	OSign::CStorageBuffer oBuffer;
	oBuffer.Add((const unsigned char*)sDataBuffer.c_str(), sDataBuffer.length());
	// sign
	OSign::CStorageBuffer oBufferSign = pCert->Sign(oBuffer);

	OSign::CCertificate* pCert2 = oStorage.Get(0);
	bool bIsValid = pCert2->Verify(oBuffer, oBufferSign);

	EXPECT_EQ(bIsValid, true);
}

// storage serialization test via signature/verification
TEST_F(COSignTest, serialize_storage_by_property)
{
	// generate a new certificate with settings
	std::map<std::wstring, std::wstring> properties;
	properties.insert(std::make_pair(OSign::Properties::Email, L"sign@onlyoffice.com"));
	properties.insert(std::make_pair(OSign::Properties::Phone, L"+00000000000"));
	std::wstring sNameTest = L"NameTest";
	std::wstring sValueTest = L"ValueTest";
	properties.insert(std::make_pair(sNameTest, sValueTest));

	OSign::CCertificate* pCert = new OSign::CCertificate();
	pCert->Generate(properties);

	// create a storage and add a certificate (the storage itself monitors the removal of the certificate)
	OSign::CStorage oStorage;
	oStorage.Add(pCert);

	// save storage
	OSign::CStorageBuffer oStorageBuffer;
	oStorage.Save(&oStorageBuffer);

	OSign::CStorage oStorageLoad;
	oStorageLoad.Load(&oStorageBuffer);

	std::wstring sValue = L"";
	OSign::CCertificate* pCert2 = oStorage.Get(0);

	std::map<std::wstring, std::wstring> mapProps = pCert2->GetProperties();
	std::map<std::wstring, std::wstring>::const_iterator iterFind = mapProps.find(sNameTest);
	if (iterFind != mapProps.end())
		sValue = iterFind->second;

	EXPECT_EQ(sValueTest, sValue);
}
