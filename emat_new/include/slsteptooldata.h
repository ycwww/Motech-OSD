///////////////////////////////////////////////////////////////////////////////
/*! \file   slsteptooldata.h
 *  \author Norbert Stapper
 *  \date   22.10.2008
 *  \brief  Class definition file for class SlStepToolData
 *
 *  This file is part of the HMI Solutionline StepEditor.
 *
 * (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_STEP_TOOL_DATA_H
#define SL_STEP_TOOL_DATA_H

// system
#include <QtCore/QObject>
// solutionline
#include "slsteplogicexports.h"
#include "slstepncconfig.h"
#include "slstepglobal.h"
#include "slsteptemplates.h"
#include "sltmtoolmanadata.h"
#include "sltmutil.h"

class SlStepEdgeDataRecordPrivate;
class SlTmMassData2ToolMagListChangedData;
class SlTmMassData2ToolMagListElData;
class SlTmToMaEdge;
class SlTmToMaContainer;

/*!
 *  \struct SlStepEdgeDataInitData
 *
 *  Structure of datas used to initialise a edge data record.
 */
struct SL_STEP_LOGIC_EXPORT SlStepEdgeDataInitData
{
   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC DATA MEMBERS FOR DIRECT ACCESS
   ///////////////////////////////////////////////////////////////////////////

   int               nChannel;               //!< channel
   SlStepValue       scaleSystem;            //!< the scale system of programmhead
   SlStepValue       scalingX;               //!< the scaling factor of the first axis
   SlStepValue       scalingY;               //!< the scaling factor of the second axis
   SlStepValue       scalingZ;               //!< the scaling factor of the third axis
   SlStepPlaneToggle activePlane;            //!< the active plane
   SlStepValue       swivelBeta;             //!< the swivel value beta
   SlStepValue       swivelGamma;            //!< the swivel value gamma
   bool              bAdaptToSubSpindle;     //!< flag, if machining at counter spindle, adapt tool data to counter spindle
   bool              bIsShopTurn;            //!< flag, if machining at shopturn


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC CONSTRUCTORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn SlStepEdgeDataInitData ()
    *
    *  Default construtor. Creates an uninitialised structure.
    */
   SlStepEdgeDataInitData ();

   /*!
    *  \fn SlStepEdgeDataInitData (int achannel,
                                   const SlStepValue& rScaleSystem,
                                   const SlStepValue& rScalingX,
                                   const SlStepValue& rScalingY,
                                   const SlStepValue& rScalingZ,
                                   const SlStepPlaneToggle& rActivePlane,
                                   const SlStepValue& rSwivelBeta,
                                   const SlStepValue& rSwivelGamma,
                                   bool aadaptToSubSpindle)
   *
   * Contructor. Provided to intialise all data members at once.
   */
   SlStepEdgeDataInitData (int achannel,
                           const SlStepValue& rScaleSystem,
                           const SlStepValue& rScalingX,
                           const SlStepValue& rScalingY,
                           const SlStepValue& rScalingZ,
                           const SlStepPlaneToggle& rActivePlane,
                           const SlStepValue& rSwivelBeta,
                           const SlStepValue& rSwivelGamma,
                           bool aadaptToSubSpindle,
                           bool bIsShopTurn);

}; // <-- struct SlStepEdgeDataInitData

   enum SlStepToolIdentifierMode
   {
      SL_STEP_TOOL_IDENT_IDENT = 0,        /*!< use identifier for tool identification */
      SL_STEP_TOOL_IDENT_PLACE,            /*!< use place number for tool identification */
   };


/*!\class SlStepEdgeDataRecord
 *
 *  class tool edge data in SlStepEditor 
 */
class SL_STEP_LOGIC_EXPORT SlStepEdgeDataRecord
{

public:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC TYPEDEFS AND ENUMS
   ///////////////////////////////////////////////////////////////////////////

  /*! \enum SlStepEdgeAdaptMirrorToolMode
   *   Enum for the typ of tool 
   */
   enum SlStepEdgeAdaptMirrorToolMode
   {
      SL_STEP_ADAPT_TOOL_CUT_EDGE_POS = 0,    /*!< cut edge pos */
      SL_STEP_ADAPT_TOOL_CUT_DIRECTION,       /*!< tool direction */
   };

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   /*! \fn SlStepEdgeDataRecord(void)
    *
    *  Constructor
    */
   SlStepEdgeDataRecord(void);

   /*! \fn SlStepEdgeDataRecord(const SlTmToMaEdge& rConstEdge, unsigned int nDiameterOrRadiusIdentifier, bool bAdaptTransDataExist)
    *
    *  Constructor
    *  \param nDiameterOrRadiusIdentifier:   identifier for diameter or radius
    *  \param bAdaptTransDataExist:          magazineplace adapter and transformation data exist
    *
    *  scource is edge data class from toolmanagement service adapter
    */
   SlStepEdgeDataRecord(const SlTmToMaEdge& rConstEdge, unsigned int nDiameterOrRadiusIdentifier, bool bAdaptTransDataExist);

   /*! 
    *  \fn SlStepEdgeDataRecord (const SlStepEdgeDataRecord& rOther)
    *
    *  \param rOther       the other object
    *
    *  This class has pointer members, so it has to implement its own copy
    *  contructor.
    */
   SlStepEdgeDataRecord(const SlStepEdgeDataRecord& rOther);

   /*! \fn  ~SlStepToolData (void)
    *
    *  protected creator used in singleton classes
    */
   ~SlStepEdgeDataRecord(void);

   ///////////////////////////////////////////////////////////////////////////
   // METHODS
   ///////////////////////////////////////////////////////////////////////////
   /*! \fn bool isValid(void)  const
    *  access to valid state
    */
   bool isValid(void) const;

   /*! \fn bool isToolValid(void) const
    *  access to tool valid state
    */
   bool isToolValid(void) const;

   /*! \fn void setIsToolValid(bool bIsToolValid)
    *
    *  \param bIsToolValid: tool data activ
    *  
    *  sets tool data activ to member of tool edge data
    */
   void setIsToolValid(bool bIsToolValid);

   /*! \fn bool isToolPlaceValid(void) const
    *  access to tool place valid state
    */
   bool isToolPlaceValid(void) const;

   /*! \fn void setIsToolPlaceValid(bool bIsToolPlaceValid)
    *
    *  \param bIsToolPlaceValid: tool place valid
    *  
    *  sets tool place data valid to member of tool edge data
    */
   void setIsToolPlaceValid(bool bIsToolPlaceValid);


   /*! \fn bool isMultiToolLocationValid(void) const
    *  access to multitool location valid state
    */
   bool isMultiToolLocationValid(void) const;

   /*! \fn void setIsMultiToolLocationValid(bool bIsMultiToolLocationValid)
    *
    *  \param bIsMultiToolLocationValid: multitool location valid
    *  
    *  sets multitool location data valid to member of tool edge data
    */
   void setIsMultiToolLocationValid(bool bIsMultiToolLocationValid);

   /*! \fn int countMultiToolLocations(void) const
    *  access to count of multitool locations
    */
   int countMultiToolLocations(void) const;

   /*! \fn void setCountMultiToolLocations(int nCountMultiToolLocations)
    *
    *  \param nCountMultiToolLocations: count of multitool locations
    *  
    *  sets count of multitool locations to member of tool edge data
    */
   void setCountMultiToolLocations(int nCountMultiToolLocations);

   /*! \fn double toolType(void) const
    *  access to tooltype
    */
   double toolType(void) const;

   /*! \fn double toolRadius(bool bAdaptToProgramScaleFactor = true)
    *
    *  \param bAdaptToProgramScaleFactor   adapt toolRadius to current program scale factor.
    *
    *  access to toolradius
    *  If bAdaptToProgramScaleFactor is false, the function  returns the real tool radius without adaption to program scale factor.
    */
   double toolRadius(bool bAdaptToProgramScaleFactor = true) const;

   /*! \fn double toolRadiusInBasicSystem(void) const
    *  access to toolradius in Basissystem
    */
   double toolRadiusInBasicSystem(void) const;

   /*! \fn double edgeRadius(void) const
    *  access to edge radius
    */
   double edgeRadius(void) const;

   /*! \fn double drillingRadius(void) const
    *  access to drilling radius
    */
   double drillingRadius(void) const;

   /*! \fn double outsideRadius(void) const
    *  access to outside radius
    */
   double outsideRadius(void) const;

   /*! \fn double toolAngle(void) const
    *  access to tool angle
    */
   double toolAngle(void) const;

   /*! \fn double holderAngle(void) const
    *  access to holder angle
    */
   double holderAngle(void) const;

   /*! \fn double angleOfConicalTools(void) const
    *  access to angle of conical tools
    */
   double angleOfConicalTools(void) const;

   /*! \fn double teethCount(void) const
    *  access to number of teeth of a tool
    */
   double teethCount(void) const;

   /*! \fn double noseAngle(void) const
    *  access to nose angle of a tool
    */
   double noseAngle(void) const;

   /*! \fn double clearanceAngle(void) const
    *  access to relief angle of a tool
    */
   double clearanceAngle(void) const;

   /*! \fn double spindleDirection(void) const
    *  access to spindle direction
    */
   double spindleDirection(void) const;

   /*! \fn double length1(void) const
    *  access to length1
    */
    double length1(void) const;

   /*! \fn double length2(void) const
    *  access to length2
    */
    double length2(void) const;

   /*! \fn double length3(void) const
    *  access to length3
    */
    double length3(void) const;

   /*! \fn double cuttDirection(void) const
    *  access to cutting direction
    */
   double cuttDirection(void) const;

   /*! \fn double cuttEdgePos(void) const
    *  access to cutting position of tooledge
    */
   double cuttEdgePos(void) const;

   /*! \fn double plateLength(void) const
    *  access to platelength
    */
   double plateLength(void) const;

   /*! \fn double toolWidth(void) const
    *  access to toolwidth
    */
   double toolWidth(void) const;

   /*! \fn double toolPitch(void) const
    *  access to toolpitch
    */
   double toolPitch(void) const;

   /*! \fn int optDNo(void) const
    *  access to optional D number
    */
   int optDNo(void) const;

   /*! \fn void setBasicLengthSecondRevolver(double dBasicLengthSecondRevolver);
    *
    *  \param dBasicLengthSecondRevolver: length of basic second revolver
    *
    *  sets active length of basic second revolver to member of tool edge data
    */
   void setBasicLengthSecondRevolver(double dBasicLengthSecondRevolver);

   /*! \fn void setBasicLengthUnit(SlTmUtil::StoreLengthUnitValueEnum nBasicLengthUnit);
    *
    *  \param nBasicLengthUnit: active system von NC
    *
    *  sets active system von NC to member of tool edge data
    */
   void setBasicLengthUnit(SlTmUtil::StoreLengthUnitValueEnum nBasicLengthUnit);

   /*! \fn void setProgScaleSystem(SlStepValue vScale)
    *
    *  \param vScale: active of programm system
    *  
    *  sets the scaling system to member of tool edge data
    */
   void setProgScaleSystem(SlStepValue vScale);

   /*! \fn void setScalingX(SlStepValue vScaleX)
    *
    *  \param vScaleX: scale in X
    *  
    *  sets scaling in X axis to member of tool edge data
    */
   void setScalingX(SlStepValue vScaleX);

   /*! \fn void setScalingY(SlStepValue vScaleY)
    *
    *  \param vScaleY: scale in Y
    *  
    *  sets scaling in Y axis to member of tool edge data
    */
   void setScalingY(SlStepValue vScaleY);

   /*! \fn void setScalingZ(SlStepValue vScaleZ)
    *
    *  \param vScaleZ: scale in Z
    *  
    *  sets scaling in Z axis to member of tool edge data
    */
   void setScalingZ(SlStepValue vScaleZ);

   /*! \fn void setActivePlane(SlStepPlaneToggle nAtivePlane);
    *
    *  \param nAtivePlane: active Plane
    *  
    *  sets activ plane to member of tool edge data
    */
   void setActivePlane(SlStepPlaneToggle nAtivePlane);

   /*! \fn void setAdaptToSubSpindle(bool bAdaptToSubSpindle)
    *
    *  \param bAdaptToSubSpindle: true in case of machining at subspindle, adapt tool data to subspindle, otherwise false
    *  
    *  sets adapt to subspindle to member of tool edge data
    */
   void setAdaptToSubSpindle(bool bAdaptToSubSpindle);

   /*! \fn double calcToolAngleNoteBeta(double dSwivelBeta,
    *                                   double dSwivelGamma,
    *                                   bool bTurningTool,
    *                                   double dIntIncrPerDeg
    *                                   int nChannel)
    *
    *  \param dSwivelBeta:           swivel value of Beta
    *  \param dSwivelGamma:          swivel value of Gamma
    *  \param bTurningTool:          true, if the tool is a turning tool, otherwise false
    *  \param dIntIncrPerDeg:        Rechenfeinheit Winkel
    *  \param nChannel:              current channel
    *  
    *  This function calculates the values for 
    *     cuttingEdge,
    *     cuttingDirection,
    *     holderAngle and 
    *     clearanceAngle 
    *  depending on angle beta and gamma.
    */
   void calcToolAngleNoteBeta(double dSwivelBeta,
                              double dSwivelGamma,
                              bool bTurningTool,
                              double dIntIncrPerDeg,
                              int nChannel);

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! 
    *  \fn SlStepEdgeDataRecord& operator= (const SlStepEdgeDataRecord& rOther)
    *
    *  \param rOther       the other object
    *
    *  This class has pointer members, so it has to implement its own 
    *  assignment operator.
    */
   SlStepEdgeDataRecord& operator= (const SlStepEdgeDataRecord& rOther);

   /*! \fn bool operator==(const SlStepEdgeDataRecord& rEdgeDataRecord) const
    *  \retval bool      Same cells or not
    *
    *  Returns true if \a rEdgeDataRecord includes the same data
    *  otherwise returns false.
    */
   bool operator==(const SlStepEdgeDataRecord& rEdgeDataRecord) const;

   /*! \fn bool operator!=(const SlStepEdgeDataRecord& rEdgeDataRecord) const
    *  \retval bool      Same cells or not
    *
    *  Returns false if \a rEdgeDataRecord includes the same data
    *  otherwise returns true.
    */
   bool operator!=(const SlStepEdgeDataRecord& rEdgeDataRecord) const;

private:

   struct SlStepEdgeDataVector
   {
      SlStepEdgeDataVector()
      {
         for (int i = 0 ; i < 3 ; i++)
         {
            coordinate[i] = 0.0;
         }
      }

      double coordinate[3];
   };

   struct SlStepEdgeDataMatrix
   {
      SlStepEdgeDataMatrix()
      {
         for (int i = 0 ; i < 3 ; i++)
         {
            for (int j = 0 ; j < 3 ; j++)
            {
               row[i].coordinate[j] = 0.0;
            }
         }
      }

      SlStepEdgeDataVector row[3];
   };

   ///////////////////////////////////////////////////////////////////////////
   // private methods
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn void adaptToScalingSystemInch(double& rdValue) const
    *
    *  \param dToolCuttdirection: direction of tools
    *  
    *  this function calculate the value of the basic system in the current system
    */
   void adaptToScalingSystemInch(double& rdValue) const;

   /*! \fn void adaptToProgrammScaleFactor(double& rdValue) const
    *
    *  \param rdValue: parameter of the tool
    *  
    *  this function calculate the value of the basic system in the current system
    */
   void adaptToProgrammScaleFactor(double& rdValue) const;

   /*! \fn void adaptToProgrammScaleFactorToolAxis(double& rdValue) const
    *
    *  \param rdValue: parameter of the tool
    *  
    *  this function calculate the value of the basic system in the current system
    */
   void adaptToProgrammScaleFactorToolAxis(double& rdValue) const;

   /*! \fn void adaptToSubSpindle(double& rdValue, SlStepEdgeAdaptMirrorToolMode adaptToolMode) const
    *
    *  \param rdValue:       direction or cutting position of the tool
    *  \param adaptToolMode: defines possible types of calculate
    *  
    *  this function calculate the value of the basic system in the current system
    */
   void adaptToSubSpindle(double& rdValue, SlStepEdgeAdaptMirrorToolMode adaptToolMode) const;

   /*! \fn double mirrorToolCuttEdgePos(double dCuttedgepos) const;
    *
    *  \param dCuttedgepos: cutting position
    *  
    *  If spindle is active, then cutting position on X-axis mirror 
    */
   double mirrorToolCuttEdgePos(double dCuttedgepos) const;

   /*! \fn double mirrorToolCuttdirection (double dToolCuttdirection) const;
    *
    *  \param dToolCuttdirection: cutdirection of tools
    *  
    *  If spindle is active, then cutting direction on X-axis mirror 
    */
   double mirrorToolCuttdirection(double dToolCuttdirection) const;

   /*! \fn void adaptToSecondRevolver(double& rdValue, SlStepEdgeAdaptMirrorToolMode adaptToolMode) const
    *
    *  \param rdValue:       direction or cutting position of the tool
    *  \param adaptToolMode: defines possible types of calculate
    *  
    *  this function calculate the value of the basic system in the current system
    */
   void adaptToSecondRevolver(double& rdValue, SlStepEdgeAdaptMirrorToolMode adaptToolMode) const;

   /*! \fn double mirrorToolCuttEdgePosAxisOne(double dCuttedgepos) const;
    *
    *  \param dCuttedgepos: cutting position
    *  
    *  This function mirror the cutting position on Z axis.
    *  Note: If one is working in front of the rotation center and second behind of
    *  the rotation center, must be taken the mirro cutting position
    */
   double mirrorToolCuttEdgePosAxisOne(double dCuttedgepos) const;

   /*! \fn double mirrorToolCuttdirectionAxisOne (double dToolCuttdirection) const;
    *
    *  \param dToolCuttdirection: cutdirection of tools
    *  
    *  This function mirror the cutting direction on Z axis 
    *  Note: If one is working in front of the rotation center and second behind of
    *  the rotation center, must be taken the mirro cutting direction
    */
   double mirrorToolCuttdirectionAxisOne(double dToolCuttdirection) const;

   /*!
    *  \fn bool isDoubleEqualToDouble (double value1, double value2) const;
    *
    *  \param value1       value 1 to check
    *  \param value2       value 2 to check
    *
    *  Returns if the value 1 is equal to value 2 (v1 == v2)
    */
   bool isDoubleEqualToDouble(double value1, double value2) const;

   /*!
    *  \fn bool isDoubleLessThanDouble (double value1, double value2) const;
    *
    *  \param value1       value 1 to check
    *  \param value2       value 2 to check
    *
    *  Returns if the value 1 is less than value 2 (v1 < v2)
    */
   bool isDoubleLessThanDouble(double value1, double value2) const;

   /*!
    *  \fn bool isDoubleLessThanOrEqualToDouble (double value1, double value2) const;
    *
    *  \param value1       value 1 to check
    *  \param value2       value 2 to check
    *
    *  Returns if the value 1 is less than or equal to value 2 (v1 <= v2)
    */
   bool isDoubleLessThanOrEqualToDouble(double value1, double value2) const;

   /*!
    *  \fn bool isDoubleGreaterThanDouble (double value1, double value2) const;
    *
    *  \param value1       value 1 to check
    *  \param value2       value 2 to check
    *
    *  Returns if the value 1 is greater than value 2 (v1 > v2)
    */
   bool isDoubleGreaterThanDouble(double value1, double value2) const;

   /*!
    *  \fn bool isDoubleGreaterThanOrEqualToDouble (double value1, double value2) const;
    *
    *  \param value1       value 1 to check
    *  \param value2       value 2 to check
    *
    *  Returns if the value 1 is greater than or equal to value 2 (v1 >= v2)
    */
   bool isDoubleGreaterThanOrEqualToDouble(double value1, double value2) const;

   /*! \fn void setVector(SlStepEdgeDataVector &vec, double dA, double dB, double dC) const
    *
    *  \param vec:     vector which will be set
    *  \param dValue1: value1
    *  \param dValue2: value2
    *  \param dValue3: value3
    *  
    *  This function sets the values value1, value2 and value3 into vec
    */
   void setVector(SlStepEdgeDataVector& vec, double dValue1, double dValue2, double dValue3) const;

   /*! \fn void setRotMatrix(SlStepEdgeDataMatrix& matrix, double dRotAngle, unsigned integer nAxis) const
    *
    *  \param toolMatrix:  matrix which will be set
    *  \param dRotAngle:   rotation angle
    *  \param nAxis:       rotation axis
    *  
    *  This function sets a matrix by a given 
    *    - rotation angle and 
    *    - rotation axis 0: rotation axis X
    *                    1: rotation axis X
    *                    2: rotation axis X
    */
   void setRotMatrix(SlStepEdgeDataMatrix& matrix, double dRotAngle, unsigned int nAxis) const;

   /*! \fn void multMatrix(const SlStepEdgeDataMatrix& matrix1, const SlStepEdgeDataMatrix& matrix2, SlStepEdgeDataMatrix& matrixResult) const
    *
    *  \param matrix1:      given first matrix 1
    *  \param matrix2:      given second matrix 2
    *  \param matrixResult: calculated result of multiplication of matrix1 and matrix2
    *  
    *  This function multiplicates the matrix1 and matrix2 in result matrixResult 
    */
   void multMatrix(const SlStepEdgeDataMatrix& matrix1, const SlStepEdgeDataMatrix& matrix2, SlStepEdgeDataMatrix& matrixResult) const;

   /*! \fn void rotateVector(const SlStepEdgeDataMatrix& rotMatrix, SlStepEdgeDataVector& vec) const
    *
    *  \param rotMatrix:    given rotation matrix
    *  \param vec:          given vector which will be rotated and overwritten for result
    *  
    *  This function rotates the vector vec by the given rotation matrix rotMatrix.
    *  The result will be written in vec. 
    */
   void rotateVector(const SlStepEdgeDataMatrix& rotMatrix, SlStepEdgeDataVector& vec) const;

   /*! \fn void permuteVector(SlStepEdgeDataVector& vec) const
    *
    *  \param vec:          given vector which will be permuted and overwritten for result
    *  
    *  This function permutes the vector vec adapting to plane G18 
    */
   void permuteVector(SlStepEdgeDataVector& vec) const;

   /*! \fn double normAngle360(double dAngle) const
    *
    *  \param dAngle:        given angle which will be normalized to a value between 0 and 360
    *  
    *  This function normalizes the given angle dAngle to a value between 0 and 360.
    *  The normalized value will be given back.
    */
   double normAngle360(double dAngle) const;

   /*! \fn double normAngle180(double dAngle) const
    *
    *  \param dAngle:        given angle which will be normalized to a value between -180 and 180
    *  
    *  This function normalizes the given angle dAngle to a value between -180 and 180.
    *  The normalized value will be given back.
    */
   double normAngle180(double dAngle) const;

   /*! \fn double diffNormAngle(double dAngle1, double dAngle2) const
    *
    *  \param dAngle1:        given angle 1
    *  \param dAngle2:        given angle 2
    *  
    *  This function calculates the shortest distance between two given angles.
    *  The shortest distance will be given back.
    */
   double diffNormAngle(double dAngle1, double dAngle2) const;

   ///////////////////////////////////////////////////////////////////////////
   // private data members
   ///////////////////////////////////////////////////////////////////////////

   SlStepEdgeDataRecordPrivate*  m_pData;    //!< d-pointer pattern
}; // <-- class SlStepEdgeDataRecord

/*! \typedef SlStepTmEdgeDataVectorType
 *  This is the typedef of gui container list
 */
typedef QMap<int, SlStepEdgeDataRecord> SlStepTmEdgeDataVectorType;

class SlStepToolDataRecordPrivate;

/*!\class SlStepToolDataRecord
 *
 *  class tool data in SlStepEditor 
 */
class SL_STEP_LOGIC_EXPORT SlStepToolDataRecord
{
public:
   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   /*! \fn SlStepToolDataRecord(void)
    *
    *  Constructor
    */
   SlStepToolDataRecord(void);

   /*! \fn SlStepToolDataRecord(const SlTmMassData2ToolMagListChangedData& rConstList,
    *                           const SlTmMassData2ToolMagListElData& rConstListEl,
    *                           unsigned int nDiameterOrRadiusIdentifier,
    *                           bool bAdaptTransDataExist)
    *
    *  Constructor
    *  \param nDiameterOrRadiusIdentifier:   identifier for diameter or radius
    *  \param bAdaptTransDataExist:          magazineplace adapter and transformation data exist
    *
    *  scource are tool data classes from toolmanagement service adapter
    */
   SlStepToolDataRecord(const SlTmMassData2ToolMagListChangedData& rConstList,
                        const SlTmMassData2ToolMagListElData& rConstListEl,
                        unsigned int nDiameterOrRadiusIdentifier,
                        bool bAdaptTransDataExist);

   /*! 
    *  \fn SlStepToolDataRecord(const SlStepToolDataRecord& rOther)
    *
    *  \param rOther       the other object
    *
    *  This class has pointer members, so it has to implement its own copy
    *  contructor.
    */
   SlStepToolDataRecord(const SlStepToolDataRecord& rOther);

   /*! \fn  ~SlStepToolDataRecord(void)
    *
    *  protected creator used in singleton classes
    */
   ~SlStepToolDataRecord(void);

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   ///////////////////////////////////////////////////////////////////////////
   /*! \fn bool isValid(void) const
    *  access to valid state
    */
   bool isValid(void) const;

   /*! \fn bool isTool(void) const
    *  access to isTool true/false
    */
   bool isTool(void) const;

   /*! \fn QString toolIdent(void) const
    *  access to toolidentifier
    */
   QString toolIdent(void) const;

   /*! \fn void setToolIdent(QString toolIdent)
    *  set toolidentifier
    */
   void setToolIdent(QString toolIdent);

   /*! \fn int placeNo(void) const
    *  access to place number
    */
   int placeNo(void) const;

   /*! \fn void setPlaceNo(int toolPlace)
    *  set place number
    */
   void setPlaceNo(int toolPlace);

   /*! \fn int duploNo(void) const
    *  access to duplonumber
    */
   int duploNo(void) const;

   /*! \fn void setDuploNo(int duploNo)
    *  set duplonumber
    */
   void setDuploNo(int duploNo);

   /*! \fn int multiToolLocation(void) const
    *  access to multitool location
    */
   int multiToolLocation(void) const;

   /*! \fn void setMultiToolLocation(int multiToolLocation)
    *  set multitool location
    */
   void setMultiToolLocation(int multiToolLocation);

   /*! \fn int countMultiToolLocations(void) const
    *  access to count of multitool locations
    */
   int countMultiToolLocations(void) const;

   /*! \fn void setCountMultiToolLocations(int countMultiToolLocations)
    *  set count multitool locations
    */
   void setCountMultiToolLocations(int nCountMultiToolLocations);

   /*! \fn int toolState(void) const
    *  tool state
    */
   int toolState(void) const;

   /*! \fn SlStepEdgeDataRecord edgeData(int edgeNo) const
    *   access to edge data record
    *
    *  \param  edgeNo    in: edge number
    */
   SlStepEdgeDataRecord edgeData(int edgeNo) const;

   /*! \fn void setEdgeData(int edge, SlStepEdgeDataRecord edgeData)
    *  set edge data record
    *
    *  \param  edgeNo    in: edge number
    *  \param  edgeData  in: edge data record
    */
   void setEdgeData(int edge, SlStepEdgeDataRecord edgeData);

   /*! \fn bool containsEdgeData(int edge) const
    *   edge with edge number exists
    *
    *  \param  edgeNo    in: edge number
    */
   bool containsEdgeData(int edge) const;

   /*!
    *  \fn int getEdgeNoByOptDNo (int nOptDNo) const
    *
    *  \param nOptDNo      optional D number to search
    *
    *  Searchs within the edges for an edge having given \a nOptDNo as 
    *  optional D-No and returns its edgeNo. If no edge was found it returns 0.
    */
   int getEdgeNoByOptDNo (int nOptDNo) const;


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! 
    *  \fn SlStepToolDataRecord& operator= (const SlStepToolDataRecord& rOther)
    *
    *  \param rOther       the other object
    *
    *  This class has pointer members, so it has to implement its own 
    *  assignment operator.
    */
   SlStepToolDataRecord& operator= (const SlStepToolDataRecord& rOther);

   /*! \fn bool operator==(const SlStepToolDataRecord& rToolDataRecord) const
    *  \retval bool      Same cells or not
    *
    *  Returns true if \a rToolDataRecord includes the same data
    *  otherwise returns false.
    */
   bool operator==(const SlStepToolDataRecord& rToolDataRecord) const;

   /*! \fn bool operator!=(const SlStepToolDataRecord& rToolDataRecord) const
    *  \retval bool      Same cells or not
    *
    *  Returns false if \a rToolDataRecord includes the same data
    *  otherwise returns true.
    */
   bool operator!=(const SlStepToolDataRecord& rToolDataRecord) const;

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE MEMBERS
   ///////////////////////////////////////////////////////////////////////////
private:

   SlStepToolDataRecordPrivate*  m_pData;    //!< d-pointer pattern
}; // <-- class SlStepToolDataRecord


class SlStepToolDataPrivate;

/*!\class SlStepToolData
 *
 *  class for tool data in toolmanagement 
 */
class SL_STEP_LOGIC_EXPORT SlStepToolData : public QObject
{
   Q_OBJECT
public:

   // declare destoyer as friend  --  destroyer needs access to destructor
   friend class SlStepDestroyer<SlStepToolData>;

   ///////////////////////////////////////////////////////////////////////////
   // ASSESSORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn static SlStepToolData* Exemplar (void)
    *
    *  \retval Pointer to the one and only singleton
    *
    *  Function to get the one and only pointer to the SlStepToolData.
    *
    */
   static SlStepToolData* Exemplar (void);

   /*!
    *  \fn int getContainerNo(int nChanNo = -1) const
    *
    *  \param nChanNo   channel index to get container to
    *
    *  If \a nChanNo is -1 the container number is bound to the current 
    *  channel. If \a nChanNo is >= 1 the container number is bound to 
    *  this channel.
    */
   int getContainerNo(int nChanNo = -1) const;

   /*!
    *  \fn SlTmUtil::StoreLengthUnitValueEnum basicLengthUnit(int containerNo) const
    *
    *  \param containerNo   container number to get basic length unit to
    *
    *  Returns active basic length unit of container.
    */
   SlTmUtil::StoreLengthUnitValueEnum basicLengthUnit(int containerNo) const;

   /*!
    *  \fn bool isOptDNumbersExist(int containerNo) const
    *
    *  \param containerNo          container number
    * 
    *  Returns true if optional D numbers exist; 
    *  otherwise it returns false.
    */
   bool isOptDNumbersExist(int containerNo) const;

   /*!
    *  \fn SlStepToolDataRecord toolData(int containerNo, QString toolIdent, int duploNo = -1) const
    *
    *  \param containerNo   container number
    *  \param toolIdent     identifier of tool
    *  \param duploNo       duplo number of tool, if -1 the frist tool with toolIdent is choosen
    *
    *  \retval tooldata record with tool and edge data
    *
    *  Function to get the tooldata of a tool spezified with toolname, edge number
    *  and optional duplonumber.
    *
    *  If \a duploNo is -1 the returned tooldata record is the first record found with 
    *  toolident.
    */
   SlStepToolDataRecord toolData(int containerNo, QString toolIdent, int duploNo = -1) const;

   /*!
    *  \fn SlStepEdgeDataRecord edgeData (const QString& rsToolIdent,
    *                                     int nDuploNo,
    *                                     int nEdgeNo,
    *                                     const SlStepEdgeDataInitData& rInitData,
    *                                     enum SlStepToolIdentifierMode = SL_STEP_TOOL_IDENT_IDENT,
    *                                     int nMultiToolLocation = 0) ) const
    *
    *  \param rsToolIdent        identifier of tool
    *  \param nDuploNo           duplo number of tool, if -1 the first tool with toolIdent is choosen
    *  \param nEdgeNo            edge number
    *  \param rInitData          datas used to initialise the returned edge data record
    *  \param toolIdentifierMode tool identifier mode: identifier or place number, default is identifier
    *  \param nMultiToolLocation multitool location: default is 0
    *
    *  \retval tooldata record with tool and edge data
    *
    *  Function to get the tooldata of a tool spezified with toolname, edge number
    *  and optional duplonumber.
    *
    *  If \a nDuploNo is -1 the returned tooldata record is the first record found with 
    *  toolident.
    */
   SlStepEdgeDataRecord edgeData (const QString& rsToolIdent,
                                  int nDuploNo,
                                  int nEdgeNo,
                                  const SlStepEdgeDataInitData& rInitData,
                                  enum SlStepToolIdentifierMode toolIdentifierMode = SL_STEP_TOOL_IDENT_IDENT,
                                  int nMultiToolLocation = 0) const;

   /*!
    *  \fn bool isToolDataListInitialized (int nChanNo) const
    *
    *  \param nChanNo   channel number
    *
    *  \retval true, if tool data list is initialized for given channel number, else false.
    *
    *  Returns true, if tool data list is initialized for given channel number \a nChanNo,
    *  else false.
    */
   bool isToolDataListInitialized (int nChanNo) const;

signals:

   ///////////////////////////////////////////////////////////////////////////
   // SIGNALS
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn void toolDataListInitialized ();
    *
    *  The signal is used to refire the SlStepToolDataPrivate's signal 
    *  toolDataListInitialized()
    */
   void toolDataListInitialized ();

protected:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   
   /*! \fn  SlStepToolData (QObject *parent = 0)
    *
    *  protected creator used in singleton classes
    *
    *  \param nChanNo   channel index for the exemplar
    */
   SlStepToolData (QObject *parent = 0);

   /*! \fn  ~SlStepToolData (void)
    *
    *  protected creator used in singleton classes
    */
   ~SlStepToolData (void);


private:

   ///////////////////////////////////////////////////////////////////////////
   // private members
   ///////////////////////////////////////////////////////////////////////////

   static SlStepToolData*  s_m_pExemplar; //!< pointer to the one an only, singleton
   SlStepToolDataPrivate*  m_pData;    //!< d-pointer pattern

   ///////////////////////////////////////////////////////////////////////////
   // private operators
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed */
   SlStepToolData (const SlStepToolData& rCopy);

   /*! assignment operator not allowed */
   SlStepToolData& operator=(const SlStepToolData& rCopy);

}; // <-- class SlStepToolData

#endif // SL_STEP_TOOL_DATA_H

