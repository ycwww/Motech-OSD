///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaactblock.h
 *  \author Harald Vieten/Guenter Ruebig/Michael Hoseus
 *  \date   25.01.2005
 *  \brief  Definition file for class SlMaActBlock
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2014. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_ACT_BLOCK_H_INCLUDED
#define SL_MA_ACT_BLOCK_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmachanlogic.h"
#include "slmalogicexports.h"

class SlMaActBlockPrivate;


/*! \enum SlMaBlockStyleEnum
 *
 *  styles of act block editor
 */
enum SlMaBlockStyleEnum
{
  SL_MA_BLOCK_STYLE_3SHORT = 0,            /*!< 3 blocks max 66 char*/
  SL_MA_BLOCK_STYLE_3LONG = 1,             /*!< 3 blocks max 198 char*/
  SL_MA_BLOCK_STYLE_7LONG = 2,             /*!< 7 blocks max 512 char*/
  SL_MA_BLOCK_STYLE_EDITOR = 3,            /*!< whole screen*/
  SL_MA_BLOCK_STYLE_ABSOLUTE = 4           /*!< absolute basic blocks max 198 char*/
};

 /*! \enum defining for SlMaProgTypeEnum*/
enum SlMaProgTypeEnum
{
   SL_MA_PROG_TYPE_NCK = 0,                /*!< prog type is nck intern*/
   SL_MA_PROG_TYPE_EXT = 1,                /*!< prog type is extmode or extcall*/
   SL_MA_PROG_TYPE_EES = 2,                /*!< prog type is execution from external storage EES*/
};

typedef struct
{
  long seekCorr;          //! number of the current NC block
  long seekw;             //! number of the first writable NC block
  qint64 seekwb;          //! offset of the first writable NC block
  long error;             //! error value
  QString strPath;        //! path of the NC-file from correction window
  QString strName;        //! name of the NC-file from correction window
} corrBlockType;

// Programm in einem anderen Kanal aktiv
static const qint64 SL_MA_PROG_IN_OTHER_CHANNEL_ACTIVE = 99999999;

/////////////////////////////////////////////////////////////////////////////
/*! \class  SlMaActBlock
 *  \brief  Interface service adapter of act block run
 */
class SL_MA_LOGIC_EXPORT SlMaActBlock : public SlMaFormLogicBase
{
  Q_OBJECT
  Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaConnectStateEnum)
  Q_ENUMS(SlMaChanStateEnum)
  Q_ENUMS(SlMaProgInfoValueTypeEnum)
  
public:
  ///////////////////////////////////////////////////////////////////////////
  // public CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaActBlock (const QString& rChannelPath = 0, QObject* pParent = 0);
   *  \param  rChannelPath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaActBlock (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaActBlock ();
   *
   *  destructor
  */
  virtual ~SlMaActBlock ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setActBlockStyle (SlMaBlockStyleEnum actBlockStyle); /*!< Anzeige in 3Satz kurz, lang, 7Satz, Editor*/
  long setSeekwTypeFile (const QString& rPathAndFileNameIn = QString::null); /*!< seekw offset nur von diesem file liefern, rPathAndFileNameIn = QString::null deaktiviert die file-funktion*/
  long setDeleteMdaBuffer (void);                         /*!< delete MDA buffer*/
  long setOstore (bool isOstoreOn);                   /*!< true == overstore on, false == overstore off*/
  long setNcStartLock (const QString& rPathAndFileName, bool isNcStartLock);  /*!< Lock(isNcStartLock == true) or unlock(isNcStartLock == false) file : rPathAndFileName*/
  long setGlobalNCStartLock (bool setNcStartLock);                            /*!< Lock(setNcStartLock == true) or unlock(setNcStartLock == false) file : all files, all modes (AUTO,MDA,JOG)*/
  long setModeAutoNCStartLock (bool setNcStartLock);                          /*!< Lock(setNcStartLock == true) or unlock(setNcStartLock == false) file : all files, mode AUTO only*/
  void setDrillObjectPosition (const QString& rObjectPosition); /*!< set the drill object position*/
  long readCorrBlock (int chanIndex = 0);                 /*!< read correction block*/
  long resetOldProgNetTime (void);                        /*!< Laufzeit des zuletzt abgearbeiteten Programms zuruecksetzen*/


  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  QString channelInstancePath(int nChanNr = -1);  /*!< ncu-path for connected ncu, e.g.: QString("@NCU840D/Channel//dummy[u1]"*/
  SlMaBlockStyleEnum actBlockStyle(void);         /*!< Anzeige in 3Satz kurz, lang, 7Satz, Editor*/
  bool isNcStartLock (const QString& rPathAndFileName);  /*!< test of nc-start-lock for specific program*/
  bool isGlobalStartLockActive (void);                   /*!< test of nc-start-lock for all programs*/
  bool isInputEnable (void) const;                    /*!< is input enable?*/
  bool isInputEnableFile (const QString& rPathAndFileNameIn) const;                    /*!< is input for file enable?*/
  bool isOstoreEnable (void) const;                /*!< is overstore enable?*/
  bool isOstoreOn (void) const;                    /*!< is overstore activated?*/
  bool isSblOn (void) const;                       /*!< is single block mode activated?*/
  bool isProgStateStartResetTrigger (void) const;     /*!< is last progState change from start to reset true?*/
  bool isStartLockPathAndFileNameInvalid (const QString& rPathAndFileNameIn) const;     /*!< check names /_N_MPF0 and ##_NO_LOAD as invalid*/
  bool isEESProgWithoutEESConfig (const QString& rPathAndFileNameIn = QString::null);     /*!< check names for EES use without an EES configuration. main-level prog is default*/
  SlMaAccessLevelEnum accessLevel (void) const;       /*!< shows the actual access level*/
  SlMaOpModeEnum opMode (void) const;                 /*!< operation mode (auto, jog, mda)*/
  SlMaProgStateEnum progState (void) const;           /*!< shows the actual program state*/
  QString ostoreEditorFileName (void) const;       /*!< file name to open editor for overstore funktion*/
  corrBlockType corrBlock (void);                     /*!< shows correction block. ATTENTION: call readCorrBlock() directly before*/
  /*!< ATTENTION: in state SL_MA_INIT_LOGIC(only) use with care. read funktions using single synchron read, QT-main-tread is blocked typical 10ms*/
  void resetWorkPandProgNames (void) const;           /*!< Programmnamen löschen, damit beim nächsten Zugriff frisch gelesen wird*/
  QString workPandProgNameMainLevel (void) const;     /*!< selected program*/
  QString workPandProgName (void);              /*!< current program*/
  QString workPandProgNameProgramLevel (unsigned int programLevel) const;              /*!< current program for programlevel */
  QString convertWorkPandProgName (const QString& rPathAndFileNameIn, SlGfwHmiDialog* pDialog, const QString& sArea); /*!< liefert den fuer die anzeige gewandelten string, auch bei externen programmen*/
  QString getRealPathEditor (const QString& rPathAndFileNameIn);  /*!< Provides the converted workpeace-path- and file-name for editor use*/
  QString getExtProgBufferName(const QString& rRealPathEditorIn); /*!< Provides the converted workpeace-path- and file-name for nck-buffer-access*/
  QString progWaitForEditUnlock (void) const;         /*!< program name which wait for edit unlock*/
  unsigned int corrBlActive (void);             /*!< correction block exists*/
  unsigned int extProgActive (const QString& rPathAndFileNameIn = QString::null);                  /*!< external programm selected*/
  SlMaProgTypeEnum extProgActiveType (const QString& rPathAndFileNameIn = QString::null);          /*!< external programm type*/
  unsigned int cycProgActive (const QString& rPathAndFileNameIn = QString::null);                  /*!< precompiled cycle programm selected*/
  long seekw (void) const;                            /*!< first writable line*/
  long seekwTypeFile (void);                          /*!< current seekw for file name*/
  long seekOffsetMainLevel (void) const;              /*!< seek offset main program level*/
  long seekOffsetProgramLevel (unsigned int programLevel) const; /*!< seek offset for programlevel*/
  long seekOffset (void) const;                       /*!< seek offset current program level.in state SL_MA_INIT_LOGIC nck-version 660000.0 is needed*/
  long byteOffsetMainLevel (void) const;              /*!< seek byte offset main program level*/
  long byteOffsetProgramLevel (unsigned int programLevel) const; /*!< seek byte offset for programlevel*/
  long byteOffset (void) const;                       /*!< seek byte offset current program level.in state SL_MA_INIT_LOGIC nck-version 920000.0 is needed*/
  unsigned int actProgramLevel (void) const;          /*!< actual programm level*/
  unsigned int dispProgramLevel (void) const;         /*!< displayed program level*/
  unsigned int ncStartSignalCounter(void) const;      /*!< ncStartSignalCounter value*/
  unsigned int startRejectCounter(void) const;        /*!< startRejectCounter value*/
  unsigned int ncStartLockCounter(void) const;        /*!< ncStartLockCounter value*/
  unsigned int chanStartLockState(void) const;        /*!< chanStartLockState value*/
  unsigned int nckType (void) const;                  /*!< Provides the type of the connected NC-Unit */   
  QString getDrillObjectPosition (void) const;        /*!< get the drill object position*/
  QString getMFunctionText (void) const;              /*!< get the M-Funktion-Text via MD: 10714: $MN_M_NO_FCT_EOP*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  QString blocksAsString (void) const;                /*!< a string of up to 600 char, containing an amount of unknown blocks, separated via CR and/or LF*/
  QString block_1 (void) const;                       /*!< first block*/
  QString block_2 (void) const;                       /*!< second block*/
  QString block_3 (void) const;                       /*!< third block*/
  int actBasicBlockIndex(void);                       
  QString instanceChannelName () const;               /*!< Provides the name of the instance channel. */

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void accessLevelSlot(SlMaAccessLevelEnum accessLevel);
  void chanStateSlot(SlMaChanStateEnum chanState);
  void isOstoreOnSlot(bool isOstoreOn);
  void isSblOnSlot(bool isSblOn);
  void ncStartCounterSlot(unsigned int ncStartCounterValue);
  void progStateSlot(SlMaProgStateEnum progState);
  void adviceActBlocksSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultActBlocks);
  void actBlockTimerSlot(void);
  void progStateChangedCheckDelaySlot (void);
  void executeCompleteSlot(SlCapErrorEnum, const QVector<QVariant>&, const QDateTime&);
  void pipeDataSlot(const QByteArray&, bool);
  void progInfoValueSlot (SlMaProgInfoValueTypeEnum progInfoValueIn);
  void languageChangedSlot(const QString& szLanguage);
  void adviseValuesChanExternNcuSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultChanExternNcu);
  void adviseValuesBagExternNcuSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultBagExternNcu);

signals:
  ///////////////////////////////////////////////////////////////////////////
  // public SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  /*! Signals defining */
  void progStateChanged (SlMaProgStateEnum);          /*!< new program state*/
  void opModeChanged (SlMaOpModeEnum);                /*!< new operating mode*/
  void accessLevelChanged (SlMaAccessLevelEnum);      /*!< new actual access level*/
  void actProgramLevelChanged (unsigned int);         /*!< new programm level*/
  void isOstoreOnChanged (bool);                      /*!< is overstore on state changed*/
  void isSblOnChanged (bool);                         /*!< is single block state changed*/
  void ncStartSignalCounterChanged (unsigned int);    /*!< ncstart signal counter state changed*/
  void startRejectCounterChanged (unsigned int);      /*!< startRejectCounter counter changed*/
  void ncStartLockCounterChanged (unsigned int);      /*!< ncStartLockCounter counter changed*/
  void chanStartLockStateChanged (unsigned int);      /*!< chanStartLockState state changed*/
  void blocksAsStringChanged (const QString&);        /*!< new string of up to 600 char, containing an amount of unknown blocks, separated via CR and/or LF*/
  void block_1Changed (const QString&);               /*!< new first block*/
  void block_2Changed (const QString&);               /*!< new second block*/
  void block_3Changed (const QString&);               /*!< new third block*/
  void workPandProgNameChanged (const QString&);      /*!< new current program*/
  void workPandProgNameMainLevelChanged (const QString&);      /*!< new current program MainLevel*/
  void seekwTypeFileChanged (long);                   /*!< new first writable line for file*/
  void seekwChanged (long);                           /*!< new first writable line*/
  void seekOffsetChanged (long);                      /*!< new seek offset corresponding to the current program level*/
  void seekOffsetMainLevelChanged (long);             /*!< new seek offset corresponding to the main program level*/
  void progWaitForEditUnlockChanged (const QString&); /*!< new program name which wait for edit unlock*/
  void corrBlActiveChanged (unsigned int);            /*!< correction block exists -> changed*/
  void isInputEnableChanged (bool);                   /*!< input enable state changed*/
  void isOstoreEnableChanged (bool);                  /*!< is overstore enable changed*/
  void drillObjectPositionChanged (const QString&);   /*!< new drill object position*/

private:
  static const int MCS_FUNCTION_MASK_DISP_BIT3 = 0x00000008;
  static bool s_isOstoreOn;
  static unsigned int s_dispProgramLevelBeforeOstoreOn;
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaActBlockPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaActBlock (const SlMaActBlock& rCopy);
  /*! assignment operator not allowed */
  SlMaActBlock& operator=(const SlMaActBlock& rCopy);
 
  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummyCorrBlock (void);
  void dummyActBlocks (void);
  void adviceActBlocks(void);
  void unadviceActBlocks(void);
  void adviceValuesExternNcu(void);
  void unadviceValuesExternNcu(void);

  unsigned int checkCorrBlActive(void);  //pruefen ob ein sinnvoller korrektursatz von nck gemeldet wurde
  void read3BlocksSync(void);  //wenn 7-Satz nichts liefert zur not die 3-satzanzeige mit synchronem read lesen
  QString convertQByteArray2QString(const QByteArray& data);  //damit auch sonderzeichen die mit HMI-Advance-Code-Pages erstellt wurden korrekt ausgegeben werden.
  QString checkAndEmitWorkPandProgName(bool isEmit = true);
  void initStaticValues(void);
  void initDummyValues (void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_MA_ACT_BLOCK_H_INCLUDED
