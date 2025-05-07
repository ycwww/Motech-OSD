///////////////////////////////////////////////////////////////////////////////
/*! \file   slcutdatalogic.h
 *  \author Harald Vieten
 *  \date   04.12.2018
 *  \brief  Declaration file for classes of cut data logic
 *
 *  This file is part of the HMI Solutionline SlCutDataLogic.
 *
 *  (C) Copyright Siemens AG A&D MC 2018. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_CUT_DATA_LOGIC_H
#define SL_CUT_DATA_LOGIC_H

#if !defined(SL_CUT_DATA_LOGIC_EXPORT)
#   if defined(WIN32) || defined(WIN64)   
#	    ifdef SLCUTDATALOGIC_EXPORTS
#		    define SL_CUT_DATA_LOGIC_EXPORT __declspec(dllexport)
#	    else
#		    define SL_CUT_DATA_LOGIC_EXPORT __declspec(dllimport)
#	    endif
#   else
#	    define SL_CUT_DATA_LOGIC_EXPORT
#   endif
#endif

#if !defined(SL_CUT_DATA_LOGIC_EXTERN_C)
#  ifdef __cplusplus
#     define SL_CUT_DATA_LOGIC_EXTERN_C    extern "C"
#  else
#     define SL_CUT_DATA_LOGIC_EXTERN_C    extern
#  endif
#endif


#include "slhmitemplatesqt.h"
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QObject>


///////////////////////////////////////////////////////////////////////////////
// GLOGAL DEFINES -- ERROR CODES
///////////////////////////////////////////////////////////////////////////////

// @TODO: Martin: HMI-konforme Umsetzung
// #define SL_CUT_DATA_LOGIC_UNEXPECTED_ERR                    -1L
#define SL_CUT_DATA_LOGIC_SERVER_CONFIG_INVALID_ERR         -2L   //!< exept for the port number config parameters must not be empty

#define SL_CUT_DATA_LOGIC_CREDENTIALS_NOT_INITIALIZED_ERR   -4L   //!< missing credentials or configuration not read in
#define SL_CUT_DATA_LOGIC_CREDENTIALS_CLIENT_ID_ERR         -5L   //!< client ID must not be empty
#define SL_CUT_DATA_LOGIC_CREDENTIALS_CLIENT_SECRET_ERR     -6L   //!< client secret must not be empty
#define SL_CUT_DATA_LOGIC_CREDENTIALS_SCOPE_ERR             -7L   //!< 'scope' must not be empty
#define SL_CUT_DATA_LOGIC_CREDENTIALS_GRANT_TYPE_ERR        -8L   //!< 'GrantType' must not be empty
#define SL_CUT_DATA_LOGIC_CREDENTIALS_USER_ID_ERR           -9L   //!< 'UserId' must not be empty
#define SL_CUT_DATA_LOGIC_CREDENTIALS_INSTANCE_ID_ERR       -10L  //!< 'InstanceId' must not be empty
#define SL_CUT_DATA_LOGIC_ERR_TASK_NOT_SUPPORTED            -16L  //!< given task, i.e. opcode with given cut toggle state not supported

// errors realted to input parameters
#define SL_CUT_DATA_LOGIC_ERR_INPUT_TOOL                    -32L  //!< input parameter for tool name (SL_CUT_DATA_GPS_KEY_T) missing
#define SL_CUT_DATA_LOGIC_ERR_INPUT_NO_MATERIAL             -33L  //!< material is missing
#define SL_CUT_DATA_LOGIC_ERR_INPUT_MATERIALS_NOT_READY     -34L  //!< request for 'my materials' not yet ready
#define SL_CUT_DATA_LOGIC_ERR_INPUT_MATERIAL_INVALID        -35L  //!< name of material is invalid
#define SL_CUT_DATA_LOGIC_ERR_MISSING_UXY                   -36L  //!< missing UXY required for finishing tasks

#define SL_CUT_DATA_LOGIC_ERR_INPUT_PARAMETER_UNKNOWN       -40L  //!< cut data logic does not know key of given input parameter
#define SL_CUT_DATA_LOGIC_ERR_INPUT_FORMAT_INVALID          -41L  //!< an in put parameter has invalid format (type)

// errors related to interpretation of reply
#define SL_CUT_DATA_LOGIC_ERR_REPLY_MISSING_OUTPUT          -65L  //!< JSON object 'TaskOutput' missing in reply
#define SL_CUT_DATA_LOGIC_ERR_REPLY_MISSING_RESULTS         -66L  //!< JSON object 'Results' missing in reply

// errors related to request for 'MyMaterials'
#define SL_CUT_DATA_LOGIC_ERR_MATERIALS_FORMAT              -70L  //!< JSON value describing a 'MyMaterial' is ill-formed
#define SL_CUT_DATA_LOGIC_ERR_NO_MATERIALS                  -71L  //!< Got no or an empty list of materials

///////////////////////////////////////////////////////////////////////////////
// GLOGAL DEFINES -- PARAMETER KEYS
///////////////////////////////////////////////////////////////////////////////

#define SL_CUT_DATA_PARAM_MATERIAL     QLatin1String("SL_CUT_DATA_MATERIAL")
#define SL_CUT_DATA_PARAM_TOOL         QLatin1String("SL_CUT_DATA_TOOL")


///////////////////////////////////////////////////////////////////////////////
// GLOGAL TYPE DEFINITIONS AND ENUMS
///////////////////////////////////////////////////////////////////////////////

/*!
 *  \typedef SlCutDataRequestParamsMap
 *
 *  Defines the parameter type to configure a request.
 */
typedef QMap<QString, QVariant> SlCutDataRequestParamsMap;

/*!
 *  \typedef SlCutDataResultParamsMap
 *
 *  Defines type to return result parameters of a request.
 */
typedef QMap<QString, QVariant> SlCutDataResultParamsMap;

/*!
 *  \typedef SlCutDataRawMaterialNames
 *
 *  Defines type to return a list of names fo user defined materials.
 */
typedef QStringList SlCutDataRawMaterialNames;


///////////////////////////////////////////////////////////////////////////////
// GLOGAL CLASS DEFINITIONS
///////////////////////////////////////////////////////////////////////////////


/*!
 *  \class SlCutDataInterface
 *
 *  Interface to access the cut data logic.
 */
class SlCutDataInterface : public QObject
{
   Q_OBJECT

public:

   /////////////////////////////////////////////////////////////////////////////
   // PUBLIC INTERFACE METHODS
   /////////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual long readConfiguration() = 0;
    *
    *  Method to (re-)read the configuration file.
    *  Must be called before first call to \a request().
    */
   virtual long readConfiguration () = 0;

   /*!
    *  \fn virtual long updateRawMaterials () = 0;
    *
    *  \return 0L on success or an error code on failure.
    *
    *  Starts a request for descriptions of 'my materials' as currently defined
    *  in Walter GPS Online. If another request is active it will be canceled.
    *  \sa rawMaterialsChanged ()
    */
   virtual long updateRawMaterials() = 0;

   /*!
    *  \fn virtual SlCutDataRawMaterialNames getRawMaterialNames () = 0;
    *
    *  Returns a list of available user defined names of raw materials.
    *  No update is performed to synchonize with user defined materials
    *  in Walter GPS Online. \sa updateRawMaterials()
    */
   virtual SlCutDataRawMaterialNames getRawMaterialNames () = 0;

   /*!
    *  \fn virtual long request (const QString& rsOpcode, const SlCutDataRequestParamsMap& rParams) = 0;
    *  
    *  \param rsOpcode      opcode to perform a request for
    *  \param rParams       map with input parameters, keys must be step keys
    *  
    *  Method to start a request for opcode \a rsOpcode with given parameters
    *  \a rParams. \n
    *  A previous request that has not yet finished will be canceled
    *  and any results from previous requests will be silently dropped, 
    *  i. e. the signals requestFinished() and requestFailed() will only
    *  be emitted for the latest request.
    *  Connect to signals requestFinished() and requestFailed() in order to
    *  receive results of the request.
    *  Connect to signals initProgress() and progress() keep track of progress
    *  of the request.
    */
   virtual long request (const QString& rsOpcode, const SlCutDataRequestParamsMap& rParams) = 0;

   /*!
    *  \fn virtual void cancelCutDataRequest () = 0;
    *
    *  Method to cancel current request for cutting data
    *  recommendations, i. e. no further signal will be emitted for
    *  that request.
    */
   virtual void cancelCutDataRequest () = 0;

signals:

   /////////////////////////////////////////////////////////////////////////////
   // SIGNALS
   /////////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn void requestFinished (const QString& rsOpcode,
                                 const SlCutDataResultParamsMap& rParams);
    *
    *  \param rsOpcode        opcode of original request
    *  \param rParams       result parameters (step key -> value)
    *
    *  This signal is emitted when a request for opcode \a rsOpcode
    *  has been finished. Results can be found in \a rParams.
    */
   void requestFinished (const QString& rsOpcode,
                         const SlCutDataResultParamsMap& rParams);

   /*!
    *  \fn void requestFailed (const QString& rsOpcode, const QString& rsMessage);
    *
    *  \param rsOpcode        opcode of original request
    *  \param rsMessage       message to be displayed
    *
    *  This signal is emitted when a request for opcode \a rsOpcode
    *  has been failed.
    */
   void requestFailed (const QString& rsOpcode, const QString& rsMessage);

   /*!
    *  \fn void initProgress (bool bIsProgress, const QString& rsLabelText)
    *
    *  \param bIsProgress        to be defined
    *  \param rsLabelText        text to be displayed in a progress popup
    *
    *  This signal is emitted when a request is send to the server. 
    */
   void initProgress (bool bIsProgress, const QString& rsLabelText);

   /*!
    *  \fn void progress (int nReceived, int nTotal)
    *
    *  \param nReceived          bytes received so far
    *  \param nTotal             total bytes to be received
    *
    *  This signal is emitted from time to time while downloading a servers reply.
    */
   void progress (int nReceived, int nTotal);

   /*!
    * \fn void rawMaterialsChanged ()
    *
    *  Connect to this signal to get informed about changes of the list of
    *  raw materials. \sa updateRawaterials()
    */
   void rawMaterialsChanged ();

public:

   /////////////////////////////////////////////////////////////////////////////
   // PUBLIC CREATORS
   /////////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn SlCutDataInterface ()
    *
    *  Default constructor.
    */
   SlCutDataInterface () = default;

   /*!
    *  \fn virtual ~SlCutDataInterface ()
    *
    *  Default destructor.
    */
   virtual ~SlCutDataInterface () = default;

}; // <-- class SlCutDataInterface


////////////////////////////////////////////////////////////////////////////////
//  GLOBAL FUNCTION FOR PLUGIN MECHANISM
////////////////////////////////////////////////////////////////////////////////

/*!
 *  \fn void* sl_cut_data_exemplar ()
 *
 *  This function is used to export the cut data interface from the dll. A user
 *  can \ref resolve() and call this function. A pointer to the interface is
 *  returned than.
 */
SL_CUT_DATA_LOGIC_EXTERN_C SL_CUT_DATA_LOGIC_EXPORT void* sl_cut_data_exemplar ();

/*!
 *  \typedef SlCutDataExemplarFctPtr
 *
 *  Type of cut data logic interface exemplar function \ref sl_cut_data_exemplar(). 
 *  To use by the plugin mechnism.
 */
typedef SlCutDataInterface* (*SlCutDataExemplarFctPtr)(void);

/*!
 *  \define SL_CUT_DATA_EXEMPLAR_FCT
 *
 *  Name of cut data logic interface exemplar function.
 */
#define SL_CUT_DATA_EXEMPLAR_FCT  "sl_cut_data_exemplar"

 /*!
  *  \define SL_CUT_DATA_LOGIC_LIB_NAME
  *
  *  Name of cut data logic library (without suffix).
  */
#define SL_CUT_DATA_LOGIC_LIB_NAME  "slcutdatalogic"

#endif // !SL_CUT_DATA_LOGIC_H
