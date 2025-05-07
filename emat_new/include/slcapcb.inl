///////////////////////////////////////////////////////////////////////////////
/*! \file   slcapcb.inl
 *  \author Hans Hubmann
 *  \date   01.10.2004
 *  \brief  SlCapCB Class inline implementation file
 *
 *  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
 *  Its not intended, to be included by SlCap clients directly, but through slcap.h
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


inline SlCapCBImplInterface* SlCapCB::impl() const
{
  return m_pCBImplIF;
}
