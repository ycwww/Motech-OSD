///////////////////////////////////////////////////////////////////////////////
/*! \file   slmamultichanhandwheel.h
 *  \author Jeyapalan Rasappah
 *  \date   13.09.2019
 *  \brief  Definition file for class SlMaMultiChanHandWheel
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2019. All rights reserved.
 */
 ///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_MULTI_CHAN_HAND_WHEEL_H_INCLUDED
#define SL_MA_MULTI_CHAN_HAND_WHEEL_H_INCLUDED


#include "slmalogic.h"
#include "slmalogicexports.h"
#include <QtCore/QObject>

class SlMaMultiChanHandWheelPrivate;

///////////////////////////////////////////////////////////////////////////////
// static const Data
///////////////////////////////////////////////////////////////////////////////
static const unsigned int S_indexHandWheel_1 = 0;
static const unsigned int S_indexHandWheel_2 = 1;
static const unsigned int S_indexHandWheel_3 = 2;

///////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////
/*! \enum defining for SlMaHandWheelFeedTypeEnum*/
enum SlMaHandWheelTypeEnum
{
   SL_MA_HANDWHEEL_GEO_AXIS_SELECT = 0x00000000,   /*!< activate a geometic axis Bit7=0*/
   SL_MA_HANDWHEEL_MACH_AXIS_SELECT = 0x00000080,   /*!< activate a machine axis Bit7=1*/
   SL_MA_HANDWHEEL_ACTIVE_ON = 0x00000040,   /*!< to set/check axis aktive Bit6=1*/
   SL_MA_HANDWHEEL_ACTIVE_OFF = 0x000000BF,   /*!< to reset axis aktive Bit6=1*/
   SL_MA_HANDWHEEL_AXES_MASK = 0x0000001F,   /*!< to mask out selected axis Bit0/1=GeoAxes Bit0-4 MachAxes*/
   SL_MA_HANDWHEEL_GEO_AXES_MASK = 0x00000003,   /*!< to mask out selected axis Bit0/1=GeoAxes */
   SL_MA_HANDWHEEL_ACTIVE_NO_CHANGE = 0x10000000,   /*!< do not change active bit */
   SL_MA_HANDWHEEL_AXIS_INDEX_NO_CHANGE = 0xFFFFFFFF,/*!< do not change axis index */
   SL_MA_HANDWHEEL_ERROR = 0xFFFFFFFF,   /*!< hand wheel status not defined Bit5=not used*/
};


// Status of the handwheel button not available, pressed or not pressed
enum SlMaHT10HandWheelButtonStateEnum
{
   SL_MA_HT10_HANDWHEEL_BUTTON_NOT_AVAILABLE = 0,
   SL_MA_HT10_HANDWHEEL_BUTTON_PRESSED = 1,
   SL_MA_HT10_HANDWHEEL_BUTTON_NOT_PRESSED = 2,
};

// request select HT10 handwheel state : Idle / select / deselect 
enum SlMaHT10HandWheelSelectRequestEnum
{
   SL_MA_HT10_HANDWHEEL_IDLE = 0,
   SL_MA_HT10_HANDWHEEL_DESELECT = 1,
   SL_MA_HT10_HANDWHEEL_SELECT = 2,
};

// type of advice call
enum SlMaAdviceTypeEnum
{
   E_AdviceOfGlobData = 0x01,  // global handwheel data
   E_AdviceOfHT10Data = 0x02,  // HT10 handwheel data
   E_AdviceInitDone   = 0x03,  // advice of global and HT10 data are initialised
};

/*! \class  SlMaMultiChanHandWheel
 *  \brief  Interface service adapter of hand wheel
 */
class SL_MA_LOGIC_EXPORT SlMaMultiChanHandWheel : public QObject
{
   Q_OBJECT

public:
   /////////////////////////////////////////////////////////////////////////////
   // static CREATORS (Singleton)
   /////////////////////////////////////////////////////////////////////////////

   /*! \fn static SlMaMultiChanHandWheel* getInstance()
    *
    *  \retval int 0 if failed, otherwise Instance Pointer
    *
    *  Delivers the Instance Pointer for Singleton SlMaNBckLogic.
    *  Is rNcuPath empty the active nck will be connected.
   */
   static SlMaMultiChanHandWheel* getInstance(void);

   /*! \fn static void releaseInstance(SlMaMultiChanHandWheel* pMultiChanHandWheelLogic)
    *
    *  \param pMultiChanHandWheelLogic:  pointer to release
    *
   */
   static void releaseInstance(SlMaMultiChanHandWheel* pMultiChanHandWheelLogic);

   ///////////////////////////////////////////////////////////////////////////
   // public ACCESSORS
   ///////////////////////////////////////////////////////////////////////////
   int getHT10HandwheelIdx(void);                                 /*!< liefert den Index des HT10 Handrads */

  /*! \fn unsigned int getHandWheelAxisAssignment(unsigned int handWheelIndex);
   *
   *  \param handWheelIndex:  Handrad-index
   *
   * gib für den handWheelIndex zugewiesene HandradAchse-Daten
  */
   unsigned int getHandWheelAxisAssignment(unsigned int handWheelIndex);

   /*! \fn unsigned int getHandWheelChanAssignment(unsigned int handWheelIndex);
    *
    *  \param handWheelIndex:  Handrad-index
    *
    * gib für den handWheelIndex zugewiesene Kanal
   */
   unsigned int getHandWheelChanAssignment(unsigned int handWheelIndex);

   /*! \fn setHandWheelAxisIndexAndActive(unsigned int handWheelIndex, unsigned int axisSelectType, unsigned int axisSelectNr, unsigned int axisSelectChannel);
    *
    *  \param handWheelIndex:  Handrad-index
    *  \param axisSelectType:  Achstyp
    *  \param axisSelectNr:  Achsnummer
    *  \param axisSelectChannel:  Kanalnummer
    *
    * Achstype, Achsnummer und Kanalnummer für Handrad-Index zuweissen
   */
   void setHandWheelAxisIndexAndActive(unsigned int handWheelIndex, unsigned int axisSelectType, unsigned int axisSelectNr, unsigned int axisSelectChannel);

   /*! \fn void setHandWheelFormLogicStarted (bool state);
    *
    *  \param state:  true --> start hotlinks else stop
    *
    *   is HandWheel Form Logic started
   */
   void setHandWheelFormLogicStarted(bool state);

   /*! \fn bool HT10WithHandwheelHasFocus(void)
    *
    *  \retval TCU HT10 whith handwheel has focus
    *
    *  returns true if HT10 with handwheel has the focus, false if not
    */
   bool HT10WithHandwheelHasFocus (void);

signals:
   ///////////////////////////////////////////////////////////////////////////
   // SIGNALS
   ///////////////////////////////////////////////////////////////////////////
   // für den Handrad zugewiesene Achse/Kanal hat sich geändert
   void handWheelAxisAssignmentChanged(unsigned int handWheelIdx, unsigned int axisAssignment, unsigned int chanAssignment);   

   /*!
    *  \fn void manyHandWheelHasSameAxisAssignedChanged(bool handWheel_1, bool handWheel_2, bool handWheel_3)
    *
    *  \param  handWheel_1   true: 1. Handradzuweisung ist mehrfach
    *  \param  handWheel_2   true: 2. Handradzuweisung ist mehrfach
    *  \param  handWheel_3   true: 3. Handradzuweisung ist mehrfach
    *
    *  mehre Handräder haben die gleiche Achse zugewiesen bekommen
    */
   void manyHandWheelHasSameAxisAssignedChanged(bool handWheel_1, bool handWheel_2, bool handWheel_3);

public slots:
   ///////////////////////////////////////////////////////////////////////////
   // public SLOTS
   ///////////////////////////////////////////////////////////////////////////
   void handWheelDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultHandWheelData);
   void HT10HandWheelDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultHandWheelData);
   void writeHandWheel1DataTimerSlot(void);
   void writeHandWheel2DataTimerSlot(void);
   void writeHandWheel3DataTimerSlot(void);
   void TCUSwitchSlot(const SlSmTcuInfo&);
   void axisSelectionChangedSlot(const QString, const long, const QVariant); // Achsanwahl ein/ausgeschaltet (z.B. Istwert-Fenster-Header) 
   void setConnStateSlot(SlMaConnectStateEnum connectState);
   void checkAndEmitAxisAssignedForManyHandWheelSlot(void);

private:

   ///////////////////////////////////////////////////////////////////////////
   // private ENUMS
   ///////////////////////////////////////////////////////////////////////////
   //BEGIN SUPPRESS 3.6.2.1c 
   //rule broken! names should match to file common.nsp

   enum SlMaLinkItemHandWheelEnum
   {
      E_PlcHandWheel_1_ChanSelect = 0,
      E_PlcHandWheel_2_ChanSelect = 1,
      E_PlcHandWheel_3_ChanSelect = 2,
      E_PlcHandWheel_1_AxisSelect = 3,
      E_PlcHandWheel_2_AxisSelect = 4,
      E_PlcHandWheel_3_AxisSelect = 5,
      //hier, vor E_HandWheelNumElements neue ergaenzen
      E_HandWheelNumElements,
   };

   enum SlMaLinkItemHT10HandWheelEnum
   {
      E_PlcHandWheel_1_Active = 0,
      E_PlcHandWheel_2_Active = 1,
      E_PlcHandWheel_3_Active = 2,
      E_requestSelectHT10Handwheel = 3,
      E_AxisSelectType_1 = 4,
      E_AxisSelectNr_1 = 5,
      // Achtung: bis 26 sind für AxisSelectType und AxisSelectNr für alle Kanäle reseviert
      E_AxisSelectTypeMax = 25,
      E_AxisSelectNrMax = 26,

      //hier, vor E_HT10HandWheelNumElements neue ergaenzen
      E_HT10HandWheelNumElements,
   };

   // /Hmi/HT10HandwheelButtonState;0;2;0;10;10;;3;;7;;;;
   // Status of the handwheel button not available, pressed or not pressed
   // Values : 0 = "button not available"
   //          1 = "button pressed"
   //          2 = "button not pressed"
   void writeHT10HandwheelButtonStateCAP(unsigned int state);
   // schreibe die Handrad-Aktivierung in der PLC (OEM kann die Freigabe ändern)
   void writeHandwheelButtonStatePLC(bool bHandwheelActive);
   // initialisiere HT10-Handrad
   void initHT10Handwheel(void);
   // zu HT10 zugewiesen Handrad-nummer holen
   long getHT10HandwheelAssignmentNumber(void);
   // Achsen zu Handrad setzen und Button updaten
   void setHT10HandWheelAxisAndButton(unsigned int handWheelIndex, bool State, bool* pbHT10HandWheelActivateDone);
   // ist ein HT10 Handrad in der PLC freigegeben (Aktiv)
   bool isHT10HandWheelInPlcApproved(void);
   // ist Achsanwahl aktiv (Auf den Header)
   bool isAxisSelectionActive(void) const;
   unsigned int buildAxisAssignment(unsigned int axisSelectType, unsigned int axisSelectNr);
   SlCapErrorEnum writeHandwheel_1_AxisAssignment(unsigned int newAxisAssignment, unsigned int nChannel);  // für die 1.Handrad die Daten in der PLC schreiben
   SlCapErrorEnum writeHandwheel_2_AxisAssignment(unsigned int newAxisAssignment, unsigned int nChannel);  // für die 2.Handrad die Daten in der PLC schreiben
   SlCapErrorEnum writeHandwheel_3_AxisAssignment(unsigned int newAxisAssignment, unsigned int nChannel);  // für die 3.Handrad die Daten in der PLC schreiben

   // behandle geänderte plc-Daten
   void handelHandWheelData(const QVector<SlCapAdviseResultType>& adviseResultHandWheelData, SlMaAdviceTypeEnum adviceType);

   void adviceHandWheelData(void); //HotLinks via Cap einrichten (allgemein Handrad Daten)
   void unadviceHandWheelData(void);  //HotLinks via Cap abmelden (allgemein Handrad Daten)
   void adviceHT10HandWheelData(void); //HotLinks via Cap einrichten (HT10 Handrad Daten)
   void unadviceHT10HandWheelData(void); //HotLinks via Cap abmelden (HT10 Handrad Daten)

   // soll die HT10 verzögert ausgeschaltet werden? hier die HotLinks abmelden 
   void handelHT10HandWheelDisConnect(void);
   // ist Achsanwahl für ein Kanal sich geändert
   bool isAxisSelectChanged(const QVector<SlCapAdviseResultType>& adviseResultHandWheelData);

   ///////////////////////////////////////////////////////////////////////////
   // private MEMBERS
   ///////////////////////////////////////////////////////////////////////////
   SlMaMultiChanHandWheelPrivate* m_pData; // d-pointer
   SlMaLogic*                     m_pLogic; // pointer to logic object

   static SlMaMultiChanHandWheel* S_pInstance;
   static int S_iInstanceCounter;

   /////////////////////////////////////////////////////////////////////////////
   // private CREATORS (Singleton)
   /////////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaMultiChanHandWheel (QObject* pParent = 0);
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
   SlMaMultiChanHandWheel(QObject* pParent = 0);

   /*! \fn ~SlMaMultiChanHandWheel ();
    *
    *  destructor
   */
   virtual ~SlMaMultiChanHandWheel();
};

#endif // SL_MA_MULTI_CHAN_HAND_WHEEL_H_INCLUDED
