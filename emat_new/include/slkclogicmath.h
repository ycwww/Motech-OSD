///////////////////////////////////////////////////////////////////////////////
/*! \file   slkclogicmath.h
 *  \author Adam Gorecki, Ould El Yezid, Moulaye Ely
 *  \date   08.06.2015
 *  \brief  Class declaration file for class SlKcLogicMath
 *
 *  This file is part of the HMI Solutionline, math. funktion for Kinematic Logic Machine/Parameter.
 *
 * (C) Copyright Siemens AG A&D MC 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_KC_LOGIC_MATH_H
#define SL_KC_LOGIC_MATH_H

#include "slkclogicexports.h"
#include <math.h>
#include <QtCore/qglobal.h>

// define of PI
#define SL_KC_PI 3.141592653589793238462643383279502884197169399

// define of Epsilon
#define SL_KC_EPS  1.0E-6f
#define SL_KC_EPS2 1.0E-12f

// Rad2Deg Faktor
const double SL_KC_G2R = SL_KC_PI/180.0;
// Deg2Rad Faktor
const double SL_KC_R2G = 180.0/SL_KC_PI;

//
//
//
////////////////////////////////////////////////////////////////
// DECLARATION OF SlKcVector CLASS
////////////////////////////////////////////////////////////////
//
//
//
//!  3D class SlKcVector 
/*!
 * \class SlKcVector
 *
 * declaration of 3D vector
 */
class SL_KC_LOGIC_EXPORT SlKcVector
{
public:
   ////////////////////////////////////////////////////////////////////
   // CONSTRUCTORS
   ////////////////////////////////////////////////////////////////////
  /*! 
   * \fn SlKcVector()
   * Default constructor. Value is set to (0,0,0).
   */
   SlKcVector() :
      x(0.0),
      y(0.0),
      z(0.0)
   {
   } // <-- SlKcVector()

   /*! 
    * \fn SlKcVector(double X, double Y, double Z)
    *
    * Standard constructor with the x, y and z values.
    */
   SlKcVector(double X, double Y, double Z) :
      x(X),
      y(Y),
      z(Z)
   {
   } // <-- SlKcVector()

   //////////////////////////////////////////////////////////////
   // PUBLIC OPERATORS
   //////////////////////////////////////////////////////////////

   /*! \name Algebraic computations */

   //! plus operator
   /*! 
    * \fn SlKcVector operator+(const SlKcVector &a, const SlKcVector &b)
    *
    * Returns the sum of the two vectors. 
    */
   friend SlKcVector operator+(const SlKcVector &a, const SlKcVector &b)
   {
      return SlKcVector(a.x+b.x, a.y+b.y, a.z+b.z);
   } // <-- operator+()

   //! minus operater
   /*! 
    * \fn SlKcVector operator-(const SlKcVector &a, const SlKcVector &b)
    *
    * Returns the difference of the two vectors. 
    */
   friend SlKcVector operator-(const SlKcVector &a, const SlKcVector &b)
   {
      return SlKcVector(a.x-b.x, a.y-b.y, a.z-b.z);
   } // <-- operator-()

   //! unary minus operator
   /*! 
    * \fn  SlKcVector operator-(const SlKcVector &a)
    *
    * Unary minus operator. 
    */
   friend SlKcVector operator-(const SlKcVector &a)
   {
      return SlKcVector(-a.x, -a.y, -a.z);
   } // <-- operator-()

   //! left hand skalar multiplikator
   /*! 
    * \fn SlKcVector operator*(const SlKcVector &a, double k)
    *
    * Returns the product of the vector with a scalar. 
    */
   friend SlKcVector operator*(const SlKcVector &a, double k)
   {
      return SlKcVector(a.x*k, a.y*k, a.z*k);
   } // <-- operator*()

   //! right hand skalar multiplikator
   /*! 
    * \fn SlKcVector operator*(double k, const SlKcVector &a)
    * 
    * Returns the product of the vector with a scalar. 
    */
   friend SlKcVector operator*(double k, const SlKcVector &a)
   {
      return a*k;
   } // <-- operator*()

   //! divide operator
   /*! 
    * \fn SlKcVector operator/(const SlKcVector &a, double k)
    *
    * Returns the division of the vector with a scalar.
    *
    * Too small \p k values are \e not tested and may result in \c NaN values. 
    */
   friend SlKcVector operator/(const SlKcVector &a, double k)
   {
      return SlKcVector(a.x/k, a.y/k, a.z/k);
   } // <-- operator/()

   //! unequal operator
   /*! 
    * \fn bool operator!=(const SlKcVector &a, const SlKcVector &b)
    *
    * Returns \c true only when the two vector are not equal (see operator==()). 
    */
   friend bool operator!=(const SlKcVector &a, const SlKcVector &b)
   {
      return !(a==b);
   } // <-- operator!=()

   //! equal operator
   /*! 
    * \fn bool operator==(const SlKcVector &a, const SlKcVector &b)
    *
    * Returns \c true when the squaredNorm() of the difference vector is lower then 1E-10. 
    */
   friend bool operator==(const SlKcVector &a, const SlKcVector &b)
   {
      return (a-b).isZero();
   } // <-- operator==()

   //! plus equal operator
   /*! 
    * \fn SlKcVector& operator+=(const SlKcVector &a)
    *
    * Adds \p a to the vector. 
    */
   SlKcVector& operator+=(const SlKcVector &a)
   {
      x += a.x; y += a.y; z += a.z;
      return *this;
   } // <-- operator+=()

   //! minus qual operator
   /*! 
    * \fn SlKcVector& operator-=(const SlKcVector &a)
    *
    * Subtracts \p a to the vector. 
    */
   SlKcVector& operator-=(const SlKcVector &a)
   {
      x -= a.x; y -= a.y; z -= a.z;
      return *this;
   } // <-- operator-=()

   //! multipilicator equal operator
   /*! 
    * \fn SlKcVector& operator*=(double k)
    *
    * Multiply the vector by a scalar \p k. 
    */
   SlKcVector& operator*=(double k)
   {
      x *= k; y *= k; z *= k;
      return *this;
   } // <-- operator*=()

   //! skalar divide equal operator
   /*! 
    * \fn SlKcVector& operator/=(double k)
    *
    * Divides the vector by a scalar \p k.
    */
   SlKcVector& operator/=(double k)
   {
      Q_ASSERT(fabs(k) > SL_KC_EPS2);

      double div = 1/k;  // to obtain performance
      x *= div;
      y *= div;
      z *= div;

      return *this;
   } // <-- operator/=()

   //! vector multiplicator operator
   /*! 
    * \fn double operator*(const SlKcVector &a, const SlKcVector &b)
    *
    * Dot product of the two SlKcVector. 
    */
   friend double operator*(const SlKcVector &a, const SlKcVector &b)
   {
      return a.x*b.x + a.y*b.y + a.z*b.z;
   } // <-- operator*()

   //! cross product operator
   /*! 
    * \fn SlKcVector operator^(const SlKcVector &a, const SlKcVector &b)
    *
    * Cross product of the two vectors. Same as cross(). 
    */
   friend SlKcVector operator^(const SlKcVector &a, const SlKcVector &b)
   {
      return cross(a,b);
   } // <-- operator^()

   //! cross product of two vectors
   /*!
    * \fn SlKcVector cross(const SlKcVector &a, const SlKcVector &b)
    *
    * Cross product of the two SlKcVector. Mind the order ! 
    */
   friend SlKcVector cross(const SlKcVector &a, const SlKcVector &b)
   {
      return SlKcVector(a.y*b.z - a.z*b.y,
	                        a.z*b.x - a.x*b.z,
	                        a.x*b.y - a.y*b.x);
   } // <-- cross()

   //! squared norm
   /*! 
    * \fn  double squaredNorm() const
    *
    * Returns the \e squared norm of the SlKcVector. 
    */
   double squaredNorm() const { return x*x + y*y + z*z; }

   //! norm of vector
   /*! 
    * \fn double norm() const
    *
    * Returns the norm of the vector. 
    */
   double norm() const { return sqrt(x*x + y*y + z*z); }

   //! normalizes vector
   /*! 
    * \fn double normalize()
    *
    * Normalizes the SlKcVector and returns its original norm.
    * Normalizing a null vector will leave it unchanged.
    */
   double normalize()
   {
      const double n = norm();
      if (n > SL_KC_EPS2)
         *this /= n;
      return n;
   } // <-- normalize()

   /*! 
    * \fn SlKcVector unit() const
    * 
    * Returns a unitary (normalized) \e representation of the vector. The original SlKcVector is not modified. 
    */
   SlKcVector unit() const
   {
      SlKcVector v = *this;
      v.normalize();
      return v;
   } // <-- unit()

   /*! 
    * \fn SlKcVector orthogonalVec() const
    *
    * Returns a SlKcVector orthogonal to the SlKcVector. Its norm() depends on the SlKcVector, but is zero only for a
    * null SlKcVector. Note that the function that associates an orthogonalVec() to a SlKcVector is not continous.
    */
   SlKcVector orthogonalVec() const;

   /*!
    * \fn double * floatVec()
    *
    * returns pointer to array with vector values
    */
   double * floatVec() { return v; }


   //! read bracket operator
   /*!
    * \fn double operator[](int i) const
    *
    * Bracket operator, with a constant return value. \p i must range in [0..2]. 
    */
   double operator[](int i) const
   {
      return v[i];
   } // <-- operator[]()

   //! write bracket operator
   /*! 
    * \fn double& operator[](int i)
    *
    * Bracket operator returning an l-value. \p i must range in [0..2]. 
    */
   double& operator[](int i)
   {
      return v[i];
   } // <-- operator[]()

   /// Check if the length of the vector is sufficiently greater than zero.
   bool isZero() const
   {
      return SL_KC_EPS2 >= squaredNorm();
   }

public:
   //////////////////////////////////////////////////////////////////////////
   // PUBLIC DATA
   //////////////////////////////////////////////////////////////////////////
   union
   {
      struct
      {
         double x, y, z;
      };
      double v[3];
   };
   
}; // <-- class SlKcVector

//
//
//
////////////////////////////////////////////////////////////////
// DECLARATION OF SlKcQuaternion CLASS
////////////////////////////////////////////////////////////////
//
//
//
//! class SlKcQuaternion 
/*!
 * \class SlKcQuaternion
 *
 * declaration of quatenion for 3D transformations
 */
class SL_KC_LOGIC_EXPORT SlKcQuaternion
{
public:
   ////////////////////////////////////////////////////////////////////
   // CONSTRUCTORS
   ////////////////////////////////////////////////////////////////////
   //! default constructor
   /*! 
    * \fn SlKcQuaternion()
    *
    * Default constructor, builds an identity rotation. 
    */
   SlKcQuaternion()
   {
      q[0]=q[1]=q[2]=0.0;  q[3]=1.0;
   } // <-- SlKcQuaternion()

   //! two vector constructor
   /*!
    * \fn SlKcQuaternion(const SlKcVector& from, const SlKcVector& to);
    *
    * This costructor defines a quaternion which describes rotation on cross product vector of 
    * \a from and \a to so that \a from becomes \a to;
    */
   SlKcQuaternion(const SlKcVector& from, const SlKcVector& to);

   //! quadruple constructor
   /*! 
    * \fn SlKcQuaternion(double q0, double q1, double q2, double q3)
    *
    * Constructor from the four values of a SlKcQuaternion. First three values are axis*sin(angle/2) and
    * last one is cos(angle/2).
    *
    * \attention The identity SlKcQuaternion is SlKcQuaternion(0,0,0,1) and \e not SlKcQuaternion(0,0,0,0) (which is
    * not unitary). The default SlKcQuaternion() creates such identity SlKcQuaternion. 
    */
   SlKcQuaternion(double q0, double q1, double q2, double q3)
   {
      q[0] = q0;
      q[1] = q1;
      q[2] = q2;
      q[3] = q3;
   } // <-- SlKcQuaternion()

   //! Copy constructor
   /*!
    * \fn SlKcQuaternion(const SlKcQuaternion& Q)
    *
    * copy constructor
    */
   SlKcQuaternion(const SlKcQuaternion& Q)
   {
      for (int i=0; i<4; ++i) q[i] = Q.q[i];
   } // <-- SlKcQuaternion()

   ////////////////////////////////////////////////////////////////////
   // PUBLIC FUNCTIONS
   ////////////////////////////////////////////////////////////////////

   //! equal operator
   /*! 
    * \fn SlKcQuaternion& operator=(const SlKcQuaternion& Q)
    *
    * Equal operator. 
    */
   SlKcQuaternion& operator=(const SlKcQuaternion& Q)
   {
      for (int i=0; i<4; ++i)
         q[i] = Q.q[i];
      return (*this);
   } // <-- operator=()

   //! confugate function
   /*!
    * \fn  SlKcQuaternion conjugate(SlKcQuaternion quat)
    *
    * The conjugate of a quaternion
    * Let's compute the conjugate of a quaternion and call it Q'. The conjugate is simply 
    *
    * Q' = [ w, -v ]
    *
    * where v is 3D vector
    */
   SlKcQuaternion conjugate(SlKcQuaternion quat);

   //! multiplication of quaternions
   /*!
    * \fn SlKcQuaternion mult(const SlKcQuaternion& A, const SlKcQuaternion& B) const
    *
    *  Multiplying quaternions
    *  Multiplication with quaternions is a little complicated as it involves dot-products cross-products. 
    *  However, if you just use the following forumula that expands these operations, it isn't too hard. 
    *  To multiply quaternion A by quaternion B, just do the following: 
    *
    *  C = A * B
    *
    *  such that: 
    *
    *  C.x = | A.w*B.x + A.x*B.w + A.y*B.z - A.z*B.y |
    *  C.y = | A.w*B.y - A.x*B.z + A.y*B.w + A.z*B.x |
    *  C.z = | A.w*B.z + A.x*B.y - A.y*B.x + A.z*B.w |
    *  C.w = | A.w*B.w - A.x*B.x - A.y*B.y - A.z*B.z |
    */
   SlKcQuaternion mult(const SlKcQuaternion& A, const SlKcQuaternion& B) const;

   //! sets quaternion in right maner for given rotation and angle
   /*! 
    * \fn void setAxisAngle(const SlKcVector& axis, double angle)
    *
    * Sets the SlKcQuaternion as a rotation of axis \p axis and angle \p angle (in radians).
    *
    *  \p axis does not need to be normalized. A null \p axis will result in an identity SlKcQuaternion.
    */
   void setAxisAngle(const SlKcVector& axis, double angle)
   {
      const double norm = axis.norm();
      if (norm < SL_KC_EPS)
      {
         // Null rotation
         q[0] = 0.0;      q[1] = 0.0;      q[2] = 0.0;      q[3] = 1.0;
      }
      else
      {
         const double sin_half_angle = sin(angle * 0.5);
         q[0] = sin_half_angle*axis[0]/norm;
         q[1] = sin_half_angle*axis[1]/norm;
         q[2] = sin_half_angle*axis[2]/norm;
         q[3] = cos(angle * 0.5);
      }
   } // <-- setAxisAngle()

   //! length of quaternion
   /*!
    * \fn double length()
    *
    * calculate length of quaternion
    */
   double length()
   {
      return sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
   } // <-- length()

   //! normalize
   /*!
    * \fn  double normalize()
    *
    * function normalizes the quaternion and returns its origin length.
    * if length is null we do nothing
    */
   double normalize()
   {
      double L = length();

      if (0 != L)
      {
         double div = 1/L;  // to obtain performance
         q[0] *= div;
         q[1] *= div;
         q[2] *= div;
         q[3] *= div;
      }

      return L;
   } // <-- normalize()

   //! returns rotation axis of quaternion
   /*! 
    * \fn SlKcVector axis() const
    *
    * Returns the normalized axis direction of the rotation represented by the SlKcQuaternion.
    * It is null for an identity SlKcQuaternion. See also angle() and getAxisAngle().
    */
   SlKcVector axis() const
   {
      SlKcVector res = SlKcVector(q[0], q[1], q[2]);
      const double sinus = res.norm();
      if (sinus > 1E-8)
         res /= sinus;
      return (acos(q[3]) <= SL_KC_PI*0.5) ? res : -res;
   } // <-- axis()

   //! return rotation angle
   /*! 
    * \fn double angle() const
    *
    * Returns the angle (in radians) of the rotation represented by the SlKcQuaternion.
    *
    * This value is always in the range [0-pi]. Larger rotational angles are obtained by inverting the
    * axis() direction.
    * See also axis() and getAxisAngle().
    */
   double angle() const
   {
      const double angle = 2.0 * acos(q[3]);
      return (angle <= SL_KC_PI) ? angle : 2.0*SL_KC_PI - angle;
   } // <-- angle()

   //! readonly bracket operator
   /*! 
    * \fn double operator[](int i) const
    *
    * Bracket operator, with a constant return value. \p i must range in [0..3]. See the \ref SlKcQuaternion(double, double, double, double)
    * documentation. 
    */
   double operator[](int i) const
   {
      return q[i];
   } // <-- operator[]()

   //! writable bracket operator
   /*! 
    * \fn double& operator[](int i)
    *
    * Bracket operator returning an l-value. \p i must range in [0..3]. 
    * See the \ref SlKcQuaternion(double, double, double, double) documentation. 
    */
   double& operator[](int i)
   {
      return q[i];
   } // <-- operator[]()

   /*! \name Rotation computations */

   //! quaternion multipication operator
   /*! 
    * \fn SlKcQuaternion operator*(const SlKcQuaternion& a, const SlKcQuaternion& b)
    * 
    * Returns the composition of the \p a and \p b rotations.
    *
    * The order is important. When applied to a SlKcVector \c v (see operator*(const SlKcQuaternion&, const SlKcVector&)
    * and rotate()) the resulting SlKcQuaternion acts as if \p b was applied first and then \p a was
    * applied. This is obvious since the image \c v' of \p v by the composited rotation satisfies: \code
    * v'= (a*b) * v = a * (b*v) \endcode
    *
    * Note that a*b usually differs from b*a.
    *
    * \attention For efficiency reasons, the resulting SlKcQuaternion is not normalized. Use normalize() in
    * case of numerical drift with small rotation composition.
    */
   friend SlKcQuaternion operator*(const SlKcQuaternion& a, const SlKcQuaternion& b)
   {
      return SlKcQuaternion(a.q[3]*b.q[0] + b.q[3]*a.q[0] + a.q[1]*b.q[2] - a.q[2]*b.q[1],
                            a.q[3]*b.q[1] + b.q[3]*a.q[1] + a.q[2]*b.q[0] - a.q[0]*b.q[2],
                            a.q[3]*b.q[2] + b.q[3]*a.q[2] + a.q[0]*b.q[1] - a.q[1]*b.q[0],
                            a.q[3]*b.q[3] - b.q[0]*a.q[0] - a.q[1]*b.q[1] - a.q[2]*b.q[2]);
   } // <-- operator*()

   //! quaternion multiplication equal operator
   /*! 
    * \fn SlKcQuaternion& operator*=(const SlKcQuaternion &q)
    *
    * SlKcQuaternion rotation is composed with \p q.
    *
    * See operator*(), since this is equivalent to \c this = \c this * \p q.
    *
    * \note For efficiency reasons, the resulting SlKcQuaternion is not normalized.
    * You may normalize() it after each application in case of numerical drift.
    */
   SlKcQuaternion& operator*=(const SlKcQuaternion &q)
   {
      *this = (*this)*q;
      return *this;
   } // <-- operator*=()

   //! quaternion/vector multiplication operator
   /*! 
    * \fn SlKcVector operator*(const SlKcQuaternion& q, const SlKcVector& v)
    *
    * Returns the image of \p v by the rotation \p q.
    *
    * Same as q.rotate(v). See \ref rotate() and \ref inverseRotate().
    */
   friend SlKcVector operator*(const SlKcQuaternion& q, const SlKcVector& v)
   {
      return q.rotate(v);
   } // <-- operator*()

   //! rotation function for vector
   /*! 
    * \fn SlKcVector rotate(const SlKcVector& v) const
    *
    * Returns the image of \p v by the SlKcQuaternion rotation.
    *
    * See also inverseRotate() and operator*(const SlKcQuaternion&, const SlKcVector&).
    */
   SlKcVector rotate(const SlKcVector& v) const;

   //! inverse rotation for vector
   /*! 
    * \fn SlKcVector inverseRotate(const SlKcVector& v) const
    *
    * Returns the image of \p v by the SlKcQuaternion inverse() rotation.
    *
    * rotate() performs an inverse transformation. Same as inverse().rotate(v).
    */
   SlKcVector inverseRotate(const SlKcVector& v) const
   {
      return inverse().rotate(v);
   } // <-- inverseRotate()

   /*! \name Inversion */

   //! returns inverse quaternion
   /*! 
    * \fn SlKcQuaternion inverse() const
    *
    * Returns the inverse Quaternion (inverse rotation).
    *
    * Result has a negated \ref axis() direction and the same \ref angle(). A composition (see \ref operator*()) of a
    * Quaternion and its \ref inverse() results in an identity function.
    *
    * Use \ref invert() to actually modify the Quaternion.
    */
   SlKcQuaternion inverse() const
   {
      return SlKcQuaternion(-q[0], -q[1], -q[2], q[3]);
   } // <-- inverse()

   /*! Associated matrix */

   const double* matrix() const;
   void getMatrix(double m[4][4]) const;
   void getMatrix(double m[16]) const;

   void getRotationMatrix(double m[3][3]) const;

   void getInverseMatrix(double m[4][4]) const;
   void getInverseMatrix(double m[16]) const;

   void getInverseRotationMatrix(double m[3][3]) const;
   void GetAxisAngle(SlKcVector& axis, double &angle);

public:
   //////////////////////////////////////////////////////////////////////////
   // PUBLIC DATA
   //////////////////////////////////////////////////////////////////////////
   union
   {
      struct { double x, y, z, w; };
      double q[4];
   };
}; // <-- class SlKcQuaternion


#endif // SL_KC_LOGIC_MATH_H

