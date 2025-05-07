#ifndef SL_LIC_MAIN_H_INCLUDED
#define SL_LIC_MAIN_H_INCLUDED

#include <QtCore/QObject>
#include "slhmisettingsqt.h"
#include "slhmimakros.h"
#include "slhmixmlwriter.h"

#include "slsulogiclicoptionreadfiles.h"

#if !defined(SL_LOGICLICMAIN_EXPORT)	
#   if defined(WIN32) || defined(WIN64)	
#	    ifdef SLLOGICLICMAIN_EXPORT	
#		    define SL_LOGICLICMAIN_EXPORT  __declspec(dllexport)
#	    else		
#		    define SL_LOGICLICMAIN_EXPORT  __declspec(dllimport)
#	    endif
#   else			// Linux / MAC: no Export Makro
#	    define SL_LOGICLICMAIN_EXPORT	
#   endif
#endif



class SL_LOGICLICMAIN_EXPORT SlSuLogicLicMain : public QObject
{
    Q_OBJECT
    Q_ENUMS(SlCapErrorEnum);

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn instance(void)
     *
     *  This method returns the single instance of SlGfwDataPool.
     *  If this instance doesn't exists, it will be created.
    */
    static SlSuLogicLicMain* instance(void);

    /*! \fn destroyInstance(void)
     *
     *  This method destroys the single instance of SlGfwDataPool.
    */
    static void destroyInstance(void);

public:
    bool refreshLicenseInformation(bool bNCUChange = false);    
    bool writeLicencseConfigSection(SlXmlWriter& xmlWriter);
    bool importLicenseKey(QString& szPath, QString* szLicenseKey);
	//-- ss 2019-04-16: for ONE: License Key is not longer in .ALM, but in zip, which contains .alm and .sig
	bool importLicenseZipFile(QString& szPath);
	bool uncompressZipFile(QString& szPath, QString& szTempDir);
    bool importLockSetFile(QString& szPath);
    bool exportMissingLicenses(QString& szPath);
    bool refreshMissingOptionDataList(void);
    bool refreshPlusLicensesDataList(void);
    //returns a machine data value indexed by a machine data name 
    int actualLicMDValueByName(const QString & licMDName);
    bool writeOptionToNC(const int row, QList<SlSuLogicLicOptionData*>	*p_List);
    //actual licensed options (NCK values)
    QVariantList* getLicensedOptionsNCK(void);

    QList<SlSuLogicLicOptionData*>* getLicOptionDataList(void);
    QList<SlSuLogicLicOptionData*>* getLicMissingOptionDataList(void);
    QList<SlSuLogicLicOptionData*>* getLicPlusLicensesDataList(void);
    QList<SlSuLogicLicOptionData*>* getLicMissingPlusDataList(void);
    int getSysOptionsId(const int iValue);

    static QString getNCType(const bool bQCap);
    static QString getLicenseKey(void);
    static QString getSerialNo(void);
    static QString getMachineName(void);
    static unsigned int readNCVar(const QString& sNCVar, QVariant& vData);
    static int getRemainingLicTrialPeriods(void);


private:
    static SlSuLogicLicMain*        m_pInstance;

    SlSuLogicLicOptionReadFiles*    m_pLicOptionData;

    QString                         m_szSerialNo;
    QString                         m_szMachineName;
    QString                         m_szNCType;
    QString                         m_szLicenseKey;

    bool                            m_bLicenseSyfLoaded;
	SlSuLogicLicMain(void);

	virtual ~SlSuLogicLicMain(void);
};

#endif // SL_LIC_MAIN_H_INCLUDED


