///////////////////////////////////////////////////////////////////////////////
/*! \file   slclmccommon.h
 *  \author Rafael Baranowski
 *  \date   06.04.2011
 *  \brief  Definition file for class SlClMcCommon
 *          (Solution Line Common Logic Multiple Clamping)
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MULTIPLE_CLAMPING_COMMON_H_INCLUDED
#define SL_MULTIPLE_CLAMPING_COMMON_H_INCLUDED

#include "fileserviceadapter.h"  

#if !defined (SL_COMMON_LOGIC_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_COMMON_LOGIC_EXPORTS)
#        define SL_COMMON_LOGIC_EXPORT __declspec (dllexport)
#     else
#        define SL_COMMON_LOGIC_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_COMMON_LOGIC_EXPORT
#  endif
#endif

/*! \class SlClMcInterface
 *
 *  Defines an interface to provide following information about multiple clamping
 *  - is a file a multiple clamping data (configuration) file
 *  - is it allowed to offer the creation of multiple clampings at a given path
 */
class SlClMcInterface
{
   public:

   SlClMcInterface(void)
   {};

   virtual ~SlClMcInterface(void)
   {};

  /*!
   *  \fn virtual bool isMultipleClampingDataFile (const QString& rsFile) = 0;
   *
   *  \param rsFile        file name with path
   *  \return              true if 'rsFile' is a multiple clamping file,
   *                       else false
   *
   *  Derived classes must re-implement this method to return if 'rsFile'
   *  is a multiple clamping data file or not.
   */
   virtual bool isMultipleClampingDataFile (const QString& rsFile) = 0;

  /*!
   *  \fn virtual bool showMultipleClampingSoftkey (const NodeInfo& rAttributes) = 0;
   *
   *  \param rsFile        file name with path
   *  \return              true if creating a multiple clamping is allowed at
   *                       given node (rAttributes), else false; 
   *
   *  Derived classes must re-implement this method to return if it's allowed
   *  to create multiple clampings at node (rAttributes).
   *
   */
   virtual bool showMultipleClampingSoftkey (const NodeInfo& rAttributes) = 0;

}; // <-- SlClMcInterface


class SlClMcInterfaceImpl : public SlClMcInterface
{
   public:

   SlClMcInterfaceImpl(void)
   {};

   virtual ~SlClMcInterfaceImpl(void)
   {};

  /*!
   *  \fn virtual bool isMultipleClampingDataFile (const QString& rsFile);
   *
   *  \param rsFile        file name with path
   *  \return              true if 'rsFile' is a multiple clamping file,
   *                       else false
   *
   *  Derived classes must re-implement this method to return if 'rsFile'
   *  is a multiple clamping data file or not.
   */
   virtual bool isMultipleClampingDataFile (const QString& rsFile);

  /*!
   *  \fn virtual bool showMultipleClampingSoftkey (const NodeInfo& rAttributes) = 0;
   *
   *  \param rsFile        file name with path
   *  \return              true if creating a multiple clamping is allowed at
   *                       given node (rAttributes), else false; 
   *
   *  Derived classes must re-implement this method to return if it's allowed
   *  to create multiple clampings at node (rAttributes).
   *
   */
   virtual bool showMultipleClampingSoftkey (const NodeInfo& rAttributes);

}; // <-- SlClSdInterface

#endif // SL_MULTIPLE_CLAMPING_COMMON_H_INCLUDED
