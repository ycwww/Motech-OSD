///////////////////////////////////////////////////////////////////////////////
/*! \file   slkcbaseobject.h
 *  \author Adam Gorecki
 *  \date   24.05.2011
 *  \brief  Class declaration file for class SlKcBaseObject
 *
 *  This file is part of the HMI Solutionline, Kinematic Chain Logic Machine/Parameter.
 *
 * (C) Copyright Siemens AG A&D MC 2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_KC_BASE_OBJECT_H
#define SL_KC_BASE_OBJECT_H

#include "slkclogicexports.h"
#include "slkclogicglobal.h"
#include "slsteptemplates.h"
#include "slhmitemplatesqt.h"

#include <QtCore/QtGlobal>
#include <QtCore/QVariant>
#include <QtCore/QList>

/*!
 * \enum SlKcValueItemEnum
 *
 * declaration of value item in data objects.
 */
enum SlKcValueItemEnum
{
   /*! name of data element used by kin. chain, kin. chain element,
    * prot. area and prot. area element
    */
   SL_KC_ITEM_NAME = 1,
   //! offset/direction vec. for kin. chain element
   SL_KC_ITEM_OFF_DIR_VEC_X,  
   SL_KC_ITEM_OFF_DIR_VEC_Y,   
   SL_KC_ITEM_OFF_DIR_VEC_Z,   
   //! name of axis for kin. chain element
   SL_KC_ITEM_AXIS,
   //! axis offset for kin. chain element
   SL_KC_ITEM_AXIS_OFF,
   //! name of first prot. area element for prot. area
   SL_KC_ITEM_FIRST_PROT_ELEM,
   //! color value for prot. area and prot. area element
   SL_KC_ITEM_COLOR,
   //! transparency value for prot. area and prot. area element
   SL_KC_ITEM_COLOR_ALPHA,
   //! color inheritance for prot. area element from prot. area
   SL_KC_ITEM_PARENT_COLOR,
   //! level of detail for prot. area and prot. area element
   SL_KC_ITEM_D_LEVEL,
   //! level of detail inheritance for prot. area element form prot. area
   SL_KC_ITEM_PARENT_D_LEVEL,
   //! plc bit number for prot. area
   SL_KC_ITEM_BIT_NO,
   //! init stat for prot. area
   SL_KC_ITEM_INIT_STAT,
   //! tool index for prot. area
   SL_KC_ITEM_INDEX_1,
   SL_KC_ITEM_INDEX_2,
   SL_KC_ITEM_INDEX_3,
   //! usage for prot. area element
   SL_KC_ITEM_USAGE,
   //! body parameter for prot. area element
   SL_KC_ITEM_PARAMETER_1,
   SL_KC_ITEM_PARAMETER_2,
   SL_KC_ITEM_PARAMETER_3,
   SL_KC_ITEM_LENGTH_X,
   SL_KC_ITEM_WIDTH_Y,
   SL_KC_ITEM_HEIGHT_Z,
   SL_KC_ITEM_RADIUS,
   SL_KC_ITEM_RADIUS1,
   SL_KC_ITEM_RADIUS_UPPER,
   SL_KC_ITEM_RADIUS_LOWER,

   //! offset vector for prot. area element
   SL_KC_ITEM_OFFSET_X,
   SL_KC_ITEM_OFFSET_Y,
   SL_KC_ITEM_OFFSET_Z,
   //! direction vector for prot. area element
   SL_KC_ITEM_ROT_AXIS_X,
   SL_KC_ITEM_ROT_AXIS_Y,
   SL_KC_ITEM_ROT_AXIS_Z,
   SL_KC_ITEM_AXIS_X,
   SL_KC_ITEM_AXIS_Y,
   SL_KC_ITEM_AXIS_Z,

   //! angle for prot. area element
   SL_KC_ITEM_ROT_ANGLE,
   //! first prot. area for coll. pair
   SL_KC_ITEM_FIRST_AREA,
   //! second prot. area for coll. pair
   SL_KC_ITEM_SECOND_AREA,
   //! safety distance for coll. pair
   SL_KC_ITEM_SAFETY_DIST,
   //! file name
   SL_KC_ITEM_FILE_NAME,
   //! real path of name
   SL_KC_ITEM_REAL_PATH_OF_FILE,

   //! index of switch
   SL_KC_ITEM_SWITCH_INDEX,
   //! position of switch (state)
   SL_KC_ITEM_SWITCH_POSITION,

   //! selected item
   SL_KC_ITEM_SELECTED_NAME,
   //! name list
   SL_KC_ITEM_NAME_LIST,
   //! show name for collision pairs
   SL_KC_ITEM_NAME_SHOW,
   //! name of first chain element
   SL_KC_ITEM_FIRST_NAME,
   //! name of stl file directory for ini-Datafile
   SL_KC_ITEM_STL_DIR,
};
Q_DECLARE_FLAGS(SlKcValueItem, SlKcValueItemEnum);
Q_DECLARE_OPERATORS_FOR_FLAGS(SlKcValueItem);

/*!
 * \typedef QList<SlKcValueItem> SlKcValueItemList
 *
 * declares list of value items
 */
typedef QList<SlKcValueItem> SlKcValueItemList;

/*!
 * \class SlKcBaseObject
 *
 * Basis class for data object in SlKcLogic
 */
class SL_KC_LOGIC_EXPORT SlKcBaseObject : public SlStepSharedData
{
public:
   ///////////////////////////////////////////////////////
   // CONSTRUCTOR / DESTRUCTOR
   ///////////////////////////////////////////////////////
   /*!
    * \fn SlKcBaseObject()
    *
    * Default constructor
    */
   SlKcBaseObject()
      : m_nObjectID(-1),
        m_attribType(0)
   {
   }

   /*!
    * \fn virtual ~SlKcBaseObject()
    *
    * Default destructor
    */
   virtual ~SlKcBaseObject(void)
   {
   }

   ///////////////////////////////////////////////////////
   // PUBLIC MEMBERS
   ///////////////////////////////////////////////////////

   /*!
    * \fn virtual int type() const = 0
    *
    * \return type of object
    *
    * this pure virtual function returns type of data object element.
    */
   virtual int type() const = 0;

   /*!
    * \fn virtual setAttribType(int nAttribType)
    * 
    * \param [in] nAttribType    attributes Flag
    *
    * setter for AttributesFlag.
    */
   virtual void setAttribType(int nAttribType)
   {
      m_attribType = SL_KC_ATTRIB_TYPE(nAttribType);
   }

   /*!
    * \fn virtual QString dataToString(int nIndex, bool bNoParallel = false) const
    *
    * \param [in] nIndex         nc index of data set
    * \param [in] bNoParallel    flag to empty nk_parallel value, default false
    * \return  string with ascii data set
    *
    * This function generates ascii code of data. If there is no data returned string is empty.
    */
   virtual QString dataToString(int nIndex, bool bNoParallel = false, bool bNppAsModel = false) const = 0;

   /*!
    * \fn void setObjectID(const qint32 nID)
    *
    * \param [in] nID      global id for object
    *
    * setter for global id of object.
    */
   void setObjectID(const qint32 nID)
   {
      m_nObjectID = nID;
   } // <-- SlKcBaseObject::setObjectID()


   /*!
    * \fn qint32 objectID() const
    *
    *  \return global id of object
    *
    * getter for global id of object.
    */
   qint32 objectID() const
   {
      return m_nObjectID;
   } // <-- SlKcBaseObject::objectID()

   /*!
    * \fn virtual SlKcValueItemList valueItems() const = 0
    *
    * \return list of value items
    *
    * This function returns list with value items which are accessible 
    * on this object.
    */
   virtual SlKcValueItemList valueItems() const = 0;

   /*!
    * \fn virtual long value(const SlKcValueItem& rItem, QVariant& rvValue) const = 0;
    *
    * \param [in] rItem       value item we want to get
    * \param [out] rvValue    return value for value item
    *
    * \return 0L if value is returned or -1L if value item is not provided by object.
    *
    * This function returns value \a rvValue for value item \a rItem. Is value item 
    * not supported by object we return -1L as error code else 0L.
    * Is returned value \a rvValue a vector we return a list with values in order of vector 0, 1, etc.
    */
   virtual long value(const SlKcValueItem& rItem, QVariant& rvValue) const = 0;

   /*!
    * \fn virtual long setValue(const SlKcValueItem& rItem, const QVariant& rvValue) = 0
    *
    * \param [in] rItem       value item we want to set
    * \param [in] rvValue     value of item we want to set
    *
    * \return 0L if value is set or -1L if value item is not provided by object.
    *
    * This function sets value \a rvValue for value item \a rItem. Is value item not 
    * supported by object we return -1L as error code else 0L.
    * Is value to set a vector we expect a list of values in order of vector 0, 1, etc.
    */
   virtual long setValue(const SlKcValueItem& rItem, const QVariant& rvValue) = 0;

   /*!
    * \fn virtual bool isValueEnabled(const SlKcValueItem& rItem) const
    *
    * \param [in] rItem       value item we check whether is enable
    * \return true   if value item is enable else false.
    *
    * This function checks if in object a value item has a value that makes it disabled
    * f.eg. if prot. area element has color 0 so it gets its color then from protection area
    * including it and is disabled
    */
   virtual bool isValueEnabled(const SlKcValueItem& rItem) const
   {
      return true;
   }

   //////////////////////////////////////////////////////
   // PUBLIC OPERATOR MEMBER
   //////////////////////////////////////////////////////
   /*!
    * \fn virtual bool operator== (const SlKcBaseObject* pOther) const
    *
    * \param [in] pOther      pointer to base object for equation.
    * \return boolean value of equation
    *
    * This operator has to compare two base objects and returns true if both are identical else false.
    */
   virtual bool operator== (const SlKcBaseObject* pOther) const;
   //{
   //   return (this == pOther);
   //}

   /*!
    * \fn virtual bool operator!= (const SlKcBaseObject* pOther) const
    *
    * \param [in] pOther      pointer to base object for equation.
    * \return  boolean value of equation.
    *
    * This operator has to compare two base objects and returns true if both aren't identical else false.
    */
   virtual bool operator!= (const SlKcBaseObject* pOther) const;
   //{
   //   return (this == pOther);
   //}

private:
   //////////////////////////////////////////////////////
   // PRIVATE DATA MEMBER
   //////////////////////////////////////////////////////
   qint32   m_nObjectID; //!< global id of object

protected:
   //////////////////////////////////////////////////////
   // PROTECTED DATA MEMBER
   //////////////////////////////////////////////////////
   int      m_attribType;  //!< attribute type of object e.g. SL_KC_NP_PARALLEL_ELEM

}; // <-- class SlKcBaseObject

#endif // <-- SL_KC_BASE_OBJECT_H
