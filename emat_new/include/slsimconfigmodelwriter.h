///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   2013-01-09
 *
 *  This file is part of the HMI Solutionline simulation.
 *
 *  (C) Copyright Siemens AG I DT MC 2013. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_SIM_CONFIG_MODEL_WRITER_H
#define SL_SIM_CONFIG_MODEL_WRITER_H

#include <QtCore/QString>
#include "slhmixmlwriter.h"

/// @brief An abstract base class for machine model generation.
/// @see SlXmlWriter
class SlSimConfigModelWriter
{
public:
   virtual ~SlSimConfigModelWriter() {}
   virtual void newLine() = 0;
   virtual void writeOpenTag(const QString &name, const AttrMap &attrs = AttrMap()) = 0;
   virtual void writeCloseTag(const QString &name) = 0;
   virtual void writeAtomTag(const QString &name, const AttrMap &attrs = AttrMap()) = 0;
   virtual void writeString(const QString &text) = 0;
};

#endif // SL_SIM_CONFIG_MODEL_WRITER_H
