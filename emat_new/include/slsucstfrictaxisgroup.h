 ///////////////////////////////////////////////////////////////////////////////
/*! \file   SlSuCstFrictAxisGroup.h
*  \author Ricky Berghold
*  \date   04.12.2013
*
*  This file is part of the HMI Solutionline.
*
*  (C) Copyright Siemens AG 2013. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef SLSUCSTFRICT_AXIS_GROUP_H_INCLUDED
#define SLSUCSTFRICT_AXIS_GROUP_H_INCLUDED

#include "slmd.h"
#include "sldcadapter.h"
#include "slsucstfrictmakro.h"
#include "slislmd.h"

class SL_EXP SlSuCstFrictAxisGroup : public QObject
{
    Q_OBJECT

    //private members
private:
    ISlMd* m_pMdAccVar;
    CDcApi* m_pdcApi;

    QList<uint> m_aaMaslDef;
    QList<uint> m_aaMaslState;
    QList<uint> m_GantryAxisType;

    //Variables
    static const uint s_MAX_GANTRY_GROUPS = 8;

    //private funktions
private:
    long getCouplingData();
    long getGantryGroupNumber(const uint AxNo, uint &GantryNumber);
    long getGantryGroup(const uint GantryNumber, QList<uint> &Group);
    long getGantryLeadAxis(const uint GantryNumber, uint &LeadAxis);
    long getMsMasterAxis(const uint AxNo, uint &Master);
    long isGantryLead(const uint uAxNo, bool &bIsGantryLead);
    long isInGantryGroup(const uint AxNo, bool &bIsMember);
    long isInMsCoupling(const uint AxNo, bool &bIsMember);
    long isMasterAxis(const uint uAxNo, bool &bIsMaster);

public:
    //constuctor / destructor
    SlSuCstFrictAxisGroup();
    virtual ~SlSuCstFrictAxisGroup();

    long clearData(); //clear data
    long initialize(ISlMd* pMdAccVar, CDcApi* pdcApi); //connection to service(es)

    bool isCouplingSlaveAxis(const uint uAxNo); //is the axis a slave axis (gantry or MS)
    bool isCouplingLeadAxis(const uint uAxNo); //is the axis a gantry lead axis (gantry or MS)
    bool getSlaveAxesNames(const uint uAxNo, QString& slaveAxesNames); //retrieve a string like "X12, X2"
    bool getSlaveAxesNos(const uint uAxNo, QList<uint>& slaveAxesNos); //retrieve a list of slave axes
    bool getMasterAxisName(const uint uAxNo, QString& masterAxisChnName); //retrieve lead axis name
    
};

#endif //SLSUCSTFRICT_AXIS_GROUP_H_INCLUDED
