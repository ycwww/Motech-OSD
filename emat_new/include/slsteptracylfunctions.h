///////////////////////////////////////////////////////////////////////////////
/*! \file   slsteptracylfunctions.h
 *  \author Walter Daners
 *  \date   12.10.2017
 *  \brief  Namspace definition file for namespace SlStepTracyl
 *
 *  This file is part of the HMI Solutionline StepEditor.
 *
 * (C) Copyright Siemens AG A&D MC 2017. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_STEP_TRACYL_FUNCTIONS_H
#define SL_STEP_TRACYL_FUNCTIONS_H


#include "slsteputilitiesexports.h"
#include "slstepglobal.h"
#include "slstepbaseobject.h"
#include "slstepncconfig.h"
#include "slstepswiveldata.h"
#include <QtCore/QLibrary>
#include <QtWidgets/QWidget>



typedef QMap<int, SlStepTracylInfo> SlTracylDataMapType; 

namespace SlStepTracyl
{   
   /*! \fn SlTracylDataMapType  SlTracyl::getTracylData (int nChannel) const
    *  \return  SlTracylDataMapType
    *
    *  This method retrun all tracyldata from current channel
    */
   SL_STEP_LOGIC_EXPORT SlTracylDataMapType getTracylData (int nChannel);

   /*! \fn SlStepTracylInfo getSelectedTracylData(int nChannel, int nTracylNumber)
    *  \return  SlStepTracylInfo
    *
    *  This method retrun the selected tracyldata from current channel
    */
   SL_STEP_LOGIC_EXPORT SlStepTracylInfo getSelectedTracylData(int nChannel, int nTracylNumber);


   /*! \fn SlStepTracylInfo fillTracylInfo(SlStepTraCylAlternativeCallData tracylData)
    *  \return  SlStepTracylInfo
    *
    *  Bestückt die SlStepTracylInfo mit den Daten aus SlStepTraCylAlternativeCallData und gibt die SlStepTracylInfo zurück
    */
   SL_STEP_LOGIC_EXPORT SlStepTracylInfo fillTracylInfo(SlStepTraCylAlternativeCallData tracylData);


   /*! \fn int getSelectedGeoAxis(SlStepTracylInfo tracylInfo)
    *  \return  SlStepToggle
    *
    *  Diese Funktion bestimmmt den Togglezustand anhand er Geoachse, um die sich die Rundachse dreht.
    */
   SL_STEP_LOGIC_EXPORT int getSelectedGeoAxis(SlStepTracylInfo& rTracylInfo);


}; // <-- namespace SlStepTracyl

#endif // SL_STEP_TRACYL_FUNCTIONS_H

