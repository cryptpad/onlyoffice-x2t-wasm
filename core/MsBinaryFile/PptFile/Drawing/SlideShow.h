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
#include "Elements.h"

namespace PPT
{
	class CTransition
	{
	public:
		bool	m_bAudioPresent;		// is there audio
		CAudioElement m_oAudio;			// audio

		BYTE	m_nEffectDirection;		// direction of effect
		BYTE	m_nEffectType;			// transition type

		bool	m_bLoopSound;			// loop audio
                bool	m_bStopSound;			// stop playing all audio before the transition

//                bool            m_bAdvClick;            // Attributes for true transition
//                int             m_nAdvTm;
                int		m_nSpeed;


		CTransition() : m_oAudio()
		{
			m_bAudioPresent		= false;
			
			m_nEffectType		= 0xff;
			m_nEffectDirection	= 0;

			m_bLoopSound		= false;
			m_bStopSound		= false;

//                        m_bAdvClick                     = true;
//                        m_nAdvTm                        = 0;
			m_nSpeed			= 2;
		}
		~CTransition()
		{
		}

		CTransition& operator=(const CTransition& oSrc)
		{
			m_bAudioPresent		= oSrc.m_bAudioPresent;
			
			m_nEffectType		= oSrc.m_nEffectType;
			m_nEffectDirection	= oSrc.m_nEffectDirection;

			m_bLoopSound		= oSrc.m_bLoopSound;
			m_bStopSound		= oSrc.m_bStopSound;

			m_nSpeed			= oSrc.m_nSpeed;

			return *this;
		}

		CTransition(const CTransition& oSrc)
		{
			*this = oSrc;
		}
	};
	
	class CSlideShowInfo
	{
	public:
		double	m_dSlideDuration;	// slide duration (excluding transition)
		bool	m_bHidden;			// Should I NOT show the slide when playing?

		CTransition	m_oTransition;	// transition

                bool	m_bAdvClick;        // allow auto-time transition
                bool    m_bManulClick;      // go to next on click

		CSlideShowInfo() : m_oTransition()
		{
                        m_dSlideDuration	= -1.0;
                        m_bHidden		= false;
                        m_bAdvClick		= false;
                        m_bManulClick           = true;
		}
		~CSlideShowInfo()
		{
		}

		CSlideShowInfo& operator=(const CSlideShowInfo& oSrc)
		{
			m_dSlideDuration	= oSrc.m_dSlideDuration;
			m_bHidden			= oSrc.m_bHidden;
                        m_bAdvClick		= oSrc.m_bAdvClick;

			m_oTransition		= oSrc.m_oTransition;
			return *this;
		}
		CSlideShowInfo(const CSlideShowInfo& oSrc)
		{
			*this = oSrc;
		}
	};
}
