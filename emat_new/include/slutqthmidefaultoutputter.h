//////////////////////////////////////////////////////////////////////////////
/*!\file slutqthmioutputter.h
*  \author Dirk Peters
*  \date 18.11.200
*  \brief headerfile for SlUtQtHMIDefaultOutputter class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SLUTQTHMIDEFAULTOUTPUTTER_H)
#define SLUTQTHMIDEFAULTOUTPUTTER_H

#include <QtCore/qtextstream.h>
#include <QtCore/qstringlist.h>


#include "slutoutputterbase.h"
#include "sluttestrunnerexport.h"

/*! \clas SlUtQtHMIDefaultOutputter
*	prints results of a test run to a QTextStream in a default- Format
*
*/


class SL_UT_RUNNER_EXPORT SlUtQtHMIDefaultOutputter:public SlUtOutputterBase
{
public:
	SlUtQtHMIDefaultOutputter( QTextStream& out);

	/*! \fn void printPassed(QString file, int line, QString expr, QString desc="")*/
    virtual void printPassed(QString file, int line, QString expr, QString desc="");

	/*! \fn void printFailure( QString path, QString file, int line, QString expr, QString desc="")*/
	virtual void printFailure( QString path, QString file, int line, QString expr, QString desc="");
	
	/*!\fn void printError( QString path, QString File, int line,QString expr, QString desc)*/
	virtual void printError( QString path, QString File, int line,QString expr, QString desc);
	
	/*!\fn void printMessage(QString message)
	*  print a messag which doesn't fit into another categorie
	*/
	virtual void printMessage(QString message);

	/*!\fn void printSummary(QString module,int total, int failed, int error, int moduleDepth)
	*  print a summary for the module "module" which is at depth "moduledepth" with
	*  "total" total tests where "failed" failed and "error" produced unexpected errors
	*/
	virtual void printSummary(QString module,int total, int failed, int error, int moduleDepth,int maxedepth);
	
	virtual void printStatistics( SlUtStatistics* pStatistic) ;
	/*!\fn void flush()
	*  write finally and close outputstream, output finished!
	*/
	virtual void flush();
private:
	///////////////////////////////////////////////////////////////////////////
	//private data

	QTextStream& m_rOut;

	QString m_szLastPath;
	///////////////////////////////////////////////////////////////////////////
	//private helper
	QStringList sortParents( QStringList parents);
	///////////////////////////////////////////////////////////////////////////
	//prevent use of
	//default and copy constructor and assignment operator

	SlUtQtHMIDefaultOutputter();
	SlUtQtHMIDefaultOutputter(SlUtQtHMIDefaultOutputter&);
	SlUtQtHMIDefaultOutputter& operator=(SlUtQtHMIDefaultOutputter&);
};


#endif//SLUTQTHMIDEFAULTOUTPUTTER_H
