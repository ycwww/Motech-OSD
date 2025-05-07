///////////////////////////////////////////////////////////////////////////////
/*! \file   slgverror.h
 *  \author Rainer Koltermann (MG)
 *  \date   08.05.2008
 *  \brief  Error number intervals for HMI Solution Line graphics view widget
 *
 *  (C) Copyright Siemens AG A&D MC 2008. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_GV_ERROR_H
#define SL_GV_ERROR_H

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x02100000
//**ModuleName: HMI - SL graphics view widget
//**TextFile:
//**TextContext:

///////////////////////////////////////////////////////////////////////////////
// Help System error codes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// global errors from         0x80000001 to 0x800000FF
// local errors from          0x80000100 to 0x800003FF
//
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:the id of the item group is empty
#define SL_GV_ERROR_EMPTY_ID                    0x80000001
//**Text:no scene set
#define SL_GV_ERROR_NO_SCENE                    0x80000002
//**Text:no active group item
#define SL_GV_ERROR_NO_GROUP                    0x80000003
//**Text:no item generated
#define SL_GV_ERROR_NO_ITEM                     0x80000004
//**Text:an unknown type of item
#define SL_GV_ERROR_UNKNOWN_ITEM_TYPE           0x80000005
//**Text:an item with impossible geometry
#define SL_GV_ERROR_IMPOSSIBLE_GEOMETRY         0x80000010
//**Text:an empty item
#define SL_GV_ERROR_EMPTY_ITEM                  0x80000011
//**Text:an invisible item (not drawn at the moment)
#define SL_GV_ERROR_INVISIBLE_ITEM              0x80000012
//**Text:the streams ends unexpected
#define SL_GV_ERROR_STREAM_ENDS_TOO_EARLY       0x80000020
//**Text:a wrong file format
#define SL_GV_ERROR_WRONG_FILE_FORMAT           0x80000021
//**Text:a wrong file version
#define SL_GV_ERROR_WRONG_FILE_VERSION          0x80000022
//**Text:internal error no private data in scene
#define SL_GV_ERROR_NO_PRIVATE_DATA             0x80000023
//**ErrEndErrorCodes


#endif // SL_GV_ERROR_H
