/* ********************************************************************** */
/* Sourcefile:      slacx_cstruk.h                                        */
/*                                                                        */
/* Project:         SOLUTION LINE                                         */
/*                                                                        */
/* Department:      SIEMENS AG                                            */
/*                  A&D MC RD 38                                          */
/*                                                                        */
/* First author:    Lothar Herzog                                         */
/* Other authors:   <symbol> <symbol> ...                                     */
/* ********************************************************************** */
/* Copyright (C) Siemens AG 2000 - 2003                                   */
/* All Rights Reserved.  Confidential                                     */
/* ********************************************************************** */


/* Description */

/*! \file slacx_cstruk.h: Strukturen fuer das C- Interface .
*/
#if !defined(AFX_SLACX_CSTRUK_H__43285218_C638_4848_B11E_B848E03963F3__INCLUDED_)
#define AFX_SLACX_CSTRUK_H__43285218_C638_4848_B11E_B848E03963F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

/*
// Aufbau der Namen der Strukturen:
// SlacxStruct<###>Type
// in slacx_cifc.c wird daraus ein Interface gemacht mit Namen 
// SlacxIfc<###>Type
// und ein Function Pointer 
// typedef const SlacxStruct<###>Type  *( *fp<###>)(void*, int); 
// in den Makros wird mit <###> darauf zugegriffen
// Beispiel:
// Cec
// Struktur:       SlacxStructCecType
// Func. Pointer:  typedef const SlacxStructCecType  *( *fpCec)(void*, int); 
// Interface:      SlacxIfcCecType

//####################################################################################
//Datenstrukturen
*/


/*
enum SLDataClass
{
    SLDATACLASS_NONE           = 0, // nicht klassifiziert
    SLDATACLASS_SIEMENS        = 1, // Datenklasse Steuerungshersteller (SIEMENS)
    SLDATACLASS_MANUFACTURER   = 2, // Datenklasse Maschinenhersteller (Maschinen gleicher Baureihe)
    SLDATACLASS_INDIVIDUAL     = 3, // Datenklasse Maschinenhersteller (maschinenindividuell)
    SLDATACLASS_USER           = 4, // Datenklasse Endanwender
};
*/




typedef void SLACX_ARRAY;        /*!< eigentlich vom Typ slacx_array<TYPE*>  */

typedef struct
{
    long         m_valueType;   /*1 = Range,  2 = Bitmask */
    /*char*        m_minValue; */
    /*char*        m_maxValue; */
    long         m_bitMask;     /* gesetzt durch setMask und unset Mask */
    const char** m_defValArray; /*char* m_DefValArray[] */
}SlacxValidValuesType;

/*####################################################################################*/
/*! Struct: SlacxChangeInfoType  */
typedef struct
{
    unsigned short  m_area;         /* Bereich; 0=NCK;1=BAG;2=Kanal;3=Achs;4=WZK;5=VSA;6=HSA */
    unsigned short  m_column;       /* Spalte               */
    unsigned short  m_row;          /* Zeile                */
    unsigned short  m_block ;       /* Baustein             */
    const char*     pFingerprint;   /* 32 Byte ASCII String */
}SlacxStructChangeInfoType;

/*####################################################################################*/
/*! Struct: SlacxStructAccOrig  */
typedef struct
{   
    double         lowerLimit;   /*!< Untergrenze fuer die Dateneingabe, falls Grenzwertpruefung aktiv */
    double         upperLimit;   /*!< Obergrenze fuer die Dateneingabe, falls Grenzwertpruefungaktiv  */
    unsigned short number;       /*!< Spaltenindex fuer die Bildung der Variablenaddressse */
    unsigned short arrayLength_1;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned short arrayLength_2;/*!< maximale Byteanzahl fuer Daten vom Typ String */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
    unsigned char  unit;         /*!< Enum der moeglichen physikalischen Einheiten */
    unsigned char  refresh;      /*!< Wirksamkeit: Enum der moeglichen Kriterien fuer das Wirksamsetzen eines geaenderten Datums */
    unsigned char  limitCheck;   /*!< Enum der moeglichen Grenzwertueberpruefungen */
    unsigned char  displayType;  /*!< vis_type: Enum der moeglichen Anzeige-Typen */
    unsigned char  readAccess;   /*!< mindestens benoetigtes Zugriffsrecht fuer lesenden Zugriff auf ein Datum */
    unsigned char  writeAccess;  /*!< mindestens benoetigtes Zugriffsrecht fuer schreibenden Zugriff auf ein Datum */
    unsigned char  sichern;      /*!< nur fuer 611D-Daten relevant */
    char           symbol[32];     /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short displayFilter;/*!< groups:Filterinformation fuer die Anzeige     */
}SlacxStructAccOrigType;

/*####################################################################################*/
/*! Struct: SlacxStructAcmType  */
typedef struct
{
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short number;   /*!< Symbol ID */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
    unsigned short arrayLength_1;/*!< Anzahl der Array-Elemente bei Array-Daten */
    long           ownerfunction;/* ? */
}SlacxStructAcmType;

/*####################################################################################*/
/*! Struct: SlacxStructCecType  */
typedef struct 
{
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short number;   /*!< Symbol ID */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
    unsigned short arrayLength_1;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned short arrayLength_2;/*!< Anzahl der Array-Elemente bei Array-Daten */
    long           ownerfunction;/* ? */
}SlacxStructCecType;

/*####################################################################################*/
/*! Struct: SlacxStructFunType  */
typedef struct
{
    char           retVal[16];   /*!< Return Value  */
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    const char    *paramList;    /*!< Parameterliste  */
    unsigned char  execute   ;   /*!< min. accesslevel to execute G-Code */
    long           ownerfunction;/* ? */
}SlacxStructFunType;

/*####################################################################################*/
/*! Struct: SlacxStructGcdType  */
typedef struct
{    
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned char  gCodeGroup;   /*!< G groups  */
    unsigned char  index;        /*!< G element */
    unsigned char  execute   ;   /*!< min. accesslevel to execute G-Code */
    long           ownerfunction;/* ? */
}SlacxStructGcdType;

/*####################################################################################*/
/*! Struct: SlacxStructGudType  */
typedef struct
{
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short number;   /*!< Symbol ID */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
    unsigned char  readAccess;   /*!< mindestens benoetigtes Zugriffsrecht fuer lesenden Zugriff auf ein Datum */
    unsigned char  writeAccess;  /*!< mindestens benoetigtes Zugriffsrecht fuer schreibenden Zugriff auf ein Datum */
    unsigned short arrayLength_1;/*!< Anzahl der Array-Elemente 1. Dimension */
    unsigned short arrayLength_2;/*!< Anzahl der Array-Elemente 2. Dimension */
    unsigned short arrayLength_3;/*!< Anzahl der Array-Elemente 3. Dimension */
    unsigned short stringLength; /*!< maximale Byteanzahl fuer Daten vom Typ String */
    long           dataclass;    /*!< Datenklasse */ 
}SlacxStructGudType;

/*####################################################################################*/    
/*! Struct: SlacxStructKywType  */
typedef struct
{
    const char*    KeyWord;      /*!< KeyWord */
}SlacxStructKywType;


/*####################################################################################*/    
/*! Struct: SlacxStructNcnType  */
typedef struct
{
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned char  execute   ;   /*!< min. accesslevel to execute */
    long           ownerfunction;/* ? */
}SlacxStructNcnType;


/*####################################################################################*/
/*! Struct: SlacxStructNskMapType  */
typedef struct
{
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short number;   /*!< Symbol ID */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
}SlacxStructNskMapType;

/*####################################################################################*/
/*! Struct: SlacxStructProType  */
typedef struct
{
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short number;   /*!< Symbol ID */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
    unsigned short arrayLength_1;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned short arrayLength_2;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned char  execute   ;   /*!< min. accesslevel to execute  */
    long           ownerfunction;/* ? */
}SlacxStructProType;

/*####################################################################################*/
/*! Struct: SlacxStructRpaType  */
typedef struct
{
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short number;   /*!< Symbol ID */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
    unsigned short arrayLength_1;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned char  execute   ;   /*!< min. accesslevel to execute G-Code */
    long           ownerfunction;/* ? */
}SlacxStructRpaType;

/*####################################################################################*/
/*! Struct: SlacxStructSydType  */
typedef struct
{
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short number;   /*!< Symbol ID */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
    unsigned long  unit;         /*!< Enum der moeglichen physikalischen Einheiten */
    unsigned char  stopRe;       /*!< Preparation stop info  */
    unsigned short arrayLength_1;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned short arrayLength_2;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned char  execute   ;   /*!< min. accesslevel to Read/Write system data  */
    long           ownerfunction;/* ? */
}SlacxStructSydType;

/*####################################################################################*/
/*! Struct: SlacxStructTeaType  */
typedef struct
{   
    double         lowerLimit;   /*!< Untergrenze fuer die Dateneingabe, falls Grenzwertpruefung aktiv */
    double         upperLimit;   /*!< Obergrenze fuer die Dateneingabe, falls Grenzwertpruefungaktiv  */
    unsigned short number;   /*!< Spaltenindex fuer die Bildung der Variablenaddressse */
    unsigned short arrayLength_1;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned short arrayLength_2;/*!< maximale Byteanzahl fuer Daten vom Typ String */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
    unsigned long  unit;         /*!< Enum der moeglichen physikalischen Einheiten */
    unsigned char  refresh;      /*!< Wirksamkeit: Enum der moeglichen Kriterien fuer das Wirksamsetzen eines geaenderten Datums */
    unsigned char  limitCheck;   /*!< Enum der moeglichen Grenzwertueberpruefungen */
    unsigned char  displayType;  /*!< vis_type: Enum der moeglichen Anzeige-Typen */
    unsigned char  readAccess;   /*!< mindestens benoetigtes Zugriffsrecht fuer lesenden Zugriff auf ein Datum */
    char           writeAccess;  /*!< mindestens benoetigtes Zugriffsrecht fuer schreibenden Zugriff auf ein Datum; -1 => ReadOnly */
    const char    *symbol;       /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short displayFilter;/*!< groups:Filterinformation fuer die Anzeige     */
    unsigned short function;     /* ? */
    long           dataclass;    /*!< Datenklasse */ 
    long           uploadtype;   /* ? */
    long           memorytype;   /* ? */    
    long           attributes;   /*!< ZusatzAttribute: BIT0: ReadOnly */
    /*SLACX_ARRAY   *pValue;*/       /*!< zeigt auf slacx_array<const*> (Array von Zeigern auf Defaultwerten, so groß wie arrayLength_1) */
    SlacxValidValuesType *pValidValues; /*!< min-,max, Defaultvalues...*/
    long           ownerfunction;/*!< spezielle NC-Funktionen z.B. Safety Filter (aus Kompatibilitaetsgruenden ans Ende*/
}SlacxStructTeaType;

/*####################################################################################*/
/*! Struct: SlacxStructToaType  */
typedef struct
{
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short number;   /*!< Symbol ID */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
    unsigned short arrayLength_1;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned short arrayLength_2;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned char  execute   ;   /*!< min. accesslevel to Read/Write system data  */
    long           ownerfunction;/* ? */
}SlacxStructToaType;

/*####################################################################################*/
/*! Struct: SlacxStructUfrType  */
typedef struct
{
    const char    *symbol;         /*!< symbolischer Bezeichner der Variablen ( NULL-terminierter String ) */
    unsigned short number;   /*!< Symbol ID */
    unsigned char  dataType;     /*!< btss_type;Enum der moeglichen Datentypen */
    unsigned short arrayLength_1;/*!< Anzahl der Array-Elemente bei Array-Daten */
    unsigned char  execute   ;   /*!< min. accesslevel to Read/Write system data  */
    long           ownerfunction;/* ? */
}SlacxStructUfrType;

/*####################################################################################*/

/*! Struct: SlacxStructDrvPdInfoType  Acx- Informationen dür Sinamics-PD*/
typedef struct
{
    const char*     m_author;
    long            m_timestamp;
    const char*     m_comment;
    struct
    {
        unsigned short  doCategory;
        unsigned short  doClass;
        const char*     guid;
        unsigned char   major;
        unsigned char   minor;
        unsigned long   version;
    }m_doBasis;
    struct
    {
        const char*     guid;
        unsigned char   major;
        unsigned char   minor;
    }m_doView;
    unsigned short  size;
    struct
    {
        unsigned long   usedConfig;
        unsigned long   startUp;
        void*           exclusion;
        void*           preCondition;
    }m_configurationDef;
}SlacxStructDrvPdInfoType;

typedef struct
{
    /* limitCheck erstmal wie bei ACC */
    long                        limitcheck;  /* = 0, keine Grenzwertueberpruefung       */
                                             /* = 1, Pruefung gegen Ober und Untergrenze*/
                                             /* = 2, Pruefung nur gegen Obergrenze      */
                                             /* = 3, Pruefung nur gegen Untergrenze     */
    double  dMinVal;
    double  dMaxVal;
    double  dDefVal;
}SlacxStructDrvPdRangeType;

typedef struct
{    
    unsigned long  ul_used_bit;
    unsigned long  ul_const_bit;
    long*          lDefVal;
}SlacxStructDrvPdBitmaskType;


/*! Struct: SlacxStructDrvPdDynArrType  : dynamische Array */
typedef struct
{
    unsigned short iParNr;  /* Parameternummer      */
    unsigned short iParVal; /* Wert des Parameters  */
}SlacxStructDrvPdDynArrType;

typedef struct
{    
    SLACX_ARRAY*                 pEnumArr;
    SlacxStructDrvPdRangeType*   pRange;
    SLACX_ARRAY*                 pDefaultValueArr;
    SlacxStructDrvPdBitmaskType* pBitMask;
}SlacxStructDrvPdValidValuesType;

/*! Struct: SlacxStructDrvPdFunctionModulType  : function module bits in r108, r171, r172 and r173*/
typedef struct
{
    long                    m_lModification0;  //Modifikation für Sinamics Antriebe (r108)
    long                    m_lModification1; //Modifikation1 für Sinamics Antriebe (r171)
    long                    m_lModification2; //Modifikation2 für Sinamics Antriebe (r172)
    long                    m_lModification3; //Modifikation3 für Sinamics Antriebe (r173)
}SlacxStructDrvPdFunctionModulType;

/*! Struct: SlacxStructDrvPdType  : eigentliche Parameter */
typedef struct
{
    unsigned long           existsInConfig;   /* depends on r108*/
    const char             *symbol;
    unsigned long           attributes1;
    unsigned long           attributes2;
    unsigned long           attributes3;
    unsigned long           attributes4;
    unsigned long           internalAttributes;
    unsigned long           displayGroup1;
    unsigned short          dataType;
    unsigned short          displayType;
    unsigned short          driveAccessLevel;

    unsigned short          number;
    unsigned short          arrayLength;
    unsigned short          dynArray;
    unsigned short          unit;
    long                    dataclass;    /*!< Datenklasse */ 
    SlacxStructDrvPdValidValuesType validValues;
    SLACX_ARRAY*            pModificationArray;
    long                    m_OaApplIndex;
    const char*             m_pOAApplSymbol; /*!0 wenn kein OA-Parameter ansonsten OA Name  */ 
    //extendet Modifications (belongs to existsInConfig above):
    unsigned long           existsInConfig1;  /* depends on r171*/
    unsigned long           existsInConfig2;  /* depends on r172*/
    unsigned long           existsInConfig3;  /* depends on r173*/
}SlacxStructDrvPdType;

/*####################################################################################*/

/*! Struct: SlacxStructDpcMasterType  */
typedef struct
{
    double          m_VersionHost;
    double          m_VersionDpm;
    double          m_VersionDpr;
    double          m_VersionDprEx;
    unsigned short  m_Row;
    unsigned short  m_ArrayLength;
    unsigned short* m_pBusNrArray;  /* m_pBusNrArray[] */
}SlacxStructDpcMasterType;
/*####################################################################################*/

/*! Struct: SlacxStructDpcSlotType  */
typedef struct
{
    unsigned short              m_Nr;
    unsigned int                m_ClientNr;
    unsigned short              m_IoType;
    unsigned int                m_Length;
    unsigned short              m_LogBaseAddress;
    unsigned short              m_Row;
    /*MachAxisNr*/
    unsigned short              m_Axis;
    unsigned short              m_Encoder1;
    unsigned short              m_Encoder2;
    unsigned short              m_filler;
}SlacxStructDpcSlotType;
/*####################################################################################*/

/*! Struct: SlacxStructDpcPNNrType  */
typedef struct
{
    long                        m_SlotNr;
    SLACX_ARRAY*                m_pSlotArray;  /* eigentlich: Slacx_Array <SlacxStructDpcSlotType*>* m_pSlotArray  */  
}SlacxStructDpcPNNrType;
/*####################################################################################*/

/*! Struct: SlacxStructDpcSlaveType  */
typedef struct
{
    unsigned short              m_BusAddr;
    unsigned short              m_IdentNo;
    struct{
        unsigned long           m_ArrayLength;
        unsigned short*         m_pIpAddrByte;  //eigentlich Array von unsigned short mit Länge m_ArrayLength
    } m_IPAddr;
    const char*                 m_pDeviceName; 
    unsigned short              m_IdentNoEx;
    unsigned short              m_IsochroneModeSupport;
    double                      m_DataExchangeTime;
    double                      m_InputTime;
    double                      m_MasterAppCycTime;
    double                      m_OutputTime;
    double                      m_ProfibusCycleTime;
    unsigned short              m_Row;
    unsigned short              m_Filler /* wg. Alignment */;
    SLACX_ARRAY*                m_pSlotArray;  /* eigentlich: Slacx_Array <SlacxStructDpcSlotType*>* m_pSlotArray  */  
    SLACX_ARRAY*                m_pPNNrArray;  /* eigentlich: Slacx_Array <SlacxStructDpcPNNrType*>* m_pPNNrArray  */
}SlacxStructDpcSlaveType;
/*####################################################################################*/

/*! Struct: SlacxStructDpcBusType  */
typedef struct
{
    unsigned short              m_Nr;
    double                      m_Baudrate;
    double                      m_CycleTime;
    double                      m_DataExTime;
    unsigned short              m_Row;    
    SLACX_ARRAY*                m_pSlaveArray;    /*eigentlich: Slacx_Array <SlacxStructDpcSlaveType*>* m_pSlaveArray; */
    const char*                 m_pSubnetId ;
    unsigned short              m_DpMasterSystemId;
}SlacxStructDpcBusType;
/*####################################################################################*/
/* DPC- Objekt */
/*####################################################################################*/
/*! Struct: SlacxStructDpcClientType  */
typedef struct
{
    unsigned short              m_Nr;
    unsigned short              m_Id;
    unsigned short              m_Row;
    unsigned short              m_Filler /* wg. Alignment */;
}SlacxStructDpcClientType;
/*####################################################################################*/

/*! Struct: SlacxStructDpcAxisType  */
typedef struct
{
    unsigned short              m_MachAxisNr;       
    unsigned short              m_Row;
}SlacxStructDpcAxisType;
/*####################################################################################*/


/*####################################################################################*/

/*! Struct: SlacxStructDpcType  : eigentliche Parameter */
typedef struct
{
    unsigned short  m_iAvailable;
    unsigned short  m_Filler /* wg. Alignment */;
    SLACX_ARRAY*    m_pMasterArray;
    SLACX_ARRAY*    m_pBusArray;    
    SLACX_ARRAY*    m_pClientArray;    
    SLACX_ARRAY*    m_pAxisArray;  
} SlacxStructDpcType; 
/*####################################################################################*/

/*####################################################################################*/
/* DOT- Objekt */
/*####################################################################################*/

/*! Struct: SlacxStructDotType  */
typedef struct
{
    unsigned short m_BaseType;
    unsigned short m_TypeId;
    const char*    m_Name;
    const char*    m_AcxName;
} SlacxStructDotType;

/*####################################################################################*/

/*####################################################################################*/
/* DOC- Objekt */
/*####################################################################################*/

/*! Struct: SlacxStructDoType  */
typedef struct
{
    unsigned short  m_Block;
    unsigned short  m_Id;
    unsigned short  m_TypeID;
    const char*     m_Name;
    unsigned char   m_Area;
    unsigned short  m_Unit;
    unsigned short  m_ArrayLength;   /* gibt Laenge des m_pSlotNrArray an */
    unsigned short* m_pSlotNrArray;  /* m_pSlotNrArray[] */
    long            m_PNNr;          /* PNNr Nummer ; -1 = nicht vorhanden */
    long            reserved[4];     /* for future use                     */
}SlacxStructDoType;

/*! Struct: SlacxStructCuType  */
typedef struct
{
    unsigned short    m_BusAddr;
    SlacxStructDoType m_DoType;
    unsigned short    m_BusAddrOfCuLinkMaster;
    SLACX_ARRAY*      m_pDoArray;  /*eigentlich: Slacx_Array <SlacxStructDoType*>* m_pDoArray; */
}SlacxStructCuType;

/*! Struct: SlacxStructDocType  */
typedef struct
{
    unsigned short  m_Nr;
    SLACX_ARRAY*    m_pCuArray;  /*eigentlich: Slacx_Array <SlacxStructCuType*>* m_pCuArray; */
}SlacxStructDocType;
/*####################################################################################*/

/*####################################################################################*/
/* SDC- Objekt */
/*####################################################################################*/

/*! Struct: SlacxStructSdcType  */
typedef struct
{
    unsigned long m_NcNumber;      /*!< Symbol ID NC   */
    unsigned long m_ServoNumber;   /*!< Symbol ID SERVO*/
}SlacxStructSdcType;


/*####################################################################################*/
/* Motor-, Geberlisten,- Objekt */
/*####################################################################################*/

/*! Struct: SlacxStructDrvLstElemType  */
/*! einzelnes Element */

typedef struct
{
    const char*     m_Name;            /*!< Symbol ID NC   */
    const char*     m_Value;           /*!< Wert als String */
    long            m_Unit;            /*!< phys. Einheit (Acx_Unit)   oder -1 falls nicht vorhanden */
    long            m_Number;          /*!< zugehörige Parameternummer oder -1 falls nicht vorhanden */
}SlacxStructDrvLstElemType;


/*####################################################################################*/
/* Parameter Sicherungsdatei - Objekt (PS*.ACX)*/
/*####################################################################################*/

/*! Struct: SlacxStructDrvPsParameterType  */
/*! einzelnes Parameter Element */


typedef struct
{
    unsigned short          m_number;
    unsigned short          m_dataType;
    unsigned short          m_arrayLength;
    const char**            m_pValueArray;   /* so groß wie arrayLength  char* pValueArray[]*/
}SlacxStructDrvPsParameterType;

/*! Struct: SlacxDrvPsCompareType  */
/*! einzelnes PS- Compare Element */
typedef struct
{
    long        m_number;
    long        m_lArrayIdx;
    const char* pLeftVal;
    const char* pRightVal;
}SlacxDrvPsCompareType;

typedef struct
{
    unsigned long           m_version;
    SLACX_ARRAY*            m_pDescStructureParamArray; /* eigentlich: Slacx_Array <SlacxStructDrvPsParameterType*>* m_pArray; */
    SLACX_ARRAY*            m_pParameterArray;          /* eigentlich: Slacx_Array <SlacxStructDrvPsParameterType*>* m_pArray; */
}SlacxStructDrvPsType;

/*####################################################################################*/
/* BICO Vorzugsverschaltung - Objekt (BI*.ACX)*/
/*####################################################################################*/

/*! Struct: SlacxStructDrvBicoRefListType  : Liste die zurückgegeb. wird ist von diesem Typ */
typedef struct 
{
    long m_number;
    long m_index;
    long m_dotype;
    long m_bit;
    long m_allindices;
    long m_allbits;
    long m_unit;
    
}SlacxStructDrvBicoRefListType;


/*! Struct: SlacxStructDrvBicoType  */
/*! einzelnes Bico Element */
typedef struct
{
    long        m_number;

}SlacxStructDrvBicoType;



/*####################################################################################*/

#endif /* !defined(AFX_SLACX_CSTRUK_H__43285218_C638_4848_B11E_B848E03963F3__INCLUDED_) */
