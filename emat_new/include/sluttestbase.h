///////////////////////////////////////////////////////////////////////////////
/*! \file sluttestbase.h
*	\author Dirk Peters
*	\date 21.10.2004
*	\brief header file for SlUtTestBase class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTTESTBASE_H)
#define SLUTTESTBASE_H

#include <QtCore/qstring.h>

#include "slutvisitorbase.h"
#include "slutcommonexport.h"
///////////////////////////////////////////////////////////////////////////////

/*! \class SlUtTestBase
*	this interface is used for implementing a tree structure following the composite design pattern
*	This structure consists	of SlUtTestSuites and SlUtTestCases, where the SlUtTestSuites are containers
*	and SlUtTestCases are leafs. All of this Objects have a name and know their parent. For traversing 
*	a visitor is used following the visitor design pattern (here: SlUtTestVisitorBase ).
*
*
*/
class SL_UT_COMMON_EXPORT SlUtTestBase
{
public:
	
	///////////////////////////////////////////////////////////////////////////
	// Creator
	
	/*!	\fn SlUtTestBase(const QString name)
	*	\param szName of this SlUtTest
	*	\param pParent parent of this SlUtTestBase
	*
	*	Constructor
	*/
	SlUtTestBase(const QString szName, SlUtTestBase* pParent);
	
	/*!	\fn virtual ~SlUtTestBase();
	*
	*	Destructor
	*/
	virtual ~SlUtTestBase();
	///////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////
	// Acsessors
	
	/*!	\fn QString name() const;
	*	\retval name of this test
	*/
	QString name() const;
	
    /*! \fn SlUtTestBase* parent()const
	*	\retval SlUtTestBase* parent of this test or null if root test
	*/
	SlUtTestBase* parent()const;

	///////////////////////////////////////////////////////////////////////////
	// Manipulators
	/*! \fn virtual bool accept(SlUtTestVisitorBase& v) = 0
	*	\param v visitor that wants to visit this test
	*	show the contents of this test to a visitor
	*/
	virtual bool accept(SlUtTestVisitorBase& v) = 0;
private:
	
	///////////////////////////////////////////////////////////////////////////
	//private data
	/*!name of this SlUtTestBase*/
	QString m_szName;
	/*! parent of this SlUtTestBase*/
    SlUtTestBase* m_pParent;

	///////////////////////////////////////////////////////////////////////////
	// Prevent the use of the copy constructor and the default constructor + assignment
	SlUtTestBase();
	SlUtTestBase(SlUtTestBase&);
	SlUtTestBase& operator=(SlUtTestBase& base);
};

#endif//SLUTTESTBASE_H
