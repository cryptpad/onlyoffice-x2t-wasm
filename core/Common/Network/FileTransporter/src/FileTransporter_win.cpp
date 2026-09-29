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

#include "FileTransporter_private.h"
#include "../../../../DesktopEditor/common/StringExt.h"

#include <wininet.h>
#include <objbase.h>
#include <urlmon.h>
#pragma comment(lib, "Wininet")
#pragma comment(lib, "Ole32.lib")

#ifdef GetTempPath
#undef GetTempPath
#endif

//------------------------------------------------------------------------------------------------------

// Constant for the maximum number of characters per line
#define	MAX_SIZE						256
// Constant for the maximum number of bytes downloaded
#define DOWNLOAD_FILE_SIZE				32768
#define MAX_SINGLE_DOWNLOAD_FILE_SIZE 524288


// Constant to get the file size
#define CONTENT_RANGE		L"bytes 0-0/"
// Constant for the number of characters in CONTENT_RANGE
#define CONTENT_RANGE_SIZE	( 11/*sizeof ( CONTENT_RANGE )*/ - 1 )

namespace NSNetwork
{
	namespace NSFileTransport
	{
		class CFileTransporterBaseWin : public CFileTransporterBase
		{
		public :
			CFileTransporterBaseWin(const std::wstring &sDownloadFileUrl, bool bDelete = true) :
				CFileTransporterBase(sDownloadFileUrl, bDelete)
			{
			}

			CFileTransporterBaseWin(const std::wstring &sUploadUrl, const unsigned char* cData, const int nSize) :
				CFileTransporterBase(sUploadUrl, cData, nSize)
			{
			}

			CFileTransporterBaseWin(const std::wstring &sUploadUrl, const std::wstring &sUploadFilePath) :
				CFileTransporterBase(sUploadUrl, sUploadFilePath)
			{
			}

			virtual ~CFileTransporterBaseWin()
			{
				if ( m_pFile )
				{
					::fclose( m_pFile );
					m_pFile = NULL;
				}
			}

			virtual int DownloadFile() override
			{
				CoInitialize ( NULL );
				if ( /*S_OK != _DownloadFile ( m_sFileUrl )*/TRUE )
				{
					if (m_sDownloadFilePath.empty())
					{
						m_sDownloadFilePath = NSFile::CFileBinary::CreateTempFileWithUniqueName(NSFile::CFileBinary::GetTempPath(), L"DWD");
						if (NSFile::CFileBinary::Exists(m_sDownloadFilePath))
							NSFile::CFileBinary::Remove(m_sDownloadFilePath);
					}

					HRESULT hrResultAll = DownloadFileAll(m_sDownloadFileUrl, m_sDownloadFilePath);

					if(E_ABORT == hrResultAll /*&& m_bIsExit->load()*/)
					{
						//DeleteUrlCacheEntry(m_sDownloadFileUrl.c_str());
						CoUninitialize ();
						return hrResultAll;
					}
					if (S_OK != hrResultAll)
					{
						hrResultAll = (true == DownloadFilePS(m_sDownloadFileUrl, m_sDownloadFilePath)) ? S_OK : S_FALSE;
						CoUninitialize ();
						return hrResultAll;
					}
				}

				CoUninitialize ();
				m_bComplete = true;
				return S_OK;
			}

			virtual int UploadData() override
			{
				//stub
				return S_OK;
			}

			virtual int UploadFile() override
			{
				//stub
				return S_OK;
			}

		protected:
			FILE * m_pFile = nullptr;           // Handle to temporary file
			unsigned int _DownloadFile(std::wstring sFileUrl)
			{
				// Checking the connection status
				if ( FALSE == InternetGetConnectedState ( 0, 0 ) )
					return S_FALSE;

				wchar_t sTempPath[MAX_PATH], sTempFile[MAX_PATH];
				if ( 0 == GetTempPathW( MAX_PATH, sTempPath ) )
					return S_FALSE;

				if ( 0 == GetTempFileNameW( sTempPath, L"CSS", 0, sTempFile ) )
					return S_FALSE;

				m_pFile = ::_wfopen( sTempFile, L"wb" );
				if ( !m_pFile )
					return S_FALSE;

				m_sDownloadFilePath = std::wstring( sTempFile );

				// Opening the session
				HINTERNET hInternetSession = InternetOpenW ( L"Mozilla/4.0 (compatible; MSIE 5.0; Windows 98)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
				if ( NULL == hInternetSession )
					return S_FALSE;

				// Request header (currently contains 0 bytes (necessary for verification))
				std::wstring sHTTPHdr = L"Range: bytes=0-0";
				// Open the link to check for its existence, as well as support for chunked reads
				HINTERNET hInternetOpenURL = InternetOpenUrlW ( hInternetSession, sFileUrl.c_str(), sHTTPHdr.c_str(), -1, INTERNET_FLAG_RESYNCHRONIZE, 0 );
				if ( NULL != hInternetOpenURL )
				{
					// Opened successfully; check the response
					if ( TRUE == QueryStatusCode ( hInternetOpenURL, TRUE ) )
					{
						// The request was successful, check support for chunked reads and get the data size
						LONGLONG nFileSize = IsAccept_Ranges ( hInternetOpenURL );
						// Closing the handle
						InternetCloseHandle ( hInternetOpenURL );
						if ( -1 == nFileSize )
						{
							// Chunked reading isn't available
							// Closing the connection handle
							InternetCloseHandle ( hInternetSession );
							// Close the file (done on DownloadAll)
								// Fall back to writing it as a whole
							return S_FALSE;
						}
						else
						{
							// Chunked reading is available
							LONGLONG nStartByte = 0;
							while ( true )
							{
								// If the entire file has been downloaded, then exit
								if ( nStartByte == nFileSize - 1 )
								{
									// Closing the connection handle
									InternetCloseHandle ( hInternetSession );
									return S_OK;
								}
								LONGLONG nEndByte = nStartByte + DOWNLOAD_FILE_SIZE;
								// If the file ends, then we load fewer bytes (1 less than the size, because it starts from 0)
								if ( nEndByte >= nFileSize )
									nEndByte = nFileSize - 1;

								// Buffer for downloading
								BYTE arrBuffer [ DOWNLOAD_FILE_SIZE ] = { 0 };
								DWORD dwBytesDownload = DownloadFilePath ( hInternetSession, arrBuffer, nStartByte, nEndByte, sFileUrl );

								nStartByte = nEndByte;
								if ( -1 == dwBytesDownload )
								{
									// No data was read.
									// Closing the connection handle
									InternetCloseHandle ( hInternetSession );
									// Close the file (done on DownloadAll)
										// Fall back to writing it as a whole
									return S_FALSE;
								}

								// Write to a file
								::fwrite( (BYTE*)arrBuffer, 1, dwBytesDownload, m_pFile );
								::fflush( m_pFile );

								NSThreads::Sleep(10);
							}
						}
					}
					else
					{
						// Closing the connection handle
						InternetCloseHandle ( hInternetSession );
						// Close the file (done on DownloadAll)
							// Fall back to writing it as a whole
						return S_FALSE;
					}
				}
				else
				{
					// Closing the connection handle
					InternetCloseHandle ( hInternetSession );
					// Close the file (done on DownloadAll)
						// Fall back to writing it as a whole
					return S_FALSE;
				}

				// Closing the connection handle
				InternetCloseHandle ( hInternetSession );

				return S_OK;
			}
			DWORD DownloadFilePath ( HINTERNET hInternet, LPBYTE pBuffer, LONGLONG nStartByte, LONGLONG nEndByte, std::wstring sFileURL )
			{
				// Unopened session
				if ( NULL == hInternet )
					return -1;

				// Invalid parameters received
				if ( nStartByte > nEndByte || !pBuffer )
					return -1;

				// Request header (contains nEndByte - nStartByte bytes)
				std::wstring sHTTPHdr = L"Range: bytes=" + std::to_wstring(nStartByte) + L"-" + std::to_wstring(nEndByte);
				// Open the download link
				HINTERNET hInternetOpenURL = InternetOpenUrlW ( hInternet, sFileURL.c_str(), sHTTPHdr.c_str(), -1, INTERNET_FLAG_RESYNCHRONIZE, 0 );
				if ( NULL == hInternetOpenURL )
					return -1;
				// Opened successfully; check the response
				if ( FALSE == QueryStatusCode ( hInternetOpenURL, TRUE ) )
				{
					// Closing the connection handle
					InternetCloseHandle ( hInternetOpenURL );
					return -1;
				}

				// Number of bytes read?
				DWORD dwBytesRead = 0;
				// Reading the file
				if ( FALSE == InternetReadFile ( hInternetOpenURL, pBuffer, DOWNLOAD_FILE_SIZE, &dwBytesRead ) )
				{
					// Closing the connection handle
					InternetCloseHandle ( hInternetOpenURL );
					return -1;
				}

				// Closing the connection handle
				InternetCloseHandle ( hInternetOpenURL );

				return dwBytesRead;
			}

			BOOL QueryStatusCode ( HINTERNET hInternet, BOOL bIsRanges )
			{
				// Why check something for an unopened session?
				if ( NULL == hInternet )
					return FALSE;

				// Response result
				INT nResult = 0;
				// Response data size (should be = 4)
				DWORD dwLengthDataSize = 4;

				// Send the request; return FALSE on failure
				if ( FALSE == HttpQueryInfo ( hInternet, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &nResult, &dwLengthDataSize, NULL ) )
					return FALSE;

				// The request succeeded; check the response code
				if ( HTTP_STATUS_NOT_FOUND == nResult )
				{
					// Object not found, bad link or something else
					return FALSE;
				}
				else if ( ( HTTP_STATUS_OK != nResult && FALSE == bIsRanges ) || ( HTTP_STATUS_PARTIAL_CONTENT != nResult && TRUE == bIsRanges ) )
				{
					// The request failed for some reason
					return FALSE;
				}

				// Everything is fine, the request went through
				return TRUE;
			}
			// Checks whether a resource is available for chunked reading and returns -1 when unavailable, otherwise the data size
			LONGLONG IsAccept_Ranges ( HINTERNET hInternet )
			{
				// Why check something for an unopened session?
				if ( NULL == hInternet )
					return -1;

				// Response result
				wchar_t arrResult [ MAX_SIZE ] = { 0 };
				// Response Data Size
				DWORD dwLengthDataSize = sizeof ( arrResult );

				// Send the request; return FALSE on failure
				if ( FALSE == HttpQueryInfoW ( hInternet, HTTP_QUERY_CONTENT_RANGE, &arrResult, &dwLengthDataSize, NULL ) )
				{
					// Get the last error
					DWORD dwLastError = GetLastError ();
					if ( dwLastError == ERROR_HTTP_HEADER_NOT_FOUND )
					{
						// The header didn't arrive, which means the resource doesn't support reading in parts
						return -1;
					}

					// Some other error occurred - return FALSE
					return -1;
				}

				// If size is 0, then there is no header
				if ( 0 >= dwLengthDataSize )
					return -1;

				// Convert to std::wstring
				std::wstring strResult ( arrResult );

				// Contains the data size
				LONGLONG nFileSize = 0;

				try
				{
					// Find the index of the data size in the string
					INT nStartIndex = (INT)strResult.find ( CONTENT_RANGE );
					if ( -1 == nStartIndex )
						return -1;

					// Keep only the data size in the line
					strResult = strResult.substr( nStartIndex + CONTENT_RANGE_SIZE );
					// Now get the data size by converting the string to LONGLONG
					nFileSize = _wtoi64 ( strResult.c_str() );
					// Because actually numbering starts from 0 (so add 1 more byte)
					if ( 0 < nFileSize )
						nFileSize += 1;
				}
				catch ( ... )
				{
					// not found, return error
					return -1;
				}

				// The resource supports chunked reads; return its size
				return nFileSize;
			}

			HRESULT DownloadFileAll(std::wstring sFileURL, std::wstring strFileOutput)
			{
				if ( m_pFile )
				{
					::fclose( m_pFile );
					m_pFile = NULL;
				}

				DownloadProgress progress;
				progress.func_checkAborted = m_check_aborted;
				progress.func_onProgress = m_func_onProgress;
				// Download the file and report progress as a percentage
				return URLDownloadToFileW (NULL, sFileURL.c_str(), strFileOutput.c_str(), NULL, static_cast<IBindStatusCallback*>(&progress));
			}

			class DownloadProgress : public IBindStatusCallback {
			public:
				HRESULT __stdcall QueryInterface(const IID &,void **) {
					return E_NOINTERFACE;
				}
				ULONG STDMETHODCALLTYPE AddRef(void) {
					return 1;
				}
				ULONG STDMETHODCALLTYPE Release(void) {
					return 1;
				}
				HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, IBinding *pib) {
					return E_NOTIMPL;
				}
				virtual HRESULT STDMETHODCALLTYPE GetPriority(LONG *pnPriority) {
					return E_NOTIMPL;
				}
				virtual HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved) {
					return S_OK;
				}
				virtual HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, LPCWSTR szError) {
					return E_NOTIMPL;
				}
				virtual HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD *grfBINDF, BINDINFO *pbindinfo) {
					return E_NOTIMPL;
				}
				virtual HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC *pformatetc, STGMEDIUM *pstgmed) {
					return E_NOTIMPL;
				}
				virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID riid, IUnknown *punk) {
					return E_NOTIMPL;
				}

				virtual HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
				{
					if(func_checkAborted && func_checkAborted())
					{
						return E_ABORT;
					}
					if(ulProgressMax != 0)
					{
						int percent = static_cast<int>((100.0 * ulProgress) / ulProgressMax);
						if(func_onProgress)
							func_onProgress(percent);
					}
					return S_OK;
				}

				std::function<bool(void)> func_checkAborted = nullptr;
				std::function<void(int)> func_onProgress = nullptr;
			};

			void EscapeQuotesPS(std::wstring& command, bool isPath)
			{
				/*
				var symbols = [0x22, 0x27, 0x2018, 0x2019, 0x201a, 0x201b, 0x201c, 0x201d, 0x201e, 0x201f];
				var output = "";
				for (let i = 0; i < symbols.length; i++) output += (" " + encodeURI(String.fromCharCode(symbols[i])));
				console.log(output);

				result:
				"%22 %27 %E2%80%98 %E2%80%99 %E2%80%9A %E2%80%9B %E2%80%9C %E2%80%9D %E2%80%9E %E2%80%9F"
				*/

				std::wstring sTmp = L" ";

				if (isPath)
				{
					sTmp[0] = (wchar_t)'\\';   NSStringExt::Replace(command, sTmp, L"/");
				}

				sTmp[0] = (wchar_t)0x22;   NSStringExt::Replace(command, sTmp, L"%22");
				sTmp[0] = (wchar_t)0x27;   NSStringExt::Replace(command, sTmp, L"%27");
				sTmp[0] = (wchar_t)0x2018; NSStringExt::Replace(command, sTmp, L"%E2%80%98");
				sTmp[0] = (wchar_t)0x2019; NSStringExt::Replace(command, sTmp, L"%E2%80%99");
				sTmp[0] = (wchar_t)0x201a; NSStringExt::Replace(command, sTmp, L"%E2%80%9A");
				sTmp[0] = (wchar_t)0x201b; NSStringExt::Replace(command, sTmp, L"%E2%80%9B");
				sTmp[0] = (wchar_t)0x201c; NSStringExt::Replace(command, sTmp, L"%E2%80%9C");
				sTmp[0] = (wchar_t)0x201d; NSStringExt::Replace(command, sTmp, L"%E2%80%9D");
				sTmp[0] = (wchar_t)0x201e; NSStringExt::Replace(command, sTmp, L"%E2%80%9E");
				sTmp[0] = (wchar_t)0x201f; NSStringExt::Replace(command, sTmp, L"%E2%80%9F");
			}

			bool DownloadFilePS(const std::wstring& sFileURLOriginal, const std::wstring& strFileOutput)
			{
				STARTUPINFO sturtupinfo;
				ZeroMemory(&sturtupinfo,sizeof(STARTUPINFO));
				sturtupinfo.cb = sizeof(STARTUPINFO);

				std::wstring sFileDst = strFileOutput;
				std::wstring sFileURL = sFileURLOriginal;

				EscapeQuotesPS(sFileDst, true);
				EscapeQuotesPS(sFileURL, false);

				std::wstring sApp = L"powershell.exe –c \"(new-object System.Net.WebClient).DownloadFile('" + sFileURL + L"','" + sFileDst + L"')\"";
				wchar_t* pCommandLine = new wchar_t[sApp.length() + 1];
				memcpy(pCommandLine, sApp.c_str(), sApp.length() * sizeof(wchar_t));
				pCommandLine[sApp.length()] = (wchar_t)'\0';

				HANDLE ghJob = CreateJobObject(NULL, NULL);

				if (ghJob)
				{
					JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };

					// Configure all child processes associated with the job to terminate when the
					jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
					if ( 0 == SetInformationJobObject( ghJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli)))
					{
						CloseHandle(ghJob);
						ghJob = NULL;
					}
				}

				PROCESS_INFORMATION processinfo;
				ZeroMemory(&processinfo,sizeof(PROCESS_INFORMATION));
				BOOL bResult = CreateProcessW(NULL, pCommandLine, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sturtupinfo, &processinfo);

				if (bResult && ghJob)
				{
					AssignProcessToJobObject(ghJob, processinfo.hProcess);
				}

				::WaitForSingleObject(processinfo.hProcess, INFINITE);

				RELEASEARRAYOBJECTS(pCommandLine);

				return NSFile::CFileBinary::Exists(sFileDst);
			}
		};

		CFileTransporter_private::CFileTransporter_private(const std::wstring &sDownloadFileUrl, bool bDelete)
			: m_pInternal(new CFileTransporterBaseWin(sDownloadFileUrl, bDelete))
		{
			m_pInternal->m_check_aborted = std::bind(&CBaseThread::isAborted, this);
		}

		CFileTransporter_private::CFileTransporter_private(const std::wstring &sUploadUrl, const unsigned char* cData, const int nSize)
			: m_pInternal(new CFileTransporterBaseWin(sUploadUrl, cData, nSize))
		{
			m_pInternal->m_check_aborted = std::bind(&CBaseThread::isAborted, this);
		}

		CFileTransporter_private::CFileTransporter_private(const std::wstring &sUploadUrl, const std::wstring &sUploadFilePath)
			: m_pInternal(new CFileTransporterBaseWin(sUploadUrl, sUploadFilePath))
		{
			m_pInternal->m_check_aborted = std::bind(&CBaseThread::isAborted, this);
		}
	}
}
