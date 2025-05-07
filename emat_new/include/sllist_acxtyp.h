/*
    acxtyp verwendet von AcxInterpreter zur Ermittlung der LinkItems
    und in sllist.dll
*/


#if !defined(SLLIST_ACXTYP_H__AC6D5AB6_8D14_42A3_A53A_3506D0734AFC__INCLUDED_)
#define SLLIST_ACXTYP_H__AC6D5AB6_8D14_42A3_A53A_3506D0734AFC__INCLUDED_

/* ACX- Handler */
typedef enum
{
    /* Achtung: bestehende Nummern nicht ändern, ansonsten inkompatibel zu Advanced!!! */
    SLLIST_ENUM_INVALID  = -1,  /*!< invalid value */
    /*NC-Objekte */
    SLLIST_TEA           = 1,   /*!< Maschinendaten   (NC,CH,AX,611x-Antriebe,BT)*/
    SLLIST_SEA           = 2,   /*!< Settingdaten                 */
    SLLIST_FUN           = 3,   /*!< vordefinierte Funktionen     */
    SLLIST_GUD           = 4,   /*!< Globale Anwenderdaten        */
    SLLIST_ACM           = 5,   /*!< Bewegungssynchronaktionen Marker*/
    SLLIST_ACP           = 6,   /*!< Bewegungssynchronaktionen Parameter*/
    SLLIST_CEC           = 7,   /*!< Durchhangfehlerkompensation  */
    SLLIST_EEC           = 8,   /*!< Geberfehlerkompensation      */
    SLLIST_QEC           = 9,   /*!< Quadrantenfehlerkompensation */
    SLLIST_PRO           = 10,  /*!< Schutzbereiche               */
    SLLIST_RPA           = 11,  /*!< Rechenparameter              */
    SLLIST_SYD           = 12,  /*!< Systemdaten                  */
    SLLIST_TOA           = 13,  /*!< Werkzeugdaten                */
    SLLIST_TOC           = 14,  /*!< Werkzeugdaten                */
    SLLIST_TMA           = 15,  /*!< Werkzeugdaten                */
    SLLIST_UFR           = 16,  /*!< Werkzeugdaten                */
    SLLIST_NCN           = 17,  /*!< NC-Adressen                  */

    /*!< Sinamics Antriebs-Parameter  */
    SLLIST_DRV_CU        = 18,  /*!< CU-Parameter)                  */       
    SLLIST_DRV_CULINK    = 19,  /*!< CU-Link-Parameter)             */       
    SLLIST_DRV_DC        = 20,  /*!< Drive Control-Parameter (Servo)*/       
    SLLIST_DRV_LM        = 21,  /*!< Line Module Parameter   (ALM)  */       
    SLLIST_DRV_TB        = 22,  /*!< Terminal board  - Parameter */
    SLLIST_DRV_TM        = 23,  /*!< Terminal Module - Parameter */       
    
    SLLIST_VIEW          = 24,  /*!< Anwendersichten(Motorlisten und View- Datum auswaehlen) */
    SLLIST_USER_VIEW     = 25,  /*!< Anwendersichten(eigentliche Sicht) */

    /* PUD/LUD */
    SLLIST_PUD           = 26,  /*!< Programmglobale Anwenderdaten      */
    SLLIST_LUD           = 27,  /*!< Programmglokale Anwenderdaten      */
    
    /* Sinamics Drive Copy */
    SLLIST_DRIVE_CPY     = 28,  /*!< Sinamics Antriebsobjekte kopieren  */

    /* Bico Reference List */
    SLLIST_DRVBICO       = 29,  /*!< BicoParameter: Sinamics Bico Referenzen    */
    SLLIST_DRVBICO_TRACE = 30,  /*!< rein intern, darf nicht in Schnittstellen verwendet werden!! */
    
    /* Sinamics Einzeldatensatz kopieren */
    SLLIST_DRIVE_CPY_DDS = 31,  /*!< Einzeldatensatz kopieren, wird behandelt wie SLLIST_DRIVE_CPY */

    /* Sinamics 3rd generation  */
    SLLIST_DRV_S210      = 32, /*!< Sinamics S210 */
    /* immer letztes Element: */
    SLLIST_ENUM_LAST,
    SLLIST_ENUM_UNKNOWN = SLLIST_ENUM_LAST
}SLLIST_ENUM;

typedef enum
{
    SLACX_AREA_XY   = -1, /*!< egal, ignorieren   */
    SLACX_AREA_NC   = 0,  /*!< allgemein          */
    SLACX_AREA_BAG  = 1,  /*!< allgemein          */
    SLACX_AREA_CH   = 2,  /*!< kanalspezifisch    */
    SLACX_AREA_AX   = 3,  /*!< achsspezifisch     */
    SLACX_AREA_TO   = 4,  /*!< Werkzeug           */
    SLACX_AREA_DRV  = 5,  /*!< Antriebe           */    
    /* 6 bis 9 fuer NC reserviert */
    SLACX_AREA_BT     = 10, /*!< Anzeige MD       */    
    SLACX_AREA_BT_CH  = 11, /*!< Anzeige MD, kanalspez. */    
    SLACX_AREA_BT_GEN = 12, /*!< Anzeige MD, allgemein  */    
    
    /* immer letztes Element: */
    SLACX_AREA_LAST,
    SLACX_AREA_UNKNOWN = SLACX_AREA_LAST
}SLACX_AREA;

#endif
