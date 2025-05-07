///////////////////////////////////////////////////////////////////////////////
/*! \file   slmamhfkts.h
 *  \author Guenter Ruebig
 *  \date   25.01.2005
 *  \brief  Definition file for class SlMaMHFkts
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_MH_FKTS_H_INCLUDED
#define SL_MA_MH_FKTS_H_INCLUDED


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"



class SlMaMHFktsPrivate;


/*! \class  SlMaMHFkts
 *  \brief  Interface service adapter of auxilary functions
 */
class SL_MA_LOGIC_EXPORT SlMaMHFkts : public SlMaFormLogicBase
{
  Q_OBJECT
  Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaChanStateEnum)
  Q_ENUMS(SlMaConnectStateEnum)

public:

  ///////////////////////////////////////////////////////////////////////////
  // public Enums
  ///////////////////////////////////////////////////////////////////////////

  enum SlMaAuxfuStateMaskEnum
  {
    SL_MA_AUXFU_NOT_AVAILABLE                 = 0x0000,
    SL_MA_AUXFU_COLLECTED_VIA_SEARCH_RUN      = 0x0001,
    SL_MA_AUXFU_OUTPUT_TO_PLC                 = 0x0002,
    SL_MA_AUXFU_OUTPUT_TO_PLC_TRANSFER_ACKN   = 0x0004,
    SL_MA_AUXFU_MANAGED_AND_INTEGRATED_BY_PLC = 0x0008,
    SL_MA_AUXFU_MANAGED_AND_ACKN_BY_PLC       = 0x0010,
    SL_MA_AUXFU_STATUS_MASK                   = 0x001F,
    SL_MA_AUXFU_VALUE_TYPE_LONG               = 0x4000,
    SL_MA_AUXFU_VALUE_TYPE_DOUBLE             = 0x8000,
    SL_MA_AUXFU_VALUE_TYPE_MASK               = 0xC000
  };

  /*! \enum SlMaMHFktsEnum
  *
  *  maximum numbers of served funktion groups
  */
  enum SlMaMHFktsEnum
  {
    SL_MA_MAX_STD_M_GROUPS = 5,
    SL_MA_MAX_STD_H_GROUPS = 3,
    SL_MA_MAX_MOD_GROUPS   = 15
  };

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaMHFkts(const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaMHFkts(const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaMHFkts();
   *
   *  destructor
  */
  virtual ~SlMaMHFkts();

  /////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  /////////////////////////////////////////////////////////////////////////////

  /*! get methods, available after SL_MA_START_LOGIC*/
  QString stdMAuxFunctionValueString(int iIndex);
  QString stdHAuxFunctionValueString(int iIndex);
  QString modAuxFunctionValueString(int iIndex);
  bool modAuxFunctionsAvailable(void);

public slots:

  /////////////////////////////////////////////////////////////////////////////
  // public SLOTS
  /////////////////////////////////////////////////////////////////////////////

signals:

  /////////////////////////////////////////////////////////////////////////////
  // public SIGNALS
  /////////////////////////////////////////////////////////////////////////////

  /*! Signals defining */
  void stdMAuxFunctionValueChanged(int iIndex, QString szValue);  /*!< Signal: Standard-M-Aux-Function value changed*/
  void stdHAuxFunctionValueChanged(int iIndex, QString szValue);  /*!< Signal: Standard-H-Aux-Function value changed*/
  void modAuxFunctionValueChanged(int iIndex, QString szValue);     /*!< Signal: Modale-Aux-Function value changed*/
  void modAuxFunctionStatusChanged(int iIndex, int iStatus);
  void modAuxFunctionsAvailableChanged(bool bModAuxFunctionsAvailable);

private:

  /////////////////////////////////////////////////////////////////////////////
  // private Enums
  /////////////////////////////////////////////////////////////////////////////

  enum SlMaLinkItemStdAuxFunctionsEnum
  {
    E_mVal   = 0,
    E_mAdr,
    E_hVal,
    E_hAdr,
    E_StdAuxFunctionNumElements     // Last Element !!!
  };

  enum SlMaLinkItemModAuxFunctionsEnum
  {
    E_type   = 0,
    E_extension,
    E_valueDo,
    E_valueLo,
    E_status,
    E_ModAuxFunctionNumElements     // Last Element !!!
  };

  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  SlMaMHFktsPrivate* m_pData; // d-pointer

  /////////////////////////////////////////////////////////////////////////////
  // private METHODS
  /////////////////////////////////////////////////////////////////////////////

  /*! copy constructor not allowed */
  SlMaMHFkts(const SlMaMHFkts& rCopy);

  /*! assignment operator not allowed */
  SlMaMHFkts& operator=(const SlMaMHFkts& rCopy);

  /////////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  /////////////////////////////////////////////////////////////////////////////

  void resumeAuxFunction(void);
  void resumeStdAuxFunction(void);
  void resumeModAuxFunction(void);

  void suspendAuxFunction(void);
  void suspendStdAuxFunction(void);
  void suspendModAuxFunction(void);

  void adviseAuxFunction(void);
  void adviseStdAuxFunction(void);
  void adviseModAuxFunction(void);

  void unadviseAuxFunction(void);
  void unadviseStdAuxFunction(void);
  void unadviseModAuxFunction(void);

  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck(bool isInit = true);
  void resumeToNck(void);
  void disconnectToNck(void);
  void suspendToNck(void);
  void connectToLogic(void);
  void disconnectToLogic(void);

  /////////////////////////////////////////////////////////////////////////////
  // private Slots
  /////////////////////////////////////////////////////////////////////////////

private slots:

  void setChanStateSlot(SlMaChanStateEnum chanState);
  void adviseStdAuxFunctionSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSelectedFunctions);
  void adviseModAuxFunctionSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSelectedFunctions);

};

#endif // SL_MA_MH_FKTS_H_INCLUDED
