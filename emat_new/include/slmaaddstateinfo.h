///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaaddstateinfo.h
 *  \author Ruebig Guenter
 *  \date   01.08.2006
 *  \brief  Definition file for class SlMaAddStateInfo
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_ADD_STATE_INFO_H_INCLUDED
#define SL_MA_ADD_STATE_INFO_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"


class SlMaAddStateInfoPrivate;


  ///////////////////////////////////////////////////////////////////////////
  // STATIC CONST DATA
  ///////////////////////////////////////////////////////////////////////////
  static const QString TRAFO_NAME_TRAANG    = "TRAANG";
  static const QString TRAFO_NAME_TRANSMIT  = "TRANSMIT";
  static const QString TRAFO_NAME_TRAORI    = "TRAORI";
  static const QString TRAFO_NAME_TRACYL    = "TRACYL";

 /*! \enum defining for SlMaActiveTrafoMaskEnum*/
enum SlMaActiveTrafoMaskEnum 
{
  SL_MA_ACTIVE_TRAFO_NONE           = 0x00000000,   /*!< none trafo is active*/
  SL_MA_ACTIVE_TRAFO_TRAANG         = 0x00000001,   /*!< TRAANG trafo is active*/
  SL_MA_ACTIVE_TRAFO_TRANSMIT       = 0x00000002,   /*!< TRANSMIT trafo is active*/
  SL_MA_ACTIVE_TRAFO_TRAORI         = 0x00000004,   /*!< TRAORI trafo is active*/
  SL_MA_ACTIVE_TRAFO_TRACYL         = 0x00000008,   /*!< TRACYL trafo is active*/
  SL_MA_ACTIVE_TRAFO_MASK           = 0x0000FFFF,   /*!< to mask out active trafos*/
  SL_MA_ACTIVE_TRAFO_CHAIN_MASK     = 0xFFFF0000,   /*!< to mask out active trafo chains*/
};

/*! \class  SlMaAddStateInfo
 *  \brief  Interface service adapter of settings manual
 */
class SL_MA_LOGIC_EXPORT SlMaAddStateInfo : public SlMaFormLogicBase
{
   Q_OBJECT
   Q_ENUMS(SlCapErrorEnum)
   Q_ENUMS(SlMaActiveTrafoMaskEnum)

public:

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaAddStateInfo (const QString& rInstancePath = 0, QObject* pParent = 0);
   *
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
   */
  SlMaAddStateInfo (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaAddStateInfo ();
   *
   *  destructor
   */
  virtual ~SlMaAddStateInfo ();


  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////

  /*! set methods */
  void setDisplayAxes (SlMaDisplayAxesTypeEnum displayAxes);            /*!< Istwerte, Ankratzen, Refpoint*/


  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_START_LOGIC*/

  SlMaActiveTrafoMaskEnum actTrafoMask (void) const;  /*!< Zeigt die aktuelle Trafo Bitcodiert an*/
  QString workOffsetName (void) const;                /*!< WorkOffset Name*/
  QString scaleUsedGeoAxesNames (void) const;         /*!< an scale beteiligte achsen als string e.g. XY or XYZ*/
  QString rotationUsedGeoAxesNames (void) const;      /*!< an rotation beteiligte achsen als string e.g. XY or XYZ*/
  QString mirrorUsedGeoAxesNames (void) const;        /*!< an mirror beteiligte achsen als string e.g. XY or XYZ*/
  bool isWorkOffsetScaleActive (void) const;          /*!< zeigt ob scale activ ist*/
  bool isWorkOffsetRotationActive (void) const;       /*!< zeigt ob rotation activ ist*/
  bool isWorkOffsetMirrorActive (void) const;         /*!< zeigt ob mirror activ ist*/
  QString actPtcTCARRName (void) const;               /*!< zeigt den aktuellen tool-carryer als string "TCARR" oder "TCARR=x" wenn es mehr als 1nen geben kann*/

  // TCARR fehlt noch. ist das ein String?

public slots:
  
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////

  void actFrameIndexSlot(unsigned int actFrameIndex);
  void isFanucModeSlot(bool isFanucMode);
  void rotationChangedSlot(const QString szState);
  void actPtcTCARRSlot(unsigned int actPtcTCARR);
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);
  void adviceAdditionalDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultAdditionalData); /*!< Slot: adviceAdditionalDataSlot*/
  void adviceCheckOffsetDetailsSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultOffsetDetailsData);
  void unadviceHandleActiveSlot(unsigned int);                   /*!< zeitverzoegertes unadvice soll nun ausgefuehrt werden*/

//BEGIN SUPPRESS 3.9.1.1a
signals:

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void actTrafoMaskChanged (SlMaActiveTrafoMaskEnum);         /*!< Zeigt die aktuelle Trafo Bitcodiert an*/
  void workOffsetNameChanged (const QString&);                /*!< WorkOffset Name*/
  void mirrorUsedGeoAxesNamesChanged (const QString&);        /*!< an mirror beteiligte achsen als string e.g. XY or XYZ*/
  void scaleUsedGeoAxesNamesChanged (const QString&);         /*!< an scale beteiligte achsen als string e.g. XY or XYZ*/
  void rotationUsedGeoAxesNamesChanged (const QString&);      /*!< an rotation beteiligte achsen als string e.g. XY or XYZ*/
  void isWorkOffsetMirrorActiveChanged (bool);                /*!< zeigt ob mirror activ ist*/
  void isWorkOffsetScaleActiveChanged (bool);                 /*!< zeigt ob scale activ ist*/
  void isWorkOffsetRotationActiveChanged (bool);              /*!< zeigt ob rotation activ ist*/
  void actPtcTCARRNameChanged (const QString&);               /*!< zeigt den aktuellen tool-carryer als string "TCARR" oder "TCARR=x" wenn es mehr als 1nen geben kann*/
  void actToolIdentChanged (const QString&);                  /*!< Name aktives Werkzeug geaendert*/
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private ENUMS
  ///////////////////////////////////////////////////////////////////////////
  //BEGIN SUPPRESS 3.6.2.1c 
  //rule broken! names should match to file common.nsp

enum SlMaLink_frameDynamicValuesEnum 
{
//  E_FRAME_linShift   = 0, 
//  E_FRAME_linShiftFine,
  E_FRAME_mirrorImgActive = 0,
  E_FRAME_scaleFact,
  //hier, vor E_FRAME_rotation neue ergaenzen, da E_FRAME_rotation nicht in allen NPV vorhanden ist.
  //Falls es noch weitere Elemente gibt, welche nicht immer vorhanden sind, muss das Konzept geaendert werden !!!!!!!!!!!!!!!
  E_FRAME_rotation,
  E_FRAME_DynamicValuesNumElements,
};

  //END SUPPRESS

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaAddStateInfoPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaAddStateInfo (const SlMaAddStateInfo& rCopy);
  /*! assignment operator not allowed */
  SlMaAddStateInfo& operator=(const SlMaAddStateInfo& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  void dummyAdditionalData (void);
  void adviceAdditionalData (void);
  void unadviceAdditionalData (void);
  void adviceCheckOffsetDetails (void);
  void unadviceCheckOffsetDetails (void);
  void checkOffsetDetails (void);

  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_MA_ADD_STATE_INFO_H_INCLUDED
