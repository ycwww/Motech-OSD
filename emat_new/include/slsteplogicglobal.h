///////////////////////////////////////////////////////////////////////////////
/*! \file   slsteplogicglobal.h
 *  \author Harald Vieten
 *  \date   24.11.2009
 *  \brief  Global definitions of step editor logic
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_STEP_LOGIC_GLOBAL_H
#define SL_STEP_LOGIC_GLOBAL_H


#include "slsteplogicexports.h"  
#include "slsteptemplates.h"
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QSet>


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   GLOBAL TYPEDEFS AND ENUMS
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*!
 *  \typedef SlStepChannelList
 *
 *  Defines a list of channels.
 */
typedef QList<int> SlStepChannelList;

/*!
 *  \typedef SlStepAxisList
 *
 *  Defines a list of axes.
 */
typedef QList<int> SlStepAxisList;

/*!
 *  \typedef SlStepAdjustableSpindleIndexList
 *
 *  Defines a list of adjustable spindle indices.
 */
typedef QList<uint> SlStepAdjustableSpindleIndexList;

#define SL_STEP_Y_AXIS_NO       0x00     //!< no Y axis
#define SL_STEP_Y_AXIS_GEO_AX   0x01     //!< Y axis is geo axis
#define SL_STEP_Y_AXIS_TRAANG   0x02     //!< Y axis because of TRAANG
#define SL_STEP_Y_AXIS_2TRA     0x04     //!< Y axis because of 2Tra
#define SL_STEP_Y_AXIS_ROTE     0x08     //!< Y axis because of ROTE 
#define SL_STEP_Y_AXIS_MAVY     0x10     //!< Y axis because of MAVY 


/////////////////////////////////////////////////////////////////////////////
// TYPEDEF SlStepNcConfigPtr
/////////////////////////////////////////////////////////////////////////////

class SlStepNcConfig;

/*!
 *  \typedef SlStepNcConfigPtr
 *
 *  Defines a shared pointer with reference counting 
 *  for class \ref SlStepNcConfig.
 */
typedef SlStepSharedPointer<SlStepNcConfig> SlStepNcConfigPtr;

#if defined(Q_OS_WIN)
   // import/export declaration for template code on windows
   template class SL_STEP_LOGIC_EXPORT SlStepSharedPointer<SlStepNcConfig>;
#endif 


/////////////////////////////////////////////////////////////////////////////
// TYPEDEF SlStepMDPtr
/////////////////////////////////////////////////////////////////////////////

class SlStepMD;

/*!
 *  \typedef SlStepMDPtr
 *
 *  Defines a shared pointer with reference counting for class 
 *  \ref SlStepMD.
 */
typedef SlStepSharedPointer<SlStepMD> SlStepMDPtr;

#if defined(Q_OS_WIN)
   // import/export declaration for template code on windows
   template class SL_STEP_LOGIC_EXPORT SlStepSharedPointer<SlStepMD>;
#endif 


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   struct SlStepProgramInfo
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*!
 *  \struct SlStepProgramInfo
 *
 *  Defines an info structure about a program
 */
struct SL_STEP_LOGIC_EXPORT SlStepProgramInfo
{
   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC DATA MEMBERS FOR DIRECT ACCESS
   ///////////////////////////////////////////////////////////////////////////

   QString     sFileName;        //!< file name of program 
   int         nChannel;         //!< channel of program


   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn SlStepProgramInfo ()
    *
    *  Default constructor. Creates an empty info structure object.
    */
   SlStepProgramInfo ();

   /*!
    *  \fn SlStepProgramInfo (const QString& rsFileName, int nChan)
    *
    *  \param rsFileName      file name of program 
    *  \param nChan           channel of program
    *
    *  Constructor. Creates an info structure object for given file name
    *  \a rsFileName and given channel \a nChannel.
    */
   SlStepProgramInfo (const QString& rsFileName, int nChan);

   /*!
    *  \fn SlStepProgramInfo (const QString& rsFileName, const QString& rsChan)
    *
    *  \param rsFileName      file name of program 
    *  \param rsChan          channel of program
    *
    *  Overloaded constructor provided for convinience.
    */
   SlStepProgramInfo (const QString& rsFileName, const QString& rsChan);

   /*!
    *  \fn SlStepProgramInfo (const SlStepProgramInfo& rOther)
    *
    *  \param rOther    other object
    *
    *  Overloaded constructor provided for convinience.
    */
   SlStepProgramInfo (const SlStepProgramInfo& rOther);


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC ACCESSORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn bool isEmpty () const
    *
    *  \return Returns true if this info structure is empty; 
    *          otherwise it return false.
    */
   bool isEmpty () const;

   /*!
    *  \fn void clear ()
    *
    *  Clears current program info type.
    */
   void clear ();


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn bool operator< (const SlStepProgramInfo& rOther) const
    *
    *  \param rOther    other object
    *
    *  \return Returns true if this object is less than the given other object
    *          \a rOther; otherwise it returns false.
    */
   bool operator< (const SlStepProgramInfo& rOther) const;

   /*!
    *  \fn bool operator== (const SlStepProgramInfo& rOther) const
    *
    *  \param rOther    other object
    *
    *  \return Returns true if this object is equal to the given other object
    *          \a rOther; otherwise it returns false.
    */
   bool operator== (const SlStepProgramInfo& rOther) const;

   /*!
    *  \fn bool operator!= (const SlStepProgramInfo& rOther) const
    *
    *  \param rOther    other object
    *
    *  \return Returns true if this object is NOT equal to the given other 
    *          object \a rOther; otherwise it returns false.
    */
   bool operator!= (const SlStepProgramInfo& rOther) const;


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC HELPER METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn QString trc () const
    *
    *  Helper method that builds a string for the trace.
    */
   QString trc () const;

}; // <-- struct SlStepProgramInfo

/*!
 *  \fn uint qHash (const SlStepProgramInfo& rItem)
 *
 *  \param rItem        item to calculate hash value for
 *
 *  Calculates a hash value for given program info item \a rItem.
 */
SL_STEP_LOGIC_EXTERN uint qHash (const SlStepProgramInfo& rItem);

/*!
 *  \typedef SlStepProgramInfoList
 * 
 *  Defines a list of program info structures
 */
typedef QList<SlStepProgramInfo> SlStepProgramInfoList;

// the whole template is generated once into the step utilities
//  -> so the allocation and release of memory is only done in the utilities lib
SL_STEP_LOGIC_EXTERN template class SL_STEP_LOGIC_EXPORT QList<SlStepProgramInfo>;

/*!
 *  \fn void sl_step_sort_by_channel (SlStepProgramInfoList& rInfoList)
 *
 *  \param rInfoList    list of programs to sort
 *
 *  Sorts given program info list \a rInfoList by its channels.
 */
SL_STEP_LOGIC_EXPORT void sl_step_sort_by_channel (SlStepProgramInfoList& rInfoList);

/*!
 *  \fn bool sl_step_contains_channel (SlStepProgramInfoList& rInfoList, int nChannel)
 *
 *  \param rInfoList    list of programs to query
 *  \param nChannel     channel to find
 *
 *  Returns true if given program info list \a rInfoList contains a program 
 *  for given channel \a nChannel; otherwise it returns false.
 */
SL_STEP_LOGIC_EXPORT bool sl_step_contains_channel (SlStepProgramInfoList& rInfoList, int nChannel);


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   TYPEDEF SlStepObjectType;
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/*!
 *  \typedef SlStepObjectType
 *
 *  Defines the type for step object type flags.
 */
typedef quint64 SlStepObjectType;

/*!
 *  \typedef SlStepObjectTypeList
 *
 *  Defines a list of step object types.
 */
typedef QList<SlStepObjectType> SlStepObjectTypeList;


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   struct SlStepProgramInfo
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/*!
 *  \struct SlStepEditorStepInfo
 *
 *  Defines a struct to store step infos provided by the step editor
 */
struct SL_STEP_LOGIC_EXPORT SlStepEditorStepInfo
{
   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC MEMBERS FOR DIRECT ACCESS
   ///////////////////////////////////////////////////////////////////////////

   long                 nBlockNumber;      //!< block number of cursor
   long                 nLevel;            //!< level of current step
   bool                 bIsStep;           //!< flag, if cursor is on step
   bool                 bIsProgramEnd;     //!< flag, if cursor is on program end
   long                 nFromBlockNumber;  //!< if step, block number of first block in step
   long                 nAmountOfBlocks;   //!< if step, amount of blocks in step
   SlStepObjectType     nType;             //!< if step, type of step
   int                  nConnection;       //!< if step, type of connection
   QString              sID;               //!< if step, step ID
   QString              sErrorTextID;      //!< if step, text ID of error message
   QString              sOpcode;           //!< if step, opcode
   QString              sAttributes;       //!< attribute string


   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   
   SlStepEditorStepInfo (long blockNumber = -1L);


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS FOR DIRECT ACCESS
   ///////////////////////////////////////////////////////////////////////////
   
   /*!
    *  \fn bool isValid() const
    *
    *  \return Returns true if step infos are valid;
    *          Otherwise it returns false.
    */
   bool isValid() const;

}; // <-- struct SlStepEditorStepInfo


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   struct SlStepFciNcInitData
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

struct SL_STEP_LOGIC_EXPORT SlStepNcInitData
{

   QByteArray            m_ax1Name;                 // 1. geo axis name  (X)
   QByteArray            m_ax2Name;                 // 2. geo axis name  (Y)
   QByteArray            m_ax3Name;                 // 3. geo axis name  (Z)
   QByteArray            m_ax1mName;                // 1. ipo axis name  (I)
   QByteArray            m_ax2mName;                // 2. ipo axis name  (J)
   QByteArray            m_ax3mName;                // 3. ipo axis name  (K)
   bool                  m_bIsMetric;               // true is metric, else inch
   long                  m_decimal;                 // decimal for inch or metric
   int                   m_nDisplayModeDiameterAx;  // display mode diameter axis
   int                   m_defaultPlaneTurning;     // default plane turning
   int                   m_defaultPlaneMilling;     // default plane milling

};

namespace SlStep
{
   SL_STEP_LOGIC_EXPORT long getNcInitData(int nChannel, SlStepNcInitData* pInitData);
}

#endif // ! SL_STEP_LOGIC_GLOBAL_H
