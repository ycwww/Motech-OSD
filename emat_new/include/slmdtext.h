///////////////////////////////////////////////////////////////////////////////
/*! \file	slmdtext.h
 *  \author Lothar Herzog
 *  \date   30.01.2009
 *  \brief  SlMdText Interface file
 *
 *  This file is part of the HMI Solutionline slmdtext.dll
 *  It contains the declaration of the class SlMdText and includes the other parts of the
 *  SlMdText interfaces. It is used for HMI-Advanced and HMI-SL 
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLMDTEXT_H__9F4E997A_964E_4D69_A780_E97ED681E9EC__INCLUDED_)
#define AFX_SLMDTEXT_H__9F4E997A_964E_4D69_A780_E97ED681E9EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "slmdtext_cifc.h"
#include "sllist_txtinterpret.h"
#include "sllist_define.h"
#include "sllist_acxtyp.h"
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QFlags>
#include <QtCore/QStringMatcher>
#include <QtCore/QRegExp>

#include <QtCore/QFile>
#include <QtCore/QTextStream>



#if !defined(SL_MDTEXT_EXPORT)	
#   if defined(WIN32) || defined(WIN64)	
#	    ifdef SLMDTEXT_EXPORTS	
#		    define SL_MDTEXT_EXPORT  __declspec(dllexport)
#	    else		
#		    define SL_MDTEXT_EXPORT  __declspec(dllimport)
#	    endif
#   else			// Linux / MAC: no Export Makro
#	    define SL_MDTEXT_EXPORT	
#   endif
#endif


/*! \class SlMdTextPriv slmdtext.h
 *  \brief private data for SlMdText
 *
*/
class SlMdTextPriv;
class SlMdTextValue;
class SlMdTextParameterInfo;
class SlMdSearchPatternPriv;
 

class SL_MDTEXT_EXPORT SlMdSearchPattern
{
public:

    /*! \fn SlMdSearchPattern(); 
    *
    *   Constructor
    */
    SlMdSearchPattern();

    /*! \fn SlMdSearchPattern(const QString &sSearchPattern, bool bNotInDescription = false, bool bSearchDown = true, bool bIsRegExpEnabled = true, bool bFirstCall = false);
    *   \param sSearchPattern Search text.
    *   \param bNotInDescription Don't search in description texts.
    *   \param bSearchDown       Search orientation TRUE = down, FALSE = up
    *   \param bIsRegExpEnabled  Use RegExp for search.
    *
    *   Constructor
    */
    SlMdSearchPattern(const QString &sSearchPattern, bool bNotInDescription = false, bool bSearchDown = true, bool bIsRegExpEnabled = true, bool bFirstCall = false);

    /*! \fn ~SlMdSearchPattern();
    *
    *   Destructor
    */
    ~SlMdSearchPattern();


    /*! \fn containsArrayDelimeter() const;
    *
    *   The Pattern contains ":" delimiter.
    */
    bool containsArrayDelimeter() const;

   /*! \fn bool containsOnlyDigits() const;
    *
    *   The Pattern contains only digits.
    */
    bool containsOnlyDigits() const;

   /*! \fn bool containsSquareBracket() const;
    *
    *   The Pattern contains '[' or ']'
    */
    bool containsSquareBracket() const;

   /*! \fn bool containsWildcards() const;
    *
    *   The Pattern contains '*' or '?'
    */
    bool containsWildcards() const;

   /*! \fn bool findIn(const QString &sText) const;
    *  \param sText Source text. 
    *  \retval True if the sourcetext is valid for the given pattern, else false. 
    *
    *  Function to check the source text. 
    */
    bool findIn(const QString &sText) const;

   /*! \fn bool exactMach(const QString &sText) const;
    *  \param sText Source text. 
    *  \retval True if the sourcetext exact valid for the given pattern, else false. 
    *
    *  Function to check the source text. 
    */
    bool exactMach(const QString &sText) const;

   /*! \fn bool isFilterSet() const;
    *
    *  The function returns true if a pattern was set and it's not empty.
    */
    bool isFilterSet() const;

   /*! \fn bool setPattern(const QString &sSearchPattern, bool bNotInDescription = false, bool bSearchDown = true, bool bIsRegExpEnabled = true, bool bFirstCall = false);
    *   \param sSearchPattern Search text.
    *   \param bNotInDescription Don't search in description texts.
    *   \param bSearchDown       Search orientation TRUE = down, FALSE = up
    *   \param bIsRegExpEnabled  Use RegExp for search.
    *   \param bFirstCall        Set use modified search for first call.
    *
    *   Set (or change) search pattern.
    */
    bool setPattern(const QString &sSearchPattern, bool bNotInDescription = false, bool bSearchDown = true, bool bIsRegExpEnabled = true, bool bFirstCall = false);

   /*! \fn bool couldBeParamIDFilter() const;
    *
    *   Return true if the pattern could mach an SymbolID text.
    */
    bool couldBeParamIDFilter() const;

   /*! \fn bool searchDownSet() const;
    *
    *   Return true if the search orientation for the search process is down. 
    */
    bool searchDownSet() const;

    /*! \fn bool searchNotInDescription() const;
    *
    *   Return true if the search is not enabled in the description texts for the search process. 
    */
    bool searchNotInDescription() const;

    /*! \fn bool dispAllArrayItems() const;
    *
    *   Return true if the all array items are to displayed. 
    */
    bool dispAllArrayItems() const;

   /*! \fn bool isParam() const;
    *
    *   Return true if filter pattern is a SymbolID (paramete) pattern
    */
    bool isParam() const;

   /*! \fn bool isFirstCall() const;
    *
    *   Return true if the first call option is set.
    */
    bool isFirstCall() const;


private:

  SlMdSearchPatternPriv *       m_pData;
  //Don't use private members in this class. All Members sould implemented in the priv class.

};

/*! \struct SlMdTextPrivElement
 *
 *  Struct describing the properties for which an SlMdTextPriv data object has been created.
 */
struct SlMdTextPrivElement
{
  friend class SlMdTextPrivContainer;

  SLACX_AREA m_area;      /*!< area-code for the data (e.g. channel specific=>SLACX_AREA_CH) */
  SLLIST_ENUM m_acxTyp;   /*!< acxtyp for the data (e.g. machinedata=>SLLIST_TEA) */
  long m_lBtssUnit;       /*!< BTSS- unit for the selected data (depends on parameter area: MachineaxisNumber, ChannelNumber, DriveNumber ) */
  QString m_szLanguage;   /*!< language abreviation  (e.g. "gr" for HMI-ADV or "deu" for HMI-SL */
  QString m_szFileName;   /*!< name of the .txt file */
  long m_lModification;   /*!< used for sinamics objects and contains the value of r108 for the object
                           *   the modifications are described with e.g. #1000  in the textfile */
  bool m_bPreventReload;  /*!< uses only delivered textfiles and does not copy from drive */

  SlMdTextPrivElement() :
      m_area(SLACX_AREA_UNKNOWN), m_acxTyp(SLLIST_ENUM_UNKNOWN), m_lBtssUnit(0), m_szLanguage(), m_szFileName(),
      m_lModification(0), m_bPreventReload(false), m_pData(0) {}
  SlMdTextPrivElement(SLACX_AREA area, SLLIST_ENUM acxTyp, long lBtssUnit, 
                      const char* szLanguage, const char* szFileName, long lModification, bool bPreventReload) : 
                      m_area(area), m_acxTyp(acxTyp), m_lBtssUnit(lBtssUnit), m_szLanguage(szLanguage), m_szFileName(szFileName),
                      m_lModification(lModification), m_bPreventReload(bPreventReload), m_pData(0) {}

  bool operator==(const SlMdTextPrivElement& element) const
  {
    return m_area == element.m_area && m_acxTyp == element.m_acxTyp && m_lBtssUnit == element.m_lBtssUnit &&
            m_szLanguage == element.m_szLanguage && m_lModification == element.m_lModification && 
            m_bPreventReload == element.m_bPreventReload &&
            m_szFileName == element.m_szFileName;
  }

  private:
    SlMdTextPriv* m_pData;
};

/*! \class SlMdTextPrivContainer
 *  \brief Singleton class storing SlMdTextPriv objects.
 *
 *  Singleton class which stores those SlMdTextPriv objects that have been already created with the properties
 *  for which they were created, and provides them if a SlMdTextPriv object is needed for the same properties. 
 */
class SlMdTextPrivContainer
{
  public:

    /*! \fn getInstance();
     *  \retval Singleton instance.
     *
     *  Provides singleton instance.
     */
    static SlMdTextPrivContainer& getInstance();

    /*! \fn ~SlMdTextPrivContainer();
     *
     *  Destructor. Clears m_listSlMdTextPrivs.
     */
    virtual ~SlMdTextPrivContainer();

    /*! \fn getSlMdTextPriv(SlMdTextPrivElement textPrivProperties);
     *  \param  textPrivProperties  The properties for which an SlMdTextPriv object is needed.
     *  \retval A pointer to an SlMdTextPriv object if there was one for the given properties, 0 otherwise.
     *
     *  Gives a pointer to an SlMdTextPriv object if there had been stored one for the given properties. Gives 0 otherwise.
     */
    SlMdTextPriv* getSlMdTextPriv(SlMdTextPrivElement textPrivProperties);

    /*! \fn addTextData(SlMdTextPrivElement textPrivProperties, SlMdTextPriv* pData);
     *  \param  textPrivProperties  The properties for which the SlMdTextPriv object pData was created.
     *  \param  pData               The SlMdTextPriv object to be stored.
     *
     *  Stores the SlMdTextPriv object which was created for the properties \param textPrivProperties
     *  in m_listSlMdTextPrivs.
     */
    void addTextData(SlMdTextPrivElement textPrivProperties, SlMdTextPriv* pData);

  private:

    SlMdTextPrivContainer() {}
    SlMdTextPrivContainer(const SlMdTextPrivContainer&);
    void operator=(const SlMdTextPrivContainer&);

    QList<SlMdTextPrivElement> m_listSlMdTextPrivs;
};

class SL_MDTEXT_EXPORT SlMdText  
{
public:

    /*! \enum TextTypeEnum
        \brief An enum for the text item of a machinedata/driveparameter
    */ 
    enum TextTypeEnum 
    {
        //! Default value, no text item
        None = 0x0,

        /*! The text item of the symbol ID. 
            E.g: 30110 or r2 */
        SymbolID = 0x1,

        /*! The text item of the symbol text. 
            E.g: $MA_CTRLOUT_MODULE_NR or "Drive operating display" */
        SymbolText = 0x2,

        /*! The text item of the description text. 
            E.g: "Setpoint assignment: module number" or "Drive operating display" */
        Description = 0x4,

        /*! The text of an array element.
            E.g for r37[0] "Inverter, maximum value"
        */
        ArrayText = 0x8,

        /*! The bit texts of a machinedata/drive parameter
        */
        BitTexts = 0x10,

        /*! The enum texts of a machinedata/drive parameter
        */
        EnumTexts = 0x20,

        /*! This text is a combination of the SymbolText and ArrayText items.
            E.g: for r37[0] "Power unit temperatures: Inverter, maximum value"
        */
        FullSymbText = 0x40,

        /*! This text is the Date unit.
            E.g: for r32 "kW"
        */
        UnitText = 0x80
    };

/*! An arbitrary combination of the TextTypeEnum flags. */
#ifdef _DEBUG
    Q_DECLARE_FLAGS(TextTypes, TextTypeEnum)
    //typedef unsigned long TextTypes;  //test
#else
    /* After measuring and analysing the execution times of the Seach/Filter functionality
       it turned out, that using unsigned long values and simply binary operators is more
       efficient than QFlag. That's why we use unsigned long and bit-operators in release
       versions (to have maximal performance), and QFlag in debug mode (to ensure type safety)
    */
    typedef unsigned long TextTypes;
#endif
     


    // creator function
    /*! \fn createObject(const char* pCallerName);
    *  \param       pCallerName     name of the calling module, used for traces only    
    *
    *  \retval the pointer to the created SlMdText; don't forget to delete this pointer after use with deleteObject
    *          zero if no memory could be allocated
    */
    static SlMdText* createObject(const char* szCallerName);    

    /*! \fn deleteObject(SlMdText*& rpSlMdText);
    *   deletes the pointer returned from createObject and set it to zero;
    *   delete function
    */    
    static void deleteObject(SlMdText*& rpSlMdText);     

public:
    
    /*! \fn init(long lDcHandle, const char* szLanguage, long lModification);
    *  \param lDcHandle       datacache handle for the drive object
    *  \param szLanguage      language abreviation  (e.g. "gr" for HMI-ADV or "deu" for HMI-SL
    *  \param lModification   used for sinamics objects and contains the value of r108 for the object
    *                         the modifications are described with e.g. #1000  in the textfile
    *                         to use the extendet modifications in r171, r172 and r173 it's necessary to call setModification before
    *
    *  \retval = number of lines in the textfile
    *
    *  Every time this function is called, all previous allocated memory is released. The szTextFile will be reinterpreted
    *  This function has to be called on every change in the param list (at least one time)
    *  Useful for drives only. This function calls the init-function below with bPreventReload=true
    */
    long         init       (long lDcHandle, const char* szLanguage, long lModification);
    long         init       (long lDcHandle, const char* szLanguage, long lModification, bool bPreventReloadText, bool bPreventReloadPDAcx);
    
    /*! \fn init(SLACX_AREA area, SLLIST_ENUM acxTyp, long lBtssUnit, const char* szLanguage, long lModification);    
    *  \param area            area-code for the data (e.g. channel specific=>SLACX_AREA_CH)
    *  \param acxTyp          acxtyp for the data (e.g. machinedata=>SLLIST_TEA)
    *  \param lBtssUnit       BTSS- unit for the selected data (depends on parameter area: MachineaxisNumber, ChannelNumber, DriveNumber )
    *  \param szLanguage      language abreviation  (e.g. "gr" for HMI-ADV or "deu" for HMI-SL
    *  \param lModification   used for sinamics objects and contains the value of r108 for the object
    *                         the modifications are described with e.g. #1000  in the textfile
    *                         to use the extendet modifications in r171, r172 and r173 it's necessary to call setModification before
    *  \param bPreventReload  uses only delivered textfiles and does not copy textfiles from drive
    *  \param bPreventReloadPDAcx  does not copy PD-acx-files from drive
    *
    *  \retval = number of lines in the textfile
    *
    *  Every time this function is called, all previous allocated memory is released. The szTextFile will be reinterpreted
    *  This function has to be called on every change in the param list (at least one time)
    *  Useful for NCK machine- and setting data
    */
    long         init       (SLACX_AREA area, SLLIST_ENUM acxTyp, long lBtssUnit, const char* szLanguage, long lModification); //(calls the init-function below with bPreventReload=true)
    long         init       (SLACX_AREA area, SLLIST_ENUM acxTyp, long lBtssUnit, const char* szLanguage, long lModification, bool bPreventReload);     
    long         init       (SLACX_AREA area, SLLIST_ENUM acxTyp, long lBtssUnit, const char* szLanguage, long lModification, bool bPreventReload, bool bPreventReloadPDAcx);

    /*! \fn setModification(long lModificationBits0, long lModificationBits1, long lModificationBits2, long lModificationBits3);
    *  \param lModificationBits0      content of r108
    *  \param lModificationBits1      content of r171
    *  \param lModificationBits2      content of r172
    *  \param lModificationBits3      content of r173
    *
    * use this function to set the extendet modifications in r108, r171, r172 and r173. It's necessary to call setModification before the init methods
    */
    void     setModification(long lModificationBits0, long lModificationBits1, long lModificationBits2, long lModificationBits3);

    //in the following methods, the conversion from or to Unicode is done automatic (so it's independent if the system is HMI-ADV or HMI-operate)

    long    GetS7ErrorText  (long lErrNo, QString& rszErrorText, QString& rszErrorDetails);

    /*! \fn GetTextParam(long lParamNumber);
    *  \param  lParamNumber          Number of the desired parameter
    *
    *  \retval the desired text or empty String
    *
    *  Used to get the parameter text for a parameter
    */
    QString GetTextParam    (long lParamNumber);

    /*! \fn GetTextArray(long lParamNumber, long lArrayIdx);
    *  \param  lParamNumber          Number of the desired parameter
    *  \param  lArrayIdx             Index of the array (starts at 0)
    *
    *  \retval the desired text or empty String
    *
    *  Used to get the parameter array text for a parameter. 
    */
    QString GetTextArray    (long lParamNumber, long lArrayIdx);

    /*! \fn GetTextBit(long lParamNumber, long lBitIdx);
    *  \param  lParamNumber          Number of the desired parameter
    *  \param  lBitIdx               bit number  (starts at 0)
    *  \param  lArrayIdx             Index of the array (starts at 0)
    *
    *  \retval the desired text or empty String
    *
    *  Used to get the parameter bit text for a parameter.
    *  If the lArrayIdx is -1, the function returns with the parameter set bit text.
    *  If the lArrayIdx isn't -1 the function retuns with the bit text from the given parameter array item.
    *  If the given array item doesn't have the given bit text, the fuction retuns with the default bit text from the parameter.
    */
    QString GetTextBit      (long lParamNumber, long lBitIdx, long lArrayIdx = -1);

    /*! \fn GetTextBitArray(long lParamNumber, QVector<SlMdTextValue>& rBitArray);
    *  \param  lParamNumber          Number of the desired parameter
    *  \param  rBitArray             returns Array of SlMdTextValue
    *  \param  lArrayIdx             Index of the array (starts at 0)
    *
    *  \retval the size of the returned array
    *
    *  Used to get all the parameter bit text for a parameter.
    *  If the lArrayIdx is -1, the function returns with the parameter set bit texts.
    *  If the lArrayIdx isn't -1 the function retuns with all bit text from the given parameter array item.
    *  If the given array item doesn't have all bit texts, the fuction feels the not setted texts with the default bit texts from the parameter.
    */
    long    GetTextBitArray (long lParamNumber, QVector<SlMdTextValue>& rBitArray, long lArrayIdx = -1);

    /*! \fn GetTextEnum(long lParamNumber, long lEnumValue);
    *  \param  lParamNumber          Number of the desired parameter
    *  \param  lEnumValue            Value of the enum
    *
    *  \retval the desired text or empty String
    *
    *  Used to get the parameter enum text for a parameter.
    */
    QString GetTextEnum     (long lParamNumber, long lEnumValue);

    /*! \fn GetTextEnumArray(long lParamNumber, QVector<SlMdTextValue>& rEnumArray);
    *  \param  lParamNumber          Number of the desired parameter
    *  \param  rEnumArray            returns Array of SlMdTextValue
    *
    *  \retval the size of the returned array
    *
    *  Used to get all the parameter enum text for a parameter. 
    */
    long    GetTextEnumArray(long lParamNumber, QVector<SlMdTextValue>& rEnumArray);


    /*! \fn GetTextUnit(long lParamNumber);
    *  \param  lParamNumber          Number of the desired parameter
    *
    *  \retval the desired parameter unit text
    *
    *  Used to get the unit text of a parameter.
    */
    QString GetTextUnit     (long lParamNumber);

    /*! \fn GetTextUnit(long lParamNumber);
    *  \param  lParamNumber          Number of the desired parameter    
    *  \retval the desired parameter unit nr for reading from slmdlist.ts or in HMI-advanced from sllist.rc
    *
    *  Used to get only the unit key to read from textfiles direct
    */
    long GetUnitNr(long lParamNumber);

    /*! \fn GetAcxUnitID(long lParamNumber);
    *  \param  lParamNumber          Number of the desired parameter    
    *  \retval .ACX unit number or 0 if not found.
    *
    *  Used to get the ACX unti ID.
    */
    long GetAcxUnitID(long lParamNumber);

    /*! This function searches for the pattern rPattern in the text items of the machinedata/drive parameter
        defined by lParamNumber/lArrayIndex. Only the text types specified by nTextsToSearch are searched.
        The returned value is None, if the given pattern rPattern was not found in the text items
        specified by nTextsToSearch.
        If the pattern rPattern has been found in a text item specified by nTextsToSearch, then the type
        of this text item will be returned. If the pattern rPattern could be found in more than one text
        item, only the text type of the first found match will be returned.
        The bTextSetForParam flag returns with "false" if the SlMdText didn't contains text entrys about the given parameter. 
    */
    SlMdText::TextTypeEnum FindPattern(long lParamNumber, long lArrayIndex, SlMdText::TextTypes nTextsToSearch, const SlMdSearchPattern& rPattern, bool& bTextSetForParam);// const;


    /*! This function is used to detect the identical text items of two different array elements of the
        same machinedata/driveparameter. The incoming parameter lParamNumber is the identifier of the
        machinedata or drive parameter; lArrayIndex1 and lArrayIndex2 are the array indexes of  
        that machinedata or drive parameter.
        If the two array elements have no identical text elements, then the return value is None.
        Otherwise the return value will contain the type of the text elements, which are identical.
        For example if the input parameters are lParamNumber=drive parameter r37, lArrayIndex1=0
        and lArrayIndex2=1, then the return value will be SymbolText.
        Another example: lParamNumber=control unit p680, lArrayIndex1=1 and lArrayIndex2=2, then
        the return value will be SymbolText|EnumTexts.
    */
    SlMdText::TextTypes getIdenticalTexts(long lParamNumber,
                                          long lArrayIndex1, long lArrayIndex2) const;


public:
    //don't use the following methods, they are only used for compatibility
    //function's from sllist_txtinterpret (depends also on init(...)- methods only for internal use, please use the upper methods instead
    // if you are using this class within HMI-SL, you have to convert the char* to unicod; use QString::fromUtf8(char*)
    
    long                    init         (const char* szTextFile, const char* szDrvPdFile, long lModification = 0);
    sllistParamTextType*    GetElem(long idx);
    const QString&          GetElemText  (long lMdNr, long lArrIdx, long lBitIdx, long lEnumVal, sllistParamTextType* pSingleElem = 0);
    sllistParamTextType*    GetParamTxtElem (long lParaNr); //the returned pointer to the element must be deleted by the caller after calling DeleteParamTxtElem!
    const sllistParamTextType*    GetParamTxtElemConst (long lParaNr) const;
    void                    DeleteParamTxtElem   (sllistParamTextType* pElem);
    long                    SearchText   (const char* pSearchStr, long lParaNrStart, long& rlArrIdxFound);


    long                    GetBitArray  (long lParaNr, const sllistBitEnumValueType*& rpBitArray, sllistParamTextType* pSingleElem = 0, long lArrayIdx = -1);
    long                    GetEnumArray (long lParaNr, const sllistBitEnumValueType*& rpEnumArray, sllistParamTextType* pSingleElem = 0);
    
    long                    GetMdUnitText(int aiUnit, int iScalingSystem, SLLIST_BASICLEN_ENUM aiBasicLength, SLLIST_AXTYPE_ENUM aiAxisType, int bufferSize, char* aszText, long* rlUnitNr=0); //const;    
    long                    GetText      (long lTextId, long lBuffsize, char* pText, int iTextTyp = -1);
    QString                 getSymbolTextFromACX(long lMDNumber);

protected:
    //No public construction; use SlMdText::createObject(const char*) instead
    SlMdText(const char* szCallerName);
    virtual ~SlMdText();    
private:
    SlMdTextPriv*       m_pData; //private data
    SlMdTextPrivElement m_textPrivElement;
    bool                m_bHasNewTextPrivElement;
};

class SlMdTextValue
{
public:
    long        m_Value;        // enum value or BitIdxFrom
    long        m_IdxTo;        // BitIdxTo (only set for nibble)
    QString     m_szText;       // according text
};

#ifdef _DEBUG
    Q_DECLARE_OPERATORS_FOR_FLAGS(SlMdText::TextTypes)
#endif

#endif // !defined(AFX_SLMDTEXT_H__9F4E997A_964E_4D69_A780_E97ED681E9EC__INCLUDED_)
