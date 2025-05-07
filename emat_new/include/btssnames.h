///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   12.08.2014
 *
 *  This file is part of the HMI Solutionline simulation.
 *
 *  This file has been automatically generated from common.xml.
 *
 *  (C) Copyright Siemens AG I DT MC 2014. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef BTSSNAMES_H
#define BTSSNAMES_H

#include <QtCore/QString>
#include "btssdef.h"

QString toString(const BtssVariable &variable);
const char *getBTSSAreaName(BtssArea area);
const char *getBTSSBausteinName(BtssBaustein baustein);
const char *getBTSSVariableName(BtssArea area, BtssBaustein baustein, unsigned int column);

#endif // BTSSNAMES_H
