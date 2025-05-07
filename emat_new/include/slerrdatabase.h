///////////////////////////////////////////////////////////////////////////////
/*! \file   slerrdatabase.h
 *  \author see corresponding Headerfile
 *  \date   21.10.2005
 *  \brief  definition of SlErrDataBase
 *
 *  This file is part of the HMI Solutionline error system
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_ERR_DATABASE)
#define SL_ERR_DATABASE

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMap>

#if defined(WIN32)
#   ifdef SLERR_EXPORTS
#        define SL_ERR_ADAPTER_EXPORT  __declspec(dllexport)
#   else
#        define SL_ERR_ADAPTER_EXPORT  __declspec(dllimport)
#   endif
#else
#   define SL_ERR_ADAPTER_EXPORT
#endif


///////////////////////////////////////////////////////////////////////////
// predefines
///////////////////////////////////////////////////////////////////////////
class SlErrDataBasePrivate;

/*! \class SlErrMap slerrdatabase.h
 *  \brief Brief description of class SlErrDataBase. (optional)
 *
 *  Here comes the detailed description of class SlErrDataBase.
*/
class SL_ERR_ADAPTER_EXPORT SlErrMap : public QMap<long, QString>
{
};

/*! \class SlErrDataBase slerrdatabase.h
 *  \brief Brief description of class SlErrDataBase. (optional)
 *
 *  Here comes the detailed description of class SlErrDataBase.
*/
class SL_ERR_ADAPTER_EXPORT SlErrDataBase
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // ENUMS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlErrDataBase()
     *
     *  Construct a SlErrDataBase.
    */
    SlErrDataBase();


    /*! \fn virtual ~SlErrDataBase()
     *
     *  Destroys a SlErrDataBase.
    */
    virtual ~SlErrDataBase();

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
	/*! \fn QString getModuleName(long nErrorCode);
	 *	\param	nErrorCode	Error code for retrieving module name
	 *	\retval	QString	    module name
	 *
	 *  returns the module name, written in the  *.h file.
	 */
    QString getModuleName(long nErrorCode);

	/*! \fn QString getSubModuleName(long nErrorCode);
	 *	\param	nErrorCode	Error code for retrieving sub module name
	 *	\retval	QString		sub module name
	 *
	 *  returns the sub module name, written in the  *.h file.
	 */
    QString getSubModuleName(long nErrorCode);

	/*! \fn QString getSubModuleSymbol(long nErrorCode);
	 *	\param	nErrorCode	Error code for retrieving sub module symbol
	 *	\retval	QString		sub module symbol
	 *
	 *  returns the sub module symbol, written in the  *.h file.
	 */
    QString getSubModuleSymbol(long nErrorCode);

    /*! \fn QString getErrorText(long nErrorCode);
	 *	\param	nErrorCode	Error code for retrieving error text, including modulecode and submodulecode
	 *	\retval	QString		error text
	 *
	 *  returns the error text, written in the  *.h file. If subModuleCode is 0, the global
     *  error code is returned.
	 */
    QString getErrorText(long nErrorCode);

	/*! \fn QString getErrorSymbol(long nErrorCode);
	 *	\param	nErrorCode	Error code for retrieving error symbol
	 *	\retval	QString		error symbol
	 *
	 *  returns the define from the *.h file, that is used in the source code. If subModuleCode 
     *  is 0, the global error symbol is returned.
	 */
    QString getErrorSymbol(long nErrorCode);

	/*! \fn SlErrMap queryErrorModules(void);
	 *	\retval	SlErrMap	Map of modulenames including their modulecodes
	 *
	 *  returns a list of all available modules, their modulecodes and modulenames
	 */
    SlErrMap queryErrorModules(void);

	/*! \fn SlErrMap queryErrorSubModules(long nModuleCode);
	 *	\param	nModuleCode	modulecode
	 *	\retval	SlErrMap	submodulenames including their submodulecodes
	 *
	 *  returns a list of all available submodules of a module, their modulecodes and modulenames
	 */
    SlErrMap queryErrorSubModules(long nModuleCode);

	/*! \fn SlErrMap queryErrorTexts(long nSubModuleCode);
	 *	\param	nSubModuleCode	modulecode and submodulecode
	 *	\retval	SlErrMap		errortexts including their errorcodes
	 *
	 *  returns a list of all available errortexts of a submodule, the errorcodes and errortexts.
     *  If subModuleCode is 0, the global error codes are returned.
	 */
    SlErrMap queryErrorTexts(long nSubModuleCode);

	/*! \fn SlErrMap queryErrorSymbols(long nSubModuleCode);
	 *	\param	nSubModuleCode  modulecode and submodulecode	
	 *	\retval	SlErrMap	    errorsymbols including their errorcodes	
	 *
	 *  returns a list of all available errorsymbols of a submodule, the errorcodes and.
     *  errorsymbols. The error symbols are the names of the defines, used in the sourcecode.
     *  If subModuleCode is 0, the global error symbols are returned.
	 */
    SlErrMap queryErrorSymbols(long nSubModuleCode);
    
    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
protected:
    ///////////////////////////////////////////////////////////////////////////
    // protected helpers
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
private:
    ///////////////////////////////////////////////////////////////////////////
    // private helpers
    ///////////////////////////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////////////////////////
    // Member variables
    ///////////////////////////////////////////////////////////////////////////
    SlErrDataBasePrivate* m_pData;  /*!< private data members */

    ///////////////////////////////////////////////////////////////////////////
    // not allowed functions:
    ///////////////////////////////////////////////////////////////////////////

};


#endif //SL_ERR_DATABASE



