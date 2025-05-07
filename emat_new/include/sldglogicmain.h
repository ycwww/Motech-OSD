///////////////////////////////////////////////////////////////////////////////
/*! \file   sldglogicmain.h
 *  \author Matthias Dütsch
 *  \date   05.03.2008
 *  \brief  Header file for public helper functions
 *
 *  This file is part of the HMI Solutionline startup dialog
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLDGLOGICMAIN_H_INCLUDED
#define SLDGLOGICMAIN_H_INCLUDED

#include <QtCore/QString>
#include <QtCore/QDir>
#include "slhmisettingsqt.h"

#if !defined(SL_LOGICMAIN_EXPORT)	
#   if defined(WIN32) || defined(WIN64)	
#	    ifdef SLLOGICMAIN_EXPORT	
#		    define SL_LOGICMAIN_EXPORT  __declspec(dllexport)
#	    else		
#		    define SL_LOGICMAIN_EXPORT  __declspec(dllimport)
#	    endif
#   else			// Linux / MAC: no Export Makro
#	    define SL_LOGICMAIN_EXPORT	
#   endif
#endif
 

class SL_LOGICMAIN_EXPORT SlDgLogicMain 
{
    public:
        SlDgLogicMain(void);
        virtual ~SlDgLogicMain();

        static bool isEKSActive(void);
        static bool removeDirRecursively(const QString& dirName);
};

#endif //SLDGLOGICMAIN_H_INCLUDED
