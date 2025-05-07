///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaactfeedrate.h
 *  \author Harald Vieten
 *  \date   18.11.2004
 *  \brief  Definition file for class SlMaActFeedrate
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_ACT_FEEDRATE_H_INCLUDED
#define SL_MA_ACT_FEEDRATE_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"


class SlMaActFeedratePrivate;


  ///////////////////////////////////////////////////////////////////////////
  // global ENUMS
  ///////////////////////////////////////////////////////////////////////////
enum SlMaFeedrateUnitsEnum 
{
   SL_MA_MM_PER_MIN     = 0,    //!< unit mm/min, 0 mm/min
   SL_MA_MM_PER_REV     = 1,    //!< unit mm/rev, 1 mm/U
   SL_MA_INCH_PER_MIN   = 2,    //!< unit inch/min, 2 inch/min
   SL_MA_INCH_PER_REV   = 3,    //!< unit inch/rev, 3 inch/U
   SL_MA_MM_PER_TOOTH   = 11,    //!< unit mm/tooth, 11 mm/Zahn
   SL_MA_INCH_PER_TOOTH = 33,    //!< unit inch/tooth, 33 inch/Zahn
   SL_MA_DEGREE_PER_MIN = 128,    //!< unit degree/min, grad/min, Wert kommt nicht von nck, wird im hmi generiert
   SL_MA_REEDRATE_ERROR = -1,    //!< wert ist ungueltig
};


/*! \class  SlMaActFeedrate
 *  \brief  Interface service adapter of act feedrate
 */
class SL_MA_LOGIC_EXPORT SlMaActFeedrate : public SlMaFormLogicBase
{
   Q_OBJECT

   Q_ENUMS(SlCapErrorEnum)
   Q_ENUMS(SlMaConnectStateEnum)
   Q_ENUMS(SlMaChanStateEnum)
   Q_ENUMS(SlMaFeedrateUnitsEnum)
   Q_ENUMS(SlMaOpModeEnum)

public:

  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
   
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaActFeedrate (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor of SlMaActFeedrate
  */
  SlMaActFeedrate (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaActFeedrate ();
   *
   *  destructor
  */
  virtual ~SlMaActFeedrate ();


  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  void setFeedPerTooth (bool isFeedPerTooth);  //!< set a new state for feed per tooth

  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  double actFeedrate (void) ;                       //!< feedrate as double value
  double cmdFeedrate (void) ;                       //!< command feedrate as double value
  double actMaxAxesFeedrate (void) const;           //!< maximum axes feedrate in jog mode as double value
  double override (void) const;                     //!< axes override as double value
  SlMaFeedrateUnitsEnum unit (void) const;          //!< feedrate unit as SlMaFeedrateUnitsEnum value
  bool isRapidFeedActive (void) const;              //!< rapid feedrate as boolean
  bool isActive (void) const;                       //!< feedrate active state as boolean
  bool isLocked (void) const;                       //!< feedrate locked state as boolean
  unsigned int masterAxisIndex(unsigned int axisIndex=SL_MA_MAX_NUM_AXIS_IN_NCU) const; //!< 0 < value is md-index of the master axis for a slave axis, 0 == value means axis is not a slave-axis

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void chanStateSlot(SlMaChanStateEnum chanState);
  void opModeSlot(SlMaOpModeEnum opMode);
  void progStateSlot(SlMaProgStateEnum progState);
  void coordinateSystemSlot(SlMaCoordinateSystemEnum coordinateSystem);
  void adviceActFeedrateSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultActFeedrate);
  void adviceActFeedrateAxesSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultActFeedrateAxes);
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);
  void unadviceHandleActiveSlot(unsigned int);                   /*!< zeitverzoegertes unadvice soll nun ausgefuehrt werden*/


//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void actFeedrateChanged (double);                 //!< feedrate as a double value
  void cmdFeedrateChanged (double);                 //!< commanded feedrate as a double value
  void actMaxAxesFeedrateChanged (double);          //!< maximum axis feedrate in jog mode as a double value
  void overrideChanged (double);                    //!< override as a double value
  void unitChanged (SlMaFeedrateUnitsEnum);         //!< feedrate unit as SlMaFeedrateUnitsEnum value
  void rapidFeedActiveChanged (bool);               //!< rapid feed acive state as a bool
  void activeChanged (bool);                        //!< active (chan not in reset) state as a bool
  void lockedChanged (bool);                        //!< feedStopActive state as a bool

//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
//BEGIN SUPPRESS 3.6.2.1c 
//rule broken! names should match to file common.nsp

   enum SlMaLinkItemFeedRateEnum 
   {
      E_actFeedRateIpo   = 0,
      E_cmdFeedRateIpo   = 1,
      E_feedRateIpoUnit  = 2,
      E_feedRateIpoOvr   = 3,
      E_rapFeedRateOvr   = 4,
      E_rapFeedRateOvrActive = 5,
      E_feedStopActive   = 6,
      E_actIpoType       = 7,
      E_wksAxisFeedRateOvr  = 8,
      E_ncFkt2               = 9,
      E_ncFkt15               = 10,
      E_acFZ                = 11,
      E_actFeedRateTechIpo  = 12,
      E_acTrafo             = 13,
      //hier, vor E_FeedNumElements neue ergaenzen
      E_FeedNumElements,
   };

   enum SlMaLinkItemFeedRateAxesEnum 
   {
      E_maAxisCmdFeedRate       = 0,
      E_maAxisActFeedRate       = 1,
      E_maAxisCmdFeedRateIpo    = 2,
      E_maAxisActFeedRateIpo    = 3,
      E_maAxisFeedRateIpoUnit   = 4,
      E_axisActiveInChan        = 5,
      E_status                  = 6,
      E_feedRateOvr             = 7,
      //hier, vor E_FeedRateAxesNumElements neue ergaenzen
      E_FeedRateAxesNumElements,
   };
//END SUPPRESS
   
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaActFeedratePrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaActFeedrate (const SlMaActFeedrate& rCopy);
  /*! assignment operator not allowed */
  SlMaActFeedrate& operator=(const SlMaActFeedrate& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummyActFeedrate (void);
  void suspendActFeedrate (void);
  void adviceActFeedrate(void);
  void unadviceActFeedrate(void);
  void dummyActFeedrateAxes(void);
  void suspendActFeedrateAxes (void);
  void adviceActFeedrateAxes(void);
  void unadviceActFeedrateAxes(void);

  void refreshFeedrateValues(bool isEmit = true);
  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_MA_ACT_FEEDRATE_H_INCLUDED
