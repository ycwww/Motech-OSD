///////////////////////////////////////////////////////////////////////////////
/*! \file   slmajogmelogic.h
 *  \author Erik Jezernik
 *  \date   22.06.2007
 *  \brief  Definition file for class SlStepMeJogLogic
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_JOG_ME_LOGIC_H
#define SL_MA_JOG_ME_LOGIC_H

// solutionline
#include "slmaformlogicbase.h" 
#include "slsteplogicexports.h"
#include "slpaworkoffsetdetails.h"
#include "slstepglobal.h"
#include "slstepmeconfigfunctions.h"

// Parameter for NCK-function $AC_MEAS_TOOL_MASK
const unsigned int SL_MEAS_TOOL_DIR_X              = 0x002;   // toollocation X-direction
const unsigned int SL_MEAS_TOOL_DIR_Y              = 0x004;   // toollocation Y-direction
const unsigned int SL_MEAS_TOOL_DIR_Z              = 0x008;   // toollocation Z-direction
const unsigned int SL_MEAS_TOOL_DIR_X_LOC_2        = 0x040;   // toollocation - X-direction
const unsigned int SL_MEAS_TOOL_DIR_Y_LOC_2        = 0x080;   // toollocation - Y-direction
const unsigned int SL_MEAS_TOOL_DIR_Z_LOC_2        = 0x100;   // toollocation - Z-direction 
const unsigned int SL_MEAS_TOOL_DIR_DIF_CALC       = 0x200;   // toollength-differences will be negative added
const unsigned int SL_MEAS_TOOL_CALC_IN_FANUC_MODE = 0x010;   // on tool-length in ISO-mode


// Plane Parameter for acMeasActPlane
const unsigned int SL_MEAS_PLANE_G17 = 0;
const unsigned int SL_MEAS_PLANE_G18 = 1;
const unsigned int SL_MEAS_PLANE_G19 = 2;

// axis offsets
const unsigned int SL_MEAS_X_AXES = 1;   // Offset for X-Achse
const unsigned int SL_MEAS_Y_AXES = 2;   // Offset for Y-Achse
const unsigned int SL_MEAS_Z_AXES = 3;   // Offset for Z-Achse

// meaning from meas_type
// The mumber was so choosen, that she was identical to NC-delivery $AC_MEAS_TYPE
const unsigned int SL_MEAS_CAL_NPV_TYPE_1  = 1;    // Kante einrichten
const unsigned int SL_MEAS_CAL_NPV_TYPE_4  = 4;    // Ecke 1
const unsigned int SL_MEAS_CAL_NPV_TYPE_5  = 5;    // Ecke 2
const unsigned int SL_MEAS_CAL_NPV_TYPE_6  = 6;    // Ecke 3
const unsigned int SL_MEAS_CAL_NPV_TYPE_7  = 7;    // Ecke 4
const unsigned int SL_MEAS_CAL_NPV_TYPE_8  = 8;    // eine Bohrung
const unsigned int SL_MEAS_CAL_NPV_TYPE_9  = 9;    // ein Kreiszapfen
const unsigned int SL_MEAS_CAL_NPV_TYPE_12 = 12;   // Abstand 2 Kanten (Nut)
const unsigned int SL_MEAS_CAL_NPV_TYPE_13 = 13;   // Abstand 2 Kanten (Steg)
const unsigned int SL_MEAS_CAL_NPV_TYPE_16 = 16;   // Kante ausrichten
const unsigned int SL_MEAS_CAL_NPV_TYPE_17 = 17;   // Ebene einrichten
const unsigned int SL_MEAS_CAL_NPV_TYPE_25 = 25;   // Rechtecktasche/Rechteckzapfen

// Partameters for cyle E_MS_CAN
const unsigned int SL_MEAS_BASIS_E_MS_CAN     = 2000;
const unsigned int SL_MEAS_ONLY_MEAS_E_MS_CAN =  100;

// Partameters for cyle CYC_JMA variable swap: mark, for the location from the corner
const unsigned int SL_MEAS_EDGE_1 = 1;
const unsigned int SL_MEAS_EDGE_2 = 2;
const unsigned int SL_MEAS_EDGE_3 = 3;
const unsigned int SL_MEAS_EDGE_4 = 4;

// direction
const unsigned int SL_MEAS_PLUS = 0;
const unsigned int SL_MEAS_MINUS = 1;

// Define for no Input
const double SL_MEAS_NO_VALUE = (1.797693E+308)/2;

 // enum defining for SlMaCoordinateSystemEnum*/
enum SlMeasCoordinateSystemEnum
{
   SL_MEAS_WKS = 0, /*!< Work coordinate system*/
   SL_MEAS_BKS = 1,
   SL_MEAS_MKS = 2, /*!< Machine coordinate system*/
   SL_MEAS_ENS = 3,
   SL_MEAS_WKS_REL = 4,
   SL_MEAS_ENS_REL = 5,
};

// enum for meas direction acMeasDirApproach
enum SlMeasDirApproach
{
   SL_MEAS_APPROACH_AX1_PLUS = 0, // X plus
   SL_MEAS_APPROACH_AX1_MINUS,    // X minus
   SL_MEAS_APPROACH_AX2_PLUS,     // Y plus
   SL_MEAS_APPROACH_AX2_MINUS,    // Y minus
   SL_MEAS_APPROACH_AX3_PLUS,     // Z plus
   SL_MEAS_APPROACH_AX3_MINUS,    // Z minus
};

/*!  \enum  SlMeasResultsEnum
 *   This is the enum for the structure SlMeasResults
 */
enum SlMeasResultsEnum
{
   SL_MEAS_RESULT_OVR4,
   SL_MEAS_RESULT_OVR5,
   SL_MEAS_RESULT_OVR6,
   SL_MEAS_RESULT_OVR7,
   SL_MEAS_RESULT_NUM,
};

/*!  \enum  SlMeasResultErrorsEnum
 *   Fehlercodes die beim Messen durch die NC zurueckgegeben werden koennen
 */
enum SlMeasResultErrorsEnum
{
   SL_MEAS_OK               =    0,  // Korrekte Berechnung
   SL_MEAS_NO_TYPE          = 0x61,  // Type nicht spezifiziert
   SL_MEAS_TOOL_ERROR       = 0x62,  // Fehler bei der Tool Ermittlung
   SL_MEAS_NO_POINT_1       = 0x63,  // Messpunkt 1 nicht vorhanden
   SL_MEAS_NO_POINT_2       = 0x64,  // Messpunkt 2 nicht vorhanden
   SL_MEAS_NO_POINT_3       = 0x65,  // Messpunkt 3 nicht vorhanden
   SL_MEAS_NO_POINT_4       = 0x66,  // Messpunkt 4 nicht vorhanden
   SL_MEAS_NO_SECPOINT      = 0x67,  // Kein Referenzpunkt vorhanden
   SL_MEAS_NO_DIR           = 0x68,  // Keine Anfahrrichtung vorhanden
   SL_MEAS_EQUAL_MEASPOINTS = 0x69,  // Messpunkte sind identisch
   SL_MEAS_WRONG_ALPHA      = 0x70,  // Alpha ist falsch
   SL_MEAS_WRONG_PHI        = 0x71,  // Phi ist falsch
   SL_MEAS_WRONG_DIR        = 0x72,  // Falsche Anfahrrichtung
   SL_MEAS_NO_CROSSING      = 0x73,  // Geraden schneiden sich nicht
   SL_MEAS_NO_PLANE         = 0x74,  // Ebene nicht vorhanden
   SL_MEAS_WRONG_FRAME      = 0x75,  // Kein oder falsches Frame selektiert
   SL_MEAS_NO_MEMORY        = 0x76,  // Nicht genügend Speicher vorhanden
   SL_MEAS_INTERNAL_ERROR   = 0x77,  // Interner Fehler
};

/*!  \enum  SlMeasPopupEnum
 *   Popups, die beim Messen angezeigt werden können.
 *   Enum dient zum Merken des "angezeigten" und "bearbeiteten" popups.
 */
enum SlMeasPopupEnum
{
   SL_MEAS_POPUP_NO  = 0,                    // kein Popup
   SL_MEAS_POPUP_FRAME_ACTIVATION,           // Popup zum Aktivieren einer Nullpunktverschiebung (Frame)
   SL_MEAS_POPUP_ROTARY_AXIS_ADJUSTMENT,     // Popup zum Ausrichten einer Rundachse
   SL_MEAS_POPUP_PROBE_TO_PLAIN_ADJUSTMENT   // Popup zum senkrechtstellen eines Messtasters in der Ebene
};

/*!
 *  \enum SlMeasWorkOffsetEnum
 *
 *  Defines work offset selectors
 */
enum SlMeasWorkOffsetEnum
{
   SL_MEAS_WORK_OFFSET_ACTIVE      = 0, //!< Selector of the active work offset (active during measurement)
   SL_MEAS_WORK_OFFSET_DESTINATION = 1  //!< Selector of destination work offset (where measure result goes to)
};

/*!  \enum  SlMeasAsupModeEnum
 *   This is the enum for the structure SlMeasAsupModeEnum
 */
enum SlMeasAsupModeEnum
{
   SL_ASUP_MODE_OFF,                   //!< asup mode is off; gcode generation by nc-start only.
   SL_ASUP_MODE_MEASURE_PROTOCOL,      //!< generates cycle call to protocol the last measurement
   SL_ASUP_MODE_CYCLE401,              //!< generates cycle call to calculate tool length by cycle401 (against dresser tool) 
   SL_ASUP_MODE_MIRROR_X,              //!< generates cycle call to turn on/off mirror of x axis in dependency to used tool carrier
   SL_ASUP_MODE_CALC_B_AXIS,           //!< generates cycle call to calculate b axis length (circular grinding) 
   SL_ASUP_MODE_MEASPOINT_P1, //!< generates cycle130 call to store meas point P1
   SL_ASUP_MODE_MEASPOINT_P2, //!< generates cycle130 call to store meas point P2
   SL_ASUP_MODE_MEASPOINT_P3, //!< generates cycle130 call to store meas point P3
   SL_ASUP_MODE_MEASPOINT_P4, //!< generates cycle130 call to store meas point P4
   SL_ASUP_MODE_CALCULATED_MEASPOINT,   //!< generates cycle call calculated meas point
};

enum SlStepMeasCalDirectionEnum
{
   MEAS_DIR_MINUS  = 0x1,     //!< calibrated in minus direction
   MEAS_DIR_PLUS   = 0x2      //!< calibrated in plus direction
};
Q_DECLARE_FLAGS(SlStepMeasCalDirectionEnums, SlStepMeasCalDirectionEnum)

enum SlStepMeasCalStatusEnum
{
   MEAS_CAL_FIRST_AXIS           = 0x1,                           //!< first axis was calibrated in the plane
   MEAS_CAL_SECOND_AXIS          = 0x2,                           //!< second axis was calibrated in the plane
   MEAS_CAL_INFEED_AXIS_TL       = 0x4,                           //!< tool length was calibrated in infeed axis and written to tool list
   MEAS_CAL_INFEED_AXIS_TL_DIFF  = 0x8,                           //!< tool length difference was determined during calibration and written to calibration data
   MEAS_CAL_INFEED_AXIS          = MEAS_CAL_INFEED_AXIS_TL 
                                 | MEAS_CAL_INFEED_AXIS_TL_DIFF   //!< infeed axis was calibrated
};
Q_DECLARE_FLAGS(SlStepMeasCalStatusEnums, SlStepMeasCalStatusEnum)

enum SlStepMeasCalValuesEnum
{
   MEAS_CAL_AXIS1_PLUS  = 1,                           
   MEAS_CAL_AXIS1_MINUS = 2,                
   MEAS_CAL_AXIS2_PLUS  = 3,                           
   MEAS_CAL_AXIS2_MINUS = 4,                        
   MEAS_CAL_AXIS3_PLUS  = 5,
   MEAS_CAL_AXIS3_MINUS = 6,
   MEAS_CAL_DIAM        = 7,
   MEAS_CAL_DELTA_AXIS1 = 8,
   MEAS_CAL_DELTA_AXIS2 = 9
};

/*!
 *  \struct SlMeasPoint
 *
 *  This structure declares a meas point
 */
struct SlMeasPoint
{
   /*!
    *  \fn SlMeasPoint()
    *
    *  Default constructor.
    */
   SlMeasPoint()
      : e_mess_0(SL_MEAS_NO_VALUE),
        e_mess_1(SL_MEAS_NO_VALUE),
        e_mess_2(SL_MEAS_NO_VALUE)
   {};

   /*!
    *  \fn SlMeasPoint()
    *
    *  Default constructor.
    */
   SlMeasPoint(double mess_0, double mess_1, double mess_2)
      : e_mess_0(mess_0),
        e_mess_1(mess_1),
        e_mess_2(mess_2)
   {};

   double e_mess_0;     //!< stored value of E_MESS[0]
   double e_mess_1;     //!< stored value of E_MESS[1]
   double e_mess_2;     //!< stored value of E_MESS[2]

   /*!
    *  \fn bool isStored (void) const
    *
    *  \return Returns true if the meas point is stored; 
               otherwise it returns false.
    */
   bool isStored (void) const
   {
      return (SL_MEAS_NO_VALUE != e_mess_0
              || SL_MEAS_NO_VALUE != e_mess_1
              || SL_MEAS_NO_VALUE != e_mess_2);
   }
};

/*!
 *  \typedef QVector<SlMeasPoint> SlMeasPointVector
 *
 *  This defines a vector of meas points for manual or automaticaly measure
 */
typedef QVector<SlMeasPoint> SlMeasPointVector;

/*!
 *  \typedef QVector<bool> SlMeasPointManVector
 *
 *  This defines a vector of flags for stored meas points for manually meause
 */
typedef QVector<bool> SlMeasPointManVector;

/*!
 *  \typedef QVector<double> SlMeasResults
 *
 *  This defines a vector of results
 */
typedef QVector<double> SlMeasResults;

/*!
 *  \typedef QVector<unsigned int> SlMeasAxisUsageAttrib
 *
 *  This defines a vector for the MD52207
 */
typedef QVector<unsigned int> SlMeasAxisUsageAttrib;

/*!
 *  \typedef QVector<unsigned int> SlMeasAxisUsage
 *
 *  This defines a vector for the MD52206
 */
typedef QVector<unsigned int> SlMeasAxisUsage;

/*!
 *  \typedef QVector<unsigned int> SlMeasCalibRingDiameter
 *
 *  This defines a vector to cache calibration ring diameters for the workpiece probe
 *  (51770[n] $MNS_J_MEA_CAL_RING_DIAM).
 *  The workpiece-tracer index is the vector index (so zero based).
 */
typedef QVector<double> SlMeasCalibRingDiameter;

/*!
 *  \typedef QVector<unsigned int> SlMeasCalibHeight
 *
 *  This defines a vector to cache calibration heights for the workpiece probe
 *  (51772[n] $MNS_J_MEA_CAL_RING_DIAM).
 *  The workpiece-tracer index is the vector index (so zero based).
 */
typedef QVector<double> SlMeasCalibHeight;

/*!
 *  \struct SlMeasParams
 *
 *  Defines a structure that holds all parameters needed for
 *  measurement.
 */
struct SlMeasParams
{
   SlMeasParams()
      : iMeasDirection(SL_STEP_MEAS_DIR_TOGGLE_NO_DIR),
        iMeasDirectionP2(0),
        bLengthDiam(false),
        bXInput(false),
        uiMeasAxis(0),
        iCoverAxis(-1),
        uiEqualize(0),              // _ST
        uiSingleEdgeMeasToggle(0),  // _ST
        uiSpindleReversal(0),       // _ST
        dGeoax1_0(0.0),
        dGeoax2_0(0.0),
        dGeoax3_0(0.0),
        dDebitAngle(0.0),
        dProbeAngle(0.0),
        dDiam(0.0),
        dDepth(0.0),
        dDelta(0.0),
        dLength(0.0),
        dWidth(0.0),
        dFixPointDistance(0.0),
        uiLocationMeas(0),
        uiAngleCorrection(0),
        uiDirCorner(0),
        uiMeasNpv(0),
        uiNum3dTracer(0),
        uiActiveNpv(0),
        uiNpvOnlyMeas(0),
        uiGlobBasis(0),
        uiChannelBasis(0),
        uiP(0),
        uiActiveP(0),
        uiMeasToolScratch(0),
        uiDToggle(0),
        uiDpToggle(0),
        sTool(QString::null),
        bAdjustRotAxis_DoAdjustment(false),
        dAdjustRotAxis_Feed(0.0),
        bAdjustRotAxis_FeedRapid(false),
        bAdjustProbeToPlane_DoAdjustment(false),
        uiAdjustProbeToPlane_Retraction(0),
        dAdjustProbeToPlane_RetractionVal(0.0),
        uiAdjustSwivelDir(0),
        uiAdjustTrackingTool(0),
        bSavedMeasPos(false),
        dMeasFeed(-1.0),
        nTurnToolHolder(SL_STEP_MEAS_TURN_TOOL_HOLDER_1),
        uiMeasMethod(0),
        uiToolDeltaToggle(0),
        uiToolDeltaAxisToggle(0),
        sTool2(QString::null),
        uiDToggle2(0),
        dBeta1(0.0),
        dBeta2(0.0),
        bCalGeoAx3(false),
        bMeasureLength(false)
   {}
   int iMeasDirection;
   int iMeasDirectionP2;
   bool bLengthDiam;
   bool bXInput;
   unsigned int uiMeasAxis;
   int iCoverAxis;
   unsigned int uiEqualize;               // _ST
   unsigned int uiSingleEdgeMeasToggle;   // _ST
   unsigned int uiSpindleReversal;        // _ST
   double dGeoax1_0;
   double dGeoax2_0;
   double dGeoax3_0;
   double dDebitAngle;
   double dProbeAngle;
   double dDiam;
   double dDepth;
   double dDelta;
   double dLength;
   double dWidth;
   double dFixPointDistance;
   unsigned int uiLocationMeas;
   unsigned int uiAngleCorrection;
   unsigned int uiDirCorner;
   unsigned int uiMeasNpv;
   unsigned int uiNum3dTracer;
   unsigned int uiActiveNpv;
   unsigned int uiNpvOnlyMeas;
   unsigned int uiGlobBasis;
   unsigned int uiChannelBasis;
   unsigned int uiP;
   unsigned int uiActiveP;
   unsigned int uiMeasToolScratch;
   unsigned int uiDToggle;
   unsigned int uiDpToggle;
   QString sTool;
   bool bAdjustRotAxis_DoAdjustment;
   double dAdjustRotAxis_Feed;
   bool bAdjustRotAxis_FeedRapid;
   bool bAdjustProbeToPlane_DoAdjustment;
   unsigned int uiAdjustProbeToPlane_Retraction;
   double dAdjustProbeToPlane_RetractionVal;
   unsigned int uiAdjustSwivelDir;
   unsigned int uiAdjustTrackingTool;
   bool bSavedMeasPos;
   double dMeasFeed;
   int nTurnToolHolder;
   unsigned int uiMeasMethod;
   QString sBetaGammaCycle;
   unsigned int uiToolDeltaToggle;
   unsigned int uiToolDeltaAxisToggle;
   QString sTool2;
   unsigned int uiDToggle2;
   double dBeta1;
   double dBeta2;
   bool bCalGeoAx3;
   bool bMeasureLength;
}; 


/*!
 *  \struct SlMeasValues
 *
 *  Defines a structure that holds all values resulting by measurement.
 */
struct SlMeasValues
{
   SlMeasValues()
      : geoax1_0_meas_res(SL_MEAS_NO_VALUE),
        geoax2_0_meas_res(SL_MEAS_NO_VALUE),
        geoax3_0_meas_res(SL_MEAS_NO_VALUE),
        alpha_meas_res(SL_MEAS_NO_VALUE),
        beta_meas_res(SL_MEAS_NO_VALUE),
        diam_meas_res(SL_MEAS_NO_VALUE),
        length_meas_res(SL_MEAS_NO_VALUE),
        width_meas_res(SL_MEAS_NO_VALUE)
   {}

   double geoax1_0_meas_res;
   double geoax2_0_meas_res;
   double geoax3_0_meas_res;
   double alpha_meas_res;
   double beta_meas_res;
   double diam_meas_res;
   double length_meas_res;
   double width_meas_res;
}; // <-- struct SlMeasParams

class SlStepMeJogLogicPrivate;

/*!
 *  \class SlMeasTargetNpvData
 *
 *  \brief Defines an array with number and refresh status for meas softkeys
 */
class SlMeasTargetNpvData
{
public:

   SlMeasTargetNpvData()
   {
   };

   void init()
   {
      m_saveTargetNpvAxisValueList.clear();
      m_saveTargetNpvAxisRotList.clear();
      m_saveTargetNpvAxisScalList.clear();
      m_saveTargetNpvAxisMirrorList.clear();
   }


   QList<double> m_saveTargetNpvAxisValueList;
   QList<double> m_saveTargetNpvAxisRotList;
   QList<double> m_saveTargetNpvAxisScalList;
   QList<bool>   m_saveTargetNpvAxisMirrorList;


}; // <-- class SlMeasTargetNpvData


/*! \class  SlStepMeJogLogic
 *  \brief  Interface service adapter of mashine jog start
 */
class SL_STEP_LOGIC_EXPORT SlStepMeJogLogic : public SlMaFormLogicBase
{
  Q_OBJECT
  Q_ENUMS(SlCapErrorEnum)
             
public:

  ///////////////////////////////////////////////////////////////////////////
  // ENUMS AND TYPE DEFINITIONS
  ///////////////////////////////////////////////////////////////////////////

  enum CapLinks
  {
     E_OPMODE,
     E_NUM_ELEMENTS,
  };


  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  
  /*! \fn SlStepMeJogLogic (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlStepMeJogLogic (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlStepMeJogLogic ();
   *
   *  destructor
  */
  virtual ~SlStepMeJogLogic ();


  ///////////////////////////////////////////////////////////////////////////////
  // PUBLIC CONFIGURATION METHODS
  ///////////////////////////////////////////////////////////////////////////////

  /*!
   *  \fn void setMeasType (unsigned int nMeasType)
   *
   *  \param nMeasType    number of the meas type
   *
   *  Sets the measure type. \sa SlMaJogMeasMasksToggleEnum.
   */
  void setMeasType (unsigned int nMeasType);

  /*!
   *  \fn unsigned int  getMeasType () const
   *
   *  Returns the measure type
   */
  unsigned int  getMeasType () const;

  /*!
   *  \fn void setSoftkeysForMeasType ()
   *
   *  Sets the softkeys for the measure type.
   */
  void setSoftkeysForMeasType ();

  /*!
   *  \fn int getNumberOfSoftkeys ()
   *
   *
   *  Returns the number of the softkeys
   */
  int getNumberOfSoftkeys () const;

  /*!
   *  \fn bool measTypeEdgeSetUp ()
   *
   *  Returns true if the meas type is SL_MA_JOG_MEAS_MASKS_TOGGLE_EDGE_SET_UP
   */
  bool measTypeEdgeSetUp ();

  /*!
   *  \fn unsigned bool measTypeNeedsSkRowRefresh () const;
   *
   *  Returns 'true' if active measure type need to refresh its vertical softkeys row,
   *  else 'false'.
   */
  bool measTypeNeedsSkRowRefresh () const;

  /*!
   *  \fn bool measTypeHasNpvSoftkey () const
   *
   *  Returns 'true' if active measure type has a "Set NPV" softkey, else 'false'
   */
  bool measTypeHasNpvSoftkey () const;

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  
  /*!
   *  \fn bool isIsoMode (void) const;
   *
   *  Returns true if ISO mode is active in nc; otherwise it returns false.
   */
  bool isIsoMode (void) const;

  /*!
   *  \fn bool isIsoMode (void) const;
   *
   *  Returns true if tool measurement with magnifying glass is enabled,
   *  else false.
   */
  bool isMagnifyingGlassEnabled (void) const;

  /*!
   *  \fn bool enlargeFunctions (void) const;
   *
    *  \Returns list of geometry axes names
   */
  QStringList geoAxisNameList(void) const;

  /*!
   *  \fn bool enlargeFunctions (void) const;
   *
   *  Returns true if the enlarge functions are enabled
   */
  bool enlargeFunctions (void) const;

  /*!
   *  \fn bool isAutoMeas (void) const;
   *
   *  Returns true if meassuring is done automaticaly with 3d tracer; 
   *  otherwise it returns false.
   */
  bool isAutoMeas (void) const;

  /*!
   *  \fn bool isAutoMeasBypassing (void) const;
   *
   *  Nur temporaerer Ersatz fuer die obige Funktion, bis NCK korrekt funktioniert
   */
  bool isAutoMeasBypassing (void) const;

  /*!
   *  \fn bool isToolAutoMeas (void) const;
   *
   *  Returns true if tool meassuring is done automatically; 
   *  otherwise it returns false.
   */
  bool isToolAutoMeas (void) const;

  /*!
   *  \fn bool millingToolIsActive (void) const;
   *
   *  Returns true if a milling tool is active
   *  otherwise it returns false.
   */
  bool millingToolIsActive (void) const;

  /*!
   *  \fn bool turningToolIsActive (void) const;
   *
   *  Returns true if a turning tool is active
   *  otherwise it returns false.
   */
  bool turningToolIsActive (void) const;

  /*!
   *  \fn bool tracingToolIsActive (void) const;
   *
   *  Returns true if a tracing tool is active
   *  otherwise it returns false.
   */
  bool tracingToolIsActive (void) const;

  /*!
   *  \fn bool facingToolIsActive (void) const;
   *
   *  Returns true if a facing tool is active
   *  otherwise it returns false.
   */
  bool facingToolIsActive (void) const;

  /*!
   *  \fn bool turningToolForCalibrationIsActive (void) const;
   *
   *  Returns true if a turning calibration tool is active
   *  otherwise it returns false.
   */
  bool turningToolForCalibrationIsActive (void) const;

  /*!
   *  \fn double actCuttingEdgePositionMod (void) const
   *
   *  Returns the cutting edge position of active tool, under the consideration of beta/gamma rotation.
   */
  double actCuttingEdgePositionMod (void) const;


  /*!
   *  \fn bool enableNum3dTracer (void) const;
   *
   *  Returns true if 3D tracer is enabled
   */
  bool enableNum3dTracer (void) const;

  /*!
   *  \fn bool enabledNum3dTracerTool (void) const;
   *
   *  Liefert 'true' wenn Kalibrierdatenfelder für Werkzeugmesstaster aktiviert sind.
   */
  bool enabledNum3dTracerTool (void) const;

  /*!
   *  \fn bool enableMeasTypeBasis (void) const;
   *
   *  Returns true if Basis is enabled
   */
  bool enableMeasTypeBasis (void) const;

  /*!
   *  \fn bool enableMeasTypeChanBasis (void) const;
   *
   *  Returns true if channel Basis is enabled
   */
  bool enableMeasTypeChanBasis (void) const;

  /*!
   *  \fn bool enableMeasTypeGlobBasis (void) const;
   *
   *  Returns true if global Basis is enabled
   */
  bool enableMeasTypeGlobBasis (void) const;

  /*!
   *  \fn bool enableAutoMeasTool (void) const;
   *
   *  Returns true meas tool auto is enable
   */
  bool enableAutoMeasTool (void) const;

  /*!
   *  \fn bool enableAutoMeas (void) const;
   *
   *  Returns true meas auto is enable
   */
  bool enableAutoMeas (void) const;

  /*!
   *  \fn bool enableMeasTypeAdjustable (void) const;
   *
   *  Returns true, if adjustable npvs are enable
   */
  bool enableMeasTypeAdjustable (void) const;

  /*!
   *  \fn bool enableMeasMethod (void) const;
   *
   *  Returns true, if measurement method are enable
   */
  bool enableMeasMethod (void) const;

  /*!
   *  \fn SlMaAccessLevelEnum calibTurnToolTracerAccLevel() const
   *
   *  Returns the access level required to calibrate the turn tool tracer.
   */
  SlMaAccessLevelEnum calibTurnToolTracerAccLevel() const;

  /*!
   *  \fn bool measIntoSetFrameEnabled() const
   *
   *  Returns true if measuring into the setframe (dt. Basisbezug) is enabled,
   *  else false.
   */
  bool measIntoSetFrameEnabled() const;

  /*!
   *  \fn int meaCalWpNum (void) const;
   *
   *  Returns the number of 3D-tracer
   */
  int meaCalWpNum (void) const;

  /*!
   *  \fn int meaCalTpNum (void) const;
   *
   *  Returns the number of calibration data fields for tool probes.
   */
  int meaCalTpNum (void) const;

  /*!
   *  \fn unsigned int numBasisFramesChan (void) const;
   *
   *  Returns the number of channel basis frames
   */
  unsigned int numBasisFramesChan (void) const;

  /*!
   *  \fn unsigned int numBasisFramesGlob (void) const;
   *
   *  Returns the number of global basis frames
   */
  unsigned int numBasisFramesGlob (void) const;

  /*!
   *  \fn unsigned int actToolType (void) const;
   *
   *  Returns act tool type
   */
  unsigned int actToolType (void) const;

  /*!
   *  \fn void setFreezeActToolType (bool bFreeze)
   *
   *  Setzt ein Lock/Unlock auf die Funktion actToolType (void). 
   *  Wird die Funktion actToolType() gelockt, liefert sie den actToolType 
   *  der zum Zeitpunkt des locken aktiv war. Ist der Lock aufgehoben liefert
   *  die Funktion actToolType() den aktuellen Status der Werkzeuglogik.
   */
  void setFreezeActToolType (bool bFreeze);

  /*!
   *  \fn bool workPlaneEnable (void) const
   *
   *  Returns true if the work plane is enable
   */
  bool workPlaneEnable (void) const;

  /*!
   *  \fn bool activeNpvEnable (void) const
   *
   *  Returns true if the active npv is enable
   */
  bool activeNpvEnable (void) const;

  /*!
   *  \fn QString actToolIdent () const
   *
   *  Returns the tool name from the active tool
   */
  QString actToolIdent () const;

  /*!
   *  \fn uint actDNumber () const
   *
   *  Returns the d-number name from the active tool
   */
  uint actDNumber () const;

  /*!
   *  \fn double actDuploNumber () const
   *
   *  Returns the duplo-number name from the active tool
   */
  double actDuploNumber () const;

  /*!
   *  \fn QVector<int> listOfRotationAxisInWorkPlane() const
   *
   *  Returns the list of rotation axis in work plane for the Angle offset toggler in
   *  the masks Align Edge, 2 Holes and 2 Circ. Spigots.
   *  The axes identifiers are channel axis indexes.
   */
  QVector<int> listOfRotationAxisInWorkPlane() const;

  /*!
   *  \fn unsigned int technology () const
   *
   *  Returns the technology
   */
  unsigned int technology () const;

  /*!
   *  \fn unsigned int technologyExtension () const
   *
   *  Returns the technologyExtension
   */
  unsigned int technologyExtension () const;

  /*!
   *  \fn int progState () const
   *
   *  Returns the programma state
   */
  int progState () const;

  /*!
   *  \fn int chanState () const
   *
   *  Returns the channel state
   */
  int chanState () const;

  /*!
   *  \fn double checkAllMeasPointsAreSet () const
   *
   *  Returns the true, when all meas points are set
   */
  bool checkAllMeasPointsAreSet () const;

  /*!
   *  \fn long storeMeasPointMan (unsigned int nIndex, SlMeasParams* pParams)
   *
   *  \param nIndex  index of meas point to store
   *  \param pParams parameters needed for measurement
   *
   *  \return If were successfull it returns 0; 
              otherwise it returns an error code
   *
   *  This stores a meas point at given index, \a nIndex.
   */
  long storeMeasPointMan (unsigned int nIndex, SlMeasParams* pParams);

  /*!
   *  \fn long storeSkMeasPointMan (unsigned int nIndex, SlMeasParams* pParams)
   *
   *  \param nIndex  index of meas point to store
   *
   *  Stores softkey highlight-information of a "save measpoint" softkey at given index, \a nIndex.
   */
  void storeSkMeasPointMan (unsigned int nIndex);

  /*!
   *  \fn long storeMeasPointEndPoint (SlMeasValues* pValues, bool& rMeasIsReady)
   *
   *  \param pValues    values returned by measurement
   *  \param rMeasIsReady  true when the measurement is ready
   *
   *  \return If were successfull it returns 0; 
              otherwise it returns an error code
   *
   *  This stores a meas point and end point for measure.
   */
  long storeMeasPointEndPoint(SlMeasValues* pValues, bool& rMeasIsReady);

  /*!
   *  \fn void updateWorkPieceMeasureCoordinates (uint planeIndex, uint calibrationRecordIndex)
   *
   *  \param planeIndex               index of selected plane
   *  \param calibrationRecordIndex   index of calibration record
   *
   *  gets the measure coordinates from the tracer
   */
  void updateWorkPieceMeasureCoordinates (uint planeIndex, uint calibrationRecordIndex);

   /*!
   *  \fn void updateToolProbeMeasureCoordinates (uint planeIndex, uint calibrationRecordIndex)
   *
   *  \param planeIndex               index of selected plane
   *  \param calibrationRecordIndex   index of calibration record
   *
   *  gets the measure coordinates from the tracer
   */
  void updateToolProbeMeasureCoordinates (uint planeIndex, uint calibrationRecordIndex);

  /*!
   *  \fn void getTurnToolProbeCalibrationResults (uint calibrationRecordIndex)
   *
   *  \param calibrationRecordIndex   index of calibration record
   *
   *  Gets the trigger points of the tool probe calibration and emits signals
   *  to pass them (as measurement results) to GUI.
   */
  void updateTurnToolProbeMeasureCoordinates (uint calibrationRecordIndex);

  /*! \fn void getMeasAutoToolResults (void);
   *
   *  Method passes the measured results (length, radius) on the automatic
   *  measuring masks under JOG.
   */
  void getMeasAutoToolResults ();

  /*!
   *  \fn long deleteMeasPointMan (unsigned int nIndex)
   *
   *  \param nIndex  index of meas point to delete
   *
   *  \return If were successfull it returns 0; otherwise it returns an error code
   *
   *  This deletes an allready stored meas point at given index, \a nIndex.
   */
  long deleteMeasPointMan (unsigned int nIndex);

  /*!
   *  \fn long deleteMeasPointAuto (unsigned int nIndex)
   *
   *  \param nIndex  index of meas point to delete
   *
   *  \return If were successfull it returns 0; otherwise it returns an error code
   *
   *  This deletes an allready stored meas point at given index, \a nIndex.
   */
  long deleteMeasPointAuto (unsigned int nIndex);

  /*!
   *  \fn long deleteMeasPoint (unsigned int nIndex)
   *
   *  \param nIndex  index of meas point to delete
   *
   *  \return If were successfull it returns 0; otherwise it returns an error code
   *
   *  This deletes an allready stored meas point at given index, \a nIndex.
   */
  long deleteMeasPoint (unsigned int nIndex);

  /*!
   *  \fn long generateNcCode (QString& rNcCode, SlMeasParams* pParams)
   *
   *  \param rsNcCode   returns generated nc code
   *  \param pParams    parameter for generator
   *
   *  Generates nc code for current meas type depending on given generator 
   *  parameters, \a pParams. The generated nc code will be returned in given
   *  string \a rNcCode. 
   *
   *  \return If were successfull it returns 0; otherwise it returns an error code
   */
  long generateNcCode (QString& rsNcCode, SlMeasParams* pParams);

  /*! \fn bool presetIsAllowed ()
    *
    *  true if the preset mask is unlocked
    *
    */
  bool presetIsAllowed ();

  /*! \fn uint axisIndexGeo (uint nAxisIndex)
    *
    *  Provides the valid axis index
    *
    */
  uint axisIndexGeo (uint nAxisIndex);

  /*! \fn SlMeasPointManVector storedMeasPoints ()
    *
    *  Gives the stored meas points
    *
    */
  SlMeasPointManVector storedMeasPoints ();

  ///////////////////////////////////////////////////////////////////////////////
  // INTERFACE TO WORK OFFSET'S LOGIC
  ///////////////////////////////////////////////////////////////////////////////

  /*!
   *  \fn void displayWorkOffset (SlPaOffsetTypeEnum offsetType = SL_PA_OFFSET_TYPE_ACTIVE, 
                                  unsigned int nOffsetIndex = 0,
                                  SlMeasWorkOffsetEnum selector = SL_MEAS_WORK_OFFSET_DESTINATION)
   *
   *  \param offsetType    type of work offset
   *  \param nOffsetIndex  index of work offset in this type
   *  \param selector      work offset selector
   *
   *  Selects the work offset to display by givin type, \a offsetType and
   *  index, \a nOffsetIndex.
   */
  void displayWorkOffset (SlPaOffsetTypeEnum offsetType = SL_PA_OFFSET_TYPE_ACTIVE, 
                          unsigned int nOffsetIndex = 0,
                          SlMeasWorkOffsetEnum selector = SL_MEAS_WORK_OFFSET_DESTINATION);

  /*!
   *  \fn double valueWorkOffset (unsigned int nAxisIndex, 
   *                              SlMeasWorkOffsetEnum selector = SL_MEAS_WORK_OFFSET_DESTINATION)
   *
   *  \param nAxisIndex    index of axis 
   *  \param selector      work offset selector
   *
   */
  double valueWorkOffset (unsigned int nAxisIndex,
                          SlMeasWorkOffsetEnum selector = SL_MEAS_WORK_OFFSET_DESTINATION);

  /*!
   *  \fn SlPaOffsetTypeEnum workOffsetType (SlMeasWorkOffsetEnum selector = SL_MEAS_WORK_OFFSET_DESTINATION) const
   *
   *  \param selector      work offset selector
   *
   *  Returns the current displayed work offset type.
   */
  SlPaOffsetTypeEnum workOffsetType (SlMeasWorkOffsetEnum selector = SL_MEAS_WORK_OFFSET_DESTINATION) const;

  /*!
   *  \fn unsigned int workOffsetIndex (SlMeasWorkOffsetEnum selector = SL_MEAS_WORK_OFFSET_DESTINATION) const
   *
   *  \param selector      work offset selector
   *
   *  Returns the current displayed work offset index.
   */
  unsigned int workOffsetIndex (SlMeasWorkOffsetEnum selector = SL_MEAS_WORK_OFFSET_DESTINATION) const;

  /*!
   *  \fn unsigned int geoAxisIndex (unsigned int nAxisIndex,
                                     SlMeasWorkOffsetEnum selector = SL_MEAS_WORK_OFFSET_DESTINATION) const
   *
   *  \param nAxisIndex    axis index
   *  \param selector      work offset selector
   *
   *  Returns the geo axis index of the given global axis index, \a nAxisIndex
   */
  unsigned int geoAxisIndex (unsigned int nAxisIndex, 
                             SlMeasWorkOffsetEnum selector = SL_MEAS_WORK_OFFSET_DESTINATION) const;

  /*!
   *  \fn unsigned int displayIndexToChanAxisNumber(unsigned int nAxisDisplayIndex) const
   *
   *  \param nFrameAxisDisplayIndex    display index of an axis (see MD $MC_DISPLAY_AXIS)
   *
   *  Returns a channel axis number (>0) for the nFrameAxisDisplayIndex.
   */
  unsigned int displayIndexToChanAxisNumber(unsigned int nAxisDisplayIndex) const;

  /*! \fn int actFrameIndexChan (void) const;
   *  \retval int    Currently active frame index.
   *                 In case of error -1.
   *
   *  Provides the index of the currently active user frame
  */
  int actFrameIndexChan (void) const;

  /*! \fn long setNPV (SlMeasParams* pParams, SlMeasValues* pValues)
   *
   *  \param pParams    parameters needed for measurement
   *  \param pValues    values returned by measurement
   *
   *  \return If were successfull it returns 0; 
   *          otherwise it returns an error code
   *
   *  sets NPV and find out meas results
   */
  long setNPV (SlMeasParams* pParams, SlMeasValues* pValues);

  /*! \fn long setToolLength (SlMeasParams* pParams);
   *
   *  \param pParams    parameters needed for measurement
   *
   *  \return If were successfull it returns 0; 
   *          otherwise it returns an error code
   *
   *  sets tool length and find out meas results
   */
  long setToolLength (SlMeasParams* pParams);

  /*! \fn long setToolLengthMagnGlass ();
   *
   *  \return If were successfull it returns 0; 
   *          otherwise it returns an error code
   *
   *  sets tool length and find out meas results
   */
  long setToolLengthMagnGlass ();

  /*! \fn long setToolRadius (SlMeasParams* pParams);
   *
   *  \param pParams    parameters needed for measurement
   *
   *  \return If were successfull it returns 0; 
   *          otherwise it returns an error code
   *
   *  sets tool radius and find out meas results
   */
  long setToolRadius (SlMeasParams* pParams);

  /*! \fn long setFixPoint (SlMeasParams* pParams);
   *
   *  \param pParams    parameters needed for measurement
   *
   *  \return If were successfull it returns 0; 
   *          otherwise it returns an error code
   *
   *  sets fix point
   */
  long setFixPoint (SlMeasParams* pParams);

  /*! \fn QString setMsgPiNSetudt (long lError, QString& rsId, QString& rsContext)
   *
   *  \param lError error number from the meas function
   *  \param rsId   text Id
   *  \param context
   *
   *  \return the text id
   *
   *  sets the error messages for the jos measure
   */
  void setMsgPiNSetudt (long lError, QString& rsId, QString& rsContext);

  /* \fn void setWorkPlane (unsigned int uiWorkPlane)
   *
   * \param iWorkPlane  working plane (valid values: 17, 18, 19; other are undefined)
   *
   * Sets workplane.
   */
  void setWorkPlane (unsigned int uiWorkPlane);

  /*! \fn SlMeasPopupEnum visiblePopup () const
   *
   *  Returns the currently visible popup.
   */
  SlMeasPopupEnum visiblePopup () const;

  /*! \fn void setVisiblePopup (SlMeasPopupEnum newPopup);
   *
   *  \param inActivePopup    Identification of a currently visible popup.
   *
   *  Tell the measure logic, that a certain popup is currently visible.
   */
  void setVisiblePopup (SlMeasPopupEnum newPopup);

  /*! \fn SlMeasPopupEnum popupInProcess() const
   *
   *  \return     identification of popup in process.
   *
   *  Remark:
   *  Popup-In-Process information is a state that doesn't influence the behavior of the
   *  measure logic.
   *  If 'PopupInProcess' methods are used correctly, this method returns QString::null,
   *  if there is currently no popup in process.
   */
  SlMeasPopupEnum popupInProcess() const;

  /*! \fn bool anyPopupInProcess() const
   *
   *  \return     true if a popup process has been started and not stopped, else false.
   *
   *  Remark:
   *  Popup-In-Process information is a state that doesn't influence the behavior of the
   *  measure logic.
   *  If 'PopupInProcess' methods are used correctly, this method returns QString::null,
   *  if there is currently no popup in process.
   */
  bool anyPopupInProcess() const;

  /*! \fn void startPopupProcess (SlMeasPopupEnum newProcess)
   *
   *  \param newProcess     Identification of a currently visible popup.
   *
   *  Stores just the given popup identification.
   *
   *  Attention:
   *  Its not allowed to call this function as long a popup is in process (means
   *  anyPopupInProcess() returns true, or stopPopupProcess() wasn't called after a
   *  popup process has been started).
   *
   *  Remark:
   *  Only one popup can be processed in a instance of the measure logic.
   *  Popup-In-Process information is a state that doesn't influence the behavior of the
   *  measure logic.
   *  If 'PopupInProcess' methods are used correctly, this method returns QString::null,
   *  if there is currently no popup in process.
   */
  void startPopupProcess(SlMeasPopupEnum newProcess);

  /*! \fn void stopPopupProcess ()
   *
   * Sets the name/id to QString::null, so that a new popup process can be started. 
   */
  void stopPopupProcess();

  /*! \fn bool bool showNpvAppliedPopup(const SlMeasParams* pParams)
   *
   *  \param pParams    parameter block describing the measure environment.
   *
   *  Returns true if the "NPV data applied" popup has to be shown, else false.
   */
  bool showNpvAppliedPopup(const SlMeasParams* pParams);

  /*! \fn bool showActivationPopup(SlMeasParams* pParams) const
   *
   *  \param pParams    parameter block describing the measure environment.
   *
   *  Returns true if the activation popup has to be shown, else false.
   */
  bool showActivationPopup(SlMeasParams* pParams) const;

  /*! \fn bool showAdjustRotaryAxisPopup(SlMeasParams* pParams) const
   *
   *  \param pParams    parameter block describing the measure environment.
   *
   *  Returns true if the adjust rotary axis popup has to be shown, else false.
   */
  bool showAdjustRotaryAxisPopup(SlMeasParams* pParams) const;

  /*! \fn bool showAdjustProbeToPlainPopup(SlMeasParams* pParams) const
   *
   *  \param pParams    parameter block describing the measure environment.
   *
   *  Returns true if the adjust probe to plain popup has to be shown, else false.
   */
  bool showAdjustProbeToPlainPopup(SlMeasParams* pParams) const;

  /*! \fn bool swivelingEnabled() const
   *
   *  Returns true if swiveling is enabled, else false.
   */
  bool swivelingEnabled() const;

  /*! \fn void saveTargetNpv()
   *
   *  save the target npvdata in member variable.
   */
  void saveTargetNpv(const SlMeasParams* pParams);

  /*! \fn void getTargetNpv(SlMeasTargetNpvData* pTargetNpvData)
   *
   *  \param pTargetNpvData   class for npv data
   *
   *  get target npv data.
   */
  void getTargetNpv(const SlMeasParams* pParams, SlMeasTargetNpvData* pTargetNpvData);

  /*! \fn void getTargetNpv(SlMeasTargetNpvData* pTargetNpvData)
   *
   *  \param pTargetNpvData   class for npv data
   *
   *  compare current target npv data with save target npv data. Is equal return true, else false
   */
  bool compareTargetNpv(SlMeasTargetNpvData* pTargetNpvData);

  /*! \fn bool isTargetFrameAndSoureFrameDifference(const SlMeasParams* pParams)
   *
   *  \param pParams          parameter block describing the measure environment.
   *
   *  is target npv and swurce npv different return true, else false
   */
  bool isTargetFrameAndSoureFrameDifference(const SlMeasParams* pParams);

  /*! \fn bool toolExchangeAllowed() const
   *
   *  Returns true if tool exchange via NC-Start is allowed, else false.
   */
  bool toolExchangeAllowed() const;

  /*! \fn unsigned int activeSwivelingRecord() const
   *
   *  Returns the active swiveling record.
   *
   *  Remark: If there is no active swiveling record, 0 is returned.
   */
  unsigned int activeSwivelingRecord() const;

  /*! \fn QList<uint> getActiveSwivelingRetractionOptions() const
   *
   *  Returns a list of retraction options, valid for the currently active swiveling record.
   *
   *  Remark: If there is no active swiveling record, an empty list is returned.
   */
  QList<uint> getActiveSwivelingRetractionOptions() const;

  /*! \fn QString getRotAxisNameFromActiveSwivelNumber() const
   *
   *  Returns the rotation axis name from active swivel record.
   */
  QString getRotAxisNameFromActiveSwivelNumber() const;

  /*! \fn bool isRotAxisContainsIntoToolCarrier(int nChanAxisIndex) const
   *
   *  \param  int nChanAxisIndex     channel axis index.
   *
   *  Returns true if rotary axis into active toolcarrier, else false.
   */
  bool isRotAxisContainsIntoToolCarrier(int nChanAxisIndex) const;

  /*! \fn bool isMoreDirectionEnable() const
   *
   *  Returns true when more direction enable, else false
   */
  bool isMoreDirectionEnable() const;

  /*! \fn int getInitSwivelDirection() const
   *
   *  Returns the allowed default or initialise direction
   */
  int getInitSwivelDirection() const;

  /*! \fn int getInitSwivelDirection() const
   *
   *  determine the name of the active swivel data record
   */
  QString getSwivelNameBySwivelNumber() const;

  /*! \fn bool isTraoriActive() const
  *
  *  Returns true when traori active, else false
  */
  bool isTraoriActive() const;

  /*! \fn QList<uint> getAllowedTrackingToggleStates() const
   *
   *  Returns a list of allowed tracking states
   */
  QList<uint> getAllowedTrackingToggleStates() const;

  /*! \fn bool isToolTypeMilling (unsigned int toolType) const
   *
   *  \param pParams toolType    type of a tool.
   *
   * Returns true if 'toolType' is a milling or a drilling tool, else false.
   */
  bool isToolTypeMilling (unsigned int toolType) const;

  /*! \fn bool isToolTypeTurning (unsigned int toolType) const
   *
   *  \param pParams toolType    type of a tool.
   *
   * Returns true if 'toolType' is a turning tool, else false.
   */
  bool isToolTypeTurning (unsigned int toolType) const;

   /*! \fn bool ringDiameterFixed(int nTracerIndex) const
    *  \param     nTracerIndex   0 zero based index to a tracer record (51770[n] $MNS_J_MEA_CAL_RING_DIAM)
    *  \return    true if ring diameter is fixed in the given tracer record, else false.
    *
    *  Returns true if the diameter of the calibration ring of the workpiece probe is fixed, else true.
    */
   bool ringDiameterFixed(int nTracerIndex) const;

   /*! \fn bool calibrationHeightFixed(int nTracerIndex) const
    *  \param     nTracerIndex   0 zero based index to a tracer record (51772[n] $MNS_J_MEA_CAL_HEIGHT_FEEDAX)
    *  \return    true if calibration height is fixed in the given tracer record, else false.
    *
    *  Returns true if the calibration height of the workpiece probe is fixed, else true.
    */
   bool calibrationHeightFixed(int nTracerIndex) const;

   /*! \fn double predefinedRingDiameter(int nTracerIndex) const
    *  \param     nTracerIndex   0 zero based index to a tracer record (51770[n] $MNS_J_MEA_CAL_RING_DIAM)
    *  \return    predefined calibration height for the given tracer record.
    *
    *  Returns the predefined calibration height for the given tracer record.
    */
   double predefinedRingDiameter(int nTracerIndex) const;

   /*! \fn double predefinedCalibrationHeight(int nTracerIndex) const
    *  \param     nTracerIndex   0 zero based index to a tracer record (51772[n] $MNS_J_MEA_CAL_HEIGHT_FEEDAX)
    *  \return    predefined calibration height for the given tracer record.
    *
    *  Returns the predefined calibration height for the given tracer record.
    */
   double predefinedCalibrationHeight(int nTracerIndex) const;

   /*! \fn bool isRadiusInDiameter(double dToolType) const
    *
    *  \param dToolType    tool type
    *  \return             true if tools of type 'dToolType' use diameter display,
    *                      false if tools of type 'dToolType' use radius.
    *
    *  Returns true, if tools of given type use diameter display, else false.
    */
   bool isRadiusInDiameter(double dToolType) const;

   /*! \fn bool isTcDp6Diameter(void) const
    *
    *  Returns true, if BIT11 of MD20310 TOOL_PARAMETER_DEF_MASK active, else false.
    */
   bool isTcDp6Diameter(void) const;

   /*! \fn long savePos(SlMeasParams* pParams, QVariant& savedPos);
    *
    *  \param  pParams     parameter block describing the measure environment.
    *  \param  savedPos    out param, the position that has been saved.
    *
    *  \return             0 if successfull,
    *                      otherwise error code
    *
    *  Saves the current position (für "Position merken").
    */
   long savePos(SlMeasParams* pParams, QVariant& savedPos);

   /*! \fn bool rotationInSrcFrame(const SlMeasParams* pParams);
    *
    *  \param  pParams     parameter block describing the measure environment.
    *
    *  \return             'true' if the frame, used as measurement basis, contains 
    *                      at least one rotation (rotations are not offsets in .
    *                      'false' otherwise.
    */
   bool rotationInSrcFrame(const SlMeasParams* pParams);

   /*! \fn bool scalingInSrcFrame(const SlMeasParams* pParams);
    *
    *  \param  pParams     parameter block describing the measure environment.
    *
    *  \return             'true' if the frame, used as measurement basis, is scaled.
    *                      'false' otherwise.
    */
   bool scalingInSrcFrame(const SlMeasParams* pParams);

   /* \fn int toolLengthConst() const;
    *
    * \return           setting of $SC_TOOL_LENGTH_CONST.
    */
   int toolLengthConst() const;

   /* \fn int toolLengthType() const;
    *
    * \return           setting of $SC_TOOL_LENGTH_TYPE.
    */
   int toolLengthType() const;

   /* \fn int srcFrameIndex(const SlMeasParams* pParams) const;
    *
    * \param pParams    parameter block describing the measure environment
    * \return           index of the during measurement active work offset.
    */
   int srcFrameIndex(const SlMeasParams* pParams) const;


   /*! \fn bool allMeasPointsSet() const;
    *
    *  \return          true if all measpoints of the current measure type are set,
    *                   else false
    */
   bool allMeasPointsSet() const;

   /*! \fn bool measPointSet (int nMeasPointNo) const;
    *
    *  \param nMeasPointNo    measure point number
    *  \return                true measure point 'nMeasPointNo' is set, 
    *                         else false
    */
   bool measPointSet(int nMeasPointNo) const;

   /*!
    *  \fn SlMeasAsupModeEnum asupMode () const
    *
    *  Returns value of asupMode.
    */
   SlMeasAsupModeEnum asupMode () const;

   /*!
    *  \fn bool isManualMachineAllowed () const
    *
    *  Returns true if the option bit for manual machine is set;
    *  otherwise it returns false.
    */
   bool isManualMachineAllowed () const;

   /*!
    *  \fn void setIgnore1stToolIdentChangedSignal(bool bNewState = true);
    *
    *  \param bNewState        the new state
    *
    *  changes the behavior of the measure logic in interaction with the first
    *  "tool ident changed signal" from the SlMaActTool.
    */
  void setIgnore1stToolIdentChangedSignal(bool bNewState = true);

   /*!
    *  \fn SlStepMeasDirectionToggleEnum getDirFromCutEdgePosAndMeasAxis (void) const
    *
    *  Returns the measurement direction determined from measure axis and the cutting edge 
    *  position of current tool.
    */
   SlStepMeasDirectionToggleEnum getMeasDirFromMeasAxisAndCutEdgePos (SlStepStaticMeasAxisToggleEnum nAxis) const;

   /*!
    *  \fn bool isGrindingDresserNPV (void) const
    *
    *  \return Returns true if on a grinding machine the tool data
    *                       for a dresser is storred as NPV
    *          otherwise it returns false.
    */
   bool isGrindingDresserNPV () const;

   /*  \fn void setAsupMode(SlMeasAsupModeEnum mode = SL_ASUP_MODE_OFF)
    *
    *  Method to control what is generated by generateNcCode().
    */
   void setAsupMode(SlMeasAsupModeEnum mode = SL_ASUP_MODE_OFF);

  /*! \fn bool fullFrameCopy (void) const
   *
   *  returns true, if source frame must be copied completely into the destination frame,
   *          false "otherwise".
   */
   bool fullFrameCopy (void) const;

public slots:

  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////

  /*!
   *  \fn void measureDataSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultJogStart)
   *
   *  \param  eError   
   *  \param  adviseResultJogStart
   *
   *  the HotLinks was changed so get the new value
   */
  void measureDataSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultJogStart);  

  /*!
   *  \fn void presetValueChangedSlot (long& nError, unsigned int nAxisIndex, double actValue)
   *
   *  \param  nError
   *  \param  nAxisIndex   
   *  \param  actValue
   *
   *  gets the changed value
   */
 void presetValueChangedSlot (long& nError, unsigned int nAxisIndex, double actValue);

  /*!
   *  \fn void presetSetsAllNPVZeroValueChangedSlot ()
   *
   *
   *  sets all NPV zero under Preset
   */
 void presetSetsAllNPVZeroValueChangedSlot ();

 /*!
  *  \fn void actToolIdentChanged (const QString&)
  *  
  *  Receives a tool identification change and emits signals a tool change.
  */
 void actToolIdentChangedSlot ();

 /*!
  *  \fn void actToolIdentChanged (unsigned int nActToolTyp)
  *  
  *  Receives a tool identification change and emits signals a tool change.
  */
 void actToolTypeChangedSlot(unsigned int nActToolType);

signals:

  ///////////////////////////////////////////////////////////////////////////
  // COMMON SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  
  /*!
   *  \fn void numMeasPointsChanged (int nNumber)
   *
   *  \param nNumber    new number of meas points
   *
   *  This signal is emited if the number of measure points to store has 
   *  changed.
   */
  void numMeasPointsChanged (int nNumber);

  /*!
   *  \fn void allMeasPointsAreSet (bool bAllSet)
   *
   *  \param bAllSet   Are all meas points set?
   *
   *  This signal is emitted when the stored meas points are changed. If
   *  \a bAllSet is true all meas points are set; otherwise it is false.
   */
  void allMeasPointsAreSet (bool bAllSet);

  /*!
   *  \fn void measPointStored (unsigned int nIndex)
   *
   *  \param nIndex  index of stored meas point
   *
   *  This signal is emitted when a meas point was stored.
   */
  void measPointStored (unsigned int nIndex);

  /*!
   *  \fn void measPointDeleted (unsigned int nIndex)
   *
   *  \param nIndex  index of deleted meas point
   *
   *  This signal is emitted when a meas point was deleted.
   */
  void measPointDeleted (unsigned int nIndex);

  /*! \fn void toolDataAccessAllowed()
   *
   *  Gets and display the tool data
   *
   */
  void toolDataAccessAllowed();

  /*! \fn void toolDataRead()
   *
   *  Emitted when tool data has been read.
   */
  void toolDataRead();

  /*!
   *  \fn void setSoftkeyPressedAgain (uint uiPos)
   *
   *  \param uiPos position from the softkey
   *
   *  sets the softkey pressed
   */
  void setSoftkeyPressedAgain (uint uiPos);

  /*!
   *  \fn void progStateChanged (SlMaProgStateEnum)
   *
   *  \param SlMaProgStateEnum programm state enum
   *
   *  sets the new program state
   */
  void progStateChanged (SlMaProgStateEnum);

  /*!
   *  \fn void measTypeChanged (void)
   *
   *  The measured mask type has changed, the PLC ID must be rewritten.
   */
  void measTypeChanged (void);

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS OF ACT TOOL'S LOGIC
  ///////////////////////////////////////////////////////////////////////////

  /*!
   *  \fn void actToolTypeChanged  (unsigned int nNewType)
   *
   *  \param nNewType   new tool type
   *
   *  This signal is emited if the tool type of the act tool is changed.
   */
  void actToolTypeChanged (unsigned int nNewType);

  /*!
   *  \fn void valueChangedFromLogic (const QString& nIndex, QVariant value)
   *
   *  \param nIndex     type of tool data
   *  \param value      new value
   *
   *  This signal is emitted if a value of active tool changed.
   */
  void valueChangedFromLogic (const QString& nIndex, QVariant value);

  /*!
   *  \fn void toggleChangedFromLogic (const QString& nIndex, QVariant value)
   *
   *  \param nIndex     type of tool data
   *  \param value      new value
   *
   *  This signal is emitted if a toggle of active tool changed.
   */
  void toggleChangedFromLogic (const QString& nIndex, QVariant value);

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS OF WORK OFFSET'S LOGIC
  ///////////////////////////////////////////////////////////////////////////

  /*!
   *  \fn void valueWorkOffsetChanged (unsigned int nOffsetIndex, 
                                       unsigned int nAxisIndex, 
                                       double value)
   *
   *  \param nOffsetIndex     index of changed work offset
   *  \param nAxisIndex       index of changed axis
   *  \param value            new value
   *
   *  This signal is emitted if a value of a work offset changed.
   */
  void valueWorkOffsetChanged (unsigned int nOffsetIndex, unsigned int nAxisIndex, double value);

  /*!
   *  \fn void rotationWorkOffsetChanged (unsigned int nOffsetIndex, 
                                          unsigned int nAxisIndex, 
                                          double value)
   *
   *  \param nOffsetIndex     index of changed work offset
   *  \param nAxisIndex       index of changed axis
   *  \param value            new rotation value
   *
   *  This signal is emitted if a rotation value of a work offset changed.
   */
  void rotationWorkOffsetChanged (unsigned int nOffsetIndex, unsigned int nAxisIndex, double value);

private:

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////

   SlStepMeJogLogicPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////

  /*! copy constructor not allowed */
  SlStepMeJogLogic (const SlStepMeJogLogic& rCopy);
  /*! assignment operator not allowed */
  SlStepMeJogLogic& operator=(const SlStepMeJogLogic& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  void adviceMeasureData (void);

  void unadviceMeasureData (void);

  /*! \fn void initStaticValues(void)
   *
   *  init static values needed in form logic object
  */
  void initStaticValues(void);

  /*! \fn void initDummyValues(void)
   *
   *  init dummy values needed in form logic object, when no ncu connection exists
  */
  void initDummyValues(void);

  /*! \fn void connectToNck(void)
   *
   *  start hotlinks to ncu for dynamic value
  */
  void connectToNck (bool isInit = true);

  /*! \fn void suspendToNck(void)
   *
   *  suspends hotlinks to ncu for dynamic value
  */
  void disconnectToNck (void);

  /*! \fn void resumeToNck(void)
   *
   *  restarts suspended hotlinks to ncu for dynamic value
  */
  void resumeToNck (void);

  /*! \fn void suspendToNck(void)
   *
   *  suspends hotlinks to ncu for dynamic value
  */
  void suspendToNck (void);

  /*! \fn void connectToLogic(void)
   *
   *  connect needed signals from central logic to form logic slots
  */
  void connectToLogic (void);

  /*! \fn void connectToLogic(void)
   *
   *  disconnect signals from central logic to form logic slots
  */
  void disconnectToLogic (void);

  /*! \fn unsigned int measMethodCycleParam(unsigned int uiMeasMethod)
   *
   *  \param uiMeasMethod  parameters needed for measurement method
   *
   *  returns the measurement method for the cycle
  */
  unsigned int measMethodCycleParam(unsigned int uiMeasMethod);

  /*! \fn unsigned int generateAx(SlMeasParams* pParams)
   *
   *  \param pParams  parameters needed for measurement
   *
   *  returns the axis index for the cycle
  */
  unsigned int generateAx(SlMeasParams* pParams);

  /*! \fn unsigned int getSetPoint(SlMeasParams* pParams, double* pSwa, double* pSwo, double* pSwap)
   *
   *  \param pParams  parameters needed for measurement
   *  \param  pSwa   set point for meas axis X
   *  \param  pSwo   set point for meas axis Y
   *  \param  pSwap  set point for meas axis Z
   *
   *  get the value for selected meas axis
  */
  void getSetPoint(SlMeasParams* pParams, double* pSwa, double* pSwo, double* pSwap);

  /*! \fn unsigned int getNpvNumber(unsigned int uiNpv, unsigned int uiP) const
   *
   *  returns the sum from the NPV and P
  */
  unsigned int getNpvNumber(unsigned int uiNpv, unsigned int uiP) const;

  /*! \fn unsigned int generateActiveNpv(SlMeasParams* pParams)
   *
   *  \param pParams    parameter for generator
   *
   *  generates the measure frame
  */
  unsigned int generateActiveNpv(SlMeasParams* pParams);

  /*! \fn unsigned generateSingleEdgeMeasuring (uint singleEdgeMesuring);
   *
   *  \param singleEdgeMesuring in:  single edge measuring yes/no
   *  \return                        single edge measuring state converted for cycle
   *
   *  convert single edge measuring state "spindle reversal" into cycle parameter
  */
  unsigned int generateSingleEdgeMeasuring (uint singleEdgeMesuring);

  /*! \fn unsigned int generateSpindleReversal (uint spindleReversal)
   *
   *  \param spindleReversal in:  spindle reversal yes/no
   *  \return                     spindle reversal state converted for cycle
   *
   *  convert toggle state "spindle reversal" into cycle parameter
  */
  unsigned int generateSpindleReversal (uint spindleReversal);
    
  /*! \fn unsigned int generateNpv(SlMeasParams* pParams)
   *
   *  returns the NPV
  */
  unsigned int generateNpv(SlMeasParams* pParams);

  /*! \fn void generateAxAndDir(unsigned int& rAx, unsigned int& rDir, SlMeasParams* pParams);
   *
   *  gets the axis index and the direction for the cycle
  */
  void generateAxAndDir(unsigned int& rAx, unsigned int& rDir, SlMeasParams* pParams);

  /*! \fn void generateCyc_jmc(QString& rNcCode, SlMeasParams* pParams);
   *
   *  \param rsNcCode   returns generated nc code
   *  \param pParams    parameter for generator
   *
   *  generates the CYC_JMC cycle
  */
  void generateCyc_jmc(QString& rNcCode, SlMeasParams* pParams);

  /*! \fn void generateToolChangeIfAllowed(QString& rNcCode, SlMeasParams* pParams);
   *
   *  \param rsNcCode   returns generated nc code
   *  \param pParams    parameter for generator
   *
   *  generates the cycle call for tool change, if tool exchange is allowed.
  */
  void generateToolChangeIfAllowed(QString& rsNcCode, SlMeasParams* pParams);

  /*! \fn unsigned int generateNum3DTracer(SlMeasParams* pParams)
   *
   *  \param pParams    parameter for generator
   *
   *  generates the probe number
  */
   unsigned int generateNum3DTracer(SlMeasParams* pParams);

  /*! \fn unsigned int generateWorkPlane()
   *
   *  generates the work plane
  */
   unsigned int generateWorkPlane();

  /*! \fn double getActiveNpvForPreset(unsigned int nAxisIndex)
   *
   *  \param nAxisIndex    axis index
   *
   *  gets the active NPV for the preset functions
  */
   double getActiveNpvForPreset(unsigned int nAxisIndex);

  /*! \fn int getContainerNoOfActiveChannel(void)
   *
   *  gets container number of active container
   */
   int getContainerNoOfActiveChannel(void) const;

   /*! \fn SlPaWorkOffsetDetails* workOffset(SlMeasWorkOffsetEnum selector) const
    *
    *  \param     selector of a work offset details instance
    *  \return    selected work offset details instance
    */
   SlPaWorkOffsetDetails* workOffset(SlMeasWorkOffsetEnum selector) const;

   /*! \fn void copyOffsetDetails(SlPaWorkOffsetDetails* pSrc, SlPaWorkOffsetDetails* pDst, const SlMeasParams* pParams);
    *
    *  \param pSrc            source npv
    *  \param pDst            dst npv
    *  \param pParams         parameter block describing the measure environment
    *
    *  Copies the data of 'pSrc' into 'pDst'.
    */
   void copyOffsetDetails(SlPaWorkOffsetDetails* pSrc, SlPaWorkOffsetDetails* pDst, const SlMeasParams* pParams);

   /*! \fn void srcOffsetType(const SlMeasParams* pParams, SlPaOffsetTypeEnum& outType, unsigned int& outOffsetIndex);
    *
    *  \param pParams            parameter block describing the measure environment
    *  \param outType            output parameter
    *  \param outOffsetIndex     output parameter
    *
    *  Returns the offset type and offset index of the currently active work offset
    *  to setup an SlPaWorkOffsetDetails instance for the currently active work offset.
    */
   void srcOffsetType(const SlMeasParams* pParams, SlPaOffsetTypeEnum& outType, unsigned int& outOffsetIndex);

   /*! \fn bool bool dstFramePreparationNeeded(const SlMeasParams* pParams)
    *
    *  \param pParams    parameter block describing the measure environment.
    *
    *  Returns true if destination frame needs preparation, else false.
    */
   bool dstFramePreparationNeeded(const SlMeasParams* pParams);

   /* \fn void prepareDstFrame(const SlMeasParams* pParams);
    *
    *  Prepares the destination frame of a measurement, if needed.
    */
   void prepareDstFrame(const SlMeasParams* pParams);

   /* \fn SlPaWorkOffsetDetails* configureSrcWorkOffsetDetails(const SlMeasParams* pParams)
    *
    *  \param     pParams    parameter block describing the measure environment.
    *  \return               work offset details of the frame that's used as source within
    *                        the measurement.
    *  
    *  The work offset details instance is setup for synchron access, before it's returned.
    */
   SlPaWorkOffsetDetails* configureSrcWorkOffsetDetails(const SlMeasParams* pParams);

   /* \fn int int dirToggle2CycleDir(SlStepMeasDirectionToggleEnum dirToggle) const;
    *
    *  \param     dirToggle  measure direction toggle state
    *  \return               cycle measure direction
    *  
    *  Converts the measure direction toggle state to a cycle measure direction.
    */
   int dirToggle2CycleDir(SlStepMeasDirectionToggleEnum dirToggle) const;
   int dirToggle2CycleDir(int dirToggle) const;

   /*!
    *  \fn unsigned int actCuttingEdgePosition (void) const
    *
    *  Returns the active cutting tool position
    */
   unsigned int actCuttingEdgePosition (void) const;

   /*!
    *  \fn double actCuttingDirMod (void) const
    *
    *  Returns the cutting direction of the active tool, under the consideration of beta/gamma rotation.
    */
   double actCuttingDirMod (void) const;

   /*!
    *  \fn void autoCompleteDirection (SlMeasParams& ) const
    *
    *  \param     rParams    parameters needed for measurement
    *
    *  Method checks, if the direction is given in parameters. If direction is not 
    *  already set it fills it in, in dependence to measure axis and cutting edge 
    *  position of actual tool.
    */
   void autoCompleteDirection(SlMeasParams& rParams) const;

   /*!
    *  \fn void selectedPlaneMatchesCalibrationPlane (uint valueOfSD, uint planeIndex, uint calibrationRecordIndex, SlStepMeConfig::SlStepMeasuringModeEnum calibrationMode) const
    *
    *  \param valueOfSD                value of correspondent status bit
    *  \param planeIndex               index of selected plane
    *  \param calibrationRecordIndex   index of calibration record
    *  \param calibrationMode          calibration Mode
    *  \return                         'true' if planes match
    *
    *  Compares the plane used during calibration of current record (Abgleichdatensatz) with the currently selected plane
    */
  bool selectedPlaneMatchesCalibrationPlane (uint valueOfSD,
                                             uint planeIndex, 
                                             uint calibrationRecordIndex, 
                                             SlStepMeConfig::SlStepMeasuringModeEnum calibrationMode) const;

   /*!
    *  \fn void calibrationRecordContainsPlaneData (uint valueOfSD, SlStepMeasCalStatusEnums axis, SlStepMeasCalDirectionEnums direction, uint calibrationRecordIndex, SlStepMeConfig::SlStepMeasuringModeEnum calibrationMode) const
    *
    *  \param valueOfSD                value of correspondent status bit
    *  \param axis                     which axis should be checked
    *  \param direction                calibration direction (plus, minus)
    *  \param calibrationRecordIndex   index of calibration record
    *  \param calibrationMode          calibration Mode
    *  \return                         'true' if calibration was done for the plane
    *
    *  Checks if current calibration record contains plane data for the axis specified 
    */
  bool calibrationRecordContainsPlaneData (uint valueOfSD,
                                           SlStepMeasCalStatusEnums axis, 
                                           SlStepMeasCalDirectionEnums direction, 
                                           uint calibrationRecordIndex, 
                                           SlStepMeConfig::SlStepMeasuringModeEnum calibrationMode) const;

   /*!
    *  \fn void isTurnCalibrationRecord (uint valueOfSD) const
    *
    *  \param valueOfSD                value of correspondent status bit
    *  \return                         'true' for turning calibration record
    *
    *  Checks if current calibration record is for turning 
    */
  bool isTurnCalibrationRecord (uint valueOfSD) const;

    /*!
    *  \fn void isMillCalibrationRecord (uint valueOfSD) const
    *
    *  \param valueOfSD                value of correspondent status bit
    *  \return                         'true' for milling calibration record
    *
    *  Checks if current calibration record is for turning 
    */
  bool isMillCalibrationRecord (uint valueOfSD) const;

   /*!
    *  \fn QVariant getCalibrationRecordValue (SlStepMeasCalValuesEnum value, uint calibrationRecordIndex, SlStepMeConfig::SlStepMeasuringModeEnum calibrationMode)
    *
    *  \param value                    calibration record value that should be fetched
    *  \param calibrationRecordIndex   index of calibration record
    *  \param calibrationMode          calibration Mode
    *  \return                         calibration record value
    *
    *  Returns the calibration record value from the corresponding SD value 
    */
  SlStepValue getCalibrationRecordValue (SlStepMeasCalValuesEnum value,
                                         uint calibrationRecordIndex, 
                                         SlStepMeConfig::SlStepMeasuringModeEnum calibrationMode);

   /*!
    *  \fn QString getCalAndMeasFeed(SlMeasParams& rParams) const;
    *
    *  \param rParams                  parameter block with measure mask parameters
    *  \return                         calibration and measure feed string (for cycle generation)
    */
   QString getCalAndMeasFeed(SlMeasParams& rParams) const;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(SlStepMeasCalStatusEnums)
Q_DECLARE_OPERATORS_FOR_FLAGS(SlStepMeasCalDirectionEnums)

#endif // SL_MA_JOG_ME_LOGIC_H
