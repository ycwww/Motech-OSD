///////////////////////////////////////////////////////////////////////////////
/*! \file   slstepswiveldatadef.h
 *  \author Robert Kindermann
 *  \date   23.11.2016
 *  \brief  Definition of the class SlStepKinematicTrafoData und SlStepToolCarrierData
 *
 *  This file is part of the HMI Solutionline StepEditor.
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_STEP_SWIVEL_DATA_DEF_H
#define SL_STEP_SWIVEL_DATA_DEF_H

#include <slsteplogicexports.h>
#include <QtCore/QString>


/*! \class SlStepSwivelsInfo
 *
 *  This clas contains swivel names, swivel numbers and swivel types
 */
class SL_STEP_LOGIC_EXPORT SlStepSwivelsInfo
{
public:

   /*! \fn SlStepSwivelsInfo();
    *
    *  Default constructor
    */
   SlStepSwivelsInfo ();
   
   /*! \fn ~SlStepSwivelsInfo()
    *
    *  Destructor
    */
   virtual ~SlStepSwivelsInfo ();

   /////////////////////////////////////////////////////////////////////////////////////////////
   // Public Methods
   /////////////////////////////////////////////////////////////////////////////////////////////



   /////////////////////////////////////////////////////////////////////////////////////////////
   // Public Members
   /////////////////////////////////////////////////////////////////////////////////////////////

   int            m_toUnitNo;       // number of tool unit
   int            m_swivelNumber;   // number of the swivel data record
   int            m_property;       // swivel properties
   QString        m_swivelName;     // name of the swivel data record
   QString        m_trafoType;      // trafo type

}; // <-- class SlStepSwivelsInfo


/*! \class SlStepKinematicTrafoData
 *
 *  This class includes all data for the kinematic data record
 */
class SL_STEP_LOGIC_EXPORT SlStepKinematicTrafoData
{

public:

   /*! \fn SlStepKinematicTrafoData();
    *
    *  Default constructor
    */
   SlStepKinematicTrafoData();

   /*! \fn SlStepKinematicTrafoData (const QString& rTrafoType);
    *
    *  constructor with trafo type (e.g. TRAORI_STAT, ...)
    */
   SlStepKinematicTrafoData (const QString& rTrafoType);

   /*! \fn ~SlStepKinematicTrafoData()
    *
    *  Destructor
    */
   virtual ~SlStepKinematicTrafoData();

  // --------------------------------------------------------------------------
  //    MEMBERS OF KINEMATIC-TRANSFORATION-DATA-RECORDS   
  // --------------------------------------------------------------------------
   
   QString     m_swivelName;           //!< name of swivel data record
   QString     m_trafoType;            //!< transformation type
   QString     m_lastToolElemName;     //!< name of the last tool kinematic chain element
   QString     m_lastPartElemName;     //!< name of the last part kinematic chain element
   QString     m_firstToolElemName;    //!< name of the first tool kinematic chain element
   QString     m_firstPartElemName;    //!< name of the first part kinematic chain element
   QString     m_correctEleTool1;      //!< 1. correction element for measurment tool
   QString     m_correctEleTool2;      //!< 2. correction element for measurment tool
   QString     m_correctEleTool3;      //!< 3. correction element for measurment tool
   QString     m_correctEleTool4;      //!< 4. correction element for measurment tool
   QString     m_correctElePart1;      //!< 1. correction element for measurment part
   QString     m_correctElePart2;      //!< 2. correction element for measurment part
   QString     m_correctElePart3;      //!< 3. correction element for measurment part
   QString     m_correctElePart4;      //!< 4. correction element for measurment part
   QString     m_kinElem1RotAxis;      //!< name of kinematic element for the first rotation axis
   QString     m_kinElem2RotAxis;      //!< name of kinematic element for the second rotation axis
   QString     m_kinElem3RotAxis;      //!< name of kinematic element for the third rotation axis
   QString     m_closingToolElement;   //!< closing tool element
   QString     m_closingPartElement;   //!< closing part element
   QString     m_kinElem1LinAxis;      //!< name of first geometrie axis
   QString     m_kinElem2LinAxis;      //!< name of second geometrie axis
   QString     m_kinElem3LinAxis;      //!< name of third geometrie axis
   
   QString     m_toolRefElement;       //!< tool reference point
   double      m_manualAxPosition1;    //!< Position of a manual rotation axis 1
   double      m_manualAxPosition2;    //!< Position of a manual rotation axis 2
   double      m_manualAxPosition3;    //!< Position of a manual rotation axis 3

   double      m_1retractionPos;       //!< first positon for retraction position
   double      m_2retractionPos;       //!< second positon for retraction position 
   double      m_3retractionPos;       //!< third positon for retraction position

   uint        m_swivelProperty;       //!< swivel properties ($NT_IDENT[n])
   uint        m_machineProperty;      //!< machine properties ($NT_CNTRL[n])
   int         m_rotaryAxisCount0;     //!< number of rotary axis in the tool chain
   int         m_rotaryAxisCount1;     //!< number of rotary axis in the part chain

   uint        m_rotAxisOffSetFromNpv; //!< Round axis offset take from the zero offset
   double      m_toleranceToolOrient;  //!< End angle tolerance for tool orientation
   double      m_1toolOrient;          //!< first vector for tool orientation
   double      m_2toolOrient;          //!< second vector for tool orientation
   double      m_3toolOrient;          //!< third vector for tool orientation
   double      m_1toolOrientNormal;    //!< first normalen vector for tool orientation
   double      m_2toolOrientNormal;    //!< second normalen vector for tool orientation
   double      m_3toolOrientNormal;    //!< third normalen vector for tool orientation
   bool        m_ignoreToolOrient;     //!< orientation from active tool or from tool orientation 

   int         m_alternativeCall;      //!< instead TRAFO_ON(TRAFO-NAME), TRAORI(1)
   double      m_tolerancePoleOrient;  //!< End angle tolerance for interpolation by pole
   bool        m_includesToolLength;   //!< Tool length in the transformation TRAANK_K
   int         m_workAreaOfTrafoAxis;  //!< Work area of transformation axis complete. Only positive Only negative TRANSMI_K
   int         m_wcsJumpByTrafoSelect; //!< Avoid WCS jump during transformation selection TRANSMI_K + TRACYL_K
   double      m_baseOffsetTool1;      //!< Base offset in X of the tool zero point TRANSMI_K + TRACYL_K
   double      m_baseOffsetTool2;      //!< Base offset in Y of the tool zero point TRANSMI_K + TRACYL_K
   double      m_baseOffsetTool3;      //!< Base offset in Z of the tool zero point TRANSMI_K + TRACYL_K
   // ab NCK 133
   double      m_rotAxis1Offset;       //!< offset from the first round axis
   double      m_rotAxis2Offset;       //!< offset from the second round axis
   double      m_rotAxis3Offset;       //!< offset from the third round axis

  // --------------------------------------------------------------------------
  //    PUBLIC METHODS
  // --------------------------------------------------------------------------

};  // <-- class SlStepKinematicTrafoData


/*! \class SlStepToolCarrierData
 *
 *  This class includes all data for the kinematic data record
 */
class SL_STEP_LOGIC_EXPORT SlStepToolCarrierData
{

public:

   /*! \fn SlStepToolCarrierData();
    *
    *  Default constructor
    */
   SlStepToolCarrierData();

   /*! \fn SlStepToolCarrierData (const QString& rTrafoType);
    *
    *  constructor with trafo type (e.g. SL_SWIVEL_TOOL_CARRIER_CHAIN, ...)
    */
   SlStepToolCarrierData (const QString& rTrafoType);

   /*! \fn SlStepToolCarrierData (bool withKinChain);
    *
    *  constructor with or without kinematic chain
    */
   SlStepToolCarrierData (bool withKinChain);
   

   /*! \fn ~SlStepToolCarrierData()
    *
    *  Destructor
    */
   virtual ~SlStepToolCarrierData();

  // --------------------------------------------------------------------------
  //    MEMBERS OF TOOLCARRIER-DATA-RECORDS   
  // --------------------------------------------------------------------------

   QString  m_swivelLocation;       //!< where is the swivel axis 
   QString  m_tcName;               //!< name of the tool carrier
   QString  m_1RotaryAxName;        //!< name of the first rotary axis
   QString  m_2RotaryAxName;        //!< name of the second rotary axis
   int      m_swivelProperty;       //!< swivel properties
   double   m_vector1x;             //!< direction vector of the first rotary axis around x
   double   m_vector1y;             //!< direction vector of the first rotary axis around y
   double   m_vector1z;             //!< direction vector of the first rotary axis around z
   double   m_vector2x;             //!< direction vector of the second rotary axis around x
   double   m_vector2y;             //!< direction vector of the second rotary axis around y
   double   m_vector2z;             //!< direction vector of the second rotary axis around z
   double   m_offsetLength3x;       //!< offset length 3 in x direction
   double   m_offsetLength3z;       //!< offset length 3 in z direction
   double   m_offsetVector1;        //!< offset of the 1. rotation axis in degree
   double   m_offsetVector2;        //!< offset of the 2. rotation axis in degree
   double   m_alpha1Min;            //!< minimal position of the 1. rotation axis
   double   m_alpha2Min;            //!< maximal position of the 2. rotation axis
   double   m_alpha1Max;            //!< minimal position of the 1. rotation axis
   double   m_alpha2Max;            //!< maximal position of the 2. rotation axis
   // die fogenden Daten sind nicht in m_cacheDataRecord enhalten
   int      m_tcWithKinChain;       //!< tool carrier with or without kinematic chain
   double   m_offsetLength1x;       //!< offset length 1 in x direction
   double   m_offsetLength1y;       //!< offset length 1 in y direction
   double   m_offsetLength1z;       //!< offset length 1 in z direction
   double   m_offsetLength1FineX;   //!< fine adjustment from length 1 in x direction
   double   m_offsetLength1FineY;   //!< fine adjustment from length 1 in y direction
   double   m_offsetLength1FineZ;   //!< fine adjustment from length 1 in z direction
   double   m_offsetRot1Fine;       //!< fine adjustment of rotation axis 1
   double   m_offsetHirthRot1;      //!< offset of the hirth joint from the rotation axis 1 
   double   m_inkHirthRot1;         //!< raster of the teeth from the hirth joint of the rotation axis 1
   double   m_offsetLength2x;       //!< offset length 2 in x direction
   double   m_offsetLength2y;       //!< offset length 2 in y direction
   double   m_offsetLength2z;       //!< offset length 2 in z direction
   double   m_offsetLength2FineX;   //!< fine adjustment from length 2 in x direction
   double   m_offsetLength2FineY;   //!< fine adjustment from length 2 in y direction
   double   m_offsetLength2FineZ;   //!< fine adjustment from length 2 in z direction
   double   m_offsetLength3y;       //!< offset length 3 in y direction    
   double   m_offsetLength3FineX;   //!< fine adjustment from length 3 in x direction
   double   m_offsetLength3FineY;   //!< fine adjustment from length 3 in y direction
   double   m_offsetLength3FineZ;   //!< fine adjustment from length 3 in z direction
   double   m_offsetRot2Fine;       //!< fine adjustment of the rotation axis 2
   double   m_offsetHirthRot2;      //!< offset of the hirth joint from the rotation axis 2
   double   m_inkHirthRot2;         //!< raster of the teeth from the hirth joint of the rotation axis 2
   double   m_offsetLength4x;       //!< offset length 4 in x direction    
   double   m_offsetLength4y;       //!< offset length 4 in y direction    
   double   m_offsetLength4z;       //!< offset length 4 in z direction    
   double   m_offsetLength4FineX;   //!< fine adjustment from length 4 in x direction
   double   m_offsetLength4FineY;   //!< fine adjustment from length 4 in y direction
   double   m_offsetLength4FineZ;   //!< fine adjustment from length 4 in z direction
   double   m_retractPosX;          //!< retraction position in X
   double   m_retractPosY;          //!< retraction position in Y
   double   m_retractPosZ;          //!< retraction position in Z
   // Daten für den ToolCarrier mit Kette
   QString  m_startToolElemName;    //!< name of the beginning tool element in the kinematic chain  
   QString  m_lastToolElemName;     //!< name of the end tool element in the kinematic chain  
   QString  m_startPartElemName;    //!< name of the beginning part element in the kinematic chain  
   QString  m_lastPartElemName;     //!< name of the end part element in the kinematic chain
   QString  m_corrElem1;            //!< name of the first correction element in the kinematic chain
   QString  m_corrElem2;            //!< name of the second correction element in the kinematic chain
   QString  m_corrElem3;            //!< name of the third correction element in the kinematic chain
   QString  m_corrElem4;            //!< name of the fourth correction element in the kinematic chain
   QString  m_kinElem1RotAxis;      //!< name of the kin. chain element with first rotary axis for tc kinematic
   QString  m_kinElem2RotAxis;      //!< name of the kin, chain element with second rotary axis for tc kinematic

};  // <-- class SlStepToolCarrierData

#endif // SL_STEP_SWIVEL_DATA_DEF_H
