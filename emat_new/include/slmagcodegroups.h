///////////////////////////////////////////////////////////////////////////////
/*! \file   slmagcodegroups.h
 *  \author Harald Vieten
 *  \date   25.01.2005
 *  \brief  Definition file for class SlMaGCodeGroups
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_GCODE_GROUPS_H_INCLUDED
#define SL_MA_GCODE_GROUPS_H_INCLUDED


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"


class SlMaGCodeGroupsPrivate;

///////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////
/*! \enum SlMaGCodeTypeEnum
 *
 *  types of displaying g-code groups
 */
enum SlMaGCodeTypeEnum
{
   SL_MA_G_CODE_SELECTION = 0,          /*!< Auswahl nach Auswahlliste*/
   SL_MA_G_CODE_COMPLETE = 1,           /*!< Alle verfuegbaren G-Codes anzeigen*/
   SL_MA_G_CODE_PART_OF = 2,            /*!< G-Codes anzeigen ab firstElement, Anzahl numElements*/
   SL_MA_G_CODE_NONE = 3,               /*!< keine G-Codes anzeigen, nur additional data */
};

/*! \enum SlMaGCodeGroupSelectListEnum
 *
 *  Liste der anzuzeigenden G-codes 1,2,3,6,7,8,9,10,13,14,15,16,21,22,29,30
 */
enum SlMaGCodeGroupSelectListEnum
{
   SL_MA_G_CODE_GROUP_1 = 1,
   SL_MA_G_CODE_GROUP_2 = 2,
   SL_MA_G_CODE_GROUP_3 = 3,
   SL_MA_G_CODE_GROUP_6 = 6,
   SL_MA_G_CODE_GROUP_7 = 7,
   SL_MA_G_CODE_GROUP_8 = 8,
   SL_MA_G_CODE_GROUP_9 = 9,
   SL_MA_G_CODE_GROUP_10 = 10,
   SL_MA_G_CODE_GROUP_13 = 13,
   SL_MA_G_CODE_GROUP_14 = 14,
   SL_MA_G_CODE_GROUP_15 = 15,
   SL_MA_G_CODE_GROUP_16 = 16,
   SL_MA_G_CODE_GROUP_21 = 21,
   SL_MA_G_CODE_GROUP_22 = 22,
   SL_MA_G_CODE_GROUP_29 = 29,
   SL_MA_G_CODE_GROUP_30 = 30,
};

enum SlMaToleranceIdEnum
{
  SL_MA_TOL_ID_LIN_G0,
  SL_MA_TOL_ID_LIN_G1,
  SL_MA_TOL_ID_ROT_G0,
  SL_MA_TOL_ID_ROT_G1,
  SL_MA_TOL_ID_CTOL,
  SL_MA_TOL_ID_OTOL,
  SL_MA_TOL_ID_CTOL_G0,
  SL_MA_TOL_ID_OTOL_G0,
};

/*! \class  SlMaGCodeGroups
 *  \brief  Interface service adapter of gcode groups
 */
class SL_MA_LOGIC_EXPORT SlMaGCodeGroups : public SlMaFormLogicBase
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaConnectStateEnum)
  Q_ENUMS(SlMaToleranceIdEnum)

public:
   ///////////////////////////////////////////////////////////////////////////
   // ENUMS
   ///////////////////////////////////////////////////////////////////////////


  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaGCodeGroups (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaGCodeGroups (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaGCodeGroups ();
   *
   *  destructor
  */
  virtual ~SlMaGCodeGroups ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setFirstElement (unsigned int firstElement); /*!< erstes Element für die Anzeige, von 0 an*/
  void setNumElements (unsigned int numElements);   /*!< Anzahl Elemente für die Anzeige*/
  void setGCodeType (SlMaGCodeTypeEnum gCodeType);  /*!< zur Auswahl, ob alle oder eine Auswahl angezeigt werden sollen*/

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  unsigned int numGCodeGroups (void) const;         /*!< zeigt die Anzahl der verfuegbaren G-Code-Gruppen*/
  bool isFanucMode(void);                           /*!< zeigt ob aktuell Siemens(G290 == false) oder ISO-Mode(G291 == true) aktiv ist*/
  int functionAvailableState(SlMaFunctionAvailableEnum functionIn);

  /*! get methods, available after SL_MA_START_LOGIC*/
  QString gCode (unsigned int index) const;         /*!< Zeigt den G-Code Namen fuer einen absoluten index (firstElement bis firstElement+numElements-1)*/
  unsigned int gCodeGroupID (unsigned int index) const;  /*!< Zeigt die G-Code Group-ID fuer einen absoluten index (firstElement bis firstElement+numElements-1)*/
  QString actTransform (void) const;                /*!< Zeigt die aktuelle trafo an, z.b. TRAORI*/
  QString acTrafoName (void) const;                 /*!< Zeigt den aktuellen trafo namen bei kinematischen ketten, nur fuer T,F,S - SL_MA_G_CODE_NONE muss gesetzt sein*/
  QString actTcarrName (void) const;                /*!< Zeigt den aktuellen toolcarrier namen, nur fuer T,F,S - SL_MA_G_CODE_NONE muss gesetzt sein*/
  double tolerance(const SlMaToleranceIdEnum eTolId) const;

  bool hasHighlightedGGroups() const;
  bool isGGroupHighlighted(const int iGroupId) const;

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void adviceGCodeGroupsSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultGCodeGroups); /*!< Slot: adviceGCodeGroupsSlot*/
  void adviceAdditionalDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultAdditionalData); /*!< Slot: adviceAdditionalDataSlot*/
  void adviceTcarrDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultTcarrData); /*!< Slot: adviceTcarrDataSlot*/
  void isFanucModeChangedSlot(bool bIsFanucMode); /*!< Slot: isFanucModeChangedSlot*/
  void actPtcTCARRSlot(unsigned int actPtcTCARR); /*!< Slot: actPtcTCARRSlot*/

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
  void activeChanChanged (const QString&);            /*!< zeigt eine Aenderung des aktiven Kanals*/
  void gCodeChanged (unsigned int index, unsigned int gCodeGroupID, const QString&);  /*!< G-Code Index und G-Code fuer einen absoluten index (firstElement bis firstElement+numElements-1)*/
  void actTransformChanged (const QString&);          /*!< zeigt die aktuelle trafo an, z.b. TRAORI*/
  void actTcarrChanged (const QString&, unsigned int actTcarrState); /*!< zeigt den aktiven tcarr an, z.b. TCARR=2 und bei kinematischen ketten den trafonamen, nur fuer T,F,S - SL_MA_G_CODE_NONE muss gesetzt sein*/
  void isFanucModeChanged(bool);                      /*!< Signal: isFanucModeChanged*/
  void functionAvailableStateChanged(void);           /*!< Signal: functionAvailableStateChanged*/
  void basicLengthUnitChanged(SlMaBasicLengthUnitEnum);
  void toleranceChanged(const SlMaToleranceIdEnum eTolId, const double dValue);

  //END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private ENUMS
  ///////////////////////////////////////////////////////////////////////////
  enum SlMaGCodeGroupsAdditionalDataEnum
  {
    E_actTransform = 0,
    E_acTrafoName,
    E_acCTol,
    E_acOTol,
    E_acSTolF,
    E_acCTolG0,
    E_acOTolG0,
    E_AdditionalDataNumElements
  };

  enum SlMaGCodeGroupsTcarrDataEnum
  {
    E_tcCarr34 = 0,
    E_tcCarr13 = 1,
    E_tcCarr14 = 2,
    E_TcarrDataNumElements
  };

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaGCodeGroupsPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaGCodeGroups (const SlMaGCodeGroups& rCopy);
  /*! assignment operator not allowed */
  SlMaGCodeGroups& operator=(const SlMaGCodeGroups& rCopy);

  void setGCodeSelectList (void);
  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummyGCodeGroups (void);
  void adviceGCodeGroups (void);
  void unadviceGCodeGroups (void);
  void dummyAdditionalData (void);
  void adviceAdditionalData (void);
  void unadviceAdditionalData (void);
  void dummyTcarrData (void);
  void adviceTcarrData (void);
  void unadviceTcarrData (void);

  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_MA_GCODE_GROUPS_H_INCLUDED
