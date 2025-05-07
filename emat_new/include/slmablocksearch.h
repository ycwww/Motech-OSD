///////////////////////////////////////////////////////////////////////////////
/*! \file   slmablocksearch.h
 *  \author Guenter Ruebig
 *  \date   02.11.2005
 *  \brief  Definition file for class SlMaBlockSearch
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005 - 2013. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_BLOCK_SEARCH_H_INCLUDED
#define SL_MA_BLOCK_SEARCH_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"
#include "slmaconfig.h"

class SlMaBlockSearchPrivate;

 /*! \enum defining for SlMaBlockSearchModeEnum*/
enum SlMaBlockSearchModeEnum 
{
  SL_MA_SEARCH_MODE_PROGRAM             = 0,   /*!< block search uses program view*/
  SL_MA_SEARCH_MODE_POINTER             = 1,   /*!< block search uses pointer view*/
};

 /*! \enum defining for SlMaBlockSearchCalculationTypeEnum*/
enum SlMaBlockSearchCalculationTypeEnum 
{
  SL_MA_SEARCH_CALC_SKIP_EXTCALL_FLAG   = 0x10000000,   /*!< block search with skipped extcall programms is set*/
  SL_MA_SEARCH_CALC_WITHOUT             = 1,   /*!< block search without calculation, only main program*/
  SL_MA_SEARCH_CALC_BLOCK_CONTOUR       = 2,   /*!< block search with start position contour*/
  SL_MA_SEARCH_CALC_BLOCK_END           = 4,   /*!< block search with start position block end*/
  SL_MA_SEARCH_SERUPRO_BLOCK_CONTOUR    = 5,   /*!< block search with SERUPRO test run*/
  SL_MA_SEARCH_SERUPRO_BLOCK_END        = 6,   /*!< block search with SERUPRO test run and start position block end */
  SL_MA_SEARCH_CALC_ERROR               = -1
};

/*! \enum defining for SlMaBlockSearchTypeEnum*/
enum SlMaBlockSearchTypeEnum 
{
  SL_MA_SEARCH_TYPE_NONE = 0,           /*!< search type not selected*/
  SL_MA_SEARCH_TYPE_BLOCK_NR = 1,       /*!< search type block number, e.g. N100*/
  SL_MA_SEARCH_TYPE_LABEL = 2,          /*!< search type label*/
  SL_MA_SEARCH_TYPE_STRING = 3,         /*!< search type string*/
  SL_MA_SEARCH_TYPE_PROG_NAME = 4,      /*!< search type program name*/
  SL_MA_SEARCH_TYPE_LINE_NR = 5,        /*!< search type line number, e.g. 123*/
};


const unsigned int MAX_NUM_PROGRAM_LEVEL = 12;
const unsigned int MAX_NUM_PROGRAM_LEVEL_NEW = 20;  //nck ab 690000 koennen bis zu 20 up-ebenen haben
const unsigned int NUM_ASUP_PROGRAM_LEVEL = 2;    //nck ab 690000 2 up-ebenen sind fuer asups reserviert
const unsigned int BLOCK_SEARCH_DIRECTION_FORWARD = 2;
const unsigned int BLOCK_SEARCH_DIRECTION_BACKWARD = 1;

/*! \class  SlMaBlockSearch
 *  \brief  Interface service adapter of block search
 */
class SL_MA_LOGIC_EXPORT SlMaBlockSearch : public SlMaFormLogicBase
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(SlMaChanStateEnum)
	Q_ENUMS(SlMaAccessLevelEnum)
  Q_ENUMS(SlMaBlockSearchCalculationTypeEnum)
  Q_ENUMS(SlMaBlockSearchTypeEnum)
  Q_ENUMS(SlMaBlockSearchStateEnum)
  Q_ENUMS(SlMaProgStateEnum)

public:

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaBlockSearch (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaBlockSearch (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaBlockSearch ();
   *
   *  destructor
  */
  virtual ~SlMaBlockSearch ();


  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////

  /*! set methods */
  long setSeruproMasterChanNo (unsigned int seruproMasterChanNo = 0);  /*!< set master channel for SERUPRO search type: Parameter: channel number 1...MaxChannelNum, 0 == channel is master channel*/
  long setBlockSearchMode (SlMaBlockSearchModeEnum searchMode);  /*!< set block search mode: Parameter: SlMaBlockSearchModeEnum*/
  long setActivateBlockSearch (SlMaBlockSearchCalculationTypeEnum calculationType);  /*!< activate block search: Parameter: SlMaBlockSearchCalculationTypeEnum*/
  long setCleanUpSearchPointer (unsigned int progLevel = MAX_NUM_PROGRAM_LEVEL_NEW);   /*!< clean up search pointer: Parameter: MAX_NUM_PROGRAM_LEVEL_NEW cleans every level, 0...18 cleans specific level*/
  long setLoadInterruptSearchPointer (void);    /*!< load interrupt search pointer*/

  long setForward (unsigned int progLevel, unsigned int forward);                  /*!< search direction for each level, default:BLOCK_SEARCH_DIRECTION_FORWARD*/
  long setInvocCount (unsigned int progLevel, unsigned int invocCount);            /*!< invocation count for each level*/
  long setProgName (unsigned int progLevel, const QString& rProgName);             /*!< program name for each level*/
  long setSearchString (unsigned int progLevel, const QString& rSearchString);     /*!< search string ore specifier for each level*/
  long setSearchType (unsigned int progLevel, SlMaBlockSearchTypeEnum searchType); /*!< search type for each level*/
  long setSeekOffset (unsigned int progLevel, unsigned int seekOffset);            /*!< seek offset line number for each level*/
  long setWorkPName (unsigned int progLevel, const QString& rWorkPName);           /*!< directory name for each level*/

  long setGUDValue (const QString& rszGUDName, const QVariant& rvGUDValue/*in*/, SlMaGUDTypeEnum GUDUnit, unsigned int chanUnit = 0/*0=>use instance channel*/);    /*!< set a GUD-Value by using the GUD-Name e.g. "OTTO[2]"*/
  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  long getGUDValue (const QString& rszGUDName, QVariant& rvGUDValue/*out*/, SlMaGUDTypeEnum GUDUnit, unsigned int chanUnit = 0/*0=>use instance channel*/);    /*!< get a GUD-Value by using the GUD-Name "OTTO[2]"*/
  bool isFindBlActive (void) const;                     /*!< is block search active true?*/
  SlMaBlockSearchStateEnum findBlState (void) const;    /*!< current find block status*/

  bool isInputEnable (void) const;                      /*!< is input enable?*/
  SlMaProgStateEnum progState (void) const;             /*!< shows the actual program state*/
  bool isOstoreOn(void) const;

  /*! get methods, available after SL_MA_START_LOGIC*/
  bool isInterruptSearchPointerAvailable (void) const;  /*!< is an interrupt position available: true or false*/
  bool isBlockSearchStartPossible (void);               /*!< is it possible to start block search, e.g. only in chan reset mode: true or false*/
  bool isDryRunActive (void) const;                     /*!< when SERUPRO DRY-Run state is needed: true or false*/
  long checkActivateBlockSearch (bool forceEmit = false);             /*!< is it possible to start block search*/
  SlMaBlockSearchStateEnum blockSearchState (void) const;             /*!< block search state, equal findBlState()*/
  unsigned int numActiveProgLevel (void) const;                       /*!< shows the number of current active program levels*/
  unsigned int maxNumProgLevels (void);                               /*!< shows the number of possible program levels*/
  unsigned int forward (unsigned int progLevel) const;                /*!< search direction*/
  unsigned int invocCount (unsigned int progLevel) const;             /*!< invocation count*/
  QString progName (unsigned int progLevel) const;                    /*!< program name*/
  QString searchString (unsigned int progLevel) const;                /*!< search string correspondig to searchType*/
  SlMaBlockSearchTypeEnum searchType (unsigned int progLevel) const;  /*!< search type*/
  unsigned int seekOffset (unsigned int progLevel) const;             /*!< seek offset*/
  unsigned int byteOffset (unsigned int progLevel) const;             /*!< byte offset*/
  QString workPName (unsigned int progLevel) const;                   /*!< directory name*/
  QString convertWorkPandProgName (const QString& rPathAndFileNameIn, SlGfwHmiDialog* pDialog, const QString& sArea, unsigned int  progLevelIn = 0); /*!< liefert den fuer die anzeige gewandelten string, auch bei externen programmen*/
  QString getRealPathEditor (const QString& rPathAndFileNameIn, unsigned int  progLevelIn = 0);   /*!< real path in, locigal path out, for block search*/
  SlMaBlockSearchModeEnum blockSearchMode (void) const;               /*!< current selected block search Mode*/
  bool isExtProgActive (unsigned int progLevel) const;                /*!< is external program used*/
  bool isAnyExtProgActive (void);                                     /*!< at least one external programm is used*/
  bool isCycProgActive (unsigned int progLevel) const;                /*!< is precompiled cycle programm used*/
  bool isAnyCycProgActive (void);                                     /*!< at least one precompiled cycle programm used*/
  bool isProgEventActive (void);                                      /*!< after block search a prog event is activated*/
  bool isExtenedFunctionsAvailable(void);
  bool isMultiChanBlockSearchAvailable(void);                         /*!< is prog sync and act chan configured for multi channel display*/
  bool isNewShopTurnBlockSearchEnabled(void) const;                   /*!< is option set for new block search for ShopTurn SERUPRO */

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////

  void chanStateSlot(SlMaChanStateEnum chanState);                    /*!< Slot: chanStateSlot*/
  void ncStartCounterSlot(unsigned int ncStartCounter);               /*!< Slot: ncStartCounterSlot*/
  void accessLevelSlot(SlMaAccessLevelEnum accessLevel);              /*!< Slot: accessLevelSlot*/
  void extmodSearchLinesSearchingSlot(const QString&,  bool bDone, long errCode); /*!< Slot: extmodSearchLinesSearchingSlot*/
  void adviceBlockSearchDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultBlockSearchData);
  void findBlStateSlot(SlMaBlockSearchStateEnum blockSearchState);
  void findBlStateCheckDelaySlot (void);
  void blockSearchCheckDelaySlot(void);

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void progStateChanged (SlMaProgStateEnum);          /*!< new program state*/
  void isInterruptSearchPointerAvailableChanged (bool);     /*!< is an interrupt position available: true or false*/
  void isBlockSearchStartPossibleChanged (bool);            /*!< is it possible to start block search, e.g. only in chan reset mode: true or false*/
  void findBlStateChanged(SlMaBlockSearchStateEnum);        /*!< Signal: findBlStateChanged*/
  void isFindBlActiveChanged(bool);                         /*!< Signal: isFindBlActiveChanged*/
  void isInputEnableChanged (bool);                         /*!< input enable state chaneged*/
  void numActiveProgLevelChanged (unsigned int);              /*!< shows the number of current active program levels*/
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private ENUMS
  ///////////////////////////////////////////////////////////////////////////
  //BEGIN SUPPRESS 3.6.2.1c 
  //rule broken! names should match to file common.nsp

  enum SlMaLinkItemBlockSearchEnum 
  {
    E_forward       = 0,
    E_invocCount    = 1,
    E_plcStartReason= 2,
    E_progName      = 3,
    E_searchString  = 4,
    E_searchType    = 5,
    E_seekOffset    = 6,
    E_byteOffset    = 7,
    E_workPName     = 8,
    E_workPNameLong = 9,
    //hier, vor E_BlockSearchNumElements neue ergaenzen
    E_BlockSearchNumElements,
  };

  enum SlMaLinkItemBlockSearchWriteEnum 
  {
    E_forward_w       = 0,
    E_invocCount_w    = 1,
    E_plcStartReason_w= 2,
    E_progName_w      = 3,
    E_searchString_w  = 4,
    E_searchType_w    = 5,
    E_seekOffset_w    = 6,
    E_workPName_w     = 7,
    E_workPNameLong_w = 8,
    //hier, vor E_BlockSearchNumElements neue ergaenzen
    E_BlockSearchWriteNumElements,
  };
  //END SUPPRESS

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaBlockSearchPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaBlockSearch (const SlMaBlockSearch& rCopy);
  /*! assignment operator not allowed */
  SlMaBlockSearch& operator=(const SlMaBlockSearch& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void resumeBlockSearchData(void);
  void suspendBlockSearchData(void);
  void adviceBlockSearchData (void);
  void unadviceBlockSearchData (void);
  unsigned int checkMaxNumProgLevels (void);
  long checkNumUsedProgLevels (void);
  void storeSearchPointer (void);
  void restoreSearchPointer (void);
  void cleanUpSearchPointer (unsigned int progLevel);
  void readInterruptPointer (unsigned int progLevel);
  void writeSearchPointer (unsigned int progLevel);
  bool checkisAnyExtProgActive (void);                                     /*!< at least one external programm is used*/
  bool checkisAnyCycProgActive (void);                                     /*!< at least one precompiled cycle programm used*/
  void activateBlockSearchNck (void);

  void initStaticValues(void);
  void initDummyValues (void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
  bool isGroupSeruproActive(void) const;                              /*!< is group SERUPRO active */
};

#endif // SL_MA_BLOCK_SEARCH_H_INCLUDED
