// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomamagconf.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for magazine configuration data classes 
          SlTmToMaMagConf and SlTmToMaMagConfData
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_MAGCONF_H)
#define SL_TM_TOMA_MAGCONF_H


#include "slhmitemplatesqt.h"

#include "sltmtomavariantdata.h"
#include "sltmtomacontainersize.h"
#include "sltmtomamag.h"
#include "sltmtomadistordmag.h"
#include "sltmtomadistspecmag.h"
#include "sltmtomaexportimport.h"
#include <QtCore/QTextStream>


#if !defined (SL_TM_UTILITIES_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_TM_UTILITIES_EXPORTS)
#        define SL_TM_UTILITIES_EXPORT __declspec (dllexport)
#     else
#        define SL_TM_UTILITIES_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_TM_UTILITIES_EXPORT
#  endif
#endif


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMagConfData sltmtomamagconf.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the parameters of a Magazine Configuration.
          (Magazine Configuration data)         

  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the parameters of a Magazine Configuration
  (like BTSS interface data module TMC).

  Use MagConfDataIdxEnum for \a idx in methods:
    - SlTmToMaMagConfData::val(SlTmToMaMagConfData::MagConfDataIdxEnum, ...) and 
    - SlTmToMaMagConfData::setVal(SlTmToMaMagConfData::MagConfDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_MAGCONF_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMagConfData
{
public:
  // ENUMS
  /// \brief This is the index enum for magazine configuration Data Parameter class SlTmToMaMagConfData
  ///        (TMC, magazine configuration parameter)
  enum MagConfDataIdxEnum
  {
    MAGCONF_DATA_IDENT                  = 0, ///< QString, name of magazine configuration (magCBIdent) ($TC_MAMP1)       
    MAGCONF_DATA_LOAD_MAG_NO            = 1, ///< int      number (not count) of the internal load magazine (magBLMag)   
    MAGCONF_DATA_BUFFER_MAG_NO          = 2, ///< int      number (not count) of the internal buffer magazine (magZWMag) 
    MAGCONF_DATA_TOOL_SEARCH            = 3, ///< int      kind of tool search (magSearch) ($TC_MAMP2)                   
    MAGCONF_DATA_PLACE_SEARCH           = 4, ///< int      kind of search for empty magazine location ($TC_MAMP2)        
    MAGCONF_DATA_NUM_ORDINARY_PLACES    = 5, ///< int      count of places without load and buffer (magVPlaces)          
    MAGCONF_DATA_NUM_ALL_PLACES         = 6, ///< int      count of all places (incl. load and buffer) (magRPlaces)      
    MAGCONF_DATA_MODE_WEARGROUP         = 7, ///< int      mode of handling wear group (modeWearGroup) ($TC_MAMP3)       
    MAGCONF_DATA_NUM_ALL_MAGS           = 8, ///< int      count of all magazins (incl. load and buffer)                 
    MAGCONF_DATA_NUM_ORDINARY_MAGS      = 9, ///< int      count of magazins without load and buffer                     

    //Do not change behind when extend enumeration!!!
    MAGCONF_DATA_MAX_COUNT,              ///< Max number of Magazine Config data parameters in SlTmToMaMagConfData
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMagConfData(const int numElements = 0 /*!< number of elements, default = 0 */
                              );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaMagConfData(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_MAGCONF_DATA_PARAMS
                              );

  /// \brief copy constructor
  SlTmToMaMagConfData(const SlTmToMaMagConfData& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaMagConfData();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMagConfData& operator= (const SlTmToMaMagConfData& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  /// 
  /// If \a rSourceVal is of type Invalid, member data is set to int 0.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMagConfData::MagConfDataIdxEnum */ 
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to int 0.
  /// 
  /// If a \a rSourceVal vector element is of type Invalid, corresponding member data is set to int 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMagConfData::MagConfDataIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagConfData& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // ACCESSORS
  /// \brief get count of member data elements
  /// \retval int number of data members.
  int count(void) const;

  // get
  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaMagConfData::MagConfDataIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMagConfData::MagConfDataIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagConfData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagConfData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMagConfData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMagConfData& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagConfData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagConfData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagConfData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaMagConfData& rSourceObj  /*!< source object */
                    );

  // ACCESSORS


  // MEMBER DATA

  SlTmToMaVariantData  m_Data;      ///<  Data, QVector<QVariant> QVector collection of QVector data

  void*                m_Reserved;  ///< reserved for binary compatibility


};

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rData from binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// Stream data determinates number of member values.

SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,            /*!< binary data stream source */ 
                                    SlTmToMaMagConfData& rData       /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                  /*!< text data stream target */ 
                                    const SlTmToMaMagConfData& rData       /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                  /*!< binary data stream target */ 
                                    const SlTmToMaMagConfData& rData       /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMagConfData
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMagConf sltmtomamagconf.h
  \brief  This class contains all data of a Magazine configuration 
         
  This class holds data of classes:
  - SlTmToMaMagConfData     referenced by SlTmToMaMagConf::rData()                 
                                         and SlTmToMaMagConf::rConstData()            
  - SlTmToMaMagColl         referenced by SlTmToMaMagConf::rMagColl()              
                                         and SlTmToMaMagConf::rConstMagColl()         
  - SlTmToMaDistOrdMagColl  referenced by SlTmToMaMagConf::rDistOrdMagColl()       
                                         and SlTmToMaMagConf::rConstDistOrdMagColl()  
  - SlTmToMaDistSpecMagColl referenced by SlTmToMaMagConf::rDistSpecMagColl()      
                                         and SlTmToMaMagConf::rConstDistSpecMagColl() 
  .                                                                                      

  SlTmToMaMagConfData contains magazine configuration data.

  SlTmToMaMagColl contains all magazines and their places inclusive tNo tool numbers of loaded tools.

  SlTmToMaDistOrdMagColl and SlTmToMaDistSpecMagColl: 
  For overview about relations and distances between special magazine (buffer, load) places 
  and ordinary magazines \n
  see page \ref pageoverviewmagazineconf.
  
  
  For convenience: methods to access buffer and load magazine related data: 
  - To get a QVector list \a rTargetBufferPlaceNoVector (caller owned) 
    of connected buffer place numbers of an ordinary magazine \a ordMagNo, 
    use: \n
    int SlTmToMaMagConf::getBufferPlaceNoVectorOfOrdMagazine(
                                              const ::SlTmToMaMagNoType ordMagNo, 
                                              ::SlTmToMaPlaceNosValueVectorType& rTargetBufferPlaceNoVector
                                                            ) 
  - To get a QVector list \a rTargetOrdMagNoVector (caller owned) 
    of connected ordinary magazine numbers of a buffer magazine place \a bufferPlaceNo, 
    use: \n
    int SlTmToMaMagConf::getOrdMagNoVectorOfBufferPlace(
                                              const ::SlTmToMaPlaceNoType bufferPlaceNo, 
                                              ::SlTmToMaMagNosValueVectorType& rTargetOrdMagNoVector
                                                       )
  - To get magazine number of buffer magazine as return value, 
    use: \n
    ::SlTmToMaMagNoType SlTmToMaMagConf::getBufferMagNo( )
  - To get a const reference to buffer magazine in magazine collection SlTmToMaMagColl, 
    use: \n
    SlTmToMaMag& SlTmToMaMagConf::rConstBufferMag( bool* pIsBufferMagContained = 0 )
  - To get a QVector list \a rTargetLoadPlaceNoVector (caller owned) 
    of connected load place numbers of an ordinary magazine \a ordMagNo, 
    use: \n
    int SlTmToMaMagConf::getLoadPlaceNoVectorOfOrdMagazine(
                                              const ::SlTmToMaMagNoType ordMagNo, 
                                              ::SlTmToMaPlaceNosValueVectorType& rTargetLoadPlaceNoVector
                                                          ) 
  - To get a QVector list \a rTargetOrdMagNoVector (caller owned) 
    of connected ordinary magazine numbers of a load magazine place \a loadPlaceNo, 
    use: \n
    int SlTmToMaMagConf::getOrdMagNoVectorOfLoadPlace(
                                              const ::SlTmToMaPlaceNoType loadPlaceNo, 
                                              ::SlTmToMaMagNosValueVectorType& rTargetOrdMagNoVector
                                                     )
  - To get magazine number of load magazine as return value, 
    use: \n
    ::SlTmToMaMagNoType SlTmToMaMagConf::getLoadMagNo( )
  - To get a const reference to load magazine in magazine collection SlTmToMaMagColl, 
    use: \n
    SlTmToMaMag& SlTmToMaMagConf::rConstLoadMag(bool* pIsLoadMagContained = 0)
  .

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMagConf
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaMagConf();

  /// \brief constructor, reads vector sizes from corresponding \a rContainerSize elements 
  ///        to size member value vectors during construction.   
  explicit SlTmToMaMagConf(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from corresponding elements of \a rContainerSize 
                                      */
                          );

  /// \brief copy constructor
  SlTmToMaMagConf(const SlTmToMaMagConf& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaMagConf();

  // MANIPULATORS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagConf& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMagConf& operator= (const SlTmToMaMagConf& rSourceObj /*!< source object */
                             );
  
  /// \brief returns reference to general parameters of magazine configuration
  SlTmToMaMagConfData&      rData(void);         
  
  /// \brief returns reference to magazine collection of magazine configuration
  SlTmToMaMagColl&          rMagColl(void);        
  
  /// \brief returns reference to ordinary magazine collection of magazine configuration
  SlTmToMaDistOrdMagColl&   rDistOrdMagColl(void);        
  
  /// \brief returns reference to special magazine collection of magazine configuration
  SlTmToMaDistSpecMagColl&  rDistSpecMagColl(void);        
  
  
  // ACCESSORS

  /// \brief returns const reference to general parameters of magazine configuration
  const SlTmToMaMagConfData&      rConstData(void) const;         
  
  /// \brief returns const reference to magazine collection of magazine configuration
  const SlTmToMaMagColl&          rConstMagColl(void) const;        
  
  /// \brief returns const reference to ordinary magazine collection of magazine configuration
  const SlTmToMaDistOrdMagColl&   rConstDistOrdMagColl(void) const;        
  
  /// \brief returns const reference to special magazine collection of magazine configuration
  const SlTmToMaDistSpecMagColl&  rConstDistSpecMagColl(void) const;        
  

  /// \brief get QVector \a rTargetBufferPlaceNoVector (caller owned) 
  ///        of connected buffer place numbers of an ordinary magazine \a ordMagNo. 
  ///        If \a ordMagNo is 0, all NOT connected buffer place numbers are given back 
  ///        in (caller owned) rTargetBufferPlaceNoVector.  
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  int getBufferPlaceNoVectorOfOrdMagazine(
                                  const SlTmToMaMagNoType ordMagNo, 
                                           ///< magzine number of an ordinary magazine
                                  SlTmToMaPlaceNosValueVectorType& rTargetBufferPlaceNoVector
                                           ///< all connected buffer magazine place numbers 
                                           ///< of ordinary magazine \a ordMagNo 
                                           ///< as QVector of ::SlTmToMaPlaceNoType place numbers 
                                         ) const;
    
  /// \brief get QVector \a rTargetLoadPlaceNoVector (caller owned) 
  ///        of connected load place numbers of an ordinary magazine \a ordMagNo. 
  ///        If \a ordMagNo is 0, all NOT connected load place numbers are given back 
  ///        in (caller owned) rTargetLoadPlaceNoVector.  
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  int getLoadPlaceNoVectorOfOrdMagazine(
                                  const SlTmToMaMagNoType ordMagNo, 
                                           ///< magzine number of an ordinary magazine
                                  SlTmToMaPlaceNosValueVectorType& rTargetLoadPlaceNoVector
                                           ///< all connected load magazine place numbers 
                                           ///< of ordinary magazine \a ordMagNo 
                                           ///< as QVector of ::SlTmToMaPlaceNoType place numbers 
                                       ) const;
    
  /// \brief get QVector \a rTargetOrdMagNoVector (caller owned) 
  ///        of connected ordinary magazine numbers of buffer magazine place \a bufferPlaceNo. 
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  int getOrdMagNoVectorOfBufferPlace(
                                  const SlTmToMaPlaceNoType bufferPlaceNo, 
                                           ///< place number of a buffer magazine place
                                  SlTmToMaMagNosValueVectorType& rTargetOrdMagNoVector
                                           ///< all connected ordinary magazine numbers 
                                           ///< of buffer magazine place \a bufferPlaceNo 
                                           ///< as QVector of ::SlTmToMaMagNoType magazine numbers 
                                    ) const;
    
  /// \brief get QVector \a rTargetOrdMagNoVector (caller owned) 
  ///        of connected ordinary magazine numbers of load magazine place \a loadPlaceNo. 
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  int getOrdMagNoVectorOfLoadPlace(
                                  const SlTmToMaPlaceNoType loadPlaceNo, 
                                           ///< place number of a load magazine place
                                  SlTmToMaMagNosValueVectorType& rTargetOrdMagNoVector
                                           ///< all connected ordinary magazine numbers 
                                           ///< of load magazine place \a loadPlaceNo 
                                           ///< as QVector of ::SlTmToMaMagNoType magazine numbers 
                                  ) const;
    
  /// \brief return magazine number of buffer magazine
  /// 
  /// \retval ::SlTmToMaMagNoType magazine number of buffer magazine, 
  ///         0 in case of error or if no buffer magazine exists.
  /// 
  SlTmToMaMagNoType getBufferMagNo(void) const;
    
  /// \brief return magazine number of load magazine
  /// 
  /// \retval ::SlTmToMaMagNoType magazine number of load magazine, 
  ///         0 in case of error or if no buffer magazine exists.
  /// 
  SlTmToMaMagNoType getLoadMagNo(void) const;
    
  /// \brief return const SlTmToMaMag& reference to buffer magazine 
  ///        in magazine collection SlTmToMaMagColl 
  ///        SlTmToMaMagConf::rConstMagColl().SlTmToMaMagColl::rConstMag()
  /// 
  /// \retval returns a const SlTmToMaMag& reference to buffer magazine. 
  /// 
  /// If \a pIsBufferMagContained is non-null, and buffer magazine does not exist, 
  /// \a *pIsBufferMagContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If buffer magazine is contained in the collection, the returned reference 
  /// refers to buffer magazine 
  /// and if \a pIsBufferMagContained is non-null, \a *pIsBufferMagContained is set to \c true. 
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() 
  /// in magazine collection SlTmToMaMagColl       
  /// SlTmToMaMagConf::rMagColl().rMag() occures.
  const SlTmToMaMag& rConstBufferMag(
                                  bool* pIsBufferMagContained = 0
                                      ///< is buffer magazine contained in 
                                      ///< magazine collection SlTmToMaMagColl 
                                      ///< SlTmToMaMagConf::rConstMagColl().SlTmToMaMagColl::rConstMag()
                                    ) const;
    
  /// \brief return const SlTmToMaMag& reference to load magazine 
  ///        in magazine collection SlTmToMaMagColl 
  ///        SlTmToMaMagConf::rConstMagColl().SlTmToMaMagColl::rConstMag()
  /// 
  /// \retval returns a const SlTmToMaMag& reference to load magazine. 
  /// 
  /// If \a pIsLoadMagContained is non-null, and load magazine does not exist, 
  /// \a *pIsLoadMagContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If load magazine is contained in the collection, the returned reference 
  /// refers to load magazine 
  /// and if \a pIsLoadMagContained is non-null, \a *pIsLoadMagContained is set to \c true. 
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() 
  /// in magazine collection SlTmToMaMagColl       
  /// SlTmToMaMagConf::rMagColl().rMag() occures.
  const SlTmToMaMag& rConstLoadMag(
                                bool* pIsLoadMagContained = 0
                                    ///< is load magazine contained in 
                                    ///< magazine collection SlTmToMaMagColl 
                                    ///< SlTmToMaMagConf::rConstMagColl().SlTmToMaMagColl::rConstMag()
                                  ) const;

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagConf& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagConf& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMagConf& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMagConf& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagConf& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagConf& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagConf& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaMagConf& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaMagConfData      m_Data;            ///< General parameters of magazine configuration
  SlTmToMaMagColl          m_MagColl;         ///< Magazine collection of magazine configuration
  SlTmToMaDistOrdMagColl   m_DistOrdMagColl;  ///< Ordinary magazine collection, 
                                              ///  relations and distances to special magazin places
  SlTmToMaDistSpecMagColl  m_DistSpecMagColl; ///< Special magazine collection, 
                                              ///< relations and distances of special places 
                                              ///< to ordinary magazins
  void*                    m_Reserved;        // ... binary compatibility
};

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rData from binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// Stream data determinates number of member values.
/// 
/// If a stream element is not castable, corresponding member data is set to 0.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,     /*!< binary data stream source */ 
                                    SlTmToMaMagConf& rData    /*!< import target object */
                                               );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,           /*!< text data stream target */ 
                                    const SlTmToMaMagConf& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,           /*!< binary data stream target */ 
                                    const SlTmToMaMagConf& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMagConf
// ////////////////////////////////////////////////////////////////////////////
#endif // !defined(SL_TM_TOMA_MAGCONF_H)
