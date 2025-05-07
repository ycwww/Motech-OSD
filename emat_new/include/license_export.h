// Copyright (c) SIEMENS AG, A&D MC, 2001, 2006, 2009

// -------------------------------------------------------------------------
// Name:            license.h
// Paket:           hmilic
//
// Beschreibung:    class CLicence (adaped for HMI)
//
// -------------------------------------------------------------------------


// -------------------------------------------------------------------------
// History:
// Grund/Fehler | Datum    | Abtlg.       | Bearbeiter | Beschreibung
// -------------+----------+--------------+----------+----------------------
//              | 12.10.09 | A&D MC R&D61 | Mueller,R. | Erstellung
//
// -------------------------------------------------------------------------


#ifdef __cplusplus
extern "C" {
#endif


// Typdefinitionen
//
typedef     int     LZError;									// FehlerCode
	#define LZ_OK                       0x000					// LizenzError: OK
	#define LZ_WRONG_PARAMETER          0x001					// LizenzError: Falscher Parameter
	#define LZ_MAC_START                0x002
	#define LZ_MAC                      0x003
	#define LZ_KEY_INCORRECT            0x004					// LizenzError: LicenseKey ist falsch
	#define LZ_OPTION_ERROR             0x005					// Wert im Option-Array zu gross

    
// Programme
//
extern void		Lic_Init				(int ArraySize,			// Groesse des OptionArray
										 int IndexBits,			// Anzahl Bits fuer Index in Array
										 int IndexExtension,	// Index mit Extension
										 int ValueBits,			// Benutzte Bits im Array
										 int ValueExtension,	// Value mit Extension
										 int ChecksumSize,		// Anzahl Stellen des ChecksumKey
										 int BlockSize,			// LicenseKey wird in Bloecken a angegebene Stellen aufgeteilt
										 int CryptoType);		// CBC-Mac oder MD 5

extern void		Lic_Free				();						// Destruktor

																// Ueberpruefe ob LicenseKey gueltig ist
extern int		Lic_CheckLicenseKey		(char*  LicenseKey,		// Platz fuer den LicenseKey
										 char*  UnikatsNr,		// Hardware-Unikatsnummer
										 int    KryptoIndex);	// Kryptoindex

extern int		Lic_ExpandLicenseKey	(char*  LicenseKey);	// Expand license key to Optionarray

extern long		Lic_GetOptionIndex		(int Index);			// Get one Option Index

extern int		Lic_GenTempLicKey		(char* pOutKey, 		// pointer to out-String, buffer should be >= 16
										 char* pTempSNr, 		// pointer to NCK TLK-Serial-Number
										 int Which);			// TLK-Funktion (0-9)

#ifdef __cplusplus
}
#endif


// Copyright (c) SIEMENS AG, A&D MC, 2001, 2006, 2009
