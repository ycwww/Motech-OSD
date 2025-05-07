// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomadistspecmag.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for relations and distances of 
          special magazines (buffer and load), classes 
          SlTmToMaDistSpecMagColl, SlTmToMaDistSpecMagSpecPlaceColl,
          SlTmToMaDistSpecMagSpecPlaceOrdMagColl and 
          SlTmToMaDistSpecMagSpecPlaceOrdMag
          
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.

  
    
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_DIST_SPEC_MAG_H)
#define SL_TM_TOMA_DIST_SPEC_MAG_H

#include "slhmitemplatesqt.h"

#include "sltmtomamag.h"
#include "sltmtomadistance.h"
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
  \class  SlTmToMaDistSpecMagSpecPlaceOrdMag sltmtomadistspecmag.h
  \brief ordinary magazine with reference rDistance() 
         to contained distance (offset) to special place
         
  This class holds data of classes:
    - SlTmToMaDistance  referenced by SlTmToMaDistSpecMagSpecPlaceOrdMag::rDistance()     
                                  and SlTmToMaDistSpecMagSpecPlaceOrdMag::rConstDistance()
    .

  For overview about relations and distances between special magazine (buffer, load) places 
  and ordinary magazines 
  see page \ref pageoverviewmagazineconf.
    
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDistSpecMagSpecPlaceOrdMag
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaDistSpecMagSpecPlaceOrdMag();

  /// \brief copy constructor
  SlTmToMaDistSpecMagSpecPlaceOrdMag(const SlTmToMaDistSpecMagSpecPlaceOrdMag& rSourceObj /*!< source object */
                                    );
  
  /// \brief destructor
  virtual ~SlTmToMaDistSpecMagSpecPlaceOrdMag();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDistSpecMagSpecPlaceOrdMag& operator= (const SlTmToMaDistSpecMagSpecPlaceOrdMag& rSourceObj /*!< source object */
                                                );
  
  /// \brief returns reference to ordinary magazines distance (offset) to special place
  SlTmToMaDistance&      rDistance(void);         
  
  
  // ACCESSORS

  /// \brief returns const reference to ordinary magazines distance (offset) to special place
  const SlTmToMaDistance&      rConstDistance(void) const;         
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDistSpecMagSpecPlaceOrdMag& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDistSpecMagSpecPlaceOrdMag& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistSpecMagSpecPlaceOrdMag& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistSpecMagSpecPlaceOrdMag& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistSpecMagSpecPlaceOrdMag& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistSpecMagSpecPlaceOrdMag& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistSpecMagSpecPlaceOrdMag& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistSpecMagSpecPlaceOrdMag& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaDistSpecMagSpecPlaceOrdMag& rSourceObj /*!< source object */
                    );

  // MEMBER DATA
  SlTmToMaDistance        m_Distance;       ///< ordinary magazines distance (offset) to special place
  // void*                   m_Reserved;       // ... binary compatibility 

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
                                    QDataStream& rStream,                        /*!< binary data stream source */ 
                                    SlTmToMaDistSpecMagSpecPlaceOrdMag& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                              /*!< text data stream target */ 
                                    const SlTmToMaDistSpecMagSpecPlaceOrdMag& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                              /*!< binary data stream target */ 
                                    const SlTmToMaDistSpecMagSpecPlaceOrdMag& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDistSpecMagSpecPlaceOrdMag
// ////////////////////////////////////////////////////////////////////////////






// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaDistSpecMagSpecPlaceOrdMagCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaMagNoType, SlTmToMaDistSpecMagSpecPlaceOrdMag>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaDistSpecMagSpecPlaceOrdMag, accessed by magNo key of type ::SlTmToMaMagNoType
typedef QMap<SlTmToMaMagNoType, SlTmToMaDistSpecMagSpecPlaceOrdMag>  SlTmToMaDistSpecMagSpecPlaceOrdMagCollMapType;  
                             ///< QMap of SlTmToMaDistSpecMagSpecPlaceOrdMag, accessed by magNo key of type ::SlTmToMaMagNoType

// /////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDistSpecMagSpecPlaceOrdMagColl sltmtomadistspecmag.h
  \brief  This class belongs to magazine description.
          This class contains all ordinary magazines of an special place 
          as ::SlTmToMaDistSpecMagSpecPlaceOrdMagCollMapType map collection 
          of SlTmToMaDistSpecMagSpecPlaceOrdMag elements. 
         
  For overview about relations and distances between special magazine (buffer, load) places 
  and ordinary magazines 
  see page \ref pageoverviewmagazineconf.
           
  This class contains such ordinary magazines of 
  special places (buffer magazine and load magazine places) which are related to an special magazine 
  in SlTmToMaDistSpecMagColl.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDistSpecMagSpecPlaceOrdMagColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaDistSpecMagSpecPlaceOrdMagColl();

  /// \brief copy constructor
  SlTmToMaDistSpecMagSpecPlaceOrdMagColl(
                    const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rSourceObj /*!< source object */
                                        );
  
  /// \brief destructor
  virtual ~SlTmToMaDistSpecMagSpecPlaceOrdMagColl();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDistSpecMagSpecPlaceOrdMagColl& operator= (
                    const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rSourceObj /*!< source object */
                                                    );
  
  /// \brief returns reference to a contained SlTmToMaDistSpecMagSpecPlaceOrdMag ordinary magazine
  /// 
  /// \retval returns a SlTmToMaDistSpecMagSpecPlaceOrdMag& reference to the magazine with key \a magNo. 
  /// 
  /// If \a pIsMagContained is non-null, and key \a magNo is out of range, 
  /// \a *pIsMagContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a magNo is contained in the map, the returned reference 
  /// refers to contained magazine  
  /// and if \a pIsMagContained is non-null, \a *pIsMagContained is set to \c true. 
  ///
  /// To check existence of \a magNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaDistSpecMagSpecPlaceOrdMag& rOrdMag(
                        const SlTmToMaMagNoType magNo,      /*!< magazine number */
                        bool* pIsMagContained = 0            /*!< is key \a magNo contained */
                                             );         
  
  /// \brief remove a magazine addressed by \a magNo
  ///
  /// Remove SlTmToMaDistSpecMagSpecPlaceOrdMag magazine data of a single magazine
  /// adressed by key ::SlTmToMaMagNoType \a magNo.
  /// 
  /// To remove all magazine, use clear().
  void remove(const SlTmToMaMagNoType magNo /*!< magazine number */
             );
  
  /// \brief removes all magazine 
  ///
  /// Removes all magazine of magazine collection.
  /// 
  /// To remove a single magazine, use remove().
  void clear(void);         
  
  /// \brief Inserts a magazine, addressed by \a magNo
  /// \retval reference to inserted or replaced magazine.
  ///
  /// Inserts SlTmToMaDistSpecMagSpecPlaceOrdMag a single ordinary \a rOrdMag
  /// adressed by key ::SlTmToMaMagNoType \a magNo.
  /// 
  /// If there is already a magazine whose key is \a magNo, 
  /// that magazine's value is replaced with \a rOrdMag. 
  /// In this case a reference to replaced magazine is returned, 
  /// else an reference to the new magazine is returned. 
  SlTmToMaDistSpecMagSpecPlaceOrdMag&  insert(
                          const SlTmToMaMagNoType magNo,                      /*!< key magazine number */
                          const SlTmToMaDistSpecMagSpecPlaceOrdMag& rOrdMag   /*!< magazine */
                                             );         
  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaDistSpecMagSpecPlaceOrdMag ordinary magazine
  /// 
  /// \retval returns a const SlTmToMaDistSpecMagSpecPlaceOrdMag& reference to the magazine with key \a magNo. 
  /// 
  /// If \a pIsMagContained is non-null, and key \a magNo is out of range, 
  /// \a *pIsMagContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a magNo is contained in the map, the returned reference 
  /// refers to contained magazine  
  /// and if \a pIsMagContained is non-null, \a *pIsMagContained is set to \c true. 
  ///
  /// To check existence of \a magNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaDistSpecMagSpecPlaceOrdMag& rConstOrdMag(
                                const SlTmToMaMagNoType magNo,    /*!< magazine number */ 
                                bool* pIsMagContained = 0         /*!< is key \a magNo contained */
                                                        ) const;         
  
  /// \brief verify existence of key \a magNo
  /// 
  /// \retval returns \c true if single SlTmToMaDistSpecMagSpecPlaceOrdMag magazine 
  ///         adressed by key ::SlTmToMaMagNoType \a magNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single magazine, use rOrdMag() or rConstOrdMag().
  bool contains(const SlTmToMaMagNoType magNo /*!< magazine number */
               ) const;         
  
  /// \brief get count of contained magazines
  /// \retval int number of contained magazines
  /// 
  /// Get count of contained magazines.
  int count(void) const;         
  
  /// \brief gets all contained magazine number magNo keys as QVector of ::SlTmToMaMagNoType
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained magazine number magNo keys 
  /// as QVector of ::SlTmToMaMagNoType 
  /// in \a rTargetMagNoVector.
  int magNoVector(SlTmToMaMagNosValueVectorType& rTargetMagNoVector 
                                ///< all contained magNo keys 
                                ///< as QVector 
                                ///< of ::SlTmToMaMagNoType magazine numbers 
                 ) const;         
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // MANIPULATORS 

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rSourceObj  /*!< source object */
                    );

  // MEMBER DATA
  SlTmToMaDistSpecMagSpecPlaceOrdMagCollMapType   m_OrdMagCollMap; 
                                ///< QMap of SlTmToMaDistSpecMagSpecPlaceOrdMag, accessed by key of type ::SlTmToMaMagNoType

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
                                    QDataStream& rStream,                             /*!< binary data stream source */ 
                                    SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rData  /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                                   /*!< text data stream target */ 
                                    const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rData  /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                                   /*!< binary data stream target */ 
                                    const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rData  /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDistSpecMagSpecPlaceOrdMagColl
// ////////////////////////////////////////////////////////////////////////////












// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaDistSpecMagSpecPlaceCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<::SlTmToMaPlaceNoType, SlTmToMaDistSpecMagSpecPlaceOrdMagColl>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaDistSpecMagSpecPlaceOrdMagColl, accessed by placeNo key of type ::SlTmToMaPlaceNoType
typedef QMap<SlTmToMaPlaceNoType, SlTmToMaDistSpecMagSpecPlaceOrdMagColl>  SlTmToMaDistSpecMagSpecPlaceCollMapType;  
                             ///< QMap of SlTmToMaDistSpecMagSpecPlaceOrdMagColl, accessed by placeNo key of type ::SlTmToMaPlaceNoType

// /////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDistSpecMagSpecPlaceColl sltmtomadistspecmag.h
  \brief  This class belongs to magazine description.
          This class contains special places of an special magazine (buffer and load) 
          as ::SlTmToMaDistSpecMagSpecPlaceCollMapType map collection 
          of SlTmToMaDistSpecMagSpecPlaceOrdMagColl elements. Each element 
          contains the list of ordinary magazine connections of a special place.
         
  For overview about relations and distances between special magazine (buffer, load) places 
  and ordinary magazines 
  see page \ref pageoverviewmagazineconf.
           
  This class contains SlTmToMaDistSpecMagColl special magazins (buffer magazine and load magazine) 
  special places. The data of each single special place is its list of ordinary magazine connections 
  of class SlTmToMaDistSpecMagSpecPlaceOrdinaryMagColl.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDistSpecMagSpecPlaceColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaDistSpecMagSpecPlaceColl();

  /// \brief copy constructor
  SlTmToMaDistSpecMagSpecPlaceColl(
                    const SlTmToMaDistSpecMagSpecPlaceColl& rSourceObj /*!< source object */
                                  );
  
  /// \brief destructor
  virtual ~SlTmToMaDistSpecMagSpecPlaceColl();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDistSpecMagSpecPlaceColl& operator= (
                    const SlTmToMaDistSpecMagSpecPlaceColl& rSourceObj /*!< source object */
                                              );
  
  /// \brief returns reference to SlTmToMaDistSpecMagSpecPlaceOrdMagColl 
  ///        ordinary magazine collection of a contained special place
  /// 
  /// \retval returns a reference to SlTmToMaDistSpecMagSpecPlaceOrdMagColl 
  /// ordinary magazine collection of the special place with key \a placeNo. 
  /// 
  /// If \a pIsPlaceContained is non-null, and key \a placeNo is out of range, 
  /// \a *pIsPlaceContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a placeNo is contained in the map, the returned reference 
  /// refers to contained places data 
  /// and if \a pIsPlaceContained is non-null, \a *pIsPlaceContained is set to \c true. 
  ///
  /// To check existence of \a placeNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rSpecPlace(
                        const SlTmToMaPlaceNoType placeNo,       /*!< place number */
                        bool* pIsPlaceContained = 0              /*!< is key \a placeNo contained */
                                                    );         
  
  /// \brief remove a place addressed by \a placeNo
  ///
  /// Remove SlTmToMaDistSpecMagSpecPlaceOrdMagColl place data of a single place
  /// adressed by key ::SlTmToMaPlaceNoType \a placeNo.
  /// 
  /// To remove all places, use clear().
  void remove(const SlTmToMaPlaceNoType placeNo /*!< place number */
             );
  
  /// \brief removes all places 
  ///
  /// Removes all places of place collection.
  /// 
  /// To remove a single place, use remove().
  void clear(void);         
  
  /// \brief Inserts a place, addressed by \a placeNo
  /// \retval reference to inserted or replaced place.
  ///
  /// Inserts SlTmToMaDistSpecMagSpecPlaceOrdMagColl of a single \a rSpecPlace
  /// adressed by key ::SlTmToMaPlaceNoType \a placeNo.
  /// 
  /// If there is already a place whose key is \a placeNo, 
  /// that place's value is replaced with \a rSpecPlace. 
  /// In this case a reference to replaced place is returned, 
  /// else an reference to the new place is returned. 
  SlTmToMaDistSpecMagSpecPlaceOrdMagColl&  insert(
                          const SlTmToMaPlaceNoType placeNo,                           
                                      /*!< key place number */
                          const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rSpecPlace   
                                      /*!< places data (special places ordinary magazine collection) */
                                                 );         
  
  // ACCESSORS

  /// \brief returns const reference to SlTmToMaDistSpecMagSpecPlaceOrdMagColl 
  ///        ordinary magazine collection of a contained special place
  /// 
  /// \retval returns a const reference to SlTmToMaDistSpecMagSpecPlaceOrdMagColl 
  /// ordinary magazine collection of the special place with key \a placeNo. 
  /// 
  /// If \a pIsPlaceContained is non-null, and key \a placeNo is out of range, 
  /// \a *pIsPlaceContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a placeNo is contained in the map, the returned reference 
  /// refers to contained places data 
  /// and if \a pIsPlaceContained is non-null, \a *pIsPlaceContained is set to \c true. 
  ///
  /// To check existence of \a placeNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaDistSpecMagSpecPlaceOrdMagColl& rConstSpecPlace(
                                const SlTmToMaPlaceNoType placeNo,     /*!< place number */ 
                                bool* pIsPlaceContained = 0            /*!< is key \a placeNo contained */
                                                               ) const;         
  
  /// \brief verify existence of key \a placeNo
  /// 
  /// \retval returns \c true if single places SlTmToMaDistSpecMagSpecPlaceOrdMagColl data 
  ///         adressed by key ::SlTmToMaPlaceNoType \a placeNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single places data, use rSpecPlace() or rConstSpecPlace().
  bool contains(const SlTmToMaPlaceNoType placeNo /*!< place number */
               ) const;         
  
  /// \brief get count of contained places
  /// \retval int number of contained places
  /// 
  /// Get count of contained places.
  int count(void) const;         
  
  /// \brief gets place number placeNo keys as QVector of ::SlTmToMaPlaceNoType 
  ///        of all contained special places
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get place number placeNo keys 
  /// as QVector of ::SlTmToMaPlaceNoType 
  /// in \a rTargetPlaceNoVector of all contained special places.
  int placeNoVector(SlTmToMaPlaceNosValueVectorType& rTargetPlaceNoVector 
                                /*!< all contained placeNo keys 
                                     as QVector 
                                     of ::SlTmToMaPlaceNoType place numbers 
                                */
                   ) const;         
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDistSpecMagSpecPlaceColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDistSpecMagSpecPlaceColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistSpecMagSpecPlaceColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistSpecMagSpecPlaceColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistSpecMagSpecPlaceColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistSpecMagSpecPlaceColl& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistSpecMagSpecPlaceColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistSpecMagSpecPlaceColl& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaDistSpecMagSpecPlaceColl& rSourceObj  /*!< source object */
                    );

  // MEMBER DATA
  SlTmToMaDistSpecMagSpecPlaceCollMapType   m_SpecPlaceCollMap; 
                                ///< QMap of SlTmToMaDistSpecMagSpecPlaceOrdMagColl, accessed by key of type ::SlTmToMaPlaceNoType

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
                                    QDataStream& rStream,                      /*!< binary data stream source */ 
                                    SlTmToMaDistSpecMagSpecPlaceColl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                            /*!< text data stream target */ 
                                    const SlTmToMaDistSpecMagSpecPlaceColl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                            /*!< binary data stream target */ 
                                    const SlTmToMaDistSpecMagSpecPlaceColl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDistSpecMagSpecPlaceColl
// ////////////////////////////////////////////////////////////////////////////









// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaDistSpecMagCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaMagNoType, SlTmToMaDistSpecMagSpecPlaceColl>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaDistSpecMagSpecPlaceColl, accessed by magNo key of type ::SlTmToMaMagNoType
typedef QMap<SlTmToMaMagNoType, SlTmToMaDistSpecMagSpecPlaceColl>  SlTmToMaDistSpecMagCollMapType;  
                             ///< QMap of SlTmToMaDistSpecMagSpecPlaceColl, accessed by magNo key of type ::SlTmToMaMagNoType

// /////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDistSpecMagColl sltmtomadistspecmag.h
  \brief  This class belongs to magazine description.
          This class contains a ::SlTmToMaDistSpecMagCollMapType map collection 
          of special magazins (bufffer and load) 
          and their special places connections to ordinary magazines. 
          All special places are contained, even if they have zero conections to 
          ordinary magazines.
       
  For overview about relations and distances between special magazine (buffer, load) places 
  and ordinary magazines 
  see page \ref pageoverviewmagazineconf.
           
  This class contains a collection of special magazins (bufffer and load) and 
  their special places connections to ordinary magazines. 
  The data of a single special magazine of this collection consists of SlTmToMaDistSpecMagSpecPlaceColl.
  This is the collection of special places of the single special magazine. 
  Each of this special places has a collection SlTmToMaDistSpecMagSpecPlaceOrdMagColl 
  of its ordinary magazines SlTmToMaDistSpecMagSpecPlaceOrdMag which are connected 
  to the special magazine and each connection has 
  a reference SlTmToMaDistSpecMagSpecPlaceOrdMag::rDistance() 
  to SlTmToMaDistance distance of places.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDistSpecMagColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaDistSpecMagColl();

  /// \brief copy constructor
  SlTmToMaDistSpecMagColl(
                    const SlTmToMaDistSpecMagColl& rSourceObj /*!< source object */
                         );
  
  /// \brief destructor
  virtual ~SlTmToMaDistSpecMagColl();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDistSpecMagColl& operator= (
                    const SlTmToMaDistSpecMagColl& rSourceObj /*!< source object */
                                     );
  
  /// \brief returns reference to SlTmToMaDistSpecMagSpecPlaceColl special place collection 
  ///        of a contained special magazine
  /// 
  /// \retval returns a reference to SlTmToMaDistSpecMagSpecPlaceColl special place collection 
  /// of the special magazine with key \a magNo. 
  /// 
  /// If \a pIsMagContained is non-null, and key \a magNo is out of range, 
  /// \a *pIsMagContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a magNo is contained in the map, the returned reference 
  /// refers to contained magazines data 
  /// and if \a pIsMagContained is non-null, \a *pIsMagContained is set to \c true. 
  ///
  /// To check existence of \a magNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaDistSpecMagSpecPlaceColl& rSpecMag(
                        const SlTmToMaMagNoType magNo,       /*!< magazine number */
                        bool* pIsMagContained = 0            /*!< is key \a magNo contained */
                                            );         
  
  /// \brief remove a special magazine addressed by \a magNo
  ///
  /// Remove SlTmToMaDistSpecMagSpecPlaceColl magazine data of a single magazine
  /// adressed by key ::SlTmToMaMagNoType \a magNo.
  /// 
  /// To remove all magazines, use clear().
  void remove(const SlTmToMaMagNoType magNo /*!< magazine number */
             );
  
  /// \brief removes all magazines 
  ///
  /// Removes all magazines of magazine collection.
  /// 
  /// To remove a single magazine, use remove().
  void clear(void);         
  
  /// \brief Inserts a special magazine (more precisely: it's special places collection data), 
  ///        addressed by \a magNo
  /// \retval reference to inserted or replaced magazine.
  ///
  /// Inserts SlTmToMaDistSpecMagSpecPlaceColl of a single special \a magazine
  /// adressed by key ::SlTmToMaMagNoType \a magNo.
  /// 
  /// If there is already a magazine whose key is \a magNo, 
  /// that magazine's value is replaced with \a magazine. 
  /// In this case a reference to replaced magazine is returned, 
  /// else an reference to the new magazine is returned. 
  SlTmToMaDistSpecMagSpecPlaceColl&  insert(
                          const SlTmToMaMagNoType magNo,                           
                                      /*!< key magazine number */
                          const SlTmToMaDistSpecMagSpecPlaceColl& magazine   
                                      /*!< magazines data (special magazines special places collection) */
                                           );         
  
  // ACCESSORS

  /// \brief returns const reference to SlTmToMaDistSpecMagSpecPlaceColl special place collection 
  ///        of a contained special magazine
  /// 
  /// \retval returns a const reference to SlTmToMaDistSpecMagSpecPlaceColl special place collection 
  /// of the special magazine with key \a magNo. 
  /// 
  /// If \a pIsMagContained is non-null, and key \a magNo is out of range, 
  /// \a *pIsMagContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a magNo is contained in the map, the returned reference 
  /// refers to contained magazines data 
  /// and if \a pIsMagContained is non-null, \a *pIsMagContained is set to \c true. 
  ///
  /// To check existence of \a magNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaDistSpecMagSpecPlaceColl& rConstSpecMag(
                                const SlTmToMaMagNoType magNo,     /*!< magazine number */ 
                                bool* pIsMagContained = 0          /*!< is key \a magNo contained */
                                                       ) const;         
  
  /// \brief verify existence of key \a magNo
  /// 
  /// \retval returns \c true if single magazines SlTmToMaDistSpecMagSpecPlaceColl data 
  ///         adressed by key ::SlTmToMaMagNoType \a magNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single magazines data, use rSpecMag() or rConstSpecMag().
  bool contains(const SlTmToMaMagNoType magNo /*!< magazine number */
               ) const;         
  
  /// \brief get count of contained magazines
  /// \retval int number of contained magazines
  /// 
  /// Get count of contained magazines.
  int count(void) const;         
  
  /// \brief gets magazine number magNo keys as QVector of ::SlTmToMaMagNoType 
  ///        of all contained special magazines
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get magazine number magNo keys 
  /// as QVector of ::SlTmToMaMagNoType 
  /// in \a rTargetMagNoVector of all contained special magazines.
  int magNoVector(SlTmToMaMagNosValueVectorType& rTargetMagNoVector 
                                /*!< all contained magNo keys 
                                     as QVector 
                                     of ::SlTmToMaMagNoType magazine numbers 
                                */
                 ) const;         
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDistSpecMagColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDistSpecMagColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistSpecMagColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistSpecMagColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistSpecMagColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // MANIPULATORS 

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistSpecMagColl& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistSpecMagColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistSpecMagColl& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaDistSpecMagColl& rSourceObj  /*!< source object */
                    );

  // MEMBER DATA
  SlTmToMaDistSpecMagCollMapType   m_SpecMagCollMap; 
                                ///< QMap of SlTmToMaDistSpecMagSpecPlaceColl, accessed by key of type ::SlTmToMaMagNoType
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
                                    QDataStream& rStream,             /*!< binary data stream source */ 
                                    SlTmToMaDistSpecMagColl& rData    /*!< import target object */
                                               );


/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                   /*!< text data stream target */ 
                                    const SlTmToMaDistSpecMagColl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                   /*!< binary data stream target */ 
                                    const SlTmToMaDistSpecMagColl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDistSpecMagColl
// ////////////////////////////////////////////////////////////////////////////




#endif // !defined(SL_TM_TOMA_DIST_SPEC_MAG_H)
