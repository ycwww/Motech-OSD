///////////////////////////////////////////////////////////////////////////////
/*! \file   slsimgeom.h
 *  \author Norbert Olah, Walter Häring
 *  \date   01.10.2005
 *  \brief  Headerfile for classes SlSimGeom/SlSimFrame
 *
 *  This file is part of the HMI SolutionLine Simulation.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_SIM_GEOM
#define SL_SIM_GEOM

///////////////////////////////////////////////////////////////////////////////

#include "slsimiface.h"
#include "slsimglbconst.h"
///////////////////////////////////////////////////////////////////////////////


const double SL_SIM_180 = 180.0; //!< 180 Grad


///////////////////////////////////////////////////////////////////////////////
// SlSimGeom
///////////////////////////////////////////////////////////////////////////////
namespace SlSimGeom
{
    ///////////////////////////////////////////////////////////////////////////
    double get_tan(double angle); //!< Calculate TAN()
    ///////////////////////////////////////////////////////////////////////////
    short int checkCircle(short int& ipotype, CircleType& circle, GeoposType apos, GeoposType epos,  const double circle_error_const, const double circle_error_factor, const double int_incr_per_mm=1000, bool noerror=false); //!< Check Circle
    short int calcCircleCenter(short int& ipotype, CircleType& circle, GeoposType apos, GeoposType epos); //!< Calculate Circle Center
    double calcCircleRadius(const CircleType& circle, const GeoposType& epos, const double epsilon=SL_SIM_EPS); //!< Calculate Circle Radius
    double calcCircleAngle(const CircleType& circle, const GeoposType& epos, const GeoposType& apos, const double epsilon=SL_SIM_EPS); //!< Calculate Circle Angle
    short int calcCircleCenterpoint(GeoposType& centerPoint, GeoposType startPoint, GeoposType endPoint, double radius, GeoposType circlePlaneNormVector, bool positiveOrientation);
    double vectAbs(const GeoposType& vect); //!< Vector Length
    double vectScal(const GeoposType& vect1, const GeoposType& vect2); //!< Scalar Product
    GeoposType vectMult(double lambda, const GeoposType& vect); //!< Vector Multiplication
    GeoposType vectNorm(const GeoposType& vect, const double espsilon=SL_SIM_EPS); //!< Vector Norm
    GeoposType vectProd(const GeoposType& vect1, const GeoposType& vect2); //!< Vector Product
    ///////////////////////////////////////////////////////////////////////////
}  

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SlSimFrame
///////////////////////////////////////////////////////////////////////////////
/*! \class SlSimFrame slsimgeom.h
 *  \brief Frame Calculations
*/
namespace SlSimFrame
{
    ///////////////////////////////////////////////////////////////////////////
    void getGeoAxFrame(AxPosType& axis, const FrameType& frame); //!< Load Geoax Frame
    void getMachAxTrans(AxPosType& axis, const FrameType& frame, const SpinType& spin, const bool vnck); //!< Load Axis Translations
    void getSpindTrans(SpinType& spin, const FrameType& frame, const bool vnck); //!< Load Spindle Translations
    void applyAxTra(MachaxType& retval, const FrameType& frame, const SpinType& spin, const bool vnck, bool invers); //!< Axis Translations
    void applySpinTra(SpinType& retval, const FrameType& frame, const bool vnck, bool invers); //!< Spindle Translations
    void applyFrame(GeoposType& retval, const FrameType& frame, bool invers); //!< Frame
    void applyTrans(GeoposType& retval, const GeoposType& trans, bool invers); //!< Translation
    void applyRot(GeoposType& retval, const GeoposType& rot, GeoposType POS, bool invers); //!< Rotation
    void applyScale(GeoposType& retval, const GeoposType& scale, bool invers); //!< Scale
    void applyMirror(GeoposType& retval, const GeoparType& mirror); //!< Mirror
    GeoposType addTrans(const GeoposType& TRANS1, const GeoposType& TRANS2);
    void checkModulo(double& angle);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#endif // SL_SIM_GEOM
///////////////////////////////////////////////////////////////////////////////
