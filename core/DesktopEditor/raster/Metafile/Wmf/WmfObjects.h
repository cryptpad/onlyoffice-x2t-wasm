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
#ifndef _METAFILE_WMF_WMFOBJECTS_H
#define _METAFILE_WMF_WMFOBJECTS_H

#include "../Common/MetaFileTypes.h"
#include "../Common/MetaFileObjects.h"

#include "WmfTypes.h"

#ifdef __linux__
    #include <string.h> //memset oO
#endif
namespace MetaFile
{
	typedef enum
	{
		WMF_OBJECT_UNKNOWN = 0x00,
		WMF_OBJECT_BRUSH   = 0x01,
		WMF_OBJECT_FONT    = 0x02,
		WMF_OBJECT_PEN     = 0x03,
		WMF_OBJECT_PALETTE = 0x04,
		WMF_OBJECT_REGION  = 0x05
	} EWmfObjectType;

	class CWmfObjectBase
	{
	public:
		CWmfObjectBase();
		virtual ~CWmfObjectBase();
		virtual EWmfObjectType GetType() const;
	};
	
	class CWmfBrush : public CWmfObjectBase, public IBrush
	{
	public:
		CWmfBrush();
		CWmfBrush(const TWmfLogBrush &oBrush);
		virtual ~CWmfBrush();
		virtual EWmfObjectType GetType() const override;
		
		void SetDibPattern(unsigned char* pBuffer, unsigned int unWidth, unsigned int unHeight);

		// IBrush
		int          GetColor()         const override;
		int          GetColor2()        const override;
		unsigned int GetStyle()         const override;
		unsigned int GetStyleEx()       const override;
		unsigned int GetHatch()         const override;
		unsigned int GetAlpha()         const override;
		unsigned int GetAlpha2()        const override;
		std::wstring GetDibPatterPath() const override;
		void GetBounds(double& left, double& top, double& width, double& height) const override;
		void GetCenterPoint(double& dX, double& dY) const override;
		void GetDibPattern(unsigned char** pBuffer, unsigned int &unWidth, unsigned int &unHeight) const override;

		void GetGradientColors(std::vector<long>& arColors, std::vector<double>& arPositions) const override;
	public:

		unsigned short ushBrushStyle;
		TRGBA          oColor;
		unsigned short ushBrushHatch;
		std::wstring   wsDibPatternPath;
		unsigned char* pDibBuffer;
		unsigned int   unDibWidth;
		unsigned int   unDibHeigth;
	};
	class CWmfFont : public CWmfObjectBase, public IFont
	{
	public:
		CWmfFont();
		virtual ~CWmfFont();

		virtual EWmfObjectType GetType() const override;

		// IFont
		double       GetHeight()      const override;
		std::wstring GetFaceName()    const override;
		int          GetWeight()      const override;
		bool         IsItalic()       const override;
		bool         IsStrikeOut()    const override;
		bool         IsUnderline()    const override;
		int          GetEscapement()  const override;
		int          GetCharSet()     const override;
		int          GetOrientation() const override;
	public:

		short         shHeight;
		short         shWidth;
		short         shEscapement;
		short         shOrientation;
		short         shWeight;
		unsigned char uchItalic;
		unsigned char uchUnderline;
		unsigned char uchStrikeOut;
		unsigned char uchCharSet;
		unsigned char uchOutPrecision;
		unsigned char uchClipPrecision;
		unsigned char uchQuality;
		unsigned char uchPitchAndFamily;
		unsigned char uchFacename[32]; // According to the specification, the name length shouldn't exceed 32 characters, including the null character at the end
	};
	class CWmfPalette : public CWmfObjectBase
	{
	public:
		CWmfPalette();
		virtual ~CWmfPalette();
		virtual EWmfObjectType GetType() const override;
	public:
		unsigned short    ushStart;
		unsigned short    ushNumberOfEntries;
		TWmfPaletteEntry* pPaletteEntries;
	};
	class CWmfPen : public CWmfObjectBase, public IPen
	{
	public:
		CWmfPen();
		virtual ~CWmfPen();
		virtual EWmfObjectType GetType() const override;

		// IPen
		int             GetColor()        const override;
		unsigned int    GetStyle()        const override;
		double          GetWidth()        const override;
		unsigned int    GetAlpha()        const override;
		double          GetMiterLimit()   const override;
		double          GetDashOffset()   const override;
		void            GetDashData(double*& arDatas, unsigned int& unSize) const override;
		const ILineCap* GetStartLineCap() const override;
		const ILineCap* GetEndLineCap()   const override;
	public:
		unsigned short ushPenStyle;
		TPointS        oWidth;
		TRGBA          oColor;
	};
	class CWmfRegion : public CWmfObjectBase, public IRegion
	{
	public:
		CWmfRegion();
		virtual ~CWmfRegion();
		virtual EWmfObjectType GetType() const override;
	public:
		short           shNextInChain; // not used
		short           shObjectType;  // not used
		int             shObjectCount; // not used
		short           shRegionSize;
		short           shScanCount;
		short           shMaxScan;
		TRectS          oBoundingRectangle;
		TWmfScanObject* pScans;
	};
}

#endif //_METAFILE_WMF_WMFOBJECTS_H
