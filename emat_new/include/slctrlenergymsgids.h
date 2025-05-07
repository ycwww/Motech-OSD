///////////////////////////////////////////////////////////////////////////////
/*! \file   slctrlenergymsgids.h
 *  \author Tqffou Hqppi
 *  \date   18.03.2011
 *  \brief  Message IDs for the HMI SL Ctrl-Energy
 *
 *  (C) Copyright Siemens AG 2005
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_CTRLE_MSG_IDS_INCLUDE)
#define SL_CTRLE_MSG_IDS_INCLUDE

#include "slhmimsgids.h"

/*! \enum lCtrlEMessageIds
 *  This enum defines message ids for the SL Ctrl-Energy.
 *
 *  \sa pageMsgIDs
 */
enum SlCtrlEMessageIds
{
	SL_CTRLE_MSG_SHOW_TEXT	 = SL_CTRlE_MSG_ID_MIN,
	SL_CTRLE_MSG_REMOVE_TEXT = SL_CTRlE_MSG_ID_MIN + 1
};



#endif // SL_CTRLE_MSG_IDS_INCLUDE

