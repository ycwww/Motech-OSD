///////////////////////////////////////////////////////////////////////////////
/*! \file   slpaprotectionzones.h
 *  \author Michael Hoseus
 *  \date   02.12.2005
 *  \brief  Definition file for class SlPaProtectionZones
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_PA_PROTECTION_ZONES_H_INCLUDED
#define SL_PA_PROTECTION_ZONES_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"


/*!\enum protAreaRelationEnum
 *
 *  Defines the relating to tool or workpiece of protection area
 */
enum protAreaRelationEnum
{
  REL_TO_WORKPIECE = 0,
  REL_TO_TOOL = 3,
  REL_TO_INVALID
};

/*!\enum protAreaPlaneEnum
 *
 *  Defines the possible planes for protection area
 */
enum protAreaPlaneEnum
{
  PLANE_G17 = 0,
  PLANE_G18,
  PLANE_G19,
  MAX_PLANES,
  PLANE_INVALID
};

/*!\enum protAreaCoordAxisEnum
 *
 *  Defines the possible planes for protection area
 */
enum protAreaCoordAxisEnum
{
  ABSCISSA = 0,
  ORDINATE,
  APPLICATE
};

/*!\enum protAreaCoordAxisEnum
 *
 *  Defines the possible planes for protection area
 */
enum protAreaContourEnum
{
  CONT_ABSCISSA = 0,
  CENT_ABSCISSA,
  CONT_ORDINATE,
  CENT_ORDINATE,
  CONT_TYPE
};

/*!\enum varSectorEnum
 *
 *  Defines the possible sector for access to variables
 */
enum varSectorEnum
{
  VAR_NCK = 0,
  VAR_CHANNEL
};

/*!\enum limitValueEnum
 *
 *  Defines the possible limit values
 */
enum limitValueEnum
{
  LIM_MAX = 0,
  LIM_MIN
};

typedef struct
{
  double                contAbs[10]; 
  double                contOrd[10];
  double                centAbs[10]; 
  double                centOrd[10];
  unsigned int          contTyp[10];
  unsigned int          numElements;          // number of contour elements
  protAreaRelationEnum  relation;             // relating to tool or workpiece
  protAreaPlaneEnum     plane;                // plane G17/G18/G19
} protAreaType;

class SlPaProtectionZonesPrivate;

/*!
 *  \class  SlPaProtectionZones
 *  \brief  Interface service adapter of active work offsets
 *
 *   contains all data of all protection zones.
 */
class SL_MA_LOGIC_EXPORT SlPaProtectionZones : public SlMaFormLogicBase
{
  Q_OBJECT;
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(protAreaPlaneEnum)
	Q_ENUMS(protAreaContourEnum)
	Q_ENUMS(varSectorEnum)

public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*!
   *  \brief  Constructor of SlPaProtectionZones
   *
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   */
  SlPaProtectionZones (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*!
   *  \brief  Destructor of SlPaProtectionZones
   */
  virtual ~SlPaProtectionZones ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  // Set new plane
  long setNewPlane (protAreaPlaneEnum newPlane);
  // Set sector for access to variables
  long setVarSector (varSectorEnum sector);

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  QString channelName(void)  const;                 //!< channel name
  unsigned int numChannels (void) const;            //!< number of available channels
  unsigned int numGeoAxes (void) const;             //!< Provides the number of defined geometric axes; necessary ??? use numPlanes()
  unsigned char numPlanes (void) const;             //!< Provides the number of planes
  unsigned int numProtArea (void) const;            //!< Provides maximum number of protection areas
  unsigned int numContourInProtArea (void) const;   //!< Provides maximum number of contours per protection areas

  /*! get methods, available after SL_MA_START_LOGIC*/
  protAreaPlaneEnum actualPlane (void) const;       //!< Provides the actual plane
  QString ordinateName (void) const;                //!< Provides the name of the ordinate (first axis)
  QString abscissaName (void) const;                //!< Provides the name of the abscissa (second axis)
  double ordinateValue (limitValueEnum) const;      //!< Provides the limit of the ordinate (first axis)
  double abscissaValue (limitValueEnum) const;      //!< Provides the limit of the abscissa (second axis)
  unsigned int numContourElements (unsigned int) const;         //!< Provides number of contour elements
  protAreaRelationEnum protAreaRelation (unsigned int) const;   //!< Provides the relating to tool or workpiece of protection area
  protAreaPlaneEnum protAreaPlane (unsigned int) const;         //!< Provides the plane of protection area
  double contourElement (unsigned int, unsigned int, protAreaContourEnum) const;   //!< Provides the requested contour element
  unsigned int contourType (unsigned int, unsigned int) const;  //!< Provides the type of the requested contour element

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void protectionZonesSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultProtectionZones);  /*!< Slot: protectionZonesSlot */

signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  void protAreaCounterChanged (unsigned int);       /*!< connectState changed */

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlPaProtectionZonesPrivate* m_pData;        // private data-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlPaProtectionZones (const SlPaProtectionZones& rCopy);
  /*! assignment operator not allowed */
  SlPaProtectionZones& operator=(const SlPaProtectionZones& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummyProtectionZones (void);
  bool readCoordSysData (void);
  bool readProtArea (protAreaType*, unsigned int, QString);
  void adviceProtectionZones (void);
  void unadviceProtectionZones (void);

  void initStaticValues (void);
  void initDummyValues (void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_PA_PROTECTION_ZONES_H_INCLUDED
