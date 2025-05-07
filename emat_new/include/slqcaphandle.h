///////////////////////////////////////////////////////////////////////////////
/*! \file   slqcaphandle.h
 *  \author Michael Schlemper
 *  \date   10.07.2018
 *  \brief  SlQCapHandle Class interface file
 *
 *  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
 *  Its not intended, to be included by SlCap clients directly, but through slcap.h
 *
 *  (C) Copyright Siemens AG A&D MC 2018. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLQCAPHANDLE_H
#define SLQCAPHANDLE_H

#include "ace/config.h"
#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif // ACE_LACKS_PRAGMA_ONCE 

#include "slcapdata.h"


// forward declarations
class SlQCapHandleImplInterface;


class SL_CAP_EXP SlQCapHandle
{
  friend class SlQCap;
  friend class SlQCapImplSeq;
  friend class SlQCapImplPar;
  friend class TwoCapsResolver;

public:
  // constructor
  SlQCapHandle();

  // copy constructor
  SlQCapHandle(const SlQCapHandle& hdl);

  // destructor
  virtual ~SlQCapHandle();

  // assignment operator
  SlQCapHandle& operator = (const SlQCapHandle& other);

  // equal operator
  bool operator == (const SlQCapHandle& other) const;

  // unequal operator
  bool operator != (const SlQCapHandle& other) const;

  bool valid() const;

  bool busy() const;

  bool suspended() const;

  void reset();

  unsigned traceValue() const;

private:

  SlQCapHandleImplInterface* m_pImpl;               /*!< Pointer to inner instance implementing the functionality and called via interface. */
};


#endif // SLQCAPHANDLE_H
