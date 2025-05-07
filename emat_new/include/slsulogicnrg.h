///////////////////////////////////////////////////////////////////////////////
/*! \file   slsulogicnrg.h
 *  \author Susan Schramm
 *  \date   11.08.2010
 *  \brief  Header file for class SlDgLogicNrg
 *
 *  This file is part of HMI Solutionline
 *
 *  (C) Copyright Siemens AG A&D MC 2010. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLSULOGICNRG_H_INCLUDED
#define SLSULOGICNRG_H_INCLUDED
#include <QtXml/qxml.h>
#include "slhmixmlwriter.h"
#include "sltxtadapter.h"

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

const static int C_MAX_STATES = 8;
//- Max. Value must be converted to Minutes, therefore 65520 instead of 65535
static const int S_MAX_SEC_TIMER = 65520;

class NrgXMLData
{
public:
  NrgXMLData(){init();};
  void init(void){m_iKeyOP=0;m_iDataTrans=0;m_iWindowChange=0;m_iKeyMCP=0;m_iChannelState=0;m_iMaster=0;m_iPLC=0;
                  m_iTime=0;m_iWarnTime=0;m_bState=false;m_bDisable=false;};
  QString m_Txt;		
  bool	m_bState;
  bool	m_bDisable;
  int   m_iKeyOP;
  int   m_iDataTrans;
  int   m_iWindowChange;
  int   m_iKeyMCP;
  int   m_iChannelState;
  int   m_iMaster;
  int   m_iPLC;
  int   m_iTime;
  int   m_iWarnTime;

};


/*!
*  \class  SlSuLogicNrg
*  \brief  Implementation class for Handling XML-files for Ctrl-E
*/
class SL_LOGICLICMAIN_EXPORT SlSuLogicNrg : public QXmlDefaultHandler
{

public:

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn instance(void)
   *
   *  This method returns the single instance of SlSuLogicNrg.
   *  If this instance doesn't exists, it will be created.
  */
  static SlSuLogicNrg* instance(void);

  /*! \fn destroyInstance(void)
   *
   *  This method destroys the single instance of SlSuLogicNrg.
  */
  static void destroyInstance(void);

  
  SlSuLogicNrg(void);
  virtual ~SlSuLogicNrg(void);


public:
  virtual bool startDocument();
  virtual bool startElement(const QString&, const QString&, const QString&, const QXmlAttributes&);
  virtual bool endElement(const QString&, const QString&, const QString&);
  virtual bool characters(const QString & ch);
  virtual QString errorString();
  virtual bool error(const QXmlParseException & exception);
  virtual bool fatalError(const QXmlParseException & exception);
  virtual bool warning(const QXmlParseException & exception);

  bool parseFile(const QString& sInputSource);

  bool isStateValid(const int iStateNo);
  int getKeyOP(const int iStateNo);
  int getDataTrans(const int iStateNo);
  int getWindowChange(const int iStateNo);
  int getKeyMCP(const int iStateNo);
  int getChannelState(const int iStateNo);
  int getMaster(const int iStateNo);
  int getPLC(const int iStateNo);
  int getTime(const int iStateNo);
  int getWarnTime(const int iStateNo);
  QList<int>* getStateList(void);

  long saveData(const int iStateNo, QString sText, NrgXMLData NewData, bool bNew);
  long deleteState(const int iStateNo);
  long writeDefinitionsTS(const QString sFile);
  long convertDefinitionsTS(const QString sFile, SlTxtAdapter* pTxtAdapter);
  long writeDefinitionsXML(const QString sFile);
  long readProfilesFromPLC();
  long writeProfileToPLC(int iStateNo, bool bDelete = false);


private:
  ///////////////////////////////////////////////////////////////////////////
  // private members
  ///////////////////////////////////////////////////////////////////////////
  static SlSuLogicNrg*  m_pInstance;
  bool        m_bDef;
  bool        m_bCond;
  bool        m_bEmpty;
  int         m_iId;
  NrgXMLData* pData;
  NrgXMLData	data[C_MAX_STATES];
  QString     m_szCurrentTagName;
  QList<int>  m_StateIDList;
  

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
 
};
#endif //SLSULOGICENERGY_H_INCLUDED


