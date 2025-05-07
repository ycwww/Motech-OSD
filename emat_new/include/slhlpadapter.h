///////////////////////////////////////////////////////////////////////////////
/*! \file   slhlpadapter.h
 *  \author Gerolf Kuehnel
 *  \date   10.11.2004
 *  \brief  Header file for class SlHlpAdapter
 *
 *  This file is part of the HMI Solutionline Help System
 *
 *  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HLP_ADAPTER_H)
#define SL_HLP_ADAPTER_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QSet>
#include <QtCore/QUrl>

#if !defined(LINUX)
  #pragma warning(disable : 4805)
#endif // LINUX

#include "slsfwserviceadapterptr.h"
#include "slhminamespace.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class SlHlpTreeModel;

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)
#   ifdef SL_HELP_EXPORT_ADAPTER
#        define SL_HLP_SVC_ADAPTER_EXPORT  __declspec(dllexport)
#   else
#        define SL_HLP_SVC_ADAPTER_EXPORT  __declspec(dllimport)
#   endif
#else
#   define SL_HLP_SVC_ADAPTER_EXPORT
#endif


//#############################################################################
//#############################################################################
/*!
 *  \class SlHlpResult slhlpadapter.h
 *  \brief one entry of the result list
 */
//#############################################################################
//#############################################################################
class SL_HLP_SVC_ADAPTER_EXPORT SlHlpResult
{
public:
  SlHlpResult();

  long    m_nReferenceId; /*!< reference to the entry */
  QString m_szTitle;      /*!< title of the entry */
  bool    m_bHasChildren; /*!< set to true, if the item has children */
  bool    m_bIsDocument;  /*!< set to true, if the item is a document, false if only entry */

  bool operator==(const SlHlpResult& rResult) const;
  bool operator!=(const SlHlpResult& rResult) const;
};


///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

/*! \class SlHlpResultList slhlpadapter.h
 *  \brief list of help result entries
*/
typedef QList<SlHlpResult> SlHlpResultList;
//template class SL_HLP_SVC_ADAPTER_EXPORT QList<SlHlpResult>;

class SlHlpAdapter;
/*! Smartpointer to the Serviceadapter. You should use this pointer instead of
 *  using the service class directly
 */
typedef SlSfwServiceAdapterPtr<SlHlpAdapter> SlHlpAdapterPtrType;
template class SL_HLP_SVC_ADAPTER_EXPORT SlSfwServiceAdapterPtr<SlHlpAdapter>;


//#############################################################################
//#############################################################################
/*!
 *  \class SlHlpAdapter slhlpadapter.h
 *  \brief gives access to the help service
 */
//#############################################################################
//#############################################################################
class SL_HLP_SVC_ADAPTER_EXPORT SlHlpAdapter :
    public QObject
{
  Q_OBJECT

public:
  /////////////////////////////////////////////////////////////////////////////
  // CREATORS (static)
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn static long getObject(SlHlpAdapter*& rpAdapter);
   *
   *  \param rpAdapter    a reference to the pointer to be filled witha an
   *                      instance of the resourceserviceadapter
   *
   *  \retval Errorcode, if an error occured, otherwise 0
   *
   *  This static function creates a Help Service Adapter.
   */
  static long getObject(SlHlpAdapter*& rpAdapter);

  /*! \fn static long releaseObject(SlHlpAdapter*& rpInstance);
   *
   *  \param  pInstance
   *
   *  \retval Errorcode, if an error occured, otherwise 0
   *
   *  This static function removes a SlHlpAdapter.
   */
  static long releaseObject(SlHlpAdapter*& rpInstance);

  /////////////////////////////////////////////////////////////////////////////
  // CONSTANTS (static)
  /////////////////////////////////////////////////////////////////////////////

  /*! reference ID of the global top chapter of the content */
  static const long S_M_GLOBAL_CHAPTER_REFERENCE;

public:

  /////////////////////////////////////////////////////////////////////////////
  // ENUMS
  /////////////////////////////////////////////////////////////////////////////

  /*! \enum SlHlpSearchTypeEnum
   *   type of search
   */
  enum SlHlpSearchTypeEnum
  {
    SL_HLP_FULLTEXT,    /*!< use the full text search engine */
    SL_HLP_XML          /*!< use the content and index search engine */
  };


  /////////////////////////////////////////////////////////////////////////////
  // CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  /////////////////////////////////////////////////////////////////////////////

  /*  \fn virtual long content(const long lChapterReference,
   *                           const SlHmi::SlTechnologyEnum eTechnology,
   *                           unsigned long& rnCallbackId)
   *
   *  \param  lChapterReference  Reference identifier of the Chapter
   *  \param  eTechnology        technology (universal, mitting, turning)
   *  \param  rnCallbackId       unique id that is used in the callback
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  All Subentries(chapters, pages) of the specified chapter(rszChapter) should be delivered.
   *  The asynchronous method returns all entries through SlIHelpServiceAdapterCallback::contentFinished
   *  with the id pCallbackId.
   */
  virtual long content(const long nChapterReference,
                       const SlHmi::SlTechnologyEnum eTechnology,
                       unsigned long& rnCallbackId) = 0;

  /*  \fn virtual long contentSync(const long lChapterReference,
   *                               const SlHmi::SlTechnologyEnum eTechnology = SlHmi::TechnologyAll,
   *                               SlHlpResultList& contentList)
   *
   *  \param  lChapterReference  Reference identifier of the Chapter
   *  \param  eTechnology        technology (universal, mitting, turning)
   *  \param  contentList        Sequence of content entry ids
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  All Subentries(chapters, pages) of the specified chapter(rszChapter) should be delivered.
   */
  virtual long contentSync(const long nChapterReference,
                           const SlHmi::SlTechnologyEnum eTechnology,
                           SlHlpResultList& contentList) = 0;

  /*  \fn virtual long index(const long lOffset,
   *                         const long lNumberOfEntries,
   *                         const long lIndexReference,
   *                         const SlHmi::SlTechnologyEnum eTechnology,
   *                         unsigned long& rnCallbackId)
   *
   *  \param  lOffset            Offset in the Index entries
   *  \param  lNumberOfEntries   numbers of entries to get
   *  \param  lIndexReference    Reference identifier of the parent index item
   *  \param  eTechnology        technology (universal, mitting, turning)
   *  \param  rnCallbackId       unique id that is used in the callback
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  The Index of the OnlineHelp is requested. The asynchronous method returns all results
   *  through SlIHelpServiceAdapterCallback::indexFinished with the id pCallbackId.
   */
  virtual long index(const long lOffset,
                     const long lNumberOfEntries,
                     const long lIndexReference,
                     const SlHmi::SlTechnologyEnum eTechnology,
                     unsigned long& rnCallbackId) = 0;

  /*  \fn virtual long indexSync(const long lOffset,
   *                             const long lIndexReference,
   *                             const SlHmi::SlTechnologyEnum eTechnology = SlHmi::TechnologyAll,
   *                             SlHlpResultList& indexList)
   *
   *  \param  lOffset            Offset in the Index entries
   *  \param  lIndexReference    Reference identifier of the parent index item
   *  \param  eTechnology        technology (universal, mitting, turning)
   *  \param  indexList          Sequence of index entry ids
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  The Index of the OnlineHelp is requested.
   */
  virtual long indexSync(const long nOffset,
                         const long nIndexReference,
                         const SlHmi::SlTechnologyEnum eTechnology,
                         SlHlpResultList& indexList) = 0;


  /*  \fn virtual long indexOf(const QString& rszStartCharacters,
   *                           const long lIndexReference,
   *                           SlHmi::SlTechnologyEnum eTechnology,
   *                           unsigned long& rnCallbackId)
   *
   *  \param  rszStartCharacters  start characters for the part of the index that is requested
   *  \param  lIndexReference     Reference identifier of the parent index item
   *  \param  eTechnology         technology (universal, mitting, turning)
   *  \param  rnCallbackId        unique id that is used in the callback
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  All indexentries with the specified rszStartCharacters should be delivered.
   *  The asynchronous method returns all entries through SlIHlpCallback::indexOfFinished
   *  with the id pCallbackId.
   */
  virtual long indexOf(const QString& rszStartCharacters,
                       const long nIndexReference,
                       SlHmi::SlTechnologyEnum eTechnology,
                       unsigned long& rnCallbackId) = 0;

  /*  \fn virtual long indexCount(const long nIndexReference,
   *                              const SlHmi::SlTechnologyEnum eTechnology,
   *                              unsigned long& rnCallbackId)
   *
   *  \param  nIndexReference     Reference identifier of the parent index item
   *  \param  rnCallbackId        unique id that is used in the callback
   *  \param  nTechnology         technology (universal, mitting, turning)
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  the number of index entries should be delivered. The asynchronous method
   *  returns all entries through SlIHlpCallback::indexCountFinished with the id pCallbackId.
   */
  virtual long indexCount(const long nIndexReference,
                          const SlHmi::SlTechnologyEnum eTechnology,
                          unsigned long& rnCallbackId) = 0;

  /*  \fn virtual long findText(const QString& rszTextToFind,
   *                            const SlHlpSearchTypeEnum eSearchType,
   *                            const SlHmi::SlTechnologyEnum eTechnology,
   *                            unsigned long& rnCallbackId)
   *
   *  \param  rszTextToFind   text to find
   *  \param  eSearchType     area to search
   *  \param  eTechnology     technology (universal, mitting, turning)
   *  \param  rnCallbackId    unique id that is used in the callback
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  The Onlinehelp is searched(not fulltext, only specified passages) for rszTextToFind. The
   *  asynchronous method returns all results through SlIHelpServiceAdapterCallback::findFinished
   *  with the id pCallbackId.
   */
  virtual long findText(const QString& rszTextToFind,
                        const SlHlpSearchTypeEnum nSearchType,
                        const SlHmi::SlTechnologyEnum eTechnology,
                        unsigned long& rnCallbackId) = 0;

  /*  \fn virtual long findUrl(const QString& rszHelpDocument, QUrl& rUrl);
   *
   *  \param  rszHelpDocument document incl. helppath to find
   *  \param  rUrl            will be filled with the page url
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  Returns the page URL for an entry in the index, search result or content.
   */
  virtual long findUrl(const QString& rszHelpDocument, QUrl& rUrl) = 0;

  /*  \fn virtual CORBA::Long findDocUrlOfBook(const QString szBookName,
   *                                           const long lNumber,
   *                                           const long lArrayIndex,
   *                                           unsigned long& rnCallbackId);
   *
   *  \param  szBookName      Name of the book
   *  \param  lNumber         Number (Anchor) to search in the book
   *  \param  lArrayIndex     Array-Index (Anchor) to search in the book
   *  \param  rnCallbackId    unique id that is used in the callback
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  Returns the page URL for an entry in the index, search result or content.
   */
  virtual long findDocUrlOfBook(const QString& rszBookName,
                                const long lNumber,
                                const long lArrayIndex,
                                unsigned long& rnCallbackId) = 0;

  virtual long findNextDocUrlOfBook(const QString& rszBookName,
                                    const QString& rszActDocument,
                                    unsigned long& rnCallbackId) = 0;

  virtual long findPrevDocUrlOfBook(const QString& rszBookName,
                                    const QString& rszActDocument,
                                    unsigned long& rnCallbackId) = 0;

  /*  \fn virtual long pageName(const long lPageReference,
   *                            QString& rszTitel);
   *
   *  \param  lPageReference  Id of the page, you want to get the title for
   *  \param  rszTitel        will be filled with the title const QString&
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  Returns the page title for an entry in the index, search result or content.
   */
  virtual long pageName(const long lPageReference, QString& rszTitel) = 0;

  /*  \fn virtual long pageUrl(const long lPageReference, QUrl& rUrl) = 0;
   *
   *  \param  nPageReference  Id of the page, you want to get the title for
   *  \param  rUrl            will be filled with the page url
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  Returns the page URL for an entry in the index, search result or content.
   */
  virtual long pageUrl(const long lPageReference, QUrl& rUrl) = 0;

  /*  \fn virtual long cancel(unsigned long nCallbackId) = 0;
   *
   *  \param  nCallbackId      id of the asynchronous call to cancel
   *
   *  \retval Errorcode, see \sa slhlperror.h
   *
   *  The asynchronous call with the Id nCallbackId will be canceled.
   */
  virtual long cancel(const unsigned long nCallbackId) = 0;

  /*  \fn virtual SlHlpTreeModel *contentModel(void) = 0;
   *  \retval Returns the Pointer to the Content data model
   *
   *  Returns the Pointer to the Content data model.
   */
  virtual SlHlpTreeModel *contentModel(void) = 0;

  /*  \fn virtual SlHlpTreeModel *indexModel(void) = 0;
   *  \retval Returns the Pointer to the Content data model
   *
   *  Returns the Pointer to the Index data model.
   */
  virtual SlHlpTreeModel *indexModel(void) = 0;

  /*  \fn virtual SlHlpTreeModel *searchResultModel(void) = 0;
   *  \retval Returns the Pointer to the Search Result data model
   *
   *  Returns the Pointer to the Search Result data model.
   */
  virtual SlHlpTreeModel *searchResultModel(void) = 0;

signals:
  /////////////////////////////////////////////////////////////////////////////
  // SIGNALS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void findFinished(SlHlpResultList findResultIdList,
   *                        unsigned long nCallbackId,
   *                        const QStringList& rszListOfTerms);
   *
   *  \param findResultList   list of results
   *  \param nCallbackId      id of the asynchronous call
   *  \param rszListOfTerms   list of searched terms, may be used for marking text
   *
   *  The search was finished and the searched result compiled.
   *  The result (page references in the form of IDs) is delivered.
   */
  void findFinished(SlHlpResultList, unsigned long, const QStringList&);

  /*! \fn void indexFinished(SlHlpResultList findResultList, unsigned long nCallbackId);
   *
   *  \param findResultList   list of results
   *  \param nCallbackId      id of the asynchronous call
   *
   *  The index was built up and the searched section compiled.
   *  The result (page references in the form of IDs) is delivered.
   */
  void indexFinished(SlHlpResultList, unsigned long);

  /*! \fn void contentFinished(SlHlpResultList findResultList, unsigned long nCallbackId);
   *
   *  \param findResultList   list of results
   *  \param nCallbackId      id of the asynchronous call
   *
   *  The table of contents was built up and the searched entries compiled.
   *  The result (page references in the form of IDs) is delivered.
   */
  void contentFinished(SlHlpResultList, unsigned long);

  /*! \fn void indexOfFinished(long nStartPos, long nNrOfEntries, unsigned long nCallbackId);
   *
   *  \param  nStartPos       first element that starts with the searched charachters
   *  \param  nNrOfEntries    number of elements, that start with the searched charachters
   *  \param nCallbackId      id of the asynchronous call
   *
   *  The table of contents was built up and the searched entries compiled.
   *  The result (page references in the form of IDs) is delivered.
   */
  void indexOfFinished(long, long, unsigned long);

  /*! \fn void indexCountFinished(long nNrOfEntries, unsigned long nCallbackId);
   *
   *  \param  nNrOfEntries    number of elements, that start with the searched charachters
   *  \param nCallbackId      id of the asynchronous call
   *
   *  The table of contents was built up and the searched entries compiled.
   *  The result (number of entries for the specified language) is delivered.
   */
  void indexCountFinished(long, unsigned long);

  /*! \fn void callCanceled(unsigned long nCallbackId);
   *
   *  \param nCallbackId      id of the asynchronous call that was canceled
   *
   *  The call with the id nCallbackId was canceled. The reason may be, that
   *  the server was shut down or that cancel was send.
   */
  void callCanceled(unsigned long);

  /*! \fn void findUrlOfBookFinished(QUrl&, unsigned long);
   *
   *  \param rUrl             url of the searched document
   *  \param nCallbackId      id of the asynchronous call that was canceled
   *
   *  The call with the id nCallbackId was canceled. The reason may be, that
   *  the server was shut down or that cancel was send.
   */
  void findUrlOfBookFinished(QUrl&, unsigned long);

  /*  \fn void readFilesProgress(QString&, long, long, unsigned long);
   *
   *  \param  rszActBookName      Name of the actual book.
   *  \param  nActBook            Number of the actual book.
   *  \param  nTotalBooks         Number of total book.
   *  \param  nCallbackId         Unique identifier of the call.
   *
   *  The binary help files were converted. If nActBook is greater
   *  than nTotalBooks, the convertion is finished.
   */
  void readFilesProgress(QString&, long, long, unsigned long);

protected:
  /////////////////////////////////////////////////////////////////////////////
  // CREATORS (protected)
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlHlpAdapter(QObject* pParent = 0);
   *
   *  \param  pParent parent of the QObject
   *
   *  Constructor
   */
  SlHlpAdapter(QObject* pParent = 0);
};

#endif // SL_HLP_ADAPTER_H
