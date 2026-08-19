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
#ifndef _ZIPBUFFER_H_
#define _ZIPBUFFER_H_

#include <string>
#include <vector>

#include "../../Common/kernel_config.h"
#include "../../DesktopEditor/common/Types.h"

// Works with archive in memory
class KERNEL_DECL CZipBuffer
{
private:
	// Archived data
	BYTE* m_zipFile;
	// Length of archived data
	DWORD m_sizeZip;
	// File
	struct CFile
	{
		// Relative path of the file in the archive
		std::string m_sPath;
		// File data
		BYTE* m_pData;
		// File length
		DWORD m_nLength;
		CFile(const std::string& sPath, BYTE* pData, DWORD nLength) : m_sPath(sPath), m_pData(pData), m_nLength(nLength) {}
	};
	// Archived file vector
	std::vector<CFile> m_arrFiles;

	friend class CZipFolderMemory;
public:
	// Creates an archive in memory
	CZipBuffer()
	{
		create();
	}
	// Opens an archive in memory, the transferred data must be freed after using the class
	CZipBuffer(BYTE* buffer, DWORD size)
	{
		open(buffer, size);
	}
	// Closes the archive and clears memory
	~CZipBuffer()
	{
		close();
	}

	// Creates an archive in memory
	void create();
	// Opens an archive in memory, the transferred data must be freed after using the class
	void open(BYTE* buffer, DWORD size);
	// Closes the archive and clears memory
	void close();
	// Moves a file in the archive
	void move(const std::string& sSrc, const std::string& sDst);

	// Returns a vector of paths in the archive
	std::vector<std::string> getPaths();
	// Saves the archive to the transferred memory, the received data must be freed
	void save(BYTE*& data, DWORD& length);
	// Returns a file relative to the path in the archive; the received data will be released after using the class
	void getFile(const std::string& sPath, BYTE*& data, DWORD& length);
	// A file is added relative to the path in the archive; the transferred data will be released after using the class
	void addFile   (const std::string& sPath, BYTE* data, DWORD length);
	// Deletes a file relative to the path in the archive
	bool removeFile(const std::string& sPath);
};

#endif // _ZIPBUFFER_H_
