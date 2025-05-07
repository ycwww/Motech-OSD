///////////////////////////////////////////////////////////////////////////////
/*! \file   sldcadapter.h
 *  \author Joachim Zapf
 *  \date   25.11.2005
 *  \brief  Headerfile for class SlDcAdapter
 *
 *  This file is part of the HMI Solutionline Services.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_DC_SERVICE_ADAPTER_H)
#define SL_DC_SERVICE_ADAPTER_H

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#   pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#ifdef WIN32
#   pragma warning(push)
// 4290: C++ Exception Specification ignored, warning from ACE_THROW_SPEC
//       made by ace sources
// 4275: non dll-interface class XXX used as base for dll-interface class YYY
//       made by ace / tao sources
// 4251: class XXX needs to have dll-interface to be used by clients of struct YYY
//       made by ace / tao sources
#   pragma warning(disable : 4290 4275 4251)
#endif // WIN32
#include <QtCore/QObject>

#include "slsfwserviceadapterptr.h"
#if !defined(HMI_SOL)
#define HMI_SOL
#endif
#include "sldc.h"
#include "sldcapi.h"

#ifdef WIN32
#   pragma warning(pop)
#endif // WIN32

//*****************************************************************************
class SlDcAdapter;
/*! Smartpointer to the Serviceadapter. You should use this pointer instead of
 *  using the adapter class directly
 */
typedef SlSfwServiceAdapterPtr<SlDcAdapter> SlDcAdapterPtrType;

class ISlDcCallbackInterface;
class SlDcCallbackInterface;
class SlDcLocVarCb;


#if !defined(LINUX)
  #if defined (SL_DC_SERVICE_ADAPTER_EXPORTS)
    #define SL_DC_SERVICE_ADAPTER_EXPORT __declspec(dllexport)
  #else
    #define SL_DC_SERVICE_ADAPTER_EXPORT __declspec(dllimport)
  #endif
#else // LINUX
  #define SL_DC_SERVICE_ADAPTER_EXPORT
#endif // LINUX


/*! \class SlDcAdapter sldcadapter.h
 *  \brief gives access to the SlDcSevice
 *
 *  this class enables access to the data cache service. Instead of using this class
 *  directly, you should use SlDcAdapterPtrType.
 *
 *  \code
 *  ... fkt(...)
 *  {
 *      SlDcAdapterPtrType pSvc;
 *      ...
 *      long nValue = pSvc->addTwoAndReturn(2);
 *      ...
 *  }
 *  \endcode
 *
 *  \sa SlSfwServiceAdapterPtr
*/
class SL_DC_SERVICE_ADAPTER_EXPORT SlDcAdapter : public QObject
{
  Q_OBJECT

public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS (static)
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn static long getObject(SlDcAdapter*& rpAdapter) = 0;
   *  \param rpAdapter    a reference to the pointer to be filled with an
   *                      instance of the data cache service adapter
   *  \retval long        errorcode, if an error occured, otherwise 0
   *
   *  This static function creates a SlDcAdapter if non exists
   *  in the local process. There may only be one SlDcAdapter in the
   *  process (process singleton).
   */
  static long getObject(SlDcAdapter*& rpAdapter);

  /*! \fn static long releaseObject(SlDcAdapter* pInstance) = 0;
   *  \param pInstance pointer to the adapter
   *  \retval errorcode, if an error occured, otherwise 0
   *
   *  This static function removes a SlDcAdapter if it's the last
   *  reference in the local process.
   */
  static long releaseObject(SlDcAdapter* pInstance);


  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////

  virtual long registerLocVarChangedSink(SlDcLocVarCb *pCbObj) = 0;

  virtual long unRegisterLocVarChangedSink(SlDcLocVarCb *pCbObj) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // Btss...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcBtss_N_Y_basicLengthUnit(long& rlNcDdeLastError, long& rlAxisType, long lAxNo)
   *
   *  \param  rlNcDdeLastError:   Error-Code (out)
   *  \param  rlAxisType:         Axis type (out)
   *  \param  lAxNo:              number of axis (1 ... N_Y_maxnumGlobMachAxes) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets Value of the BTSS-Variable "N_Y_axisType".
   */
  virtual long slDcBtss_N_Y_axisType(long& rlNcDdeLastError, long& rlAxisType, long lAxNo) = 0;

  /*! \fn virtual long slDcBtss_N_Y_basicLengthUnit(long& rlNcDdeLastError, long& rlBasicLengthUnit)
   *
   *  \param  rlNcDdeLastError:   Error-Code (out)
   *  \param  rlBasicLengthUnit:  Value of "N_Y_basicLengthUnit" (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets Value of the BTSS-Variable "N_Y_basicLengthUnit".
   */
  virtual long slDcBtss_N_Y_basicLengthUnit(long& rlNcDdeLastError, long& rlBasicLengthUnit) = 0;

  /*! \fn virtual long slDcBtss_N_Y_maxnumDrives(long& rlNcDdeLastError, long& rlMaxNumDrives)
   *
   *  \param  rlNcDdeLastError:  Error-Code (out)
   *  \param  rlMaxNumDrives:    maximum number of drives (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets maximum number of drives (BTSS-Variable "N_Y_maxnumDrives").
   */
  virtual long slDcBtss_N_Y_maxnumDrives(long& rlNcDdeLastError, long& rlMaxNumDrives) = 0;

  /*! \fn virtual long slDcBtss_N_Y_maxnumGlobMachAxes(long& rlNcDdeLastError, long& rlMaxNumGlobMachAxes)
   *
   *  \param  rlNcDdeLastError:      Error-Code (out)
   *  \param  rlMaxNumGlobMachAxes:  maximum number of machine axis (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets maximum number of drives (BTSS-Variable "N_Y_maxnumGlobMachAxes").
   */
  virtual long slDcBtss_N_Y_maxnumGlobMachAxes(long& rlNcDdeLastError, long& rlMaxNumGlobMachAxes) = 0;

  /*! \fn virtual long slDcBtss_N_Y_nckType(long& rlNcDdeLastError, long& rlNckType)
   *
   *  \param  rlNcDdeLastError:  Error-Code (out)
   *  \param  rlNckType   :      Type of NCK (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the NCK-Version (BTSS-Variable "N_Y_nckVersion").
   */
  virtual long slDcBtss_N_Y_nckType(long& rlNcDdeLastError, long& rlNckType) = 0;

  /*! \fn virtual long slDcBtss_N_Y_nckVersion(long& rlNcDdeLastError, double& rdNckVersion)
   *
   *  \param  rlNcDdeLastError:  Error-Code (out)
   *  \param  rdNckVersion:      NCK-Version (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the NCK-Version (BTSS-Variable "N_Y_nckVersion").
   */
  virtual long slDcBtss_N_Y_nckVersion(long& rlNcDdeLastError, double& rdNckVersion) = 0;

  /*! \fn virtual long slDcBtss_N_Y_numChannels(long& rlNcDdeLastError, long& rlNumChannels)
   *
   *  \param  rlNcDdeLastError:  Error-Code (out)
   *  \param  rlNumChannels:     number of channels (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets number of (active) channels (BTSS-Variable "N_Y_numChannels").
   */
  virtual long slDcBtss_N_Y_numChannels(long& rlNcDdeLastError, long& rlNumChannels) = 0;

  /*! \fn virtual long slDcBtss_N_Y_numGlobMachAxes(long& rlNcDdeLastError, long& rlNumGlobMachAxes)
   *
   *  \param  rlNcDdeLastError:    Error-Code (out)
   *  \param  rlNumGlobMachAxes:   number of machine axis (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets number of drives (BTSS-Variable "N_Y_numGlobMachAxes").
   */
  virtual long slDcBtss_N_Y_numGlobMachAxes(long& rlNcDdeLastError, long& rlNumGlobMachAxes) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgAx...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgAxVb(T_CFG_AX_CFG_VB *ptAxCfgVb, long lcbAxCfgVbItem, long lAxNo)
   *
   *  \param  ptAxCfgVb:       Data structure of information about the axis (out)
   *  \param  lcbAxCfgVbItem:  Size of structur in bytes (in)
   *  \param  lAxNo            axis numer (1 ... N_Y_maxnumGlobMachAxes) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets informations about the given axis
   */
   virtual long slDcCfgAxVb(T_CFG_AX_CFG_VB *ptAxCfgVb, long lcbAxCfgVbItem, long lAxNo) = 0;

  /*! \fn virtual long slDcCfgAxAndDrvSel(long lAxNo)
   *
   *  \param  lAxNo:  number of axis to select (1 ... N_Y_maxnumGlobMachAxes) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Select the given axis and the assigned drive
   */
  virtual long slDcCfgAxAndDrvSel(long lAxNo) = 0;

  /*! \fn virtual long slDcCfgAxAndDrvSelNext(long& rlAxNo, long lAxType, long lAxClass)
   *
   *  \param  rlAxNo:    axis number (out)
   *  \param  lAxType:   axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:  axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects next axis and the assigned drive of the given axis type,
   *  axis class, drive type and gets the new axis number
   */
  virtual long slDcCfgAxAndDrvSelNext(long& rlAxNo, long lAxType, long lAxClass) = 0;

  /*! \fn virtual long slDcCfgAxAndDrvSelNextX(long& rlAxNo, long lAxType, long lAxClass, long lDrvType)
   *
   *  \param  rlAxNo:    axis number (out)
   *  \param  lAxType:   axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:  axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *  \param  lDrvType:  drive type (e.g. \ref CFG_DRV_TYPE_CMN_611D) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects next axis and the assigned drive of the given axis type,
   *  axis class, drive type and gets the new axis number
   */
  virtual long slDcCfgAxAndDrvSelNextX(long& rlAxNo, long lAxType, long lAxClass, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgAxAndDrvSelPrev(long& rlAxNo, long lAxType, long lAxClass)
   *
   *  \param  rlAxNo:    axis number (out)
   *  \param  lAxType:   axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:  axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects previous axis and the assigned drive of the given axis type,
   *  axis class, drive type and gets the new axis number
   */
  virtual long slDcCfgAxAndDrvSelPrev(long& rlAxNo, long lAxType, long lAxClass) = 0;

  /*! \fn virtual long slDcCfgAxAndDrvSelPrevX(long& rlAxNo, long lAxType, long lAxClass, long lDrvType)
   *
   *  \param  rlAxNo:    axis number (out)
   *  \param  lAxType:   axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:  axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *  \param  lDrvType:  drive type (e.g. \ref CFG_DRV_TYPE_CMN_611D) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects previous axis and the assigned drive of the given axis type,
   *  axis class, drive type and gets the new axis number
   */
  virtual long slDcCfgAxAndDrvSelPrevX(long& rlAxNo, long lAxType, long lAxClass, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgAxCnt(long& rlAxCnt, long lAxType, long lAxClass)
   *
   *  \param  rlAxCnt:   number of axis (out)
   *  \param  lAxType:   axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:  axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of axis of the given axis type,
   *  axis class and drive type
   */
  virtual long slDcCfgAxCnt(long& rlAxCnt, long lAxType, long lAxClass) = 0;

  /*! \fn virtual long slDcCfgAxCntX(long& rlAxCnt, long lAxType, long lAxClass, long lDrvType)
   *
   *  \param  rlAxCnt:   number of axis (out)
   *  \param  lAxType:   axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:  axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *  \param  lDrvType:  drive type (e.g. \ref CFG_DRV_TYPE_CMN_611D) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of axis of the given axis type,
   *  axis class and drive type
   */
  virtual long slDcCfgAxCntX(long& rlAxCnt, long lAxType, long lAxClass, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgAxNameAndSlaveIdentNoSzDrv(char **pszAxName, long& rlcbAxName, char **pszSlaveIdentNo, long& rlcbSlaveIdentNo, long lDrvNr)
   *
   *  \param  pszAxName:         String for the axis name (out)
   *  \param  rlcbAxName:        Length of axis name (Byte count)(in and out)
   *  \param  pszSlaveIdentNo:   String for the Slave-Ident-Number (out)
   *  \param  rlcbSlaveIdentNo:  Length of the String for the Slave-Ident-Number
   *                             (Byte count)(in and out)
   *  \param  lDrvNr:            Number of the drive (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the name of the assigned axis and the string of the
   *  Slave-Ident-Number-String (Format: hex, 4 digits with leading 0)
   *  of the given drive
   */
   virtual long slDcCfgAxNameAndSlaveIdentNoSzDrv(char **pszAxName, long& rlcbAxName, char **pszSlaveIdentNo, long& rlcbSlaveIdentNo, long lDrvNr) = 0;

  /*! \fn virtual long slDcCfgAxNameDrvVb(char *pszAxName, long& rlcbAxName, long lDrvNo)
   *
   *  \param  pszAxName:       String for the axis name (out)
   *  \param  rlcbAxName:      Length of axis name (Byte count)(in and out)
   *  \param  lDrvNr:          Number of the drive (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert den Namen der Achse, welcher der uebergebene Antrieb
   *  zugeordnet ist.
   */
   virtual long slDcCfgAxNameDrvVb(char *pszAxName, long& rlcbAxName, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgAxNameVb(char *psAxName, long& rlcbAxName, long lAxNo)
   *
   *  \param  psAxName:   String for the axis name (out)
   *  \param  rlcbAxName: Length of axis name (in and out)
   *  \param  lAxNo:      Axis number (1 ... N_Y_maxnumGlobMachAxes) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the name and the length of name of the given axis
   */
  virtual long slDcCfgAxNameVb(char *psAxName, long& rlcbAxName, long lAxNo) = 0;

  /*! \fn virtual long slDcCfgAxNoCheck(long lAxNo, long lAxType, long lAxClass)
   *
   *  \param  lAxNo:     Axis number (1 ... N_Y_maxnumGlobMachAxes) (in)
   *  \param  lAxType:   axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:  axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Prueft, ob die Nummer der uebergebenen Achse des uebergebenen Typs und
   *  der uebergebenen Klasse vorhanden ist.
   */
  virtual long slDcCfgAxNoCheck(long lAxNo, long lAxType, long lAxClass) = 0;

  /*! \fn virtual long slDcCfgAxNoCheckX(long lAxNo, long lAxType, long lAxClass, long lDrvType)
   *
   *  \param  lAxNo:     Axis number (1 ... N_Y_maxnumGlobMachAxes) (in)
   *  \param  lAxType:   axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:  axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *  \param  lDrvType:  drive type (e.g. \ref CFG_DRV_TYPE_CMN_611D) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Prueft, ob die Nummer der uebergebenen Achse des uebergebenen Typs,
   *  der uebergebenen Klasse und des uebergebenen Antriebstyps vorhanden ist.
   */
  virtual long slDcCfgAxNoCheckX(long lAxNo, long lAxType, long lAxClass, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgAxNoCheckIdentifierVb(long& rlAxNo, char *pszAxIdentifier, long lcbAxIdentifier, long lAxType, long lAxClass)
   *
   *  \param  rlAxNo:           Axis number (1 ... N_Y_maxnumGlobMachAxes) (out)
   *  \param  pszAxIdentifier:  Achsnummer oder Achsname (in)
   *  \param  lcbAxIdentifier:  Laenge (count byte) der Achsnummer oder des
   *                            Achsamens (in)
   *  \param  lAxType:          axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:         axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Prueft, ob die uebergebenen Achse (Nummer oder Name) des uebergebenen
   *  Typs und der uebergebenen Klasse vorhanden ist. Liefert im Erfolgsfall
   *  die Nummer der uebergebenen Achse.
   */
  virtual long slDcCfgAxNoCheckIdentifierVb(long& rlAxNo, char *pszAxIdentifier, long lcbAxIdentifier, long lAxType, long lAxClass) = 0;

  /*! \fn virtual long slDcCfgAxNoCheckIdentifierVbX(long& rlAxNo, char *pszAxIdentifier, long lcbAxIdentifier, long lAxType, long lAxClass, long lDrvType)
   *
   *  \param  rlAxNo:           Axis number (1 ... N_Y_maxnumGlobMachAxes) (out)
   *  \param  pszAxIdentifier:  Achsnummer oder Achsname (in)
   *  \param  lcbAxIdentifier:  Laenge (count byte) der Achsnummer oder des
   *                            Achsamens (in)
   *  \param  lAxType:          axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:         axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *  \param  lDrvType:         drive type (e.g. \ref CFG_DRV_TYPE_CMN_611D) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Prueft, ob die uebergebene Achse (Nummer oder Name) des uebergebenen
   *  Typs, der uebergebenen Klasse und des uebergebenen Antriebstyps vor-
   *  handen ist. Liefert im Erfolgsfall die Nummer der uebergebenen Achse.
   */
  virtual long slDcCfgAxNoCheckIdentifierVbX(long& rlAxNo, char *pszAxIdentifier, long lcbAxIdentifier, long lAxType, long lAxClass, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgAxNoDrv(long& rlAxNo, long lDrvNo)
   *
   *  \param  rlAxNo:  Axis number (out)
   *  \param  lDrvNo:  Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of the axis, which the given drive is assigned
   */
  virtual long slDcCfgAxNoDrv(long& rlAxNo, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgAxNoNext(long& rlAxNo, long lAxType, long lAxClass)
   *
   *  \param  rlAxNo:           Axis number (1 ... N_Y_maxnumGlobMachAxes) (in/out)
   *  \param  lAxType:          axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:         axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die naechste Achsnummer bezueglich rlAxNo, sofern mindestens
   *  eine Achse des uebergebenen Typs und der uebergebenen Klasse vorhanden
   *  ist, sonst 0.
   */
   virtual long slDcCfgAxNoNext(long& rlAxNo, long lAxType, long lAxClass) = 0;

  /*! \fn virtual long slDcCfgAxNoNextX(long& rlAxNo, long lAxType, long lAxClass, long lDrvType)
   *
   *  \param  rlAxNo:           Axis number (1 ... N_Y_maxnumGlobMachAxes) (in/out)
   *  \param  lAxType:          axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:         axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *  \param  lDrvType:         drive type (e.g. \ref CFG_DRV_TYPE_CMN_611D) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die naechste Achsnummer bezueglich rlAxNo, sofern mindestens
   *  eine Achse des uebergebenen Typs, der uebergebenen Klasse und des
   *  uebergebenen Antriebstyps vorhanden ist, sonst 0.
   */
  virtual long slDcCfgAxNoNextX(long& rlAxNo, long lAxType, long lAxClass, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgAxNoPrev(long& rlAxNo, long lAxType, long lAxClass)
   *
   *  \param  rlAxNo:           Axis number (1 ... N_Y_maxnumGlobMachAxes) (in/out)
   *  \param  lAxType:          axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:         axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die naechste Achsnummer bezueglich rlAxNo, sofern mindestens
   *  eine Achse des uebergebenen Typs und der uebergebenen Klasse vorhanden
   *  ist, sonst 0.
   */
  virtual long slDcCfgAxNoPrev(long& rlAxNo, long lAxType, long lAxClass) = 0;

  /*! \fn virtual long slDcCfgAxNoPrevX(long& rlAxNo, long lAxType, long lAxClass, long lDrvType)
   *
   *  \param  rlAxNo:           Axis number (1 ... N_Y_maxnumGlobMachAxes) (in/out)
   *  \param  lAxType:          axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:         axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *  \param  lDrvType:         drive type (e.g. \ref CFG_DRV_TYPE_CMN_611D) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die naechste Achsnummer bezueglich rlAxNo, sofern mindestens
   *  eine Achse des uebergebenen Typs, der uebergebenen Klasse und des
   *  uebergebenen Antriebstyps vorhanden ist, sonst 0.
   */
  virtual long slDcCfgAxNoPrevX(long& rlAxNo, long lAxType, long lAxClass, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgAxNoSel(long& rlAxNo, long lAxType, long lAxClass)
   *
   *  \param  rlAxNo:    axis number (out)
   *  \param  lAxType:   axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:  axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of the axis, which is seleceted and has the given
   *  axis type and axis class.
   */
  virtual long slDcCfgAxNoSel(long& rlAxNo, long lAxType, long lAxClass) = 0;

  /*! \fn virtual long slDcCfgAxNoSelX(long& rlAxNo, long lAxType, long lAxClass, long lDrvType)
   *
   *  \param  rlAxNo:    axis number (out)
   *  \param  lAxType:   axis type (e.g. \ref CFG_AX_TYPE_LIN) (in)
   *  \param  lAxClass:  axis class (e.g. \ref CFG_AX_CLASS_MACHINE) (in)
   *  \param  lDrvType:  drive type (e.g. \ref CFG_DRV_TYPE_CMN_611D) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of the axis, which is seleceted and has the given
   *  axis type, axis class and drive type.
   */
  virtual long slDcCfgAxNoSelX(long& rlAxNo, long lAxType, long lAxClass, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgAxNoSzDrvVb(char *pszAxNo, long& rlcbAxNo, long lDrvNo)
   *
   *  \param  pszAxNo:   string of axis number (out)
   *  \param  pwcbAxNo:  length of string of axis number
   *  \param  lDrvNo:    Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die Nummer der Achse als String, welcher der uebergebene
   *  Antrieb zugeordnet ist.
   */
  virtual long slDcCfgAxNoSzDrvVb(char *pszAxNo, long& rlcbAxNo, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgAxSel(long lAxNo)
   *
   *  \param  rlAxNo:    Axis number (1 ... N_Y_maxnumGlobMachAxes) (in/out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selektiert die uebergebene Achse (ohne den zugehoehrigen Antrieb).
   */
  virtual long slDcCfgAxSel(long lAxNo) = 0;

  /*! \fn virtual long slDcCfgAxSelOfDrvSel()
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selektiert die Achse, welcher der selektierte Antrieb zugeordnet ist.
   */
  virtual long slDcCfgAxSelOfDrvSel() = 0;

  /*! \fn virtual long slDcCfgAxType(long& rlAxType, long lAxNo)
   *
   *  \param  rlAxType:  axis type (e.g. \ref CFG_AX_TYPE_LIN) (out)
   *  \param  lAxNo      axis numer (1 ... N_Y_maxnumGlobMachAxes) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the type of the axis of the given axis number
   */
  virtual long slDcCfgAxType(long& rlAxType, long lAxNo) = 0;

  /*! \fn virtual long slDcCfgAxTypeDrv(long& rlAxType, long lDrvNo)
   *
   *  \param  rlAxType:  axis type (e.g. \ref CFG_AX_TYPE_LIN) (out)
   *  \param  lDrvNo:    Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert den Typ der Achse, welcher der uebergebene Antrieb zugeordnet ist.
   */
  virtual long slDcCfgAxTypeDrv(long& rlAxType, long lDrvNo) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // CfgBusSlave...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgBusSlaveOfDrv(long& rlBusNrBuf, long& rlSlaveAddrBuf, long lDrvNr, char *pszStationName)
   *
   *  \param  rlBusNrBuf:      Puffer fuer die Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr) des CU- bzw. CX-PROFIBUS-Slaves. [out]
   *  \param  rlSlaveAddrBuf:  Puffer fuer Adresse des CU- bzw. CX-Geraetes am PROFIBUS. [out]
   *  \param  lDrvNr:          Antriebsnummer (1 ... N_Y_maxnumDrives).
   *  \param  pszStationName:  Zeiger auf den Namen der Station, von der der Wert geliefert werden soll.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die Busnummer und die Slaveadresse des Antriebsgeraetes,
   *  dem der Antrieb mit der uebergebenen Nummer zugeordnet ist, fuer
   *  die Station mit dem uebergebenen Stationsnamen.
   */
  virtual long slDcCfgBusSlaveOfDrv(long& rlBusNrBuf, long& rlSlaveAddrBuf, long lDrvNr, char *pszStationName) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // CfgChg...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgChgCnt(long& rlChgCnt, E_CFG_CHG_CNT eCfgChgCnt, long lObjHdl)
   *
   *  \param  rlChgCnt:    Value of the change counter (number of changes of the object) (out)
   *  \param  eCfgChgCnt:  Type of the change counter (in)
   *  \param  lObjHdl:     Handle of the object, which change counter should be supplied.
   *                       If this handle is 0, the change couter of
   *                       all objects will be supplied. (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the change counter of the given object and the given type.
   *  If the type is 0, the function gets the change counter of all objects.
   *  The change counter is the number of changes of the object.
   */
  virtual long slDcCfgChgCnt(long& rlChgCnt, E_CFG_CHG_CNT eCfgChgCnt, long lObjHdl) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // CfgChn...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgChnAxConfChanAxNameTab(T_CFG_UNIT_NAME *patCfgUnitNameChanAxNamesBuf, long& rlNumChanAxNamesBuf, long lChnNo)
   *
   *  \param  patCfgUnitNameChanAxNamesBuf:   Buffer for all channel axis names (out)
   *  \param  rlNumChanAxNamesBuf: Number of channel axes.
   *                               If this parameter is 0, then this
   *                               function retrieves the number of channel axes  (in and out)
   *  \param  lChnNo:              Channel number (1 ... N_Y_maxnumChannels) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Retrieves the channel axis names of all axis assigned to the given channel
   */
  virtual long slDcCfgChnAxConfChanAxNameTab(T_CFG_UNIT_NAME *patCfgUnitNameChanAxNamesBuf, long& rlNumChanAxNamesBuf, long lChnNo) = 0;

  /*! \fn virtual long slDcCfgChnAxConfGeoAxAssignTab(DWORD* padwChanAxIndexesBuf, long& rlNumChanAxIndexesBuf, long lChnNo)
   *
   *  \param  padwChanAxIndexesBuf:  Zeiger auf den Puffer fuer die Zuordnung der Geometrieachsen
   *                                 zu den Kanalachsen (Kanalachsindizes) aller Geometrieachsen. (out)
   *  \param  rlNumChanAxIndexesBuf: Zeiger auf den Puffer fuer die Anzahl der Zuordnungen
   *                                 der Geometrieachsen zu den Kanalachsen (Kanalachsindizes), die
   *                                 der Puffer fuer die Zuordnung der Geometrieachsen zu den Kanal-
   *                                 achsen (Kanalachsindizes) aller Geometrieachsen aufnehmen kann.
   *                                 Wenn in diesem Parameter 0 uebergeben wird, liefert die Funktion
   *                                 in diesem Parameter lediglich die Anzahl aller Geometrieachsen des
   *                                 uebergebenen Kanals, andernfalls die in padwChanAxIndexesBuf
   *                                 kopierte Anzahl der Kanalachsindizes, denen die Geometrieachsen
   *                                 zugeordnet sind. (in and out)
   *  \param  lChnNo:                Channel number (1 ... N_Y_maxnumChannels) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die Zuordnung der Geometrieachsen zu den Kanalachsen
   *         (Kanalachsindizes) aller Geometrieachsen des uebergebenen Kanals.
   */
  virtual long slDcCfgChnAxConfGeoAxAssignTab(DWORD* padwChanAxIndexesBuf, long& rlNumChanAxIndexesBuf, long lChnNo) = 0;

  /*! \fn virtual long slDcCfgChnAxConfGeoAxNameTab(T_CFG_UNIT_NAME* patCfgUnitNameGeoAxNamesBuf, long& rlNumGeoAxNamesBuf, long lChnNo)
   *
   *  \param  patCfgUnitNameGeoAxNamesBuf: Zeiger auf den Puffer fuer die Zuordnung der Geometrieachsen
   *                                zu den Kanalachsen (Kanalachsindizes) aller Geometrieachsen. (out)
   *  \param  rlNumGeoAxNamesBuf:   Zeiger auf den Puffer fuer die Anzahl der Zuordnungen
   *                                der Geometrieachsen zu den Kanalachsen (Kanalachsindizes), die
   *                                der Puffer fuer die Zuordnung der Geometrieachsen zu den Kanal-
   *                                achsen (Kanalachsindizes) aller Geometrieachsen aufnehmen kann.
   *                                Wenn in diesem Parameter 0 uebergeben wird, liefert die Funktion
   *                                in diesem Parameter lediglich die Anzahl aller Geometrieachsen des
   *                                uebergebenen Kanals, andernfalls die in padwChanAxIndexesBuf
   *                                kopierte Anzahl der Kanalachsindizes, denen die Geometrieachsen
   *                                zugeordnet sind. (in and out)
   *  \param  lChnNo:               Channel number (1 ... N_Y_maxnumChannels) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die Zuordnung der Geometrieachsen zu den Kanalachsen
   *         (Kanalachsindizes) aller Geometrieachsen des uebergebenen Kanals.
   */
  virtual long slDcCfgChnAxConfGeoAxNameTab(T_CFG_UNIT_NAME* patCfgUnitNameGeoAxNamesBuf, long& rlNumGeoAxNamesBuf, long lChnNo) = 0;

  /*! \fn virtual long slDcCfgChnNameVb(char *psChnName, long& rlcbChnName, long lChnNo)
   *
   *  \param  psChnName:   Channel name (out)
   *  \param  rlcbChnName: Length of channel name (Byte count)(in and out)
   *  \param  lChnNo:      Channel number (1 ... N_Y_maxnumChannels) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the name of the given channel
   */
  virtual long slDcCfgChnNameVb(char *psChnName, long& rlcbChnName, long lChnNo) = 0;

  /*! \fn virtual long slDcCfgChnNoAx(long& rlChnNo, long lAxNo)
   *
   *  \param  rlChnNo:  Channel number (out)
   *  \param  lAxNo:    Axis number (1 ... N_Y_maxnumGlobMachAxes) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief
   *  \li Before BTSS_NCK_VERSION_N_SEMA_CHAN_NO_AXIS_IS_ACTIVE:
   *      Gets the number of the channel, in which the given axis was aktive
   *      at the time, the configuration was establish
   *  \li Since BTSS_NCK_VERSION_N_SEMA_CHAN_NO_AXIS_IS_ACTIVE:
   *      Gets the number of the channel, in which the given axis is aktive
   */
  virtual long slDcCfgChnNoAx(long& rlChnNo, long lAxNo) = 0;

  /*! \fn virtual long slDcCfgChnNoSel(long& rlChnNo)
   *
   *  \param  rlChnNo:  Channel number (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of the selected channel
   */
  virtual long slDcCfgChnNoSel(long& rlChnNo) = 0;

  /*! \fn virtual long slDcCfgChnRelAxIdx(long& rlChnRelAxIdx, long lChnNo, long lAxNo)
   *
   *  \param  rlChnRelAxIdx:  Relative axis index in Channel (out)
   *  \param  lChnNo:         Channel number (in)
   *  \param  lAxNo:          Axis number (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the relative axis index of the given axis in th given channel
   */
  virtual long slDcCfgChnRelAxIdx(long& rlChnRelAxIdx, long lChnNo, long lAxNo) = 0;

  /*! \fn virtual long slDcCfgChnRelSpIdx(long& rlChnRelSpIdx, long lChnNo, long lAxNo)
   *
   *  \param  rlChnRelSpIdx:  Relative spindle index in Channel (out)
   *  \param  lChnNo:         Channel number (in)
   *  \param  lAxNo:          Axis number (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the relative spindle index of the given axis in th given channel
   */
  virtual long slDcCfgChnRelSpIdx(long& rlChnRelSpIdx, long lChnNo, long lAxNo) = 0;

  /*! \fn virtual long slDcCfgChnSel(long lChnNo)
   *
   *  \param  lChnNo:  Channel number (1 ... N_Y_maxnumChannels) (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the channel with the given number
   */
  virtual long slDcCfgChnSel(long lChnNo) = 0;

  /*! \fn virtual long slDcCfgChnSelNext(long& rlChnNo)
   *
   *  \param  rlChnNo:  Channel number (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the next channel and gets the new channel number
   */
  virtual long slDcCfgChnSelNext(long& rlChnNo) = 0;

  /*! \fn virtual long slDcCfgChnSelPrev(long& rlChnNo)
   *
   *  \param  rlChnNo:  Channel number (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the previous channel and gets the new channel number
   */
  virtual long slDcCfgChnSelPrev(long& rlChnNo) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgCuObj...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgCuFwVersionObj(long& rlFwVersionBuf, long lObjHdl)
   *
   *  \param  rlFwVersionBuf:  Referenz auf den Puffer fuer die Firmwareversion des
   *                           Control Unit - Objekts. (out)
   *  \param  dwObjHdl:        Handle des Objekts, dass dem Control Unit - Objekt
   *                           zugeordnet ist oder das Handle des Control Unit - Objekts. (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die Firmwareversion fuer das Control Unit - Objekt, welchem
   *  das uebergebene Objekt zugeordnet ist.

   */
  virtual long slDcCfgCuFwVersionObj(long& rlFwVersionBuf, long lObjHdl) = 0;

  /*! \fn virtual long slDcCfgCuObjHdlBusSlave(long& rlCuObjHdl, long lBusNr, long lSlaveAddr)
   *
   *  \param  rlCuObjHdl:  Handle of the control unit object (out)
   *  \param  lBusNr:      Bus number (_N_COMPLETE_DPC_ACX.Bus.Nr) of the CU-
   *                       resp. CX-PROFIBUS-Slave (in)
   *  \param  lSlaveAddr:  PROFIBUS adress of the CU- resp. CX-Slave (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the handle of the control unit object with the given
   *  profibus number and slave adress.
   */
  virtual long slDcCfgCuObjHdlBusSlave(long& rlCuObjHdl, long lBusNr, long lSlaveAddr) = 0;

  /*! \fn virtual long slDcCfgCuObjHdlObj(long& rlCuObjHdl, long lObjHdl)
   *
   *  \param  rlCuObjHdl:  Handle of the control unit object (out)
   *  \param  lObjHdl:     Handle to the higher object, which the
   *                       control unit objekt is assigned (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the handle of the control unit object with is assigned
   *  the given higher object
   */
  virtual long slDcCfgCuObjHdlObj(long& rlCuObjHdl, long lObjHdl) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgDo...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgDoDpSlot(T_CFG_DO_DP_SLOT *patCfgDoDpSlotBuf, long& rlNumDoDpSlotsBuf, long& rlcbCfgDoDpSlotBufOfOneItemBuf, long lObjHdl)
   *
   *  \param  patCfgDoDpSlotBuf:  Pointer to the buffer for the DP slot configuration. (out)
   *  \param  rlNumDoDpSlotsBuf:  Pointer to the buffer for the number of the slots.
   *                              If a value of 0 is given, the function provides only the number
   *                              of slots of the given drive object.
   *                              If a value unequal 0 is given, a buffer of this number of
   *                              T_CFG_DO_DP_SLOT items must be given as buffer for the
   *                              DP slot configuration and maximal *pdwNumDoDpSlotsBuf slot items
   *                              are copied to the buffer for DP slot configuration. The number
   *                              of slot items copied to the buffer for the DP slot configuration
   *                              is returned. (in/out)
   *  \param  rlcbCfgDoDpSlotBufOfOneItemBuf: Pointer to the buffer for the size (number of bytes) of
   *                              one array item of the buffer for the DP slot configuration
   *                              (size of one array item of patCfgDoDpSlotBuf).
   *                              The number of bytes copied to one array item of patCfgDoDpSlotBuf
   *                              is returned in this parameter. If the returned size is less than
   *                              the given size, only the structure elements of patCfgDoDpSlotBuf
   *                              up to the returned number of bytes were provided. (in/out)
   *  \param  dwObjHdl:           Handle of the drive object, of which the
   *                              DP slot configuration is requested. (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Provides the DP slot configuration which is configured in the SDB
   *  for the given drive object.
   */
  virtual long slDcCfgDoDpSlot(T_CFG_DO_DP_SLOT *patCfgDoDpSlotBuf, long& rlNumDoDpSlotsBuf, long& rlcbCfgDoDpSlotBufOfOneItemBuf, long lObjHdl) = 0;

  /*! \fn virtual long slDcCfgDoDpSlotEx(long& rlPNSlotNrBuf, T_CFG_DO_DP_SLOT *patCfgDoDpSlotBuf, long& rlNumDoDpSlotsBuf, long& rlcbCfgDoDpSlotBufOfOneItemBuf, long lObjHdl)
   *
   *  \param  rlPNSlotNrBuf:      Pointer to the buffer for the PROFINET slot number of the
   *                              given drive object. (out)
   *  \param  patCfgDoDpSlotBuf:  Pointer to the buffer for the DP slot configuration. (out)
   *  \param  rlNumDoDpSlotsBuf:  Pointer to the buffer for the number of the slots.
   *                              If a value of 0 is given, the function provides only the number
   *                              of slots of the given drive object.
   *                              If a value unequal 0 is given, a buffer of this number of
   *                              T_CFG_DO_DP_SLOT items must be given as buffer for the
   *                              DP slot configuration and maximal *pdwNumDoDpSlotsBuf slot items
   *                              are copied to the buffer for DP slot configuration. The number
   *                              of slot items copied to the buffer for the DP slot configuration
   *                              is returned. (in/out)
   *  \param  rlcbCfgDoDpSlotBufOfOneItemBuf: Pointer to the buffer for the size (number of bytes) of
   *                              one array item of the buffer for the DP slot configuration
   *                              (size of one array item of patCfgDoDpSlotBuf).
   *                              The number of bytes copied to one array item of patCfgDoDpSlotBuf
   *                              is returned in this parameter. If the returned size is less than
   *                              the given size, only the structure elements of patCfgDoDpSlotBuf
   *                              up to the returned number of bytes were provided. (in/out)
   *  \param  dwObjHdl:           Handle of the drive object, of which the
   *                              DP slot configuration is requested. (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Provides the DP slot configuration which is configured in the SDB
   *  for the given drive object.
   */
  virtual long slDcCfgDoDpSlotEx(long& rlPNSlotNrBuf, T_CFG_DO_DP_SLOT *patCfgDoDpSlotBuf, long& rlNumDoDpSlotsBuf, long& rlcbCfgDoDpSlotBufOfOneItemBuf, long lObjHdl) = 0;

  /*! \fn virtual long slDcCfgDoDpTlgrmInf(T_CFG_DP_TLGRM_INF *patCfgDpTlgrmInfListBuf, long& rlNumCfgDpTlgrmInfListItemsBuf, const long lObjHdl, const bool bInclTlgrmExt)
   *
   *  \param  patCfgDpTlgrmInfListBuf:      [out] Zeiger auf den Puffer (der Liste) fuer das in der PROFIBUS-
   *                                        Konfiguration projektierte Telegramm (mit Telegrammerweiterungen)
   *                                        mit den zugehoerigen Informationen.
   *                                        Dieser Parameter kann NULL sein, wenn lediglich die Anzahl der
   *                                        Listenelemente ermittelt werden soll.
   *  \param  rlNumCfgDpTlgrmInfListItemsBuf:  [in, out] Zeiger auf den Puffer fuer die Anzahl der Listenelemente.
   *                                        Wenn in diesem Parameter 0 uebergeben wird, liefert die Funktion
   *                                        in diesem Parameter lediglich die Anzahl der Listenelemente,
   *                                        andernfalls die in patCfgDpTlgrmInfListBuf kopierte Anzahl der
   *                                        Listenelemente.
   *  \param  lObjHdl:                      [in] Handle des Objekts, fuer das das in der PROFIBUS-Konfiguration
   *                                        projektierte Telegramm (mit Telegrammerweiterungen) mit den
   *                                        zugehoerigen Informationen geliefert werden soll.
   *  \param  bInclTlgrmExt:                [in] Flag, ob die Telegrammerweiterungen ((nc)SI Motion-Monitoring,
   *                                        PROFIsafe und SCI/SCC) mitgeliefert werden sollen.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert das in der PROFIBUS-Konfiguration projektierte Telegramm (mit
   *         Telegrammerweiterungen) mit den zugehoerigen Informationen fuer das
   *         uebergebene (DO) Objekt.
   */
  virtual long slDcCfgDoDpTlgrmInf(T_CFG_DP_TLGRM_INF *patCfgDpTlgrmInfListBuf, long& rlNumCfgDpTlgrmInfListItemsBuf, const long lObjHdl, const bool bInclTlgrmExt) = 0;

  /*! \fn virtual long slDcCfgDoNameAndDoIdOfAxName(char **pszDoNameBuf, long& rlcbDoNameBufBuf, long& rlDoIdBuf, char *pszAxName)
   *
   *  \param  pszDoNameBuf:     DO-Name. Could be NULL if you only want to
   *                            determine the Length of the name (out)
   *  \param  rlcbDoNameBufBuf: Length of the DO-Name (Byte-count). If you
   *                            want to determine the Length of the name, this
   *                            parameter must be 0 (in/out)
   *  \param  rlDoIdBuf:        DI-Id (out)
   *  \param  pszAxName:        Axis-Name (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets name and id of th DO (Drive-Object), which is assigned
   *  to the given axis-name
   */
  virtual long slDcCfgDoNameAndDoIdOfAxName(char **pszDoNameBuf, long& rlcbDoNameBufBuf, long& rlDoIdBuf, char *pszAxName) = 0;

  /*! \fn virtual long slDcCfgDoNameAndDoIdOfAxNameEx(char **pszDoNameBuf, long& rlcbDoNameBufBuf, long& rlDoIdBuf, char *pszAxName, char *pszStationName)
   *
   *  \param  pszDoNameBuf:     DO-Name. Could be NULL if you only want to
   *                            determine the Length of the name (out)
   *  \param  rlcbDoNameBufBuf: Length of the DO-Name (Byte-count). If you
   *                            want to determine the Length of the name, this
   *                            parameter must be 0 (in/out)
   *  \param  rlDoIdBuf:        DI-Id (out)
   *  \param  pszAxName:        Axis-Name (in)
   *  \param  pszStationName:   Zeiger auf den Namen der Station, von der der Wert
   *                            geliefert werden soll. (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets name and id of th DO (Drive-Object), which is assigned
   *  to the given axis-name
   */
  virtual long slDcCfgDoNameAndDoIdOfAxNameEx(char **pszDoNameBuf, long& rlcbDoNameBufBuf, long& rlDoIdBuf, char *pszAxName, char *pszStationName) = 0;

  /*! \fn virtual long slDcCfgDoNameOfBusSlaveDoId(char **pszDoNameBuf, long& rlcbDoNameBufBuf, long lBusNr, long lSlaveAddr, long lDoId)
   *
   *  \param  pszDoNameBuf:     DO-Name. Could be NULL if you only want to
   *                            determine the Length of the name (out)
   *  \param  rlcbDoNameBufBuf: Length of the DO-Name (Byte-count). If you
   *                            want to determine the Length of the name, this
   *                            parameter must be 0 (in/out)
   *  \param  lBusNr:           Busnumber of the CU- resp. CX Profibus-Slave (in)
   *  \param  lSlaveAddr:       Profibus-Adress of the CU- resp. CX-Unit (in)
   *  \param  lDoId:            DI-Id (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets name and id of th DO (Drive-Object) of the given Bus- and
   *  Slave-Adress and the given DI-Id
   */
  virtual long slDcCfgDoNameOfBusSlaveDoId(char **pszDoNameBuf, long& rlcbDoNameBufBuf, long lBusNr, long lSlaveAddr, long lDoId) = 0;

  /*! \fn virtual long slDcCfgDoNameOfBusSlaveDoIdEx(char **pszDoNameBuf, long& rlcbDoNameBufBuf, long lBusNr, long lSlaveAddr, long lDoId, char *pszStationName)
   *
   *  \param  pszDoNameBuf:     DO-Name. Could be NULL if you only want to
   *                            determine the Length of the name (out)
   *  \param  rlcbDoNameBufBuf: Length of the DO-Name (Byte-count). If you
   *                            want to determine the Length of the name, this
   *                            parameter must be 0 (in/out)
   *  \param  lBusNr:           Busnumber of the CU- resp. CX Profibus-Slave (in)
   *  \param  lSlaveAddr:       Profibus-Adress of the CU- resp. CX-Unit (in)
   *  \param  lDoId:            DI-Id (in)
   *  \param  pszStationName:   Zeiger auf den Namen der Station, von der der Wert
   *                            geliefert werden soll. (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets name and id of th DO (Drive-Object) of the given Bus- and
   *  Slave-Adress and the given DI-Id
   */
  virtual long slDcCfgDoNameOfBusSlaveDoIdEx(char **pszDoNameBuf, long& rlcbDoNameBufBuf, long lBusNr, long lSlaveAddr, long lDoId, char *pszStationName) = 0;

  /*! \fn virtual long slDcCfgDoObj(T_CFG_DO_OBJ* ptCfgDoObj, long& rlcbCfgDoObjItem, long lObjHdl)
   *
   *  \param  ptCfgDoObj:        Configuration of a DO-Object (out)
   *  \param  rlcbCfgDoObjItem:  Size of the structure for configuration of a DO-Object (in and out)
   *  \param  lObjHdl:           Handle of the object (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the configuration of the given DO-Object.
   */
  virtual long slDcCfgDoObj(T_CFG_DO_OBJ* ptCfgDoObj, long& rlcbCfgDoObjItem, long lObjHdl) = 0;

  /*! \fn virtual long slDcCfgDoTypeInf(T_CFG_DO_TYPE_INF *ptCfgDoTypeInfBuf, long lDoTypeId)
   *
   *  \param  ptCfgDoTypeInfBuf:  Information of a DO-Type (out)
   *  \param  lObjHdl:            Handle of the object (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the information of a DO-Type.
   */
  virtual long slDcCfgDoTypeInf(T_CFG_DO_TYPE_INF *ptCfgDoTypeInfBuf, long lDoTypeId) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgDp...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgDpSlaveDrvInpNcDrv(bool& rbDpSlaveValid, long& rlDpSlave, bool& rbDpSlotValid, long& rlDpSlot, bool& rbDpIoAddressValid, long& rlDpIoAddress, bool& rbDpIoTypeValid, long& rlDpIoType, bool& rbDrvTypeValid, long& rlDrvType, bool& rbAxNoValid, long& rlAxNo, long lDrvNo)
   *
   *  \param  rbDpSlaveValid:      Validity of the DP-Slave (out)
   *  \param  rlDpSlave:           DP-Slave (out)
   *  \param  rbDpSlotValid:       Validity of the slots (inside the slave) (out)
   *  \param  rlDpSlot:            Slot (inside the slave) (out)
   *  \param  rbDpIoAddressValid:  Validity of the E/A-Adress (out)
   *  \param  rlDpIoAddress:       E/A-Adress (out)
   *  \param  rbDpIoTypeValid:     Validity of the (slot-) type (out)
   *  \param  rlDpIoType:          (Slot-) Type (out)
   *  \param  rbDrvTypeValid:      Validity of the drive type (out)
   *  \param  rlDrvType:           Drive Type (out)
   *  \param  rbAxNoValid:         Validity of the axis number (out)
   *  \param  rlAxNo:              Axis number (out)
   *  \param  lDrvNo:              Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the configuration of the DP-Slave with the given
   *  drive number (Input/Actual value)
   */
  virtual long slDcCfgDpSlaveDrvInpNcDrv(bool& rbDpSlaveValid, long& rlDpSlave, bool& rbDpSlotValid, long& rlDpSlot, bool& rbDpIoAddressValid, long& rlDpIoAddress, bool& rbDpIoTypeValid, long& rlDpIoType, bool& rbDrvTypeValid, long& rlDrvType, bool& rbAxNoValid, long& rlAxNo, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDpSlaveDrvInpNcSlot(bool& rbDpSlaveValid, long& rlDpSlave, bool& rbDpSlotValid, long& rlDpSlot, bool& rbDpIoAddressValid, long& rlDpIoAddress, bool& rbDpIoTypeValid, long& rlDpIoType, bool& rbDrvNoValid, long& rlDrvNo, bool& rbDrvTypeValid, long& rlDrvType, bool& rbAxNoValid, long& rlAxNo, long lSlot)
   *
   *  \param  rbDpSlaveValid:      Validity of the DP-Slave (out)
   *  \param  rlDpSlave:           DP-Slave (out)
   *  \param  rbDpSlotValid:       Validity of the slots (inside the slave) (out)
   *  \param  rlDpSlot:            Slot (inside the slave) (out)
   *  \param  rbDpIoAddressValid:  Validity of the E/A-Adress (out)
   *  \param  rlDpIoAddress:       E/A-Adress (out)
   *  \param  rbDpIoTypeValid:     Validity of the (slot-) type (out)
   *  \param  rlDpIoType:          (Slot-) Type (out)
   *  \param  rbDrvNoValid:        Validity of the drive number (out)
   *  \param  rlNoType:            Drive number (out)
   *  \param  rbDrvTypeValid:      Validity of the drive type (out)
   *  \param  rlDrvType:           Drive Type (out)
   *  \param  rbAxNoValid:         Validity of the axis number (out)
   *  \param  rlAxNo:              Axis number (out)
   *  \param  lSlot :              Slot (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert aus der Liste der DP-Slaves vom Typ Antrieb und
   *  Eingang/Istwert, die der NC zugewiesen sind, die Konfiguration
   *  des DP-Slaves zum uebergebenen Slot [wirksame Daten].
   */
  virtual long slDcCfgDpSlaveDrvInpNcSlot(bool& rbDpSlaveValid, long& rlDpSlave, bool& rbDpSlotValid, long& rlDpSlot, bool& rbDpIoAddressValid, long& rlDpIoAddress, bool& rbDpIoTypeValid, long& rlDpIoType, bool& rbDrvNoValid, long& rlDrvNo, bool& rbDrvTypeValid, long& rlDrvType, bool& rbAxNoValid, long& rlAxNo, long lSlot) = 0;

  /*! \fn virtual long slDcCfgDpSlaveDrvOutpNcDrv(bool& rbDpSlaveValid, long& rlDpSlave, bool& rbDpSlotValid, long& rlDpSlot, bool& rbDpIoAddressValid, long& rlDpIoAddress, bool& rbDpIoTypeValid, long& rlDpIoType, bool& rbDrvTypeValid, long& rlDrvType, bool& rbAxNoValid, long& rlAxNo, long lDrvNo)
   *
   *  \param  rbDpSlaveValid:      Validity of the DP-Slave (out)
   *  \param  rlDpSlave:           DP-Slave (out)
   *  \param  rbDpSlotValid:       Validity of the slots (inside the slave) (out)
   *  \param  rlDpSlot:            Slot (inside the slave) (out)
   *  \param  rbDpIoAddressValid:  Validity of the E/A-Adress (out)
   *  \param  rlDpIoAddress:       E/A-Adress (out)
   *  \param  rbDpIoTypeValid:     Validity of the (slot-) type (out)
   *  \param  rlDpIoType:          (Slot-) Type (out)
   *  \param  rbDrvTypeValid:      Validity of the drive type (out)
   *  \param  rlDrvType:           Drive Type (out)
   *  \param  rbAxNoValid:         Validity of the axis number (out)
   *  \param  rlAxNo:              Axis number (out)
   *  \param  lDrvNo:              Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the configuration of the DP-Slave with the given
   *  drive number (Output/Setpoint)
   */
  virtual long slDcCfgDpSlaveDrvOutpNcDrv(bool& rbDpSlaveValid, long& rlDpSlave, bool& rbDpSlotValid, long& rlDpSlot, bool& rbDpIoAddressValid, long& rlDpIoAddress, bool& rbDpIoTypeValid, long& rlDpIoType, bool& rbDrvTypeValid, long& rlDrvType, bool& rbAxNoValid, long& rlAxNo, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDpSlaveDrvOutpNcSlot(bool& rbDpSlaveValid, long& rlDpSlave, bool& rbDpSlotValid, long& rlDpSlot, bool& rbDpIoAddressValid, long& rlDpIoAddress, bool& rbDpIoTypeValid, long& rlDpIoType, bool& rbDrvNoValid, long& rlDrvNo, bool& rbDrvTypeValid, long& rlDrvType, bool& rbAxNoValid, long& rlAxNo, long lSlot)
   *
   *  \param  rbDpSlaveValid:      Validity of the DP-Slave (out)
   *  \param  rlDpSlave:           DP-Slave (out)
   *  \param  rbDpSlotValid:       Validity of the slots (inside the slave) (out)
   *  \param  rlDpSlot:            Slot (inside the slave) (out)
   *  \param  rbDpIoAddressValid:  Validity of the E/A-Adress (out)
   *  \param  rlDpIoAddress:       E/A-Adress (out)
   *  \param  rbDpIoTypeValid:     Validity of the (slot-) type (out)
   *  \param  rlDpIoType:          (Slot-) Type (out)
   *  \param  rbDrvNoValid:        Validity of the drive number (out)
   *  \param  rlNoType:            Drive number (out)
   *  \param  rbDrvTypeValid:      Validity of the drive type (out)
   *  \param  rlDrvType:           Drive Type (out)
   *  \param  rbAxNoValid:         Validity of the axis number (out)
   *  \param  rlAxNo:              Axis number (out)
   *  \param  lSlot :              Slot (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert aus der Liste der DP-Slaves vom Typ Antrieb und
   *  Ausgang/Sollwert, die der NC zugewiesen sind, die Konfiguration
   *  des DP-Slaves zum uebergebenen Slot [wirksame Daten].
   */
  virtual long slDcCfgDpSlaveDrvOutpNcSlot(bool& rbDpSlaveValid, long& rlDpSlave, bool& rbDpSlotValid, long& rlDpSlot, bool& rbDpIoAddressValid, long& rlDpIoAddress, bool& rbDpIoTypeValid, long& rlDpIoType, bool& rbDrvNoValid, long& rlDrvNo, bool& rbDrvTypeValid, long& rlDrvType, bool& rbAxNoValid, long& rlAxNo, long lSlot) = 0;

  /*! \fn virtual long slDcCfgDpSlaveSlot(bool& rbDpSlaveValid, long& rlDpSlave, bool& rbDpSlotValid, long& rlDpSlot, bool& rbDpIoAddressValid, long& rlDpIoAddress, bool& rbDpIoTypeValid, long& rlDpIoType, bool& rbDrvNoValid, long& rlDrvNo, bool& rbDrvTypeValid, long& rlDrvType, bool& rbAxNoValid, long& rlAxNo, long lSlot)
   *
   *  \param  rbDpSlaveValid:      Validity of the DP-Slave (out)
   *  \param  rlDpSlave:           DP-Slave (out)
   *  \param  rbDpSlotValid:       Validity of the slots (inside the slave) (out)
   *  \param  rlDpSlot:            Slot (inside the slave) (out)
   *  \param  rbDpIoAddressValid:  Validity of the E/A-Adress (out)
   *  \param  rlDpIoAddress:       E/A-Adress (out)
   *  \param  rbDpIoTypeValid:     Validity of the (slot-) type (out)
   *  \param  rlDpIoType:          (Slot-) Type (out)
   *  \param  rbDrvNoValid:        Validity of the drive number (out)
   *  \param  rlNoType:            Drive number (out)
   *  \param  rbDrvTypeValid:      Validity of the drive type (out)
   *  \param  rlDrvType:           Drive Type (out)
   *  \param  rbAxNoValid:         Validity of the axis number (out)
   *  \param  rlAxNo:              Axis number (out)
   *  \param  lSlot :              Slot (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert aus der Liste der DP-Slaves vom Typ Antrieb und
   *  Ausgang/Sollwert, die der NC zugewiesen sind, die Konfiguration
   *  des DP-Slaves zum uebergebenen Slot [wirksame Daten].
   */
  virtual long slDcCfgDpSlaveSlot(bool& rbDpSlaveValid, long& rlDpSlave, bool& rbDpSlotValid, long& rlDpSlot, bool& rbDpIoAddressValid, long& rlDpIoAddress, bool& rbDpIoTypeValid, long& rlDpIoType, bool& rbDrvNoValid, long& rlDrvNo, bool& rbDrvTypeValid, long& rlDrvType, bool& rbAxNoValid, long& rlAxNo, long lSlot) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgDrv...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgDrvAndAxSel(long lDrvNo)
   *
   *  \param  lDrvNo:  Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the given drive and the axis, which the drive is assigned
   */
  virtual long slDcCfgDrvAndAxSel(long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDrvAndAxSelNext(long& rlDrvNo, long lDrvType)
   *
   *  \param  rlDrvNo:   Drive number (1 ... N_Y_maxnumDrives) (out)
   *  \param  lDrvType:  Drive type (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the next drive of the given drive type
   *  and the axis, which this drive is assigned.
   *  Gets the new drive number
   */
  virtual long slDcCfgDrvAndAxSelNext(long& rlDrvNo, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgDrvAndAxSelPrev(long& rlDrvNo, long lDrvType)
   *
   *  \param  rlDrvNo:   Drive number (1 ... N_Y_maxnumDrives) (out)
   *  \param  lDrvType:  Drive type (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the previous drive of the given drive type
   *  and the axis, which this drive is assigned.
   *  Gets the new drive number
   */
  virtual long slDcCfgDrvAndAxSelPrev(long& rlDrvNo, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgDrvBoardType(long& rlDrvBoardType, long lDrvNo)
   *
   *  \param  rlDrvBoardType:  Type of module (out)
   *  \param  lDrvNo:          Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the type of the module with the given drive number
   */
  virtual long slDcCfgDrvBoardType(long& rlDrvBoardType, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDrvBusType(long& rlDrvBusType, long lDrvNo)
   *
   *  \param  rlDrvBusType:  Bus type (out)
   *  \param  lDrvNo:        Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the bus type of the drive with the given drive number
   */
  virtual long slDcCfgDrvBusType(long& rlDrvBusType, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDrvCnt(long& rlDrvCnt, long lDrvType)
   *
   *  \param  rlDrvCnt  Number of drives (out)
   *  \param  lDrvType  Drive type (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of drives of the given drive type
   */
  virtual long slDcCfgDrvCnt(long& rlDrvCnt, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgDrvConsRegistered(bool& rbDrvConsRegistered)
   *
   *  \param  rbDrvConsRegistered
   *         out Zeiger auf den Puffer fuer das Flag zur Anzeige, ob die
   *         Adresseintraege fuer die Verbindungen zu den Antrieben in der
   *         mmc.ini eingetragen und wirksam sind. (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  Liefert das Flag zur Anzeige, ob die Adresseintraege fuer die
   *  Verbindungen zu den Antrieben in der mmc.ini eingetragen und
   *  wirksam sind.
   */
  virtual long slDcCfgDrvConsRegistered(bool& rbDrvConsRegistered) = 0;

  /*! \fn virtual long slDcCfgDrvModRelSlotNo(long& rlDrvModRelSlotNo, long lDrvNo)
   *
   *  \param  rlDrvModRelSlotNo:  Antriebs-modulrelative Steckplatznummer (out)
   *  \param  lDrvNo:             Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  Liefert die modulrelative Achsnummer des uebergebenen Antriebs.
   */
  virtual long slDcCfgDrvModRelSlotNo(long& rlDrvModRelSlotNo, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDrvModType(long& rlDrvModType, long lDrvNo)
   *
   *  \param  rlDrvModType:  Modultyp des Antriebs (out)
   *  \param  lDrvNo:        Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  Liefert den Modultyp des uebergebenen Antriebs.
   */
  virtual long slDcCfgDrvModType(long& rlDrvModType, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxName(long& rlDrvNr, char *rszSlaveIdentNo_DoTypeId, long& rlcbSlaveIdentNo_DoTypeId, const char *pszAxName)
   *
   *  \param  rlDrvNr:           [out] Zeiger auf den Puffer fuer die Antriebsnummer (1 ... N_Y_maxnumDrives).
   *  \param  rszSlaveIdentNo_DoTypeId:
   *                             [out] Zeiger auf den Puffer fuer den String der Slave-Ident-Nummer
   *                             und die [DO-Sicht-ID,] DO-Typ-ID [und Version der installierten SINAMICS-Texte].
   *  \param  rlcbSlaveIdentNo_DoTypeId:
   *                             [in, out] Zeiger auf den Puffer fuer die Groesse des Puffers fuer
   *                             den String der Slave-Ident-Nummer und der [DO-Sicht-ID,] DO-Typ-ID
   *                             [und Version der installierten SINAMICS-Texte] in Byte (count byte).
   *  \param  pszAxName:         String for the axis name (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert fuer den Antrieb, der der Achse mit dem uebergebenen Achsnamen
   *  zugeordnet ist, die Nummer des Antriebs und den String bestehend aus
   *     - Slave-Ident-Nummer (hexadezimal, vierstellig, mit  fuehrenden Nullen), Unterstrich und
   *     - DO-Typ-ID (dezimal, dreistellig mit fuehrenden Nullen),
   *       sofern keine SINAMICS Sicht- und Versions-spezifischen Texte
   *       installiert sind (die (Eintraege der) Datei
   *       sl_sinamics_text_versions.ini nicht existiert(existieren)) oder
   *     - DO-Sicht-ID der installierten SINAMICS-Texte (dezimal, dreistellig
   *       mit fuehrenden Nullen),
   *       DO-Typ-ID (dezimal, dreistellig mit fuehrenden Nullen), Unterstrich und
   *       Version der installierten SINAMICS-Texte (dezimal, achtstellig,
   *       mit fuehrenden Nullen), die zur Firmware-Version der Control Unit
   *       gehoeren bzw. die fuer die Firmware-Version der Control Unit geeignet
   *       sind, sofern SINAMICS Sicht- und Versions-spezifische Texte installiert
   *       sind (die (Eintraege der) Datei sl_sinamics_text_versions.ini
   *       existiert(existieren))
   *    Sofern der Achse kein DO zugeordnet ist bzw. zugeordnet werden
   *    kann, besteht der gelieferte String lediglich aus der
   *    Slave-Ident-Nummer (hexadezimal, vierstellig, mit fuehrenden Nullen).
   */
  virtual long slDcCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxName(long& rlDrvNr, char *rszSlaveIdentNo_DoTypeId, long& rlcbSlaveIdentNo_DoTypeId, const char *pszAxName) = 0;

  /*! \fn virtual long slDcCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxNameEx(long& rlDrvNr, char *rszSlaveIdentNo_DoTypeId, long& rlcbSlaveIdentNo_DoTypeId, const char *pszAxName, char* pszStationName)
   *
   *  \param  rlDrvNr:           [out] Zeiger auf den Puffer fuer die Antriebsnummer (1 ... N_Y_maxnumDrives).
   *  \param  rszSlaveIdentNo_DoTypeId:
   *                             [out] Zeiger auf den Puffer fuer den String der Slave-Ident-Nummer
   *                             und die [DO-Sicht-ID,] DO-Typ-ID [und Version der installierten SINAMICS-Texte].
   *  \param  rlcbSlaveIdentNo_DoTypeId:
   *                             [in, out] Zeiger auf den Puffer fuer die Groesse des Puffers fuer
   *                             den String der Slave-Ident-Nummer und der [DO-Sicht-ID,] DO-Typ-ID
   *                             [und Version der installierten SINAMICS-Texte] in Byte (count byte).
   *  \param  pszAxName:         [in] Zeiger auf den Achsnamen.
   *  \param  pszStationName:    Zeiger auf den Namen der Station, von der die Werte
   *                             geliefert werden sollen. (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert fuer die Station mit dem uebergebenen Stationsnamen, fuer den
   *  Antrieb, der der Achse mit dem uebergebenen Achsnamen zugeordnet ist,
   *  die Nummer des Antriebs und den String bestehend aus
   *    - Slave-Ident-Nummer (hexadezimal, vierstellig, mit fuehrenden Nullen), Unterstrich und
   *    - DO-Typ-ID (dezimal, dreistellig mit fuehrenden Nullen),
   *      sofern keine SINAMICS Sicht- und Versions-spezifischen Texte
   *      installiert sind (die (Eintraege der) Datei
   *      sl_sinamics_text_versions.ini nicht existiert(existieren)) oder
   *    - DO-Sicht-ID der installierten SINAMICS-Texte (dezimal, dreistellig
   *      mit fuehrenden Nullen),
   *      DO-Typ-ID (dezimal, dreistellig mit fuehrenden Nullen),
   *      Unterstrich und
   *      Version der installierten SINAMICS-Texte (dezimal, achtstellig,
   *      mit fuehrenden Nullen), die zur Firmware-Version der Control Unit
   *      gehoeren bzw. die fuer die Firmware-Version der Control Unit geeignet
   *      sind,
   *      sofern SINAMICS Sicht- und Versions-spezifische Texte installiert
   *      sind (die (Eintraege der) Datei sl_sinamics_text_versions.ini
   *      existiert(existieren))
   *  Sofern der Achse kein DO zugeordnet ist bzw. zugeordnet werden
   *  kann, besteht der gelieferte String lediglich aus der
   *  Slave-Ident-Nummer (hexadezimal, vierstellig, mit fuehrenden Nullen).
   */
  virtual long slDcCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxNameEx(long& rlDrvNr, char *rszSlaveIdentNo_DoTypeId, long& rlcbSlaveIdentNo_DoTypeId, const char *pszAxName, char* pszStationName) = 0;

  /*! \fn virtual long slDcCfgDrvNoAndSlaveIdentNoSzAxName(long& rlDrvNr, char **paszSlaveIdentNo, long& rlcbSlaveIdentNo, const char *pszAxName)
   *
   *  \param  rlDrvNr:           Drive number (1 ... N_Y_maxnumDrives) (out)
   *  \param  paszSlaveIdentNo:  String for the Slave-Ident-Number (out)
   *  \param  rlcbSlaveIdentNo:  Length of the String for the Slave-Ident-Number
   *                             (Byte count)(in and out)
   *  \param  rszAxName:         String for the axis name (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of the drive and its Slave-Ident-Number-String
   *  (Format: hex, 4 digits with leading 0), of the drive, which
   *  is assigned to the axis with the given axis name
   */
  virtual long slDcCfgDrvNoAndSlaveIdentNoSzAxName(long& rlDrvNr, char *rszSlaveIdentNo_DoTypeId, long& rlcbSlaveIdentNo, const char *pszAxName) = 0;

  /*! \fn virtual long slDcCfgDrvNoArrayOfMod(DC_PA_WORD psaArray, long& rlArrayLen, long lDrvNo)
   *
   *  \param  psaArray:     Data array (out)
   *  \param  rlArrayLen:   Array length (in/out)
   *  \param  lDrvNo:       Drive number (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets array of drive-numbers of the module of thew given drive
   */
  virtual long slDcCfgDrvNoArrayOfMod(DC_PA_WORD psaArray, long& rlArrayLen, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDrvNoAx(long& rlDrvNo, long lAxNo)
   *
   *  \param  rlDrvNo:  Drive number (1 ... N_Y_maxnumDrives) (out)
   *  \param  lAxNo:    Axis number (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of the drive, which is assigned to the given axis number
   */
  virtual long slDcCfgDrvNoAx(long& rlDrvNo, long lAxNo) = 0;

  /*! \fn virtual long slDcCfgDrvNoSel(long& rlDrvNo, long lDrvType)
   *
   *  \param  rlDrvNo:   Drive number (1 ... N_Y_maxnumDrives) (out)
   *  \param  lDrvType:  Drive type (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of the seleceted drive of the given drive type
   */
  virtual long slDcCfgDrvNoSel(long& rlDrvNo, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgDrvObj(T_CFG_DRV_OBJ* ptCfgDrvObj, long& rlcbCfgDrvObjItem, long lDrvObjHdl)
   *
   *  \param  ptCfgDrvObj:        Configuration of the drive object
   *  \param  rlcbCfgDrvObjItem:  Size of struct T_CFG_DRV_OBJ
   *  \param  lDrvObjHdl:         Handle of the drive object (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the configuration of the given drive object
   */
  virtual long slDcCfgDrvObj(T_CFG_DRV_OBJ* ptCfgDrvObj, long& rlcbCfgDrvObjItem, long lDrvObjHdl) = 0;

  /*! \fn virtual long slDcCfgDrvObjAndAxSel(long lDrvObjHdl)
   *
   *  \param  lDrvObjHdl:  Handle of the drive object (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the drive object with the given handle
   */
  virtual long slDcCfgDrvObjAndAxSel(long lDrvObjHdl) = 0;

  /*! \fn virtual long slDcCfgDrvObjAndAxSelNext(long& rlDrvObjHdl, long lDrvType, long lFlags)
   *
   *  \param  rlDrvObjHdl:  Handle of the drive object (out)
   *  \param  lDrvType:     Drive type (in)
   *  \param  lFlags:       Flags (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the next drive object with the given
   *  drive type and appropriated flags and the axis which
   *  the drive is assigned.
   *  Gets the handle ob the new drive object
   */
  virtual long slDcCfgDrvObjAndAxSelNext(long& rlDrvObjHdl, long lDrvType, long lFlags) = 0;

  /*! \fn virtual long slDcCfgDrvObjAndAxSelPrev(long& rlDrvObjHdl, long lDrvType, long lFlags)
   *
   *  \param  rlDrvObjHdl:  Handle of the drive object (out)
   *  \param  lDrvType:     Drive type (in)
   *  \param  lFlags:       Flags (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the previous drive object with the given
   *  drive type and appropriated flags and the axis which
   *  the drive is assigned.
   *  Gets the handle ob the new drive object
   */
  virtual long slDcCfgDrvObjAndAxSelPrev(long& rlDrvObjHdl, long lDrvType, long lFlags) = 0;

  /*! \fn virtual long slDcCfgDrvObjCnt(long& rlDrvObjCnt, long lDrvType, long lFlags)
   *
   *  \param  rlDrvObjCnt:  Number of drive objects (out)
   *  \param  lDrvType:     Drive type (in)
   *  \param  lFlags:       Flags (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the number of drive objects with the given
   *  type and appropriated flags
   */
  virtual long slDcCfgDrvObjCnt(long& rlDrvObjCnt, long lDrvType, long lFlags) = 0;

  /*! \fn virtual long slDcCfgDrvObjHdlAx(long& rlDrvObjHdl, long lAxNr)
   *
   *  \param  rlDrvObjHdl:  Handle of the drive object (out)
   *  \param  lAxNr:        Axis number (1 ... N_Y_maxnumGlobMachAxes) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the handle of the drive object which is assigned
   *  to the given axis
   */
  virtual long slDcCfgDrvObjHdlAx(long& rlDrvObjHdl, long lAxNr) = 0;

  /*! \fn virtual long slDcCfgDrvObjHdlDrv(long& rlDrvObjHdl, long lDrvNr)
   *
   *  \param  rlDrvObjHdl:  Handle of the drive object (out)
   *  \param  lDrvNr:       Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the handle of the drive object which has the given drive number
   */
  virtual long slDcCfgDrvObjHdlDrv(long& rlDrvObjHdl, long lDrvNr) = 0;

  /*! \fn virtual long slDcCfgDrvObjHdlSel(long& rlDrvObjHdl, long lDrvType, long lFlags)
   *
   *  \param  rlDrvObjHdl:  Handle of the drive object (out)
   *  \param  lDrvType:     Drive type (in)
   *  \param  lFlags:       Flags (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the handle of selected drive object with the given
   *  type and appropriated flags
   */
  virtual long slDcCfgDrvObjHdlSel(long& rlDrvObjHdl, long lDrvType, long lFlags) = 0;

  /*! \fn virtual long slDcCfgDrvSel(long lDrvNo)
   *
   *  \param  lDrvNo:  Antriebsnummer (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selektiert den uebergebenen Antrieb (ohne die Achse, welcher der
   *  Antrieb zugeordnet ist).
   */
  virtual long slDcCfgDrvSel(long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDrvSelOfAxSel(void)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selektiert den Antrieb, welcher der selektierten Achse zugeordnet ist.
   */
  virtual long slDcCfgDrvSelOfAxSel(void) = 0;

  /*! \fn virtual long slDcCfgDrvSlotNo(long& rlSlotNo, long lDrvNo)
   *
   *  \param  rlSlotNo:  Slot number (out)
   *  \param  lDrvNo:    Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the slot number of the given drive
   */
  virtual long slDcCfgDrvSlotNo(long& rlSlotNo, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDrvType(long& rlDrvType, long lDrvNo)
   *
   *  \param  rlDrvType:  Drive type (out)
   *  \param  lDrvNo:     Drive number (1 ... N_Y_maxnumDrives) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the type of the drive with the given drive number
   */
  virtual long slDcCfgDrvType(long& rlDrvType, long lDrvNo) = 0;

  /*! \fn virtual long slDcCfgDrvTypeAx(long& rlDrvType, long lAxNo)
   *
   *  \param  rlDrvType:  Drive type (out)
   *  \param  lAxNo:      Axis number (1 ... N_Y_maxnumGlobMachAxes) (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the type of the drive which is assigned th given axis number
   */
  virtual long slDcCfgDrvTypeAx(long& rlDrvType, long lAxNo) = 0;

  /*! \fn virtual long slDcCfgDrvTypeCmn(long& rlDrvTypeCmn)
   *
   *  \param  rlDrvTypeCmn:  Drive type (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the general drive type
   */
  virtual long slDcCfgDrvTypeCmn(long& rlDrvTypeCmn) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // CfgFixPtVal...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgFixPtVal(long& rlFixPtValBuf, E_CFG_SNX_FIX_PT_VAL eCfgFixPtVal, ilong lParam)
   *
   *  \param  rlFixPtValBuf:      Referenz auf den Puffer fuer den Festpunktwert. (out)
   *  \param  eCfgFixPtVal:       Enumerator des zu liefernden Festpunktwerts. (in)
   *  \param  lParam:             Handle des Objekts, von dem der Festpunktwert geliefert
   *                              werden soll.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert den durch den uebergebenen Enumerator und das uebergebene
   *         Objekthandle adressierten SINAMICS-Festpunktwert.
   */
  virtual long slDcCfgFixPtVal(long& rlFixPtValBuf, E_CFG_FIX_PT_VAL eCfgFixPtVal, long lParam) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // CfgList...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgListAxVb(T_CFG_UNIT_VB **patListVb, long& rlListLen, long lcbListItem, long lAxType, long lAxClass)
   *
   *  \param  patListVb:    List of all axis names of the given type (out)
   *  \param  rlListLen:    Size of list (number of array elements) (in and out)
   *  \param  lcbListItem:  Size of structur in bytes (in)
   *  \param  lAxType:      Achstyp (in)
   *  \param  lAxClass:     Achsklasse (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of all axis names and numbers of the
   *  given axis type, axis class and drive type.
    */
  virtual long slDcCfgListAxVb(T_CFG_UNIT_VB **patListVb, long& rlListLen, long lcbListItem, long lAxType, long lAxClass) = 0;

  /*! \fn virtual long slDcCfgListAxVbX(T_CFG_UNIT_VB **patListVb, long& rlListLen, long lcbListItem, long lAxType, long lAxClass, long lDrvType)
   *
   *  \param  patListVb:    List of all axis names of the given type (out)
   *  \param  rlListLen:    Size of list (number of array elements) (in and out)
   *  \param  lcbListItem:  Size of structur in bytes (in)
   *  \param  lAxType:      Achstyp (in)
   *  \param  lAxClass:     Achsklasse (in)
   *  \param  lDrvType:     Antriebstyp (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of all axis names and numbers of the
   *  given axis type, axis class and drive type.
    */
  virtual long slDcCfgListAxVbX(T_CFG_UNIT_VB **patListVb, long& rlListLen, long lcbListItem, long lAxType, long lAxClass, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgListChnVb(T_CFG_UNIT_VB **patListVb, long& rlListLen, long lcbListItem)
   *
   *  \param  patListVb:    List of all axis names of the given type (out)
   *  \param  rlListLen:    Size of list (number of array elements) (in and out)
   *  \param  lcbListItem:  Size of structur in bytes (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of all channel names and numbers.
    */
  virtual long slDcCfgListChnVb(T_CFG_UNIT_VB **patListVb, long& rlListLen, long lcbListItem) = 0;

  /*! \fn virtual long slDcCfgListDoObj(T_CFG_DO_OBJ **patCfgDoObjList, long& rlNumListItems, long& rlcbCfgDoObjItem, long lObjType)
   *
   *  \param  patCfgDoObjList:    List of Configuration of all DO-Objects (out)
   *  \param  rlNumListItems:     Number of List elements (in and out)
   *  \param  rlcbCfgDoObjItem:   Size of one List element in bytes (in and out)
   *  \param  lObjType:           Type of the Objects (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of the configuration of all (DO-) objects of the given object type
   */
  virtual long slDcCfgListDoObj(T_CFG_DO_OBJ **patCfgDoObjList, long& rlNumListItems, long& rlcbCfgDoObjItem, long lObjType) = 0;

  /*! \fn virtual long slDcCfgListDoObjCu(T_CFG_DO_OBJ **patCfgDoObjList, long& rlNumListItems, long& rlcbCfgDoObjItem, long lCuObjHdl)
   *
   *  \param  patCfgDoObjList:   List of Configuration of all DO-Objects (out)
   *  \param  rlNumListItems:    Number of List elements (in and out)
   *  \param  rlcbCfgDoObjItem:  Size of one List element in bytes (in and out)
   *  \param  lCuObjHdl:         Handle of the Control Unit - Object, which
   *                             List of all DO-Objects should be supplied
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of configuration of all DO-Objects of the given Control Unit
   *  (including the Control Unit itself)
   */
  virtual long slDcCfgListDoObjCu(T_CFG_DO_OBJ **patCfgDoObjList, long& rlNumListItems, long& rlcbCfgDoObjItem, long lCuObjHdl) = 0;

  /*! \fn virtual long slDcCfgListDpSlaves(T_CFG_DP_SLAVE_CFG **patList, long& rlniList, long lnbListItem)
   *
   *  \param  patList:      Array of List elements
   *  \param  rlniList:     Number of list elements
   *  \param  lnbListItem:  Size of one list element
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of all DP-Slaves with the configuration of those.
   *  The configuration contains following :
   *     \li DP-Slave
   *     \li Slot (inside the Slaves)
   *     \li E/A-Adress
   *     \li (Slot-) Type
   *     \li [Drive number]
   *     \li [Drive type]
   *     \li [Axis index]
   *  sorted by Bus number, DP-Slave and Slot.
   */
  virtual long slDcCfgListDpSlaves(T_CFG_DP_SLAVE_CFG **patList, long& rlniList, long lnbListItem) = 0;

  /*! \fn virtual long slDcCfgListDpSlavesDrvInpNc(T_CFG_DP_SLAVE_CFG **patList, long& rlniList, long lnbListItem)
   *
   *  \param  patList:      Array of List elements
   *  \param  rlniList:     Number of list elements
   *  \param  lnbListItem:  Size of one list element
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of all DP-Slaves with the configuration of those.
   *  The configuration contains following :
   *     \li DP-Slave
   *     \li Slot (inside the Slaves)
   *     \li E/A-Adress
   *     \li (Slot-) Type
   *     \li [Drive number]
   *     \li [Drive type]
   *     \li [Axis index]
   *  sorted by Bus number, DP-Slave and Slot.
   */
  virtual long slDcCfgListDpSlavesDrvInpNc(T_CFG_DP_SLAVE_CFG **patList, long& rlniList, long lnbListItem) = 0;

  /*! \fn virtual long slDcCfgListDpSlavesDrvOutpNc(T_CFG_DP_SLAVE_CFG **patList, long& rlniList, long lnbListItem)
   *
   *  \param  patList:      Array of List elements
   *  \param  rlniList:     Number of list elements
   *  \param  lnbListItem:  Size of one list element
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of all DP-Slaves with the configuration of those.
   *  The configuration contains following :
   *     \li DP-Slave
   *     \li Slot (inside the Slaves)
   *     \li E/A-Adress
   *     \li (Slot-) Type
   *     \li [Drive number]
   *     \li [Drive type]
   *     \li [Axis index]
   *  sorted by Bus number, DP-Slave and Slot.
   */
  virtual long slDcCfgListDpSlavesDrvOutpNc(T_CFG_DP_SLAVE_CFG **patList, long& rlniList, long lnbListItem) = 0;

  /*! \fn virtual long slDcCfgListDpSlot(T_CFG_DP_SLOT **patCfgDpSlotList, long& rlNumListItems, long& rlcbCfgDpSlotItem, long lStartIndex, long lBusNr, long lSlaveAddr, long lDrvNr, E_CFG_DP_SLOT_CLS eCfgDpSlotCls)
   *
   *  \param  patCfgDpSlotList:   List of configuration of the DP-Slots
   *                              This parameter might be NULL to determine the number of DP-Slots (out)
   *  \param  rlNumListItems:     Number of list elements (in and out)
   *                              This parameter might be NULL to determine the number of DP-Slots (out)
   *  \param  rlcbCfgDpSlotItem:  \li (in)  Size of one list element (in)
   *                              \li (out) Number of Bytes copied in an list element. If this value is smaller than
   *                              sizeof(T_CFG_DP_SLOT), not all elements of the structure are filled (out)
   *  \param  lStartIndex:        Start index started by 0, only relevant if rlNumListItems not equal 0
   *  \param  lBusNr:             Bus number (_N_COMPLETE_DPC_ACX.Bus.Nr). If this parameter is equal -1,
   *                              the configuration of DP-Slots of all bus segments is supplied
   *  \param  lSlaveAddr:         Slave adress. If this parameter is equal -1, the configuration
   *                              of DP-Slots of all DP-Slaves is supplied
   *  \param  lDrvNr:             Drive number. If this parameter is equal -1, the configuration
   *                              of all DP-Slots is supplied
   *  \param  eCfgDpSlotCls:      Slot class \ref E_CFG_DP_SLOT_CLS, which DP-Slots should be supplied:
   *                              \li all
   *                              \li Drive and Input/Actual value and assigned to the NC
   *                              \li Drive and Output/Setpoint and assigned to the NC
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets a list of the configuration of all DP-Slots of the given bus number,
   *  slave adress, drive number, sorted by bus number, slave adress and slot number.
   */
  virtual long slDcCfgListDpSlot(T_CFG_DP_SLOT **patCfgDpSlotList, long& rlNumListItems, long& rlcbCfgDpSlotItem, long lStartIndex, long lBusNr, long lSlaveAddr, long lDrvNr, E_CFG_DP_SLOT_CLS eCfgDpSlotCls) = 0;

  /*! \fn virtual long slDcCfgListDpTlgrmInfSlaveCu(T_CFG_DP_TLGRM_INF *patCfgDpTlgrmInfListBuf, long& rlNumCfgDpTlgrmInfListItemsBuf, const long lCuObjHdl, const bool bInclTlgrmExt)
   *
   *  \param  patCfgDpTlgrmInfListBuf:      [out] Zeiger auf den Puffer der Liste fuer die in der PROFIBUS-
   *                                        Konfiguration projektierten Telegramme (mit Telegrammerweiterungen)
   *                                        mit den zugehoerigen Informationen.
   *                                        Dieser Parameter kann NULL sein, wenn lediglich die Anzahl der
   *                                        Listenelemente ermittelt werden soll.
   *  \param  rlNumCfgDpTlgrmInfListItemsBuf:  [in, out] Zeiger auf den Puffer fuer die Anzahl der Listenelemente.
   *                                        Wenn in diesem Parameter 0 uebergeben wird, liefert die Funktion
   *                                        in diesem Parameter lediglich die Anzahl der Listenelemente,
   *                                        andernfalls die in patCfgDpTlgrmInfListBuf kopierte Anzahl der
   *                                        Listenelemente.
   *  \param  lCuObjHdl:                    [in] Handle des Control Unit - Objekts des SINAMICS Slave/Device,
   *                                        fuer den die Liste der in der PROFIBUS-Konfiguration projektierten
   *                                        Telegramme (mit Telegrammerweiterungen) mit den zugehoerigen
   *                                        Informationen geliefert werden soll.
   *  \param  bInclTlgrmExt:                [in] Flag, ob die Telegrammerweiterungen ((nc)SI Motion-Monitoring,
   *                                        PROFIsafe und SCI/SCC) mitgeliefert werden sollen.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die Liste der in der PROFIBUS-Konfiguration projektierten
   *         Telegramme (mit Telegrammerweiterungen) mit den zugehoerigen
   *         Informationen fuer den SINAMICS Slave/Device der uebergebenen
   *         Control Unit.
   */
  virtual long slDcCfgListDpTlgrmInfSlaveCu(T_CFG_DP_TLGRM_INF *patCfgDpTlgrmInfListBuf, long& rlNumCfgDpTlgrmInfListItemsBuf, const long lCuObjHdl, const bool bInclTlgrmExt) = 0;

  /*! \fn virtual long slDcCfgListDrvObj(T_CFG_DRV_OBJ **patCfgDrvObjList, long& rlNumListItems, long lcbCfgDrvObjItem, long lDrvType, long lFlags)
   *
   *  \param  patCfgDrvObjList:   List of the configuration of the drive objects
   *  \param  rlNumListItems:     Number of list elements
   *  \param  rlcbCfgDrvObjItem:  Size of one list element
   *  \param  lDrvType:           Drive type
   *  \param  lFlags:             Flags
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of configurations of drive objects which are
   *  of the given object type and appropriated flags
   */
  virtual long slDcCfgListDrvObj(T_CFG_DRV_OBJ **patCfgDrvObjList, long& rlNumListItems, long lcbCfgDrvObjItem, long lDrvType, long lFlags) = 0;

  /*! \fn virtual long slDcCfgListDrvVb(T_CFG_UNIT_VB **patListVb, long& rlListLen, long lcbListItem, long lDrvType)
   *
   *  \param  patListVb:    List of all axis names of the given type (out)
   *  \param  rlListLen:    Size of list (number of array elements) (in and out)
   *  \param  lcbListItem:  Size of structur in bytes (in)
   *  \param  lDrvType:     Antriebstyp (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of all drive names and numbers of the
   *  given drive type.
   */
  virtual long slDcCfgListDrvVb(T_CFG_UNIT_VB **patListVb, long& rlListLen, long lcbListItem, long lDrvType) = 0;

  /*! \fn virtual long slDcCfgListIndexVb(long& rlListIndex, const char *pszUnit, long lcbUnit, T_CFG_UNIT_VB **patListVb, long lListLen, long lcbListItem)
   *
   *  \param  rlListIndex:  Listenindex (Rueckgabeparameter)
   *  \param  rsUnit:       Einheit (in)
   *  \param  pszUnit:      Laenge (count byte) der Einheit (in)
   *  \param  patListVb:    Liste (in)
   *  \param  lListLen:     Listenlaenge (in)
   *  \param  lcbListItem:  Groesse eines Listenelementes in Byte (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Prueft, ob die uebergebene Einheit (Nummer oder Name) in der ueber-
   *  gebenen Liste vorhanden ist. Liefert im Erfolgsfall den Index, mit
   *  dem die uebergebene Einheit in der uebergebenen Liste adressiert
   *  werden kann.
   */
  virtual long slDcCfgListIndexVb(long& rlListIndex, const char *pszUnit, long lcbUnit, T_CFG_UNIT_VB **patListVb, long lListLen, long lcbListItem) = 0;

  /*! \fn virtual long slDcCfgListPbObj(T_CFG_PB_OBJ **patCfgPbObjList, long& rlNumListItemsBuf, long& rlcbCfgPbObjListBufOfOneItemBuf)
   *
   *  \param  ratCfgPbObjListBuf:               List of the configuration of profibus
   *  \param  rlNumListItemsBuf:                Number of list elements
   *  \param  rlcbCfgPbObjListBufOfOneItemBuf:  Size of one list element
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the list of configurations of profibus
   */
  virtual long slDcCfgListPbObj(T_CFG_PB_OBJ **patCfgPbObjList, long& rlNumListItemsBuf, long& rlcbCfgPbObjListBufOfOneItemBuf) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // CfgLockEvent...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgLockEvent(bool& rbPreviousEventLockedStateBuf, E_CFG_EVENT eCfgEvent, bool bLockEvent)
   *
   *  \param  rbPreviousEventLockedStateBuf:  Zeiger auf den Puffer fuer das Flag zur Anzeige, ob das
   *                                          Event vor dem Aufruf der Funktion gesperrt (TRUE) oder
   *                                          freigegeben (FALSE) war.
   *  \param  eCfgEvent:                      Event
   *  \param  bLockEvent:                     TRUE, wenn das Event gespert werden soll, FALSE wenn das
   *                                          Event freigegeben werden soll.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Sperrt bzw. gibt das uebergebene Event frei.
   *         Das Sperren und Freigeben der Events erfolgt ueber Referenzzaehler,
   *         d.h. fuer jeden Aufruf zum Sperren eines Events muss ein zugehoeriger
   *         Aufruf zum Freigegen des Events erfolgen, damit das Event wieder
   *         freigegeben ist.
   */
  virtual long slDcCfgLockEvent(bool& rbPreviousEventLockedStateBuf, E_CFG_EVENT eCfgEvent, bool bLockEvent) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // CfgObj...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgObjBtssComParam(long& rlBtssModule, long& rlBtssArea, long& rlBtssUnit, long lObjHdl)
   *
   *  \param  rlBtssModule:  BTSS-Module (out)
   *  \param  rlBtssArea:    BTSS-Area (out)
   *  \param  rlBtssUnit:    BTSS-Unit (out)
   *  \param  lObjHdl:       Handle of the object (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the BTSS-Parameters for BTSS communication
   *  to the object with the given handle
   */
  virtual long slDcCfgObjBtssComParam(long& rlBtssModule, long& rlBtssArea, long& rlBtssUnit, long lObjHdl) = 0;

  /*! \fn virtual long slDcCfgObjCnt(long& rlObjCnt, long lObjType)
   *
   *  \param  rlObjCnt:  Number of objects (out)
   *  \param  lObjType:  Type of object (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief : Gets the number of objects of the given object type
   */
  virtual long slDcCfgObjCnt(long& rlObjCnt, long lObjType) = 0;

  /*! \fn virtual long slDcCfgObjDrvConName(char *rszDrvConName, long& rlcbDrvConName, long lObjHdl)
   *
   *  \param  rszDrvConName:   Name of the connection to the object (out)
   *  \param  rlcbDrvConName:  Length of the Name of the connection to the object
   *                           If this parameter ist 0, the function return
   *                           the needed size for the String.
   *                           (count byte) (in and out)
   *  \param  lObjHdl:         Handle of the object (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the name of the connection to the object with the given handle
   */
  virtual long slDcCfgObjDrvConName(char *rszDrvConName, long& rlcbDrvConName, long lObjHdl) = 0;

  /*! \fn virtual long slDcCfgObjHdlSel(long& rlObjHdl, long lObjType)
   *
   *  \param  rlObjHdl:  Handle of the object (out)
   *  \param  lObjType:  Objekt type (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the handle to the selectet object of the given type
   */
  virtual long slDcCfgObjHdlSel(long& rlObjHdl, long lObjType) = 0;

  /*! \fn virtual long slDcCfgObjSel(long lObjHdl) = 0;
   *
   *  \param  lObjHdl:  Handle of the object (in)
   *
   *  \retval long : Im Erfolgsfall 0, im Fehlerfall LastError.
   *
   *  \brief Selects the object with the given handle
   */
  virtual long slDcCfgObjSel(long lObjHdl) = 0;

  /*! \fn virtual long slDcCfgObjSelNext(long& rlObjHdl, long lObjType)
   *
   *  \param  rlObjHdl:  Handle of the object (out)
   *  \param  lObjType:  Objekt type (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the next object of the given type and gets the new handle of the object
   */
  virtual long slDcCfgObjSelNext(long& rlObjHdl, long lObjType) = 0;

  /*! \fn virtual long slDcCfgObjSelPrev(long& rlObjHdl, long lObjType)
   *
   *  \param  rlObjHdl:  Handle of the object (out)
   *  \param  lObjType:  Objekt type (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Selects the previous object of the given type and gets the new handle of the object
   */
  virtual long slDcCfgObjSelPrev(long& rlObjHdl, long lObjType) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgPb...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgPbObj(T_CFG_PB_OBJ *ptCfgPbObjBuf, long& rlcbCfgPbObjBufBuf, long lObjHdl)
   *
   *  \param  rtCfgPbObjBuf:       Pointer to buffer for the configuration of the PROFIBUS
   *                               object. (out)
   *  \param  rlcbCfgPbObjBufBuf:  Pointer to buffer for size of buffer (number of bytes)
   *                               for the configuration of the PROFIBUS object. The number of bytes
   *                               copied to ptCfgPbObjBuf is returned in this parameter. If the
   *                               returned size is less than the passed size, only the structure
   *                               elements of ptCfgPbObjBuf up to the returned number of bytes
   *                               were provided. (in/out)
   *  \param  lObjHdl:             Handle of PROFIBUS object of which configuration is requested. (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Provides the configuration of the passed PROFIBUS object.
   */
  virtual long slDcCfgPbObj(T_CFG_PB_OBJ *ptCfgPbObjBuf, long& rlcbCfgPbObjBufBuf, long lObjHdl) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgPn...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgPnDevNameAndIpAddr(char *rszPnDevNameBuf, long& rlcbPnDevNameBufBuf, unsigned char *rszPnDevIpAddrBuf, long& rlcbPnDevIpAddrBufBuf, long lBusNr, long lSlaveAddr, char *pszStationName)
   *
   *  \param  rtCfgPbObjBuf:          Zeiger auf den Puffer fuer den Namen des Geraetes. (out)
   *  \param  rlcbPnDevNameBufBuf:    Zeiger auf den Puffer fuer die Groesse des Puffers fuer
   *                                  den Namen des Geraetes (inkl. '\0') in Byte (count byte). (in/out)
   *  \param  rszPnDevIpAddrBuf:      Zeiger auf den Puffer fuer die IP-Adresse des Geraetes. (out)
   *  \param  rlcbPnDevIpAddrBufBuf:  Zeiger auf den Puffer fuer die Groesse des Puffers fuer
   *                                  die IP-Adresse des Geraetes in Byte (count byte). (in/out)
   *  \param  lBusNr:                 Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr) (in)
   *  \param  lSlaveAddr:             Nummer (Adresse) des Geraetes (Slaves) am PROFINET (PROFIBUS). (in)
   *  \param  pszStationName:         Zeiger auf den Namen der Station, von der die Werte
   *                                  geliefert werden sollen. (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert den Namen und die IP-Adresse fuer das PROFINET-Geraet
   *  (PROFIBUS-Slave) am uebergebenen Bus mit der uebergebenen
   *  Geraetenummer (Slaveadresse), fuer die Station mit dem
   *  uebergebenen Stationsnamen.
   *  Wird in pdwcbPnDevNameBufBuf der Wert 0 uebergeben, liefert die
   *  Funktion ueber pdwcbPnDevNameBufBuf lediglich die erforderliche
   *  Groesse des ueber pszPnDevNameBuf zu uebergebenden Puffers fuer
   *  den Namen des Geraetes (inkl. '\0') in Byte (number of bytes) zurueck.
   *  Wird in pdwcbPnDevNameBufBuf ein NULL Zeiger uebergeben, liefert
   *  die Funktion fuer den Namen des Geraetes keine Werte zurueck.
   *  In diesen beiden Faellen kann in pszPnDevNameBuf ein NULL Zeiger
   *  uebergeben werden.
   *  Entsprechendes gilt fuer pabyPnDevIpAddrBuf und pdwcbPnDevIpAddrBufBuf.
   *  Im Puffer der IP-Adresse wird im niederwertigsten Byte (0) das ganz
   *  links dargestellte und im hoechstwertigen Byte das ganz rechts
   *  dargestellte Byte der IP-Adresse geliefert, z.B.
   *  fuer
   *    '192.168.0.2'
   *  ist
   *     pszPnDevNameBuf[0] = 192;
   *     pszPnDevNameBuf[1] = 168;
   *     pszPnDevNameBuf[2] = 0;
   *     pszPnDevNameBuf[3] = 2;
   */
  virtual long slDcCfgPnDevNameAndIpAddr(char *rszPnDevNameBuf, long& rlcbPnDevNameBufBuf, unsigned char *rszPnDevIpAddrBuf, long& rlcbPnDevIpAddrBufBuf, long lBusNr, long lSlaveAddr, char *pszStationName) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgSlave...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoId(char *rszSlaveIdentNo_DoTypeId, long& rlcbSlaveIdentNo_DoTypeId, long lBusNr, long lSlaveAddr, long lDoId)
   *
   *  \param  rszSlaveIdentNo_DoTypeId:
   *                             [out] Zeiger auf den Puffer fuer den String der Slave-Ident-Nummer
   *                             und die [DO-Sicht-ID,] DO-Typ-ID [und Version der installierten
   *                             SINAMICS-Texte].
   *  \param  rlcbSlaveIdentNo_DoTypeId:
   *                             [in, out] Zeiger auf den Puffer fuer die Groesse des Puffers fuer
   *                             den String der Slave-Ident-Nummer und der [DO-Sicht-ID,] DO-Typ-ID
   *                             [und Version der installierten SINAMICS-Texte] in Byte (count byte).
   *  \param  lBusNr:            [in] Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr)
   *                             des CU- bzw. CX-PROFIBUS-Slaves.
   *  \param  lSlaveAddr:        [in] Adresse des CU- bzw. CX-Geraets am PROFIBUS.
   *  \param  lDoId:             [in] DO-ID (DO-Nr.).
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert fuer den PROFIBUS-Slave am uebergebenen Bus mit der
   *  uebergebenen Slaveadresse und der uebergebenen DO-ID, den
   *  String bestehend aus
   *    - Slave-Ident-Nummer (hexadezimal, vierstellig, mit fuehrenden Nullen),
   *      Unterstrich und
   *    - DO-Typ-ID (dezimal, dreistellig mit fuehrenden Nullen),
   *      sofern keine SINAMICS Sicht- und Versions-spezifischen Texte
   *      installiert sind (die (Eintraege der) Datei
   *      sl_sinamics_text_versions.ini nicht existiert(existieren)) oder
   *    - DO-Sicht-ID der installierten SINAMICS-Texte (dezimal, dreistellig
   *      mit fuehrenden Nullen),
   *      DO-Typ-ID (dezimal, dreistellig mit fuehrenden Nullen),
   *      Unterstrich und
   *      Version der installierten SINAMICS-Texte (dezimal, achtstellig,
   *      mit fuehrenden Nullen), die zur Firmware-Version der Control Unit
   *      gehoeren bzw. die fuer die Firmware-Version der Control Unit geeignet
   *      sind,
   *      sofern SINAMICS Sicht- und Versions-spezifische Texte installiert
   *      sind (die (Eintraege der) Datei sl_sinamics_text_versions.ini
   *      existiert(existieren))
   *  Sofern dem PROFIBUS-Slave das DO nicht zugeordnet ist bzw. kein DO
   *  zugeordnet werden kann, besteht der gelieferte String lediglich aus der
   *  Slave-Ident-Nummer (hexadezimal, vierstellig, mit fuehrenden Nullen).
   */
  virtual long slDcCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoId(char *rszSlaveIdentNo_DoTypeId, long& rlcbSlaveIdentNo_DoTypeId, long lBusNr, long lSlaveAddr, long lDoId) = 0;

  /*! \fn virtual long slDcCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoIdEx(char *rszSlaveIdentNo_DoTypeId, long& rlcbSlaveIdentNo_DoTypeId, long lBusNr, long lSlaveAddr, long lDoId, char* pszStationName)
   *
   *  \param  rszSlaveIdentNo_DoTypeId:
   *                             [out] Zeiger auf den Puffer fuer den String der Slave-Ident-Nummer
   *                             und die [DO-Sicht-ID,] DO-Typ-ID [und Version der installierten
   *                             SINAMICS-Texte].
   *  \param  rlcbSlaveIdentNo_DoTypeId:
   *                             [in, out] Zeiger auf den Puffer fuer die Groesse des Puffers fuer
   *                             den String der Slave-Ident-Nummer und der [DO-Sicht-ID,] DO-Typ-ID
   *                             [und Version der installierten SINAMICS-Texte] in Byte (count byte).
   *  \param  lBusNr:            [in] Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr)
   *                             des CU- bzw. CX-PROFIBUS-Slaves.
   *  \param  lSlaveAddr:        [in] Adresse des CU- bzw. CX-Geraets am PROFIBUS.
   *
   *  \param  lDoId:             [in] DO-ID (DO-Nr.).
   *  \param  pszStationName:    [in] Zeiger auf den Namen der Station, von der der Wert
   *                             geliefert werden soll.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert fuer die Station mit dem uebergebenen Stationsnamen, fuer den
   *  PROFIBUS-Slave am uebergebenen Bus mit der uebergebenen Slaveadresse
   *  und der uebergebenen DO-ID, den String bestehend aus
   *    - Slave-Ident-Nummer (hexadezimal, vierstellig, mit fuehrenden Nullen),
   *      Unterstrich und
   *    - DO-Typ-ID (dezimal, dreistellig mit fuehrenden Nullen),
   *      sofern keine SINAMICS Sicht- und Versions-spezifischen Texte
   *      installiert sind (die (Eintraege der) Datei
   *      sl_sinamics_text_versions.ini nicht existiert(existieren)) oder
   *    - DO-Sicht-ID der installierten SINAMICS-Texte (dezimal, dreistellig
   *      mit fuehrenden Nullen),
   *      DO-Typ-ID (dezimal, dreistellig mit fuehrenden Nullen),
   *      Unterstrich und
   *      Version der installierten SINAMICS-Texte (dezimal, achtstellig,
   *      mit fuehrenden Nullen), die zur Firmware-Version der Control Unit
   *      gehoeren bzw. die fuer die Firmware-Version der Control Unit geeignet
   *      sind,
   *      sofern SINAMICS Sicht- und Versions-spezifische Texte installiert
   *      sind (die (Eintraege der) Datei sl_sinamics_text_versions.ini
   *      existiert(existieren))
   *  Sofern dem PROFIBUS-Slave das DO nicht zugeordnet ist bzw. kein DO
   *  zugeordnet werden kann, besteht der gelieferte String lediglich aus der
   *  Slave-Ident-Nummer (hexadezimal, vierstellig, mit fuehrenden Nullen).
   */
  virtual long slDcCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoIdEx(char *rszSlaveIdentNo_DoTypeId, long& rlcbSlaveIdentNo_DoTypeId, long lBusNr, long lSlaveAddr, long lDoId, char* pszStationName) = 0;

  /*! \fn virtual long slDcCfgSlaveIdentNoSzBusSlave(char *rszSlaveIdentNo, long& rlcbSlaveIdentNo, long lBusNr, long lSlaveAddr)
   *
   *  \param  rszSlaveIdentNo:   String for the Slave-Ident-Number (out)
   *  \param  rlcbSlaveIdentNo:  Length of the String for the Slave-Ident-Number
   *                             (Byte count)(in and out)
   *  \param  lBusNr:            Bus number (_N_COMPLETE_DPC_ACX.Bus.Nr)
   *                             of the CU- resp. CX-PROFIBUS-Slave
   *  \param  lSlaveAddr:        PROFIBUS-Adress of the CU- resp. CX-Geraets
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets Slave-Ident-Number-String
   *  (Format: hex, 4 digits with leading 0), of the PROFIBUS-Slave
   *  with the given bus number and slave adress
   */
  virtual long slDcCfgSlaveIdentNoSzBusSlave(char *rszSlaveIdentNo, long& rlcbSlaveIdentNo, long lBusNr, long lSlaveAddr) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // CfgSnx...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgSnxFixPtVal(long& rlSnxFixPtValBuf, E_CFG_SNX_FIX_PT_VAL eCfgSnxFixPtVal, ilong lObjHdl)
   *
   *  \param  rlSnxFixPtValBuf:   Referenz auf den Puffer fuer den Festpunktwert. (out)
   *  \param  eCfgSnxFixPtVal:    Enumerator des zu liefernden Festpunktwerts. (in)
   *  \param  lObjHdl:            Handle des Objekts, von dem der Festpunktwert geliefert
   *                              werden soll.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert den durch den uebergebenen Enumerator und das uebergebene
   *         Objekthandle adressierten SINAMICS-Festpunktwert.
   */
  virtual long slDcCfgSnxFixPtVal(long& rlSnxFixPtValBuf, E_CFG_SNX_FIX_PT_VAL eCfgSnxFixPtVal, long lObjHdl) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // CfgSnxFwUpdate...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgSnxFwUpdateIsRunning(bool& rbFwUpdateIsRunningBuf, long lCuObjHdl) = 0;
   *
   *  \param  rbFwUpdateIsRunningBuf:  [out] Pointer to the buffer for the flag which indicates, if the
   *                                   automatic firmware update is running. If the automatic firmware
   *                                   update is running, the buffer is set to TRUE, otherwise the
   *                                   buffer is set to FALSE.
   *  \param  lCuObjHdl:               [in] Handle of the control unit object of which the flag is
   *                                   requested, which indicates, if the automatic firmware update
   *                                   is running. If a value of 0 is given, the function provides
   *                                   the flag which indicates, if the automatic firmware update of
   *                                   any control unit is running. If a control unit object handle
   *                                   is given, the function provides the flag which indicates, if
   *                                   the automatic firmware update of the given control unit is
   *                                   running.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Provides the flag which indicates, if the automatic firmware update of
   *         the given control unit object is running.
   */
  virtual long slDcCfgSnxFwUpdateIsRunning(bool& rbFwUpdateIsRunningBuf, long lCuObjHdl) = 0;

  /*! \fn virtual long slDcCfgSnxFwUpdateProgress(float& rfFwUpdateProgressBuf, long lCuObjHdl) = 0;
   *
   *  \param  rfFwUpdateProgressBuf:  [out] Pointer to the buffer for the progress of the automatic
   *                                  firmware update. The buffer is set to a value between 0.0% and
   *                                  100.0%.
   *  \param  lCuObjHdl:              [in] Handle of the control unit object of which the progress of
   *                                  the automatic firmware update is requested. If a value of 0 is
   *                                  given, the function provides the progress of the automatic
   *                                  firmware update of all control units, i.e. the lowest progress
   *                                  of the firmware update of any control unit. If a control unit
   *                                  object handle is givven, the function provides the progress of
   *                                  the automatic firmware update of the given control unit.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Provides the progress of the automatic firmware update of the given
   *         control unit object.
   */
  virtual long slDcCfgSnxFwUpdateProgress(float& rfFwUpdateProgressBuf, long lCuObjHdl) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgSnxTopo...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgSnxTopo(long *plaTopo, long& rlNumTopoArrayItems, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, long lCuObjHdl)
   *
   *  \param  plaTopo:              Topologie data (Array) (out)
   *  \param  rlNumTopoArrayItems:  Number of array elements (in and out)
   *  \param  eCfgSnxTopoType:      Type of topologie (in)
   *  \param  lCuObjHdl:            Handle of the object (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the SINAMICS topologie data of the given type of topologie
   *  for the given object
   */
  virtual long slDcCfgSnxTopo(DC_PA_WORD psaTopo, long& rlNumTopoArrayItems, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, long lCuObjHdl) = 0;

  /*! \fn virtual long slDcCfgSnxTopoEx(long *plaTopo, long& rlNumTopoArrayItems, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, long lCuObjHdl, long lBusNr, long lSlaveNr, const char* pszStationName)
   *
   *  \param  plaTopo:              Topologie data (Array) (out)
   *  \param  rlNumTopoArrayItems:  Number of array elements (in and out)
   *  \param  eCfgSnxTopoType:      Type of topologie (in)
   *  \param  lCuObjHdl:            Handle of the object (in)
   *  \param  lBusNr:               Bus number (in)
   *  \param  lSlaveNr:             Slave adress (in)
   *  \param  pszStationName:       NCU name (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the SINAMICS topologie data of the given type of topologie
   *  for the given object
   */
  virtual long slDcCfgSnxTopoEx(DC_PA_WORD psaTopo, long& rlNumTopoArrayItems, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, long lCuObjHdl, long lBusNr, long lSlaveNr, const char* pszStationName) = 0;

  /*! \fn virtual long slDcCfgSnxTopoUuid(long& rlTopoUuidHigh, long& rlTopoUuidLow, long lCuObjHdl)
   *
   *  \param  rlTopoUuidHigh:  Higher 32 Bit of the identification number of the topologie data
   *  \param  rlTopoUuidLow:   Lower 32 Bit of the identification number of the topologie data
   *  \param  lCuObjHdl:       Handle of the object (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the universal, unequivocal identification number for
   *  SINAMICS topologie data with the given handle
   */
  virtual long slDcCfgSnxTopoUuid(long& rlTopoUuidHigh, long& rlTopoUuidLow, long lCuObjHdl) = 0;

  /*! \fn virtual long slDcCfgSnxTopoUuidEx(long& rlTopoUuidHigh, long& rlTopoUuidLow, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, long lCuObjHdl, long lBusNr, long lSlaveNr, const char* pszStationName)
   *
   *  \param  rlTopoUuidHigh:  Higher 32 Bit of the identification number of the topologie data
   *  \param  rlTopoUuidLow:   Lower 32 Bit of the identification number of the topologie data
   *  \param  eCfgSnxTopoType: Type of topologie (in)
   *  \param  lCuObjHdl:       Handle of the object (in)
   *  \param  lBusNr:          Bus number (in)
   *  \param  lSlaveNr:        Slave adress (in)
   *  \param  pszStationName:  NCU name (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the universal, unequivocal identification number for
   *  SINAMICS topologie data with the given handle
   */
  virtual long slDcCfgSnxTopoUuidEx(long& rlTopoUuidHigh, long& rlTopoUuidLow, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, long lCuObjHdl, long lBusNr, long lSlaveNr, const char* pszStationName) = 0;

  /*! \fn virtual long slDcCfgSnxTxtFileNameTail(bool& rbTxtVerOfFwVerIsInstalledBuf, long& rlDoViewBuf, long& rlDoTypeBuf, long& rlTxtVersionBuf, long& rlFwVersionBuf, long lObjHdl)
   *
   *  \param  rbTxtVerOfFwVerIsInstalledBuf:  [out] Pointer to the buffer for the flag which indicates, if the
   *          texts of the SINAMICS version are installed, which belongs to the
   *          firmware version of the control unit, to which the DO belongs.
   *  \param  rlDoViewBuf:      [out] Pointer to the buffer for the DO view.
   *  \param  rlDoTypeBuf:      [out] Pointer to the buffer for the DO type.
   *  \param  rlTxtVersionBuf:  [out] Pointer to the buffer for the version of the
   *          installed SINAMICS texts, which belongs to the firmware version of
   *          the control unit resp. which is suitable for the firmware version
   *          of the control unit, to which the DO belongs.
   *          If 0 is returned in this parameter, no view and version specific
   *          SINAMICS texts are installed.
   *  \param  rlFwVersionBuf:   [out] Pointer to the buffer for the firmware version of the
   *          control unit, to which the DO belongs.
   *  \param  lObjHdl:          [in] Handle of the object of which the text file name tail is requested.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Provides the information for the text file name tail of the SINAMICS
   *  fault and parameter text files of the drive object which is associated
   *  with the given object handle.
   */
  virtual long slDcCfgSnxTxtFileNameTail(bool& rbTxtVerOfFwVerIsInstalledBuf, long& rlDoViewBuf, long& rlDoTypeBuf, long& rlTxtVersionBuf, long& rlFwVersionBuf, long lObjHdl) = 0;

  /*! \fn virtual long slDcCfgSnxTxtFileNameTailEx(bool& rbTxtVerOfFwVerIsInstalledBuf, long& rNxTxtFileNameViewBuf, long& rHyTxtFileNameViewBuf, long& rDoViewBuf, long& rDoTypeIdBuf, long& rTxtVersionBuf, long& rFwVersionBuf, long lObjHdl)
   *
   *  \param  rbTxtVerOfFwVerIsInstalledBuf   [out] Pointer to the buffer for the flag which indicates, if the
   *                                          texts of the SINAMICS version are installed, which belongs to the
   *                                          firmware version of the control unit, to which the DO belongs.
   *  \param  rNxTxtFileNameViewBuf           [out] Pointer to the buffer for the SINAMICS ?nx text file name view.
   *  \param  rHyTxtFileNameViewBuf           [out] Pointer to the buffer for the SINAMICS ?hy text file name view.
   *  \param  rDoViewBuf                      [out] Pointer to the buffer for the DO view.
   *  \param  rDoTypeIdBuf                    [out] Pointer to the buffer for the DO type.
   *  \param  rTxtVersionBuf                  [out] Pointer to the buffer for the version of the
   *                                          installed SINAMICS texts, which belongs to the firmware version of
   *                                          the control unit resp. which is suitable for the firmware version
   *                                          of the control unit, to which the DO belongs.
   *                                          If 0 is returned in this parameter, no view and version specific
   *                                          SINAMICS texts are installed.
   *  \param  rFwVersionBuf                   [out] Pointer to the buffer for the firmware version of the
   *                                          control unit, to which the DO belongs.
   *  \param  lObjHdl:                        [in] Handle of the object of which the text file name tail is requested.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Provides the information for the text file name tail of the SINAMICS
   *  fault and parameter text files of the drive object which is associated
   *  with the given object handle.
   */
  virtual long slDcCfgSnxTxtFileNameTailEx(bool& rbTxtVerOfFwVerIsInstalledBuf, long& rNxTxtFileNameViewBuf, long& rHyTxtFileNameViewBuf, long& rDoViewBuf, long& rDoTypeIdBuf, long& rTxtVersionBuf, long& rFwVersionBuf, long lObjHdl) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // CfgSp...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgSpNoAx(long& rlSpNoBuf, long lAxNo) = 0;
   *
   *  \param  rlSpNoBuf:  Referenz auf den Puffer fuer die Spindelnummer. (out)
   *  \param  lAxNo:      Achsnummer (1 ... N_Y_maxnumGlobMachAxes). (in)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Liefert die Spindelnummer der uebergebenen Achse.
   */
  virtual long slDcCfgSpNoAx(long& rlSpNoBuf, long lAxNo) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgState...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgState(long& rlCfgState)
   *
   *  \param  rlCfgState:  Configuration state (out)
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Gets the state of the configuration
   */
  virtual long slDcCfgState(long& rlCfgState) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CfgStation...
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long slDcCfgStationAddress(char *pszStationAddressBuf, long& rlcbStationAddressBufBuf)
   *
   *  \param  pszStationAddressBuf:      Pointer to the buffer for the station address. (out)
   *  \param  rlcbStationAddressBufBuf:  Pointer to the buffer for the size (count of bytes) of
   *                                     the buffer for the station address.
   *                                     If a value of 0 is given, the function provides only the size
   *                                     which is needed for the buffer of the station address.
   *                                     If a value unequal 0 is given, a buffer of this size must be given
   *                                     as buffer for the station address and maximal
   *                                     *pdwcbStationAddressBufBuf bytes are copied to the buffer for the
   *                                     station address. The count of bytes copied to the buffer for the
   *                                     station address is returned.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Provides the address of the station, to which is communicated.
   */
  virtual long slDcCfgStationAddress(char *pszStationAddressBuf, long& rlcbStationAddressBufBuf) = 0;

  /*! \fn virtual long slDcCfgStationName(char *pszStationNameBuf, long& rlcbStationNameBufBuf)
   *
   *  \param  pszStationAddressBuf:   Pointer to the buffer for the station name. (out)
   *  \param  rlcbStationNameBufBuf:  Pointer to the buffer for the size (count of bytes) of
   *                                  the buffer for the station name.
   *                                  If a value of 0 is given, the function provides only the size
   *                                  which is needed for the buffer of the station name.
   *                                  If a value unequal 0 is given, a buffer of this size must be given
   *                                  as buffer for the station name and maximal
   *                                  *pdwcbStationNameBufBuf bytes are copied to the buffer for the
   *                                  station name. The count of bytes copied to the buffer for the
   *                                  station name is returned.
   *
   *  \retval 0 if OK, otherwise error code
   *
   *  \brief Provides the name of the station, to which is communicated.
   */
  virtual long slDcCfgStationName(char *pszStationNameBuf, long& rlcbStationNameBufBuf) = 0;


signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  long slDcQSigLastErrorChanged(long lLastError);
  long slDcQSigLastErrorChanged(QString szLastError);
  long slDcQSigAccessLevelChanged(long lAccessLevel);
  long slDcQSigAccessLevelChanged(QString szAccessLevel);
  long slDcQSigCfgStateChanged(long lCfgState);
  long slDcQSigCfgStateChanged(QString szCfgState);
  long slDcQSigGlobalChgCntChanged(long lGlobalChgCnt);
  long slDcQSigGlobalChgCntChanged(QString szGlobalChgCnt);
  long slDcQSigDpCfgChgCntChanged(long lDpCfgChgCnt);
  long slDcQSigDpCfgChgCntChanged(QString szDpCfgChgCnt);
  long slDcQSigDrvTypeChgCntChanged(long lDrvTypeChgCnt);
  long slDcQSigDrvTypeChgCntChanged(QString szDrvTypeChgCnt);
  long slDcQSigPersistDataChanged(QString szStationName, long lBusNr, long lBusAddr);

protected:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS (protected)
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn SlDcAdapter(QObject* pParent = 0, const char* pName = 0) = 0;
   *  \param  pParent parent of the QObject
   *  \param  pName   intenal name of the object, used for debugging
   *
   *  Creates an SlDcAdapter
  */
  SlDcAdapter(QObject* pParent = 0, const char* pName = 0);
  virtual ~SlDcAdapter(){};

};

class SL_DC_SERVICE_ADAPTER_EXPORT SlDcLocVarCb
{
public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlDcLocVarCb(void);
   *
   *  Constructor
   */
  SlDcLocVarCb(void)
    : m_pSinkPtr(0)
  {
  }

  /*! \fn virtual ~SlDcLocVarCb();
   *
   *  Destructor
   */
  virtual ~SlDcLocVarCb();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  virtual long lastError(long lLastError)
  {
    Q_UNUSED(lLastError);
    return(SL_ERR_SUCCESS);
  }

  virtual long lastError(QString szLastError)
  {
    Q_UNUSED(szLastError);
    return(SL_ERR_SUCCESS);
  }

  virtual long accessLevel(long lAccessLevel)
  {
    Q_UNUSED(lAccessLevel);
    return(SL_ERR_SUCCESS);
  }

  virtual long accessLevel(QString szAccessLevel)
  {
    Q_UNUSED(szAccessLevel);
    return(SL_ERR_SUCCESS);
  }

  virtual long cfgState(long lCfgState)
  {
    Q_UNUSED(lCfgState);
    return(SL_ERR_SUCCESS);
  }

  virtual long cfgState(QString szCfgState)
  {
    Q_UNUSED(szCfgState);
    return(SL_ERR_SUCCESS);
  }

  virtual long globalChgCnt(long lGlobalChgCnt)
  {
    Q_UNUSED(lGlobalChgCnt);
    return(SL_ERR_SUCCESS);
  }

  virtual long globalChgCnt(QString szGlobalChgCnt)
  {
    Q_UNUSED(szGlobalChgCnt);
    return(SL_ERR_SUCCESS);
  }

  virtual long dpCfgChgCnt(long lDpCfgChgCnt)
  {
    Q_UNUSED(lDpCfgChgCnt);
    return(SL_ERR_SUCCESS);
  }

  virtual long dpCfgChgCnt(QString szDpCfgChgCnt)
  {
    Q_UNUSED(szDpCfgChgCnt);
    return(SL_ERR_SUCCESS);
  }

  virtual long drvTypeChgCnt(long lDrvTypeChgCnt)
  {
    Q_UNUSED(lDrvTypeChgCnt);
    return(SL_ERR_SUCCESS);
  }

  virtual long drvTypeChgCnt(QString szDrvTypeChgCnt)
  {
    Q_UNUSED(szDrvTypeChgCnt);
    return(SL_ERR_SUCCESS);
  }

  virtual long persistDataChanged(QString szStationName, long lBusNr, long lBusAddr)
  {
    Q_UNUSED(szStationName);
    Q_UNUSED(lBusNr);
    Q_UNUSED(lBusAddr);
    return(SL_ERR_SUCCESS);
  }

private:

  void setSinkPointer(SlDcCallbackInterface *pSinkPtr)
  {
    m_pSinkPtr = pSinkPtr;
  }
  friend class SlDcCallbackInterface;

  SlDcCallbackInterface *m_pSinkPtr;
};

#endif // SL_DC_SERVICE_ADAPTER_H
