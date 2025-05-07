///////////////////////////////////////////////////////////////////////////////
/*! \file   slclsdcommon.h
 *  \author Walter Daners
 *  \date   28.08.2009
 *  \brief  Definition file for class SlClSdCommon
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_SETUP_DATA_COMMON_H_INCLUDED
#define SL_SETUP_DATA_COMMON_H_INCLUDED

#include "slhmifileaccessqt.h"
#include "slhmimakros.h"
#include "slstepglobal.h"
#include "slstepobjectinterface.h"
#include "slpmhelper.h"
#include "slgfwdialog.h"       
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



/*!
 *  \enum SlToolExistStateEnum
 *
 *  Defines possible states for setup data.
 */
enum SlToolExistStateEnum
{             
   SKIP             =  1,     //!< skip
   REMOVE_ALL       =  2,     //!< remove all tool
   REMOVE_NO        =  3,     //!< remove no 
   ABORT            =  4,     //!< abort
   YES              =  5,     //!< overwrite yes
};    
/*!
 *  \class SlClSdState
 *
 *  Defines the setup data state
 */
Q_DECLARE_FLAGS(SlToolExistState, SlToolExistStateEnum);


class SlToolExistStateData
{

public:

   SlToolExistStateData()
      : m_toolExistState(ABORT)
   {
   };

   SlToolExistState getToolDataState(void)
   {
      // get tool exist state
      return m_toolExistState;
   };
   
   void setToolDataState(SlToolExistState toolExistState)
   {
      // set tool exist state
      m_toolExistState = toolExistState;
   };

   QString getNewName (void)
   {
      // get new tool name
      return m_sNewName;
   };

   void setNewName (QString sName)
   {
      // set new tool name
      m_sNewName = sName;
   };

private:

   QString           m_sNewName;       // new tool name
   SlToolExistState  m_toolExistState; // tool exist state


};

/*! \class SlClSdInterface
 *
 */
class SlClSdInterface
{
   public:

   SlClSdInterface(void)
   {};

   virtual ~SlClSdInterface(void)
   {};

  /*!
   *  \fn virtual bool isSetupDataFile (const QString& rsFile) = 0;
   *
   *  \param rsFile        file name with path
   *
   *  Derived classes have to re-implement this method to do check 
   *  is setup data fiel. 
   *
   *  \return true when setup data file, else false; 
   */

   virtual bool isSetupDataFile (const QString& rsFile) = 0;

  /*!
   *  \fn virtual bool isSetupDataFile (const QString& rsFile) = 0;
   *
   *  \param rsFile        file name with path
   *
   *  Derived classes have to re-implement this method to do check 
   *  is setup data fiel. 
   *
   *  \return true when show softkey stetup data, else false; 
   */

   virtual bool showSetupDataSoftkey (const NodeInfo& rAttributes) = 0;


  /*!
   *  \fn virtual bool showParamSaveSoftkey (const NodeInfo& rAttributes) = 0;
   *
   *  \param rAttributes        file attributes
   *
   *  Derived classes have to re-implement this method to do check 
   *  is parameter save fiel. 
   *
   *  \return true when show softkey parameter save, else false; 
   */

   virtual bool showParamSaveSoftkey (const NodeInfo& rAttributes) = 0;

}; // <-- SlClSdInterface


class SlClSdInterfaceImpl : public SlClSdInterface
{
   public:

   SlClSdInterfaceImpl(void)
   {};

   virtual ~SlClSdInterfaceImpl(void)
   {};

   virtual bool isSetupDataFile (const QString& rsFile);

   virtual bool showSetupDataSoftkey (const NodeInfo& rAttributes);

   virtual bool showParamSaveSoftkey (const NodeInfo& rAttributes);

}; // <-- SlClSdInterface


#endif // SL_SETUP_DATA_COMMON_H_INCLUDED
