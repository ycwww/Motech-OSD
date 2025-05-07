///////////////////////////////////////////////////////////////////////////////
/*! \file   SlDgLogicIdentityXmlFile.h
 *  \author Susan Schramm
 *  \date   27.03.2007
 *  \brief  Header file for class SlDgLogicIdentityXmlFile
 *
 *  This file is part of the HMI Solutionline dialog sldg (diagnosis).
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef SLDGLOGICIDENTITYXMLFILE_H_INCLUDED
#define SLDGLOGICIDENTITYXMLFILE_H_INCLUDED

#include <QtXml/qxml.h>
#include <QtCore/QFile>
#include <QtCore/QVector>
#include "slhmixmlwriter.h"

#if !defined(SL_LOGICIDENTITY_EXPORT)	
#   if defined(WIN32) || defined(WIN64)	
#	    ifdef SLLOGICVERSIONS_EXPORT	
#		    define SL_LOGICIDENTITY_EXPORT  __declspec(dllexport)
#	    else		
#		    define SL_LOGICIDENTITY_EXPORT  __declspec(dllimport)
#	    endif
#   else			// Linux / MAC: no Export Makro
#	    define SL_LOGICIDENTITY_EXPORT	
#   endif
#endif

class SL_LOGICIDENTITY_EXPORT SlDgLogicIdentityXmlFile: public QXmlDefaultHandler
{
public:
  static const int NUM_OF_ADDRESS_TAGS = 12;
  enum e_address_type
  {
    USER = 0,
    DEALER,
    OEMSUBS,
    OEM
  };

  SlDgLogicIdentityXmlFile();
	~SlDgLogicIdentityXmlFile();

  bool startDocument();
  bool startElement(const QString&, const QString&, const QString& , 
                    const QXmlAttributes&);
  bool endElement(const QString&, const QString&, const QString&);
	bool characters(const QString & ch);

	QString errorString();
	bool error(const QXmlParseException & exception);
	bool fatalError(const QXmlParseException & exception);
	bool warning(const QXmlParseException & exception);

  bool parseFile          (QString sFile);
  bool AddressItem        (const QString& sItem);

  bool getAddress         (const int iAddressType, const int iAddressNo, QVector<QString> &pAddress);
  bool getNamesList       (const int iAddressType, QStringList &szNames);
  bool appendAddressToList(QList <QVector<QString> > *pList);
  bool isAddressListEmpty (const QVector<QString> rAddress);
  int  getAddressListSize (const int iAddressType);
  void clearAddressLists   (void);
  void clearOemAddressList (void);
  void clearOemSubsAddressList (void);
  void clearDealerAddressList (void);
  void clearUserAddressList (void);
  void clearMaTypesList (void);

  int  getMaTypesListSize ();
  bool getMaTypesList     (QStringList &szNames);
 
  void writeIdentity      (const QString sFile, const QString m_szActMaType,
                           const QVector<QString> m_ActOemAddress, const QVector<QString> m_ActOemSubsAddress,
                           const QVector<QString> m_ActDealerAddress, const QVector<QString> m_ActUserAddress);
  void writeAddress       (SlXmlWriter& xmlWriter, const QString sTag, const QVector<QString> Address);
  unsigned int readNckType(const bool bQCap);
  QString readSerialNo(const bool bQCap);
  QString readMaName();
  /*! \fn  bool writeIdentityConfigSection (SlXmlWriter& xmlWriter);
  *  \param xmlWriter		     SlXmlWriter Object
  *  \retval bool            returns true if successful, otherwise false
  *
  *  writes the section with the machine identity into config.xml
  */
  bool writeIdentityConfigSection (SlXmlWriter& xmlWriter);

private:
  enum e_file_type
  {
    NONE = 0,              
    ADDRESS,      
    MA_TYPE             
  };

	QString		  		  m_szCurrentTagName;
  QXmlAttributes    m_Attr;
	int 		  	    	m_iFileType;
  QVector<QString>  m_CurrentParsedAddress;

  QList <QVector<QString> > m_pUserList;
  QList <QVector<QString> > m_pDealerList;
  QList <QVector<QString> > m_pOemSubsList;
  QList <QVector<QString> > m_pOemList;
  QStringList       m_szMaTypes;

};



#endif //SLDGLOGICIDENTITYXMLFILE_H_INCLUDED
