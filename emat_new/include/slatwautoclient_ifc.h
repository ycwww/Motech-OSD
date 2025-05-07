///////////////////////////////////////////////////////////////////////////////
/*! \file   slatwautoclient_ifc.h
 *  \author Lothar Herzog
 *  \date   06.06.2014
 *  \brief  Definition file for class SlatwAutoclient_Ifc
 *          to implement an automation client for the ATW it necessery to do the follwing steps:
 *          1) create a DLL project as described in 02_HowTo-PrepareVcProjects.doc and add the C/C++/precompiler macro SLATWAUTOCLIENT_EXPORTS to it
 *          2) derive your class from this interface (SlatwAutoclient_Ifc) and implement the virtual methods for plc_cmd_init, plc_action, plc_cmd_ready and exitAutomation
 *          3) add the dll creator macro CREATE_ATW_AUTO_CLIENT to your cpp-file with your class name
 *          3) in user/slatw.ini set: [ATWASettings] StartATWAutomationClient=<atwwclient_dll_name> ; atwwclient_dll_name is the name of the DLL without extension
 *
 *  This file is part of the HMI Solutionline slatwlogic.dll.
 *
 *  (C) Copyright Siemens AG A&D MC 2014. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_ATW_SLATWAUTOCLIENT_IFC_H_INCLUDED
#define SL_ATW_SLATWAUTOCLIENT_IFC_H_INCLUDED

#include <QtCore/QString>
#include <QtCore/QMap>

#if !defined(SLATW_AUTOCLIENT_EXPORT)    
#   if defined(WIN32) || defined(WIN64)    
#        ifdef SLATWAUTOCLIENT_EXPORTS    
#            define SLATW_AUTOCLIENT_EXPORT  __declspec(dllexport)
#        else        
#            define SLATW_AUTOCLIENT_EXPORT  __declspec(dllimport)
#        endif
#   else            // Linux / MAC: no Export Makro
#        define SLATW_AUTOCLIENT_EXPORT    
#   endif
#endif

/*
already used Testtyp Numbers:
    ncSi - Tests:
        1  = PD  
        2  = XS  
        3  = SPL 
        5  = ES  
        6  = FR  
        7  = SBH 
        8  = SG  
        9  = SE  
        10 = SBC 

    dbSi-Tests:
        20 = POS
        21 = STO
        22 = SS1
        23 = SS2
        24 = SOS
        25 = SLS
        26 = SSM
        27 = SLP
        28 = SBT
        29 = SDI
        30 = SS2E
        31 = SS2ESR
        32 = FLOGIC
*/

class SlatwAutoclient_TestInfo
{
public:
    SlatwAutoclient_TestInfo()
        : m_bAlreadyTested(false),  m_iAxisNumber(0), m_bDirIsPositive(false)
    {
    };
    virtual ~SlatwAutoclient_TestInfo()
    {
    };
public:
    QString                 m_szTestName;
    QString                 m_szKey;            //T<TestTyp_Nr>_<TestInstanceNr>   (e.g T7_1  means the first instance of SBH)
    QString                 m_szTestTyp;        //TestTyp  (e.g. SBH)
    bool                    m_bAlreadyTested;
    int                     m_iAxisNumber;
    bool                    m_bDirIsPositive;   //true, if the drive should be moved in positive direction
    /*
     m_ParamMap for additional testcase specific parameters. The following keys are already used (the first 3 letters show in which testcase they are used)
     m_ParamMap.keys()  return a list of all additional parameters for that test.
     dbSi - tests:
         "SBTBreak"             Brake;           1 or 2  
         "SBTSequence"          Testsequence:    1 or 2  ;TEST_SEQ_1, TEST_SEQ_1
         "SLPPositionArea"      Positionsbereich 1 or 2
         "SLPLimit"             Grenzwert:       1 = SLP_UPPER_POSITIVE; 2 = SLP_LOWER_NEGATIVE
         "SlSLevel"             SLS level        1.. 4

     ncSi - tests:
         "SEPositionArea"       Positionsbereich: 1=SE1 ; 2=SE2
         "SELimit"              Grenzwert::       1=oberer Grenzwert(positive Richtung), 2=unterer Grenzwert(negative Richtung)
         "SGLevel"              SG level 1..4    (1 = SG1; 2 = SG2; 3 = SG3; 4 = SG4)
         "ES_SHSelected"        Not-Halt:: Stoppmodus SH = 1  ; SBH=0
    */
    QMap<QString, QString>  m_ParamMap;         //additional params
};

/*! \class SlatwAutoclient_CallbackIfc slatwautoclient_ifc.h
 *  \brief Callback-Interface to the atw. The implementation of showMessage is done in slatwautomated.dll
 */
class SlatwAutoclient_CallbackIfc
{    
public:
    virtual void showMessage(const QString& szMessage) = 0;
};


/*! \class SlatwAutoclient_Ifc slatwautoclient_ifc.h
 *  \brief Interface for ATW - automation clients
 */
class SlatwAutoclient_Ifc
{    
public:    

    SlatwAutoclient_Ifc(){};
    virtual ~SlatwAutoclient_Ifc(){};
    
    //plc_cmd_init is used to set all the required preconditions and the axis can be moved to a start position. 
    //After this method is called the entry "Test preconditions fullfilled" in the status overview grid must show the green OK- icon
    //with pCallback, you can set messages  for the automation window
    //if retval is != 0 the automated test is canceled
    virtual long    plc_cmd_init (const SlatwAutoclient_TestInfo& testInfo, SlatwAutoclient_CallbackIfc* pCallback) = 0;

    //plc_action is used to do the test movement
    //e.g: STO: move the axis a small way and while moving activate the STO
    //with pCallback, you can set messages  for the automation window
    //if retval is != 0 the automated test is canceled
    virtual long    plc_action   (const SlatwAutoclient_TestInfo& testInfo, SlatwAutoclient_CallbackIfc* pCallback) = 0;

    //plc_cmd_ready can be used to make some initialisations and moves after the test. e.g. move the axis back to the start position
    //with pCallback, you can set messages  for the automation window
    //if retval is != 0 the automated test is canceled
    virtual long    plc_cmd_ready(const SlatwAutoclient_TestInfo& testInfo, SlatwAutoclient_CallbackIfc* pCallback) = 0;

    //exitAutomation is called after after the softkey exit was pressed, or the selected run function has stopped 
    //(e.g. run group => exitAutomation is called after the last test in the group has tested).
    virtual void exitAutomation(SlatwAutoclient_CallbackIfc* pCallback) = 0;

};

extern "C" SLATW_AUTOCLIENT_EXPORT SlatwAutoclient_Ifc* sl_create_autoclient();


//creator function: This makro must be set in the cpp- File of the derived class with the name of the derived class  (e.g. CREATE_ATW_AUTO_CLIENT(myAutolient) )
#define CREATE_ATW_AUTO_CLIENT(n)                                   \
extern "C" SLATW_AUTOCLIENT_EXPORT SlatwAutoclient_Ifc*             \
                sl_create_autoclient()                              \
                {                                                   \
                    SlatwAutoclient_Ifc* pIfc = new n;              \
                    return pIfc;                                    \
                }                                                   \


#endif //SL_ATW_SLATWAUTOCLIENT_IFC_H_INCLUDED



