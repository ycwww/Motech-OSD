///////////////////////////////////////////////////////////////////////////////
/*! \file   slmamultichanblocksearch.h
 *  \author Joachim Zapf
 *  \date   12.08.2009
 *  \brief  Definition file for class SlMaMultiChanBlockSearch
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_MULTI_CHAN_ACT_BLOCK_H_INCLUDED
#define SL_MA_MULTI_CHAN_ACT_BLOCK_H_INCLUDED

#include "slmalogicexports.h"
#include "slmamultichanlogicbase.h"
#include "slmablocksearch.h"

///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////

class SlMaBlockSearch;
class SlMaMultiChanBlockSearchPrivate;

///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////
/*! \enum defining for SlMaBlockSearchModeMaskEnum*/
enum SlMaBlockSearchModeMaskEnum 
{
  // Die folgenden Defines sind ein Abbild von dem Maschendatum $MNS_BLOCK_SEARCH_MODE_MASK_JS und $MNS_BLOCK_SEARCH_MODE_MASK_JS
  SL_MA_SEARCH_MODE_NONE                    = 0x00000000,   /*!< none available*/
  SL_MA_SEARCH_MODE_WITHOUT_APPROACH        = 0x00000001,   /*!< block search with start position block end available*/
  SL_MA_SEARCH_MODE_WITH_APPROACH           = 0x00000002,   /*!< block search with start position contour available*/
  SL_MA_SEARCH_MODE_ASK_WINDOW              = 0x00000004,   /*!< block search with defered select mask available*/
  SL_MA_SEARCH_MODE_SKIP_EXTCALL            = 0x00000008,   /*!< block search with extcall skip available*/
  SL_MA_SEARCH_MODE_WITHOUT_CALCULATING     = 0x00000010,   /*!< block search without calculation, only main program available*/
  SL_MA_SEARCH_MODE_SERUPRO_WITHOUT_APPROACH = 0x00000020,  /*!< block search with SERUPRO test run available start position block end available */
  SL_MA_SEARCH_MODE_SERUPRO_WITH_APPROACH   = 0x00000040,   /*!< block search with SERUPRO test run available with start position contour available */
  
  // Hifsdefines fuer Suchtyp mit deren Strategien
  SL_MA_SEARCH_MODE_WITH_CALCULATING       = SL_MA_SEARCH_MODE_WITHOUT_APPROACH | SL_MA_SEARCH_MODE_WITH_APPROACH,                  // mit Berechnung, mit/ohne Anfahren
  SL_MA_SEARCH_MODE_SERUPRO_TEST_RUN       = SL_MA_SEARCH_MODE_SERUPRO_WITH_APPROACH | SL_MA_SEARCH_MODE_SERUPRO_WITHOUT_APPROACH,  // mit Programmtest, mit/ohne Anfahren
  
  // Maske für alle Suchtypen
  SL_MA_SEARCH_MODE_MASK                    = SL_MA_SEARCH_MODE_WITHOUT_APPROACH   /*!< to mask out selected block search types*/
  | SL_MA_SEARCH_MODE_WITH_APPROACH
  | SL_MA_SEARCH_MODE_ASK_WINDOW
  | SL_MA_SEARCH_MODE_SKIP_EXTCALL
  | SL_MA_SEARCH_MODE_WITHOUT_CALCULATING
  | SL_MA_SEARCH_MODE_SERUPRO_TEST_RUN,
  SL_MA_SEARCH_MODE_ERROR                   = 0xFFFFFFFF,   /*!< */
};


/*! \class  SlMaMultiChanBlockSearch
 *  \brief  Block search logic for multi channel display
 */
class SL_MA_LOGIC_EXPORT SlMaMultiChanBlockSearch : public SlMaMultiChanLogicBase
{
  Q_OBJECT
  Q_ENUMS(SlMaBlockSearchCalculationTypeEnum)
  Q_ENUMS(SlMaBlockSearchStateEnum)
  Q_ENUMS(SlMaBlockSearchTypeEnum)
  Q_ENUMS(SlMaProgStateEnum)
  Q_ENUMS(SlMaConnectStateEnum)

public:
  /////////////////////////////////////////////////////////////////////////////
  // ENUMS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // static methods
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn static SlMaMultiChanBlockSearch* getInstance(void);
   *
   *  \retval int 0 if failed, otherwise Instance Pointer
   *
   *  Delivers the Instance Pointer for Singleton SlMaMultiChanBlockSearch.
  */
  static SlMaMultiChanBlockSearch* getInstance(void);

  /*! \fn static void releaseInstance(SlMaMultiChanBlockSearch *& rpInstance);
   *
   *  \param pInstance   instance to release
  */
  static void releaseInstance(SlMaMultiChanBlockSearch *& rpInstance);

  /////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual void setActive(const bool bActive = true)
   *
   *  \param bActive  activate/deactivate logic
   *
   *  Activates (starts) logics. If every activated logic is deactivated,
   *  the state of logic ist reseted
  */
  virtual void setActive(const bool bActive = true);

  /*! \fn long setSeruproMasterChanNo(const int iChanIndex, unsigned int seruproMasterChanNo = 0)
   *
   *  \param iChanIndex           channel index
   *  \param seruproMasterChanNo  channel number 1...MaxChannelNum, 0 == channel is master channel
   *
   *  \retval  Error code
   *
   *  set master channel for SERUPRO search type: Parameter: channel number 1...MaxChannelNum, 0 == channel is master channel
  */
  long setSeruproMasterChanNo(const int iChanIndex, unsigned int seruproMasterChanNo = 0);

  /*! \fn long setBlockSearchMode(const int iChanIndex, SlMaBlockSearchModeEnum searchMode)
   *
   *  \param iChanIndex           channel index
   *  \param searchMode
   *
   *  \retval  Error code
   *
   *  set block search mode: Parameter: SlMaBlockSearchModeEnum
  */
  long setBlockSearchMode(const int iChanIndex, SlMaBlockSearchModeEnum searchMode);

  /*! \fn long setActivateBlockSearch(const int iChanIndex, SlMaBlockSearchCalculationTypeEnum calculationType)
   *
   *  \param iChanIndex           channel index
   *  \param calculationType
   *
   *  \retval  Error code
   *
   *  activate block search: Parameter: SlMaBlockSearchCalculationTypeEnum
  */
  long setActivateBlockSearch(const int iChanIndex, SlMaBlockSearchCalculationTypeEnum calculationType);

  /*! \fn long setCleanUpSearchPointer(const int iChanIndex, unsigned int progLevel = MAX_NUM_PROGRAM_LEVEL_NEW)
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *
   *  \retval  Error code
   *
   *  clean up search pointer: Parameter: MAX_NUM_PROGRAM_LEVEL_NEW cleans every level, 0...18 cleans specific level
  */
  long setCleanUpSearchPointer(const int iChanIndex, unsigned int progLevel = MAX_NUM_PROGRAM_LEVEL_NEW);

  /*! \fn long setLoadInterruptSearchPointer(const int iChanIndex)
   *
   *  \param iChanIndex           channel index
   *
   *  \retval  Error code
   *
   *  load interrupt search pointer
  */
  long setLoadInterruptSearchPointer(const int iChanIndex);

  /*! \fn long setForward(const int iChanIndex, unsigned int progLevel, unsigned int forward)
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *  \param forward
   *
   *  \retval  Error code
   *
   *  search direction for each level, default:BLOCK_SEARCH_DIRECTION_FORWARD
  */
  long setForward(const int iChanIndex, unsigned int progLevel, unsigned int forward);

  /*! \fn long setInvocCount(const int iChanIndex, unsigned int progLevel, unsigned int invocCount)
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *  \param invocCount
   *
   *  \retval  Error code
   *
   *  invocation count for each level
  */
  long setInvocCount(const int iChanIndex, unsigned int progLevel, unsigned int invocCount);

  /*! \fn long setProgName(const int iChanIndex, unsigned int progLevel, const QString& rProgName)
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *  \param rProgName
   *
   *  \retval  Error code
   *
   *  program name for each level
  */
  long setProgName(const int iChanIndex, unsigned int progLevel, const QString& rProgName);

  /*! \fn long setSearchString(const int iChanIndex, unsigned int progLevel, const QString& rSearchString)
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *  \param rSearchString
   *
   *  \retval  Error code
   *
   *  search string or specifier for each level
  */
  long setSearchString(const int iChanIndex, unsigned int progLevel, const QString& rSearchString);

  /*! \fn long setSearchType(const int iChanIndex, unsigned int progLevel, SlMaBlockSearchTypeEnum searchType)
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *  \param searchType
   *
   *  \retval  Error code
   *
   *  search type for each level
  */
  long setSearchType(const int iChanIndex, unsigned int progLevel, SlMaBlockSearchTypeEnum searchType);

  /*! \fn long setSeekOffset(const int iChanIndex, unsigned int progLevel, unsigned int seekOffset)
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *  \param seekOffset
   *
   *  \retval  Error code
   *
   *  seek offset line number for each level
  */
  long setSeekOffset(const int iChanIndex, unsigned int progLevel, unsigned int seekOffset);

  /*! \fn long setWorkPName(const int iChanIndex, unsigned int progLevel, const QString& rWorkPName)
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *  \param rWorkPName
   *
   *  \retval  Error code
   *
   *  directory name for each level
  */
  long setWorkPName(const int iChanIndex, unsigned int progLevel, const QString& rWorkPName);

  /*! \fn long setGUDValue(const int iChanIndex, const QString& rszGUDName, const QVariant& rvGUDValue, SlMaGUDTypeEnum GUDUnit, unsigned int chanUnit = 0)
   *
   *  \param iChanIndex           channel index
   *  \param rszGUDName
   *  \param rvGUDValue
   *  \param GUDUnit
   *  \param chanUnit             0 => use instance channel
   *
   *  \retval  Error code
   *
   *  set a GUD-Value by using the GUD-Name e.g. "OTTO[2]"
  */
  long setGUDValue(const int iChanIndex, const QString& rszGUDName, const QVariant& rvGUDValue, SlMaGUDTypeEnum GUDUnit, unsigned int chanUnit = 0);

    /////////////////////////////////////////////////////////////////////////////
  // public ACCESSORS   (available after SL_MA_INIT_LOGIC)
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn int chanIndexOfLogicIndex(const int iLogicIndex)
   *
   *  \retval
   *
  */
  int chanIndexOfLogicIndex(const int iLogicIndex);

  /*! \fn int numChannelsSelectedForBlockSearch(void)
   *
   *  \retval
   *
   *  number of channels wich are selected for block search
  */
  int numChannelsSelectedForBlockSearch(void);

  /*! \fn SlMaBlockSearchModeEnum blockSearchMode(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  current selected block search Mode
  */
  SlMaBlockSearchModeEnum blockSearchMode(const int iChanIndex) const;

  /*! \fn long getGUDValue(const int iChanIndex, const QString& rszGUDName, QVariant& rvGUDValue, SlMaGUDTypeEnum GUDUnit, unsigned int chanUnit = 0)
   *
   *  \param iChanIndex           channel index
   *  \param rszGUDName
   *  \param rvGUDValue
   *  \param GUDUnit
   *  \param chanUnit             0 => use instance channel
   *
   *  \retval  Error code
   *
   *  get a GUD-Value by using the GUD-Name "OTTO[2]"
  */
  long getGUDValue(const int iChanIndex, const QString& rszGUDName, QVariant& rvGUDValue, SlMaGUDTypeEnum GUDUnit, unsigned int chanUnit = 0);

  /*! \fn bool isFindBlActive(const int iChanIndex) const;
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  is block search active true
  */
  bool isFindBlActive(const int iChanIndex) const;

  /*! \fn SlMaBlockSearchStateEnum findBlState(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  current find block status
  */
  SlMaBlockSearchStateEnum findBlState(const int iChanIndex) const;

  /*! \fn unsigned int blockSearchModeMask() const
   *
   *  \retval
   *
   *  mask of available block search modes
  */
  unsigned int blockSearchModeMask() const;

  /*! \fn unsigned int blockSearchModeMaskForJobShop() const
   *
   *  \retval
   *
   *  mask of available block search modes for single jobshop programs
  */
  unsigned int blockSearchModeMaskForJobShop() const;

  /*! \fn bool isInputEnable(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  is input enable?
  */
  bool isInputEnable(const int iChanIndex) const;

  /*! \fn SlMaOpModeEnum opMode(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  shows the actual op mode
  */
  SlMaOpModeEnum opMode(const int iChanIndex) const;

  /*! \fn bool isOstoreOn(const int iChanIndex) const
   *
   *  \retval bool isOstoreOn
   *
   *  Provides the overstore active state for the connected channel.
  */
  bool isOstoreOn(const int iChanIndex) const;

  /*! \fn SlMaProgStateEnum progState(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  shows the actual program state
  */
  SlMaProgStateEnum progState(const int iChanIndex) const;

  /*! \fn  bool isInterruptSearchPointerAvailable(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  is an interrupt position available: true or false
  */
  bool isInterruptSearchPointerAvailable(const int iChanIndex) const;

  /*! \fn   bool isBlockSearchStartPossible(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  is it possible to start block search, e.g. only in chan reset mode: true or false
  */
  bool isBlockSearchStartPossible(const int iChanIndex) const ;

  /*! \fn   bool isDryRunActive(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  is dry run active
  */
  bool isDryRunActive(const int iChanIndex) const;

  /*! \fn   long checkActivateBlockSearch(const int iChanIndex, bool forceEmit = false)
   *
   *  \param iChanIndex           channel index
   *  \param forceEmit
   *
   *  \retval
   *
   *  is it possible to start block search
  */
  long checkActivateBlockSearch(const int iChanIndex, bool forceEmit = false);

  /*! \fn  SlMaBlockSearchStateEnum blockSearchState(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  block search state, equal findBlState()
  */
  SlMaBlockSearchStateEnum blockSearchState(const int iChanIndex) const;

  /*! \fn  unsigned int numActiveProgLevel(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  shows the number of current active program levels
  */
  unsigned int numActiveProgLevel(const int iChanIndex) const;

  /*! \fn  unsigned int maxNumProgLevels(const int iChanIndex)
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  shows the number of possible program levels
  */
  unsigned int maxNumProgLevels(const int iChanIndex);

  /*! \fn  unsigned int forward(const int iChanIndex, unsigned int progLevel) const
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *
   *  \retval
   *
   *  search direction
  */
  unsigned int forward(const int iChanIndex, unsigned int progLevel) const;

  /*! \fn  unsigned int invocCount(const int iChanIndex, unsigned int progLevel) const
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *
   *  \retval
   *
   *  invocation count
  */
  unsigned int invocCount(const int iChanIndex, unsigned int progLevel) const;

  /*! \fn  QString progName(const int iChanIndex, unsigned int progLevel) const
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *
   *  \retval
   *
   *  program name
  */
  QString progName(const int iChanIndex, unsigned int progLevel) const;

  /*! \fn  QString searchString(const int iChanIndex, unsigned int progLevel) const
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *
   *  \retval
   *
   *  search string correspondig to searchType
  */
  QString searchString(const int iChanIndex, unsigned int progLevel) const;
 
  /*! \fn  SlMaBlockSearchTypeEnum searchType(const int iChanIndex, unsigned int progLevel) const
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *
   *  \retval
   *
   *  search type
  */
  SlMaBlockSearchTypeEnum searchType(const int iChanIndex, unsigned int progLevel) const;

  /*! \fn  unsigned int seekOffset(const int iChanIndex, unsigned int progLevel) const
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *
   *  \retval
   *
   *  seek offset
  */
  unsigned int seekOffset(const int iChanIndex, unsigned int progLevel) const;

  /*! \fn  QString workPName(const int iChanIndex, unsigned int progLevel) const
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *
   *  \retval
   *
   *  directory name
  */
  QString workPName(const int iChanIndex, unsigned int progLevel) const;

  /*! \fn  QString convertWorkPandProgName(const int iChanIndex, const QString& rPathAndFileNameIn, SlGfwHmiDialog* pDialog, const QString& sArea, unsigned int  progLevelIn = 0);
   *
   *  \param iChanIndex           channel index
   *  \param rPathAndFileNameIn
   *  \param pDialog
   *  \param sArea
   *  \param progLevelIn
   *
   *  \retval
   *
   *  liefert den fuer die anzeige gewandelten string, auch bei externen programmen
  */
  QString convertWorkPandProgName(const int iChanIndex, const QString& rPathAndFileNameIn, SlGfwHmiDialog* pDialog, const QString& sArea, unsigned int progLevelIn = 0);

  /*! \fn  QString getRealPathEditor(const int iChanIndex, const QString& rPathAndFileNameIn, unsigned int progLevelIn = 0)
   *
   *  \param iChanIndex           channel index
   *  \param rPathAndFileNameIn
   *  \param progLevelIn
   *
   *  \retval
   *
   *  real path in, locigal path out, for block search
  */
  QString getRealPathEditor(const int iChanIndex, const QString& rPathAndFileNameIn, unsigned int progLevelIn = 0);

  /*! \fn  bool isExtProgActive(const int iChanIndex, unsigned int progLevel) const
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *
   *  \retval
   *
   *  is external program used
  */
  bool isExtProgActive(const int iChanIndex, unsigned int progLevel) const;

  /*! \fn  bool isAnyExtProgActive(const int iChanIndex)
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  at least one external programm is used
  */
  bool isAnyExtProgActive(const int iChanIndex);

  /*! \fn  bool isCycProgActive(const int iChanIndex, unsigned int progLevel) const
   *
   *  \param iChanIndex           channel index
   *  \param progLevel
   *
   *  \retval
   *
   *  is precompiled cycle programm used
  */
  bool isCycProgActive(const int iChanIndex, unsigned int progLevel) const;

  /*! \fn  bool isAnyCycProgActive(const int iChanIndex)
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  at least one precompiled cycle programm used
  */
  bool isAnyCycProgActive(const int iChanIndex);

  /*! \fn  bool isProgEventActive(const int iChanIndex)
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  after block search a prog event is activated
  */
  bool isProgEventActive(const int iChanIndex);

  /*! \fn  bool isExtenedFunctionsAvailable(void)
   *
   *  \retval
   *
   *  is option "extendes functions" available
  */
  bool isExtenedFunctionsAvailable(void);

  /*! \fn  bool isMultiChanBlockSearchAvailable(void)
   *
   *  \retval
   *
   *  is prog sync and act chan configured for multi channel display
  */
  bool isMultiChanBlockSearchAvailable(void);

  /*! \fn SlMaBlockSearch *blockSearchLogic(const int iChanIndex) const
   *
   *  \param iChanIndex   channel index
   *
   *  \retval  pointer to block search logic
   *
   *  Returns the pointer to the block search logic of the given channel index
  */
  SlMaBlockSearch *blockSearchLogic(const int iChanIndex) const;

  /*! \fn long setSearchMode(SlMaConfigBsmTypeEnum searchType, SlMaConfigBsmStrategyEnum calcuSearchStrategy,
                             SlMaConfigBsmStrategyEnum progTestSearchStrategy, bool isSingleJobShopActive)
   *
   *  \param   searchType              new search type
   *  \param   calcuSearchStrategy     new search strategy for with calculated
   *  \param   progTestSearchStrategy  new search strategy for with program test
   *  \param   isSingleJobShopActive   is the single jobShop active
   *
   *  \retval  errorcode
   *
   *  Sets a new block search type and strategy
  */
  long setSearchMode(SlMaConfigBsmTypeEnum searchType, SlMaConfigBsmStrategyEnum calcuSearchStrategy,
                     SlMaConfigBsmStrategyEnum progTestSearchStrategy, bool isSingleJobShopActive);

  /*! \fn long searchMode(SlMaConfigBsmTypeEnum& rSearchType, SlMaConfigBsmStrategyEnum& rCalcuSearchStrategy,
                          SlMaConfigBsmStrategyEnum& rProgTestSearchStrategy, bool isSingleJobShopActive);
   *
   *  \param   rSearchType      buffer for search type
   *  \param   rCalcuSearchStrategy  buffer for search strategy with calculated
   *  \param   rProgTestSearchStrategy  buffer for search strategy with programtest
   *  \param   isSingleJobShopActive   is the single jobShop active
   *
   *  \retval  errorcode
   *
   *  Sets a new block search type and strategy
  */
  long searchMode(SlMaConfigBsmTypeEnum& rSearchType, SlMaConfigBsmStrategyEnum& rCalcuSearchStrategy,
                  SlMaConfigBsmStrategyEnum& rProgTestSearchStrategy, bool isSingleJobShopActive);

  /*! \fn bool checkSearchMode(SlMaConfigBsmTypeEnum searchType, SlMaConfigBsmStrategyEnum calcuSearchStrategy,
                               SlMaConfigBsmStrategyEnum progTestSearchStrategy, bool isSingleJobShopActive);
   *
   *  \param   searchType              search type
   *  \param   calcuSearchStrategy     search strategy for search type with calculation
   *  \param   progTestSearchStrategy  search strategy for search type with program test
   *  \param   isSingleJobShopActive   is the single jobShop active
   *
   *  \retval  boolean          true if the selected search mode is valid, else false
   *
   *  Checks if block search type and strategy are valid (enabled in the mode mask MD)
  */
  bool checkSearchMode(SlMaConfigBsmTypeEnum searchType, SlMaConfigBsmStrategyEnum calcuSearchStrategy,
                       SlMaConfigBsmStrategyEnum progTestSearchStrategy, bool isSingleJobShopActive);

  /*! \fn virtual int chanNumberOfChanIndex(const int iChanIndex)
   *
   *  \param iChanIndex  channel index
   *
   *  \retval  channel number
   *
   *  Gets the channel number with the index in the visible configured
   *  channel list is displayed.
  */
  virtual int chanNumberOfChanIndex(const int iChanIndex) const;

  /*! \fn virtual QString chanNameOfChanIndex(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  Provides the name of the instance channel.
  */
  virtual QString chanNameOfChanIndex(const int iChanIndex) const;

public slots:
  /////////////////////////////////////////////////////////////////////////////
  // public SLOTS
  /////////////////////////////////////////////////////////////////////////////

signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn void blockSearchActivated(const int iChanIndex, const bool bActive)
   *
   *  \param iChanIndex   channel index
   *  \param bActive      block search is activated
   *
   *  This signal is emitted if block search is activated or deactivated for the given channel column
  */
  void blockSearchActivated(const int, const bool);

  /*! \fn void progStateChanged(const int iChanIndex, SlMaProgStateEnum eProgramState)
   *
   *  \param iChanIndex       channel index
   *  \param eProgramState
   *
   *  new program state
  */
  void progStateChanged(const int, SlMaProgStateEnum);

  /*! \fn void isBlockSearchStartPossibleChanged(const int iChanIndex, const bool bActive)
   *
   *  \param iChanIndex   channel index
   *  \param bActive
   *
   *  is it possible to start block search, e.g. only in chan reset mode: true or false
  */
  void isBlockSearchStartPossibleChanged(const int, const bool);

  /*! \fn void isInterruptSearchPointerAvailableChanged(const int iChanIndex, const bool)
   *
   *  \param iChanIndex   channel index
   *
   *  is it possible to start block search, e.g. only in chan reset mode: true or false
  */
  void isInterruptSearchPointerAvailableChanged(const int, const bool);

  /*! \fn void findBlStateChanged(const int iChanIndex, const SlMaBlockSearchStateEnum)
   *
   *  \param iChanIndex   channel index
   *
   *  is it possible to start block search, e.g. only in chan reset mode: true or false
  */
  void findBlStateChanged(const int, const SlMaBlockSearchStateEnum);

  /*! \fn void isFindBlActiveChanged(const int iChanIndex, bool)
   *
   *  \param iChanIndex   channel index
   *
   *  Signal: isFindBlActiveChanged
  */
  void isFindBlActiveChanged(const int, bool);

  /*! \fn void isInputEnableChanged(const int iChanIndex, bool)
   *
   *  \param iChanIndex   channel index
   *
   *  input enable state chaneged
  */
  void isInputEnableChanged (const int, bool);

  /*! \fn void numActiveProgLevelChanged(const int iChanIndex, unsigned int)
   *
   *  \param iChanIndex   channel index
   *
   *  shows the number of current active program levels
  */
  void numActiveProgLevelChanged (const int, unsigned int);

  /*! \fn void searchModeChanged(unsigned int searchType, unsigned int calcuSearchStrategy, unsigned int progTestSearchStrategy);
   *
   *  \param searchType             search type (SlMaConfigBsmTypeEnum)
   *  \param calcuSearchStrategy    search strategy (SlMaConfigBsmStrategyEnum)
   *  \param progTestSearchStrategy search strategy (SlMaConfigBsmStrategyEnum)
   *
   *  This signal is emitted when the selected search mode has changed
  */
  void searchModeChanged(unsigned int searchType, unsigned int calcuSearchStrategy, unsigned int progTestSearchStrategy);

  /*! \fn void blockSearchModeMaskChanged(unsigned int uiModeMask);
   *
   *  \param uiModeMask       new mode mask
   *
   *  This signal is emitted when the search mode mask has changed 
  */
  void blockSearchModeMaskChanged(unsigned int uiModeMask);

protected:
  ///////////////////////////////////////////////////////////////////////////
  // protected Methods
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn virtual void startLogics(const bool bStart = true)
   *
   *  \param bStart   start or stop logics
   *
   *  This virtual function have to be overwritten for starting or stoping the logics.
  */
  virtual void startLogics(const bool bStart = true);

protected slots:
  /////////////////////////////////////////////////////////////////////////////
  // protected SLOTS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void setConnStateSlot(SlMaConnectStateEnum eConnState)
   *
   *  \param  eConnState   new connection state
   *
   *  Sets the new state for the CAP connection of the axes form.
   */
  virtual void setConnStateSlot(SlMaConnectStateEnum);

  /*! \fn void numDisplayedChanColsChangedSlot(const int iNumDisplayedChanCols)
   *
   *  \param iNumDisplayedChanCols   number of channel columns
   *
   *  This Signal is emitted if the number of visible channel columns is changed.
   *  This is occured by toggle between single and multi channel display, if the
   *  configuration or resolution of the screen changed.
  */
  virtual void numDisplayedChanColsChangedSlot(const int);

  /*! \fn void channelsConfiguredAsVisibleChangedSlot(void)
   *
   *  This Signal is emitted if the list of channels, configures as visible, changed.
  */
  virtual void channelsConfiguredAsVisibleChangedSlot(void);

  /*! \fn void activeChanColChangedSlot(const int iActChanCol)
   *
   *  \param iActChanCol   channel column
   *
   *  This signal is emitted if the channel column in which the data of the
   *  active channel is displayed, was changed, e.g. by channel switch.
  */
  virtual void activeChanColChangedSlot(const int);

  /*! \fn virtual void chanColChanUnitChangedSlot(const int iChanCol, const int iChanUnit)
   *
   *  \param iChanCol    channel column
   *  \param iChanUnit   channel unit
   *
   *  This signal is emitted if the assignment between channel column
   *  and channel unit changes. This means, that forms of another channel unit
   *  should be displayed in the given channel column.
  */
  virtual void chanColChanUnitChangedSlot(const int iChanCol, const int iChanUnit);

  /*! \fn virtual void chanUnitChannelNumberChangedSlot(const int iChanUnit, const int iChannelNumber)
   *
   *  \param iChanUnit        channel unit
   *  \param iChannelNumber   channel number
   *
   *  This signal is emitted if another channel should be displayed in the
   *  given channel column.
  */
  virtual void chanUnitChannelNumberChangedSlot(const int iChanUnit, const int iChannelNumber);

  /*! \fn void searchModeChangedSlot(unsigned int searchType, unsigned int calcuSearchStrategy, unsigned int progTestSearchStrategy);
   *
   *  \param searchType             search type (SlMaConfigBsmTypeEnum)
   *  \param calcuSearchStrategy    search strategy for with calculation (SlMaConfigBsmStrategyEnum)
   *  \param progTestSearchStrategy search strategy for program test (SlMaConfigBsmStrategyEnum)
   *
   *  This signal is emitted when the selected search mode has changed
  */
  void searchModeChangedSlot(unsigned int searchType, unsigned int calcuSearchStrategy, unsigned int progTestSearchStrategy);

private slots:
  /////////////////////////////////////////////////////////////////////////////
  // private SLOTS
  /////////////////////////////////////////////////////////////////////////////

private slots:
  /////////////////////////////////////////////////////////////////////////////
  // private SLOTS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void setActiveChanSlot(const QString& rsChanPath)
   *
   *  \param  rsChanPath  new channel identifier
   *
   *  Sets a new active channel for the form
   */
  void setActiveChanSlot(const QString&);

  /*! \fn void setProgStateSlot(SlMaProgStateEnum)
   *
  */
  void setProgStateSlot(SlMaProgStateEnum);

  /*! \fn void setBlockSearchStartPossibleSlot(const bool bActive)
   *
  */
  void setBlockSearchStartPossibleSlot(const bool);

  /*! \fn void setInterruptSearchPointerAvailableSlot(const bool)
   *
  */
  void setInterruptSearchPointerAvailableSlot(const bool);

  /*! \fn void setFindBlStateSlot(const SlMaBlockSearchStateEnum)
   *
  */
  void setFindBlStateSlot(const SlMaBlockSearchStateEnum);

  /*! \fn void setFindBlActiveSlot(bool)
   *
  */
  void setFindBlActiveSlot(bool);

  /*! \fn void setInputEnableSlot(bool)
   *
  */
  void setInputEnableSlot(bool);

  /*! \fn setNumActiveProgLevelSlot(unsigned int)
   *
  */
  void setNumActiveProgLevelSlot(unsigned int);

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////

  SlMaMultiChanBlockSearchPrivate *m_pData; // d-pointer

  static SlMaMultiChanBlockSearch* S_pInstance;
  static int S_iInstanceCounter;

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // private CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaMultiChanBlockSearch();
   *
   *  constructor
   */
  SlMaMultiChanBlockSearch();

  /*! \fn ~SlMaMultiChanBlockSearch();
   *
   *  destructor
   */
  virtual ~SlMaMultiChanBlockSearch();

  /*! copy constructor not allowed */
  SlMaMultiChanBlockSearch(const SlMaMultiChanBlockSearch& rCopy);
  /*! assignment operator not allowed */
  SlMaMultiChanBlockSearch& operator=(const SlMaMultiChanBlockSearch& rCopy);

  friend class SlMaMultiChanBlockSearchPrivate;

};
#endif // SL_MA_MULTI_CHAN_ACT_BLOCK_H_INCLUDED
