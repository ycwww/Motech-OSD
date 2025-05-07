///////////////////////////////////////////////////////////////////////////////
/*! \file slutcommand.h
*  \author Dirk Peters
*  \date 17.01.2005
*  \brief headerfile for SlUtCommand class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTCOMMAND_H)
#define SLUTCOMMAND_H

#include <QtCore/QString>
#include <QtCore/QFile>
#include "slutcommonexport.h"

/*! \class SlUtCommand
*	represents a command which changed the context of a testrun inside a testcase or testsuite
*
*	execute() executes the command and undo() restores the old state if possible( depends on the special command)
*/

class SL_UT_COMMON_EXPORT SlUtCommand
{
public:
	///////////////////////////////////////////////////////////////////////////
	//creators
	/*! \fn virtual ~SlUtCommand()
	*	destructor
	*/
	virtual ~SlUtCommand();

	///////////////////////////////////////////////////////////////////////////
	//Manipulators
	/*! \fn virtual long execute()=0
	*	\retval long 0 if execution failed, otherwise command specific
	*	execute the command
	*/
	virtual long execute()=0;

	/*! \fn virtual bool undo()=0
	*	\retval bool true if successful, false otherwise
	*	try to undo the command
	*/
	virtual bool undo()=0;

	/*! \fn virtual QString command()=0
	*	\retval QString textual description of the command
	*/
	virtual QString command()=0;
};

QString translateFileError(QFile::FileError errorCode);

#endif//SLUTCOMMAND_H
