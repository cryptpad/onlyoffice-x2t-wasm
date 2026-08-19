/*
 * (c) Copyright Ascensio System SIA 2010-2023
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */
#pragma once

#include "../../../../DesktopEditor/common/File.h"
#include "../../../../DesktopEditor/graphics/BaseThread.h"
#include "../include/FileTransporter.h"
#include "../../../../DesktopEditor/common/ProcessEnv.h"

namespace NSNetwork
{
	namespace NSFileTransport
	{
		class CFileTransporterBase
		{
		public :
			CFileTransporterBase(const std::wstring &sDownloadFileUrl, bool bDelete)
			{
				m_sDownloadFilePath = L"";
				m_sDownloadFileUrl = sDownloadFileUrl;
				m_sUploadFilePath = L"";
				m_sUploadUrl = L"";

				m_bComplete = false;
				m_bDelete   = bDelete;
				m_eLoadType = DOWNLOADFILE;

				m_cData = NULL;
				m_nSize = 0;

				m_pSession = NULL;

				//                m_bIsExit = nullptr;
			}

			CFileTransporterBase(const std::wstring &sUploadUrl, const unsigned char* cData, const int nSize)
			{
				m_sDownloadFilePath = L"";
				m_sDownloadFileUrl = L"";
				m_sUploadFilePath = L"";
				m_sUploadUrl = sUploadUrl;

				m_bComplete = false;
				m_bDelete   = true;
				m_eLoadType = UPLOADDATA;

				m_cData = cData;
				m_nSize = nSize;

				m_pSession = NULL;

				//                m_bIsExit = nullptr;
			}

			CFileTransporterBase(const std::wstring &sUploadUrl, const std::wstring &sUploadFilePath)
			{
				m_sDownloadFilePath = L"";
				m_sDownloadFileUrl = L"";
				m_sUploadFilePath = sUploadFilePath;
				m_sUploadUrl = sUploadUrl;

				m_bComplete = false;
				m_bDelete   = true;
				m_eLoadType = UPLOADFILE;

				m_cData = NULL;
				m_nSize = 0;

				m_pSession = NULL;

				//                m_bIsExit = nullptr;
			}

			virtual ~CFileTransporterBase ()
			{
				if ( m_sDownloadFilePath.length() > 0 && m_bDelete )
				{
					NSFile::CFileBinary::Remove(m_sDownloadFilePath);
					m_sDownloadFilePath = L"";
				}
				//                m_bIsExit = nullptr;
			}

			virtual int DownloadFile() = 0;
			virtual int UploadFile() = 0;
			virtual int UploadData() = 0;

		public:
			std::wstring    m_sDownloadFilePath; // Path to the saved file on disk
			std::wstring    m_sDownloadFileUrl;// File download link
			std::wstring    m_sUploadFilePath; // Path to the file to upload to the server
			std::wstring    m_sUploadUrl;      // URL for uploading data

			bool            m_bComplete;       // Is the file downloaded or not?
			bool            m_bDelete;         // Whether to delete the file in the destructor

			typedef enum LoadType
			{
				DOWNLOADFILE,
				UPLOADFILE,
				UPLOADDATA
			} LoadType;

			LoadType m_eLoadType;              // Data/file upload/download type

			const unsigned char*  m_cData;     // Data in raw form for uploading
			int             m_nSize;           // Data size

			std::wstring    m_sResponse = L"";       // Server response

			std::function<void(int)> m_func_onComplete = nullptr;
			std::function<void(int)> m_func_onProgress = nullptr;
			std::function<bool(void)> m_check_aborted = nullptr;

			CSession* m_pSession;

			//            std::atomic<bool>* m_bIsExit; // To stop and exit the thread
		};

		class CFileTransporter_private : public NSThreads::CBaseThread
		{
		protected:
			// create depending on the platform
			CFileTransporterBase* m_pInternal;

		public:
			CFileTransporterBase* GetInternal()
			{
				return m_pInternal;
			}

		public:
			CFileTransporter_private(const std::wstring &sDownloadFileUrl, bool bDelete = true);
			CFileTransporter_private(const std::wstring &sUploadUrl, const unsigned char* cData, const int nSize);
			CFileTransporter_private(const std::wstring &sUploadUrl, const std::wstring &sUploadFilePath);

			virtual ~CFileTransporter_private()
			{
				Stop();
				if (NULL != m_pInternal)
					delete m_pInternal;
			}

			void SetDownloadFileUrl(const std::wstring &sDownloadFileUrl, bool bDelete = true)
			{
				m_pInternal->m_sDownloadFileUrl = sDownloadFileUrl;
				m_pInternal->m_bDelete = bDelete;
				m_pInternal->m_eLoadType = m_pInternal->DOWNLOADFILE;
			}

			void SetDownloadFilePath(const std::wstring& sDownloadFilePat)
			{
				m_pInternal->m_sDownloadFilePath = sDownloadFilePat;
			}

			std::wstring GetDownloadFilePath()
			{
				return m_pInternal->m_sDownloadFilePath;
			}

			bool IsFileDownloaded()
			{
				return m_pInternal->m_bComplete;
			}

			void SetUploadUrl(const std::wstring &sUploadUrl)
			{
				m_pInternal->m_sUploadUrl = sUploadUrl;
			}

			void SetUploadBinaryDara(const unsigned char* cData, const int nSize)
			{
				m_pInternal->m_cData = cData;
				m_pInternal->m_nSize = nSize;
				m_pInternal->m_eLoadType = m_pInternal->UPLOADDATA;
			}

			void SetUploadFilePath(const std::wstring &sUploadFilePath)
			{
				m_pInternal->m_sUploadFilePath = sUploadFilePath;
				m_pInternal->m_eLoadType = m_pInternal->UPLOADFILE;
			}

			std::wstring& GetResponse()
			{
				return m_pInternal->m_sResponse;
			}

			bool TransferSync()
			{
				this->Start( 1 );
				while ( this->IsRunned() )
				{
					NSThreads::Sleep( 10 );
				}
				return IsFileDownloaded();
			}

			void TransferAsync()
			{
				this->Start( 1 );
			}

			void SetSession(CSession* session)
			{
				m_pInternal->m_pSession = session;
			}

		protected :

			virtual DWORD ThreadProc ()
			{
				m_pInternal->m_bComplete = false;

				bool bIsCanUseNetwork = true;
				if (NSProcessEnv::IsPresent(NSProcessEnv::Converter::gc_allowNetworkRequest))
					bIsCanUseNetwork = NSProcessEnv::GetBoolValue(NSProcessEnv::Converter::gc_allowNetworkRequest);

				int hrResultAll = 0;

				if (bIsCanUseNetwork)
				{
					if(m_pInternal->m_eLoadType == m_pInternal->DOWNLOADFILE)
						hrResultAll = m_pInternal->DownloadFile();
					else if(m_pInternal->m_eLoadType == m_pInternal->UPLOADFILE)
						hrResultAll = m_pInternal->UploadFile();
					else if(m_pInternal->m_eLoadType == m_pInternal->UPLOADDATA)
						hrResultAll = m_pInternal->UploadData();
				}
				else
				{
					hrResultAll = 1;
				}

				if (0 == hrResultAll)
					m_pInternal->m_bComplete = true;
				else
				{
					if (NSFile::CFileBinary::Exists(m_pInternal->m_sDownloadFilePath))
						NSFile::CFileBinary::Remove(m_pInternal->m_sDownloadFilePath);
				}

				if (m_pInternal->m_func_onComplete)
					m_pInternal->m_func_onComplete(hrResultAll);

				m_bRunThread = FALSE;
				return 0;
			}
		};
	}
}
