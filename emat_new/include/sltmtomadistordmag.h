// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomadistordmag.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for relations and distances of ordinary magazines, classes 
          SlTmToMaDistOrdMagColl, SlTmToMaDistOrdMagSpecMagColl,
          SlTmToMaDistOrdMagSpecMagSpecPlaceColl and 
          SlTmToMaDistOrdMagSpecMagSpecPlace
          
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.

  
    
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_DIST_ORD_MAG_H)
#define SL_TM_TOMA_DIST_ORD_MAG_H

#include "slhmitemplatesqt.h"

#include "sltmtomamag.h"
#include "sltmtomaplace.h"
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



/*!
  \page pageoverviewmagazineconf Relations and distances between special magazine (buffer, load) places and ordinary magazines.

  Relations and distances between special magazine (buffer, load) places and ordinary magazines

  - Relations and distances (offsets) from ordinary magazines to special magazine places:
    - Example: 
      SlTmToMaMagConf::rDistOrdMagColl().rOrdMag(6).rSpecMag(9998).rSpecPlace(1).rDistance().setVal(source) and 
      SlTmToMaMagConf::rConstDistOrdMagColl().rConstOrdMag(6).rConstSpecMag(9998).rConstSpecPlace(1).rConstDistance().val(target)
    - Participant classes and methods:
      - SlTmToMaDistOrdMagColl&                      SlTmToMaMagConf::rDistOrdMagColl()
      - SlTmToMaDistOrdMagSpecMagColl&               SlTmToMaDistOrdMagColl::rOrdMag()
      - SlTmToMaDistOrdMagSpecMagSpecPlaceColl&      SlTmToMaDistOrdMagSpecMagColl::rSpecMag()
      - SlTmToMaDistOrdMagSpecMagSpecPlace&          SlTmToMaDistOrdMagSpecMagSpecPlaceColl::rSpecPlace()
      - SlTmToMaDistance&                            SlTmToMaDistOrdMagSpecMagSpecPlace::rDistance()
      - (int retVal)                                 SlTmToMaDistance::setVal()
      .
    - Explanation:
      The class SlTmToMaMagConf has a method SlTmToMaMagConf::rDistOrdMagColl() 
      to get a reference to SlTmToMaDistOrdMagColl to get relations and distances from 
      ordinary magazins to special magazin places.
      The class SlTmToMaDistOrdMagColl contains a collection of ordinary magazins and 
      their connections to special places of buffer magazine and load magazine. 
      The data of a single magazine of this collection consists of SlTmToMaDistOrdMagSpecMagColl.
      This is the collection of special magazines (buffer and load) of the single magazine. 
      Each of this special magazines has a collection SlTmToMaDistOrdMagSpecMagSpecPlaceColl 
      of its special places SlTmToMaDistOrdMagSpecMagSpecPlace which are connected 
      to the ordinary magazine and each connection has 
      a reference (SlTmToMaDistOrdMagSpecMagSpecPlace::rDistance()) 
      to SlTmToMaDistance distance of places.
    - Usage example: 
      To get a QVector list of connected buffer place numbers 
      of ordinary magazine no 6, use (if buffer magaine number is 9998): 
      SlTmToMaMagConf::rDistOrdMagColl().rOrdMag(6).rSpecMag(9998).placeNoVector(rTargetBufferPlaceNoVector) 
      or much easier use convenience method 
      SlTmToMaMagConf::getBufferPlaceNoVectorOfOrdMagazine( 6, rTargetBufferPlaceNoVector )
    .
  - Relations and distances (offsets) from special magazine places to ordinary magazines:
    - Example: 
      SlTmToMaMagConf::rDistSpecMagColl().rSpecMag(9998).rSpecPlace(1).rOrdMag(6).rDistance().setVal(sourve) and 
      SlTmToMaMagConf::rConstDistSpecMagColl().rConstSpecMag(9998).rConstSpecPlace(1).rConstOrdMag(6).rConstDistance().val(target)
    - Participant classes and methods:
      - SlTmToMaDistSpecMagColl&                     SlTmToMaMagConf::rDistSpecMagColl()
      - SlTmToMaDistSpecMagSpecPlaceCol&             SlTmToMaDistSpecMagColl::rSpecMag()
      - SlTmToMaDistSpecMagSpecPlaceOrdMagCol&       SlTmToMaDistSpecMagSpecPlaceCol::rSpecPlace()
      - SlTmToMaDistSpecMagSpecPlaceOrdMag&          SlTmToMaDistSpecMagSpecPlaceOrdMagCol::rOrdMag()
      - SlTmToMaDistance&                            SlTmToMaDistSpecMagSpecPlaceOrdMag::rDistance()
      - (int retVal)                                 SlTmToMaDistance::setVal()
      .
    - Explanation:
      The class SlTmToMaMagConf has a method SlTmToMaMagConf::rDistSpecMagColl() 
      to get a reference to SlTmToMaDistSpecMagColl to get relations and distances from 
      special magazin places to ordinary magazins.
      The class SlTmToMaDistSpecMagColl contains a collection of 
      special magazins (buffer and load magazine) and their special places connections 
      to ordinary magazines.
      The data of a single special magazine of SlTmToMaDistSpecMagColl 
      consists of SlTmToMaDistSpecMagSpecPlaceColl.
      This is the collection of special magazines special places. 
      Each of this special places has a collection SlTmToMaDistSpecMagSpecPlaceOrdMagColl 
      of its ordinary magazines SlTmToMaDistSpecMagSpecPlaceOrdMag which are connected 
      to the special places. Each connection has 
      a reference (SlTmToMaDistSpecMagSpecPlaceOrdMag::rDistance()) 
      to SlTmToMaDistance distance of places.
    - Usage example: 
      To get a QVector list of connected ordinary magazines numbers 
      of buffer magazine special place 2, use (if buffer magaine number is 9998): 
      SlTmToMaMagConf::rDistSpecMagColl().rSpecMag(9998).rSpecPlace(2).magNoVector(rTargetOrdMagNoVector)
      or much easier use convenience method 
      SlTmToMaMagConf::getOrdMagNoVectorOfBufferPlace(2, rTargetOrdMagNoVector)
    .
  - Convenience methods: 
    - To get a QVector list \a rTargetBufferPlaceNoVector (caller owned) 
      of connected buffer place numbers of an ordinary magazine \a ordMagNo, 
      use:\n
      int SlTmToMaMagConf::getBufferPlaceNoVectorOfOrdMagazine(
                                                const ::SlTmToMaMagNoType ordMagNo, 
                                                ::SlTmToMaPlaceNosValueVectorType& rTargetBufferPlaceNoVector
                                                                 ) 
    - To get a QVector list \a rTargetLoadPlaceNoVector (caller owned) 
      of connected load place numbers of an ordinary magazine \a ordMagNo, 
      use:\n
      int SlTmToMaMagConf::getLoadPlaceNoVectorOfOrdMagazine(
                                                const ::SlTmToMaMagNoType ordMagNo, 
                                                ::SlTmToMaPlaceNosValueVectorType& rTargetLoadPlaceNoVector
                                                               ) 
    - To get a QVector list \a rTargetOrdMagNoVector (caller owned) 
      of connected ordinary magazine numbers of a buffer magazine place \a bufferPlaceNo, 
      use:\n
      int SlTmToMaMagConf::getOrdMagNoVectorOfBufferPlace(
                                                const ::SlTmToMaPlaceNoType bufferPlaceNo, 
                                                ::SlTmToMaMagNosValueVectorType& rTargetOrdMagNoVector
                                                            )
    - To get a QVector list \a rTargetOrdMagNoVector (caller owned) 
      of connected ordinary magazine numbers of a load magazine place \a loadPlaceNo, 
      use:\n
      int SlTmToMaMagConf::getOrdMagNoVectorOfLoadPlace(
                                                const ::SlTmToMaPlaceNoType loadPlaceNo, 
                                                ::SlTmToMaMagNosValueVectorType& rTargetOrdMagNoVector
                                                          )
    - To get magazine number of buffer magazine as return value, 
      use:\n
      ::SlTmToMaMagNoType SlTmToMaMagConf::getBufferMagNo( )
    - To get magazine number of load magazine as return value, 
      use:\n
      ::SlTmToMaMagNoType SlTmToMaMagConf::getLoadMagNo( )
    - To get a const reference to buffer magazine in magazine collection SlTmToMaMagColl, 
      use:\n
      SlTmToMaMag& SlTmToMaMagConf::rConstBufferMag( bool* pIsBufferMagContained = 0 )
    - To get a const reference to load magazine in magazine collection SlTmToMaMagColl, 
      use:\n
      SlTmToMaMag& SlTmToMaMagConf::rConstLoadMag( bool* pIsLoadMagContained = 0 )
    .
  .
 

*/






// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDistOrdMagSpecMagSpecPlace sltmtomadistordmag.h
  \brief special place with reference rDistance() 
         to contained distance (offset) to ordinary magazine
         
  This class holds data of classes:
    - SlTmToMaDistance  referenced by SlTmToMaDistOrdMagSpecMagSpecPlace::rDistance()     
                                  and SlTmToMaDistOrdMagSpecMagSpecPlace::rConstDistance()
    .

  For overview about relations and distances between special magazine (buffer, load) places 
  and ordinary magazines 
  see page \ref pageoverviewmagazineconf.
    
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDistOrdMagSpecMagSpecPlace
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaDistOrdMagSpecMagSpecPlace();

  /// \brief copy constructor
  SlTmToMaDistOrdMagSpecMagSpecPlace(const SlTmToMaDistOrdMagSpecMagSpecPlace& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaDistOrdMagSpecMagSpecPlace();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDistOrdMagSpecMagSpecPlace& operator= (const SlTmToMaDistOrdMagSpecMagSpecPlace& rSourceObj /*!< source object */
                                                );
  
  /// \brief returns reference to special place distance (offset) to ordinary magazine
  SlTmToMaDistance&      rDistance(void);         
  
  
  // ACCESSORS

  /// \brief returns const reference to special place distance (offset) to ordinary magazine
  const SlTmToMaDistance&      rConstDistance(void) const;         
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDistOrdMagSpecMagSpecPlace& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDistOrdMagSpecMagSpecPlace& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistOrdMagSpecMagSpecPlace& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistOrdMagSpecMagSpecPlace& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistOrdMagSpecMagSpecPlace& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistOrdMagSpecMagSpecPlace& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistOrdMagSpecMagSpecPlace& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistOrdMagSpecMagSpecPlace& rData)
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
                     const SlTmToMaDistOrdMagSpecMagSpecPlace& rSourceObj /*!< source object */
                    );

  // MEMBER DATA
  SlTmToMaDistance        m_Distance;       ///< special place distance (offset) to ordinary magazine
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
                                    SlTmToMaDistOrdMagSpecMagSpecPlace& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                              /*!< text data stream target */ 
                                    const SlTmToMaDistOrdMagSpecMagSpecPlace& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                              /*!< binary data stream target */ 
                                    const SlTmToMaDistOrdMagSpecMagSpecPlace& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDistOrdMagSpecMagSpecPlace
// ////////////////////////////////////////////////////////////////////////////





// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaDistOrdMagSpecMagSpecPlaceCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaPlaceNoType, SlTmToMaDistOrdMagSpecMagSpecPlace>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaDistOrdMagSpecMagSpecPlace, accessed by placeNo key of type ::SlTmToMaPlaceNoType
typedef QMap<SlTmToMaPlaceNoType, SlTmToMaDistOrdMagSpecMagSpecPlace>  SlTmToMaDistOrdMagSpecMagSpecPlaceCollMapType;  
                             ///< QMap of SlTmToMaDistOrdMagSpecMagSpecPlace, accessed by placeNo key of type ::SlTmToMaPlaceNoType

// /////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDistOrdMagSpecMagSpecPlaceColl sltmtomadistordmag.h
  \brief  This class belongs to magazine description.
          This class contains all special places of an ordinary mag 
          as ::SlTmToMaDistOrdMagSpecMagSpecPlaceCollMapType map collection 
          of SlTmToMaDistOrdMagSpecMagSpecPlace elements. 
         
  For overview about relations and distances between special magazine (buffer, load) places 
  and ordinary magazines 
  see page \ref pageoverviewmagazineconf.
           
  This class contains such special places of 
  special magazins (buffer magazine and load magazine) which are related to an ordinary magazine 
  in SlTmToMaDistOrdMagColl.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDistOrdMagSpecMagSpecPlaceColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaDistOrdMagSpecMagSpecPlaceColl();

  /// \brief copy constructor
  SlTmToMaDistOrdMagSpecMagSpecPlaceColl(
                    const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rSourceObj /*!< source object */
                                        );
  
  /// \brief destructor
  virtual ~SlTmToMaDistOrdMagSpecMagSpecPlaceColl();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDistOrdMagSpecMagSpecPlaceColl& operator= (
                    const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rSourceObj /*!< source object */
                                                    );
  
  /// \brief returns reference to a contained SlTmToMaDistOrdMagSpecMagSpecPlace place
  /// 
  /// \retval returns a SlTmToMaDistOrdMagSpecMagSpecPlace& reference to the place with key \a placeNo. 
  /// 
  /// If \a pIsPlaceContained is non-null, and key \a placeNo is out of range, 
  /// \a *pIsPlaceContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a placeNo is contained in the map, the returned reference 
  /// refers to contained place  
  /// and if \a pIsPlaceContained is non-null, \a *pIsPlaceContained is set to \c true. 
  ///
  /// To check existence of \a placeNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaDistOrdMagSpecMagSpecPlace& rSpecPlace(
                        const SlTmToMaPlaceNoType placeNo,     /*!< place number */
                        bool* pIsPlaceContained = 0            /*!< is key \a placeNo contained */
                                                );         
  
  /// \brief remove a place addressed by \a placeNo
  ///
  /// Remove SlTmToMaDistOrdMagSpecMagSpecPlace place data of a single place
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
  /// Inserts SlTmToMaDistOrdMagSpecMagSpecPlace a single \a rSpecPlace
  /// adressed by key ::SlTmToMaPlaceNoType \a placeNo.
  /// 
  /// If there is already a place whose key is \a placeNo, 
  /// that place's value is replaced with \a rSpecPlace. 
  /// In this case a reference to replaced place is returned, 
  /// else an reference to the new place is returned. 
  SlTmToMaDistOrdMagSpecMagSpecPlace&  insert(
                          const SlTmToMaPlaceNoType placeNo,                     /*!< key place number */
                          const SlTmToMaDistOrdMagSpecMagSpecPlace& rSpecPlace   /*!< special place */
                                             );         
  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaDistOrdMagSpecMagSpecPlace place
  /// 
  /// \retval returns a const SlTmToMaDistOrdMagSpecMagSpecPlace& reference to the place with key \a placeNo. 
  /// 
  /// If \a pIsPlaceContained is non-null, and key \a placeNo is out of range, 
  /// \a *pIsPlaceContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a placeNo is contained in the map, the returned reference 
  /// refers to contained place  
  /// and if \a pIsPlaceContained is non-null, \a *pIsPlaceContained is set to \c true. 
  ///
  /// To check existence of \a placeNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaDistOrdMagSpecMagSpecPlace& rConstSpecPlace(
                                const SlTmToMaPlaceNoType placeNo,     /*!< place number */ 
                                bool* pIsPlaceContained = 0            /*!< is key \a placeNo contained */
                                                           ) const;         
  
  /// \brief verify existence of key \a placeNo
  /// 
  /// \retval returns \c true if single SlTmToMaDistOrdMagSpecMagSpecPlace place 
  ///         adressed by key ::SlTmToMaPlaceNoType \a placeNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single place, use rSpecPlace() or rConstSpecPlace().
  bool contains(const SlTmToMaPlaceNoType placeNo /*!< place number */
               ) const;         
  
  /// \brief get count of contained places
  /// \retval int number of contained places
  /// 
  /// Get count of contained places.
  int count(void) const;         
  
  /// \brief gets all contained place number placeNo keys as QVector of ::SlTmToMaPlaceNoType
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained place number placeNo keys 
  /// as QVector of ::SlTmToMaPlaceNoType 
  /// in \a rTargetPlaceNoVector.
  int placeNoVector(SlTmToMaPlaceNosValueVectorType& rTargetPlaceNoVector 
                                ///< all contained placeNo keys 
                                ///< as QVector 
                                ///< of ::SlTmToMaPlaceNoType place numbers 
                   ) const;         
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // MANIPULATORS 

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rData)
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
                     const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rSourceObj  /*!< source object */
                    );

  // MEMBER DATA
  SlTmToMaDistOrdMagSpecMagSpecPlaceCollMapType   m_SpecPlaceCollMap; 
                                ///< QMap of SlTmToMaDistOrdMagSpecMagSpecPlace, accessed by key of type ::SlTmToMaPlaceNoType

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
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rData  /*!< import target object */
                                               );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rData  /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rData  /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDistOrdMagSpecMagSpecPlaceColl
// ////////////////////////////////////////////////////////////////////////////







// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaDistOrdMagSpecMagCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaMagNoType, SlTmToMaDistOrdMagSpecMagSpecPlaceColl>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaDistOrdMagSpecMagSpecPlaceColl, accessed by magNo key of type ::SlTmToMaMagNoType
typedef QMap<SlTmToMaMagNoType, SlTmToMaDistOrdMagSpecMagSpecPlaceColl>  SlTmToMaDistOrdMagSpecMagCollMapType;  
                             ///< QMap of SlTmToMaDistOrdMagSpecMagSpecPlaceColl, accessed by magNo key of type ::SlTmToMaMagNoType

// /////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDistOrdMagSpecMagColl sltmtomadistordmag.h
  \brief  This class belongs to magazine description.
          This class contains special magazines (buffer and load) of an ordinary magazine 
          as ::SlTmToMaDistOrdMagSpecMagCollMapType map collection 
          of SlTmToMaDistOrdMagSpecMagSpecPlaceColl for such special magazines 
          special places that are connected to the ordinary magazine. 
         
  For overview about relations and distances between special magazine (buffer, load) places 
  and ordinary magazines 
  see page \ref pageoverviewmagazineconf.
           
  This class contains such special magazins (buffer magazine and load magazine) 
  which have special places that are related to an ordinary magazine 
  in SlTmToMaDistOrdMagColl.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDistOrdMagSpecMagColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaDistOrdMagSpecMagColl();

  /// \brief copy constructor
  SlTmToMaDistOrdMagSpecMagColl(
                    const SlTmToMaDistOrdMagSpecMagColl& rSourceObj /*!< source object */
                               );
  
  /// \brief destructor
  virtual ~SlTmToMaDistOrdMagSpecMagColl();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDistOrdMagSpecMagColl& operator= (
                    const SlTmToMaDistOrdMagSpecMagColl& rSourceObj /*!< source object */
                                           );
  
  /// \brief returns reference to SlTmToMaDistOrdMagSpecMagSpecPlaceColl special place collection 
  ///        of a contained magazine
  /// 
  /// \retval returns a reference to SlTmToMaDistOrdMagSpecMagSpecPlaceColl special place collection 
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
  SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rSpecMag(
                        const SlTmToMaMagNoType magNo,       /*!< magazine number */
                        bool* pIsMagContained = 0            /*!< is key \a magNo contained */
                                                  );         
  
  /// \brief remove a magazine addressed by \a magNo
  ///
  /// Remove SlTmToMaDistOrdMagSpecMagSpecPlaceColl magazine data of a single magazine
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
  
  /// \brief Inserts a magazine, addressed by \a magNo
  /// \retval reference to inserted or replaced magazine.
  ///
  /// Inserts SlTmToMaDistOrdMagSpecMagSpecPlaceColl of a single \a rSpecMag
  /// adressed by key ::SlTmToMaMagNoType \a magNo.
  /// 
  /// If there is already a magazine whose key is \a magNo, 
  /// that magazine's value is replaced with \a rSpecMag. 
  /// In this case a reference to replaced magazine is returned, 
  /// else an reference to the new magazine is returned. 
  SlTmToMaDistOrdMagSpecMagSpecPlaceColl&  insert(
                          const SlTmToMaMagNoType magNo,                           
                                      /*!< key magazine number */
                          const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rSpecMag   
                                      /*!< special magazines data (special magazines special place collection) */
                                                 );         
  
  // ACCESSORS

  /// \brief returns const reference to SlTmToMaDistOrdMagSpecMagSpecPlaceColl special place collection 
  ///        of a contained magazine
  /// 
  /// \retval returns a const reference to SlTmToMaDistOrdMagSpecMagSpecPlaceColl special place collection 
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
  const SlTmToMaDistOrdMagSpecMagSpecPlaceColl& rConstSpecMag(
                                const SlTmToMaMagNoType magNo,     /*!< magazine number */ 
                                bool* pIsMagContained = 0          /*!< is key \a magNo contained */
                                                             ) const;         
  
  /// \brief verify existence of key \a magNo
  /// 
  /// \retval returns \c true if single magazines SlTmToMaDistOrdMagSpecMagSpecPlaceColl data 
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
        const SlTmToMaDistOrdMagSpecMagColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDistOrdMagSpecMagColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistOrdMagSpecMagColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistOrdMagSpecMagColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistOrdMagSpecMagColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // MANIPULATORS 

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistOrdMagSpecMagColl& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistOrdMagSpecMagColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistOrdMagSpecMagColl& rData)
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
                     const SlTmToMaDistOrdMagSpecMagColl& rSourceObj  /*!< source object */
                    );

  // MEMBER DATA
  SlTmToMaDistOrdMagSpecMagCollMapType   m_SpecMagCollMap; 
                                ///< QMap of SlTmToMaDistOrdMagSpecMagSpecPlaceColl, accessed by key of type ::SlTmToMaMagNoType

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
                                    QDataStream& rStream,                   /*!< binary data stream source */ 
                                    SlTmToMaDistOrdMagSpecMagColl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                         /*!< text data stream target */ 
                                    const SlTmToMaDistOrdMagSpecMagColl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                         /*!< binary data stream target */ 
                                    const SlTmToMaDistOrdMagSpecMagColl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDistOrdMagSpecMagColl
// ////////////////////////////////////////////////////////////////////////////







// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaDistOrdMagCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaMagNoType, SlTmToMaDistOrdMagSpecMagColl>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaDistOrdMagSpecMagColl, accessed by magNo key of type ::SlTmToMaMagNoType
typedef QMap<SlTmToMaMagNoType, SlTmToMaDistOrdMagSpecMagColl>  SlTmToMaDistOrdMagCollMapType;  
                             ///< QMap of SlTmToMaDistOrdMagSpecMagColl, accessed by magNo key of type ::SlTmToMaMagNoType

// /////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDistOrdMagColl sltmtomadistordmag.h
  \brief  This class belongs to magazine description.
          This class contains a ::SlTmToMaDistOrdMagCollMapType collection of ordinary magazins 
          and their connection to spezial magazins (bufffer and load) special places. 
          All ordinary magazines are contained, even if they have zero conections to 
          special places.
         
  For overview about relations and distances between special magazine (buffer, load) places 
  and ordinary magazines 
  see page \ref pageoverviewmagazineconf.
           
  This class contains a collection of ordinary magazins and 
  their connections to special places of buffer magazine and load magazine. 
  The data of a single magazine of this collection consists of SlTmToMaDistOrdMagSpecMagColl.
  This is the collection of special magazines (buffer and load) of the single magazine. 
  Each of this special magazines has a collection SlTmToMaDistOrdMagSpecMagSpecPlaceColl 
  of its special places SlTmToMaDistOrdMagSpecMagSpecPlace which are connected 
  to the ordinary magazine and each connection has 
  a reference SlTmToMaDistOrdMagSpecMagSpecPlace::rDistance() 
  to SlTmToMaDistance distance of places.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDistOrdMagColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaDistOrdMagColl();

  /// \brief copy constructor
  SlTmToMaDistOrdMagColl(
                    const SlTmToMaDistOrdMagColl& rSourceObj /*!< source object */
                        );
  
  /// \brief destructor
  virtual ~SlTmToMaDistOrdMagColl();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDistOrdMagColl& operator= (
                    const SlTmToMaDistOrdMagColl& rSourceObj /*!< source object */
                                    );
  
  /// \brief returns reference to SlTmToMaDistOrdMagSpecMagColl special magazine collection 
  ///        of a contained ordinary magazine
  /// 
  /// \retval returns a reference to SlTmToMaDistOrdMagSpecMagColl special magazine collection 
  /// of the ordinary magazine with key \a magNo. 
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
  SlTmToMaDistOrdMagSpecMagColl& rOrdMag(
                        const SlTmToMaMagNoType magNo,       /*!< magazine number */
                        bool* pIsMagContained = 0            /*!< is key \a magNo contained */
                                        );         
  
  /// \brief remove a magazine addressed by \a magNo
  ///
  /// Remove SlTmToMaDistOrdMagSpecMagColl magazine data of a single magazine
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
  
  /// \brief Inserts a magazine (more precisely: it's special magazine collection data), 
  ///        addressed by \a magNo
  /// \retval reference to inserted or replaced magazine.
  ///
  /// Inserts SlTmToMaDistOrdMagSpecMagColl of a single \a magazine
  /// adressed by key ::SlTmToMaMagNoType \a magNo.
  /// 
  /// If there is already a magazine whose key is \a magNo, 
  /// that magazine's value is replaced with \a magazine. 
  /// In this case a reference to replaced magazine is returned, 
  /// else an reference to the new magazine is returned. 
  SlTmToMaDistOrdMagSpecMagColl&  insert(
                          const SlTmToMaMagNoType magNo,                           
                                      /*!< key magazine number */
                          const SlTmToMaDistOrdMagSpecMagColl& rOrdMag   
                                      /*!< ordinary magazines data (ordinary magazines special magazine collection) */
                                        );         
  
  // ACCESSORS

  /// \brief returns const reference to SlTmToMaDistOrdMagSpecMagColl special magazine collection 
  ///        of a contained ordinary magazine
  /// 
  /// \retval returns a const reference to SlTmToMaDistOrdMagSpecMagColl special magazine collection 
  /// of the ordinary magazine with key \a magNo. 
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
  const SlTmToMaDistOrdMagSpecMagColl& rConstOrdMag(
                                const SlTmToMaMagNoType magNo,     /*!< magazine number */ 
                                bool* pIsMagContained = 0          /*!< is key \a magNo contained */
                                                   ) const;         
  
  /// \brief verify existence of key \a magNo
  /// 
  /// \retval returns \c true if single magazines SlTmToMaDistOrdMagSpecMagColl data 
  ///         adressed by key ::SlTmToMaMagNoType \a magNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single magazines data, use rOrdMag() or rConstOrdMag().
  bool contains(const SlTmToMaMagNoType magNo /*!< magazine number */
               ) const;         
  
  /// \brief get count of contained magazines
  /// \retval int number of contained magazines
  /// 
  /// Get count of contained magazines.
  int count(void) const;         
  
  /// \brief gets magazine number magNo keys as QVector of ::SlTmToMaMagNoType 
  ///        of all contained ordinary magazines
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get magazine number magNo keys 
  /// as QVector of ::SlTmToMaMagNoType 
  /// in \a rTargetMagNoVector of all contained ordinary magazines.
  int magNoVector(SlTmToMaMagNosValueVectorType& rTargetMagNoVector 
                                /*!< all contained magNo keys 
                                     as QVector 
                                     of ::SlTmToMaMagNoType magazine numbers 
                                */
                 ) const;         
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDistOrdMagColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDistOrdMagColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistOrdMagColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistOrdMagColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistOrdMagColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistOrdMagColl& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistOrdMagColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistOrdMagColl& rData)
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
                     const SlTmToMaDistOrdMagColl& rSourceObj  /*!< source object */
                    );

  // MEMBER DATA
  SlTmToMaDistOrdMagCollMapType   m_OrdMagCollMap; 
                                ///< QMap of SlTmToMaDistOrdMagSpecMagColl, accessed by key of type ::SlTmToMaMagNoType
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
                                    QDataStream& rStream,            /*!< binary data stream source */ 
                                    SlTmToMaDistOrdMagColl& rData    /*!< import target object */
                                               );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                  /*!< text data stream target */ 
                                    const SlTmToMaDistOrdMagColl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                  /*!< binary data stream target */ 
                                    const SlTmToMaDistOrdMagColl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDistOrdMagColl
// ////////////////////////////////////////////////////////////////////////////




#endif // !defined(SL_TM_TOMA_DIST_ORD_MAG_H)
