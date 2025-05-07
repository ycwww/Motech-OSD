///////////////////////////////////////////////////////////////////////////////
/*! \file   slkclogicglobal.h
 *  \author Adam Gorecki
 *  \date   11.05.2011
 *  \brief  Global definitions of kinematic chain logic
 *
 *  This file is part of the HMI Solutionline, Kinematic Logic Machine/Parameter.
 *
 *  (C) Copyright Siemens AG A&D MC 2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_KC_LOGIC_GLOBAL_H
#define SL_KC_LOGIC_GLOBAL_H


#include "slkclogicexports.h"
#include "slsteptemplates.h"
#include "slhmimakros.h"
#include "slmalogic.h"

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtCore/QPair>
#include <QtCore/QVector>
#include <QtCore/QDataStream>

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   GLOBAL TYPEDEFS AND ENUMS
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// TYPEDEF SlKcLogicPtr
/////////////////////////////////////////////////////////////////////////////

class SlKcLogic;

/*!
 *  \typedef SlKcLogicPtr
 *
 *  Defines a shared pointer with reference counting 
 *  for class \ref SlKcLogic.
 */
typedef SL_KC_LOGIC_EXPORT SlStepSharedPointer<SlKcLogic, SlKcLogic> SlKcLogicPtr;

#if defined(Q_OS_WIN)
   // import/export declaration for template code on windows
   template class SL_KC_LOGIC_EXPORT SlStepSharedPointer<SlKcLogic>;
#endif 

/////////////////////////////////////////////////////////////////////////////
// TYPEDEF SlKcBaseObjectPtr
/////////////////////////////////////////////////////////////////////////////

class SlKcBaseObject;

/*!
 *  \typedef SlKcBaseObjectPtr
 *
 *  Defines a shared pointer with reference counting 
 *  for class \ref SlKcBaseObject.
 */
typedef SlStepSharedPointer<SlKcBaseObject> SlKcBaseObjectPtr;

#if defined(Q_OS_WIN)
   // import/export declaration for template code on windows
   template class SL_KC_LOGIC_EXPORT SlStepSharedPointer<SlKcBaseObject>;
#endif 



///////////////////////////////////////////////////////////////////////////////
//    SL_KC_CHECK_PTR
///////////////////////////////////////////////////////////////////////////////

/*!
 *  \fn void sl_kc_check_ptr (const char* pszPointer,
                                const char* pszFile,
                                long nLine)
 *
 *  \param pszPointer   pointer as a string
 *  \param pszFile      filename
 *  \param nLine        line number
 *
 *  Implements what is done, if pointer \a pszPointer is invalid.
 */
SL_KC_LOGIC_EXPORT void sl_kc_check_ptr (const char* pszPointer,
                                         const char* pszFile,
                                         long nLine);


/*!
 *  \macro SL_KC_CHECK_PTR(POINTER)
 *
 *  Defines a macro to check if the given pointer \a POINTER is invalid, e.g.
 *  \a POINTER is \a 0. In this case an error will be traced and the method
 *  will be quit with return. If \a QT_NO_DEBUG is not set the application
 *  will be quit with \a qFatal().
 */
#define SL_KC_CHECK_PTR(POINTER)                          \
   do {                                                     \
      if (0 == (void*)(POINTER)) {                          \
         sl_kc_check_ptr(#POINTER, __FILE__, __LINE__);   \
         return;                                            \
      }                                                     \
   } while (false)


/*!
 *  \macro SL_KC_CHECK_PTR_RETURN(POINTER,RET_VAL)
 *
 *  Defines a macro to check if the given pointer \a POINTER is invalid, e.g.
 *  \a POINTER is \a 0. In this case an error will be traced and the method
 *  will be quit with returning \a RET_VAL. If \a QT_NO_DEBUG is not set the
 *  application will be quit with \a qFatal().
 */
#define SL_KC_CHECK_PTR_RETURN(POINTER,RET_VAL)           \
   do {                                                     \
      if (0 == (void*)(POINTER)) {                          \
         sl_kc_check_ptr(#POINTER, __FILE__, __LINE__);   \
         return (RET_VAL);                                  \
      }                                                     \
   } while (false)


/*!
 *  \macro SL_KC_CHECK_PTR_NORETURN(POINTER)
 *
 *  Defines a macro to check if the given pointer \a POINTER is invalid, e.g.
 *  \a POINTER is \a 0. In this case an error only  will be traced and the
 *  method will be continued. If \a QT_NO_DEBUG is not set the application will
 *  quit with \a qFatal().
 */
#define SL_KC_CHECK_PTR_NORETURN(POINTER)                 \
   do {                                                     \
      if (0 == (void*)(POINTER)) {                          \
         sl_kc_check_ptr(#POINTER, __FILE__, __LINE__);   \
      }                                                     \
   } while (false)

///////////////////////////////////////////////////////////////////////
//
// Types for data elements
//
///////////////////////////////////////////////////////////////////////

/*!
 * 0x00000000
 * 0x00000001 - 0x0000000f main type (kin. chain, kin. chain elem., prot. area , prot. area elem, coll pair, stl files)
 * 0x00000010 - 0x000000f0 sub type (KCE: OFFSET, ROT_CONST, AXIS_LIN, AXIS_ROT || PA: TOOL, MACHINE, WORKPIECE, FIXTURE, vorhandener
                                    || PAE: BOX, FRAME, CYLINDER, SPHERE, FILE || KC: vorhandene)
 */

/*!
 * \enum SlKcDataTypeAreaEnum
 *
 * Enum to differentiate between elements of kinematic chains
 * and elements of protection areas.
 */
enum SlKcDataTypeAreaEnum
{
   SL_KC_DATA_KINEMATIC_TYPE,
   SL_KC_DATA_PROTECTION_TYPE,
   SL_KC_DATA_FILE_SYS_TYPE
};
Q_DECLARE_FLAGS(SlKcDataTypeArea, SlKcDataTypeAreaEnum);

/*!
 * \enum SlKcElementTypeEnum
 * 
 * defines type of elements we manage in kc logic
 */
enum SlKcElementTypeEnum
{
   SL_KC_KINEMATIC_CHAIN_ELEMENT    = 0x00000001,  //!< kin. chain element object type
   SL_KC_PROT_AREA                  = 0x00000002,  //!< protection area object type
   SL_KC_PROT_AREA_ELEMENT          = 0x00000003,  //!< prot. area element object type
   SL_KC_COLLISION_PAIR             = 0x00000004,  //!< collision pair object type
   SL_KC_3D_FILE                    = 0x00000005,  //!< 3d file object type

   SL_KC_ACTIVE_DATA                = 0x00000006,  //!< active data area object type
   SL_KC_EXAMPLES_DATA              = 0x00000007,  //!< examples area object type
   SL_KC_NETWORK_USB_DATA           = 0x00000008,  //!< network/usb area object type

   SL_KC_KC_DATA                    = 0x00000009,  //!< kinematic chains area object type
   SL_KC_CP_DATA                    = 0x0000000a,  //!< collision pair area object type
   SL_KC_UNFINISHED_DATA            = 0x0000000b,  //!< unfinished elements area object type
   SL_KC_FILE_DATA                  = 0x0000000c,  //!< 3d file area object type
   SL_KC_FILE_DATA_MM               = 0x0000000d,  //!< 3d file in milimeter area object type
   SL_KC_FILE_DATA_M                = 0x0000000e,  //!< 3d file in meter area object type
   SL_KC_FILE_DATA_INCH             = 0x0000000f,  //!< 3d file in inch area object type
   SL_KC_FILE_DATA_NCK_GENERIC      = 0x00000010,  //!< 3d nck generic tool file area object type

   SL_KC_DRIVE                      = 0x00000011,  //!< file system drive object type
   SL_KC_DIRECTORY                  = 0x00000012,  //!< directory object type
   SL_KC_INI_FILE                   = 0x00000013,  //!< data ini-file object type
   SL_KC_PRIMITIVE_FILE             = 0x00000014,  //!< data primitive-file object type
};
/*!
 * \def SlKcElementType
 *
 * we declare QFlags for \a SlKcElementTypeEnum
 */
Q_DECLARE_FLAGS(SlKcElementType, SlKcElementTypeEnum);

/*!
 * \enum SlKcKinematicChainElementTypeEnum
 *
 * Defines sub types of kin. chain element.
 */
enum SlKcKinematicChainElementTypeEnum
{
   SL_KC_NK_OFFSET    = 0x00000100,      //!< type for chain offset element
   SL_KC_NK_ROT_CONST = 0x00000200,      //!< type for chain const rotation element
   SL_KC_NK_AXIS_LIN  = 0x00000300,      //!< type for chain linear axis element
   SL_KC_NK_AXIS_ROT  = 0x00000400,      //!< type for chain rotation axis element
   SL_KC_NK_SWITCH    = 0x00000500       //!< type for chain switch element
};

/*!
 * \def SlKcKinChainElemType
 *
 * we declare QFlags for \a SlKcKinematicChainElementTypeEnum
 */
Q_DECLARE_FLAGS(SlKcKinChainElemType, SlKcKinematicChainElementTypeEnum);
Q_DECLARE_OPERATORS_FOR_FLAGS(SlKcKinChainElemType);

/*!
 * \enum SlKcLogicEcoMaxNum
 *
 * Defines number limits of protection areas, protection area elements and collision pairs for eco mode.
 */
enum SlKcLogicEcoMaxNum
{
   MAX_PROT_AREAS_ECO = 17,         //!< Maximale Anzahl Schutzbereiche für Kollisionvermeidung ECO
   MAX_PROT_AREA_ELEM_ECO = 34,     //!< Maximale Anzahl Schutzbereichselemente für Kollisionvermeidung ECO
   MAX_COLL_PAIRS_ECO = 10          //!< Maximale Anzahl Kollisionspaare für Kollisionvermeidung ECO
};

/*!
 * \enum SlKcProtectionAreaTypeEnum
 *
 * Defines subtypes of protection area.
 */
enum SlKcProtectionAreaTypeEnum
{
   SL_KC_PROT_AREA_TOOL       = 0x00000100,    //!< type for protection area of tool
   SL_KC_PROT_AREA_MACHINE    = 0x00000200,    //!< type for protection area of machine
   SL_KC_PROT_AREA_WORKPIECE  = 0x00000300,    //!< type for protection area of workpiece
   SL_KC_PROT_AREA_FIXTURE    = 0x00000400,    //!< type for protection area of fixture
};

/*!
 * \def SlKcProtAreaType
 *
 * we declare QFlags for \a SlKcProtectionAreaTypeEnum
 */
Q_DECLARE_FLAGS(SlKcProtAreaType, SlKcProtectionAreaTypeEnum);

/*!
 * \enum SlKcProtectionAreaElementTypeEnum
 *
 * Defines sub types of prot. area element.
 */
enum SlKcProtectionAreaElementTypeEnum
{
   // add valid primitive elements here
   SL_KC_NP_BOX               = 0x00000100,        //!< type for protection area box element
   SL_KC_NP_SPHERE            = 0x00000200,        //!< type for protection area sphere element
   SL_KC_NP_CYLINDER          = 0x00000300,        //!< type for protection area cylinder element
   SL_KC_NP_CONE              = 0x00000400,        //!< type for protection area cone element
   SL_KC_NP_PRIMITIVE_MAX     = SL_KC_NP_CONE,     //!< special enum to differentiate between primitive and non-primitive elements 
   SL_KC_NP_TORUS             = 0x00000500,        //!< type for protection area torus element

   // values for not primitive elements need to be higher than SL_KC_NP_PRIMITIVE_MAX(= 0x00000300)
   SL_KC_NP_FRAME             = 0x00000600,        //!< type for protection area frame element
   SL_KC_NP_3D_FILE           = 0x00000700,        //!< type for protection area stl-file element
   SL_KC_NP_TOOL_FILE         = 0x00000800,        //!< type for protection area tool element which is generated by nc
};

/*!
 * \def SlKcProtAreaElemType
 *
 * we declare QFlags for \a SlKcProtectionAreaElementTypeEnum
 */
Q_DECLARE_FLAGS(SlKcProtAreaElemType, SlKcProtectionAreaElementTypeEnum);

/*!
 * \enum SlKcSubTypeAttribTypeEnum
 *
 * Defines sub sub type for elements
 */
enum SlKcSubTypeAttribTypeEnum
{
   SL_KC_NP_PARALLEL_ELEM = 0x00001000 //!< sub type for prot. area element sub types ;) 
};

/*!
 * \def SlKcSubTypeAttribType
 *
 * we declare QFlags for \a SlKcSubTypeAttribTypeEnum
 */
Q_DECLARE_FLAGS(SlKcSubTypeAttribType, SlKcSubTypeAttribTypeEnum);

/*!
 * \enum SlKcSubTypeAttribSimTypeEnum
 *
 * Defines sub sub type for elements in simulation
 */
enum SlKcSubTypeAttribSimTypeEnum
{
   SL_KC_NP_TOOL_ELEM = 0x00010000 //!< sub type for prot. area element for simulation ;) 
};

/*!
 * \def SlKcSubTypeAttribSimType
 *
 * we declare QFlags for \a SlKcSubTypeAttribSimTypeEnum
 */
Q_DECLARE_FLAGS(SlKcSubTypeAttribSimType, SlKcSubTypeAttribSimTypeEnum);

/*!
 * \def SL_KC_ELEM_MASK
 *
 * defines bit mask for \a SlKcElementTypeEnum
 */
#define SL_KC_ELEM_MASK 0x000000ff

/*!
 * \def SL_KC_ELEM_TYPE(type)
 *
 * defines little macro to get element type
 */
#define SL_KC_ELEM_TYPE(type) (type & SL_KC_ELEM_MASK)

/*!
 * \def SL_KC_SUB_TYPE_MASK
 *
 * defines bit mask for types of elements
 */
#define SL_KC_SUB_TYPE_MASK 0x00000f00

/*!
 * \def SL_KC_SUB_TYPE(type)
 *
 * defines little macro to get sub type
 */
#define SL_KC_SUB_TYPE(type) (type & SL_KC_SUB_TYPE_MASK)

/*!
 * \def SL_KC_ATTRIB_TYPE_MASK
 *
 * defines bit mask for attribute types of elements
 */
#define SL_KC_ATTRIB_TYPE_MASK 0x0000f000

/*!
 * \def SL_KC_ATTRIB_TYPE(type)
 *
 * defines little macro to get attribute sub type
 */
#define SL_KC_ATTRIB_TYPE(type) (type & SL_KC_ATTRIB_TYPE_MASK)

/*!
 * \def SL_KC_ATTRIB_SIM_TYPE_MASK
 *
 * defines bit mask for simulation attribute types of elements
 */
#define SL_KC_ATTRIB_SIM_TYPE_MASK 0x000f0000

/*!
 * \def SL_KC_ATTRIB_SIM_TYPE(type)
 *
 * defines little macro to get simulation attribute sub type
 */
#define SL_KC_ATTRIB_SIM_TYPE(type) (type & SL_KC_ATTRIB_SIM_TYPE_MASK)

/*!
 * \def SL_KC_CHECK_TYPE
 *
 * defines little macro for binary check of types.
 */
#define SL_KC_CHECK_TYPE(x,y)    (0 != (x&y))

/*!
 * \enum SlKcDataAreaTypeEnum
 *
 * Defines areas of data. we have till now three of them:
 * "active data", "examples" and "network/usb".
 */
enum SlKcDataAreaTypeEnum
{
   //! activ data area
   SL_KC_ACTIVE_DATA_AREA,
   //! examples data area
   SL_KC_EXAMPLES_AREA,
   //! network/usb data area
   SL_KC_NET_USB_AREA,

   // INSERT NEW AREAS ABOVE!!!!

   //! unknown area
   SL_KC_UNKNOWN_DATA_AREA,
   //! count of area datas
   SL_KC_INDEX_DATA_COUNT = SL_KC_UNKNOWN_DATA_AREA
};
Q_DECLARE_FLAGS(SlKcDataAreaType, SlKcDataAreaTypeEnum);

// defines for automaticly creating names of data files  
#define SL_KC_DATA_MODEL_BASE_NAME     "collavoiddata"
#define SL_KC_DATA_MODEL_NPP_BASE_NAME "primitivedata"
#define SL_KC_DATA_MODEL_FILE_SUFFIX   ".ini"
#define SL_KC_DATA_MODEL_DIR_SUFFIX    ".stl_dir"
#define SL_KC_DATA_MODEL_STL_SUFFIX    ".stl"
#define SL_KC_DATA_MODEL_NPP_SUFFIX    ".npp"

//! default init state of protaction area 
#define SL_KC_PA_DEFAULT_INIT_STATE    QChar(Qt::Key_I)

//! define of initial active state of protaction area
#define SL_KC_PA_INIT_STATE_ACTIVE     QChar(Qt::Key_A)
//! define of initial inactive state of protaction area
#define SL_KC_PA_INIT_STATE_INACTIVE   QChar(Qt::Key_I)
//! define of initial plc triggered stata of protation area
#define SL_KC_PA_INIT_STATE_PLC        QChar(Qt::Key_P)

//! default usage of protaction area element
#define SL_KC_PAE_DEFAULT_USAGE        QChar(Qt::Key_A)

//! define of visualization usage only of protaction area element 
#define SL_KC_PAE_USAGE_VISUALIZATION  QChar(Qt::Key_V)
//! define of collision avoidness usage only of protaction area element 
#define SL_KC_PAE_USAGE_COLLISION      QChar(Qt::Key_C)
//! define of visualization and collision avoidness usage of protaction area element 
#define SL_KC_PAE_USAGE_ALL            QChar(Qt::Key_A)

/*!
 * \enum SlKcErrorIDEnum
 *
 */
enum SlKcErrorIDEnum
{
   SL_KC_NO_ERROR = 0,                       // is all right
   CAP_ERROR_MSG,                            // simple "error" message
   SL_KC_ERR_MSG_ELEM_NO_NAME,               // name is missing
   SL_KC_ERR_MSG_ELEM_NAME_TO_LONG,          // name is to long
   SL_KC_ERR_NAME_HAS_SYSTEM_PREFIX,         // name has system value prefix
   SL_KC_ERR_MSG_ELEM_NAME_NOT_SINGULAR,     // name is not singular
   SL_KC_PASTE_FAILED_NO_MEMORY,             // not enogh memory
   SL_KC_NC_ACTIVATE_FAILED,                 // data activating failed
   SL_KC_PASTE_FAILED_WRONG_PARENT,          // pasted on wrong parent
   SL_KC_PASTE_FAILED,                       // pasting failed
   SL_KC_ERR_MSG_READONLY_AREA,              // read only area
   SL_KC_ERR_MSG_WRONG_INPUT,                // wrong value for data field
   SL_KC_ERR_MSG_WRONG_CONFIG,               // configuration error
   SL_KC_ERR_MSG_LACK_OF_INPUT,              // no input data
   SL_KC_ERR_MSG_INVALID_PARAMETER,          // wrong parameter
   SL_KC_ERR_MSG_SAME_CHAINS,                // two or more chains with same name
   SL_KC_ERR_MSG_SAME_CHAIN_ELEM,            // two or more chain elements with same name
   SL_KC_ERR_MSG_FOLOWER_KCE_EXIST,          // next element already as next in use (graph loop)
   SL_KC_ERR_MSG_FOLOWER_EXIST_S,            // next element already as next in use (graph loop). message in short
   SL_KC_ERR_MSG_NO_FIRST_CHAIN_ELEM,        // chain has not first element
   SL_KC_ERR_MSG_NO_NK_NEXTP,                // parallel chain is not found
   SL_KC_ERR_MSG_TOO_MANY_CHAINS,            // full count of chains 
   SL_KC_ERR_MSG_TOO_MANY_CHAIN_ELEMS,       // full count of chain elements
   SL_KC_ERR_MSG_WRONG_AXIS_DIR,             // direction of axis not defined
   SL_KC_ERR_MSG_INVALID_NAME,               // invalid name
   SL_KC_ERR_MSG_INVALID_KCE_TYPE,           // unknown type of chain element
   SL_KC_ERR_MSG_UNKNOWN_AXIS_FRAME_NAME,    // unknown type of axis or frame
   SL_KC_ERR_MSG_SAME_PROT_AREA,             // name of protection area is not singular
   SL_KC_ERR_MSG_SAME_PROT_AREA_ELEM,        // name of prot. area element is not singular
   SL_KC_ERR_MSG_INVALID_PROT_AREA_TYPE,     // unknown type of protection area
   SL_KC_ERR_MSG_INVALID_PROT_AREA_ELEM_TYPE,// unknown type of prot. area element
   SL_KC_ERR_MSG_NO_PROT_AREA_ELEM,          // prot. area element is not found
   SL_KC_ERR_MSG_NO_3D_FILE,                 // 3d file with name is not found
   SL_KC_ERR_MSG_NO_1ST_PROT_AREA_ELEM,      // prot. area has not first element
   SL_KC_ERR_MSG_INVALID_TOOL_PA_ELEM_TYPE,  // wrong type of first element for prot. area of type "tool"
   SL_KC_ERR_MSG_INVALID_TOOL_PA_ELEM_TYPE_S,// wrong type of first element for prot. area of type "tool", message in short
   SL_KC_ERR_MSG_NO_NP_NEXT,                 // next prot. area element is not found
   SL_KC_ERR_MSG_TOO_MANY_PROT_AREA_ELEM,    // full count of prot. area elements
   SL_KC_ERR_MSG_TOO_MANY_TOOL_PA_ELEM,      // full count of prot. area elements for prot. area of type "tool"
   SL_KC_ERR_MSG_PA_WITH_NO_ELEM,            // prot. area without elements
   SL_KC_ERR_MSG_PA_WITH_NO_REF_TO_KC,       // reference point on kinematic chain for prot. area not found
   SL_KC_ERR_MSG_INVALID_NEXT_ELEM_IN_TOOL_PA,// invalid pointer to next element in prot. area of type "tool"
   SL_KC_ERR_MSG_FOLOWER_PAE_EXIST,          // prot. area element already used in prot. area
   SL_KC_ERR_MSG_PARA_FOLOWER_PAE_EXIST,     // parallel prot. area element already used in prot. area
   SL_KC_ERR_MSG_PARA_FOLOWER_EXIST_S,       // parallel prot. area element already used in prot. area, message in short
   SL_KC_ERR_MSG_NO_PROT_AREA_S,             // prot. area not found
   SL_KC_ERR_MSG_PA_CONNECTED_TO_KC,         // prot. area connected to a kin. chain (for NP_ADD)
   SL_KC_ERR_MSG_TOOL_PA_CONN_TO_KC,         // prot. area "tool" has connection to a kin. chain
   SL_KC_ERR_MSG_TOOL_PA_CONN_TO_KC_S,       // prot. area "tool" has connection to a kin. chain, message in short
   SL_KC_ERR_MSG_INVALID_POS_FOR_PROT_AREA,  // invalid connect to kin. chain.
   SL_KC_ERR_MSG_INVALID_POS_FOR_PROT_AREA_S,// invalid connect to kin. chain, message in short
   SL_KC_ERR_MSG_FOLOWER_PA_ADD_EXIST,       // port. area element already in chain
   SL_KC_ERR_MSG_WRONG_PARA,                 // wrong parameter
   SL_KC_ERR_MSG_WRONG_PLC_BIT,              // wrong plc bit
   SL_KC_ERR_MSG_WRONG_USAGE,                // wrong usage
   SL_KC_ERR_MSG_NO_PROT_AREA,               // prot. area not found
   SL_KC_ERR_MSG_MULTIPLE_PROT_AREA,         // multiple count of one prot. area
   SL_KC_ERR_MSG_INVALID_INIT_STATE,         // wrong init state of prot area
   SL_KC_ERR_MSG_NO_CHAIN,                   // kin. chain not found
   SL_KC_ERR_MSG_NO_CHAIN_ELEM,              // kin. chain element not found
   SL_KC_ERR_MSG_ELEM_NOT_IN_CHAIN,          // kin. chain element not part of a chain
   SL_KC_ERR_MSG_INVALID_CAD_FILE,           // invalid 3d file
   SL_KC_ERR_MSG_NO_COLL_OPT_SET,            // collision avoidness bit not set
   SL_KC_ERR_MSG_NO_NAME_IN_COLLPAIR,        // no prot. area in collpair
   SL_KC_ERR_MSG_NO_PROT_AREA_IN_COLLPAIR,   // prot. area for collpair not found
   SL_KC_ERR_MSG_SAME_NAMES_IN_COLLPAIR,     // same prot. areas in collpair
   SL_KC_ERR_MSG_FREE_PA_IN_COLLPAIR,        // prot. area in collpair not connected to a kin chain
   SL_KC_ERR_MSG_NO_PLC_BIT_IN_PROT_AREA,    // no plc bit for prot. area
   SL_KC_ERR_MSG_COLLPAIR_COMMAND_ERR,       // error due create of collpair
   SL_KC_ERR_MSG_INVALID_ACTIV_PARA,         // invalid activating parameter
   SL_KC_ERR_MSG_INVALID_DEF_KC_PA,          // invalid definition of prot. area or kin. chain
   SL_KC_ERR_MSG_NO_COLLAVOID,               // function "collision avoidance" not there
}; // <-- enum SlKcErrorIDEnum
Q_DECLARE_FLAGS(SlKcErrorID, SlKcErrorIDEnum);


enum SlKcEditAttribEnum
{
  SL_KC_FLAG_INVALID     = 0x00,
  SL_KC_FLAG_HAS_NO_DATA = 0x01,
  SL_KC_FLAG_HAS_DATA    = 0x02,
  SL_KC_FLAG_EDITABLE    = 0x04,
  SL_KC_FLAG_CREATE_NEW  = 0x08,
  SL_KC_FLAG_CAN_COPY    = 0x10,
  SL_KC_FLAG_CAN_CUT     = 0x20,
  SL_KC_FLAG_CAN_PASTE   = 0x40,
  SL_KC_FLAG_CAN_DELETE  = 0x80,
  SL_KC_FLAG_CAN_PROTA   = 0x100,
};
Q_DECLARE_FLAGS(SlKcEditAttributes, SlKcEditAttribEnum);
Q_DECLARE_OPERATORS_FOR_FLAGS(SlKcEditAttributes);

/*!
 * \enum SlKcIdCollectModeEnum
 *
 * declares collecting modes for wanted successor ids
 */
enum SlKcIdCollectModeEnum
{
   SL_KC_COLLECT_ALL_SUCCESSORS,    //!< collect all successors
   SL_KC_COLLECT_ALL_PAE,           //!< collect all protection area elements coming as successors
   SL_KC_COLLECT_ALL_STL_WITH_NAME, //!< collect all prot. area elements with a singular stl file
   SL_KC_COLLECT_ALL_PA_OF_ELEM,    //!< collect all prot. area elements which are direct children of an element
};
Q_DECLARE_FLAGS(SlKcIdCollectMode, SlKcIdCollectModeEnum);

/*!
 * \typedef typedef QList<int> SlKcTypeList
 *
 * defines list with types for elements
 */
typedef QList<int> SlKcTypeList;

/*!
 *  \typedef SlKcGlobalIDList SlKcGlobalIDList
 *
 *  declaration for list of SlKcDataTreeNode's global id
 */
typedef QList<qint32>      SlKcGlobalIDList;

/*
 * \typedef typedef QList<SlKcBaseObjectPtr> SlKcObjectList
 *
 * defines list with SlBaseObjectPtr
 */
typedef QList<SlKcBaseObjectPtr> SlKcObjectList;

/*!
 * \struct SlKcModelChangeKey 
 *
 * declaration of struct for model change counter state for a cached data object.
 */
struct SlKcModelChangeKey
{
   int      m_kinematic;            //!< counter for changes on kinematic model
   int      m_activeStatus;         //!< counter for changes on active status
   int      m_protGeometry;         //!< counter for changes on protection area geometry
   int      m_protCreateDelete;     //!< counter for creating and deleting of protection areas

   // default constructor
   SlKcModelChangeKey(): m_kinematic(-1), m_activeStatus(-1), m_protGeometry(-1), m_protCreateDelete(-1)
   {}

   // equal operator
   bool operator==(const struct SlKcModelChangeKey& rOther) const
   {
      return (m_kinematic==rOther.m_kinematic) 
         && (m_activeStatus==rOther.m_activeStatus)
          && (m_protGeometry==rOther.m_protGeometry) 
          && (m_protCreateDelete==rOther.m_protCreateDelete);
   }

   // unequal operator
   bool operator!=(const struct SlKcModelChangeKey& rOther) const
   {
      return !(*this == rOther);
   }

   // smaler equal operator
   bool operator<=(const struct SlKcModelChangeKey& rOther) const
   {
      return (m_kinematic<=rOther.m_kinematic) 
         && (m_activeStatus<=rOther.m_activeStatus)
         && (m_protGeometry<=rOther.m_protGeometry) 
         && (m_protCreateDelete<=rOther.m_protCreateDelete);
   } 

   // smaler operator
   bool operator<(const struct SlKcModelChangeKey& rOther) const
   {
      return ((m_kinematic        < rOther.m_kinematic)
         ||   (m_activeStatus     < rOther.m_activeStatus)
         ||   (m_protGeometry     < rOther.m_protGeometry) 
         ||   (m_protCreateDelete < rOther.m_protCreateDelete)) && (*this <= rOther);
   } 

}; // <-- struct SlKcModelChangeKey
Q_DECLARE_METATYPE(SlKcModelChangeKey);

/*!
 * \struct SlKcSimComponent
 *
 * this structure declares export element of kinematic chain element for
 * mts model export
 */
struct SlKcSimComponent
{
   /*!
    * unique id of the kinamtic chain element
    */
   qint32 m_objectID;
   /*!
    * name of kinematic chain element
    */
   QString  m_sName;
   /*!
    * name of machine axis in case of axis element
    */
   QString  m_sAxisName;

   /*!
    * name of stl file in case of stl file element
    */
   QString  m_sFileName;

   /// $NP_1ST_PROT
   QString m_firstProt;

   /*!
    * first parameter of element
    * for offset: x value
    * for axis and rotation: x coorditate of axis
    */
   double   m_param1;
   /*!
    * second parameter of element
    * for offset: y value
    * for axis and rotation: y coorditate of axis
    */
   double   m_param2;
   /*!
    * third parameter of element
    * for offset: z value
    * for axis and rotation: z coorditate of axis
    */
   double   m_param3;
   /*!
    * fourth parameter of element
    * for offset: not used
    * for axis: axis offset
    * for rotation: angle of rotation
    */
   double   m_param4;

   /*!
    * type of kinematic chain element
    */
   int      m_nType;

   /*!
    * color off element
    */
   int m_nColor;

   /*!
    * level of detail
    */
   int m_nDLevel;

   /*!
    * local offset of element
    */
   double m_x_off;
   double m_y_off;
   double m_z_off;

   /*!
    * axis for local rotation of element
    */
   double m_x_rotAxis;
   double m_y_rotAxis;
   double m_z_rotAxis;

   /*!
    * angle for local rotation of element
    */
   double m_angle_rotAxis;
   
   /*!
    * flag set if node is parallel
    */
   bool m_bIsParallel;

   /// usage of protection area element
   /** visualisation ('V' or 'v'), collision checking ('C' or 'c'), or both ('A' or 'a') */
   QChar m_usage;

   /// $NP_BIT_NO
   int m_PLCBitNo;

   /// $NP_INDEX
   int m_index0;
   int m_index1;
   int m_index2;

   // is element behind switch in position on
   // default value is true!!
   bool m_bSwitchOn;

   // basic length unit
   SlMaBasicLengthUnitEnum m_basicUnit;
   // basic length unit of stl file
   SlMaBasicLengthUnitEnum m_basicUnitOfStl;

   /// index in NC, e. g., for $NK_NAME[x], with x = m_nNcIndex
   int m_nNcIndex;
   /// index in npp file
   int m_nNcSubIndex;
   //! flag to mark node of prot. area element with npp file data.
   bool m_bIsNpp;
   //! z axis offset for examples for better graphic picture
   double m_nExampleZAxisOffset;

   //! default constructor
   SlKcSimComponent()
      : m_objectID(0), m_sName(QString()), m_sAxisName(QString()), m_sFileName(QString()),
        m_param1(0.0), m_param2(0.0), m_param3(0.0), m_param4(0.0),
        m_nType(0), m_nColor(0), m_nDLevel(0), m_x_off(0.0), m_y_off(0.0), m_z_off(0.0),
        m_x_rotAxis(0.0), m_y_rotAxis(0.0), m_z_rotAxis(0.0), m_angle_rotAxis(0.0), m_bIsParallel(false)
      , m_usage('a')
      , m_PLCBitNo(-1), m_index0(0), m_index1(0), m_index2(0), m_bSwitchOn(true), 
        m_basicUnit(SL_MA_UNIT_MM), m_basicUnitOfStl(SL_MA_UNIT_MM)
      , m_nNcIndex(-1)
      , m_nNcSubIndex(-1)
      , m_bIsNpp(false)
      , m_nExampleZAxisOffset(0.0)
   {}

   bool operator==(const struct SlKcSimComponent& rOther) const
   {
      return (m_objectID==rOther.m_objectID) && (m_sName==rOther.m_sName) && (m_sAxisName==rOther.m_sAxisName) && (m_sFileName==rOther.m_sFileName)
         && (m_nType==rOther.m_nType) && (m_param1==rOther.m_param1)
         && (m_param2==rOther.m_param2) && (m_param3==rOther.m_param3)
         && (m_param4==rOther.m_param4) && (m_nColor==rOther.m_nColor)
         && (m_nDLevel==rOther.m_nDLevel) && (m_angle_rotAxis==rOther.m_angle_rotAxis)
         && (m_x_off==rOther.m_x_off) && (m_y_off==rOther.m_y_off) && (m_z_off==rOther.m_z_off)
         && (m_x_rotAxis==rOther.m_x_rotAxis) && (m_y_rotAxis==rOther.m_y_rotAxis)
         && (m_z_rotAxis==rOther.m_z_rotAxis) && (m_bIsParallel==rOther.m_bIsParallel)
         && (m_usage==rOther.m_usage) && (m_bSwitchOn==rOther.m_bSwitchOn)
         && (m_nNcIndex==rOther.m_nNcIndex)
         && (m_nNcSubIndex==rOther.m_nNcSubIndex)
         && (m_bIsNpp == rOther.m_bIsNpp)
         ;
   }
}; // <-- struct SlKcSimComponent

/*!
 * \struct SlKcSimComponentNode
 *
 * declaration of tree node for mts model
 */
struct SlKcSimComponentNode
{
   //! default constructor
   SlKcSimComponentNode(const SlKcSimComponent& rData) 
      : m_data(rData)
   {}

      //! default constructor
   SlKcSimComponentNode() 
      : m_data(SlKcSimComponent())
   {}

   SlKcSimComponent m_data;            //!< own data
   QList<SlKcSimComponentNode> m_children; //!< children data

}; // <-- struct SlKcSimComponentNode

/*!
 * \typedef QList<SlKcSimComponent> SlKcSimComponents
 *
 * type declaration for list of elements for mts export
 */
typedef QList<SlKcSimComponent> SlKcSimComponents;

/*!
 * \struct SlKcDataModelID
 *
 * this struct declares model id for graphics view
 */
struct SlKcDataModelID
{
   SlKcDataAreaType  m_areaType;          //!< data area type, where model is from
   int               m_nDataHolderID;     //!< data holder id, id of data holder represents by data model. Irrelevant if m_areaType == SL_KC_ACTIVE_DATA_AREA.
   int               m_elemIdxType;       //!< data area sub type, where current element is
   int               m_nUnusedElementIdx; //!< element index of in model element which is in model data holder but is not used by kinematic model of machine

   //! default constructor
   SlKcDataModelID(SlKcDataAreaType areaType = SL_KC_UNKNOWN_DATA_AREA, int dataHolderID = -1, 
      int indexType = 0, int nUnusedElementIdx = -1)
      : m_areaType(areaType), m_nDataHolderID(dataHolderID), 
        m_elemIdxType(indexType), m_nUnusedElementIdx(nUnusedElementIdx)
   {
   }

   static SL_KC_LOGIC_EXPORT const SlKcDataModelID unknown, active;

   bool operator==(const SlKcDataModelID& rOther) const
   {
      return (this->m_areaType == rOther.m_areaType 
           && this->m_nUnusedElementIdx == rOther.m_nUnusedElementIdx) 
           && this->m_elemIdxType == rOther.m_elemIdxType 
           && (this->m_areaType == SL_KC_ACTIVE_DATA_AREA || this->m_nDataHolderID == rOther.m_nDataHolderID);
   }

   bool operator!=(const SlKcDataModelID& rOther) const
   {
      return !((*this) == rOther);
   }

   bool operator<(const SlKcDataModelID& rOther) const
   {
      bool bRet = false;
      // first: area type
      if (this->m_areaType < rOther.m_areaType)
      {
         bRet = true;
      }
      // second: for all areas but active data, data holder id
      else if ((this->m_areaType != SL_KC_ACTIVE_DATA_AREA) && (this->m_nDataHolderID < rOther.m_nDataHolderID))
      {
         bRet = true;
      }
      else if (this->m_elemIdxType < rOther.m_elemIdxType)
      {
         bRet = true;
      }
      // third: unused stl file index
      else if (this->m_nUnusedElementIdx < rOther.m_nUnusedElementIdx)
      {
         bRet = true;
      }
       
      return bRet;
   }
};

inline uint qHash(const SlKcDataModelID& rID)
{
   QByteArray a;
   QDataStream s(&a, QIODevice::WriteOnly);
   s << rID.m_areaType;
   s << rID.m_nDataHolderID;
   s << rID.m_elemIdxType;
   s << rID.m_nUnusedElementIdx;

   return (uint)qChecksum(a.constData(), a.length());
}
/// A 3D vector.
struct SlKcVector3
{
   double x, y, z;
   SlKcVector3() : x(0.0), y(0.0), z(0.0) {}
   SlKcVector3(double x, double y, double z) : x(x), y(y), z(z) {}
};

Q_DECLARE_METATYPE(SlKcVector3);

/// Transport structure for MTS SKCAMERA.
struct SlKcSimCamera
{
   //
   // Types
   //

   enum Type {
      INVALID,
      ORTHOGRAPHIC,
      PERSPECTIVE
   };
   typedef void *HANDLE;

   //
   // Data members.
   //

   Type type;
   HANDLE context;

   SlKcVector3 position;
   SlKcVector3 direction;
   SlKcVector3 up;
   double resolution;
   double NearDistance, FocalDistance, FarDistance;

   //
   // C'tor
   //

   SlKcSimCamera()
      : type(INVALID)
      , context(0)
      , resolution(0.0)
      , NearDistance(0.0)
      , FocalDistance(0.0)
      , FarDistance(0.0)
      {}

   //
   // queries
   //

   bool isValid() const { return type != INVALID; }
};

Q_DECLARE_METATYPE(SlKcSimCamera);

/*!
 * \struct SlKcActiveStateCondition
 *
 */
struct SlKcActiveStateCondition
{
   qint32   m_nGlobalID;   //!< global id of protection area
   unsigned m_nCondition;  //!< nck value of active state condition for protection area
   bool     m_bSwitchOn;   //!< flag to say whether elemnt is on aktive kinematic chain or not

   // default constructor
   SlKcActiveStateCondition(): m_nGlobalID(-1), m_nCondition(0), m_bSwitchOn(true) {}
}; // <-- struct SlKcActiveStateCondition

Q_DECLARE_METATYPE(SlKcActiveStateCondition);

/*!
 * \typedef QList<SlKcActiveStateCondition> SlKcActiveStateCondList 
 *
 */
typedef  QList<SlKcActiveStateCondition> SlKcActiveStateCondList;

/*!
 * \typedef QPair<QString, QString> SlKcFileCacheInfo
 *
 * pair for stl file name and its cache path
 */
typedef QPair<QString, QString> SlKcFileCacheInfo;

/*!
 * \typedef QVector<SlKcFileCacheInfo > SlKcFileCacheInfoList
 *
 * list of stl file names and its cache paths
 */
typedef QVector<SlKcFileCacheInfo > SlKcFileCacheInfoList;

namespace SlKc
{
   QString basicLengthUnitToString(SlMaBasicLengthUnitEnum lengthUnit);
   /// \brief Recognize NPP files.
   /// \details An object is an NPP file if all of the following are true:
   /// \li SL_KC_ELEM_TYPE is SL_KC_PROT_AREA_ELEMENT
   /// \li SL_KC_SUB_TYPE is SL_KC_NP_3D_FILE or SL_KC_NP_TOOL_FILE
   /// \li SL_KC_ITEM_SELECTED_NAME ends with SL_KC_DATA_MODEL_NPP_SUFFIX, ignoring case
   bool SL_KC_LOGIC_EXPORT isNppFile(const SlKcBaseObjectPtr dataObject);
}

#endif // ! SL_KC_LOGIC_GLOBAL_H
