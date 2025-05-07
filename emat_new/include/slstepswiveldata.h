///////////////////////////////////////////////////////////////////////////////
/*! \file   slstepswiveldata.h
 *  \author Robert Kindermann
 *  \date   04.07.2008
 *  \brief  Definition of the class SlStepSwivelData
 *
 *  This file is part of the HMI Solutionline StepEditor.
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_STEP_SWIVEL_DATA_RECORD_H
#define SL_STEP_SWIVEL_DATA_RECORD_H

#include "slstepswiveldatadef.h"
#include "slstepncconfig.h"      // maschine data
#include "slsteplogicexports.h"
#include "slmalogicdefs.h"
#include "slcapdata.h"               // connecting nc

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QMutex>
#include <QtCore/QPair>


////////////////////////////////////////////////////////////////////////////////
//       ++++        POP UP IDENTIFIER        ++++
////////////////////////////////////////////////////////////////////////////////

/*! \enum SlStepPopUpArtEnum
 *
 *  Identifier of swivel pop-ups
 */
enum SlStepPopUpIdEnum
{
   SL_SWIVEL_NO_POPUP               = 0,   //!< no pop-up
   SL_SWIVEL_CLEAR_ZERO_PLANE_POPUP = 1,   //!< clear zero plane pop-up
   SL_SWIVEL_SET_ZERO_PLANE_POPUP   = 2    //!< set zero plane pop-up
};

////////////////////////////////////////////////////////////////////////////////
//       ++++        types of swivel data records        ++++
////////////////////////////////////////////////////////////////////////////////


/*! \def differentiation offset between TC-number and KT-number
 *       So the swivel singleton can differentiate both.
 *
 *  TC    1 - 999
 *  KT 1000 - ...
 */
#define KT_DIFFERENTIATION_OFFSET    1000


/*! \def alternative call number is effective over all channels */
#define ALTERNATIVE_CALL_NUMBER_OVER_ALL_CHANNELS  99


/*! \def all TRACYL slot side offset types */
#define BIT_PATTERN_SLOT_WALL_CORR_FIXED_OFF         0x0000    // 512
#define BIT_PATTERN_SLOT_WALL_CORR_FIXED_ON          0x0200    // 513
#define BIT_PATTERN_SLOT_WALL_CORR_DEFAULT_OFF       0x0400    // 514
#define BIT_PATTERN_SLOT_WALL_CORR_DEFAULT_ON        0x0600    // 514


/*! \def bit pattern for the order of geometry axes */
#define BIT_PATTERN_AXES_ORDER_X_Y_Z   0x00000
#define BIT_PATTERN_AXES_ORDER_Z_X_Y   0x10000
#define BIT_PATTERN_AXES_ORDER_Y_Z_X   0x20000
#define BIT_PATTERN_AXES_ORDER_Z_Y_X   0x30000
#define BIT_PATTERN_AXES_ORDER_X_Z_Y   0x40000
#define BIT_PATTERN_AXES_ORDER_Y_X_Z   0x50000
/*! \def pattern mask for the order of geometry axes */
#define BIT_PATTERN_MASK_AXES_ORDER    0x70000   // Bit 16, 17, 18 are contains in trafoDatCntrl[]


/*! \enum SlStepDirPlaneEnum
 *
 * The plane is determined by the axis order (x,y,z).
 */
enum SlStepDirPlaneEnum
{
   PLANE_NO_INIT,       
   PLANE_G17,       
   PLANE_G18,       
   PLANE_G19        
};


/*! \def transformation types
 *
 *  String defines for the different transformation types
 */
#define SL_SWIVEL_TOOL_CARRIER_CLASSIC    QLatin1String("TOOL_CARRIER_CLASSIC")    //!< swivel data come from tool carrier
#define SL_SWIVEL_TOOL_CARRIER_CHAIN      QLatin1String("TOOL_CARRIER_CHAIN")      //!< tool carrier using kinematic chain data
#define SL_SWIVEL_TRAORI_STAT             QLatin1String("TRAORI_STAT")             //!< kinematic transformation TRAORI_STAT
#define SL_SWIVEL_TRAORI_DYN              QLatin1String("TRAORI_DYN")              //!< kinematic transformation TRAORI_DYN
#define SL_SWIVEL_TRANSMIT_K              QLatin1String("TRANSMIT_K")              //!< kinematic transformation TRANSMIT_K
#define SL_SWIVEL_TRACYL_K                QLatin1String("TRACYL_K")                //!< kinematic transformation TRACYL_K
#define SL_SWIVEL_TRAANG_K                QLatin1String("TRAANG_K")                //!< kinematic transformation TRAANG_K
#define SL_SWIVEL_TRAINT                  QLatin1String("TRAINT")                  //!< kinematic transformation TRAINT interpolation turning


/*! \def transformation types
 *
 *  int defines for the different transformation types
 */
#define SLSTEP_TRACYL                     3   //!< kinematic transformation TRACYL_K
#define SLSTEP_TRAANG                     4   //!< kinematic transformation TRAANG_K


/*! \def transformation types
 *
 *  Differentiation between TC Classic, TC Chain and TC Classic+Chain
 */
#define SL_SWIVEL_ONLY_TC_CLASSIC       true


/*! \enum SlStepSwivelDataTypesEnum
 *
 *  types of swivel data records
 */
enum SlStepSwivelDataTypesEnum
{
   SL_SWIVEL_DATA_FRAME_TYPE = 1,  //!< swivel data records which change the frame
   SL_SWIVEL_DATA_ALIGN_TYPE = 2,  //!< swivel data records used by align tool
   SL_SWIVEL_DATA_ALL_TYPES = 3,  //!< swivel data records which change the frame and used by align tool (only mill and turn)
   SL_SWIVEL_DATA_GRIND_ALIGN_TYPE = 4,  //!< swivel data records for align grinding tool
   SL_SWIVEL_DATA_TRAINT_TYPE = 5,  //!< swivel data records used by interpolationsdrehen
};

/*! \enum SlStepSwivelSourceEnum
 *
 *  Location of the swivel datas
 */
enum SlStepSwivelSourceEnum
{
   SL_SWIVEL_SOURCE_KT           = 0,  //!< For code locations where the exact type is not needed.
   SL_SWIVEL_SOURCE_TC           = 1,  //!< swivel data records which change the frame
   SL_SWIVEL_SOURCE_TC_AND_KT    = 2,  //!< swivel data records used by align tool
};


/*! \enum SlStepBasicToolPositionEnum
 *
 *  basic tool position
 */
enum SlStepBasicToolPositionEnum
{
   SL_STEP_BASIC_TOOL_POS_DEFAULT,        //!< basic tool position not defined --> compatibility mode
   SL_STEP_BASIC_TOOL_POS_Z_MINUS,        //!< basic tool position in axis Z minus
   SL_STEP_BASIC_TOOL_POS_Z_PLUS,         //!< basic tool position in axis Z plus
   SL_STEP_BASIC_TOOL_POS_X_MINUS,        //!< basic tool position in axis X minus
   SL_STEP_BASIC_TOOL_POS_X_PLUS,         //!< basic tool position in axis X plus
};


////////////////////////////////////////////////////////////////////////////////
//       ++++        TOGGLESTATES        ++++
////////////////////////////////////////////////////////////////////////////////

/*! \enum SlStepSwivelDataNameToggleEnum
 *
 *  Defines about swivel data names
 */
enum SlStepSwivelDataNameToggleEnum
{
   SL_STEP_TOGGLE_EMPTY_RECORD      = -3,  //!< empty toggle state
   SL_STEP_TOGGLE_NAME_IS_VARIABLE  = -2,  //!< step value is a variable
   SL_STEP_TOGGLE_INVALID_NAME      = -1,  //!< interpreted record name
   SL_STEP_TOGGLE_DESELECT          = 0    //!< deselect swivel record (Abwahl Schwenkdatensatz)
};


/*! \enum SlStepSwivelToggleRetractEnum
 *
 *  Defines about retraction modi, swiveling
 */
enum SlStepSwivelToggleRetractEnum
{
   SL_STEP_TOGGLE_NO_RETRACTION         = 0,  //!< no retraction
   SL_STEP_TOGGLE_RETRACTION_IN_Z       = 1,  //!< retraction in Z-axis
   SL_STEP_TOGGLE_RETRACT_XYZ           = 2,  //!< retraction in all axis
   SL_STEP_TOGGLE_RETRACT_TOOL_DIR_MAX  = 3,  //!< Maximum retraction in tool direction, software limit switch
   SL_STEP_TOGGLE_RETRACT_TOOL_DIR_INC  = 4   //!< Retract tool up to the incremental value entered in the tool direction
};

/*! \typedef SwivelModeQList
*
*  Defines a list of valid swivel modes
*/
typedef QList<enum SlStepSwivelModeToggleEnum>  SwivelModeQList;    //!< list of valid swivel modes

/*! \enum SlStepSwivelRotDirToggleEnum
 *
 *  Defines about the direction of the rotation
 */
enum SlStepSwivelRotDirToggleEnum
{
   SL_STEP_TOGGLE_NEGATIVE_OFFSET = 0,  //!< swiveling, rotation in negative direction
   SL_STEP_TOGGLE_POSITIVE_OFFSET = 1   //!< swiveling, rotation in positive direction
};


/*! \enum SlStepSwivelRotOperationModeEnum
 *
 *  Defines about the operation of the rotation axis
 */
enum SlStepSwivelRotOperationModeEnum
{
   SL_STEP_TOGGLE_ROTARY_SWIVEL_AXIS_NO_EXIST       = 0,  //!< rotary axis no exist
   SL_STEP_TOGGLE_ROTARY_SWIVEL_AXIS_AUTOMATIC      = 1,  //!< rotary axis in automatic mode
   SL_STEP_TOGGLE_ROTARY_SWIVEL_AXIS_MANUAL         = 2,  //!< rotary axis in manual mode
   SL_STEP_TOGGLE_ROTARY_SWIVEL_AXIS_SEMI_AUTOMATIC = 3,  //!< rotary axis in semi automatic mode
};

/*!
 *  \typedef SlStepSwivelRotOperationModePair
 *
 *  Defines an item information for rotary axis 1 and rotary axis 2.
 */
typedef QPair<SlStepSwivelRotOperationModeEnum, SlStepSwivelRotOperationModeEnum> SlStepSwivelRotOperationModePair;


/*! \enum SlStepTrackingToggleEnum
 *
 *  Defines possible toggle states no/yes
 */
enum SlStepTrackingToggleEnum
{
   SL_STEP_TOGGLE_NO  = 0,   //!< no
   SL_STEP_TOGGLE_YES = 1,   //!< yes
};

////////////////////////////////////////////////////////////////////////////////
//       ++++       error identifier     ++++
////////////////////////////////////////////////////////////////////////////////

/*! \enum SlSwivelDataErrorEnum
 *
 *   enum for access of the btss variable.
 */
enum SlSwivelDataErrorEnum 
{
   // ALLGEMEINE FEHLER
   SWIVEL_NO_ERROR    = 0,             //!< no error occured
   SWIVEL_NOT_ENABLE,                  //!< $MCS_FUNCTION_MASK_TECH bit is not set
   SWIVEL_TC_NOT_ENABLE,               //!< $MCS_FUNCTION_MASK_TECH bit 0 is not set
   SWIVEL_KT_NOT_ENABLE,               //!< $MCS_FUNCTION_MASK_TECH bit 10 is not set
   SWIVEL_NO_DATA_RECORDS,             //!< MN_MM_NUM_TOOL_CARRIER = 0
   SWIVEL_KT_NO_DATA_RECORDS,          //!< no data records for kinematic transformation
   SWIVEL_TC_NO_DATA_RECORDS,          //!< no data records for ToolCarrier
   SWIVEL_CHANNEL_HAS_NO_TO_UNIT,      //!< channel got no to-unit
   SWIVEL_NO_DATA_RECORDS_ENABLE,      //!< no swivel data records are enable
   SWIVEL_NO_FRAME_DATA_RECORDS_FOUND, //!< no swivel data records found for swivel frame
   SWIVEL_NO_ALIGN_DATA_RECORDS_FOUND, //!< no swivel data records found for swivel align
   SWIVEL_NO_TRAINT_DATA_RECORDS_FOUND, //!< no swivel data records found for interpolation turning

   // EINZELBETRACHTUNG DER DATENSÄTZE
   SWIVEL_RECORD_NOT_EXIST,            //!< swivel data record does not existed
   SWIVEL_RECORD_NOT_ENABEL,           //!< swivel data record is not enable
   SWIVEL_DESELECT_NOT_ALLOWED,        //!< deselect swivel data record is mnot allowed
   SWIVEL_RECORD_INVALID_IS_ALIGN,     //!< wrong swivel data, swivel data is in the align swivel data
   SWIVEL_RECORD_INVALID_IS_FRAME,      //!< wrong swivel data, swivel data is in the frame swivel data
   SWIVEL_RECORD_INVALID_IS_GRIND_ALIGN, //!< wrong swivel data, swivel data is in the grind align swivel data
   SWIVEL_RECORD_INVALID_IS_TRAORI_DYN, //!< wrong swivel data, swivel data is in the TRAORI_DYN
   SWIVEL_RECORD_INVALID_IS_TRAINT     //!< wrong swivel data, swivel data is in the TRAINT
};


/*! \enum SlSwivelErrorEnum
 *
 *   enum for error handling by edit functions
 */
enum SlSwivelErrorEnum 
{
   SWIVEL_ERR_NO_ERROR    = 0,         //!< no error occured
   SWIVEL_ERR_CHANNEL_IS_ACTIVE,       //!< channel is activw
   SWIVEL_ERR_NAME_EXIST,              //!< double swivel name
   SWIVEL_ERR_WRONG_SWIVEL_AREA,       //!< wrong swivel area, e.g. KT instead TC
   SWIVEL_ERR_SDR_IS_OCCUPIED,         //!< swivel data record is occupied
   SWIVEL_ERR_SDR_IS_EMPTY,            //!< swivel data record is empty
   SWIVEL_ERR_SDR_WRITE_ERROR,         //!< could not write swivel data record
   SWIVEL_ERR_SDR_READ_ERROR,          //!< could not read swivel data record
   SWIVEL_ERR_SYSTEM_ERROR             //!< system error
};

////////////////////////////////////////////////////////////////////////////////
//       ++++       elements of machine data    ++++
////////////////////////////////////////////////////////////////////////////////

/*! \enum SlSwivelDisplayOptionsEnum
 *
 *   SD 55221 FUNCTION_MASK_SWIVEL_SET
 *
 */
enum SlSwivelDisplayOptionsEnum 
{
   SWIVEL_ENABLE_SWIVEL_TOGGLE_YES_NO  = 0x0001,   //!< Bit0: swivel head
   SWIVEL_TEXT_WITHOUT_AXIS_IDENTIFIER = 0x0002,   //!< Bit1: toolTip retraction: with axis identifier or use text "fixpoint"
   SWIVEL_ENABLE_UNLOAD_SWIVEL_HEAD    = 0x0004,   //!< Bit2: enable to unload the inclinable head
   SWIVEL_VISIBLE_ACTIVE_SWIVEL_PLANE  = 0x0008,   //!< Bit3: displaying the active swivel plane
   SWIVEL_NOT_ENABLE_SWIVEL_DIRECT_JOG = 0x0040,   //!< Bit6: enable swivel direct under JOG
   SWIVEL_ENABLE_SWIVEL_POS_DIRECTION  = 0x0400,   //!< Bit10: enable swivel positioning direction
};

////////////////////////////////////////////////////////////////////////////////
//       ++++       elements of the mechanics    ++++
////////////////////////////////////////////////////////////////////////////////


/*! \enum SlSwivelLocationEnum
 *
 *   enum for, where is the swivel mechanic
 */
enum SlSwivelLocationEnum 
{
   SWIVEL_NO_LOCATON = 0,       //!< no location of swivel
   SWIVEL_HEAD,                 //!< swivel head
   SWIVEL_TABLE,                //!< swivel table
   SWIVEL_TABLE_HEAD            //!< mixed mechaninc
};


/*! \enum SlSwivelMechanicsEnum
 *
 *   enum for swivel mechanics
  *   The enum describes the mechanics of the machine and its coordinate system.
 */

// Das ENUM wird zur Zeit nur bei der Darstellung der Animationen für die Ermittlung spezieller 3D Bilder
// verwendet. Dies sind 3D Bilder die nicht gedreht werden und Koordinatenbezeichner besitzen. Sie
// werden nicht gedreht, da sonst die Darstellung der Bearbeitung nicht glücklich ist.
// Da diese 3D-Bilder feste Koordinatenbezeichner besitzen, muß für jedes andere Koordinatensystem eine neue 
// Datei erstellt werden. Zur Zeit werden nur die Koordsysteme 0, 16 und 34 dargestellt.

enum SlSwivelMechanicsEnum 
{
   SWIVEL_NO_MECHANIC = 0,
   SWIVEL_BORING_UNIVERSAL,               //!< Showing machine-independent swivel mechanics for boring machine in coordinate system 16
   SWIVEL_MILLING_UNIVERSAL,              //!< Showing machine-independent swivel mechanics for milling machine in coordinate system 0
   SWIVEL_TURNING_UNIVERSAL,              //!< Showing machine-independent swivel mechanics for turning machine in coordinate system 34
   SWIVEL_BORING_TABLE_B90_A90,           //!< 90 degree mechanic, swivel axis = B, table axis = A
   SWIVEL_BORING_TABLE_C90_A90,           //!< 90 degree mechanic, swivel axis = C, table axis = A
   SWIVEL_BORING_TABLE_B90_HEAD_C45,      //!< 45 degree mechanic, head axis = C, table axis = B
   SWIVEL_BORING_TABLE_B90_HEAD_A90,      //!< 90 degree mechanic, head axis = A, table axis = B  coordinate system 16
   SWIVEL_BORING_HEAD_C90_A90,            //!< 90 degree mechanic, swivel axis = C, tool axis = A
   SWIVEL_MILL_HEAD_A90_B90,              //!< 90 degree mechanic, swivel axis = A, tool axis = B
   SWIVEL_MILL_HEAD_C90_B90,              //!< 90 degree mechanic, fixing axis = C, swivel axis = B
   SWIVEL_MILL_HEAD_B90_C45,              //!< 45 degree mechanic, fixing axis = B, swivel axis = C
   SWIVEL_MILL_HEAD_C90_TOOL_C,           //!< 90 degree tool extension, swivel axis = C, tool on C
   SWIVEL_MILL_HEAD_C90_TOOL_A,           //!< 90 degree angle head, swivel axis = C, tool on A
   SWIVEL_MILL_HEAD_C90_B90_FIX90,        //!< Hammer-Head, fixing axis = C, swivel axis = B, tool on A
   SWIVEL_MILL_HEAD_C90_B90_FIX45,        //!< Elbow-Head, fixing axis = C, swivel axis = B, tool on A
   SWIVEL_MILL_TABLE_C90_A90,             //!< 90 degree mechanic, swivel axis = A, table axis = C
   SWIVEL_MILL_TABLE_C90_B90,             //!< 90 degree mechanic, swivel axis = B, table axis = C
   SWIVEL_MILL_TABLE_C90_B45,             //!< 45 degree mechanic, swivel axis = B, table axis = C
   SWIVEL_MILL_TABLE_C90_HEAD_A90,        //!< 90 degree mechanic, head axis = A, table axis = C
   SWIVEL_MILL_TABLE_A90_HEAD_B90,        //!< 90 degree mechanic, head axis = B, table axis = A  coordinate system 0
   SWIVEL_TURN_TABLE_A90_HEAD_B90,        //!< 90 degree mechanic, head axis = B, table axis = A  coordinate system 34
   SWIVEL_MILL_CAROU_TABLE_C90_HEAD_B90,  //!< 90 degree mechanic, head axis = B, table axis = C
   SWIVEL_MILL_TABLE_C90_HEAD_B45,        //!< 45 degree mechanic, head axis = B, table axis = C
};


/*! \enum SlSwivelMachineType
 *
 *   enum for machine types
 */
enum SlSwivelMachineType 
{
   SWIVEL_NO_MACHINE_TYP = 0,    //!< Machine type could not be determined.
   SWIVEL_MILLING_MACHINE,       //!< milling machine
   SWIVEL_BORING_MACHINE,        //!< boring machine
   SWIVEL_TURNING_MACHINE,       //!< turning machine
   SWIVEL_CAROUSEL_MACHINE,      //!< vertical turning machine, vertical lathe (carousel-type lathe)
};

// ---------------------------------------------------------------------------
// *******  Begin für Definitionen für IBN - Maske Schwenkdaten    ********
// ---------------------------------------------------------------------------

/*! \enum SlSwivelEditFunctionEnum
 *
 *   enum for edit functions
 */
enum SlSwivelEditFunctionEnum 
{
   SWIVEL_EDIT_DELETE = 1,       //!< clean the swivel data record
   SWIVEL_EDIT_COPY,             //!< copy the swivel data record
   SWIVEL_EDIT_PASTE,            //!< paste the swivel data record
   SWIVEL_EDIT_NEW,              //!< create new swivel data record
   SWIVEL_EDIT_OK                //!< accept swivel data record
};

/*! \typedef SlSwivelEditFunctionList  
 *
 *   The QList contains the information which edit function can be used 
 */
typedef QList<SlSwivelEditFunctionEnum> SlSwivelEditFunctionList;   

// ---------------------------------------------------------------------------
// *******  Ende für Definitionen für IBN - Maske Schwenkdaten    ********
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
// typedef für den Inbetriebnahmedialog Schwenkdatensätze
// ---------------------------------------------------------------------------

//!< vector with swivel names, swivel number, swivel type, etc. of all swivel data records
typedef QVector<SlStepSwivelsInfo>  SlStepAllSwivelsInfo;    



// ---------------------------------------------------------------------------
// Cache für StepEditor-Objekt Schwenkdatensätze
// ---------------------------------------------------------------------------

/*! \enum SlStepVectorDirection
 *
 *  Identifier of vector directio
 */
enum SlStepVectorDirectionEnum
{
   NEG = 0x01,   //!< negative direction
   O   = 0x02,   //!< no direction
   POS = 0x04    //!< positive direction
};


/*! \struct SlStepSwivelMechanicsStructType
 *
 *   variables for determine the mechanics
 */
struct SlStepSwivelMechanicsStructType
{
   SlSwivelMechanicsEnum mechanics;      //!< associated mechanics
   SlSwivelMachineType   machineType;    //!< machine Type like milling machine or boring machine
   SlSwivelLocationEnum  rot1Location;   //!< location of first rotary axis 
   SlSwivelLocationEnum  rot2Location;   //!< location of second rotary axis 
   int vectorRot1X;                      //!< first rotary axis vector around x.
   int vectorRot1Y;                      //!< first rotary axis vector around y.
   int vectorRot1Z;                      //!< first rotary axis vector around z.
   int vectorRot2X;                      //!< second rotary axis vector around x.
   int vectorRot2Y;                      //!< second rotary axis vector around y. 
   int vectorRot2Z;                      //!< second rotary axis vector around z.
   int vectorToolX;                      //!< first tool axis vector around x.
   int vectorToolY;                      //!< first tool axis vector around y. 
   int vectorToolZ;                      //!< first tool axis vector around z.

   void init (void)
   {
      mechanics = SWIVEL_NO_MECHANIC;
      machineType = SWIVEL_NO_MACHINE_TYP;
      rot1Location = SWIVEL_NO_LOCATON;
      rot2Location = SWIVEL_NO_LOCATON;
      vectorRot1X  = O;
      vectorRot1Y  = O;  
      vectorRot1Z  = O;  
      vectorRot2X  = O;  
      vectorRot2Y  = O;  
      vectorRot2Z  = O;
      vectorToolX  = O;   //!< first tool axis vector around x.
      vectorToolY  = O;   //!< first tool axis vector around y. 
      vectorToolZ  = O;   //!< first tool axis vector around z.
   }

   /*! \fn bool hasVectorRightDirection (int btssVector, int tabVector) const;
    *  \param btssVector   in: direction vector from btss variable
    *  \param tabVector    in: direction vector from table
    *  \return            out: both vectors match
    *
    *  compare the vectors from table and btss variable 
    */
   bool hasVectorRightDirection (int btssVector, int tabVector) const;

   /*! \fn bool compareSwivelMechanicsWithTable (SlStepSwivelMechanicsStructType const& SwivelMechanicsTable) const;
    *  \param SwivelMechanicsTable    in: reference swivel datas from the table
    *  \return bool                  out: swivel mechanics found
    *
    *  Returns true if swivel mechanics found
    */
   bool compareSwivelMechanicsWithTable (SlStepSwivelMechanicsStructType const& rSwivelMechanicsTable) const;
   
};  // <-- struct SlStepSwivelMechanicsStructType


/*! \struct SlStepAxisRotStruct
 *
 *   struct of the axis rotation
 */
struct SlStepAxisRotStruct
{
   SlStepAxisRotStruct()
        :isXrotation(false),
         isYrotation(false),
         isZrotation(false)
   {}

   bool  isXrotation;
   bool  isYrotation;
   bool  isZrotation;
};

////////////////////////////////////////////////////////////////////////////////
// speicherelemente für das schwenken
////////////////////////////////////////////////////////////////////////////////

/*! \struct SlStepSwivelDataRecord
 *
 *   struct of the swivel data record
 */
struct SL_STEP_LOGIC_EXPORT SlStepSwivelDataRecord
{
   SlStepSwivelDataRecord()
        :m_rot1Location(SWIVEL_NO_LOCATON),
         m_rot2Location(SWIVEL_NO_LOCATON),
         m_vector1x(0.0),
         m_vector1y(0.0),
         m_vector1z(0.0),
         m_vector2x(0.0),
         m_vector2y(0.0),
         m_vector2z(0.0),
         m_swivelNumber(0),
         m_swivelProperty(0),
         m_mechanics(SWIVEL_NO_MECHANIC),
         m_alpha1Min(0.0),
         m_alpha1Max(0.0),
         m_alpha2Min(0.0),
         m_alpha2Max(0.0),
         m_basicToolPosition(SL_STEP_BASIC_TOOL_POS_DEFAULT),
         m_basicToolPositionB(SL_STEP_BASIC_TOOL_POS_DEFAULT),
         m_betaMin(0.0),
         m_betaMax(0.0),
         m_offsetLength3x(0.0),       //!< x-component of the 2. length offset
         m_offsetLength3z(0.0),       //!< z-component of the 2. length offset
         m_offsetVector1(0.0),
         m_offsetVector2(0.0),
         m_tcWithKinChain(false),      //!< TC with or without chain
         m_rotaryAxisBLimited(false),
         m_rotaryAxisBMin(0.0),
         m_rotaryAxisBMax(0.0),
         m_divisorHirthAxisB(1.0),
         m_offsetHirthAxisB(0.0),
         m_divisorHirthAxisC(1.0),
         m_offsetHirthAxisC(0.0),
         m_rotAxProperty(0)
   {}

   // daten die von beiden verwendet werden
   QString     m_tcName;              //!< name of swivel data record
   QString     m_1RotaryAxName;       //!< name of first rotation axis
   QString     m_2RotaryAxName;       //!< name of second rotation axis
   QString     m_3RotaryAxName;       //!< name of third rotation axis
   QString     m_swivelLocation;      //!< location of the swivel mechanics
   SlSwivelLocationEnum  m_rot1Location; //!< location of the rotary axis1
   SlSwivelLocationEnum  m_rot2Location; //!< location of the rotary axis2
   double      m_vector1x;            //!< x-component of the rotary axis 1
   double      m_vector1y;            //!< y-component of the rotary axis 1
   double      m_vector1z;            //!< z-component of the rotary axis 1
   double      m_vector2x;            //!< x-component of the rotary axis 2
   double      m_vector2y;            //!< y-component of the rotary axis 2
   double      m_vector2z;            //!< z-component of the rotary axis 2
   uint        m_swivelNumber;        //!< the number of the swivel data record or kinematic transformaton
   uint        m_swivelProperty;      //!< swivel properties
   SlSwivelMechanicsEnum m_mechanics; //!< kind of special machine mechanics, e.g. 90 degree mix-mechanic: head B axis and table A axis
   // kt oder tc mit Kette
   QString     m_kinElem1RotAxis;     //!< name of kinematic element for the first rotation axis
   QString     m_kinElem2RotAxis;     //!< name of kinematic element for the second rotation axis
   QString     m_kinElem3RotAxis;     //!< name of kinematic element for the third rotation axis
   QString     m_lastToolElemName;    //!< name of the last tool kinematic chain element (KT or TC with chain)
   QString     m_lastPartElemName;    //!< name of the last part kinematic chain element (KT or TC with chain)

   // Daten die Momentan nur das ToolCarrier verwendet
   double      m_alpha1Min;           //!< minimal value for angle alpha 1
   double      m_alpha1Max;           //!< maximal value for angle alpha 1
   double      m_alpha2Min;           //!< minimal value for angle alpha 2
   double      m_alpha2Max;           //!< maximal value for angle alpha 2
   SlStepBasicToolPositionEnum  m_basicToolPosition;    //!< basic tool position, for the alignment tool (only ShopTurn)
   SlStepBasicToolPositionEnum  m_basicToolPositionB;   //!< basic tool position, for measuring kinematics complete (Turning Machine)
   double      m_betaMin;             //!< minimal beta value
   double      m_betaMax;             //!< maximal beta value   
   double      m_offsetLength3x;      //!< x-component of the 2. length offset
   double      m_offsetLength3z;      //!< z-component of the 2. length offset
   double      m_offsetVector1;       //!< angle offset rotary axis 1
   double      m_offsetVector2;       //!< angle offset rotary axis 2
   bool        m_tcWithKinChain;      //!< TC with or without chain
   QString     m_startToolElemName;    //!< name of the beginning tool element in the kinematic chain  
   QString     m_startPartElemName;    //!< name of the beginning part element in the kinematic chain  

   // Daten nur für die kinematische Transformation
   QString     m_1RotaryMachineAxName; //!< machine name of first rotation axis
   QString     m_2RotaryMachineAxName; //!< machine name of second rotation axis
   QString     m_3RotaryMachineAxName; //!< machine name of third rotation axis

   bool        m_rotaryAxisBLimited;  //!< true, if m_rotaryAxisBMin/m_rotaryAxisBMax are valid
   double      m_rotaryAxisBMin;      //!< minimal rotary axis B value
   double      m_rotaryAxisBMax;      //!< maximal rotary axis B value
   double      m_divisorHirthAxisB;   //!< divisor of hirth axis B
   double      m_offsetHirthAxisB;    //!< offset of hirth axis B
   double      m_divisorHirthAxisC;   //!< divisor of hirth axis C
   double      m_offsetHirthAxisC;    //!< offset of hirth axis C
   uint        m_rotAxProperty;       //!< rotary axes properties

}; 


/*! \class SlStepSwivelDataSet
 *
 *  memory for swivel datas
 *  This datas are from all tool carriers valid or invalid
 */
class SlStepSwivelDataSet
{
public:

   /*! \fn SlStepSwivelDataSet();
    *
    *  Default constructor
    */
   SlStepSwivelDataSet();
   
   /*! \fn SlStepSwivelDataSet (const QString& rSwivelName, const QString& rTrafoType, int iProperty);
    *  \param rSwivelName in: swivel name
    *  \param rTrafoType  in: trafo type
    *  \param iProperty   in: property of the tool carrier
    *
    *  Constructor
    */
   SlStepSwivelDataSet (const QString& rSwivelName, const QString& rTrafoType, int iProperty);

   /*! \fn ~SlStepSwivelDataSet()
    *
    *  Destructor
    */
   virtual ~SlStepSwivelDataSet();

   QString   m_swivelName;    // name of the tool carrier
   QString   m_trafoType;     // trafo type
   int       m_property;      // property of the tool carrier

};


/*! \class SlStepTraCylAlternativeCallData
 *
 *   class of data for alternative TRACYL call, for internal use
 */
class SlStepTraCylAlternativeCallData
{
 public:

   SlStepTraCylAlternativeCallData()
        :m_altCallNumber(0),
         m_altCallChannelNumber(0),
         m_chnAxisNumber(0),
         m_altCallTraCylTrafoType(SlStepTracylInfo::TRAFO_TYPE_NO_INIT),
         m_geoAxisNumberToRotary(SlStepTracylInfo::ROTARY_AT_NO_INIT),
         m_altCallPlane(PLANE_G19)
   {}

   int     m_altCallNumber;          //!< alternative call number
   int     m_altCallChannelNumber;   //!< channel number
   int     m_chnAxisNumber;           //!< channel axis number from the swivel Axis
   
   SlStepTracylInfo::SlStepTracylTypeNumberEnum    m_altCallTraCylTrafoType;  //!< trafo type 512, 513, 514
   SlStepTracylInfo::SlStepGeoAxisIndexEnum        m_geoAxisNumberToRotary;   //!< The axis rotates around which axis 
   SlStepDirPlaneEnum                              m_altCallPlane;            //!< plane

}; 

/*! \class SlStepTraangAlternativeCallData
 *
 *   class of data for alternative TRAANG call, for internal use
 */
class SlStepTraangAlternativeCallData
{
 public:

   SlStepTraangAlternativeCallData()
        :m_altCallNumber(0),
         m_altCallChannelNumber(0)
   {}

   int     m_altCallNumber;          //!< alternative call number
   int     m_altCallChannelNumber;   //!< channel number
}; 


class SlMaLogic;
class SlStepSwivelDataCallBack;

/*! \typedef QList<SlStepSwivelDataSet> SwivelDataSetQList
 *  List over all swivel data records names, additional data are transformation types and the property
 *  about the swivel data records.
 */
typedef QList<SlStepSwivelDataSet> SwivelDataSetQList;

/*! \typedef QList<SlStepTraCylAlternativeCallData> SlStepTraCylAlternativeCallDataList
 *  List for all valid alternative TRACYL call data, over all Channels
 */
typedef QList<SlStepTraCylAlternativeCallData> SlStepTraCylAlternativeCallDataList;

/*! \typedef QList<SlStepTraangAlternativeCallData> SlStepTraangAlternativeCallDataList
 *  List for all valid alternative TRAANG call data, over all Channels
 */
typedef QList<SlStepTraangAlternativeCallData> SlStepTraangAlternativeCallDataList;


////////////////////////////////////////////////////////////////////////////////
// main class for swivel
////////////////////////////////////////////////////////////////////////////////

/*! \class SlStepSwivelData
 *
 *  This class provides a map with swivel data records.
 *  Only one object of the class is generated. (singleton)
 */
class SL_STEP_LOGIC_EXPORT SlStepSwivelData
{
   // singleton for swivel datas
   friend class SlStepSwivelDataSingleton;
   // class is used for signal/slot handle
   friend class SlStepSwivelDataCallBack;

public:

   /*!
    *  \enum RotaryAxisNameIndex
    *
    *  This defines indices for access into the rotary axes name list, given by getRotaryAxisNames.
    */
   enum RotaryAxisNameIndex
   {
      ROT_AXIS_WORKPIECE = 0,     //!< index of the workpiece´s rotary axis 
      ROT_AXIS_TOOL_B = 1,        //!< index of the tool´s rotary axis B
      ROT_AXIS_TOOL_C = 2,        //!< index of the tool´s rotary axis C 
   };
   typedef QList<enum RotaryAxisNameIndex>  RotaryAxisNameIndexQList;    //!< list of valid rotary axis name index



  // ---------------------------------------------------------------------------
  //     PUBLIC METHODES OF SWIVEL-DATA-RECORDS   
  // ---------------------------------------------------------------------------
   
  /*! \fn static bool isSwivelEnable (int channelNumber, SlStepSwivelSourceEnum swivelDataSource);
   *  \param channelNumber       in: channel number
   *  \param swivelDataSource    in: use TC or KT or both
   *  \return                        TC or KT is switch to enable
   *
   *  Is swivel enable
   */
  static bool isSwivelEnable(int channelNumber, SlStepSwivelSourceEnum swivelDataSource);

  /*! \fn QList<uint> getValidSwivelFrameNumberList (int channelNumber, bool bOnlyTcClassic = false);
   *  \param channelNumber                in: channel number
   *  \param bOnlyTcClassic               in: true = only TC Classic
   *  \return                               : list of swivel data record numbers
   *
   *  retuns a list of all swivel data record numbers which are activated
   */
  QList<uint> getValidSwivelFrameNumberList (int channelNumber, bool bOnlyTcClassic = false);

  /*! \fn QList<uint> getValidSwivelAlignNumberList (int channelNumber, SlStepSwivelSourceEnum swivelDataSource,
                                                     bool bOnlyTcClassic = false);
   *  \param channelNumber              in: channel number
   *  \param swivelDataSource           in: use TC or KT or both
   *  \param bOnlyTcClassic             in: true = only TC Classic
   *  \return                             : list of swivel data records or transformation records
   *
   *  retuns a list of all valid swivel data record numbers for align tool
   */
  QList<uint> getValidSwivelAlignNumberList (int channelNumber, SlStepSwivelSourceEnum swivelDataSource,
                                             bool bOnlyTcClassic = false);

  /*! \fn QList<uint> getValidSwivelGrindAlignNumberList (int channelNumber);
   *  \param channelNumber              in: channel number
   *  \return                             : list of swivel data records or transformation records
   *
   *  retuns a list of all valid swivel data record numbers for align grinding tool
   */
   QList<uint> getValidSwivelGrindAlignNumberList (int channelNumber);

  /*! \fn QList<uint> getValidTraOriDynNumberList (void);
   *  \return                             : list of swivel data records or transformation records
   *
   *  retuns a list of all valid TRAORI numbers
   */
   QList<uint> getValidTraOriDynNumberList (void);

   /*! \fn QList<uint> getValidTraIntNumberList (void);
    *  \return                             : list of valid swivel numbers for interpolations turning
    *
    *  retuns a list of valid swivel numbers for interpolations turning
    */
   QList<uint> getValidTraIntNumberList (void);

  /*! \fn SlStepTraCylAlternativeCallDataList getValidTraCylAlternativeCallData (int channelNumber)
   *  \param channelNumber       in: channel number
   *  \return                      : list of valid alternative call data
   *
   *  retuns a list of valid alternative call numbers, dependent from the channel number
   */
   SlStepTraCylAlternativeCallDataList getValidTraCylAlternativeCallData (int channelNumber);

  /*! \fn SlStepTraCylAlternativeCallData getValidTraCylAlternativeCallData (int channelNumber, int altCallNaumber)
   *  \param channelNumber       in: channel number
   *  \param altCallNaumber      in: alternative call number
   *  \return                      : alternative call data
   *
   *  retuns valid alternative call data
   */
   SlStepTraCylAlternativeCallData getValidTraCylAlternativeCallData (int channelNumber, int altCallNaumber);

  /*! \fn bool existValidTraangAlternativeCallData (int channelNumber)
   *  \param channelNumber       in: channel number
   *  \return                      : traang exists for channel number
   *
   *  retuns if a valid traang exist for channel number
   */
   bool existValidTraangAlternativeCallData (int channelNumber);

   /*! \fn QList<uint> getAllSwivelNumberList (int channelNumber, SlStepSwivelSourceEnum swivelDataSource)
   *  \param channelNumber               in: channel number
   *  \param swivelDataSource                in: use TC or KT or both
   *  \return                              : list of swivel data recors
   *
   *  retuns a list of all swivel data record numbers, which are deactiveted or 
   *  activated.
   *  Condition, all this swivel data records has been assigned a name.
   *  Special case, if only one swivel data record is activated, the swivel name
   *  can be a empty string.
   */
   QList<uint> getAllSwivelNumberList (int channelNumber, SlStepSwivelSourceEnum swivelDataSource);

  /*! \fn QStringList getAllSwivelDataNames (int channelNumber, SlStepSwivelSourceEnum swivelDataSource);
   *  \param channelNumber        in: channel number
   *  \param swivelDataSource         in: TC or KT or both
   *  \return                       : list with the names of the swivel data records
   *
   *  retuns a list of all swivel data record names.
   *  Special case, if only one swivel data record is activated, the swivel name
   *  can be a empty string.
   */
  QStringList getAllSwivelDataNames (int channelNumber, SlStepSwivelSourceEnum swivelDataSource);

   /*!\fn int getSwivelNumberBySwivelName (int channelNumber, const QString& rSwivelName, int swivelType
                                          bool bUseDeselection = true, SlStepSwivelSourceEnum swivelDataSource,
                                          bool bOnlyTcClassic = false);
    * \param channelNumber               in: channel number
    * \param rSwivelName                 in: name of the swivel data record
    * \param swivelType                  in: align or frame swivel data record
    * \param bUseDeselection             in: true = deslection of a swivel data record is possible in the mask
    * \param swivelDataSource in         in: use KT or TC or both
    * \param bOnlyTcClassic              in: true = only TC Classic
    * \return                              : corresponding swivel number
    *
    *  determine the togglestate (swivelNumber) about the swivel data record name
    *  methode is plublic, because is it used in the form too.
    */
   int getSwivelNumberBySwivelName (int channelNumber, const QString& rSwivelName, int swivelType,
                                    bool bUseDeselection,
                                    SlStepSwivelSourceEnum swivelDataSource, bool bOnlyTcClassic = false);
   
   /*!\fn bool isKinematicTransformation (int swivelNumber) const;
    * \param swivelNumber               in: swivel number
    * \return                             : KT or TC
    *
    *  return, whether the swivel number belongs to KinematicTransformation or to ToolCarrier
    */
   bool isKinematicTransformation (int swivelNumber) const;

   /*! \fn QString getSwivelNameBySwivelNumber (int channelNumber, int swivelToggleState,
                                               const QString& notExistendName = QString());
    *  \param channelNumber               in: channel number
    *  \param swivelToggleState           in: swivel or transformation number
    *  \param notExistendName             in: not existend name which was interpretiert
    *  \return                              : swivel or transformation name
    *
    *  determine the name of the swivel data record about the togglestate = swivel number
    */
   QString getSwivelNameBySwivelNumber (int channelNumber, int swivelToggleState,
                                        const QString& notExistendName = QString());

  /*! \fn int getKinematicTransformationNumber(int channelNumber, const QString& rsInputRotAxisName)
   *
   *  \param rsInputRotAxisName          in: rotary axis name
   *
   *   check about individual swivel data record
   */
   int getKinematicTransformationNumber(int channelNumber, const QString& rsInputRotAxisName);

  /*! \fn bool isSwivelToggleEnable (int channelNumber, int swivelType, SlStepSwivelSourceEnum swivelDataSource,
                                     bool bOnlyTcClassic = false);
   *  \param channelNumber               in: channel number
   *  \param swivelType                  in: align or frame swivel data record
   *  \param swivelDataSource            in: use TC or KT or both
   *  \param bOnlyTcClassic              in: true = only TC Classic
   *  \return                              : toggle swivel data record enable?
   *
   *  returns the info, whether the swivel data record can be toggled and
   *  additional the first activated swivel data record
   */
   bool isSwivelToggleEnable (int channelNumber, int swivelType, SlStepSwivelSourceEnum swivelDataSource,
                              bool bOnlyTcClassic = false);

  /*! \fn bool isTrafoSuitableForClamping(int nChannelNumber, int nTrafoNumber, const QString& rsRotaryAxisClamping);
   *  \param nChannelNumber              in: channel number
   *  \param nTrafoNumber                in: kinematic transformation number
   *  \param sRotaryAxisClamping         in: rotary axis name of current clamping
   *  \return                              : true, if the kinematic transformation number is suitable for the clamping
   *                                         false, otherwise
   *
   *  returns the info, whether the kinematic transformation number is suitable for the current clamping
   */
   bool isTrafoSuitableForClamping(int nChannelNumber, int nTrafoNumber, const QString& rsRotaryAxisClamping);

  /*! \fn bool isSelectAndDeselectSwivelEnable(int channelNumber);
   *  \param channelNumber  in: channel number
   *  \return                 : enable state
   *
   *  returns the information whether deselect swivel data record is enable
   */
   bool isDeselectSwivelEnable(int channelNumber);

  /*! \fn int getActiveSwivelNumber(void);
   *  \return            out: active swivel number
   *
   *  in the NC active swivel data record number will returned
   */
   int getActiveSwivelNumber(void);

  /*! \fn QList<uint> getAllowedRetractionToggleStates (int channelNumber, int swivelNumber,
                                                        SlStepSwivelSourceEnum swivelDataSource = SL_SWIVEL_SOURCE_TC);
   *  \param channelNumber               in: channel number
   *  \param swivelNumber                in: number of swivel data record
   *  \param swivelDataSource            in: use TC or KT or both
   *  \return                              : allowed togglestates list
   *
   *   returns the allowed toggle states for the retraction.
   *   Passed can the swivel data record number or it's name.
   */
   QList<uint> getAllowedRetractionToggleStates (int channelNumber, int number,
                                                 SlStepSwivelSourceEnum swivelDataSource = SL_SWIVEL_SOURCE_TC);

  /*! \fn int getSwivelInitRetraction (int channelNumber)
   *  \param channelNumber             in: channel number
   *  \return                            : initialise state of retraction
   *
   *   0 = no change
   *   1 = no retraction
   *   2 = Z
   *   3 = Z XY
   *   4 = tool direction max.
   *   5 = tool direction inc.
   */
  int getSwivelInitRetraction (int channelNumber);
   
  /*! \fn int swivelInitSwivelMode (int channelNumber)
   *  \param channelNumber             in: channel number
   *  \return                            : initialise state of swivel mode
   *
   *  0 = axis by axis
   *  1 = direct mode
   */
  int swivelInitSwivelMode (int channelNumber);

  /*! \fn SwivelModeQList getAllowedSwivelModeToggleStates (int channelNumber, int swivelNumber);
   *  \param channelNumber  in: channel number
   *  \param swivelNumber                in: number of swivel data record
   *  \return              out: allowed togglestates
   *
   *   returns the allowed toggle states for the swivel mode
   */
   SwivelModeQList getAllowedSwivelModeToggleStates (int channelNumber, int swivelNumber);

  /*! \fn int getInitSwivelDirection (int channelNumber, int swivelNumber);
   *  \param channelNumber               in: channel number
   *  \param swivelNumber                in: number of swivel data record
   *  \return                              : allowed default or initialise direction
   *
   *   returns the allowed default or initialise direction
   */
   int getInitSwivelDirection (int channelNumber, int swivelNumber);

   /*! \fn bool isMoreDirectionEnable (int channelNumber, int swivelNumber);
   *  \param channelNumber               in: channel number
   *  \param swivelNumber                in: number of swivel data record
   *  \return                              : true = more directions
   *
   *   Are more direction possible
   *   Passed can the swivel data record number or it's name.
   */
   bool isMoreDirectionEnable (int channelNumber, int swivelNumber);

  /*! \fn int getAxisReferencingDirection (int channelNumber, int swivelNumber);
   *  \param channelNumber               in: channel number
   *  \param swivelNumber                in: number of swivel data record
   *  \param bUseKinematicTransformation in: use kinematic transformation
   *  \return                              : Direction reference
   *
   *   Which rotary axis reference the direction?
   *   Passed can the swivel data record number or it's name.
   */
   int getAxisReferencingDirection (int channelNumber, int swivelNumber);

  /*! \fn QList<uint> getAllowedTrackingToggleStates (int channelNumber, int swivelNumber);
   *  \param channelNumber               in: channel number
   *  \param swivelNumber                in: number of swivel data record
   *  \return                              : allowed togglestates
   *
   *   returns the allowed toggle states for the tracking mode
   *   Passed can the swivel data record number or it's name.
   */
   QList<uint> getAllowedTrackingToggleStates (int channelNumber, int swivelNumber);

  /*! \fn int getSwivelInitTracking (int channelNumber)
   *  \param channelNumber             in: channel number
   *  \return                            : initialise state of tracking
   *
   *  0 = no change
   *  1 = no tracking
   *  2 = tracking
   */
   int getSwivelInitTracking (int channelNumber);
  
  /*! \fn QStringList getRotaryAxisNames (int channelNumber, int swivelNumber);
   *  \param channelNumber  in: channel number
   *  \param swivelNumber   in: number of swivel data record
   *  \return              out: names of rotary axis
   *
   *   returns a list with the rotary axis
   *   Passed can the swivel data record number or it's name.
   */
   QStringList getRotaryAxisNames (int channelNumber, int swivelNumber);

  /*! \fn SlStepSwivelRotOperationModePair getRotaryAxisOperationMode (int channelNumber, int swivelNummer);
   *
   *  \param channelNumber  in: channel number
   *  \param swivelNumber   in: number of swivel data record
   *  \return               the information of operation mode of rotary axis 1 and rotary axis 2   
   *
   *  returns the information of rotary axis: automatic, manual or semi automatic
   */
   SlStepSwivelRotOperationModePair getRotaryAxisOperationMode (int channelNumber, int swivelNummer);

   /*! \fn SlStepBasicToolPositionEnum getBasicToolPosition(int channelNumber);
   *  \param channelNumber  in: channel number
   *  \return               the basic tool position  
   *
   *  returns tool direction in basic position, for the alignment tool (ShopTurn)
   */
   SlStepBasicToolPositionEnum getBasicToolPosition(int channelNumber);

  /*! \fn void getToolSwivelBetaMinMax (int channelNumber, double& rBetaMin, double& rBetaMax);
   *  \param channelNumber  in: channel number
   *  \param rBetaMin       out: reference to minimal value of beta
   *  \param rBetaMax       out: reference to maximal value of beta
   *
   *  returns beta min/max, for the alignment tool (ShopTurn)
   */
   void getToolSwivelBetaMinMax (int channelNumber, double& rBetaMin, double& rBetaMax);

  /*! \fn void getTcBetaMinMax (int channelNumber, int swivelNumber, double& rBetaMin, double& rBetaMax);
   *  \param channelNumber  in: channel number
   *  \param swivelNumber   in: number of swivel data record
   *  \param rBetaMin       out: reference to minimal value of beta
   *  \param rBetaMax       out: reference to maximal value of beta
   *
   *  returns beta min/max, for the alignment tool (circular grinding)
   */
   void getTcBetaMinMax (int channelNumber, int swivelNumber, double& rBetaMin, double& rBetaMax);

   /*! \fn void getBAxisEnvironment (int channelNumber, int swivelNumber, double& rBmin, double& rBmax, double& rOffset, SlStepBasicToolPositionEnum& rBasicToolPositionB);
   *  \param channelNumber    in: channel number
   *  \param swivelNumber     in: number of swivel data record
   *  \param rotaryAxisNumber in: number of rotary axis
   *  \param rBmin            out: reference to minimal value of B-axis
   *  \param rBmax            out: reference to maximal value of B-axis
   *  \param rOffset             out: reference to B-axis angle offset
   *  \param rBasicToolPositionB out: basic tool position
   *
   *  returns all data's of the B-axis, for measuring kinematics complete (Turning Machine)
   *  There are also separate interface functions for each individual date. 
   *   - B min/max,
   *   - tool direction in basic position
   *   - offset of the B-axis
   */
   void getBAxisEnvironment (int channelNumber, int swivelNumber, int rotaryAxisNumber,
                             double& rBmin, double& rBmax, double& rOffset, SlStepBasicToolPositionEnum& rBasicToolPositionB);

   /*! \fn void getBAxisMinMax (int channelNumber, int swivelNumber, int rotaryAxisNumber, double& rBmin, double& rBmax);
   *  \param channelNumber    in: channel number
   *  \param swivelNumber     in: number of swivel data record
   *  \param rotaryAxisNumber in: number of rotary axis
   *  \param rBmin            out: reference to minimal value of B-axis
   *  \param rBmax            out: reference to maximal value of B-axis
   *
   *  Returns the B min/max between the software limit switches, for measuring kinematics complete (Turning Machine).
   */
   void getBAxisMinMax (int channelNumber, int swivelNumber, int rotaryAxisNumber, double& rBmin, double& rBmax);

   /*! \fn void getBAxisOffset (int channelNumber, int swivelNumber, int rotaryAxisNumber, double& rOffset);
   *  \param channelNumber    in: channel number
   *  \param swivelNumber     in: number of swivel data record
   *  \param rotaryAxisNumber in: number of rotary axis
   *  \param rOffset          out: reference to B-axis angle offset
   *
   *  Returns the offset of the B axis, for measuring kinematics complete (Turning Machine).
   */
   void getBAxisOffset (int channelNumber, int swivelNumber, int rotaryAxisNumber, double& rOffset);

   /*! \fn getBAxisBasicToolPosition (int channelNumber, int swivelNumber, SlStepBasicToolPositionEnum& rBasicToolPositionB);
   *  \param channelNumber       in: channel number
   *  \param swivelNumber        in: number of swivel data record
   *  \param rBasicToolPositionB out: basic tool position
   *
   *  Returns the tool direction in basic position, for measuring kinematics complete (Turning Machine)
   */
   void getBAxisBasicToolPosition (int channelNumber, int swivelNumber, SlStepBasicToolPositionEnum& rBasicToolPositionB);

   /*! \fn void getToolSwivelBMinMax(int channelNumber, int swivelNumber, double& dBMin, double& dBMax);
   *  \param channelNumber  in: channel number
   *  \param swivelNumber   in: number of swivel data record
   *  \param dBMin          in, out: reference to minimal value of axis B
   *  \param dBMax          in, out: reference to maximal value of axis B
   *
   *  Returns the B min/max between the software limit switches. (Turning on milling machine)
   */
   bool getToolSwivelBMinMax(int channelNumber, int swivelNumber, double& dBMin, double& dBMax);

   /*! \fn void getDivisorAndOffsetOfHirthAxis(int channelNumber, int swivelNumber, enum RotaryAxisNameIndex hirthAxisIndex,
   *                                           double& rdDivisor, double& rdOffset);
   *  \param channelNumber         in: channel number
   *  \param swivelNumber          in: number of swivel data record
   *  \param hirthAxisIndex        in: hirth axis index (ROT_AXIS_TOOL_B or ROT_AXIS_TOOL_C)
   *  \param rdDivisor             in, out: reference to divisor of the hirth axis
   *  \param rdOffset              in, out: reference to offset of the hirth axis
   *  returns true, if rdDivisor and rdOffset are valid
   */
   bool getDivisorAndOffsetOfHirthAxis(int channelNumber, int swivelNumber, enum RotaryAxisNameIndex hirthAxisIndex,
                                       double& rdDivisor, double& rdOffset);

  /*! \fn bool isHirthToothSystemEnable (int channelNumber, int swivelNumber);
   *  \param channelNumber  in: channel number
   *  \param swivelNumber   in: number of kinematic transformation
   *  \return              out: state hirth tooth system exist
   *
   *  returns the state hirth tooth system exist for any axis (workpiece, tool B, tool C) 
   */
   bool isHirthToothSystemEnable (int channelNumber, int swivelNumber);

  /*! \fn RotaryAxisNameIndexQList getHirthToothSystemAxesList (int channelNumber, int swivelNumber);
   *  \param channelNumber  in: channel number
   *  \param swivelNumber   in: number of kinematic transformation
   *  \return              out: list of axes which have a hirth tooth system
   *
   *  returns the list of axes (workpiece, tool B, tool C) which have a hirth tooth system
   */
   RotaryAxisNameIndexQList getHirthToothSystemAxesList (int channelNumber, int swivelNumber);

  /*! \fn SlSwivelLocationEnum getSwivelLocation (int channelNumber, int swivelNumber);
   *  \param channelNumber               in: channel number
   *  \param swivelNumber                in: number of kinematic transformation
   *  \return                           out: location of the swivel mechanic
   *
   *   returns the location of the swivel mechanic
   */
   SlSwivelLocationEnum getSwivelLocation (int channelNumber, int swivelNumber);

  /*! \fn SlSwivelMechanicsEnum getSwivelMechanics (int channelNumber, int swivelNumber);
   *  \param channelNumber               in: channel number
   *  \param swivelNumber                in: number of kinematic transformation
   *  \return                           out: type of swivel mechanics
   *
   *   returns type of swivel mechanics
   */
   SlSwivelMechanicsEnum getSwivelMechanics (int channelNumber, int swivelNumber);

  /*! \fn void readSwivelLengthOffset (int channelNumber, int swivelNumber, double& rOffsetLengthX, double& rOffsetLengthZ);
   *  \param channelNumber       in: channel number
   *  \param swivelNumber        in: number of kinematic transformation
   *  \param rOffsetLengthX     out: x component of the length offset
   *  \param rOffsetLengthZ     out: z component of the length offset
   *
   *   returns the 2. length offset
   */
   void readSwivelLengthOffset (int channelNumber, int swivelNumber, double& rOffsetLengthX, double& rOffsetLengthZ);

  /*! \fn int getSwivelNumberBySpindle(int spindleTyp, int channelNumber);
   *  \param spindleTyp     in: spindle typ
   *  \param channelNumber  in: channel number
   *  \return              out: swivel number
   *
   *   get swivel number for shopturn with the help of the spindeltype
   */
   int getSwivelNumberBySpindle(int spindleTyp, int channelNumber);
   
  /*! \fn uint checkSwivelDataSettings (int channelNumber, int swivelType, SlStepSwivelSourceEnum swivelDataSource
                                        int swivelNumber, bool bOnlyTcClassic = false);
   *  \param channelNumber               in: channel number
   *  \param swivelType                  in: type of the swivel data record
   *  \param swivelDataSource            in: use TC or KT or both
   *  \param swivelNumber                in: swivel number
   *  \param bOnlyTcClassic              in: true = only TC Classic
   *  \return                              : part of error message
   *
   *   general swivel data check
   */
   uint checkSwivelDataSettings (int channelNumber, int swivelType, SlStepSwivelSourceEnum swivelDataSource,
                                 int swivelNumber, bool bOnlyTcClassic = false);

  /*! \fn int checkIndividualSwivels (int channelNumber, int swivelNumber, int swivelType, bool bUseInvalidValues,
                                      bool bUseDeselection, SlStepSwivelSourceEnum swivelDataSource, bool bOnlyTcClassic = false);
   *  \param channelNumber               in: channel number
   *  \param swivelNumber                in: swivel number
   *  \param swivelType                  in: align or frame swivel data record
   *  \param bUseInvalidValues           in: true = empty TC-toggler is possible in mask 
   *  \param bUseDeselection             in: true = deslection of a swivel data record is possible in mask
   *  \param swivelDataSource            in: use KT or TC or both
   *  \param bOnlyTcClassic              in: true = only TC Classic
   *  \return                              : error state
   *
   *   check about individual swivel data record
   */
   int checkIndividualSwivels (int channelNumber, int swivelNumber, int swivelType, bool bUseInvalidValues,
                               bool bUseDeselection, SlStepSwivelSourceEnum swivelDataSource,
                               bool bOnlyTcClassic = false);

  /*! \fn bool isKt45DegreeMechanics (int swivelNumber);
   *  \param swivelNumber        in: swivel number
   *  \return                      : state
   *
   *   returns the state, is it a 45 dregree swivel mechanic 
   */
   bool isKt45DegreeMechanics (int swivelNumber);

  /*! \fn void getActiveChannelNumber(int& rChannelNumber);
   *  \param rChannelNumber  out: channel number
   *
   *   returns the channel number if it be -1
   */
   void getActiveChannelNumber(int& rChannelNumber);
   
  /*! \fn void refreshCache (void);
   *
   *   erase the swivel number, so the cache for the swivel datas will new loaded from NCK
   */
   void refreshCache (void);

  /*! \fn void refreshData(int channelNumber);
   *  \param channelNumber  in: channel number
   *
   *   erase the markers, so the swivel datas are loaded new from NCK
   */
   void refreshData(int channelNumber);


  // ---------------------------------------------------------------------------
  // Methoden für den Inbetriebnahmedialog Schwenkdatensätze
  // ---------------------------------------------------------------------------
  
  /*! \fn SlStepAllSwivelsInfo getAllSwivelsInfos (void);
   *  \return                   : data of all swivel data records
   *
   *   get a list with all swivel data record names, swivel data record numbers,
   *   swivel types and TO unit numbers
   */
   SlStepAllSwivelsInfo getAllSwivelsInfos (void);

  /*! \fn SlStepKinematicTrafoData getKinematicTrafoData (int ktNumber);
   *  \param ktNumber         in: number of the kinematic transformation
   *  \return                   : data of the kinematic transformation
   *
   *   Get the swivel data record from the wanted kinematic transformation
   */
   SlStepKinematicTrafoData getKinematicTrafoData (int ktNumber);
   
  /*! \fn SlStepToolCarrierData getToolCarrierData (int tcNumber, int toUnitNumber);
   *  \param tcNumber         in: number of the toolCarrier
   *  \param toUnit Number     in: toUnit Number
   *  \return                   : data of the toolCarrier
   *
   *   Get the swivel data record from the wanted toolCarrier
   */
   SlStepToolCarrierData getToolCarrierData (int tcNumber, int toUnitNumber);

  /*! \fn SlCapErrorEnum writeKinematicTrafoData (const SlStepKinematicTrafoData& ktData, int ktNumber);
   *  \param ktData         in: data record of the kinematic transformation
   *  \param ktNumber       in: number of the kinematic transformation
   *  \return                 : error
   *
   *   Write the swivel data record to the wanted kinematic transformation
   */
   SlCapErrorEnum writeKinematicTrafoData (const SlStepKinematicTrafoData& rKtData, int ktNumber);

  /*! \fn SlCapErrorEnum writeToolCarrierData (const SlStepToolCarrierData& rTcData, int tcNumber, int toUnitNumber);
   *  \param rTcData        in: data record of the toolCarrier
   *  \param tcNumber       in: number of the toolCarrier
   *  \param toUnitNumber   in: number of the toUnit
   *  \return                 : error
   *
   *   Write the swivel data record to the wanted toolCarrier
   */
   SlCapErrorEnum writeToolCarrierData (const SlStepToolCarrierData& rTcData, int tcNumber, int toUnitNumber);

  /*! \fn SlSwivelErrorEnum deleteSwivelDataRecord (const SlStepSwivelsInfo& rSwivelInfo);
   *  \param rSwivelInfo    in: general information about the swivel data records list.
   *  \return                 : error state
   *
   *   Deletes the wanted swivel data record.
   */
   SlSwivelErrorEnum deleteSwivelDataRecord (const SlStepSwivelsInfo& rSwivelInfo);

  /*! \fn SlSwivelErrorEnum copySwivelDataRecord (const SlStepSwivelsInfo& rSwivelInfo);
   *  \param rSwivelInfo    in: general information about the swivel data records list.
   *  \return                 : error state
   *
   *   Copied the wanted the swivel data record
   */
   SlSwivelErrorEnum copySwivelDataRecord (const SlStepSwivelsInfo& rSwivelInfo);

  /*! \fn SlSwivelErrorEnum pasteSwivelDataRecord (const SlStepSwivelsInfo& rSwivelInfo, const QString& NewName);
   *  \param rSwivelInfo    in: general information about the swivel data records list.
   *  \return                 : error state
   *
   *   Pasted the wanted the swivel data record
   */
   SlSwivelErrorEnum pasteSwivelDataRecord (const SlStepSwivelsInfo& rSwivelInfo, const QString& NewName=QString());

   /*! \fn SlSwivelEditFunctionList swivelEditFunctionAllowed (const SlStepSwivelsInfo& rSwivelInfo);
    *
    *  \param rSwivelInfo    in: general information about the swivel data records list.
    *  \return             out: list of possible edit functions
    *
    *  returns a of possible edit functions
    */
   SlSwivelEditFunctionList swivelEditFunctionAllowed (const SlStepSwivelsInfo& rSwivelInfo);

   /*! \fn SlSwivelErrorEnum swivelEditFunctionError (const SlStepSwivelsInfo& rSwivelInfo, SlSwivelEditFunctionEnum editFunction);
    *
    *  \param rSwivelInfo    in: general information about the swivel data records list.
    *  \param editFunction   in: kind of edit function
    *  \return              out: error state of edit function
    *
    *  returns the error state of the wanted edit function
    */
   SlSwivelErrorEnum swivelEditFunctionError (const SlStepSwivelsInfo& rSwivelInfo, SlSwivelEditFunctionEnum editFunction);

   /*! \fn bool swivelDataRecordNameExists (QString swivelName, int swivelNumber =0, const QString& rTrafoTyp =QString(),
                                            int m_nToUnitNumber);
    *  \param swivelName      in: name of swivel data record
    *  \param swivelNumber    in: number of swivel data record
    *  \param rTrafoTyp       in: trafo type of swivel data record
    *  \param m_nToUnitNumber in: number of TO-unit
    *  \return               out: error state
    *
    *  Does the name already exist?
    */
   bool swivelDataRecordNameExists (const QString& rSwivelName, int swivelNumber = 0, const QString& rTrafoTyp = QString(),
                                    int toUnitNumber = 0);

  // ---------------------------------------------------------------------------
  // PUBLIC OF PSEUDO SLOTS CALLED BY CALL BACK OBJECT
  // ---------------------------------------------------------------------------

  /*! \fn void setActiveChanSlot(const QString& rsChan);
   *  \param rsChan  in: channel number
   *
   *   Da diese Klasse keine Slot oder Signals behandeln kann, wird dieser
   *   Pseudo Slot von einer Klasse aufgerufen die das Signal Kanalwechsel
   *   empfangen kann und es dieser Methode weiterleitet.
   */
   void setActiveChanSlot(const QString& rsChan);

  /*! \fn void setActiveChanSlot(const QString& rsChan);
   *  \param rsChan  in: channel number
   *
   *   Da diese Klasse keine Slot oder Signals behandeln kann wird dieser
   *   Pseudo Slot von einer Klasse aufgerufen die das Signal Power On Reset
   *   empfangen kann und es dieser Methode weiterleitet.
   */
   void setConnectStateSlot (SlMaConnectStateEnum state);

private:

   // private constructor can only called by 
   // singleton friend
   SlStepSwivelData();

   // private destructor can only called by
   // singleton friend
   ~SlStepSwivelData();

   // -- container
   typedef QVector<int>               SpindleQVector;           //!< list existing spindle types on machine
   typedef QList<uint>                NumberQList;              //!< list of valid swivelnumbers


   QMap<uint, NumberQList>         m_allSwivelNumberMap;                 //!< value is list of dependend swivel numbers of the names, key is TO unit number
   QMap<uint, SwivelDataSetQList>  m_allSwivelDataMap;                   //!< save swivel names, key i s TO unit number
   QMap<uint, NumberQList>         m_validSwivelFrameNumberWithChainMap; //!< value is list of valid swivel numbers, key is TO unit number
   QMap<uint, NumberQList>         m_validSwivelFrameNumberClassicMap;   //!< value is list of valid swivel numbers, key is TO unit number
   QMap<uint, NumberQList>         m_validSwivelAlignNumberWithChainMap; //!< value is list of valid align tool numbers, key is TO unit number
   QMap<uint, NumberQList>         m_validSwivelAlignNumberClassicMap;   //!< value is list of valid align tool numbers, key is TO unit number
   QMap<uint, NumberQList>         m_validSwivelGrindAlignNumberMap;     //!< value is list of valid grinding align tool numbers, key is TO unit number

   QMap<uint, uint>                m_toUnitNumberMap;           //!< value list of to-unit numbers, key is channel number
   QMap<uint, SpindleQVector>      m_spindleSwivelMap;          //!< value swivel number <-> spindle type, key is TO unit number

   NumberQList                     m_allTrafoNumberList;        //!< value is list of dependend swivel numbers of the names
   SwivelDataSetQList              m_allTrafoDataList;          //!< value is tranformation name, key is transformation number
   NumberQList                     m_validTrafoAlignNumberList; //!< list of valid transformation numbers for align tool
   NumberQList                     m_validTraOriDynNumberList;  //!< list of valid transformation numbers for TRAORI
   NumberQList                     m_validTransmitNumberList;   //!< list of valid transformation numbers for TRANSMIT_K
   NumberQList                     m_validTracylNumberList;     //!< list of valid transformation numbers for TRACYL_K
   NumberQList                     m_validTraangNumberList;     //!< list of valid transformation numbers for TRAANG_K
   NumberQList                     m_validTraintNumberList;     //!< list of valid transformation numbers for TRAINT interpolation turning

   QList<uint>                     m_channelInitList;           //!< memorise the channel numbers
   QList<uint>                     m_toUnitInitList;            //!< memorise the to unit numbers
   bool                            m_bTrafoInit;                //!< kinematic transformation must new initialised
   bool                            m_bToUnitInit;               //!< marker for initialise TO-Unit, channel nummer
   int                             m_numSwivelsPerToUnit;       //!< number of swivel data records per TO-Unit
   int                             m_numTrafos;                 //!< number of valid trafo chains

   SlStepSwivelDataCallBack*       m_pCallBack;                 //!< my callback object pointer auf eine Klasse, die Slot/Signal behandeln kann
   SlMaLogic*                      m_pMaLogic;                  //!< pointer auf das machine logic object
   
   // members for caching a read swivel data record
   QMutex                        m_cacheMutex;                  //!< mutex to lock cache against calls from different threads
   SlStepSwivelDataRecord        m_cacheDataRecord;             //!< cached swivel data record
   int                           m_cacheChannelNumber;          //!< channel number of cached swivel data record

   // ---------------------------------------------------------------------------
   // Member für den Inbetriebnahmedialog Schwenkdatensätze
   // ---------------------------------------------------------------------------
   
   SlStepAllSwivelsInfo          m_allSwivelsInfos;            //!< List with swivel infos, e.g swivel names und numbers
   
   SlStepKinematicTrafoData      m_KinematicTrafoData;          //!< cached all datas from the kinematic trafomation data record
   SlStepToolCarrierData         m_ToolCarrierData;             //!< cached all datas from the tool carrier data record

   SlStepKinematicTrafoData      m_copyBufferKT;               //!< saved kinematic datas for paste
   SlStepToolCarrierData         m_copyBufferTC;               //!< saved toolcarrier datas for paste


   // ---------------------------------------------------------------------------
   // Member für den Maske Zylindertransformation
   // ---------------------------------------------------------------------------

   bool                                 m_initAlternativeTracylCall;       //!< marker for get data for the alternative TRACYL call
   bool                                 m_initAlternativeTraangCall;       //!< marker for get data for the alternative TRAANG call
   SlStepTraCylAlternativeCallDataList  m_allAlternativeTracylCallData;    //!< list of valid alternative TRACYL call data
   SlStepTraangAlternativeCallDataList  m_allAlternativeTraangCallData;    //!< list of valid alternative TRAANG call data
   
  
  // --------------------------------------------------------------------------
  //    PRIVATE METHODES OF SWIVEL-DATA-RECORDS   
  // --------------------------------------------------------------------------

   /*! \fn void callInitSwivelDataEnviorment (int& rChannelNumber, SlStepSwivelSourceEnum swivelDataSource);
    *  \param channelNumber        in: channel number
    *  \param swivelDataSource     in: TC or TC or both
    *  \return                       : list all swivel data record names and properties
    *
    *   The function calls the appropriate initialization for the swiveling.
    */
   void callInitSwivelDataEnviorment (int& rChannelNumber, SlStepSwivelSourceEnum swivelDataSource);

   /*! \fn SwivelDataSetQList initSwivelDataEnviorment (int channelNumber, bUseKinematicTransformation);
    *  \param channelNumber                in: channel number
    *  \param bUseKinematicTransformation  in: kinematic transformation will be used
    *  \return                               : list all swivel data record names and properties
    *
    *   initalise the environment of the swivel data record and returns a list of all swivel data records
    */
   SwivelDataSetQList initSwivelDataEnviorment (int& rChannelNumber, bool bUseKinematicTransformation);

   /*! \fn void initNumberKinematicTransformation(void);
    *
    *   it is determined the number of transformation chains
    */
   void initNumberKinematicTransformation (void);

   /*! \fn uint getNumKinematicTransformation(void);
    *
    *   Got the number of transformation chains.
    *   This number indicates how many records the user will really use.
    */
   uint getNumKinematicTransformation (void);

   /*! \fn void initNumSwivelPerToUnit(void);
    *  \param channelNumber in: channel number
    *
    *   get number of kinamatic transformations
    */
   void initNumberSwivelPerToUnit(void);

  /*! \fn void initToUnitListByChannel(void);
   *  \param channelNumber in: channel number
   *
   *   got the assignment channel, to-unit.
   */
   void initToUnitListByChannel(void);

  /*! \fn int toUnitByChannel(int channelNumber)
   *
   *   gets the to-unit number by channel number.
   */
   int toUnitByChannel(int channelNumber);

  /*! \fn SwivelDataSetQList initSwivelNumberAndNamesList (int channelNumber, bool bUseKinematicTransformation = false);
   *  \param channelNumber               in: channel number
   *  \param bUseKinematicTransformation  in: kinematic transformation will be used
   *
   *   generates a list of names and indices about the swivel data records.
   *   gaps of swivel data records are not be memorised in member variables.
   *   returns a list of all swivel data record including gaps.
   */
   SwivelDataSetQList initSwivelNumberAndNamesList (int channelNumber, bool bUseKinematicTransformation = false);

  /*! \fn void fillValidSwivelNumberMap (int swivelCounter, int swivelNumber, uint alignProperty1, uint alignProperty2,
                                         SwivelDataSetQList *pAllRecordData, NumberQList* pAllSwivelNumbers,
                                         NumberQList* pAllValidSwivelNumbers, bool bUseKinematicTransformation);
   *  \param swivelCounter                in: counting swivel number
   *  \param swivelNumber                 in: swivel number
   *  \param alignProperty1               in: property of the alignment
   *  \param alignProperty2               in: property of the alignment
   *  \param pAllRecordData               in: list of swivel name, property and trafo type
   *  \param pAllSwivelNumbers            in: list of swivel number
   *  \param pValidSwivelNumbers         out: number list of valid swivels
   *  \param bUseKinematicTransformation  in: kinematic transformation will be used
   *
   *   generates a list of names and indices about the swivel data records.
   *   gaps of swivel data records are not be memorised.
   */
   void fillValidSwivelNumberMap (int swivelCounter, int swivelNumber, uint alignProperty1, uint alignProperty2,
                                  SwivelDataSetQList *pAllRecordData, NumberQList* pAllSwivelNumbers,
                                  NumberQList* pAllValidSwivelNumbers, const QString& sTrafoType,
                                  bool bUseKinematicTransformation);
            
  /*! \fn void getStringDataRecordOrderForInit(QVector<SlCapReadSpecType>& rReadSpec, QVector<SlCapReadResultType>& rReadResult,
                                               int numberRecords, int channelNumber, bool bUseKinematicTransformation = false);
   *  \param rReadSpec                 out: container for order
   *  \param numberRecords              in: number of data records
   *  \param channelNumber              in: channel number
   *  \param bUseKinematicTransformation in: kinematic transformation will be used
   *  \return                             : error state
   *
   *   build the string order the btss variablen
   */
   bool getStringDataRecordOrderForInit (QVector<SlCapReadSpecType>& rReadSpec,
                                         int numberRecords, int channelNumber,
                                         bool bUseKinematicTransformation = false);

  /*! \fn void initAssignmentSpindleSwivel (int channelNumber);
   *  \param channelNumber in: channel number
   *
   *   Initialise the assignment spindle type and swivel number
   */
   void initAssignmentSpindleSwivel (int channelNumber);


  /*! \fn void initSwivelDataRecord (SlStepSwivelDataRecord& rCacheDataRecord);
   *  \param  rCacheDataRecord               out: swivel data record
   *
   * cleans the swivel data record, due to swivel toggle
   */
   void initSwivelDataRecord (SlStepSwivelDataRecord& rCacheDataRecord);


  /*! \fn void initKinTrafoChannelDataRecord (SlStepSwivelDataRecord& rCacheDataRecord);
   *  \param  rCacheDataRecord               out: swivel data record
   *
   * cleans the swivel data record, due to channel change
   */
   void initKinTrafoChannelDataRecord (SlStepSwivelDataRecord& rCacheDataRecord);
   
   
  /*! \fn SlStepSwivelDataRecord getSwivelDataRecord (int channelNumber, int swivelNumber);
   *  \param channelNumber               in: channel number
   *  \param swivelNumber                in: swivel data record number
   *  \return                              : swivel data record
   *
   * About the swivel name or swivel number, the corresponding swivel data record
   * will be returned.
   */
  SlStepSwivelDataRecord getSwivelDataRecord (int channelNumber, int swivelNumber);

  /*! \fn void readSwivelDataRecord (int channelNumber, int swivelNumber, bool bAllKinematicTrafoData);
   *  \param channelNumber              in: channel number
   *  \param swivelNumber               in: swivel number
   *  \param bAllKinematicTrafoData      in: all data from the kinematic transformation data record are used
   *
   *  get the data record of swivel or transformation, according the record number
   */
  void readSwivelDataRecord (int channelNumber, int swivelNumber, bool bAllKinematicTrafoData);

  /*! \fn int getStringToOrderDataRecord (QVector<SlCapReadSpecType>& rReadSpec, int numberRecords, 
                                          int toUnitNumber, bool bAllKinematicTrafoData);
   *  \param rReadSpec                 out: container for the order
   *  \param numberRecords              in: number of Records
   *  \param toUnitNumber               in: to unit number
   *  \param bAllKinematicTrafoData in: all kinematic transformation data
   *  \return                             : error state
   *
   *  get the data record of swivel or transformation, according the record number
   */
  int getStringToOrderDataRecord (QVector<SlCapReadSpecType>& rReadSpec, int numberRecords,
                                  int toUnitNumber, bool bAllKinematicTrafoData);


  /*! \fn SlCapErrorEnum writeSwivelDataRecord (int recordNumber, int toUnitNumber) const;
   *  \param recordNumber                 in: record number
   *  \param toUnitNumber                 in: toUnit Number
   *  \return                               : error state
   *
   *  write the swivel dta recor in BTSS variables
   */
   SlCapErrorEnum writeSwivelDataRecord (int recordNumber, int toUnitNumber) const;


  /*! \fn int getStringToWriteDataRecord (QVector<SlCapWriteSpecType>& rWriteValues, int recordNumber,
                                           int toUnitNumber) const;
   *  \param rWriteValues                out: container for the order
   *  \param recordNumber                 in: number of Records
   *  \param toUnitNumber                 in: toUnit number
   *  \return                               : error state
   *
   *  write the data record of transformation, according the record number
   */
   int getStringToWriteDataRecord (QVector<SlCapWriteSpecType>& rWriteValues, int recordNumber,
                                    int toUnitNumber) const;

  /*! \fn void saveDataRecord (const QVector<SlCapReadResultType>& rReadResult, SlStepSwivelDataRecord& rSwivelDataRecord,
                               bool bUseKinematicTransformation, bool bAllKinematicTrafoData);
   *  \param rReadSpec                  in: container to receive the order
   *  \param bUseKinematicTransformation in: kinematic transformation will be used
   *  \param bAllKinematicTrafoData     in: all kinematic transformation data
   *
   *  get the data record of swivel or transformation, according the record number
   */
  void saveDataRecord (const QVector<SlCapReadResultType>& rReadResult,
                       bool bUseKinematicTransformation, bool bAllKinematicTrafoData);

  /*! \fn void getAllSwivelDataNamesList (QStringList* pSwivelNameList, int toUnitNumber, bool bUseKinematicTransformation);
   *  \param rSwivelNameList             out: list of all swivel data record names
   *  \param toUnitNumber                 in: to-unit number
   *  \param bUseKinematicTransformation  in: use tc or kt
   *
   *   Returns the name of swivel data record, appropriate to the number
   */
  void getAllSwivelDataNamesList (QStringList* pSwivelNameList, int toUnitNumber, bool bUseKinematicTransformation);

/*! \fn QString getSwivelDataName (int channelNumber, int swivelNumber);
   *  \param channelNumber              in: channel number
   *  \param swivelNumber               in: swivel number
   *  \return                             : name of the swivel data record
   *
   *   Returns the name of swivel data record, appropriate to the number
   */
  QString getSwivelDataName (int channelNumber, int swivelNumber);

   /*! \fn int indexOfSwivelName (int channelNumber, QString swivelName, bool bUseKinematicTransformation = false);
    *  \param channelNumber              in: channel number
    *  \param swivelName                 in: datarecord name
    *  \param bUseKinematicTransformation in: kinematic transformation will be used
    *  \return                             : index of datarecord
    *
    *  Gets index of data set with swivel name.
    */
   int indexOfSwivelName (int channelNumber, QString swivelName, bool bUseKinematicTransformation = false);

   /*! \fn void getRotaryAxisConfiguration (SlStepSwivelDataRecord& rSwivelDataRecord, int channel = 0);
    *  \param rSwivelDataRecord         out: swivel datas
    *  \param channel                    in: channel number
    *
    *  Gets the rotary axis configuration
    */
   void getRotaryAxisConfiguration (SlStepSwivelDataRecord& rSwivelDataRecord, int channel = 0);

   /*! \fn void getChainRotAxesNamesAndVectors (SlStepSwivelDataRecord& rSwivelDataRecord)
    *  \param rSwivelDataRecord           out: swivel datas
    *
    *  Get rotary axes names and their vectors. (only kinematic transformation)
    */
   void getChainRotAxesNamesAndVectors (SlStepSwivelDataRecord& rSwivelDataRecord);
   /*! \fn void getKtRotaryAxisLocation (SlStepSwivelDataRecord& rSwivelDataRecord)
    *  \param rSwivelDataRecord           out: swivel datas
    *
    *  Gets the location of the rotary axes. (only kinematic transformation)
    */
   void getKtRotaryAxisLocation (SlStepSwivelDataRecord& rSwivelDataRecord);

   /*! \fn void getTcRotaryAxisLocation (SlStepSwivelDataRecord& rSwivelDataRecord)
    *  \param rSwivelDataRecord           out: swivel datas
    *
    *  Gets the location of the rotary axes. (tool carrier)
    */
   void getTcRotaryAxisLocation (SlStepSwivelDataRecord& rSwivelDataRecord);

   /*! \fn void getKtSwivelLocation (SlStepSwivelDataRecord& rSwivelDataRecord)
    *  \param rSwivelDataRecord           out: swivel datas
    *
    *  Gets the location of the swivel mechanics. (only kinematic transformation)
    */
   void getKtSwivelLocation (SlStepSwivelDataRecord& rSwivelDataRecord);

   /*! \fn void getMachineMechanic (SlStepSwivelDataRecord& rSwivelDataRecord, int channelNumber);
    *  \param rSwivelDataRecord  in: swivel data record
    *  \param channelNumber      in: channel number
    *
    *  Compare the structur with the tables of machine mechanics. The result is correct machine mechanics
    */
   void getMachineMechanic (SlStepSwivelDataRecord& rSwivelDataRecord, int channelNumber);

   /*! \fn void getMachineType (int channelNumber, SlSwivelMachineType& rMachineType);
    *  \param channelNumber              in: channel number
    *  \param channelNumber             out: e.g. turning- milling- machine
    *
    *  With the help of technology and the coordinate system the machine type is determined.
    */
   void getMachineType (int channelNumber, SlSwivelMachineType& rMachineType);

   /*! \fn void swivelVectorNormalization (double& rVectorXin, double& rVectorYin, double& rVectorZin,
                                           int& rVectorXout, int& int, int& rVectorZout);
    *  \param rVectorXin      in: rotary axis vector x
    *  \param rVectorYin      in: rotary axis vector y
    *  \param rVectorZin      in: rotary axis vector z
    *  \param rVectorXout    out: rotary axis vector x
    *  \param rVectorYout    out: rotary axis vector y
    *  \param rVectorZout    out: rotary axis vector z
    *
    *  Normalization of the rotary axis vectors
    */
   void swivelVectorNormalization (double& rVectorXin, double& rVectorYin, double& rVectorZin,
                                   int& rVectorXout, int& rVectorYout, int& rVectorZout) const;

   /*! \fn void adaptToolCarrierToKinematicTrafo (rSwivelDataRecord, swivelMechanicsStruct);
    *  \param rSwivelDataRecord            in: swivel datas
    *  \param swivelMechanicsStruct       out: compare data
    *
    *  Gets the swivel mechanics. (only kinematic transformation)
    */
   void adaptToolCarrierToKinematicTrafo (SlStepSwivelDataRecord& rSwivelDataRecord, SlStepSwivelMechanicsStructType& rSwivelMechanicsStruct);

   /*! \fn void getKtToolDirectionVector (QString& rLastToolElemName, int& rVectorToolX, int& rVectorToolY, int& rVectorToolZ);
    *  \param rLastToolElemName           in: last element name of the tool chain
    *  \param rVectorToolX               out: tool direction vector
    *  \param rVectorToolY               out: tool direction vector
    *  \param rVectorToolZ               out: tool direction vector
    *
    *  Gets tool direction vectors, kinematic transformations
    */
   void getKtToolDirectionVector (const QString& rLastToolElemName, int& rVectorToolX, int& rVectorToolY, int& rVectorToolZ) const;

   /*! \fn void getTcToolDirectionVector (uint swivelProperty, int& rVectorToolX, int& rVectorToolY, int& rVectorToolZ);
    *  \param swivelProperty              in: swivel properties
    *  \param rVectorToolX               out: tool direction vector
    *  \param rVectorToolY               out: tool direction vector
    *  \param rVectorToolZ               out: tool direction vector
    *
    *  Gets tool direction vectors, from tool carrier
    */
   void getTcToolDirectionVector (uint swivelProperty, int& rVectorToolX, int& rVectorToolY, int& rVectorToolZ);

   /*! \fn void calcTcBetaOffsetsAndMinMax (SlStepSwivelDataRecord& rTransfoData);
    *  \param rTransfoData               out: swivel datas
    *
    *  This function is valid for swivel datas (Grinding), not for kinematic transformations!
    *
    *  Calculates the offset between beta and B
    *         and the offset beta at basic position
    *  Calculates the beta minimal and maximal values
    *  Here comes the information only from rotary axis 1
    */
   void calcTcBetaOffsetsAndMinMax (SlStepSwivelDataRecord& rTransfoData);

   /*! \fn void getTcToolDirectionBasicPosition (SlStepSwivelDataRecord& rTransfoData);
    *  \param rTransfoData               in/out: swivel datas
    *
    *  This function is valid for only toolcarrier
    *  Calculates the tool direction in basic position, for measuring kinematics complete (Turning Machine)
    */
   void getTcToolDirectionBasicPosition (SlStepSwivelDataRecord& rTransfoData);

   /*! \fn void getKtToolDirectionBasicPosition (SlStepSwivelDataRecord& rTransfoData);
    *  \param rTransfoData               out: swivel datas
    *
    *  This function is valid for only kinematic transformations
    *  Calculates the tool direction in basic position, for measuring kinematics complete (Turning Machine)
    */
   void getKtToolDirectionBasicPosition (SlStepSwivelDataRecord& rTransfoData);

   /*! \fn void calcKtAllDataAxisB (SlStepSwivelDataRecord& rTransfoData, int channelNumber);
    *  \param rTransfoData    in/out: current swivel datas
    *  \param channelNumber   in: current channel
    *
    *  Methode is for measuring kinematics complete (Turning Machine, only KT´s)
    *  Get the angle offset of the rotary axes.
    *  Calculates B min/max between the software limit switches
    *  Calculates the tool direction in basic position
    */
   void calcKtAllDataAxisB (SlStepSwivelDataRecord& rTransfoData, int channelNumber);

   /*! \fn void getRotAxOffsetsForTcChain (SlStepSwivelDataRecord& rSwivelDataRecord);
    *  \param rSwivelDataRecord     in: swivel datas
    *
    *  determine the X component offset length l3
    *  . . . . . the Z component offset length l3
    *  . . . . . the offset of the 1. Rotaryaxis in degree
    */
   void getRotAxOffsetsForTcChain (SlStepSwivelDataRecord& rSwivelDataRecord);

   /*! \fn void getKtAngleOffset (SlStepSwivelDataRecord& rSwivelDataRecord);
    *  \param rSwivelDataRecord     in: name of the rotary B axis
    *
    *  Methode is for measuring kinematics complete (Turning Machine, only KT´s)
    *  get the angle offset of the rotary axes
    */
   void getKtAngleOffset (SlStepSwivelDataRecord& rSwivelDataRecord);

   /*! \fn void saveRotaryAxisBMinMax(SlStepSwivelDataRecord& rTransfoData, int channelNumber)
    *  \param channelNumber              in: channel number
    *  \param rTransfoData               out: swivel datas
    *
    *  Saves the minimal and maximal values for rotary axis B
    */
   void saveRotaryAxisBMinMax(SlStepSwivelDataRecord& rTransfoData, int channelNumber);

   /*! \fn void saveDivisorAndOffsetOfHirthAxes(SlStepSwivelDataRecord& rTransfoData, int channelNumber)
    *  \param channelNumber              in: channel number
    *  \param rTransfoData               out: swivel datas
    *
    *  Saves the divisor and offset values for of hirth axes B and C (turning on milling machine, only KT)
    */
   void saveDivisorAndOffsetOfHirthAxes(SlStepSwivelDataRecord& rTransfoData, int channelNumber);

   /*! \fn QStringList getRotaryAxisNames(SlStepSwivelDataRecord swivelDataRecord);
    *  \param swivelDataRecord            in: swivel data record
    *  \return                           out: rotary axis name list
    *
    *  Gets the rotary axis name list of given swivel data record
    */
   QStringList getRotaryAxisNames(const SlStepSwivelDataRecord& rSwivelDataRecord) const;

   /*! \fn void convertMachineRotAxisToChannelRotAxis(const SlStepSwivelDataRecord& rKinematikDataRecord, int channelNumber);
    *  \param rKinematikDataRecord        in: swivel datas from kinematic chain
    *  \param channelNumber               in: channel number
    *
    *  convert the machine axes name of rotary axes to channel axes name.
    */
   void convertMachineRotAxisToChannelRotAxis(SlStepSwivelDataRecord& rKinematikDataRecord, int channelNumber);

   /*! \fn void getAllChannelsList (int *pChannelCount, QList<int> *pChannelNumberList) const;
    *  \param rChannelCount         out: swivel datas from kinematic chain
    *  \param rChannelNumberList    out: channel number
    *
    *  get a list of all channels
    */
   void getAllChannelsList (int *pChannelCount, QList<int> *pChannelNumberList) const;

   /*! \fn int whichSwivelIsEnable (int channelNumber) const;
    *  \param channelNumber         out: swivel datas from kinematic chain
    *
    *  returns, which swivel data source is available
    */
   int whichSwivelIsEnable (int channelNumber) const;


  // ---------------------------------------------------------------------------
  // Private Methoden für die Maske Zylindertransformation
  // ---------------------------------------------------------------------------

   /*! \fn void initListOfTracylAlternatveCallData (int channelNumber);
    *
    *  initilaise a list of TRACYL alternatve call data
    */
   void initListOfTracylAlternatveCallData (int channelNumber);

   /*! \fn void initListOfTraangAlternatveCallData (int channelNumber);
    *
    *  initilaise a list of TRAANG alternatve call data
    */
   void initListOfTraangAlternatveCallData (int channelNumber);

   /*! \fn SlStepTracylInfo::SlStepGeoAxisIndexEnum getAxisAroundRotaryAxis (double vector1, double vector2, double vector3);
    *  \param rotAxProperty          in: rotAxProperty
    *  \return             out: the axis rotates around which axis
    *
    *  returns The axis rotates around which axis
    */
   SlStepTracylInfo::SlStepGeoAxisIndexEnum getAxisAroundRotaryAxis (int rotAxProperty);

   /*! \fn bool isAltCallNumberDouble (SlStepTraCylAlternativeCallDataList validAlternativeDataList, int altCallNumber);
    *  \param validAlternativeDataList     in: list of all valid alternative data
    *  \param altCallNumber                in: alternative call number
    *  \return                            out: state, number has already been assigned
    *
    *  returns state, number has already been assigned
    */
   bool isAltCallNumberDouble (SlStepTraCylAlternativeCallDataList validAlternativeDataList, int altCallNumber);

   /*! \fn void getAlternativeTracylCallDatas (int channelNumber);
    *
    *  Get the general data for the alternative tracyl call from the NCK
    */
    void getAlternativeTracylCallDatas (int channelNumber);

   /*! \fn void getAlternativeTraangCallDatas (int channelNumber);
    *
    *  Get the general data for the alternative traang call from the NCK
    */
    void getAlternativeTraangCallDatas (int channelNumber);

   /*! \fn int getTrafoTyp (int alternativeCall);
    *  \param               in: general Data for alternative call
    *  \return             out: trafo type
    *
    *  returns the trafo type, trnasmit_k, traang_k, tracyl_k ...
    */
   int getTrafoTyp (int alternativeCall);

   /*! \fn int getAlternativeCallNumber (int alternativeCall);
    *  \param               in: general Data for alternative call
    *  \return             out: alternative call number
    *
    *  returns alternative call number
    */
   int getAlternativeCallNumber (int alternativeCall);

   /*! \fn int getChannelNumber (int alternativeCall);
    *  \param               in: general Data for alternative call
    *  \return             out: channel number
    *
    *  returns channel number
    */
   int getChannelNumber (int alternativeCall);

   /*! \fn SlStepTracylInfo::SlStepTracylTypeNumberEnum getTraCylTrafoType (int rotAxProperty)
   *  \param rotAxProperty          in: rotAxProperty
   *  \return                         : tracyl trafo type
   *
   *  retuns the TRACYL transformation type, 512, 513, 514
   */
   SlStepTracylInfo::SlStepTracylTypeNumberEnum getTraCylTrafoType (int rotAxProperty);

  /*! \fn SlStepAxesOrderEnum getPlaneForTraCyl (int rotAxProperty)
   *  \param rotAxProperty          in: rotary axix property
   *  \return                         : plane
   *
   *  retuns the plane, it´s determined from the axis order (x,y,z).
   */
   SlStepDirPlaneEnum getPlaneForTraCyl (int rotAxProperty);

  // ---------------------------------------------------------------------------
  // Private Methoden für den Inbetriebnahmedialog Schwenkdatensätze
  // ---------------------------------------------------------------------------

   /*! \fn void fillListWithAllSwivelsInfos (SlStepAllSwivelsInfo *pAllSwivels,
                                             const SwivelDataSetQList& rAllRecordData,
                                             int toUnitNumber) const;
    *  \param rAllSwivels         out: List of all swivel names and nubers
    *  \param rAllRecordData      in: all swivel names of TC or KT
    *  \param toUnitNumber        in: TO unit number
    *
    *  Fill the list with all existing swivel names and numbers
    */
   void fillListWithAllSwivelsInfos (SlStepAllSwivelsInfo *pAllSwivels,
                                     const SwivelDataSetQList& rAllRecordData,
                                     int toUnitNumber) const;

   /*! \fn bool isTcType (const QString& trafoType) const;
    *
    *  \param trafoType           in: List of all swivel names and nubers
    *  \return                   out: is a ToolCarrier
    *
    *  Return whether it is a ToolCarrier.
    */
   bool isTcType (const QString& trafoType) const;

   /*! \fn SlSwivelErrorEnum isChannelOfSwivelInfoInReset (const SlStepSwivelsInfo& rSwivelInfo);
    *
    *  \param rSwivelInfo    in: general information about the swivel data records list.
    *  \return              out: error state
    *
    *  Is the channel busy
    */
   SlSwivelErrorEnum isChannelOfSwivelInfoInReset (const SlStepSwivelsInfo& rSwivelInfo);

   /*! \fn bool isSwivelDataRecordEmpty (const SlStepSwivelsInfo& rSwivelInfo)
    *
    *  \param rSwivelInfo      in: general information about the swivel data records list.
    *  \return                out: empty state
    *
    *  get swivel data record
    */
   bool isSwivelDataRecordEmpty (const SlStepSwivelsInfo& rSwivelInfo);
 
   /*! \fn SlSwivelErrorEnum isDeleteSwivelDataRecordAllowed (const SlStepSwivelsInfo& rSwivelInfo);
    *
    *  \param rSwivelInfo      in: general information about the swivel data records list.
    *  \return                out: empty state
    *
    *  is delete swivel-data-record allowed
    */
   SlSwivelErrorEnum isDeleteSwivelDataRecordAllowed (const SlStepSwivelsInfo& rSwivelInfo);

   /*! \fn SlSwivelErrorEnum isCopySwivelDataRecordAllowed (const SlStepSwivelsInfo& rSwivelInfo);
    *
    *  \param rSwivelInfo      in: general information about the swivel data records list.
    *  \return                out: empty state
    *
    *  is copy swivel-data-record allowed
    */
   SlSwivelErrorEnum isCopySwivelDataRecordAllowed (const SlStepSwivelsInfo& rSwivelInfo);

   /*! \fn SlSwivelErrorEnum isPasteSwivelDataRecordAllowed (const SlStepSwivelsInfo& rSwivelInfo, const QString& newName, bool bCheckName)
    *
    *  \param rSwivelInfo      in: general information about the swivel data records list.
    *  \param newName          in: Name of the swivel data record, where the new will be paste
    *  \param bCheckName       in: enable or disable the test for duplicate names, enabled by default
    *  \return                out: empty state
    *
    *  is paste swivel-data-record allowed
    */
   SlSwivelErrorEnum isPasteSwivelDataRecordAllowed (const SlStepSwivelsInfo& rSwivelInfo, const QString& newName, bool bCheckName = true);

   /*! \fn SlSwivelErrorEnum isNewSwivelDataRecordAllowed (const SlStepSwivelsInfo& rSwivelInfo);
    *
    *  \param rSwivelInfo      in: general information about the swivel data records list.
    *  \return                out: empty state
    *
    *  is create a new swivel-data-record allowed
    */
   SlSwivelErrorEnum isNewSwivelDataRecordAllowed (const SlStepSwivelsInfo& rSwivelInfo);

   /*! \fn SlSwivelErrorEnum isAcceptSwivelDataRecordAllowed (const SlStepSwivelsInfo& rSwivelInfo);
    *
    *  \param rSwivelInfo      in: general information about the swivel data records list.
    *  \return                out: empty state
    *
    *  is the acceptance of the swivel-data-record allowed
    */
   SlSwivelErrorEnum isAcceptSwivelDataRecordAllowed (const SlStepSwivelsInfo& rSwivelInfo);

  // ---------------------------------------------------------------------------
  // PRIVATE OF PSEUDO SLOTS CALLED BY CALL BACK OBJECT
  // ---------------------------------------------------------------------------

  /*! \fn void connectToLogic(void)
   *
   *  Establishes the connection from machine logic object to callback object
   */
   void connectToLogic(void);

  /*! \fn void disconnectFromLogic(void)
   *
   *  Releases the connections to the machine logic object.
   */
   void disconnectFromLogic(void);

}; // <-- class SlStepSwivelData


/*! \class SlStepSwivelDataSingleton
 *
 *  This implements the singleton pattern for class \sa SlStepSwivelData
 */
class SL_STEP_LOGIC_EXPORT SlStepSwivelDataSingleton
{
public:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC ACCESSORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn static SlStepSwivelData& exemplar()
    *
    *  \return Returns a reference to the one and only exemplar 
    *          of SlStepSwivelData.
    */
   static SlStepSwivelData& exemplar()
   {
      return m_s_exemplar;
   }

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBER
   ///////////////////////////////////////////////////////////////////////////

   static SlStepSwivelData m_s_exemplar;     //!< storage for the exemplar


   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE OPERATORS TO PREVENT ACCESS
   ///////////////////////////////////////////////////////////////////////////

   /*! constructor is not allowed for singletons */
   SlStepSwivelDataSingleton ();

   /*! destructor is not allowed for singletons */
   ~SlStepSwivelDataSingleton ();

   /*! assignment operator not allowed */
   SlStepSwivelDataSingleton& operator=(SlStepSwivelDataSingleton&);

   /*! copy constructor not allowed */
   SlStepSwivelDataSingleton(const SlStepSwivelDataSingleton&);

}; // <-- class SlStepSwivelDataSingleton


/*! \class SlStepSwivelDataCallBack
 *
 *  This implements is used for handle slot/signal applications
 */
class SlStepSwivelDataCallBack : public QObject
{
   Q_OBJECT;

public:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC CREATORS
   ///////////////////////////////////////////////////////////////////////////

   SlStepSwivelDataCallBack (SlStepSwivelData* pSwivelData,
                             QObject* pParent = 0);

   virtual ~SlStepSwivelDataCallBack ();

public slots:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC SLOTS
   ///////////////////////////////////////////////////////////////////////////

  /*! \fn void setActiveChanSlot(const QString& rsChan);
   *  \param rsChan  in: channel number
   *
   *   Die Klasse SlStepSwivelData kann keine Slot oder Signals behandeln.
   *   Darum gibt diser Slot das Signal Kanalumschaltung weiter.
   */
   void setActiveChanSlot(const QString& rsChan);

  /*! \fn void setActiveChanSlot(const QString& rsChan);
   *  \param rsChan  in: channel number
   *
   *   Die Klasse SlStepSwivelData kann keine Slot oder Signals behandeln.
   *   Darum gibt diser Slot das Signal Power On Reset weiter.
   */
   void setConnectStateSlot(SlMaConnectStateEnum state);

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   SlStepSwivelData*    m_pSwivelData;    //!< creating swivel data object
}; // <-- class SlStepSwivelDataCallBack

#endif // SL_STEP_SWIVEL_DATA_RECORD_H
