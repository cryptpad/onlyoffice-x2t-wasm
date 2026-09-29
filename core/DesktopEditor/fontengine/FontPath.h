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
#ifndef _PATH_H
#define _PATH_H

#include "../common/Types.h"
#include <memory>
#include <string.h>
#include <stdlib.h>
#include "ftbitmap.h"
#include "ftimage.h"

#include "../graphics/pro/Fonts.h"

//-------------------------------------------------------------------------------------------------------------------------------
// TPathPoint
//-------------------------------------------------------------------------------------------------------------------------------

struct TPathPoint 
{
	double dX;
	double dY;
};

//-------------------------------------------------------------------------------------------------------------------------------
// CPath.nFlags
//-------------------------------------------------------------------------------------------------------------------------------

// Flag for the first point of any subpath
#define PathFirst         0x01

// Flag for the last point of any subpath
#define PathLast          0x02

// If the subpath is closed, then its last and first points must match, their flag in this case is the following
#define PathClosed        0x04

// Flag indicating that this point is a control point for a Bezier curve
#define PathCurve         0x08

//-------------------------------------------------------------------------------------------------------------------------------
// TPathHint
//-------------------------------------------------------------------------------------------------------------------------------

struct TPathHint 
{
	int nFirstControl;
	int nSecondControl;
	int nFirstPoint;
	int nLastPoint;
};

//-------------------------------------------------------------------------------------------------------------------------------
// CFontPath
//-------------------------------------------------------------------------------------------------------------------------------

class CFontPath : public NSFonts::IFontPath
{
public:

	CFontPath();
	virtual ~CFontPath();

	void Append(CFontPath *pPath);

	int MoveTo(double dX, double dY);

	int LineTo(double dX, double dY);

	int CurveTo(double dX1, double dY1, double dX2, double dY2, double dX3, double dY3);

	int Close();

	void Offset(double dDx, double dDy);

	void Reverse();

	void ToMM(double dHorDpi, double dVerDpi);

	int GetCount()
	{
		return m_nPointsCount;
	}
	void GetPoint(int nIndex, double *pdX, double *pdY, unsigned char *punFlag)
	{
		*pdX = m_pPoints[nIndex].dX;
		*pdY = m_pPoints[nIndex].dY;
		*punFlag = m_pFlags[nIndex];
	}

	INT GetCurPoint(double *pdX, double *pdY);

	// Add the StrokeAdjust flag.
	void AddStrokeAdjustHint(int nFirstControl, int nSecondControl, int nFirstPoint, int nLastPoint);
	
	virtual int ToInterface(NSFonts::ISimpleGraphicsPath* pPath);

private:

	CFontPath(CFontPath *pPath);
	void Resize(int nPointsCount);
	INT NoCurrentPoint()
	{
		return m_nCurSubpath == m_nPointsCount;
	}
	INT OnePointSubpath()
	{
		return m_nCurSubpath == m_nPointsCount - 1;
	}
	INT OpenSubpath()
	{
		return m_nCurSubpath < m_nPointsCount - 1;
	}

private:

	TPathPoint    *m_pPoints;      // Array of points
	unsigned char *m_pFlags;       // An array of flags indicating the value of a point in SubPath
	int            m_nPointsCount; // Number of points
	int            m_nSize;        // Allocated array size
	
	int            m_nCurSubpath;  // Number of the first point of the last SubPath

	TPathHint     *m_pHints;       //
	int            m_nHintsCount;
	int            m_nHintsSize;
};

#endif /* _PATH_H */
