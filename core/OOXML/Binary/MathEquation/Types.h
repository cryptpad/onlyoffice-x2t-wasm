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

#include <map>
#include "../../../DesktopEditor/common/Types.h"
#include "../../Base/Base.h"

namespace MathEquation
{
	struct TMathFont
	{
		std::string sName;
		bool        bItalic;
		bool        bBold;
	};

    typedef std::map<unsigned char, TMathFont> TFontMap;

	enum MBRACKETSTYPE
	{
		bracketsAngle            = 0x00, // < > Angle brackets
		bracketsRound            = 0x01, // ( ) Parentheses
		bracketsCurve            = 0x02, // { } Curly braces
		bracketsSquare           = 0x03, // [ ] Square brackets
		bracketsLine             = 0x04, // Vertical bar brackets (absolute value)
		bracketsDLine            = 0x05, // || ||Double line brackets
		bracketsFloor            = 0x06, // Brackets with corner at bottom
		bracketsCeil             = 0x07, // Brackets with corner at top
		bracketsSquareOpenOpen   = 0x08, // [ [
		bracketsSquareCloseClose = 0x09, // ] ]
		bracketsSquareCloseOpen  = 0x0a, // ] [
		bracketsSquareRound      = 0x0b, // [ )
		bracketsRoundSquare      = 0x0c  // ( ]

	};

	enum MFRACTIONTYPES
	{
		fractionRegular = 0, // Common fraction
		fractionSlanted = 1  // Slant fraction
	};

	enum MSCRIPTALIGN
	{
		scriptalignRight  = 0,
		scriptalignCenter = 1,
		scriptalignLeft   = 2
	};

	enum MBARTYPE
	{
		bartypeLine        = 0, // simple line
		bartypeDoubleLine  = 1, // double line
		bartypeArrowLeft   = 2, // left arrow
		bartypeArrowRight  = 3, // right arrow
		bartypeArrowDouble = 4  // double arrow (both left and right)
	};

	enum MARROWTYPE
	{
		arrowtypeLeft   = 0, // left arrow
		arrowtypeRight  = 1, // right arrow
		arrowtypeDouble = 2  // double arrow (both left and right)
	};

	enum MINTEGRALTYPE
	{
		integraltypeSingle             = 0, // Ordinary single integral without subscripts
		integraltypeSingleRSub         = 1, // Single integral with right subscript
		integraltypeSingleRSubSup      = 2, // Single integral with right upper and lower indices
		integraltypeSingleOriented     = 3, // Single oriented integral
		integraltypeSingleOrientedRSub = 4, // Single oriented integral with right subscript

		integraltypeDouble             = 5,  // Double integral without subscripts
		integraltypeDoubleRSub         = 6,  // Double integral with right subscript
		integraltypeDoubleOriented     = 7,  // Double oriented integral
		integraltypeDoubleOrientedRSub = 8,  // Double oriented integral with right subscript

		integraltypeTriple             = 9,  // Triple integral without subscripts
		integraltypeTripleRSub         = 10, // Triple integral with right subscript
		integraltypeTripleOriented     = 11, // Triple oriented integral
		integraltypeTripleOrientedRSub = 12, // Triple oriented integral with right subscript

		integraltypeSingleCSubSup      = 13, // Single integral with central superscript and subscript
		integraltypeSingleCSub         = 14, // Single integral with central subscript
		integraltypeSingleOrientedCSub = 15, // Single oriented integral with central subscript

		integraltypeDoubleOrientedCSub = 16, // Double oriented integral with central subscript
		integraltypeDoubleCSub         = 17, // Double integral with central subscript

		integraltypeTripleOrientedCSub = 18, // Triple oriented integral with central subscript
		integraltypeTripleCSub         = 19  // Triple integral with central subscript
	};

	enum MNARRAYTYPE
	{
		narySumCSub          = 0,  // Sum sign with central subscript
		narySumCSubSup       = 1,  // Sum sign with central subscript and superscript
		narySum              = 2,  // Sum sign without subscripts

		narySumRSub          = 3,  // Sum sign with right subscript
		narySumRSubSup       = 4,  // Sum sign with right lower and upper indices

		naryProdCSub         = 5,  // Product sign with central subscript
		naryProdCSubSup      = 6,  // Product sign with central subscript and superscript
		naryProd             = 7,  // Product sign without subscripts

		naryProdRSub         = 8,  // Product sign with right subscript
		naryProdRSubSup      = 9,  // Product sign with right lower and upper indices

		naryCoProdCSub       = 10, // Coproduct sign with central subscript
		naryCoProdCSubSup    = 11, // Coproduct sign with central subscript and superscript
		naryCoProd           = 12, // Coproduct sign without subscripts

		naryCoProdRSub       = 13, // Coproduct sign with right subscript
		naryCoProdRSubSup    = 14, // Coproduct sign with right lower and upper indices

		naryUnionCSub        = 15, // Union sign with central subscript
		naryUnionCSubSup     = 16, // Union sign with central subscript and superscript
		naryUnion            = 17, // Union sign without subscripts

		naryUnionRSub        = 18, // Union sign with right subscript
		naryUnionRSubSup     = 19, // Union sign with right subscript and superscript

		naryIntersectCSub    = 20, // Intersection sign with upper and lower limits
		naryIntersectCSubSup = 21, // Intersection sign with upper and lower limits and superscript
		naryIntersect        = 22, // Intersection sign without indexes

		naryIntersectRSub    = 23, // Intersection sign with right subscript
		naryIntersectRSubSup = 24  // Intersection sign with right lower and upper indices
	};

	enum MLONGDIVISION
	{
		longdivisionWithResult = 0, // Division sign without quotient
		longdivisionRegular    = 1  // Division sign with quotient
	};

	enum MANGLEBRACKETSWITHSEPARATORTYPE
	{
		angbrwithsepBoth  = 0, // < | >
		angbrwithsepLeft  = 1, // < |
		angbrwithsepRight = 2  // | >		
	};

	enum MEMBELTYPE
	{
		embelDot         = 0x02, // point .
		embelDDot        = 0x03, // two points..
		embelDDDot       = 0x04, // three dots...
		embelPrime       = 0x05, // stroke'
		embelDPrime      = 0x06, // two strokes"
		embelLPrime      = 0x07, // left stroke '
		embelTilde       = 0x08, // wave ~
		embelHat         = 0x09, // cap (hat) ^
		embelSlash       = 0x0a, // slash /
		embelRArrow      = 0x0b, // right arrow ->
		embelLArrow      = 0x0c, // left arrow <-
		embelDArrow      = 0x0d, // arrow in both directions <->
		embelRHarpoon    = 0x0e, // harpoon right
		embelLHarpoon    = 0x0f, // harpoon left
		embelStrikeout   = 0x10, // strikethrough
		embelBar         = 0x11, // line
		embelTPrime      = 0x12, // three strokes '''
		embelFrown       = 0x13, // arc up
		embelSmile       = 0x14, // arc down

		embelMin         = 0x02,
		embelMax         = 0x14
	};

	enum MMATRIXBORDERTYPE
	{
		matrixborderNone  = 0x00,
		matrixborderSolid = 0x01,
		matrixborderDash  = 0x02,
		matrixborderDot   = 0x03
	};

	enum MMATRIXHORALIGN
	{
		matrixhoralignLeft      = 0x00, // fit to the left edge
		matrixhoralignCenter    = 0x01, // center fit
		matrixhoralignRight     = 0x02, // fit to the right edge
		matrixhoralignEqualSign = 0x03, // Approaches sign =
		matrixhoralignCommaSign = 0x04  // sign fit,
	};

	enum MMATRIXVERALIGN
	{
		matrixveralignTop      = 0x00,
		matrixveralignBaseLine = 0x01,
		matrixveralginBottom   = 0x02
	};

	enum MSPECIALSYMBOLS
	{
		specialsymAlignment  = 0xeb00,
		specialsymZeroSpace  = 0xeb01,
		specialsymThinSpace  = 0xeb02,
		specialsymThickSpace = 0xeb04,
		specialsymLargeSpace = 0xeb05,
		specialsymOnePtSpace = 0xeb08
	};
}
