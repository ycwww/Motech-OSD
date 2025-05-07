///////////////////////////////////////////////////////////////////////////////
/*! \file   slmateachin.h
 *  \author Michael Hoseus
 *  \date   27.01.2006
 *  \brief  Definition file for class SlMaTeachIn
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2006 - 2017. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_TEACHIN_H_INCLUDED
#define SL_MA_TEACHIN_H_INCLUDED


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"
#include "slmaaxis.h"
#include "slmachanlogic.h"

/*!\enum SlMaFuncGroupEnum
 *
 *  Defines the function group which are supported by teachin in MACHINE
 */
enum SlMaFuncGroupEnum
{
  SL_MA_FUNC_GROUP_1  = 1,       // function group 1
  SL_MA_FUNC_GROUP_10 = 10,      // function group 10
  SL_MA_FUNC_GROUP_15 = 15,      // function group 15
  SL_MA_FUNC_GROUP_19 = 19,      // function group 19
  SL_MA_FUNC_GROUP_20 = 20,      // function group 20
  SL_MA_FUNC_GROUP_49 = 49       // function group 49
};

/*!\enum maTeGCodeGroup1Enum
 *
 *  Defines the index of variables for the G-Code identifiers of group 1
 */
enum maTeGCodeGroup1Enum
{
  SL_MA_G_CODE_G0 = 0,           // Eilgang G0
  SL_MA_G_CODE_G1,               // Vorschub G1
  SL_MA_G_CODE_CIP,              // Kreis mit Stuetzpunkt
  SL_MA_G_CODE_ASPLINE,          // Akima-Spline
  NUM_VAR_MA_TE_GROUP1
};

/*!\enum maTeGCodeGroup15Enum
 *
 *  Defines the index of variables for the G-Code identifiers of group 15
 */
enum maTeGCodeGroup15Enum
{
  SL_MA_G_CODE_G94 = 0,          // Linervorschub (mm/min or inch/min)
  SL_MA_G_CODE_G95,              // Umdrehungsvorschub (mm/U or inch/U)
  NUM_VAR_MA_TE_GROUP15
};

/*!\enum maTeachAxModeEnum
 *
 *  Defines the mode of function setTeachinAxes()
 */
enum maTeachAxModeEnum
{
  SL_MA_TAM_INIT = 0,             // initialize teachin mask
  SL_MA_TAM_USERDEF_ALL,          // teach all user defined axes
  SL_MA_TAM_RESET_ALL,            // reset teachin axes which will be teached
  SL_MA_TAM_SET_MOVED,            // teach moved axes
  SL_MA_TAM_SET_USERDEF,          // teach user defined axes
  SL_MA_TAM_SET_TEACHIN,          // set axes which will be teached
  SL_MA_TAM_USERDEF_ALL_AXES      // teach all user defined axes ever
};

/*!\enum maTeachModeBitEnum
 *
 *  Defines the teach mode (bit coded)
 */
enum maTeachModeBitEnum
{
  SL_MA_TMB_STANDARD = 0,         // standard teachin mode
  SL_MA_TMB_PLC_LOCK,             // teachin lockable by PLC
  SL_MA_TMB_BL_SEL_EXPLICIT,      // block select only explicit
  SL_MA_TMB_ALL_USERDEF_AXES      // teach all user-defined axes every time
};


typedef struct
{
  unsigned int  numElements;      // number of elements
  QStringList   gCodeNameList;    // name of G-Codes in the group
} funcGroupType;

class SlMaTeachInPrivate;

/////////////////////////////////////////////////////////////////////////////
/*! \class  SlMaTeachIn
 *  \brief  Interface service adapter of act block run
 */
class SL_MA_LOGIC_EXPORT SlMaTeachIn : public SlMaFormLogicBase
{
  Q_OBJECT
  Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaConnectStateEnum)
  Q_ENUMS(SlMaFuncGroupEnum)
  Q_ENUMS(maTeGCodeGroup1Enum)
  Q_ENUMS(maTeGCodeGroup15Enum)
  Q_ENUMS(maTeachAxModeEnum)

public:
  ///////////////////////////////////////////////////////////////////////////
  // public CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaTeachIn (const QString& rChannelPath = 0, QObject* pParent = 0);
   *  \param  rChannelPath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaTeachIn (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaTeachIn ();
   *
   *  destructor
  */
  virtual ~SlMaTeachIn ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  long setTeachinAxes (maTeachAxModeEnum, unsigned int = 0); //!< set the axes which will be teached
  long setLockForEdit (void);                         //!< start PI-service: Lock program start for edit
  long setSelectBlock (unsigned int);                 //!< start PI-service: Select new block for programm start
  long setAutoTeachDetect (bool);                     //!< detect the axes which will be teached automatically

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  SlMaAccessLevelEnum accessLevel (void) const;       //!< shows the actual access level
  SlMaChanStateEnum chanState (void) const;           //!< shows the actual channel state
  unsigned int instanceChanNumber (void) const;       //!< shows the actual channel number
  QString getInstanceChanPath (void) const;           //!< shows the actual channel path
  SlMaProgStateEnum progState (void) const;           //!< shows the actual program state
  SlMaOpModeEnum opMode (void) const;                 //!< shows the actual operating mode
  SlMaMachFuncEnum machFunc (void) const;             //!< shows the actual machine function

  /*! get methods, available after SL_MA_START_LOGIC*/
  bool isInputEnable (void) const;                    /*!< is input enable? shows the actual teachIn input state*/
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const;     //!< shows the actual basic length unit
  bool acPtpSup(void) const;                          //!< PTP supported
  quint32 acIwStat(void) const;                       //!< Stellungsinformation zur Aufloesung der Mehrdeutigkeiten beim kartesischen PTP-Fahren
  quint32 acIwTu(void) const;                         //!< Stellungsinformation der Achsen zur Aufloesung der Mehrdeutigkeiten beim kartesischen PTP-Fahren
  unsigned int statDisplayBase(void);           //!< Anzeigestatus fuer acIwStat
  unsigned int tuDisplayBase(void);             //!< Anzeigestatus fuer acIwTu
  QString statName(void) const;                       //!< Bezeichner für Stellungsinformation zur Aufloesung der Mehrdeutigkeiten beim kartesischen PTP-Fahren
  QString tuName(void) const;                         //!< Bezeichner für Stellungsinformation der Achsen zur Aufloesung der Mehrdeutigkeiten beim kartesischen PTP-Fahren
  QString statValue (quint32 iValue);                 //!< generate the text from value of STAT for teach-block
  QString tuValue (quint32 iValue);                   //!< generate the text from value of TURN for teach-block
  QString statText (quint32 iValue);                  //!< generate the text of STAT for teach-block
  QString tuText (quint32 iValue);                    //!< generate the text of TURN for teach-block
  unsigned int teachMode (void) const;                //!< shows the actual teach mode
  unsigned int teachinAxes (void) const;              //!< shows the axes which will be teach
  unsigned int teachableAxes (void) const;            //!< shows the teachable axes
  unsigned int userdefAxes (void) const;              //!< shows the teachable axes defined by user

  unsigned int numAxes (void) const;                  //!< shows the number of all visible axis
  unsigned int numGeoAxes (void) const;               //!< shows the number of all geometric axis
  QString axisName (unsigned int) const;              //!< shows the name of an axis
  double axisActValue (unsigned int) const;           //!< shows the actual value of an axis
  double axisActIpValue (unsigned int axisIndex);     //!< shows the actual value of an ip axis
  SlMaAxisTypeEnum axisType (unsigned int) const;     //!< shows the type of an axis
  SlMaAxisMovingDirEnum axisMovingDir (unsigned int) const; //!< shows the moving direction of an axis

  bool isSplineEnable (void) const;                         //!< checks whether splines are enabled
  bool isBlockSelImplicit (void) const;                     //!< checks whether implicit block select are enabled
  QString ipAxisName (unsigned int ipAxisIndex) const;      //!< shows the name of intermediate point axis
  QString Function (SlMaFuncGroupEnum, unsigned int) const; //!< shows the wanted function in the group
  unsigned int FunctionNum (SlMaFuncGroupEnum) const;       //!< shows the number of functions in the group
  bool plcTeachLock(void) const;                            //!< teachin locked by PLC

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void adviceMaTeachVarSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultMaEditVar);
  void axisTypeSlot (unsigned int, SlMaAxisTypeEnum);
  void axisActValueSlot(unsigned int, double);

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // public SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  //! Signals defining
  void plcTeachLockChanged (bool);                    //!< lock for teaching from PLC changed
  void chanStateChanged (SlMaChanStateEnum);          //!< new channel state
  void progStateChanged (SlMaProgStateEnum);          //!< new program state
  void opModeChanged (SlMaOpModeEnum);                //!< new operating mode
  void machFuncChanged (SlMaMachFuncEnum);            //!< new sub-operation mode (refpoint repos teach...)
  void accessLevelChanged (SlMaAccessLevelEnum);      //!< new actual access level

  void axisNameChanged (unsigned int, const QString&) const;      //!< new name of an axis
  void axisActValueChanged (unsigned int, double);                //!< new actual value
  void acPtpSupChanged(bool);                                     //!< cartesian point-to-point support changed
  void acIwStatChanged(quint32);                                  //!< actual status of machine changed
  void acIwTuChanged(quint32);                                    //!< actual status of channel axes changed
  void axisTypeChanged (unsigned int, SlMaAxisTypeEnum);          //!< new type of an axis
  void axisMovingDirChanged (unsigned int, SlMaAxisMovingDirEnum);//!< new moving direction

  void teachinAxesChanged (unsigned int);                         //!< axes, which will be teach, changed
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaTeachInPrivate* m_pData;  // localLogic-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaTeachIn (const SlMaTeachIn& rCopy);
  /*! assignment operator not allowed */
  SlMaTeachIn& operator=(const SlMaTeachIn& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void adviceMaTeachVar   (void);
  void unadviceMaTeachVar (void);

  void dummyTeachIn       (void);
  long readNckMachineData (void);
  long readGCodeNames     (void);
  long readGCodeGroup     (SlMaFuncGroupEnum, funcGroupType *);
  long readGCodeGroupList (SlMaFuncGroupEnum, funcGroupType *,const unsigned int []);

  void initStaticValues(void);
  void initDummyValues (void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};
#endif // SL_MA_TEACHIN_H_INCLUDED
