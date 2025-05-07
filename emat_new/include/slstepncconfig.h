///////////////////////////////////////////////////////////////////////////////
/*! \file   slstepncconfig.h
 *  \author Harald Vieten / Stefan Peschke
 *  \date   22.11.2006
 *  \brief  Class definition file for class SlStepNcConfig
 *
 *  This file is part of the HMI Solutionline StepEditor.
 *
 * (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_STEP_NC_CONFIG_H
#define SL_STEP_NC_CONFIG_H


#include "slsteplogicexports.h"
#include "slmalogicdefs.h"
#include "slstepglobal.h"
#include "slsteptemplates.h"
#include "slmd.h"
#include <QtCore/QStringList>
#include <QtCore/QObject>
#include "slmalogic.h"

/*! \enum SlStepRotaryAxisEnum
*   Enum for the type of axis 
*/
enum SlStepRotaryAxisEnum
{
   SL_STEP_ROT_AT_GEOAXIS_1 = 1,    /*!< rotary axis at geoaxis 1 */
   SL_STEP_ROT_AT_GEOAXIS_2,        /*!< rotary axis at geoaxis 2 */
   SL_STEP_ROT_AT_GEOAXIS_3,        /*!< rotary axis at geoaxis 3 */
};

/*! \enum SlStepDefaultMDHighSpeedSettingsEnum
*   Enum for the type default high speed settings
*/
enum SlStepDefaultMDHighSpeedSettingsEnum
{
   SL_STEP_SCS_MILL_TOL_VALUE_ROUGH = 1,        /*!< default value for rough          SD 55446 $SCS_MILL_TOL_VALUE_ROUGH*/
   SL_STEP_SCS_MILL_TOL_VALUE_SEMIFIN,          /*!< default value for semifinish     SD 55447 $SCS_MILL_TOL_VALUE_SEMIFIN */
   SL_STEP_SCS_MILL_TOL_VALUE_FINISH,           /*!< default value for finish         SD 55448 $SCS_MILL_TOL_VALUE_FINISH */
   SL_STEP_SCS_MILL_TOL_VALUE_PRECISION,        /*!< default value for precision      SD 55449 $SCS_MILL_TOL_VALUE_PRECISION */
   SL_STEP_SCS_MILL_ORI_TOL_ROUGH,              /*!< default value for ori rough      SD 55451 $SCS_MILL_ORI_TOL_ROUGH */
   SL_STEP_SCS_MILL_ORI_TOL_SEMIFIN,            /*!< default value for ori semifinish SD 55452 $SCS_MILL_ORI_TOL_SEMIFIN */
   SL_STEP_SCS_MILL_ORI_TOL_FINISH,             /*!< default value for ori finish     SD 55453 $SCS_MILL_ORI_TOL_FINISH */
   SL_STEP_SCS_MILL_ORI_TOL_PRECISION,          /*!< default value for ori precision  SD 55454 $SCS_MILL_ORI_TOL_PRECISION */
}; // <-- enum SlStepDefaultMDHighSpeedSettingsEnum

///////////////////////////////////////////////////////////////////////////////
// typedef´s
///////////////////////////////////////////////////////////////////////////////

// for rotary axis in position pattern
// 1te: int: Kanalachsenummer der Rundachs
// 2te: int: Geoachsnummer der Achse um die Rundachse dreht
typedef QMap<int, int> SlStepRotaryAxisMap;

/*!
 *  \typedef QMap<int, QString> SlStepChannelNumberNameMap
 *
 *  Defines a map of channelnumbers and channelnames.
 */
typedef QMap<int, QString> SlStepChannelNumberNameMap;

/*!
*  \typedef QVector<int> SlStepChanAxisNumberVector
*
*  Defines a vector of channelsnumbers.
*/
typedef QVector<int> SlStepChanAxisNumberVector;

///////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////

#define  DEFAULT_LINUX_CHECK_THREAD_NICE_LEVEL 15    //!< default value of be nice as linux thread
#define  DEFAULT_WINDOWS_CHECK_THREAD_PRIO     -999  //!< default value of thread priority as widows thread
#define  DEFAULT_WINDOWS_THREAD_BOOST_ENABLED  true  //!< default value of thread boost on windows


class SL_STEP_LOGIC_EXPORT SlStepMaAxisInfo
{
public:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC TYPEDEFS AND ENUMS
   ///////////////////////////////////////////////////////////////////////////

  /*! \enum SlStepMaAxisTypEnum
   *   Enum for the typ of axis 
   */
   enum SlStepMaAxisTypEnum
   {
      AXIS_TYP_LINEAR = 0,    /*!< axis typ not a special meaning */
      AXIS_TYP_GEO,           /*!< axis typ is geo */
      AXIS_TYP_SPINDLE,       /*!< axis typ is c */
      AXIS_TYP_ROTATION,      /*!< axis typ is round */
   };

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   /*! \fn SlStepMaAxisInfo()
    *
    *  Constructor
    *
    */
   SlStepMaAxisInfo()
      : m_sAxisName(QString::null),
        m_enumAxisTyp(AXIS_TYP_LINEAR),
        m_nAxisNo(0),
        m_nGeoAxisIndex(-1),
        m_bPositioningAxis(false)
   {}

   /*! \fn virtual ~SlStepMaAxisInfo();
    *
    *  Destructor
    */
   ~SlStepMaAxisInfo()
   {}

   /*! \fn QString getAxisName(void) const;
    *
    *  return the axis name
    */
   QString getAxisName(void) const
   {
      return m_sAxisName;
   }

   /*! \fn void setAxisName(QString name);
    *
    *  set the axis name
    */
   void setAxisName(QString name)
   {
      m_sAxisName = name;
   }

   /*! \fn SlStepMaAxisTypEnum getAxisTyp(void);
    *
    *  return the axis typ
    */
   SlStepMaAxisTypEnum getAxisTyp(void)
   {
      return m_enumAxisTyp;
   }

   /*! \fn void setAxisTyp(SlStepMaAxisTypEnum typ);
    *
    *  set the axis typ
    */
   void setAxisTyp(SlStepMaAxisTypEnum typ)
   {
      m_enumAxisTyp = typ;
   }

   /*! \fn uint getAxisNo(void) const
    *
    *  return the axis number
    */
   uint getAxisNo(void) const
   {
       return m_nAxisNo;
   }

   /*! \fn void setAxisNo(uint nAxisNo);
    *
    *  set the axis number
    */
   void setAxisNo(uint nAxisNo)
   {
       m_nAxisNo = nAxisNo;
   }

   /*! \fn uint getGeoAxisIndex(void)
    *
    *  return the geo axis index
    */
   uint getGeoAxisIndex(void)
   {
       return m_nGeoAxisIndex;
   }

   /*! \fn void setGeoAxisIndex(uint nGeoAxisIndex);
    *
    *  set the geo axis index in case of geo axis type, default -1
    */
   void setGeoAxisIndex(int nGeoAxisIndex)
   {
       m_nGeoAxisIndex = nGeoAxisIndex;
   }

   /*! \fn uint getePositioningAxis(void)
    *
    *  return axis is position axis
    */
   bool getPositioningAxis(void)
   {
       return m_bPositioningAxis;
   }

   /*! \fn void setPositioningAxis(bool bIsPositionAxis)
    *
    *  set axis is position axis
    */
   void setPositioningAxis(bool bIsPositionAxis)
   {
       m_bPositioningAxis = bIsPositionAxis;
   }

   
private:

   QString               m_sAxisName;     /*!< the name of the axis */
   SlStepMaAxisTypEnum   m_enumAxisTyp;   /*!< the typ of the axis */
   uint                  m_nAxisNo;       /*!< the channel axis number */
   int                   m_nGeoAxisIndex; /*!< the index of the geo axis */
   bool                  m_bPositioningAxis; /*!< axis is positioning axis */

}; // <-- SlStepMaAxisInfo


class SL_STEP_LOGIC_EXPORT SlStepTracylInfo
{
public:

  /*! \enum SlStepGeoAxisIndexEnum
   *   Enum for the typ of axis 
   */
   enum SlStepGeoAxisIndexEnum
   {
      ROTARY_AT_NO_INIT = 0,   /*!< no init*/
      ROTARY_AT_AXIS_X,        /*!< rotary at axis x */
      ROTARY_AT_AXIS_Y,        /*!< rotary at axis y */
      ROTARY_AT_AXIS_Z,        /*!< rotary at axis z */
   };

  /*! \enum SlStepGeoAxisIndexEnum
   *   Enum for the typ of axis 
   */
   enum SlStepTracylTypeNumberEnum
   {
      TRAFO_TYPE_NO_INIT = 0,  /*!< no init*/
      TRAFO_TYPE_512 = 512,    /*!< trafo type 512 */
      TRAFO_TYPE_513,          /*!< trafo type 513 */
      TRAFO_TYPE_514,          /*!< trafo type 514 */
      TRAFO_TYPE_4096 = 4096,  /*!< trafo type 4096 */
      TRAFO_TYPE_TRAANG = 1024, /*!< trafo type 1024 */
   };

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   /*! \fn SlStepTracylInfo()
    *
    *  Constructor
    *
    */
   SlStepTracylInfo()
      : m_nTrafoTyp(TRAFO_TYPE_NO_INIT),
        m_nRotaryAxisNumber(0),
        m_nGeoAxisNumberToRotary(ROTARY_AT_NO_INIT),
        m_plane(0)
   {}


   /*! \fn virtual ~SlStepTracylInfo();
    *
    *  Destructor
    */
   ~SlStepTracylInfo()
   {}


   /*! \fn SlStepTracylTypeNumberEnum getTrafoTyp(void)
    *
    *  return the trafo typ
    */
   SlStepTracylTypeNumberEnum getTrafoTyp(void)
   {
       return m_nTrafoTyp;
   }

   /*! \fn void setTrafoTyp(SlStepTracylTypeNumberEnum nTrafoTyp);
    *
    *  set trafo typ (512/513/514)
    */
   void setTrafoTyp(SlStepTracylTypeNumberEnum nTrafoTyp)
   {
       m_nTrafoTyp = nTrafoTyp;
   }


   /*! \fn SlStepPlaneToggle setPlane (void)
    *
    *  set the plane 
    */
   void setPlane (SlStepPlaneToggle nPlane)
   {
      m_plane = nPlane;
   }

   /*! \fn SlStepPlaneToggle getPlane (void)
    *
    *  return the plane 
    */
   SlStepPlaneToggle getPlane (void)
   {
      return m_plane;
   }

   /*! \fn int getRotaryAxisNumber(void)
    *
    *  get number from rotary axis
    */
   int getRotaryAxisNumber(void)
   {
       return m_nRotaryAxisNumber;
   }

   /*! \fn void setRotaryAxisNumber(int nRotaryAxisIdx)
    *
    *  set number from rotary axis
    */
   void setRotaryAxisNumber(int nRotaryAxisNumber)
   {
       m_nRotaryAxisNumber = nRotaryAxisNumber;
   }

   /*! \fn int getChanAxisNumberToRotary(void)
    *
    *  get number for chan axis number to rotary
    */
   SlStepGeoAxisIndexEnum getGeoAxisNumberToRotary(void)
   {
       return m_nGeoAxisNumberToRotary;
   }

   /*! \fn void setChanAxisNumberToRotary(int nGeoAxisNumberToRotary);
    *
    *  set number for chan axis number to rotary
    */
   void setGeoAxisNumberToRotary(SlStepGeoAxisIndexEnum nGeoAxisNumberToRotary)
   {
       m_nGeoAxisNumberToRotary = nGeoAxisNumberToRotary;
   }
   

private:

   SlStepTracylTypeNumberEnum  m_nTrafoTyp;
   int                         m_nRotaryAxisNumber;
   SlStepGeoAxisIndexEnum      m_nGeoAxisNumberToRotary;
   SlStepPlaneToggle           m_plane;

}; // <-- SlStepMaAxisInfo


/*!
 *  The default precision of float values
 */
const long SL_STEP_DEFAULT_PRECISION = 3;


///////////////////////////////////////////////////////////////////////////////
// GLOBAL TYPE DEFINITIONS AND ENUMS
///////////////////////////////////////////////////////////////////////////////

/*!
 *  \enum SlStepDiameterStateGCodeResetEnum
 *
 *  Defines an enum type to declare the possible form MD 20150: $MC_GCODE_RESET_VALUES[28]
 */
enum SlStepDiameterStateGCodeResetEnum
{
   SL_STEP_GCODE_RESET_VALUE_DIAMOFF = 1,  //!< radius by G90/G91
   SL_STEP_GCODE_RESET_VALUE_DIAMON  = 2,  //!< diameter by G90/G91
   SL_STEP_GCODE_RESET_VALUE_DIAM90  = 3   //!< diameter by G90, radius by G91
};
 
class SlStepNcConfigPrivate;
class SlMaLogic;
class SlStepMD;
class SlCap;

/*!\class SlStepNcConfig
 *
 *  Class for configuration NC/StepEditor 
 */
class SL_STEP_LOGIC_EXPORT SlStepNcConfig : public SlStepSharedData
{
public:
   // declare destoyer as friend  --  destroyer needs access to destructor
   friend class SlStepNcConfigManager;

   // declare cache starting dongle as friend
   friend class SlStepNcConfigCacheEnabled;

   ///////////////////////////////////////////////////////////////////////////
   // TYPE DEFINITIONS AND ENUMS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \typedef QVector<QVariant> ValueList
    *
    *  Defines a list of machine data values.
    */
   typedef QVector<QVariant> ValueList;

   /*!
    *  \typedef QList<SlStepMaAxisInfo> AxisInfoList
    *
    *  Defines a list of axis infomation like axisname, typ. 
    */
   typedef QList<SlStepMaAxisInfo> AxisInfoList;

   /*!
    *  \typedef QVector<SlStepTracylInfo> TrafoInfoVector
    *
    *  Defines a vector of tracyl data.
    */
   typedef QVector<SlStepTracylInfo> TrafoInfoVector;

   /*!
    *  \enum McsTechnology
    *
    *  This defines the technologies for the step editor.
    */
   enum McsTechnology
   {
      MCS_TECHNO_NOT_SET = 0,             //!< no technology set yet
      MCS_TECHNO_TURNING = 1,             //!< technology turning
      MCS_TECHNO_MILLING = 2,             //!< technology milling
      MCS_TECHNO_CIRCULAR_GRINDING = 3,   //!< technology circular grinding
      MCS_TECHNO_SURFACE_GRINDING = 4,    //!< technology surface grinding
   };

   /*!
   *  \enum AxisUsageEnum
   *
   *  Defines all possible axis usages
   */
   enum AxisUsageEnum
   {
      AXIS_USAGE_NO_SPECIAL_USAGE            = 0, //!< no special usage
      AXIS_USAGE_TOOL_SPINDLE                = 1, //!< tool spindle
      AXIS_USAGE_PORCH_TOOL_SPINDLE          = 2, //!< porch tool spindle
      AXIS_USAGE_MAIN_SPINDLE                = 3, //!< main spindle
      AXIS_USAGE_MAIN_SPINDLE_C_AXIS         = 4, //!< c axis of the main spindle
      AXIS_USAGE_COUNTER_SPINDLE             = 5, //!< counter spindle
      AXIS_USAGE_COUNTER_SPINDLE_C_AXIS      = 6, //!< c axis of the counter spindle
      AXIS_USAGE_COUNTER_SPINDLE_LINEAR_AXIS = 7, //!< lineal axis of the counter spindle
      AXIS_USAGE_TAILSTOCK                   = 8, //!< tailstock (dt. Reitstock)
      AXIS_USAGE_BACK_REST                   = 9, //!< back rest (dt. Lünette; Setzstock)
      AXIS_USAGE_B_AXIS                      = 10 //!< b-axis
   };

   /*!
   *  \enum JogFeedPerRevSourceEnum
   *
   *  Defines all possible states of the revolutional feedrate in JOG control setting(manual machine)
   */
   enum JogFeedPerRevSourceEnum
   {
      ONE_CONTROL    = 0,  //!< manual machine offers one feedrate control
                           //   the unit of the feedrate field can be toggled (mm/min; mm/U)

      TWO_CONTROLS   = -3  //!< manual machine offers two feedrate controls
                           //   1st feedrate field for rotating spindle: mm/U (unit cannot be toggled)
                           //   2nd feedrate field for stopped spindle: mm/min (unit cannot be toggled)
                           //   reason for this setting: if user toggles spindle speed to mm/U and main
                           //                            spindle is stopped user can't JOG because spindle
                           //                            doesn't rotate.
   };

   /*!
    *  \enum SpindleChuckDataEnum
    *
    *  Defines all possible states of the spindle chuck in program.
    */
   enum SpindleChuckDataEnum
   {
      SPINDLE_CHUCK_NO           = 0,     //!< no
      SPINDLE_CHUCK_ONLY_CHUCK   = 1,     //!< only futter/yes
      SPINDLE_CHUCK_COMPLETELY   = 2      //!< completely
   };

   /*!
 *  \enum SpindleLogicEnum
 *
 *  Defines for use the speedLogic with the section tfs spindle or all spindle.
 */
   enum SpindleLogicEnum
   {
      USED_TFS_SPINDLE_LOGIC = 0,       //!< used tfs spindle logic
      USED_ALL_SPINDLE_LOGIC = 1,       //!< used all spindle logic
   };


   /*!
    *  \enum TurningToolFixedEnum
    *
    *  Defines all possible states of the turning tool is fixed.
    */
   enum TurningToolFixedEnum
   {
      TURNING_TOOL_VARIABLE,         //!< turning tool is in tool spindle
      TURNING_TOOL_FIXED,            //!< turning tool is fixed
      TURNING_TOOL_FIXED_AVAILABLE   //!< turning tool is in tool spindle or fixed
   };

   /*!
    *  \enum KindOfRotaryAxisEnum
    *
    *  Defines all possible states of rotary axis to use.
    */
   enum KindOfRotaryAxisEnum
   {
      ROTARY_AXIS_POSITION_PATTERN,       //!< for positionpattern
      ROTARY_AXIS_CLAMPING,               //!< for clamping
   };

   /*!
    *  \enum TableForClampingEnum
    *
    *  Defines all possible states of table to use.
    */
   enum TableForClampingEnum
   {
      TABLE_NO_EXIST,  //!< no tisch
      TABLE_MILLING,   //!< table for milling
      TABLE_BORING,    //!< table for Boring 
   };

   /*!
    *  \enum FeaturesTechnologyZeroEnum
    *
    *  Defines all features that are blocked by handling/add channel or (MD52200 = 0 and MD?)
    */
   enum FeaturesTechnologyZeroEnum
   {
      FEATURES_TOOLS,             //!< every feature that shows any tools:
                                  //!< - tool display (machine) // Werkzeuganzeige
                                  //!< - tool options and input in tsm mask (machine jog) // Werkzeugoptionen und Eingabefeld in TSM
                                  //!< - tool list softkey (parameter) // Werkzeugliste
                                  //!< - tool wear softkey (parameter) // Werkzeugverschleiß
                                  //!< - oem tool list softkey (parameter) // OEM Werkzeigliste
                                  //!< - magazine softkey (parameter) // Magazin
                                  //!< - select tool softkey (editor) and tsm mask (machine jog) // Werkzeug auswählen
                                  //!< - save setup data softkey (program manager) // Rüstdaten sichern
                                  //!< - creating ttd files // TTD Datei
      FEATURES_SPINDLE,           //!< spindle features:
                                  //!< - spindle display (machine) // Spindelanzeige
                                  //!< - performance display (machine) // Leistungsanzeige
                                  //!< - spindle options and input in tsm mask (machine jog) // Spindeloptionen und Eingabefeld in TSM
                                  //!< - tsm softkey (machine): hidden if FEATURES_TOOLS and FEATURES_SPINDLE is disabled
      FEATURES_RETRACT,           //!< retract softkey (machine) // Rückziehen
      FEATURES_SYNCH_ACTION,      //!< synch.action. softkey (machine) // Synchr.aktion.
      FEATURES_CONTOUR,           //!< contour softkey (editor) // Kontur
      FEATURES_MISC,              //!< misc softkey (editor) // Diverses
      FEATURES_SIMULATION,        //!< simulation softkey (editor) // Simulation
      FEATURES_SIMULT_RECORDING,  //!< simul.record. softkey (machine) // Mitzeichnen
      FEATURES_MOLD_MAKING_VIEW   //!< mold mak. view softkey (editor) // Formenbauansicht
   };

   ///////////////////////////////////////////////////////////////////////////
   // ASSESSORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn static SlStepNcConfigPtr Exemplar (int nChanIndex = -1)
    *
    *  \param nChanIndex   channel index for the exemplar
    *
    *  \retval Pointer to the one and only singleton
    *
    *  Function to get the one and only pointer to the SlStepNcConfig.
    *
    *  If \a nChanIndex is -1 the returned nc config object is bound to the 
    *  current channel. If \a nChanIndex is >= 1 the returned nc config object
    *  is bound to this channel.
    */
   static SlStepNcConfigPtr Exemplar (int nChanIndex = -1);

   /*!
    *  \fn QString ncuPath () const
    *
    *  Returns the name of the NCU the nc config object is bound to.
    */
   QString ncuPath () const;

   /*!
    *  \fn int channel (void) const
    *
    *  Returns the channel index the nc config object is bound to.
    */
   int channel (void) const;

   /*!
    *  \fn QString channelName (void) const
    *
    *  Returns the channel name of the channel the nc config object is bound 
    *  to.
    */
   QString channelName (void) const;

   /*!
    *  \fn int numChannels (void) const
    *
    *  Returns number of channels available.
    */
   int numChannels (void) const;

   /*!
    *  \fn SlStepChannelList assignedChannelList (void) const
    *
    *  Returns a list of channels that are assigned to a mode group. This 
    *  considers "channel gaps".
    */
   SlStepChannelList assignedChannelList (void) const;

   /*! \fn SlStepChanelNumberNameMap channelNumbersToNamesMap (void) const
    *
    *  Returns a map with channelnumbers (key) and channelnames (value).
    */
   SlStepChannelNumberNameMap channelNumbersToNamesMap (void) const;

   /*! \fn bool waitMarkChannelNameOrNumber (void) const;
    *
    *  Returnvalue true: Cycle parameter could be a channel number or a channel name.
    *  Returnvalue false: Cycle parameter could only be a channel number.
    */
   bool waitMarkChannelNameOrNumber (void) const;

   /*! \fn QString channelInstancePath(int nChanNr)
    *
    *  \param  nChanNr channel number
    *
    *  \retval QString channelName
    *
    *  Provides the channel path of the channel with the given number.
    */
    QString channelInstancePath(int nChanNr);

   /*!
    *  \fn long refreshData (const SlStepChannelList& rChannelList = SlStepChannelList(), 
                             const AxisList& rAxisList = AxisList(),
                             bool bForceRefresh = false)
    *
    *  \param rChannelList   list of channels to refresh (1, 2, ...) (empty means all channels)
    *  \param rAxisList      list of axes to refresh (1, 2, ...) (empty means all axes)
    *  \param bForceRefresh  if true, refresh is done unconditional, else
    *                        refresh is done only, if requirement evaluation is true
    *
    *  \retval   return state (0 = OK)
    *
    *  Function to refresh the machine data.
    */
   long refreshData (const SlStepChannelList& rChannelList = SlStepChannelList(), 
                     const SlStepAxisList& rAxisList = SlStepAxisList(),
                     bool bForceRefresh = false);

   /*!
    *  \fn unsigned int numGeoAxes (void) const
    *
    *  \retval number of geometry axes
    */
   unsigned int numGeoAxes (void) const;

   /*!
    *  \fn QStringList geoAxesNameList (SlMaCoordinateSystemEnum coordSystem = SL_MA_WKS,
    *                                   SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const
    *
    *  \retval list of geometry axes names
    */
   QStringList geoAxesNameList (SlMaCoordinateSystemEnum coordSystem = SL_MA_WKS,
                                SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

   /*!
    *  \fn QStringList spindleNameList (void) const
    *
    *  \retval list of spindle names
    */
   QStringList spindleNameList (void) const;
                                                                              
   /*!
    *  \fn SlStepAdjustableSpindleIndexList adjustableSpindleIndexList (void) const
    *    *
    *  \retval list of spindle indices, which are adjustable
    */
   SlStepAdjustableSpindleIndexList adjustableSpindleIndexList (void) const;

   /*!
    *  \fn int masterSpindleSpindleListIndex (void) const
    *
    *  \retval returns the spindle list name index of the master spindle.
    *          -1 is returned, if master spindle not found, or master spindle not in spindle name list.
    */
   int masterSpindleSpindleListIndex (void) const;

   /*!
    *  \fn SlStepSpindleNameMap spindleNameMap (void) const
    *
    *  \retval map of main, tool and sub spindle names
    */
   SlStepSpindleNameMap spindleNameMap (void) const;

   /*!
    *  \fn unsigned int spinIndexAxis (unsigned int nSpinIndex, bool bGlobIndexMode) const
    *  \param  nSpinIndex  spindle index
    *  \param  bGlobIndexMode true -->global spindel index else chan dependent
    *
    *  \retval axis index of spindle
    */
   unsigned int spinIndexAxis (unsigned int nSpinIndex, bool bGlobIndexMode) const;

   /*!
    *  \fn SlMaSpinTurnStateEnum spindleTurnState (SlStepSpindleNameEnum nSpindleName = SL_STEP_SPINDLE_NAME_MAIN) const
    *  \param nSpindleName spindle name
    *  \retval SlMaSpinTurnStateEnum turn state of spindle
    *
    *  This function returns the turn state of a given spindle (main, sub, tool)
    */
   SlMaSpinTurnStateEnum spindleTurnState (SlStepSpindleNameEnum nSpindleName = SL_STEP_SPINDLE_NAME_MAIN) const;

   /*!
    *  \fn bool isSpindleSynchronized (SlStepSpindleNameEnum nSpindleName = SL_STEP_SPINDLE_NAME_MAIN, SlStepSpindleSyncPointEnum nSyncPoint = SL_STEP_SPINDLE_SYNC_POINT_1) const
    *  \param  nSpindleName   spindle name
    *  \param  nSyncPoint     synchronization point
    *  \retval true, if spindle is synchronized with given sync point
    *
    *  Returns whether the given spindle is synchronized with given synchronization point or not.
    */
   bool isSpindleSynchronized (SlStepSpindleNameEnum nSpindleName = SL_STEP_SPINDLE_NAME_MAIN, SlStepSpindleSyncPointEnum nSyncPoint = SL_STEP_SPINDLE_SYNC_POINT_1) const;

   /*!
    *  \fn unsigned int axisIndexGeo (unsigned int index) const
    *  \param geo axes index 0,1,2
    *  \param coordinateSystem mks, wks
    *  \param displayAxes skip axes depending on machine data
    *
    *  \retval axis index of geo axis
    */
   unsigned int axisIndexGeo (unsigned int index, 
                           SlMaCoordinateSystemEnum coordinateSystem = SL_MA_WKS, 
                           SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

   /*!
    *  \fn bool isScalingSystemMetric (void) const
    *
    *  \retval true,  the nc's scaling system is metric
    *          false, otherwise
    */
   bool isScalingSystemMetric (void) const;

   /*!
    *  \fn bool isTransformationPersistent (void) const
    *
    *  \retval true,  there is an persisent transformation
    *          false, otherwise
    */
   bool isTransformationPersistent (void) const;

   /*!
    *  \fn SlStepActiveTransformationEnum getActiveTransformation () const;
    *  \retval active transformation
    *
    *  Returns the active transformation.
    */
   SlStepActiveTransformationEnum getActiveTransformation () const;

   /*!
    *  \fn bool isMagnifyingGlassEnabled (void) const
    *
    *  \retval true,  tool measurement with magnifying glass in JOG enabled
    *          false, otherwise
    */
   bool isMagnifyingGlassEnabled (void) const;

   /*!
    *  \fn bool isPartsGripperEnabled (void) const
    *
    *  \retval true,  there is parts gripper
    *          false, otherwise
    */
   bool isPartsGripperEnabled (void) const;

   /*!
    *  \fn bool isSubSpindleEnabled (void) const
    *
    *  \retval true,  there is a counter spindle enabled
    *          false, otherwise
    */
   bool isSubSpindleEnabled() const;

   /*!
    *  \fn bool hasSubSpindle (void) const
    *
    *  \retval true,  if equipped with a counter spindle
    *          false, otherwise
    */
   bool hasSubSpindle (void) const;

   /*!
    *  \fn bool hasLinearSubSpindle (void) const
    *
    *  \retval true,  if counter spindle is equipped with a linear axis 
    *          false, otherwise
    */
   bool hasLinearSubSpindle (void) const;

   /*!
    *  \fn bool isToolSpindleEnabled (void) const
    *
    *  \retval true,  there is a tool spindle enabled
    *          false, otherwise
    */
   bool isToolSpindleEnabled (void) const;

   /*!
    *  \fn int spindleNameListIndex (SlStepSpindleNameEnum spindleType) const;
    *
    *  \param spindleType     type of spindle
    *  \return                index in list delivered by SlStepNcConfig::spindleNameList()
    *
    *  Return an index of the spindleNameList of the spindle with type 'spindleType'.
    *  If 'spindleType' is not contained in the spindle name list, -1 is returned
    */
   int spindleNameListIndex (SlStepSpindleNameEnum spindleType) const;

   /*!
    *  \fn bool isRestMaterialProcessEnabled (void) const
    *
    *  \retval true,  if rest material processing is enabled
    *          false, otherwise
    */
   bool isRestMaterialProcessEnabled (void) const;

   /*! \fn bool isAdvancedTopSurfaceToggleEnabled()
    *
    *  answers whether advanced/top surface toggle may be enabled
    */
   bool isAdvancedTopSurfaceToggleEnabled() const;

   /*! \fn bool isSmoothingToggleEnabled()
    *
    *  answers whether smoothing surface toggle may be disbaled
    */
   bool isSmoothingToggleEnabled() const;

   /*!
    *  \fn bool isTopSurfaceAllowed (void) const
    *
    *  \retval true,  top surface are unlock
    *          false, otherwise
    */
   bool isTopSurfaceAllowed (void) const;

   /*!
    *  \fn bool isDepthCalForMillCycleWithOutSafetyClearance (void) const
    *
    *  \retval true,  calculate depth with out safety clearance
    *          false, otherwise
    */
   bool isDepthCalForMillCycleWithOutSafetyClearance (void) const;

   /*!
    *  \fn bool isMachiningTimeEnabled(void)
    *
    *  machining time enabled depends on machine datas.
    */
   bool isMachiningTimeEnabled(void);

   /*!
    *  \fn bool advancedTechnologyAllowed (void) const
    *
    *  \retval true,  advanced technology are unlock
    *          false, otherwise
    */
   bool advancedTechnologyAllowed (void) const;

   /*!
    *  \fn bool isSurfaceTurningAllowed (void) const
    *
    *  \retval true,  surface technology are unlock
    *          false, otherwise
    */
   bool isSurfaceTurningAllowed (void) const;

   /*!
    *  \fn bool unlockedHighSpeedSettings (void) const
    *
    *  \retval true,  high speed settings are unlocked
    *          false, they are locked
    */
   bool unlockedHighSpeedSettings (void) const;

   /*!
    *  \fn bool cylErrorCompensationAllowed (void) const
    *
    *  \retval true,  if cylinder error compensation is unlocked
    *          false, otherwise
    */
   bool cylErrorCompensationAllowed (void) const;

   /*!
    *  \fn bool enableCombGrooving (void) const
    *
    *  \retval true,  if comb grooving allowed
    *          false, otherwise
    */
   bool enableCombGrooving(void) const;

   /*!
    *  \fn bool enableTwoChannelFciTurning (void) const
    *
    *  \retval true,  more channel contour turning are unlock
    *          false, otherwise
    */
   bool enableTwoChannelFciTurning (void) const;

   /*!
    *  \fn bool isTailstockEnabled (void) const
    *
    *  \retval true,  there is a tailstock enabled
    *          false, otherwise
    */
   bool isTailstockEnabled (void) const;

   /*!
    *  \fn bool isBalanceCuttingEnabled (void) const
    *
    *  \retval true,  there is a balance cutting enabled
    *          false, otherwise
    */
   bool isBalanceCuttingEnabled (void) const;

   /*! \fn bool isCircularThreadEnable (void) const
    *
    *  \retval true,  circular threading is enabled
    *          false, otherwise
    */
   bool isCircularThreadEnable (void) const;

   /*!
    *  \fn SpindleChuckDataEnum programSpindleChuckInput (void) const
    *
    *  \retval This method returns the value of MD 52218: $MCS_FUNCTION_MASK_TURN. Possible value
    *          are SPINDLE_CHUCK_ONLY_CHUCK if Bit 8 is true and Bit 9 is false or SPINDLE_CHUCK_COMPLETELY if
    *          Bit 8 is true and bit 9 is true, otherwise it returns SPINDLE_CHUCK_NO.
    */
   SpindleChuckDataEnum programSpindleChuckInput (void) const;

   /*!
    *  \fn bool fciRoughWithCycle95Enable (void) const
    *
    *  Returns true if MD 52218: $MCS_FUNCTION_MASK_TURN Bit12 active and advancedTechnology deactive else returns false.
    */
   bool fciRoughWithCycle95Enable (void) const; 

   /*!
    *  \fn bool isIsoMode (void) const;
    *
    *  Returns true if ISO mode is active in nc; otherwise it returns false.
    */
   bool isIsoMode (void) const;

   /*!
    *  \fn double getScalingValueInch (void) const;
    *
    *  \retval getScalingValueInch      scaling value inch
    *
    *  Function to get the scaling value for calculation inch to millimeter (default 25.4).
    */
   double getScalingValueInch (void) const;

   /*!
    *  \fn double getExternFloatingpointProg (void);
    *
    *  \retval true,    there is 1     no the point (.) behind the number     example: 123
    *          false,   there is 0     with the point (.) behind the number   example: 123.
    *
    *  Function to get the value for the point of behind number.
    */
   bool getExternFloatingpointProg (void);

  /*!
    *  \fn bool isSafty ()
    *
    *  Returns true if maschinensdatum is no 0, false is otherwise
    */
   bool isSafty ();

   /*!
    *  \fn int getEmpiricValueNum (void);
    *
    *  \retval empiricValueNum      available empiric value numbers
    *
    *  Function to get the available empiric value number (default 0).
    */
   int getEmpiricValueNum (void);

   /*!
    *  \fn QString getMeReportFileExtensionFromMD (void);
    *
    *  Function to get the file extension for meas report
    */
   QString getMeReportFileExtensionFromMD (void);

   /*!
    *  \fn int getMeanValueNum (void);
    *
    *  \retval meanValueNum      available mean value numbers
    *
    *  Function to get the available mean value number (default 0).
    */
   int getMeanValueNum (void);

   /*!
    *  \fn double getMaxFeedratePerRevolution (void);
    *
    *  \retval maxFeedratePerRevolution      maximum input value for the feedrate per revolution
    *
    *  Function to get the maximum input value for the feedrate per revolution (default 1).
    */
   double getMaxFeedratePerRevolution (void);

   /*!
    *  \fn double getMaxFeedratePerTime (void);
    *
    *  \retval maxFeedratePerTime      maximum input value for the feedrate per time
    *
    *  Function to get the maximum input value for the feedrate per time (default 10000).
    */
   double getMaxFeedratePerTime (void);

   /*!
    *  \fn double getMaxFeedratePerTooth (void);
    *
    *  \retval maxFeedratePerTooth      maximum input value for the feedrate per tooth
    *
    *  Function to get the maximum input value for the feedrate per tooth (default 1).
    */
   double getMaxFeedratePerTooth (void);

   /*!
    *  \fn double getMaxInputRangeGamma (void);
    *
    *  \retval getMaxInputRangeGamma      maximum input value for the range of gamma
    *
    *  Function to get the maximum input value for the range of gamma (default 5.0).
    */
   double getMaxInputRangeGamma (void);


   /*! \fn int maxInputWaitMarkerNumber (void);
    *  \return maximum allowed wait mark number
    *
    *  returns maximum allowed wait mark number
    */
   int maxInputWaitMarkerNumber (void);


   /*!
    *  \fn TurningToolFixedEnum getTurningToolFixed (void);
    *
    *  \retval getTurningToolFixed      turning tool is fixed or variable in tool spindle
    *
    *  Function to get turning tool is fixed or variable in tool spindle.
    */
   TurningToolFixedEnum getTurningToolFixed (void);

   /*!
    *  \fn int getNumberOfCuttingEdges () const
    *
    *  \retval nNumberOfCuttingEdges      number of cutting edges
    *
    *  Function to get the number of cutting edges
    *  Possible return values are: 1 ... 9
    */
   int getNumberOfCuttingEdges () const;

   /*!
    *  \fn bool isOptDNumbersExist () const
    *
    *  Returns true if optional D numbers exist for tool container 
    *  of current channel; otherwise it returns false.
    */
   bool isOptDNumbersExist () const;

   /*!
    *  \fn int maxNumberReplacementTools () const
    *
    *  \retval nMaxNumberReplacementTools      number of sister tools
    *
    *  Function to get the number of sister tools
    */
   int maxNumberReplacementTools () const;

   /*!
    *  \fn bool isSisterToolAvailable (void) const
    *
    *  \retval true,  sister tool is available
    *          false, otherwise
    */
   bool isSisterToolAvailable (void) const;

   /*!
    *  \fn bool gearStepChangeEnabledBySpindleNameListIndex (int nSpindleIndex, int nMinGearSteps = 2) const;
    *  \param  nSpindleIndex           index of a spinde of the spindle list (see SLStepNcConfig::spindleNameList())
    *  \param  nMinGearSteps           minimum desired number of gear steps
    *
    *  Function to get if gear state changes are enabled, that means,
    *  the content of MD $MA_GEAR_STEP_CHANGE_ENABLE (Bit0 or Bit1) is set
    *  and additional the number of gear steps is greater or equal nMinGearSteps.
    *  Usually nMinGearSteps is 1 in program and 2 in manual.
    */
   bool gearStepChangeEnabledBySpindleNameListIndex (int nSpindleIndex, int nMinGearSteps = 2) const;

   /*!
    *  \fn bool gearStepChangeEnabled (int nAxisIndex, int nMinGearSteps = 2) const;
    *  \param  nAxisIndex              axis index
    *  \param  nMinGearSteps           minimum desired number of gear steps
    *
    *  Function to get if gear state changes are enabled, that means,
    *  the content of MD $MA_GEAR_STEP_CHANGE_ENABLE (Bit0 or Bit1) is set
    *  and additional the number of gear steps is greater or equal nMinGearSteps.
    *  Usually nMinGearSteps is 1 in program and 2 in manual.
    */
   bool gearStepChangeEnabled (int nAxisIndex, int nMinGearSteps = 2) const;

   /*!
    *  \fn int getNumberOfGearSteps (int nAxisIndex = 1);
    *  \param  nAxisIndex              axis index
    *  \retval nNumberOfGearSteps      number of gear steps
    *
    *  Function to get the number of gear steps depending on the axis index.
    *  Possible return values are: 0...5
    */
   int getNumberOfGearSteps (int nAxisIndex = 1);

   /*!
    *  \fn bool isAxisPositioningAxis (int nAxisIndex = 1)
    *  \param  nAxisIndex              axis index
    *
    *  \retval isPositionAxis          is axis position axis
    *
    *  return true -> axis is position axis ($MA_BASE_FUNCTION_MASK Bit6=1), else false
    */
   int isAxisPositioningAxis (int nAxisIndex /*= 1*/);

   /*!
    *  \fn bool isProgramStepAllowed () const
    *
    *  Read MD 19730 $ON_HMI_FUNCTION_MASK[0]. Is Programstep allowed return true, else return false 
    */
   bool isProgramStepAllowed () const;

   /*!
   *  \fn bool isIdentifyToolDemandAllowed() const
   *
   *  Read MD 19730 $ON_HMI_FUNCTION_MASK[0]. Is Bit 17 = 1 -> identify tool demand allowed return true, else return false
   */
   bool isIdentifyToolDemandAllowed() const;

   /*!
    *  \fn bool isDxfReaderAllowed () const
    *
    *  Read MD 19730 $ON_HMI_FUNCTION_MASK[1]. Is DxfReader allowed return true, else return false 
    */
   bool isDxfReaderAllowed () const;

   /*!
    *  \fn bool is3DImportAllowed () const
    *
    *  Read MD 19730 $ON_HMI_FUNCTION_MASK[1]. If 3D-Import is allowed returns true, else returns false
    */
   bool is3DImportAllowed() const;

   /*!
    *  \fn bool isCutDataLogicAllowed() const
    *
    *  It returns true if cut data logic (Walter Tool web service) is allowed;
    *  otherwise it returns false.
    */
   bool isCutDataLogicAllowed() const;

   /*!
    *  \fn bool isInterpolationAllowed () const
    *
    *  Read MD 19730 $ON_HMI_FUNCTION_MASK[1]. Is interpolation allowed return true, else return false 
    */
   bool isInterpolationAllowed () const;

   /*!
    *  \fn bool isIMachiningAllowed () const
    *
    *  Read MD 19730 $ON_HMI_FUNCTION_MASK[1]. Is iMachining allowed return true, else return false
    */
   bool isIMachiningAllowed () const;

   /*!
    *  \fn bool isManualMachineAllowed () const
    *
    *  Returns true if the option bit for manual machine is set;
    *  otherwise it returns false.
    */
   bool isManualMachineAllowed () const;

   /*!
    *  \fn bool isSetResetNpvInSettableWorkOffsetNpvEnable () const
    *
    *  Returns true if the option bit for set/reset npv in mask settable work offset is set;
    *  otherwise it returns false.
    */
   bool isSetResetNpvInSettableWorkOffsetNpvEnable() const;

   /*!
    *  \fn bool isTracylEnabled () const
    *
    *  \retval n tracyl enable    true/false
    *
    *  Function to get the tracyl mode
    *  Possible return values are:
    *    true : tracyl enable
    *    false: tracyl disable
    */
   bool isTracylEnabled () const;

   /*!
    *  \fn bool isSimpleFormInputModeEnabled () const
    *
    *  Returns true if the option bit for simple step mask input mode is set;
    *  otherwise it returns false.
    */
   bool isSimpleFormInputModeEnabled () const;

   /*!
    *  \fn bool isMoldMakingViewEnabled () const
    *
    *  Returns true if mold making view should not displaying
    *  otherwise it returns false.
    */
   bool isMoldMakingViewEnabled () const;

   /*!
    *  \fn bool getClampingMode (void);
    *
    *  \retval nClamping      clamping mode
    *
    *  Function to get the clamping mode
    *  Possible return values are:
    *    true : no clamping
    *    false: clamping allowed
    */
   bool getClampingMode (void);

   /*!
    *  \fn bool getBreakControlMode (void);
    *
    *  \retval nBreakControl      breaking control mode
    *
    *  Function to get the breaking mode
    *  Possible return values are:
    *    true : no break controll
    *    false: break controll allowed
    */
   bool getBreakControlMode(void);


   /*!
    *  \fn bool getInsideRearAllowed (void);
    *
    *  Function to get if inside and rear machining is allowed
    */
   bool getInsideRearAllowed (void);

   /*! \fn uint getDisplayThreadTechnology(void);
    *  \return techDisplay   
    *
    *  The machine date decides whether the threads technology parameters are displayed.
    *  1: technology parameter are displayed, tapping with compensation chuck
    *  2: technology parameter are displayed, tapping without compensation chuck
    *  4: tapping without encoder is possible for Shop Mill and Shop Turn, tapping with compensation chuck
    */
   uint getDisplayThreadTechnology(void);

   /*! \fn bool isConstCuttingSpeedBasedOnDiamOfCenteringActive(void);
    *
    *  returns true if constant cutting speed based on the diameter of the centering is active, false is otherwise
    */
   bool isConstCuttingSpeedBasedOnDiamOfCenteringActive(void);

   /*! \fn uint getNumberOfTrafoRecords(void);
    *  \return number of swivel data record
    *
    *  returns the number of transformationsrecords in kinematic chains
    */
   uint getNumberOfTrafoRecords(void) const;

   /*! \fn uint getNumberOfToolCarrier(void);
    *  \return number of swivel data record
    *
    *  returns the number of swivel data records
    */
   uint getNumberOfToolCarrier(void) const;

   /*! \fn bool isSwivelEnable (void) const;
    *  \return: Info, is swivel enable
    *
    *  returns the info whether swivel is enable
    */
   bool isSwivelEnable (void) const;

   /*! \fn bool isBetaGamaWithTcAllowed (void) const;
    *  \return: Info, is swivel enable
    *
    *  returns the info whether swivel is enable
    */
   bool isBetaGamaWithTcAllowed (void) const;

   /*! \fn bool isKinematicTransformationEnable (void);
    *  \return: Info, is kinematic transformation enable
    *
    *  returns the info whether kinematic transformation is enable
    */
   bool isKinematicTransformationEnable (void) const;  

   /*! \fn bool isKinematicTransformationAllowed (void) const;
    *  \return: Info, is kinematic transformation enable
    *
    *  returns the info whether the mask use kinematic transformation
    */
   bool isKinematicTransformationAllowed (void) const;
   
   /*! \fn bool isGrindingAlignAllowed (void) const
    *  \return: Info, is grinding align allowed
    *
    *  returns the info whether machine configuration supports grinding align
    *  (Schwenken B-Achse auf Rundschleifmaschine)
    */
   bool isGrindingAlignAllowed (void) const;

   /*! \fn bool getSwivelDisplayOptions(void);
    *  \return: display options
    *
    *  returns display options for swivel mask
    *  0x01 = field swivel = no is enable
    */
   uint getSwivelDisplayOptions (void);

   /*! \fn bool toolCarrierSelectionByTool(void) const
    *
    *  returns 'true' if tool carrier is selected by tool, else 'false'.
    */
   bool toolCarrierSelectionByTool(void) const;

   /*! \fn uint getSwivelInitRetracking(void);
    *  \return: initalise state of retraction
    *
    *  0 = no change
    *  1 = no retraction
    *  2 = Z
    *  3 = Z XY
    *  4 = tool direction max.
    *  5 = tool direction inc.
    */
   uint getSwivelInitRetracking (void);

   /*! \fn uint getInitSwivelMode(void);
    *  \return: initalise state of swivel mode
    *
    *  0 = axis by axis
    *  1 = direct mode
    */
   uint getInitSwivelMode (void);

   /*! \fn uint getSwivelInitTracking (void);
    *  \return: initalise state of tracking
    *
    *  0 = no change
    *  1 = no tracking
    *  2 = tracking
    */
   uint getSwivelInitTracking (void);

   /*! \fn double getMachiningPositionSubSpindle(void);
    *
    *  returns park position of subspindle
    */
   double getMachiningPositionSubSpindle(void);

   /*! \fn double getDrillCentralOffsetLimit(void);
    *  \return: limt
    *
    *  returns limit of the centric offset
    *  see drill centric
    */
   double getDrillCentralOffsetLimit(void);

   /*! \fn double getTurnRoughReleaseDistance(int location);
    *  \param   location              location of machining
    *  \return: release distance depending on external / internal machining
    *
    *  returns release distance depending on external / internal machining
    */   
   double getTurnRoughReleaseDistance(int location);

   /*! \fn double getTurnContInterRetraction(void)
    *
    *  returns the turn cont inter retraction.
    */   
   double getTurnContInterRetraction(void);

   /*! \fn double getMaJogSafetyClearance(void);
    *  \return: safety clearance
    *
    *  returns the safety clearance for maschine JOG
    *  cycle masks
    */
   double getMaJogSafetyClearance(void);

   /*! \fn double double getMaJogReleasePlane(void);
    *  \return: release plane
    *
    *  returns the release plane for maschine JOG
    *  cycle masks
    */
   double getMaJogReleasePlane(void);

   /*! \fn double getDefaultMDHighSpeedSettings(SlStepDefaultMDHighSpeedSettingsEnum settingMD);
    *
    * folgenden MD werden gelesen 
      SD 55446 $SCS_MILL_TOL_VALUE_ROUGH     default value for rough
      SD 55447 $SCS_MILL_TOL_VALUE_SEMIFIN   default value for semifinish
      SD 55448 $SCS_MILL_TOL_VALUE_FINISH    default value for finish
      SD 55449 $SCS_MILL_TOL_VALUE_PRECISION default value for precision
      SD 55451 $SCS_MILL_ORI_TOL_ROUGH       default value for ori rough
      SD 55452 $SCS_MILL_ORI_TOL_SEMIFIN     default value for ori semifinish
      SD 55453 $SCS_MILL_ORI_TOL_FINISH      default value for ori finish
      SD 55454 $SCS_MILL_ORI_TOL_PRECISION   default value for ori precision

    *  returns the default value of MD for high speed settings
    */
   double getDefaultMDHighSpeedSettings(SlStepDefaultMDHighSpeedSettingsEnum settingMD);

   /*!
    *  \fn QString getDiameterAxis (void);
    *
    *  Function to get the geo axis with plan axis to display the diameter
    */
   QString getDiameterAxis (void);

   /*!
    *  \fn SlStepDiameterState getDisplayModeDiameterAx (void);
    *
    *  \retval retDiameterMode      display mode for diameter
    *
    *  Function to get the display mode for diameter
    *  Possible values are: abs and inc is possible
    *    SL_STEP_DIAMETER_OFF
    *    SL_STEP_DIAMETER_ABS
    *    SL_STEP_DIAMETER_INC
    */
   SlStepDiameterState getDisplayModeDiameterAx (void);

   /*!
    *  \fn SlStepPlaneToggle getDefaultPlaneMilling (void);
    *
    *  \retval nPlane      default plane for milling (e. g. G17)
    *
    */
   int getDefaultPlaneMillingValue (void);

   /*!
    *  \fn SlStepPlaneToggle getDefaultPlaneMilling (void);
    *
    *  \retval nPlane      default plane for milling
    *
    *  Function to get the default plane for milling
    *  Possible return values are:
    *    SL_STEP_PLANE_TOGGLE_EMPTY
    *    SL_STEP_PLANE_TOGGLE_G17
    *    SL_STEP_PLANE_TOGGLE_G18
    *    SL_STEP_PLANE_TOGGLE_G19
    */
   SlStepPlaneToggle getDefaultPlaneMilling (void);

   /*!
    *  \fn int getDefaultPlaneTurningValue (void);
    *
    *  \retval nPlane      default plane for turning (e.g. G18)
    *
    */
   int getDefaultPlaneTurningValue (void);

   /*!
    *  \fn SlStepPlaneToggle getDefaultPlaneTurning (void);
    *
    *  \retval nPlane      default plane for turning
    *
    *  Function to get the default plane for turning
    *  Possible return values are:
    *    SL_STEP_PLANE_TOGGLE_EMPTY
    *    SL_STEP_PLANE_TOGGLE_G17
    *    SL_STEP_PLANE_TOGGLE_G18
    *    SL_STEP_PLANE_TOGGLE_G19
    */
   SlStepPlaneToggle getDefaultPlaneTurning (void);

   /*!
    *  \fn bool getTransmit (void);
    *
    *  Function to get if transmit exists.
    */
   bool getTransmit (void);

   /*!
    *  \fn bool getTracyl (void);
    *
    *  Function to get if tracyl exists.
    */
   bool getTracyl (void);

   /*!
    *  \fn bool getTraang (void);
    *
    *  Function to get if traang exists.
    */
   bool getTraang (void) const;

   /*!
    *  \fn bool getRote(void)  const 
    *
    *  Function to get if rote (Compile-Zyklus: Kinematische Transformation „Rotierender Exzenter“) exists
    */
   bool getRote(void) const;

   /*!
    *  \fn bool get2Tra(void)  const 
    *
    *  Function to get if 2Tra (doppeltransmit) exists
    */
   bool get2Tra(void) const;

   /*!
    *  \fn bool getMavy(void)  const 
    *
    *  Function to get if Mavy (Compile-Zyklus) exists
    */
   bool getMavy(void) const;

   /*!
    *  \fn long getYAxis (int& rnReasons);
    *
    *  \param rnReasons      reasons for y axis existing
    *
    *  Function to get if a Y axis exists.
    *  Possible reasons are:
    *    SL_STEP_Y_AXIS_GEO_AX
    *    SL_STEP_Y_AXIS_TRAANG
    */
   long getYAxis (int& rnReasons);

   /*!
    *  \fn bool getBAxis (void) const;
    *
    *  Function to get if a B axis exists.
    *  \return true, if a B axis exist
    */
   bool getBAxis (void) const;

   /*!
    *  \fn bool checkMDCutEdgePosAllowed (void) const;
    *
    *  Function to get if a check cutting edge exists.
    *  \return true, if a check cutting edge exist
    */
   bool checkMDCutEdgePosAllowed (void) const;

   /*!
    *  \fn bool isControlSettingByLoadTotalLoad(void) const;
    *
    *  Function to get information kind of control setting by load.
    *  \return true is total load
    *          false is load of workpiece 
    */
   bool isControlSettingByLoadTotalLoad(void) const;

   /*!
    *  \fn bool getResetModeUnitMeasuringSystem (void) const;
    *
    *  Function to get the reset mode of the unit measuring system.
    *  \return true, if the unit measuring system is to be reset
    */
   bool getResetModeUnitMeasuringSystem (void) const;

   /*!
    *  \fn bool getDisplayUnitMeasuringSystem (void) const;
    *
    *  Function to get the display of the unit measuring system.
    *  \return true, if the unit measuring system is to be displayed
    */
   bool getDisplayUnitMeasuringSystem (void) const;

   /*!
    *  \fn McsTechnology getMcsTechnology (void) const
    *
    *  \return This method returns the value of MD $MCS_TECHNOLOGY. Possible 
    *          values are MCS_TECHNO_TURNING for turning or MCS_TECHNO_MILLING
    *          for milling. If no techonlogy is set it returns MCS_TECHNO_NOT_SET. 
    */
   McsTechnology getMcsTechnology (void) const;

   /*! \fn McsTechnology getMcsTechnologyExtension(void) const;
    *  \return This method returns the value of MD $MCS_TECHNOLOGY_EXTENSION. Possible 
    *          values are MCS_TECHNO_TURNING for turning or MCS_TECHNO_MILLING
    *          for milling. If no techonlogy is set it returns MCS_TECHNO_NOT_SET.
    *
    *   Is milling on a turningmaschine possible?
    *   Is turning on a millingmaschine possible?
    */
   McsTechnology getMcsTechnologyExtension(void) const;

   /*!
    *  \fn bool isTechnologyMillingConfigured (void) const;
    *
    *  Returns true if technology milling is in NC, false otherwise
    */
   bool isTechnologyMillingConfigured (void) const;

   /*!
    *  \fn bool getToolAsPlace (void) const
    *
    *  \return true, if tool as place is possible.
    */
   bool getToolAsPlace (void) const;

   /*!
    *  \fn bool getNckVersion (void) const
    *
    *  \return NCKs version number
    */
   double getNckVersion(void) const;

   /*!
    *  \fn unsigned int numNpvUserFrames (void) const
    *
    *  \retval number of npv user frames
    */
   unsigned int numNpvUserFrames (void) const;

   /*!
    *  \fn QString userFrameName (unsigned int frameIndexIn, bool isFastAccess, bool bIgnorIsoMode) const
    *
    *  \param frameIndexIn index from the frame
    *  \param isFastAccess default is false, access is without nck-access, name may differ from nck-name if frame-names in nck are changed
    *  \param bIgnorIsoMode default is false, intern the nc can't run with IOS-code
    *
    *  \retval name of npv user frames
    */
   QString userFrameName (unsigned int frameIndexIn, bool isFastAccess = false, bool bIgnorIsoMode = false) const;

   /*!
    *  \fn int userFrameNameIndex (const QString& frameNameIn, bool bIgnorIsoMode = false) const
    *
    *  \param frameNameIn G500, G54...
    *  \param bIgnorIsoMode default is false, intern the nc can't run with IOS-code
    *  \retval int index of the user frame, -1 is error, e.g. name not found, no index available
    *
    *  Provides the user frame index corresponding to the offset name: e.g. name G500 = index 0, G54 = index 1 .....
    */
   int userFrameNameIndex (const QString& frameNameIn, bool bIgnorIsoMode = false) const;

   /*!
    *  \fn unsigned int numBasisFramesChan (void) const
    *
    *  \retval number of npv channel basis frames
    */
   unsigned int numBasisFramesChan (void) const;

   /*!
    *  \fn unsigned int numBasisFramesGlob (void) const
    *
    *  \retval number of npv global basis frames
    */
   unsigned int numBasisFramesGlob (void) const;

   /*!
    *  \fn SlStepAxisOrderToggleEnum getDefaultAxesOrderForSwivelPlane (void) const
    *
    *  \retval default axes order for swivel plane
    */
   SlStepAxisOrderToggleEnum getDefaultAxesOrderForSwivelPlane(void) const;

   /*!
    *  \fn bool isMultiToolEnabled (void) const
    *
    *  \retval true,  multi tool is enabled
    *          false, otherwise
    */
   bool isMultiToolEnabled (void) const;

   /*! \fn bool isToolOffsetAdjustable (void) const
    *
    *  Reads MD $MC_RESET_MODE_MASK Bit0 und Bit6
    *    and MD $MC_TOOL_MANAGEMENT_MASK Bit 14
    *  to check whether tool offset is adjustable.
    *  \returns true, if tool offset is adjustable
    */
   bool isToolOffsetAdjustable (void) const;

   /*! \fn bool isNPVAdjustable (void) const
    *
    *  Reads MD $MC_GCODE_RESET_MODE[7] to check whether NPV is adjustable.
    *  In ISO mode: $MC_EXTERN_GCODE_RESET_MODE[13]
    *  \returns true, if NPV is adjustable
    */
   bool isNPVAdjustable (void) const;

   /*! \fn bool rotationAllowedInUserFrames (void) const
    *
    *  \returns 'true' if $MN_MM_NUM_GLOBAL_USER_FRAMES=0, else 'false'
    */
   bool rotationAllowedInUserFrames (void) const;

   /*! \fn bool isPlaneAdjustable (void) const
    *
    *  Reads MD $MC_GCODE_RESET_MODE[5] to check whether plane is adjustable.
    *  In ISO mode: milling $MC_EXTERN_GCODE_RESET_MODE[1]
    *               turning $MC_EXTERN_GCODE_RESET_MODE[15]
    *  \returns true, if plane is adjustable
    */
   bool isPlaneAdjustable (void) const;

   /*! \fn bool isSpindleAdjustable (int nAxis) const
    *
    *  Reads machine datas $MN_M_NO_FCT_EOP and $MA_SPIND_ACTIVE_AFTER_RESET[nAxis] to check whether spindle is adjustable.
    *  Spindles are adjustable only if machine data
    *     $MA_SPIND_ACTIVE_AFTER_RESET[nAxis] = 1
    *     OR
    *     $MA_SPIND_ACTIVE_AFTER_RESET[nAxis] = 2
    *     and $MN_M_NO_FCT_EOP is set (unequal -1)
    *  \returns true, if spindle is adjustable
    */
   bool isSpindleAdjustable (int nAxis) const;

   /*! \fn bool isSpeedTypeAdjustable (void) const
    *
    *  Reads MD $MC_GCODE_RESET_MODE[14] to check whether speed is adjustable (reset fest).
    *
    *  \returns true, if speed type is adjustable
    */
   bool isSpeedTypeAdjustable (void) const;

   /*! \fn bool isDrfOffsetEnabled (void) const
    *
    *  Reads MD $MCS_FUNCTION_MASK_DISP Bit14 to check whether DRF offset is enabled.
    *
    *  \returns true, if DRF offset is enabled
    */
   bool isDrfOffsetEnabled (void) const;

   /*! \fn bool isAaToolOffsetEnabled (void) const
    *
    *  Reads MD $MCS_FUNCTION_MASK_DISP Bit15 to check whether $AA_TOFF is enabled.
    *
    *  \returns true, if $AA_TOFF is enabled
    */
   bool isAaToolOffsetEnabled (void) const;

   /*! \fn bool isMinAaToolOffsetEnabled (void) const
    *
    *  Reads MD $MC_TOFF_MODE Bit6 to check whether minimal $AA_TOFF is enabled.
    *
    *  \returns true, if minimal $AA_TOFF is enabled
    */
   bool isMinAaToolOffsetEnabled (void) const;

   /*! \fn bool writeToNPVDisabled(void);
    *  \return: Info, is NPV describe unenable
    *
    *  returns the info if npv describe is unenable
    */
   bool writeToNPVDisabled(void);

   /*!
    *  \fn unsigned int getCurrentScalingSystem (void) const
    *
    *  \retval  the current scaling system (70, 71, 700 or 710)
    */
   unsigned int getCurrentScalingSystem (void) const;

   /*!
    *  \fn unsigned int getActPlane (void) const
    *
    *  \retval  the active plane (17, 18 or 19)
    */
   unsigned int getActPlane (void) const;

   /*!
    *  \fn SlStepPlaneToggle getActivePlane () const
    *
    *  \retval  the active plane (17, 18 or 19)
    *  Possible return values are:
    *    SL_STEP_PLANE_TOGGLE_EMPTY
    *    SL_STEP_PLANE_TOGGLE_G17
    *    SL_STEP_PLANE_TOGGLE_G18
    *    SL_STEP_PLANE_TOGGLE_G19
    */
   SlStepPlaneToggle getActivePlane () const;

   /*!
    *  \fn bool getIsFrameFineEnable (void) const
    *
    *  \retval  state of frame fine trans
    */
   bool getIsFrameFineEnable (void) const;

   /*!
    *  \fn uint getActFrameIndexChan (void) const
    *
    *  \retval  the active frame (G500, G54, G55...)
    */
   uint getActFrameIndexChan (void) const;

   /*!
    *  \fn bool isCoordinateSystemRelActive (void) const
    *
    *  \retval  returns if rel coordinate system is active
    */
   bool isCoordinateSystemRelActive (void) const;

   /*!
    *  \fn bool isCoordinateSystemENS (void) const
    *
    *  \retval  returns if ENS coordinate system is active
    */
   bool isCoordinateSystemENS (void) const;

   /*!
    *  \fn uint instanceChannelNumber() const
    *
    *  \return Returns the index of the channel of the logic instance 
    */
   uint instanceChannelNumber() const;

   /*!
    *  \fn QString instanceChannelString (void) const
    *
    *  \return Returns the index of the channel of the logic instance 
    *          as a string
    */
   QString instanceChannelString (void) const;

   /*!
    *  \fn int getCoordinateSystem  (void);
    *
    *  \retval nGetCoordinateSystem       number of coordinate system
    *
    *  Function to get the number of coordinate system
    *  Possible return values are: 0 ... 47
    */
   int getCoordinateSystem (void);

   /*!
    *  \fn SlStepDiameterStateGCodeResetEnum getMcGCodeResetValueDiam  (void);
    *
    *  \retval SlStepDiameterStateGCodeResetEnum: state of G code reset
    *
    *  Function to get information from $MC_GCODE_RESET_VALUES[28]
    *  Possible values are:
    *     SL_STEP_GCODE_RESET_VALUE_DIAMOFF = 1    radius by abs/inc
    *     SL_STEP_GCODE_RESET_VALUE_DIAMON  = 2    diameter by abs/inc
    *     SL_STEP_GCODE_RESET_VALUE_DIAM90  = 3    diameter by abs, radius by inc
    */
   SlStepDiameterStateGCodeResetEnum getMcGCodeResetValueDiam (void);

   /*!
    *  \fn SlStepSpeedToogleEnum getMcGCodeResetValueSpeedType (void) const
    *
    *  \retval SlStepSpeedToogleEnum: state of G code reset value
    *
    *  Function to get information from $MC_GCODE_RESET_VALUES[14]
    */
   SlStepSpeedToogleEnum getMcGCodeResetValueSpeedType (void) const;

   /*! \fn uint getDisplayResolutionMM(void);
    *  \return Resolution in mm   
    *
    * this function get information from MD 51000: $MNS_DISP_RES_MM
    */
   uint getDisplayResolutionMM(void);

   /*! \fn uint getDisplayResolutionMMFeedPerRev(void);
    *  \return Resolution feed per rev in mm   
    *
    * this function get information from MD 51001: $MNS_DISP_RES_MM_FEED_PER_REV
    */
   uint getDisplayResolutionMMFeedPerRev(void);

   /*! \fn uint getDisplayResolutionINCH(void);
    *  \return Resolution in INCH
    *
    * this function get information from MD 51010: $MNS_DISP_RES_INCH
    */
   uint getDisplayResolutionINCH(void);

   /*! \fn uint getDisplayResolutionINCHFeedPerRev(void);
    *  \return Resolution feed per rev in INCH
    *
    * this function get information from MD 51011: $MNS_DISP_RES_INCH_FEED_PER_REV
    */
   uint getDisplayResolutionINCHFeedPerRev(void);

   /*! \fn uint getDisplayResolutionRotation(void);
    *  \return Resolution of rotaion
    *
    * this function get information from MD 51019: $MNS_DISP_RES_ROT_WO if it is 0, get
    * information from MD 51020: $MNS_DISP_RES_ANGLE
    */
   uint getDisplayResolutionRotation(void);

   /*! \fn uint getDisplayResolutionAngle(void);
    *  \return Resolution of angle   
    *
    * this function get information from MD 51020: $MNS_DISP_RES_ANGLE
    */
   uint getDisplayResolutionAngle(void);

   /*! \fn uint getDisplayResolutionSpindle(void);
    *  \return Resolution of rotary axis
    *
    * this function get information from MD 51021: $MNS_DISP_RES_SPINDLE
    */
   uint getDisplayResolutionSpindle(void);

   /*! \fn bool checkSwitchFromStepEditorToAreaMaStatus(void);
    *  \return    false allowed
    *             true  locked
    *
    * this function get information from bit 2 MD 51040: $MNS_SWITCH_TO_MACHINE_MASK
    */
   bool checkSwitchFromStepEditorToAreaMaStatus(void);

   /*! \fn bool isAutomaticBlockSearchNotAllowed(void);
    *  \return    false allowed
    *             true  not allowed
    *
    * this function get information from bit 3 MD 51040: $MNS_SWITCH_TO_MACHINE_MASK
    */
   bool isAutomaticBlockSearchNotAllowed(void);

   /*! \fn bool startCheckByExternProgramSelect(void);
    *  \return    false dont start the startcheck (default)
    *             true  start the startcheck
    *
    * this function get information from bit 2 MD 51228: $MNS_FUNCTION_MASK_TECH
    */
   bool startCheckByExternProgramSelect(void);

   /*! \fn bool isProgramSyncEnabled(void) const
    *
    *  \return Returns true if option program sync ($ON_HMI_FUNCTION_MASK[0] Bit3)
    *          is set; otherwise it returns false.
    */
   bool isProgramSyncEnabled(void) const;

   /*! \fn bool isWaitMarksEnabled(void) const
    *
    *  \return Returns true if option program sync ($ON_HMI_FUNCTION_MASK[0] Bit3) enable 
    *          and MD 51300 $MNS_MAXNUM_WAITM_USER > 0 is set; otherwise it returns false.
    */
   bool isWaitMarksEnabled(void) const;

   /*! \fn bool isSimDisabled (void) const
    *
    *  \return Returns true if simulation disabled:
    *          otherwise it returns false.
    */
   bool isSimDisabled (void) const;

   /*! \fn bool isMultiChannelForGCodeEnabled (void) const
    *
    *  \return Returns true if multi channel is enabled for g-code programs:
    *          otherwise it returns false.
    */
   bool isMultiChannelForGCodeEnabled (void) const;

   /*! \fn bool isChannelVisibleInJobList () const
    *
    *  \return Returns true if channel of logic object is visible in job-list;
    *          otherwise it returns false.
    */
   bool isChannelVisibleInJobList () const;

   /*!
    *  \fn bool isHelperChannel () const
    *
    *  Returns true if channel is a helper channel
    *  otherwise it returns false.
    */
   bool isHelperChannel () const;

   /*!
    *  \fn bool isHandlingChannel () const
    *
    *  Returns true if channel is a handling channel
    *  otherwise it returns false.
    */
   bool isHandlingChannel() const;

   /*!
    *  \fn bool isFollowOnToolEnabled () const
    *
    *  \return Returns true if follow on tool is enabled; 
    *          otherwise it returns false.
    */
   bool isFollowOnToolEnabled () const;

   /*!
    *  \fn bool isTurnGrooveChamferCHFActive () const
    *
    *  \return Returns true if turn groove CHF active; 
    *          otherwise it returns false.
    */
   bool isTurnGrooveChamferCHFActive () const;

   /*! \fn bool currentPosForThreadSync(SlStepSpindleNameEnum spindle, double& dSpindleMcs, double& dXMcs, double& dZMcs) const
    *
    *  \param spindle      spindle selector (main or sub spindle)
    *  \param dSpindleMcs  output parameter: spindle position in mcs
    *  \param dZMcs        output parameter: position of the z axis in mcs and active system of units
    *  \param dXMcs        output parameter: position of the x axis in mcs and active system of units
    *
    *  \return             true if thread synchron position has been set in GUDs, else (error case) false.
    *
    *  Provides the current mcs position for thread synchronization at 'spindle' in the active system of units.
    */
   bool currentPosForThreadSync(SlStepSpindleNameEnum spindle, double& dSpindleMcs, double& dXMcs, double& dZMcs) const;

   /*! \fn bool removeThreadSyncPos (SlStepSpindleNameEnum spindle)
    *
    *  \param spindle      spindle selector (main or sub spindle)
    *
    *  \return             true if thread synchron position has been removed, else (error case) false.
    *
    *  Removes the currently set thread synchronization position for 'spindle'.
    */
   bool removeThreadSyncPos(SlStepSpindleNameEnum spindle);

   /*! \fn bool bool setThreadSyncPos (SlStepSpindleNameEnum spindle, double dXAxisPosMcs, double dZAxisPosMcs, double dSpindlePosMcs)
    *
    *  \param spindle      spindle selector (main or sub spindle)
    *  \param dSpindleMcs  spindle position in mcs
    *  \param dZMcs        position of the z axis in mcs and the active system of unit
    *  \param dXMcs        position of the x axis in mcs and the active system of unit
    *
    *  \return             true if thread synchron position has been set in GUDs, else (error case) false.
    *
    *  Sets a thread synchronization position for 'spindle'.
    */
   bool setThreadSyncPos(SlStepSpindleNameEnum spindle, double dXAxisPosMcs, double dZAxisPosMcs, double dSpindlePosMcs);

   /*!
    *  \fn bool getThreadSyncPos(SlStepSpindleNameEnum spindle, double& spindlePos, double& zAxisPos, double& xAxisPos, bool& bStored) const;
    *
    *  \param spindle         spindle selection (main or sub)
    *  \param spindlePos      output parameter: spindle position in mcs
    *  \param zAxisPos        output parameter: metric z axis position in mcs and the active system of units
    *  \param xAxisPos        output parameter: metric x axis position in mcs and the active system of units
    *  \param bStored         output parameter: marker if a thread synchron position has been set, else false.
    *  \retval long           true if GUDs has been read without error,
    *                         else false.
    *
    *  Provides existing thread synchronization position for 'spindle' in the active system of units.
    */
   bool getThreadSyncPos(SlStepSpindleNameEnum spindle, double& spindlePos, double& zAxisPos, double& xAxisPos, bool& bStored) const;

   /*! \fn double getIntIncrPerDeg(void);
    *  \return: value of machine data $MN_INT_INCR_PER_DEG
    *
    *  returns the value of machine data $MN_INT_INCR_PER_DEG: calculation resolution for angular positions
    *
    */
   double getIntIncrPerDeg(void);


   /*! \fn bool isRotAxis (int nMachineAxisIndex, bool bInputWithChannelAxisIndex = false)
    *
    *  \param nMachineAxisIndex  axis index of machine
    *  \param bInputWithChannelAxisIndex  false: input with machine axis index
    *                                     true: input with channel axis index
    *  \return: bool             true is rotary axis, false is otherwise
    *
    */
   bool isRotAxis (int nMachineAxisIndex, bool bInputWithChannelAxisIndex = false) const;

   /*! \fn bool isRotAxis (int nMachineAxisIndex, bool bInputWithChannelAxisIndex = false)
    *
    *  \param nMachineAxisIndex  axis index of machine
    *  \param bInputWithChannelAxisIndex  false: input with machine axis index
    *                                     true: input with channel axis index
    *  \return: bool             true is rotary axis, false is otherwise
    *
    */
   bool isBAxis(int nMachineAxisIndex, bool bInputWithChannelAxisIndex = false) const;

   /*! \fn bool isRotAxisModuloAxis (const QString& rsRotAxisNameIn)
    *
    *  \param rsRotAxisNameIn    name of rotation axis
    *  \return: bool             true is rotary axis modulo axis, false is otherwise
    *
    */
   bool isRotAxisModuloAxis(const QString& rsRotAxisNameIn) const;

   /*! \fn bool isLinearAxisWithLinearDrive (int nChannAxisNumber);
    *
    *  \param nChannAxisNumber   channel axis number
    *  \return: bool             true is rotary axis, false is otherwise
    *
    */
   bool isLinearAxisWithLinearDrive(int nChannAxisNumber) const;

   /*!
   *  \fn bool isControlSettingByLoadAllowed (void) const
   *
   *  \retval true,  control setting is allowed
   *          false, otherwise
   */
   bool isControlSettingByLoadAllowed(void) const;

   /*! \fn SlStepChanAxisNumberVector listAxisControlSettingByLoad();
   *
   *  \return: channel axis number of control setting by load.
   */
   SlStepChanAxisNumberVector listAxisControlSettingByLoad();

   /*! \fn SlStepRotaryAxisMap listOfRotaryAxis(KindOfRotaryAxisEnum kindOfRotaryAxis = ROTARY_AXIS_POSITION_PATTERN);
    *
    *  \param kindOfRotaryAxis   rotary axis to use for position pattern or clamping
    *  \return: value of rotary axis for position pattern
    *
    */
   SlStepRotaryAxisMap listOfRotaryAxis(KindOfRotaryAxisEnum kindOfRotaryAxis = ROTARY_AXIS_POSITION_PATTERN);

   /*!
    *  \fn SlStepNcConfig::TableForClampingEnum getTableForClamping (void) const
    *
    *  \retval the table for clamping
    *          TABLE_NO_EXIST:   table is not exist
    *          TABLE_MILLING:    table for milling
    *          TABLE_BORING:     table for bohring
    */
   SlStepNcConfig::TableForClampingEnum getTableForClamping (void) const;

   /*!
    *  \fn int getSpindleNumber(int nChannelAxisIndex)  const
    *
    *  \param spindle   channel axis index
    *
    *  \retval return the spindle number
    */
   int getSpindleNumber(int nChannelAxisIndex)  const;

   /*!
    *  \fn double getSpindlePower (long lAxisNumber) const;
    *
    *  \param lAxisNumber number of axis
    *
    *  \retval spindle power of axis with axis number \a lAxisNumber
    */
   double getSpindlePower (long lAxisNumber) const;

   /*!
    *  \fn double getMaxAllowedSpindleSpeed (int nAxisIndex) const;
    *
    *  \param nAxisIndex index of axis
    *
    *  \retval maximal allowed spindle speed of axis with axis index \a nAxisIndex
    *
    *  Returns the maximal allowed spindle speed from MD 35100: $MA_SPIND_VELO_LIMIT.
    */
   double getMaxAllowedSpindleSpeed (int nAxisIndex) const;

   /*!
    *  \fn bool isRevolutionalFeedrateResetMode (void) const;
    *
    *  \retval true:  in case of reset value is revolutional feedrate (G95, G952, G97, G971, G973)
    *          false: otherwise
    *
    *   Reset |       | 
    *   Value | GCode | Bedeutung
    *   ------+-------+--------------------------------------------------------------
    *    01   | G93   | Zeitreziproker Vorschub 1/min
    *    02   | G94   | Linear-Vorschub mm/min, inch/min
    *    03   | G95   | Umdrehungsvorschub in mm/U, inch/U
    *    04   | G96   | Konstante Schnittgeschwindigkeit (Vorschubtyp wie bei G95) EIN
    *    05   | G97   | Konstante Schnittgeschwindigkeit (Vorschubtyp wie bei G95) AUS
    *    06   | G931  | Vorschubvorgabe durch Verfahrzeit, konst. Bahngeschwindigkeit ausschalten
    *    07   | G961  | Konstante Schnittgeschwindigkeit (Vorschubtyp wie bei G94) EIN
    *    08   | G971  | Konstante Schnittgeschwindigkeit (Vorschubtyp wie bei G94) AUS
    *    09   | G942  | Linear-Vorschub und konstante Schnittgeschw. oder Spindeldrehzahl einfrieren
    *    10   | G952  | Umdrehungsvorschub u. konst. Schnittgeschw. oder Spindeldrehzahl einfrieren
    *    11   | G962  | Linear-Vorschub oder Umdrehungsvorschub und konst. Schnittgeschwindigkeit
    *    12   | G972  | Linearvorschub oder Umdrehungsvorschub und konstante Spindeldrehzahl (konstante Schnittgeschwindigkeit AUS)
    *    13   | G973  | Umdrehungsvorschub ohne Spindeldrehzahlbegrenzung und konstante Spindeldrehzahl (G97 ohne LIMS für ISO-Modus)
    */
   bool isRevolutionalFeedrateResetMode (void) const;

   /*! \fn double getLengthSecondRevolver(void);
    *  \return: value of machine data MD 52248: $MCS_REV_2_BORDER_TOOL_LENGTH
    *
    *  returns the value of machine data MD 52248: $MCS_REV_2_BORDER_TOOL_LENGTH: basic lenght of second revolver
    *
    */
   double getLengthSecondRevolver(void) const;

   /*  \fn SlMaChanStateEnum channelState () const
    *
    *  returns the state of the channel, used by ncconfig
    */
   SlMaChanStateEnum channelState () const;

   /*! \fn SlMaAccessLevelEnum getAccessLevel(void)
    *
    *  returns the current access level.
    *
    */
   SlMaAccessLevelEnum getAccessLevel(void) const;

   /*! \fn int getAccessExecDirectoryCSTLevel(void) const
    *
    *  returns: Ausführungsrecht das den im Verzeichnis /_N_CST_DIR abgelegten Programmen zugeordnet wird.
    *
    */
   int getAccessExecDirectoryCSTLevel(void) const;

   /*! \fn int getAccessExecMeasureCyclesLevel(void) const
    *
    *  returns: Begrenzung der Schutzstufen beim Schreiben von Systemvariablen beim Abarbeiten von Messzyklen..
    *
    */
   int getAccessExecMeasureCyclesLevel(void) const;

   /*!
    *  \fn void SlMaOpModeEnum opMode(void)
    *
    *  \retval enum opMode
    *
    *  Provides the current channel operation mode.
    */
   SlMaOpModeEnum opMode(void);


   /////////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS TO ACCESS MD
   /////////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn QString readMD (const QString& rsMD, 
                           long& rnError,
                           int nArrayIndex = -1, 
                           int nAxisGudIndex = 1, 
                           int nChannelIndex = 1, 
                           enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN,
                           bool bDirectRead = false) const;
    *
    *  \param rsMD            name of MD to read
    *  \param rbError         reference on error code storage
    *  \param nArrayIndex     index of a value in a MD array
    *  \param nAxisGudIndex   index of axis for axis specific MDs/SDs or index of GUD
    *  \param nChannelIndex   index of channel for channel specific MDs/SDs
    *  \param accType         accType (optional)
    *  \param bDirectRead     flag, if MD is read direct from service or from cache
    *
    *  Returns the value of a MD or SD or GUD \a rsMD as a string. 
    *  If an array index \a nArrayIndex is given, the array entry of the MD is returned. 
    *  For axis specific MDs or SDs use the index of the axis \a nAxisGudIndex.
    *  For GUDs use the number of the GUD-modul \a nAxisGudIndex.
    */
   QString readMD (const QString& rsMD, 
                   long& rnError,
                   int nArrayIndex = -1, 
                   int nAxisGudIndex = 1, 
                   int nChannelIndex = 1, 
                   enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN,
                   bool bDirectRead = false) const;

   /*!
    *  \fn long writeMD (const QString& rsMD, 
                         const QString& rsValue,
                         int nArrayIndex = -1, 
                         int nAxisGudIndex = 1, 
                         int nChannelIndex = 1, 
                         enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN);
   *
   *  \param rsMD            name of MD to write
   *  \param rsValue         value of MD to write
   *  \param nArrayIndex     index of a value in a MD array
   *  \param nAxisGudIndex   index of axis for axis specific MDs/SDs or index of GUD
   *  \param nChannelIndex   index of channel for channel specific MDs/SDs
   *  \param accType         accType (optional)
   *  \retval                error code
   *
   *  Writes the value of a MD or SD or GUD \a rsMD as a string. 
   *  If an array index \a nArrayIndex is given, the array entry of the MD is written. 
   *  For axis specific MDs or SDs use the index of the axis \a nAxisGudIndex.
   *  For GUDs use the number of the GUD-modul \a nAxisGudIndex.
   */
   long writeMD (const QString& rsMD, 
                 const QString& rsValue,
                 int nArrayIndex = -1, 
                 int nAxisGudIndex = 1, 
                 int nChannelIndex = 1, 
                 enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN);

   /*!
    *  \fn QString directReadMD (const QString& rsMD,
                                 long& rnError,
                                 int nArrayIndex = -1, 
                                 int nAxisGudIndex = 1, 
                                 int nChannelIndex = 1, 
                                 enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN) const
    *
    *  Method is provided for convinience. It behaves like \sa readMD() execept
    *  that the MD is read direct from MD service bypassing the MD cache.
    */
   QString directReadMD (const QString& rsMD,
                         long& rnError,
                         int nArrayIndex = -1, 
                         int nAxisGudIndex = 1, 
                         int nChannelIndex = 1, 
                         enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN) const;
   
   /*!
    *  \fn long readMDValue (const QString& rsMD, 
                            const enum QVariant::Type type, 
                            QVariant& rRetVal, 
                            const QVariant defaultValue = QVariant::Invalid, 
                            const int nMask = 0x00, 
                            int nArrayIndex = -1, 
                            int nAxisGudIndex = 1, 
                            enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN,
                            int nChannelIndex = -1) const;
    *
    *  \param rsMD            name of MD to read
    *  \param type            type of the MD
    *  \param rRetVal         return value
    *  \param defaultValue    default value for the return val
    *  \param nMask           mask to bool
    *  \param nArrayIndex     index of a value in a MD array
    *  \param nAxisGudIndex   index of axis for axis specific MDs/SDs or index of GUD
    *  \param accType         accType (optional)
    *  \param nChannelIndex   index of channel for channel specific MDs/SDs
    *                         -1 means currently active channel
    *
    *  This function reads a MD or SD like readMD().
    *  In difference to the function above the return value \a rRetVal is the 
    *  boolean AND with the mask \a nMask.
    *  
    *  See also readMDValue() with rRetVal of type bool.
    */
   long readMDValue (const QString& rsMD, 
                     const enum QVariant::Type type, 
                     QVariant& rRetVal, 
                     const QVariant defaultValue = QVariant::Invalid, 
                     const int nMask = 0x00, 
                     int nArrayIndex = -1, 
                     int nAxisGudIndex = 1, 
                     enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN,
                     int nChannelIndex = -1) const;

   /*!
    *  \fn long writeMDValue (const QString& rsMD, 
                              const enum QVariant::Type type, 
                              const QVariant& rValue, 
                              int nArrayIndex = -1, 
                              int nAxisGudIndex = 1, 
                              int nChannelIndex = 1, 
                              enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN);
   *
   *  \param rsMD            name of MD to read
   *  \param type            type of the MD
   *  \param rValue          value to write
   *  \param nArrayIndex     index of a value in a MD array
   *  \param nAxisGudIndex   index of axis for axis specific MDs/SDs or index of GUD
   *  \param nChannelIndex   index of channel for channel specific MDs/SDs
   *  \param accType         accType (optional)
   *
   *  This function write a MD or SD.
   */
   long writeMDValue (const QString& rsMD, 
                      const enum QVariant::Type type, 
                      const QVariant& rValue,  
                      int nArrayIndex = -1, 
                      int nAxisGudIndex = 1, 
                      int nChannelIndex = 1, 
                      enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN);

   /*!
    *  \fn long writeChanMDValue (const QString& rsMD, const enum QVariant::Type type, const QVariant& rValue, 
                                  int nArrayIndex = -1, int nAxisGudIndex = 1, 
                                  enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN) const
    *  \param rsMD            name of MD to read
    *  \param type            type of the MD
    *  \param rValue          value to write
    *  \param nArrayIndex     index of a value in a MD array
    *  \param nAxisGudIndex   index of axis for axis specific MDs/SDs or index of GUD
    *  \param accType         accType (optional)
    *
    *  Calls \ref readMDValue() for the bound channel.
    */
   long writeChanMDValue (const QString& rsMD, 
                          const enum QVariant::Type type, 
                          const QVariant& rValue, 
                          int nArrayIndex = -1, 
                          int nAxisGudIndex = 1, 
                          enum SlmdAccEnum accType = SLMD_ACC_UNKNOWN);

   /*!
    *  \fn QVariant getMDValue (const QString& rsMD, 
    *                           const enum QVariant::Type type)
    *
    *  \param  rsMD        name of MD to read
    *  \param  type        preferred type of the MD
    * 
    *  Returns the value of a MD or SD or GUD \a rsMD. 
    *  On any error a value of QVariant::Invalid is returned.
    *
    *  Calls \ref readMDValue().
    */
   QVariant getMDValue(const QString& rsMD, const enum QVariant::Type type);

   /*!
    *  \fn bool getSoftwareLimitSwitches(QString& sChanAxisName, 
    *                                    double& rdSoftwareLimitSwitchMinus,
    *                                    double& rdSoftwareLimitSwitchPlus) 
    *
    *  \param sChanAxisName               channel axis name, we ask for
    *  \param rdSoftwareLimitSwitchMinus  return value for software limit switch minus
    *  \param rdSoftwareLimitSwitchPlus   return value for software limit switch plus
    *
    *  Function to get the software limit switches for sChanAxisName.
    *  Returns true, if software limit switches are enabled (axis is a linear axis OR a rotary axis, but not a modulo axis)
    *  returns false, if software limit switches are disabled (axis is a spindle or a rotary modulo axis)
    */
   bool getSoftwareLimitSwitches(QString& sChanAxisName,
                                 double& rdSoftwareLimitSwitchMinus,
                                 double& rdSoftwareLimitSwitchPlus);

   /*!
    *  \fn bool getDivisorAndOffsetOfHirthAxis(QString& sChanAxisName, 
    *                                          double& rdDivisorHirthAxis,
    *                                          double& rdOffsetHirthAxis) 
    *
    *  \param sChanAxisName               channel axis name, we ask for
    *  \param rdDivisorHirthAxis          return value for software limit switch minus
    *  \param rdOffsetHirthAxis           return value for software limit switch plus
    *
    *  Function to get the divisor and offset of the hirth tooth axis sChanAxisName.
    *  Returns true, if divisor and offset of channel axis exist,
    *  returns false, otherwise.
    */
   bool getDivisorAndOffsetOfHirthAxis(QString& sChanAxisName, double& rdDivisorHirthAxis, double& rdOffsetHirthAxis);

   /*!
    *  \fn long positionAxesNameList(AxisInfoList& rAxisInfoList,
    *                                SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE,
    *                                SlMaCoordinateSystemEnum coordSystem = SL_MA_WKS) 
    *
    *  \param rAxisInfoList       List of axis information
    *  \param displayAxes    skip axes depending on machine data
    *  \param coordSystem    coordinate system
    *
    *  Function to get the axis infomation like axisname, typ, channelindex.
    */
   long positionAxesNameList(AxisInfoList& rAxisInfoList, 
                             SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE,
                             SlMaCoordinateSystemEnum coordSystem = SL_MA_WKS);

   /*!
    *  \fn  AxisUsageEnum getAxisUsage(uint nChannelAxisIndex) 
    *
    *  \param   nChannelAxisIndex       channel axis index
    *  \retval  AxisUsageEnum           usage of tje channel axis index
    *
    *  Function to get the usage of channel axis index
    */
   SlStepNcConfig::AxisUsageEnum getAxisUsage (uint nChannelAxisIndex);

   /*! 
    *  \fn unsigned int nckType (void);
    *
    *  \retval unsigned int nckType
    *
    *  Provides the type of the connected NC-Unit.
    */
   unsigned int nckType (void) const;

   /*!
    *  \fn void SlStepNcConfig::getListOfGeoAxAndIpoAxis (QStringList& rAxisList) const 
    *
    *  \param rAxisList       List of geoaxis name (e.g. X,Y,Z) and interpolationsparameter (I, J, K)
    *
    *  Function to get the list of geoaxis name and axis interpolationsparameter (I, J, K).
    *  Achslücken erkennt man an einen oder mehrere Leerstring in der List
    */
   void getListOfGeoAxAndIpoParam (QStringList& rAxisList) const;

   /*!
    *  \fn void TrafoInfoVector getTracylData(void) const 
    *
    *  Function return TrafoInfoVector  with the tracyl data for the class SlStepTracylInfo
    */
   TrafoInfoVector getTracylData(void) const;

   /*!
    *  \fn bool existAxis (const SlStepRotaryAxis axistType,
    *                      QString& sTextId) const;
    *
    *  \param axisType      axis type we ask for
    *  \param sTextId       text identifier
    *
    *  Returns true,
    *      if the axis with text identifier exists and in 'sTextId' the name of the axis 
    *  Returns false,
    *      otherwise.
    */
   bool existAxis (const SlStepRotaryAxis axistType,
                   QString& sTextId) const;

   /*!
    *  \fn int getChannelAxisIndexOfChannelAxis (const QString& rsChanAxName) const
    *  \param rsRotName    name of rotation axis
    *  \retval             Axis index > 0
    *                      if axis type not available -1.
    *
    *  Return the axis index of the given rotation axis.
    */
   int getChannelAxisIndexOfChannelAxis (const QString& rsChanAxName); 

   /*!
    *  \fn int getChannelAxisIndex (AxisUsageEnum axisType) const
    *  \param axisType     axisType
    *  \retval             Axis index > 0
    *                      - or-
    *                      if axis type not available 0.
    *
    *  Return the axis index of the given axis usage.
    */
   int getChannelAxisIndex (AxisUsageEnum axisType) const; 

   /*!
    *  \fn int channelAxisIndexToMachineAxisIndex (int nChannelAxisIndex)
    *  \param nChannelAxisIndex    axis index of channel
    *  \retval                     axis index of machine
    *                               - or-
    *                               if axis type not available 0.
    *
    *  Return the axis index of the machine.
    */
   int channelAxisIndexToMachineAxisIndex (int nChannelAxisIndex) const; 

   /*!
    *  \fn int getChanAxNumberByMachAxName (QString sMachAxisName) const
    *  \param sMachAxisName    machine axis name
    *  \retval                 channel axis number
    *
    *  Return the channel axis number.
    */
   int getChanAxNumberByMachAxName (QString sMachAxisName) const;

   /*!
    *  \fn int machineAxisIndexToChannelAxisIndex (int nMachineAxisIndex)
    *  \param nMachineAxisIndex    axis index of machine
    *  \retval                     axis index of channel
    *                              - or-
    *                              if axis not used in channel 0.
    *
    *  Return the axis index of the machine.
    */
   int machineAxisIndexToChannelAxisIndex (int nMachineAxisIndex) const;

   /*!
    *  \fn int getMachineAxisIndex (AxisUsageEnum axisType) const
    *  \param axisType     axisType
    *  \retval             Axis index > 0
    *                      - or-
    *                      if axis type not available 0.
    *
    *  Return the axis index of the machine.
    */
   int getMachineAxisIndex (AxisUsageEnum axisType) const; 

   /*!
    *  \fn int getAxisIndexByAxisName (const QString& rAxisName);
    *  \param rAxisName    in: axis name
    *  \return               : axis number
    *
    *  Return the axis number by axis name.
    */
   int getAxisIndexByAxisName (const QString& rAxisName);

   /*!
    *  \fn long valueActToolBasePos (double& rdActToolBasePos, int nAxisIndex = 1, SlMaCoordinateSystemEnum coordinateSystem = SL_MA_MKS, int nGeoAxIndex = -1) const
    *
    *  \param rdActToolBasePos   actual tool base position
    *  \param nAxisIndex         axis index
    *  \param coordinateSystem   coordinate system
    *  \param nGeoAxIndex        geoaxis index (0, 1, 2; like in axisIndexGeo())
    *  \retval long              error code
    *
    *  Return the actual tool base position for given axis index.
    *  SL_MA_MKS => ("/Channel/MachineAxis/actToolBasePos")
    *  SL_MA_WKS => ("/Channel/GeometricAxis/actToolBasPosEN")
    *
    *  Note: This function requires the 'nGeoAxIndex' only in the case, you ask for a WCS position of a geometric axis.
    *        'nGeoAxIndex' is required to find out if the given 'nAxisIndex' addresses a geometric axis which run with
    *        traverse axis function (dt. "als Planachse"). In the case it does, the axis position is multiplicated by 2.
    *           If 'nGeoAxIndex' is not given (-1), traverse axis function test is NOT performed, and the axis position
    *        is NEVER multiplicated by 2.
    */
   long valueActToolBasePos (double& rdActToolBasePos, int nAxisIndex = 1, SlMaCoordinateSystemEnum coordinateSystem = SL_MA_MKS, int nGeoAxIndex = -1) const;

   /*!
    *  \fn long valueActToolBasePosBN (double& rdActPos, int nAxisIndex) const;
    *
    *  \param rdActToolBasePos   actual tool base position in BCS
    *  \param nAxisIndex         axis index
    *  \retval long              error code
    *
    *  Return the actual tool base position for given axis index in Basic Coordinate System 
    *  (dt. relativ zum Basis-Nullpunkt; BTSS Variable "/Channel/GeometricAxis/actToolBasPosBN").
    */
   long valueActToolBasePosBN (double& rdActPos, int nAxisIndex) const;

   /*!
    *  \fn QString actFeedType (void) const;
    *
    *  Returns the currently active feed type (GCode value of GCode group 15).
    */
   QString actFeedType (void) const;

   ///////////////////////////////////////////////////////////////////////////
   // METHODS FOR MANUAL MACHINE
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn bool spindleGuiControlEnabled (SlStepSpindleNameEnum spindleType, 
    *                                     McsTechnology technology) const
    *
    *  \param spindleType     type of spindle
    *  \param technology      technology (spindle gui control is setup in technology depending MD)
    *  \return                true if gui control enabled for spindle 'spindleType',
    *                         else false
    *
    *  Return true if gui control for spindle 'spindleType' enabled, else false.
    */
   bool spindleGuiControlEnabled (SlStepSpindleNameEnum spindleType, McsTechnology technology) const;

   /*! \fn JogFeedPerRevSourceEnum jogFeedPerRevSource (void) const
    *
    *  returns the control setting of the revolutional feedrate in JOG (manual machine)
    *
    */
   JogFeedPerRevSourceEnum jogFeedPerRevSource (void) const;

   /*! \fn long btssConeAngle (double& value) const
    *
    *  \param value              [out] value of /Channel/State/acConeAngle
    *  \retval long              error code
    *
    *  Return the btss channel state variable acConeAngle (cone angle active during cone turning in JOG).
    *
    */
   long btssConeAngle (double& value) const;

   /*! \fn long coneAngle (double& value, bool bDirectRead = false) const
    *
    *  \param value              [out] value of $SC_CONE_ANGLE
    *  \param bDirectRead        [in]  'true' for direct read, 'false' for cache access
    *  \retval long              error code
    *
    *  Return the cone angle, active during cone turning in JOG.
    *
    */
   long coneAngle (double& value, bool bDirectRead = false) const;

   /*  \fn long setConeAngle (double newValue);
    *
    *  \param newValue           new value of $SC_CONE_ANGLE
    *  \retval long              error code
    *
    *  Sets the cone angle, active during cone turning in JOG.
    */
   long setConeAngle (double newValue);

   /*! \fn long jogRevIsActive (bool& bIsActive, bool bDirectRead = false) const
    *
    *  \param bIsActive          [out] true if jog revolutional feedrate mode is active,
    *                                  else false
    *  \param bDirectRead        [in]  'true' for direct read, 'false' for cache access
    *  \retval long              error code
    *
    *  JOG revolutional feedrate mode is set, if $SN_JOG_REV_IS_ACTIVE bit-0 is set.
    *  Note: The setting of $SN_JOG_REV_IS_ACTIVE bit-0 may be evaluated only, if JOG feedrate 
    *        control ($SC_JOG_FEED_PER_REV_SOURCE) is NOT set to (-3; which means the user specifies 
    *        two feeds: one for running main and sub spindle, and one for stopped/standing spindle).
    */
   long jogRevIsActive (bool& bIsActive, bool bDirectRead = false) const;

   /*! \fn long setJogRevIsActive (bool bIsActive)
    *
    *  \param bIsActive          true if SN_JOG_REV_IS_ACTIVE bit-0 has to be set,
    *                            else false
    *  \retval long              error code
    *
    *  Sets JOG revolutional feedrate mode on and off.
    *  Note: The setting of $SN_JOG_REV_IS_ACTIVE bit-0 may be evaluated only, if JOG feedrate 
    *        control ($SC_JOG_FEED_PER_REV_SOURCE) is NOT set to (-3; which means the user 
    *        specifies two feeds: one for running main and sub spindle, and one for 
    *        stopped/standing spindle).
    */
   long setJogRevIsActive (bool bIsActive);

   /*!
    *  \fn long jogSettingVelo (double &value, bool bDirectRead = false) const
    *
    *  \param value              [out] value of $SN_JOG_SET_VELO
    *  \param bDirectRead        [in]  'true' for direct read, 'false' for cache access
    *  \retval long              error code
    *
    *  Return the velocity of linear axes in JOG (feed of linear axes at stopped spindle).
    */
   long jogSettingVelo (double &value, bool bDirectRead = false) const;

   /*!
    *  \fn long setJogSettingVelo (double &value) const
    *
    *  \param newValue           new value of $SN_JOG_SET_VELO
    *  \retval long              error code
    *
    *  Sets the velocity of linear axes in JOG(feed of linear axes of the stopped spindle).
    */
   long setJogSettingVelo (double newValue);

   /*!
    *  \fn long jogRevSettingVelo (double &value, bool bDirectRead = false) const
    *
    *  \param value              [out] value of $SN_JOG_REV_SET_VELO
    *  \param bDirectRead        [in]  'true' for direct read, 'false' for cache access
    *  \retval long              error code
    *
    *  Return the velocity of linear axes in JOG (feed of linear axes at running spindle)
    */
   long jogRevSettingVelo (double &value, bool bDirectRead = false) const;

   /*!
    *  \fn long setJogRevSettingVelo (double &value) const
    *
    *  \param newValue           new value of $SN_JOG_REV_SET_VELO
    *  \retval long              error code
    *
    *  Sets the velocity of linear axes in JOG (feed of linear axes at running spindle)
    */
   long setJogRevSettingVelo (double newValue);

   /*!
    *  \fn spindS (double& value, int nMaAxisIndex, bool bDirectRead = false) const
    *
    *  \param value              [out] value of $SA_SPIND_S
    *  \param nMaAxisIndex       [in]  machine index of the spindle axis
    *  \param bDirectRead        [in]  'true' for direct read, 'false' for cache access
    *  \retval long              error code
    *
    *  Returns the revolution speed of spindle in JOG
    */
   long spindS (double& value, int nMaAxisIndex, bool bDirectRead = false) const;

   /*!
    *  \fn setSpindS (double newValue, int nMaAxisIndex)
    *
    *  \param newValue           new value of $SA_SPIND_S
    *  \param nMaAxisIndex       machine index of the spindle axis
    *  \retval long              error code
    *
    *  Sets the revolution speed of spindle in JOG
    */
   long setSpindS (double newValue, int nMaAxisIndex);

   /*!
    *  \fn long spindConstcutS (double& value, int nMaAxisIndex, bool bDirectRead = false) const
    *
    *  \param value              [out] value of $SA_SPIND_CONSTCUT_S
    *  \param nMaAxisIndex       [in]  machine index of the spindle axis
    *  \param bDirectRead        [in]  'true' for direct read, 'false' for cache access
    *  \retval long              error code
    *
    *  Returns the constant cut speed of a spindle
    */
   long spindConstcutS (double& value, int nMaAxisIndex, bool bDirectRead = false) const;
   
   /*!
    *  \fn long setSpindConstcutS (double newValue, int nMaAxisIndex)
    *
    *  \param newValue           new value of $SA_SPIND_CONSTCUT_S
    *  \param nMaAxisIndex       machine index of the spindle axis
    *  \retval long              error code
    *
    *  Sets the constant cut speed von the spindle
    */
   long setSpindConstcutS (double newValue, int nMaAxisIndex);

   /*!
    *  \fn long getSpindSpeedType (int& value, int nMaAxisIndex, bool bDirectRead = false) const
    *
    *  \param value              [out] value of $SA_SPIND_SPEED_TYPE
    *  \param nMaAxisIndex       [in]  machine index of the spindle axis
    *  \param bDirectRead        [in]  'true' for direct read, 'false' for cache access
    *  \retval long              error code
    *
    *  Returns the constant cut speed von the spindle
    */
   long getSpindSpeedType (int& value, int nMaAxisIndex, bool bDirectRead = false) const;

   /*!
    *  \fn long setSpindSpeedType (int newValue, int nMaAxisIndex)
    *
    *  \param newValue           new value of $SA_SPIND_SPEED_TYPE
    *  \param nMaAxisIndex       machine index of the spindle axis
    *  \retval long              error code
    *
    *  Sets the constant cut speed von the spindle
    */
   long setSpindSpeedType (int newValue, int nMaAxisIndex);

   /*! \fn unsigned int actWalimGroupNo() const;
    *
    *  \retval                number of the active work area limits group
    *                         (0..10; 0 = no work area limits group active).
    *
    *  Description see retval.
    */
   unsigned int actWalimGroupNo() const;

   /*! \fn bool ensActiveInActiveWalimGroup() const;
    *
    *  \retval                true, if active work area limit group uses ENS 
    *                         coordinate system, else false
    */
   bool ensActiveInActiveWalimGroup() const;

   /*! \fn bool coordSysWorkAreaLimitsActive() const;
    *
    *  \retval                true, if any coordinate system specific work area limit
    *                         group is active (WALCS1..10), else (WALCS0) false.
    *
    *  Description see retval.
    */
   bool coordSysWorkAreaLimitsActive() const;

   /*!
    *  \fn long workAreaLimitPlusEnabled (bool& bState, int nChAxisIndex) const;
    *
    *  \param bState             [out] value of $SA_WORKAREA_PLUS_ENABLE
    *  \param nChAxisIndex       channel index of the axis
    *  \retval long              error code
    *
    *  Returns true, if work area limitation of axis 'nChAxisIndex' in positive
    *  direction is enabled, else false.
    */
   long workAreaLimitPlusEnabled (bool& value, int nChAxisIndex) const;

   /*!
    *  \fn long setWorkAreaLimitPlusEnabled (bool bNewState, int nChAxisIndex);
    *
    *  \param bNewState          new value of $SA_WORKAREA_PLUS_ENABLE
    *  \param nChAxisIndex       channel index of the axis
    *  \retval long              error code
    *
    *  Activates/deactivates the work area limitation of axis 'nChAxisIndex' in 
    *  positive direction.
    */
   long setWorkAreaLimitPlusEnabled (bool bNewState, int nChAxisIndex);

   /*!
    *  \fn long workAreaLimitMinusEnabled (bool &bState, int nChAxisIndex) const;
    *
    *  \param bState             [out] value of $SA_WORKAREA_MINUS_ENABLE
    *  \param nChAxisIndex       channel index of the axis
    *  \retval long              error code
    *
    *  Returns true, if work area limitation of axis 'nChAxisIndex' in negative
    *  direction is enabled, else false.
    */
   long workAreaLimitMinusEnabled (bool &value, int nChAxisIndex) const;

   /*!
    *  \fn long setWorkAreaLimitMinusEnabled (bool bNewState, int nChAxisIndex);
    *
    *  \param bNewState          new value of $SA_WORKAREA_MINUS_ENABLE
    *  \param nChAxisIndex       channel index of the axis
    *  \retval long              error code
    *
    *  Activates/deactivates the work area limitation of axis 'nChAxisIndex' in 
    *  negative direction.
    */
   long setWorkAreaLimitMinusEnabled (bool bNewState, int nChAxisIndex);

   /*!
    *  \fn long workAreaLimitPlus (double &value, int nChAxisIndex) const;
    *
    *  \param value              [out] value of $SA_WORKAREA_LIMIT_PLUS
    *  \param nChAxisIndex       channel index of the axis
    *  \retval long              error code
    *
    *  Returns the work area limitation in positive direction of axis 'nChAxisIndex',
    *  independent if it's active or not.
    */
   long workAreaLimitPlus (double &value, int nChAxisIndex) const;

   /*!
    *  \fn long setWorkAreaLimitPlus (double newValue, int nChAxisIndex);
    *
    *  \param newValue           new value of $SA_WORKAREA_LIMIT_PLUS
    *  \param nChAxisIndex       channel index of the axis
    *  \retval long              error code
    *
    *  Sets the work area limitation in positive direction of axis 'nChAxisIndex',
    *  independent if it's active or not.
    */
   long setWorkAreaLimitPlus (double newValue, int nChAxisIndex);

   /*!
    *  \fn long workAreaLimitMinus (double &value, int nChAxisIndex) const;
    *
    *  \param value              [out] value of SA_WORKAREA_LIMIT_MINUS
    *  \param nChAxisIndex       channel index of the axis
    *  \retval long              error code
    *
    *  Returns the work area limitation in negative direction of axis 'nChAxisIndex',
    *  independent if it's active or not.
    */
   long workAreaLimitMinus (double &value, int nChAxisIndex) const;

   /*!
    *  \fn long setWorkAreaLimitMinus (double newValue, int nChAxisIndex);
    *
    *  \param bNewState          new value of SA_WORKAREA_LIMIT_MINUS
    *  \param nChAxisIndex       channel  index of the axis
    *  \retval long              error code
    *
    *  Sets the work area limitation in negative direction of axis 'nChAxisIndex',
    *  independent if it's active or not.
    */
   long setWorkAreaLimitMinus (double newValue, int nChAxisIndex);

   /*!
    * \fn bool isKcGraphicEnabled() const
    *
    * \return true if ON_COLLISION_MASK bit 0 and 2 is set, false else
    *
    * This function returns true if no error happened and bit 0 and 2 in MD
    * $ON_COLLISION_MASK is set. Else function returns false;
    */
   bool isKcGraphicEnabled() const;

   /*!
    * \fn SlStepMeasApprAxisDirType getDirAndAxisForToolDelta (int nIndex) const
    *
    *  \param nIndex: Nummer der Messtaster
    *  
    * \return Anfahrrichtung in der Ebene an den Werkzeugmesstaster
    *
    */
   SlStepMeasApprAxisDirType getDirAndAxisForToolDelta(int nIndex) const;

   /*!
    * \fn  QString axisNameText(int nAxis, int nPlane) const
    *
    * \param [in] nAxis          geo axis number
    * \param [in] nPlane         plane for axis
    *
    * \return string with axis label
    *
    * this function returns axis label for given plane in channel of nc config.
    */
   QString axisNameText(int nAxis, int nPlane) const;

   /*!
    * \fn  QString convertMachineAxisToChannelAxis (const QString& axisNameIn)
    *
    * \param axisNameIn    : axis name input
    *
    * \return name of machine axis or channel axis
    *
    * this function returns name of machine axis name or channel axis name depend kindOfConvertAxisMode.
    */
   QString convertMachineAxisToChannelAxis (const QString& axisNameIn);

   /*!
    * \fn  bool toolIdentActive(const QString& sToolName, int nDpNumber) const;
    *
    * \param [in] sToolName      tool name or number
    * \param [in] nDpNumber      duplo number
    * \return                    'true' if given tool is active, else 'false'.
    */
   bool toolIdentActive(const QString& sToolName, int nDpNumber) const;

   /*!
    * \fn  bool kinematicTransformationForTurningOnMillingMachineActive() const;
    *
    * \return                    'true' if a kinematic tranformation for turning on milling machines is active, else 'false'.
    */
   bool kinematicTransformationForTurningOnMillingMachineActive() const;

   /*!
    * \fn  QString activeKinematicTranformationName() const;
    *
    * \return                    name of the active kinematic transformation; empty if not transformation active.
    */
   QString activeKinematicTranformationName() const;

   /*!
    * \fn  unsigned int activeToolCarrierNumber() const;
    *
    * \return                    name of the active tool carrier name; empty if no tool carrier active.
    */
   unsigned int activeToolCarrierNumber() const;

   /*!
    * \fn  QString getMachAxName(const int iMachAxNo) const;
    *
    * \param iMachAxNo           machine axis number (1...31)
    * \return                    name of the machine axis of $MN_AXCONF_MACHAX_NAME_TAB at index iMachAxIndex.
    */
   QString getMachAxName(const int iMachAxNo) const;

   /*!
    * \fn  bool isCompileCycleE996Exist(int nChannel) const;
    *
    * \param nChannel            channel axis
    * \return                    true if it is compile cycle E996 exist, false otherwise.
    */
   bool isCompileCycleE996Exist(int nChannel) const;

   /*!
    * \fn  bool isKinematicMeasReferenceActive() const;
    *
    * \return                    true if it is kinematic measure with refenerce active, false otherwise.
    */
   bool isKinematicMeasReferenceActive() const;

   /*!
    *  \fn int getChannelProgCoordinateSystem  (void);
    *
    *  \return                   number of channel for programm coordinatesystem.
    *
    */
   int getChannelProgCoordinateSystem (void);

   /*!
    * \fn bool isSearchOnlyForSubProgsWithExtension (void) const;
    *
    * \return                    true, if it is only searched for sub programs with extension, false otherwise.
    */
   bool isSearchOnlyForSubProgsWithExtension (void) const;

   /*!
    *  \fn long writeStepEditorInfoCAP(const QString& rsEditorInfo)
    *
    *  \param rsEditorInfo    : editor infomation
    *
    *   get the editor infomation (technlogy, appearance, EditEnabled, EditDisabled,...) 
    *   and write in cap local variable (/Hmi/StepEditorInfo)
    */
   long writeStepEditorInfoCAP(const QString& rsEditorInfo);

   /*!
    * \fn bool isFeatureAllowedHandlingChannelTechZero (void) const;
    *
    * \return                    true, if channel is not a handling/add channel or technology = 0 and bit is set in MD?, false otherwise.
    */
   bool isFeatureAllowedHandlingChannelTechZero(const int nFeature) const;

   /*!
    * \fn int programCheckNiceLevelLinux() const
    * 
    * get nice level for check thread in linux. Default value is 15.
    * It can be changed by editing sleditorwidget.ini file the Internal section
    * example:
    * [Internal]
    * LinuxThreadNice=10
    *
    * \return check thread nice level for linux OS
    */
   int programCheckNiceLevelLinux() const;

   /*!
    *  \fn int programCheckThreadPrioWindows() const
    * 
    * get check thread priority in windows. Default value -999 it means do not change current 
    * priority. It can be changed by editing sleditorwidget.ini file the Internal section
    * example:
    * [Internal]
    * WindowsThreadPriority = 10
    * 
    * \return check thread priority for windows OS
    */
   int programCheckThreadPrioWindows() const;

   /*!
    * \fn bool programCheckThreadBoostEnabledWindows() const
    * 
    * returns true/false flag if windows thread boost has to be enabled or not.
    * default is thread boost on windows is enabled. In that case we have nothing to do.
    * Do we want to disable that feature we have to do it in sleditorwidget.ini file the Internal section.
    * [Internal]
    * WindowsDisableThreadBoost=true
    * 
    * \return true for enabled else false
    */
   bool programCheckThreadBoostEnabledWindows() const;

   /*!
    * \fn bool isPlungeMillingEnabel (void) const;
    *
    * \return  true, if plunge milling allowed, false otherwise.
    */
   bool isPlungeMillingEnabel() const;

protected:

   /*!
    *  \fn bool writeThreadSyncPosToGUDs(SlStepSpindleNameEnum spindle, double spindlePos, double zAxisPos, double xAxisPos, bool bStored)
    *
    *  \param spindle         spindle selection (main or sub)
    *  \param spindlePos      spindle position in mcs
    *  \param zAxisPos        metric z axis position in mcs
    *  \param xAxisPos        metric x axis position in mcs
    *  \param bStored         marker if a "new" thread synchron position has been set, 
    *                         else false.
    *  \retval long           true if GUDs has been written without error,
    *                         else false.
    */
   bool writeThreadSyncPosToGUDs(SlStepSpindleNameEnum spindle, double spindlePos, double zAxisPos, double xAxisPos, bool bStored);

   /*! \fn long buildWorkAreaLimitCapLinkItemIndex (int nChAxisIndex, unsigned int& nCapLinkItemIndex) const;
    *
    *  \param nChAxisIndex       [in]  channel axis index
    *  \param nCapLinkItemIndex  [out] index parameter for SlMaLogic::capLinkItem() calls
    *  \retval                   error code, if filling parameters failed.       
    *
    *  This method fills the 'nCapLinkItemIndex' parameter to be able to create capLinktItems
    *  (btss variable strings) for reading work area limits out of btss variables over SlCap.
    */
   long buildWorkAreaLimitCapLinkItemIndex(int nChAxisIndex, unsigned int& nCapLinkItemIndex) const;

   /*! \fn long updateWaCSLimits(SlCap& rsCap) const;
    *
    *  \param rsCap           [in]  reference on a slcap instance
    *  \retval                error code, if filling parameters failed.       
    *
    *  This method fills the 'nCapLinkItemIndex' parameter to be able to create capLinktItems
    *  (btss variable strings) for reading work area limits out of btss variables over SlCap.
    */
   long updateWaCSLimits(SlCap* rsCap) const;

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   SlStepNcConfigPrivate*  m_pData;    //!< d-pointer pattern

   
   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE CREATORS TO AVOID UNCONTROLED INSTATIATION AND DELETION
   ///////////////////////////////////////////////////////////////////////////
   
   /*! \fn  SlStepNcConfig (SlMaLogic* pMaLogic, SlStepMDPtr mdPtr)
    *
    *  \param pMaLogic     machine logic object 
    *  \param mdPtr        pointer to MD object
    *
    *  private constuctor to avoid instantiation outside the nc config object
    *  manager.
    */
   SlStepNcConfig (SlMaLogic* pMaLogic, SlStepMDPtr mdPtr);

   /*! \fn  ~SlStepNcConfig (void)
    *
    *  private destructor to avoid deletion outside the nc config object
    *  manager.
    */
   ~SlStepNcConfig (void);


   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed */
   SlStepNcConfig (const SlStepNcConfig& rCopy);

   /*! assignment operator not allowed */
   SlStepNcConfig& operator=(const SlStepNcConfig& rCopy);

   //////////////////////////////////////////////////////////////////////////
   // PRIVATE HELPERS
   //////////////////////////////////////////////////////////////////////////

   /*!
    * \fn void checkCacheEnabled(bool bEnable, const class QThread* pThread)
    *
    * \param [in] bEnable     flag to start or stop cache
    * \param [in] pThread     thread of cache
    *
    * This function starts or stops cache.
    */
   void checkCacheEnabled(bool bEnable, const class QThread* pThread);

   /*!
    * \fn void removeSpindleOperationAxes(AxisInfoList& rAxisInfoList)
    *
    * \param [in/out] rAxisInfoList pointer to an axis info list.
    *
    * This function removes an axis which is for spindle operation, if this axis
    * has a C-axis assigned to it. This will be done for main and counter spindle.
    * That means, if for example a main spindle and a C-axis assigned to the main
    * spindle are found, the main spindle will be removed from the axis info list.
    */
   void removeSpindleOperationAxes(AxisInfoList& rAxisInfoList);

   /*!
    * \fn void setActiveWalimToENS(SlCap& cap) const;
    *
    * \param [in/out] rCap  reference to an slcap instance.
    *
    * This function sets the coordinate system of the active work area limit
    * group to ENS - so cone angle has no effect on the limits.
    */
   void setActiveWalimToENS(SlCap& rCap) const;
   
   /*!
    *  \fn QStringList spindleNameListWorker (SpindleLogicEnum usedSpindleLogic = USED_TFS_SPINDLE_LOGIC) const
    *
    * \param  usedSpindleLogic  -> used TFS Spindle logic or all spindle logic
    *
    *  \retval list of spindle names
    */
   QStringList spindleNameListWorker (SpindleLogicEnum usedSpindleLogic = USED_TFS_SPINDLE_LOGIC) const;

}; // <-- class SlStepNcConfig

/*!
 * \class SlStepNcConfigCacheEnabled
 *
 * this is a little switch class to enable or disable nc config cache.
 * constructor turns on the cache
 * destructor turns off the cache
 */
class SlStepNcConfigCacheEnabled
{
   //! nc config which want to use cache
   SlStepNcConfigPtr m_ptrNcConfig;
   //! thread for which we use the cache
   const class QThread* m_pThread;

public:
   /*!
    * \fn SlStepNcConfigCacheEnabled(const SlStepNcConfigPtr& rConfigPtr,const class QThread* pMyThread)
    *
    * \param [in] rConfigPtr     smart pointer for nc config to start cache there
    * \param [in] pMyThread      thread for which the cache should be enabled
    *
    * constructor and enabler of cache
    */
   SlStepNcConfigCacheEnabled(const SlStepNcConfigPtr& rConfigPtr,const class QThread* pMyThread)
      : m_ptrNcConfig(rConfigPtr),
        m_pThread(pMyThread)
   {
      if (false == m_ptrNcConfig.isNull())
      {
         m_ptrNcConfig->checkCacheEnabled(true, m_pThread);
      }
   } // <-- SlStepNcConfigCacheEnabled()

   /*!
    * \fn ~SlStepNcConfigCacheEnabled()
    *
    * destructor and disableer of cache
    */
   ~SlStepNcConfigCacheEnabled()
   {
      if (false == m_ptrNcConfig.isNull())
      {
         m_ptrNcConfig->checkCacheEnabled(false, m_pThread);
      }
   } // <-- ~SlStepNcConfigCacheEnabled()
}; // <-- class SlStepNcConfigCacheEnabled

#endif // SL_STEP_NC_CONFIG_H
