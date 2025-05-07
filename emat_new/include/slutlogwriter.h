//////////////////////////////////////////////////////////////////////////////
/*! \file slutlogwriter.h
*  \author Dirk Peters
*  \date 19.01.2005
*  \brief header file for SlUtLogWriter Class 
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTLOGWRITER_H)
#define SLUTLOGWRITER_H



#include "slutcommonexport.h"
//Added by qt3to4:
#include <QtCore/QTextStream>

class QString;
class QTextStream;

#define SLUT_LOG(text) SlUtLogWriter::instance()<<text;

/*! \class SlUtLogWriter
*	singleton for writing
*	
*/

class SL_UT_COMMON_EXPORT SlUtLogWriter
{
public:
	///////////////////////////////////////////////////////////////////////////
	virtual ~SlUtLogWriter();
	///////////////////////////////////////////////////////////////////////////
	static SlUtLogWriter& instance();

	///////////////////////////////////////////////////////////////////////////

	bool open(const QString& fileName);

	bool close();

	SlUtLogWriter& operator<<(const QString& text);

	///////////////////////////////////////////////////////////////////////////

private:
	
	///////////////////////////////////////////////////////////////////////////
	//Creator
	/*! \fn SlUtLogWriter();
	*	constructor
	*
	*/
	SlUtLogWriter();	
	
	///////////////////////////////////////////////////////////////////////////
	//private helper
	/*! \fn QTextStream& stream()
	*	
	*/
	QTextStream& stream();
	
	///////////////////////////////////////////////////////////////////////////
	//private data
	/*! the output stream*/
	QTextStream* m_pStream;

	///////////////////////////////////////////////////////////////////////////
	//prevent use of copy constructor and assignment operator
	SlUtLogWriter(SlUtLogWriter&);
	SlUtLogWriter& operator=(SlUtLogWriter&);
};
#endif//SLUTLOGWRITER_H
