///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaacttool.h
 *  \author Harald Vieten
 *  \date   18.11.2004
 *  \brief  Definition file for class SlMaActTool
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2004 - 2013. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_ACT_TOOL_H_INCLUDED
#define SL_MA_ACT_TOOL_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"
#include "sltmqcmd.h"
#include "sltminfo.h"
#include "sltmutil.h"

   ///////////////////////////////////////////////////////////////////////////
   // ENUMS
   ///////////////////////////////////////////////////////////////////////////
 /*! \enum defining for SlMaToolCRCEnum*/
enum SlMaToolCRCEnum
{
   SL_MA_TOOL_CRC_G40 = 40,                 /*!< cutting radius correction G40, none. same code in ISO/Fanuc or Siemens*/
   SL_MA_TOOL_CRC_G41 = 41,                 /*!< cutting radius correction G41, left contour*/
   SL_MA_TOOL_CRC_G42 = 42,                 /*!< cutting radius correction G42, right contour*/
   SL_MA_TOOL_ERROR = -1,                   /*!< cutting radius correction undefined*/
};

class SlMaActToolPrivate;

/*! \class  SlMaActTool
 *  \brief  Interface service adapter of act tool
 */
class SL_MA_LOGIC_EXPORT SlMaActTool : public SlMaFormLogicBase
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(SlMaBasicLengthUnitEnum)
	Q_ENUMS(SlMaToolCRCEnum)

public:
   ///////////////////////////////////////////////////////////////////////////
   // ENUMS
   ///////////////////////////////////////////////////////////////////////////


  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaActTool (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaActTool (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaActTool ();
   *
   *  destructor
  */
  virtual ~SlMaActTool ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  void setModeManualMachine (bool isModeManualMachine = true); /*!< reduce refreshed values to actToolIdent, actDuploNumber, actDNumberStandard*/

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  unsigned int  externCncSystem (void);                 /*!< get cnc-system, siemens-mode or a iso-mode*/
  SlMaFormLogicTechnoTypeEnum technoType (void);        /*!< get technologic type universal/milling/turning*/
  SlMaFormLogicTechnoTypeEnum technoTypeExtension (void); /*!< erweiterte Technologie*/
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const; /*!< unit mm, inch*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  unsigned int actTNumber (void);         /*!< Nummer aktives Werkzeug*/
  qlonglong    actDNumber (void);         /*!< Nummer aktive Schneide ISO oder Standard-Siemens*/
  unsigned int actDLNumber (void);        /*!< Nummer der aktiven Summenkorrektur DL*/
  unsigned int actDNumberStandard (void); /*!< Nummer aktive Schneide nur Standard-Siemens*/
  qlonglong    actHNumber (void);         /*!< Nummer aktive Schneide iso mode*/
  unsigned int progTNumber (void);        /*!< Nummer vorgewaehltes Werkzeug*/
  unsigned int progDNumber (void);        /*!< Nummer vorgewahlte Schneide*/
  QString      actToolIdent (void);       /*!< Name aktives Werkzeug*/
  QString      progToolIdent (void);      /*!< Name vorgewaehltes Werkzeug*/
  double       actToolRadius (void);      /*!< Radius aktives Werkzeug*/
  double       actToolRadiusP_TOOLR (void); /*!< aktiver Werkzeugradius, aktives Werkzeug entprechend parameter P_TOOLR*/
  double       actToolWearRadius (void);  /*!< Verschleiss Radius aktives Werkzeug*/
  double       geoAxisActToolLength (unsigned int uiGeoAxisIndex); /*!< wirksame laengenkorrektur fuer geoAxisIndex 0, 1, 2*/
  double       toolGeoLength (unsigned int uiLengthIndex); /*!< aktives Werkzeug laengenkorrektur fuer lengthIndex 0, 1, 2*/
  double       toolWearLength (unsigned int uiWearIndex); /*!< aktives Werkzeug laengenkorrektur fuer wearIndex 0, 1, 2*/
  double       toolAdptLength (unsigned int uiAdptIndex); /*!< aktives Werkzeug Adaptermass fuer uiAdptIndex 0, 1, 2*/
  double       toolEcLength (unsigned int uiEcIndex); /*!< aktives Werkzeug Einrichtekorrektur fuer uiEcIndex 0, 1, 2*/
  double       toolScLength (unsigned int uiScIndex); /*!< aktives Werkzeug Summenkorrektur fuer uiScIndex 0, 1, 2*/
  QString      geoAxisName (unsigned int uiGeoAxisIndex); /*!< geoAxisName fuer geoAxisIndex 0, 1, 2*/
  unsigned int actDuploNumber (void);     /*!< Duplo-Nr aktives Werkzeug*/
  unsigned int actToolType (void);        /*!< Typ aktives Werkzeug*/
  SlMaToolCRCEnum actCRCMode (void);         /*!< cutting radius correction aktives Werkzeug*/
  unsigned int actCuttingEdgePosition (void);   /*!< schneidenlage aktives Werkzeug*/
  unsigned int actCuttingEdgeDirection (void);   /*!< schneidenrichtung aktives Werkzeug*/
  unsigned int actToolMagazinePlace (void);   /*!< magazinplatz aktives Werkzeug*/
  unsigned int multiToolPlace (void);         /*!< werkzeugplatz auf multitool des aktiven Werkzeugs*/
  bool         showAsDiameter(void);      /*!< Durchmesser statt Radius */
  int          toolStatusISO(unsigned int indexIn);  /*!< indexIn 0 up to 4, to get ISO params L1 up to L5*/
  double       cuttEdgeParamMod (unsigned int parameter);  /*!< Mod. Parameter des akt. Werkzeugs geaendert, (parameter)*/
  QString      actPlane(void);            /*!< aktive ebene G17, G18, G19*/
  unsigned int newToolTargetMagazine (void); /*!< Zielmagazin des neuen Werkzeugs*/
  unsigned int newToolTargetPlace (void);    /*!< Zielplatz des neuen Werkzeugs*/
  unsigned int oldToolTargetMagazine (void); /*!< Zielmagazin des alten Werkzeugs*/
  unsigned int oldToolTargetPlace (void);    /*!< Zielplatz des alten Werkzeugs*/
  unsigned int myMag (void);              /*!< Heimat-Magazinnummer aktives Werkzeug*/
  unsigned int myPlace (void);            /*!< Heimat-Magazinplatznummer aktives Werkzeug*/
  unsigned int inMag (void);              /*!< Werkzeug im Magazinnummer*/
  unsigned int inPlace (void);            /*!< Werkzeug im Magazinplatznummer*/
  unsigned int magKind (void);            /*!< Typ des Magazins des aktiven Werkzeugs*/
  bool         isShowProgTool(void);      /*!< soll vorgewaehltes werkzeug angezeigt werden */
  bool         isShowToolRadius(void);    /*!< soll werkzeugradius/-durchmesser angezeigt werden */
  bool         isShowToolLength(void);    /*!< soll werkzeuglaengen angezeigt werden */
  bool         isShowToolIcon(void);      /*!< soll werkzeuglage(Icon) angezeigt werden */
  bool         isMirrorActive(void);      /*!< zeigt ob mirror activ ist, fuer mindestens eine Achse*/
  bool         valueOffsetMirror(unsigned int indexAxis);  /*!< zeigt den Mirror Zustand fuer eine Achse (0 bis numAxes-1)*/
  unsigned int toolEffectiveAccessIndex(unsigned int uiGeoAxisIndex);/*!< index fuer zugriff auf wzv-spezifische daten, unter beruecksichtigung von werkzeug-typ und aktiver ebene */
  

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void adviceToolStatusSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultToolStatus); /*!< Slot: adviceSpinStatusSlot*/
  void adviceToolStatusSlotManualMachine(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultToolStatus); /*!< Slot: adviceSpinStatusSlot*/
  void adviceToolStatusISOSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultToolStatusISO); /*!< Slot: adviceSpinStatusISOSlot*/
  void adviceTotFrameMirrorInfoSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviceTotFrameMirrorInfo); /*!< Slot: adviceTotFrameMirrorInfoSlot*/
  void unadviceHandleActiveSlot(unsigned int);                      /*!< zeitverzoegertes unadvice soll nun ausgefuehrt werden*/
  void isFanucModeSlot (bool); /*!< Slot: isFanucModeSlot*/
  void onTmPOReset(SlTmQCmd&, int typeOfNotify, const SlTmContainerNosMapType&, const SlTmInfo& info);
  void onGetTmData(void);

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn connectStateChanged (SlMaConnectStateEnum);
   *  \param  state of nc cap connection
   *
   *  Signal, emitted when connection state via cap changed
  */
  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);  /*!< zeigt eine Aenderung der Einheit mm, inch*/
  void actTNumberChanged (unsigned int);        /*!< Nummer aktives Werkzeug geaendert*/
  void actDNumberChanged (qlonglong);           /*!< Nummer aktive Schneide geaendert*/
  void actDLNumberChanged (unsigned int);       /*!< Nummer der aktiven Summenkorrektur DL*/
  void actHNumberChanged (qlonglong);           /*!< Nummer aktive Schneide iso- mode geaendert*/
  void progTNumberChanged (unsigned int);       /*!< Nummer vorgewaehltes Werkzeug geaendert*/
  void progDNumberChanged (unsigned int);       /*!< Nummer vorgewahlte Schneide geaendert*/
  void actToolIdentChanged (const QString&);    /*!< Name aktives Werkzeug geaendert*/
  void progToolIdentChanged (const QString&);   /*!< Name vorgewaehltes Werkzeug geaendert*/
  void actToolRadiusChanged (double);           /*!< Radius aktives Werkzeug geaendert*/
  void actToolWearRadiusChanged (double);       /*!< Verschleiss Radius aktives Werkzeug geaendert*/
  void geoAxisActToolLengthChanged (unsigned int, double); /*!< wirksame laengenkorrektur fuer geoAxisIndex 0, 1, 2*/
  void toolGeoLengthChanged (unsigned int, double); /*!< aktives Werkzeug laengenkorrektur fuer lengthIndex 0, 1, 2*/
  void toolWearLengthChanged (unsigned int, double); /*!< aktives Werkzeug laengenkorrektur fuer wearIndex 0, 1, 2*/
  void toolAdptLengthChanged (unsigned int, double); /*!< aktives Werkzeug Adaptermass fuer adptIndex 0, 1, 2*/
  void toolEcLengthChanged (unsigned int, double); /*!< aktives Werkzeug Einrichtekorrektur fuer ecIndex 0, 1, 2*/
  void toolScLengthChanged (unsigned int, double); /*!< aktives Werkzeug Summenkorrektur fuer scIndex 0, 1, 2*/
  void actDuploNumberChanged (unsigned int);    /*!< Duplo-Nr aktives Werkzeug geaendert*/
  void actCRCModeChanged (SlMaToolCRCEnum);     /*!< cutting radius corrction mode. values: 40,41,42*/
  void actToolTypeChanged (unsigned int);       /*!< Typ aktives Werkzeug geaendert*/
  void actCuttingEdgePositionChanged (unsigned int);   /*!< Schneidenlage aktives Werkzeug geaendert*/
  void actCuttingEdgeDirectionChanged (unsigned int);   /*!< Schneidenrichtung aktives Werkzeug geaendert*/
  void actToolMagazinePlaceChanged (unsigned int);   /*!< magazinplatz aktives Werkzeug geaendert*/
  void multiToolPlaceChanged (unsigned int);    /*!< multitoolplatz aktives Werkzeug geaendert*/
  void showAsDiameterChanged(bool);             /*!< Durchmesser statt Radius geaendert*/
  void toolStatusISOChanged(void);              /*!< one ore more ISO params L1 up to L5 are changed*/
  void cuttEdgeParamModChanged (unsigned int, double);  /*!< Mod. Parameter des akt. Werkzeugs geaendert, (parameter,value)*/
  void actPlaneChanged (const QString&);        /*!< aktive ebene G17, G18, G19*/
  void actToolSomeDataChanged (unsigned int, unsigned int);    /*!< eines der tool-daten fuer T-Nr, D-Nr hat sich geaendert, abgleich erforderlich*/
  void valueOffsetMirrorChanged(unsigned int, unsigned int, bool);   /*!< valueOffsetMirror geaendert: Achsindex (0 bis numAxes-1), neuer Wert*/

//END SUPPRESS


private:

//BEGIN SUPPRESS 3.6.2.1c 
//rule broken! names should match to file common.nsp
  enum SlMaLinkItemToolManualMachineEnum 
  {
    E_actTNumberManualMachine   = 0,
    E_actDNumberManualMachine,
    E_actToolIdentManualMachine,
    E_actDuploNumberManualMachine,
    E_newToolTargetMagazineManualMachine,
    E_newToolTargetPlaceManualMachine,
    E_oldToolTargetMagazineManualMachine,
    E_oldToolTargetPlaceManualMachine,
      //hier, vor E_ToolStatusManualMachineNumElements neue ergaenzen
    E_ToolStatusManualMachineNumElements,
  };

  enum SlMaLinkItemToolEnum 
  {
    E_actTNumber   = 0,
    E_actDNumber,
    E_actDLNumber,
    E_progTNumber,
    E_progDNumber,
    E_actToolIdent,
    E_progToolIdent,
    E_actToolRadius,
    E_actOriToolLength1,
    E_actOriToolLength2,
    E_actOriToolLength3,
    E_actDuploNumber,
    E_ncFktAct7,
    E_maskToolManagement,
    E_cuttEdgeParamMod_2,
    E_cuttEdgeParamMod_11,
    E_actPlane,
    E_actHNumberFanuc32,
    E_actDNumberFanuc32,
    E_actHNumberFanuc,
    E_actDNumberFanuc,
    E_magActPlace,
    E_newToolTargetMagazine,
    E_newToolTargetPlace,
    E_oldToolTargetMagazine,
    E_oldToolTargetPlace,
      //hier, vor E_ToolStatusNumElements neue ergaenzen
    E_ToolStatusNumElements,
  };

  enum SlMaLinkItemToolISOEnum 
  {
    E_isoL1   = 0,
    E_isoL2,
    E_isoL3,
    E_isoL4,
    E_isoL5,
      //hier, vor E_isoL5 neue ergaenzen
    E_ToolStatusISONumElements,
  };
//END SUPPRESS

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaActToolPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaActTool (const SlMaActTool& rCopy);
  /*! assignment operator not allowed */
  SlMaActTool& operator=(const SlMaActTool& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void readToolStatusManualMachine(void);
  void readToolStatus(void);
  void dummyToolStatus (void);
  void resumeToolStatus (void);
  void suspendToolStatus (void);
  void adviceToolStatus (void);
  void adviceToolStatusManualMachine (void);
  void unadviceToolStatus (void);  
  void dummyToolStatusISO (void);
  void readToolStatusISO(void);
  void resumeToolStatusISO (void);
  void suspendToolStatusISO (void);
  void adviceToolStatusISO (void);
  void unadviceToolStatusISO (void);
  void dummyTotFrameMirrorInfo(void);
  void adviceTotFrameMirrorInfo(void);
  void unadviceTotFrameMirrorInfo(void);
  QString actToolIdent_or_numberAsIdent (void) const;
  QString progToolIdent_or_numberAsIdent (void) const;
  void getTmToolType(void);
  void emitDAndHNumber(void);
  void checkReadToolDataSync(void);
  void checkToolEffectiveAccessIndex(void);

  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_MA_ACT_TOOL_H_INCLUDED
