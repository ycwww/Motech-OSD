///////////////////////////////////////////////////////////////////////////////
/*! \file   m:\ef3frd00_dev_sl_2_6\hmi_prog\include\slsnxtopodriveconftextdefines.h
 *  \author Michael Schlemper / Zapf Joachim
 *  \date   21.11.2006
 *  \brief  Headerfile for the class SlSnxTopoAdapter Drive Configuration text defines used by SCI
 *
 *  The class SlStAdapter implements interface for Sinamics topology.
 *
 *  This file is part of the HMI Solutionline Sinamics Topology Data.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_SNX_TOPO_DRIVE_CONF_TEXT_DEFINES_H_INCLUDED_)
#define SL_SNX_TOPO_DRIVE_CONF_TEXT_DEFINES_H_INCLUDED_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


///////////////////////////////////////////////////////////////////////////////
// Text defines for drive configuration
///////////////////////////////////////////////////////////////////////////////


#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_START_AUTO_DRV_DEV       61409
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_START_AUTO_DRV_DEV_2     4217
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_AUTO_DEV_DEV_RUNNING     61410
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SORT_DOS                 61412
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SORT_DOS_2               4219
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WAIT_REORG_DOS           61414
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SAVE_PARAMETER           4221
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WAIT_RESTART             4222
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WAIT_NC_GATEWAY			  61411

#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SET_TELEGRAMTYPE			  61413
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_RENAME_DOS               4321
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SET_BICOS                4322
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_READ_TOPOLOGY            4323
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SETTOPOTARGET_INIT		  4324 
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SETTOPOTARGET			    4325
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WRITE_P9428				    4326
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WRITE_DOS				      4327
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_LOAD_FIRMWARE			    4336
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_LM_QUICK_COMMISSIONING   4337
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SUPPLY                   60004
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_RENUMBER_COMP_INIT		61215
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_RENUMBER_COMP_IN_PROGRESS 61216
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_RENUMBER_DO_INIT			61217
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_RENUMBER_DO_IN_PROGRESS	61218
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SET_PB_MD              61415

#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_PREPARE_DEL				61237
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_DELETE_COMP_ADAPT_DDS  61238
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SIN_DEL_DO				61271
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SIN_DEL_COMP				61272
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SAVE_DRV_PARAM			61231
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_DELETE_AX_DO				61232
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_DELETE_AX_COMP			61233
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_LOWER_COMP				61234
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_NEW_DEL_COMP_ASSIGN		61235
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_DELETE_COMP_ADAPT_EDS	61236

#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WAIT_DRIVE_SYS			61328

#define IBSUTP_TXT_WAIT_FOR_P9										61323
#define IBSUTP_CHECK_FOR_SETUP_LM                                 61333
#define IBSUTP_CHECK_FOR_SETUP_DRV                                61334

#endif // !defined(SL_SNX_TOPO_ADAPTER_H_INCLUDED_)
