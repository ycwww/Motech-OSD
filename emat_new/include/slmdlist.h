// slmdlist.h: SL (QT) - interface for the slmdlist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLMDLIST_H__9E62EAE6_10F5_49B8_9C05_0F13624C22CC__INCLUDED_)
#define AFX_SLMDLIST_H__9E62EAE6_10F5_49B8_9C05_0F13624C22CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if !defined(SLMD_EXPORT)	
#   if defined(WIN32) || defined(WIN64)	
#	    ifdef SLMDLIST_EXPORTS	
#		    define SLMD_EXPORT  __declspec(dllexport)
#	    else		
#		    define SLMD_EXPORT  __declspec(dllimport)
#	    endif
#   else			// Linux / MAC: no Export Makro
#	    define SLMD_EXPORT	
#   endif
#endif


#include "sllist_ifc.h"
#include <QtCore/QStringList>


class SLMD_EXPORT slmdlistUserListTypeQt
{
public:
    slmdlistUserListTypeQt();
    virtual ~slmdlistUserListTypeQt();
public:
    long        m_lSymbolId;
    long        m_lArrayIdx;
    SLLIST_ENUM m_acxTyp;
    SLACX_AREA  m_area;
    QString     m_szLinkItem;
    QString     m_szValue;
    long        m_lBtssUnit;
    long        m_bChanged;
    long        m_lAttribut;
    bool        m_bReadOnly;
};

class slmdList_priv;

class SLMD_EXPORT slmdlist  
{
public:
	slmdlist();
	virtual ~slmdlist();
public:
#if 0
    long        CreateView      (const sllistCreateType* pCreate, long* plAnzCol, long* pColValue, long eventFunctionAdress); //sllist_CreateViewVB
    void        DeleteView      ();                                                              //sllist_DeleteView
#endif
    long        SetUserData     (const QVector<slmdlistUserListTypeQt>& sllistUsrArr, sllistIfcStruct* pIfc);         //sllist_SetUserDataVB
    long        GetUserViewData (QVector<slmdlistUserListTypeQt>& rSllistUsrArr, sllistIfcStruct* pIfc);
#if 0
    long        GetArray        (long lNumRows, const QStringList& rArray);                      //sllist_GetVbArray
    long        GetValues       (const QVector<sllistValueType>& rValArray);                     //sllist_GetVbValues
    long        GetBitTxtArray  (long lRow, const QVector<sllistCifcBitEnumValueType>& rBitArray);   //sllist_GetVbTextArray
    long        GetEnumTxtArray (long lRow, const QVector<sllistCifcBitEnumValueType>& rEnumArray);  //sllist_GetVbTextArray
    long        GetRecordInfo   (long lGridIdx, const sllist_linkStructType& rElem);             //sllist_GetRecordInfo

    long        SetActPos       (long& rlRowAbs,long& rGridRow, SLLIST_POS_ENUM iPos);           //sllist_SetActPos
    long        SetCmd          (SLLIST_CMD_ENUM iCmd, long lPar1, long lPar2, char* pString);   //sllist_Cmd
    QString     SetCmdString    (SLLIST_CMDSTR_ENUM iCmd, long par1, long par2);                 //sllist_CmdVbString, sllist_CmdVbString2    
    long        SetViewUnits    (const SllistViewUnitType&  Units);                              //sllist_SetViewUnits    
    
    long        GetUserData     (const QVector<sllistUserListType>& rCArray);                    //sllist_GetUserDataVB
    long        SetUserData     (long lAnz, const QVector<sllistUserListType>& rCArray);         //sllist_SetUserDataVB
    long        SetUserDataFile (const char* pKlbFile, const SllistViewUnitType& rUnits);        //sllist_SetUserDataFile    
#endif
private:
    slmdList_priv* m_pData;
};

#endif // !defined(AFX_SLMDLIST_H__9E62EAE6_10F5_49B8_9C05_0F13624C22CC__INCLUDED_)
