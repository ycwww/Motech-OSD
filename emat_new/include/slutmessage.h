///////////////////////////////////////////////////////////////////////////////
/*! \file slutmessage.h
*  \author Dirk Peters
*  \date 21.10.2004
*  \brief headerfile for SlUtMessage class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTMESSAGE_H)
#define SLUTMESSAGE_H

#include "slutcommonexport.h"
#include <QtCore/qstring.h>

/*! \class SlUtMessage
*   \brief this class is a wrapper for all data that are needed for communication
*   between a SlUtTestContext and its SlUtTestListeners
*/

class SL_UT_COMMON_EXPORT SlUtMessage
{
public:
	///////////////////////////////////////////////////////////////////////////
	//enums
	/*! \enum enum MessageTypeEnum
	*	specifies the type of message
	*/
	enum MessageTypeEnum
	{
		TESTSTARTED = 0,
		TESTPASSED = 1,	
		TESTFAILED = 2,
		TESTERROR = 3,
		TESTENDED = 4,
		CONTEXTFAILURE = 5,
		EMPTYTESTCASE = 6,
    EXECUTE = 7,
    SAVE = 8,
    UNZIP = 9,
    COPY = 10,
    SETUPENV = 11,
    TEARDOWNENV = 12
	};	
	
	/////////////////////////////////////////////////////////////////////////////
	// Creators
	/*! \fn SlUtMessage(MessageTypeEnum type, QString path, QString expr = "unknown", QString desc ="", QString file = "", int line = 0)
	*	
	*	constructor
	*/
	SlUtMessage(MessageTypeEnum type, QString path, QString expr = "unknown", QString desc ="", QString file = "", int line = 0);
	
	/////////////////////////////////////////////////////////////////////////////
	// Manipulators
	
	/////////////////////////////////////////////////////////////////////////////
	// Accessors
	/*! \fn MessageTypeEnum type()
	*	returns MessageTypeEnum the type of this message
	*/
	MessageTypeEnum type(){return m_nMessageType;}

	/*! \fn QString path()
	*	\retval QString the path where this message was send from
	*/
	QString path(){return m_szPath;}
	
	/*! \fn QString expression()
	*	\retval QString expression
	*/
	QString expression(){return m_szExpr;}
	
	/*! \fn QString file()
	*	\retval QString filename
	*/
	QString file(){return m_szFile;}
	
	/*! \fn QString description()
	*   \retval QString description
	*/	
	QString description(){return m_szDesc;}
	
	/*! \fn int line()
	*	\retval int line in the file
	*/
	int line(){return m_nLine;}
protected:
	///////////////////////////////////////////////////////////////////////////
	//protected helper

private:
	///////////////////////////////////////////////////////////////////////////
	//private helper

	///////////////////////////////////////////////////////////////////////////
	//private data
	/*! type of this message*/
	MessageTypeEnum m_nMessageType;
	
	/*! path to the test this message is about*/
	QString m_szPath;
	
	/*! tested expression*/
	QString m_szExpr;
	
	/*! file where the tested expression is in*/
	QString m_szFile;
	
	/*! optional description for this message*/
	QString m_szDesc;
	
	/*! line in the file where the tested expression is in*/
	int m_nLine;
	
	/////////////////////////////////////////////////////////////////////////////
	// prevent the use of default constructor
	SlUtMessage();
};

#endif//SLUTMESSAGE_H
