/* ********************************************************************** */
/* Sourcefile:      slqmdlist.h                                           */
/* Project:         SOLUTION LINE                                         */
/*                                                                        */
/* Department:      SIEMENS AG                                            */
/*                  MC RD 71                                              */
/*                                                                        */
/* First author:    Lothar Herzog                                         */
/* Other authors:   <name> <name> ...                                     */
/* ********************************************************************** */
/* Copyright (C) Siemens AG 2000 - 2012                                   */
/* All Rights Reserved.  Confidential                                     */
/* ********************************************************************** */


/* Description */

/*! \file slqmdlist.h: slqmdlist interface.
*/
#if !defined(SLQMDLIST_H__E8A32485_69FE_4FF4_9C3E_5670D6687D25__INCLUDED_)
#define SLQMDLIST_H__E8A32485_69FE_4FF4_9C3E_5670D6687D25__INCLUDED_


#if !defined(SLQMDLIST_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SLMDLIST_EXPORTS
#           define SLQMDLIST_EXPORT  __declspec(dllexport)
#       else
#           define SLQMDLIST_EXPORT  __declspec(dllimport)
#       endif
#   else            // Linux / MAC: no Export Makro
#       define SLQMDLIST_EXPORT
#   endif
#endif

#include <QtCore/QString>
#include <QtCore/QVector>
#include "slacxenums.h"
#include "sllist_acxtyp.h"
#include "slmdtext.h"


class SLQMDLIST_EXPORT SlQMdList_LinkElem
{
public:
    SlQMdList_LinkElem();
    virtual ~SlQMdList_LinkElem();
public:
    long             m_lSymbId;          // param number
    SLACX_AREA       m_area;             //nc, channel, axis, drive
    SLLIST_ENUM      m_acxTyp;           //machine data, setting data, axis data, drive data    
    long             m_lBtssUnit;        //Btss-Unit
    const char*      m_pName;            //Symbolic name
    long             m_lArrIdx;          //-1=no Array;  else ArrayIndex, usually used as input-parameter for GetLinkItem or GetText... functions
    long             m_lArrayLen;        //Arraylen of the first dimension of the corresponding parameter
    long             m_lArrayLen_2;      //Arraylen for the second dimension of the corresponding parameter
    long             m_lArrayLen_3;      //Arraylen for the third dimension of the corresponding parameter
    long             m_StringLen;        //string len for parameters of m_DataType = ACX_DATATYPE_STRING 
    Acx_DataType     m_DataType;         //Acx_DataType
    Acx_DisplayType  m_DisplayType;      //Acx_DisplayType
    Acx_Unit         m_lAcxUnit;         //for param unit text
    unsigned long    m_lLimitType;       //0=no check; 1 = check against lower- and upper limit; 2 = check against upper limit; 3 = check against lower limit
    double           m_dLowerLimit;      //depends on m_lLimitType
    double           m_dUpperLimit;      //depends on m_lLimitType
    long             m_lWriteAccess;     //min accesslevel for writing
    long             m_lNumFloatDigits;  //Anzahl der Nachkommastellen (nur bei  Sinamics; Default = -1)
    bool             m_bIsEnum;          //=1 if value is of type enum  (only for Sinamics)
    bool             m_bReadOnly;        //true=> param is read only    
    Acx_Refresh      m_lNckRefreshCondition; //0=po, 1=re, 2=cf, 3=so, -1=not used  ; only for NC-views not for Sinamics    
};


/* forward definitions */
class SlQMdListPriv;

/*! \class SlMdListProgress slqmdlist.h
 *  \brief Abstract Interface for getting progress events; The client who wants to get the events must derrivate from this class
 *
*/
class SlMdListProgress
{
public:
    virtual long CopyState(const QString& szName, int iState)=0;
};

/*! \class SlQMdList slqmdlist.h
 *  \brief main class for that project
 *
*/
class SLQMDLIST_EXPORT SlQMdList
{
public:    
    /*! \fn SlQMdList();
     *  Constructor
     */
    SlQMdList();

    /*! \fn virtual ~SlQMdList();
     *  Destructor
     */
    virtual ~SlQMdList();
public:
    //automatisch: inch/metrisch; Linear-/Rundachs; Accesslevel
    //für NC- Daten  
    long CreateView(SLACX_AREA area, SLLIST_ENUM acxTyp, long lBtssUnit, const char* pLanguage, long lGudNr = 0);
    //für Antriebsdaten
    long CreateView(long lDcHandle, const char* pLanguage);
    //copy events
    void SetProgress(SlMdListProgress* pCallback);
    //vollständige Liste (nur Array-Element[0])
    long GetList   (QVector<SlQMdList_LinkElem>& rItems);
    //einzelnes Element der Liste. Zurückgeliefert wird der Index in der Liste bzw. -1 im Fehlerfall
    long GetElem   (long lParamNumber);
    //Linkitem für Cap
    QString GetLinkItem         (const SlQMdList_LinkElem& item);
    QString GetSymbolName       (const SlQMdList_LinkElem& item);
    //#####################################################################################################
    //Zugriffe auf mehrdimensionale Arrays
    //Gesamtarraylänge aus m_lArrayLen, m_lArrayLen_2 und m_lArrayLen_3
    long    GetArrayLength(const SlQMdList_LinkElem& item);
    //Indizes für Anzeige in der Liste liefern (anhand des Indexes für slCap)
    void    GetIdx_1_2_3_FromIdx(long lArrIdx, const SlQMdList_LinkElem& item, long &idx1, long &idx2, long &idx3);
    //Anhand der Indizes in der Anzeige, den zugehörigen Index für getLinkItem (für slCap)liefern
    long    GetIdx_FromIdx_1_2_3(const SlQMdList_LinkElem& item, long idx1, long idx2, long idx3);

public:
    //Properties:
    //long setSymbolText(bool bSymbol);      //evtl. automatisch aus Anzeige-MD ermitteln, oder Parameter in CreateView?

public:
    //#####################################################################################################
    //Zugriffsfunktionen für Text
    long    GetS7ErrorText  (long lErrNo, QString& rszErrorText, QString& rszErrorDetails);  //für Antriebsfehler
    QString GetTextParam    (long lParamNumber, long lArrayIdx);
    QString GetTextBit      (long lParamNumber, long lBitIdx, long lArrayIdx = -1);
    long    GetTextBitArray (long lParamNumber, QVector<SlMdTextValue>& rBitArray, long lArrayIdx = -1);
    QString GetTextEnum     (long lParamNumber, long lEnumValue);
    long    GetTextEnumArray(long lParamNumber, QVector<SlMdTextValue>& rEnumArray);
    QString GetTextUnit     (Acx_Unit AcxUnit);        


private:
    SlQMdListPriv* m_pData;   //private data
};

#endif  //!defined(SLQMDLIST_H__E8A32485_69FE_4FF4_9C3E_5670D6687D25__INCLUDED_)
