//////////////////////////////////////////////////////////////////////////////
/*! \file slutxmloutputter.h
*  \author Dirk Peters
*  \date 26.10.2004
*  \brief headerfile for SlUtXMLOutputter class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////


#if !defined(SLUTXMLOUTPUTTER_H)
#define SLUTXMLOUTPUTTER_H

#include <slutoutputterbase.h>
#include <iostream>

#include "sluttestrunnerexport.h"

/*! \class SlUtXMLOutputter
*   \brief prints test results in a XML format to std::ostream
*
*    use the SlUtQtXMLOutputter for output in files,
*    there are under certain circumstances problems with th std::ostream
*/

class SL_UT_RUNNER_EXPORT SlUtXMLOutputter:public SlUtOutputterBase
{
public:
	/*! \fn SlUtXMLOutputter( std::ostream& out)*/
	SlUtXMLOutputter( std::ostream& out);

	/*! \fn virtual void printPassed(QString file, int line, QString expr, QString desc="")*/
    virtual void printPassed(QString file, int line, QString expr, QString desc="");

	/*! \fn virtual void printFailure( QString path, QString file, int line, QString expr, QString desc="")*/
	virtual void printFailure( QString path, QString file, int line, QString expr, QString desc="");
	
	/*! \fn virtual void printError( QString path, QString File, int line,QString expr, QString desc)*/
	virtual void printError( QString path, QString File, int line,QString expr, QString desc);
	
	/*!\fn void printMessage(QString message)
	*  print a message which doesn't fit into another categorie
	*/
	virtual void printMessage(QString message);

	/*!\fn void printSummary(QString module,int total, int failed, int error, int moduleDepth)
	*  print a summary for the module "module" which is at depth "moduledepth" with
	*  "total" total tests where "failed" failed and "error" produced unexpected errors
	*/
	virtual void printSummary(QString module,int total, int failed, int error, int moduleDepth,int maxedepth);
	
	/*! \fn void printStatistics( SlUtStatistics* pStatistic)*/
	virtual void printStatistics( SlUtStatistics* pStatistic);

	/*!\fn void flush()
	*  write finally and close outputstream, output finished!
	*/
	virtual void flush();
private:
	///////////////////////////////////////////////////////////////////////////
	//private data

	std::ostream& m_rOut;
	///////////////////////////////////////////////////////////////////////////
	//prevent use of
	//default and copy constructor and assignment operator

	SlUtXMLOutputter();
	SlUtXMLOutputter(SlUtXMLOutputter&);
	SlUtXMLOutputter& operator=(SlUtXMLOutputter&);
};

#endif
