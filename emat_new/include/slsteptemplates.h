///////////////////////////////////////////////////////////////////////////////
/*! \file   slsteptemplates.h
 *  \author Harald Vieten
 *  \date   25.04.2009
 *  \brief  Some definition of templates used by step editor
 *
 *  This file is part of the HMI Solutionline StepEditor.
 *
 * (C) Copyright Siemens AG A&D MC 2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_STEP_TEMPLATES_H
#define SL_STEP_TEMPLATES_H


#include <QtCore/QMap>


///////////////////////////////////////////////////////////////////////////////
//    TEMPLATE CLASS  SlStepProxyPointer
///////////////////////////////////////////////////////////////////////////////
/*!
 *  \class SlStepProxyPointer
 *
 *  Defines a template class that provides a generic proxy pointer for the
 *  stored pointer. It provides access methods to access the stored pointer 
 *  transparently. 
 *  This template just steres a pointer. Responsible for setting and deleting
 *  of the stored pointer are the derived classes.
 */
template <class T>
class SlStepProxyPointer
{
public:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn SlStepProxyPointer (T* pT = 0)
    *
    *  \param  pT    pointer to store
    *
    *  Default constructor. This creates a generic proxy pointer for type \a T
    *  and initialises it with \a pT.
    */
   SlStepProxyPointer (T* pT = 0)
      : m_pT(pT)
   {}


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn bool isNull (void) const
    *
    *  \return Returns true if no pointer is stored into this proxy pointer;
    *          otherwise it returns false.
    */
   bool isNull (void) const
   {
      return (m_pT == 0);
   }

   /*!
    *  \fn T* get (void) const
    *
    *  \return Returns the stored pointer. If no pointer is stored into this
    *          proxy pointer it returns 0.
    */
   T* get (void) const
   {
      return m_pT;
   }


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC OPERATORS TO ACCESS THE STORED POINTER TRANSPARENTLY
   ///////////////////////////////////////////////////////////////////////////

   operator T* () const
   {
      return m_pT;
   }

   T& operator* () const
   {
      return *m_pT;
   }

   T* operator-> () const
   {
      return m_pT;
   }

protected:

   ///////////////////////////////////////////////////////////////////////////
   // PROTECTED METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn void set (T* pT)
    *
    *  \param  pT    pointer to store
    *
    *  (Re-)Sets the stored pointer. Only derived classes can (re-)set the
    *  pointer to grand maximum control over the pointer insede the proxy
    *  pointer.
    */
   void set (T* pT)
   {
      m_pT = pT;
   }

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   T*    m_pT;    //!< stored pointer

}; // <-- class SlStepProxyPointer


///////////////////////////////////////////////////////////////////////////////
//    TEMPLATE CLASS  SlStepScopedPointer
///////////////////////////////////////////////////////////////////////////////

/*!
 *  \class SlStepScopedPointer
 *
 *  Defines a template class that provides a simpler kind of a smart pointer. 
 *  It just calls \ref delete on the stored pointer when the 
 *  SlStepScopedPointer get out of scope, e.g. when SlStepScopedPointer is 
 *  deleted itself.
 *
 *  There is no reference counting. There is no possiblity to copy a 
 *  SlStepScopedPointer
 */
template <class T>
class SlStepScopedPointer : public SlStepProxyPointer<T>
{
public:
   
   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn explicit SlStepScopedPointer (T* pPointer = 0)
    *
    *  \param pPointer     pointer to store
    *
    *  Default constructor. This creates the scoped pointer object for given
    *  pointer \a pPointer.
    */
   explicit SlStepScopedPointer (T* pPointer = 0)
      : SlStepProxyPointer<T>(pPointer)
   {}

   /*!
    *  \fn ~SlStepScopedPointer ()
    *
    *  Destructor. This calls \ref delete on the stored pointer.
    */
   ~SlStepScopedPointer ()
   {
      delete SlStepProxyPointer<T>::get();
   }

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE OPERATORS TO DISALLOW COPIING
   ///////////////////////////////////////////////////////////////////////////

   /* copy contructor is not allowed */
   SlStepScopedPointer (const SlStepScopedPointer&);

   /* assingment is not allowed */
   SlStepScopedPointer& operator= (const SlStepScopedPointer&);

}; // <-- class SlStepScopedPointer


///////////////////////////////////////////////////////////////////////////////
//    TEMPLATE CLASS  SlStepSharedPointer
///////////////////////////////////////////////////////////////////////////////

/*!
 *  \class SlStepSharedData
 *
 *  Defines the base class for a shared data object that can be handled by 
 *  smart pointer template \sa SlStepSharedPointer. 
 */
class SlStepSharedData
{
public:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn SlStepSharedData ()
    *
    *  Default constructor. It initialises the reference counter.
    */
   SlStepSharedData ()
   {}

   /*!
    *  \fn virtual ~SlStepSharedData()
    *
    *  Destructor. Has to be virtual.
    */
   virtual ~SlStepSharedData ()
   {}


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC ACCESSORD
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn void addRef (void)
    *  
    *  Adds a reference to this shared data object.
    */
   void addRef (void)
   {
      m_refCnt.ref();
   }

   /*!
    *  \fn void removeRef (void)
    *  
    *  Removes a reference from this shared data object. If reference counter
    *  decreases to 0 it destroys this shared data object. 
    */
   void removeRef (void)
   {
      Q_ASSERT(0 < m_refCnt);

      bool bNonZero = m_refCnt.deref();
      if (false == bNonZero)
      {
         delete this;
      }
   }

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   QAtomicInt  m_refCnt;         //!< the reference counter


   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   // assignment operator is not allowed
   SlStepSharedData& operator= (const SlStepSharedData&);

   // copy constructor is not allowed
   SlStepSharedData (const SlStepSharedData&);

}; // <-- class SlStepSharedData


/*!
 *  \class SlStepSharedPointer
 *
 *  Defines a template class that provides a smart pointer to a shared data 
 *  object. The shared data object has to be derived from \sa SlStepSharedData.
 *  With help from that base class it also provides a reference counting. So,
 *  if that counter decreased to 0 the shared data object is detroyed with 
 *  delete.
 *
 *  This smart pointer is a good choice if the shared object is filled only 
 *  once at creation time and than only read accesses are performed.
 */
template <typename T, typename DATA = SlStepSharedData>
class SlStepSharedPointer : public SlStepProxyPointer<T>
{
public:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn explicit SlStepSharedPointer (T* pT = 0)
    *
    *  \param pT     pointer to shared data object
    *
    *  Constructor. Creates a smart pointer for given shared data object \a pT. 
    */
   explicit SlStepSharedPointer (T* pT = 0)
      : SlStepProxyPointer<T>(0)
   {
      // all is done in assignment operator
      *this = pT;
   }

   /*!
    *  \fn SlStepSharedPointer (const SlStepSharedPointer& rOther)
    *
    *  \param rOther    the other smart pointer
    *
    *  Copy constuctor. Creates a smart pointer to the shared data object from
    *  given smart pointer \a rOther.
    */
   SlStepSharedPointer (const SlStepSharedPointer& rOther)
      : SlStepProxyPointer<T>(0)
   {
      // all is done in assignment operator
      *this = rOther;
   }

   /*!
    *  \fn ~SlStepSharedPointer ()
    *
    *  Destructor. Removes my reference fromshared data object.
    */
   ~SlStepSharedPointer ()
   {
      // not null object
      //  -> remove my reference from stored shared data object
      if (false == SlStepProxyPointer<T>::isNull())
      {
         d()->removeRef();
      }
   }


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC EQUALITY OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   bool operator== (const SlStepSharedPointer& rOther)
   {
      // this smart pointers are the same 
      // when they share the same data object
      return (SlStepProxyPointer<T>::get() == rOther.get());
   }

   bool operator != (const SlStepSharedPointer& rOther)
   {
      // this smart pointers are different
      // when they do not share the same data object
      return (SlStepProxyPointer<T>::get() != rOther.get());
   }


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC ASSIGN OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn SlStepSharedPointer& operator= (const SlStepSharedPointer& rOther)
    *
    *  \param rOther    the other smart pointer
    *
    *  Assigns the shared data object from given smart pointer \a rOther 
    *  to me.
    */
   SlStepSharedPointer& operator= (const SlStepSharedPointer& rOther)
   {
      // do not copy if both share the same data object
      // (witch implicites that I do not copy myself)
      if (*this != rOther)
      {
         // not null object
         // -> remove my reference from stored data object
         if (false == SlStepProxyPointer<T>::isNull())
         {
            d()->removeRef();
         }

         // copy pointer
         SlStepProxyPointer<T>::set(rOther.get());

         // received not null object
         //  -> add a reference to the data object
         if (false == SlStepProxyPointer<T>::isNull())
         {
            d()->addRef();
         }
      }

      return *this;
   }

   /*!
    *  \fn SlStepSharedPointer& operator= (T* pT)
    *
    *  \param pT     pointer to shared data object
    *
    *  Assigns the given shared data object \a pT to me.
    */
   SlStepSharedPointer& operator= (T* pT)
   {
      // not null object
      // -> remove my reference from stored data object
      if (false == SlStepProxyPointer<T>::isNull())
      {
         d()->removeRef();
      }

      // copy pointer
      SlStepProxyPointer<T>::set(pT);

      // received not null object
      //  -> add a reference to the data object
      if (false == SlStepProxyPointer<T>::isNull())
      {
         d()->addRef();
      }

      return *this;
   }

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE HELPER METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn inline SlStepSharedData* d (void) const
    *
    *  \return Returns a pointer to the stored data object, 
    *          but casted to the shared data object base class.
    */
   inline DATA* d (void) const
   {
      return (DATA*) SlStepProxyPointer<T>::get();
   }

}; // <-- class SlStepSharedPointer

///////////////////////////////////////////////////////////////////////////////
//    TEMPLATE CLASS  SlStepDestroyer
///////////////////////////////////////////////////////////////////////////////

/*!
 *  \class SlStepDestroyer
 *
 *  Defines a template to destroy an object of type T when library is unloaded
 */
template<typename T>
class SlStepDestroyer
{
public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn SlStepLogicDestroyer (T* pObject)
    *
    *  \param pObject      object to destroy
    *
    *  Constructor. Creates destroyer for given object \a pObject.
    */
   SlStepDestroyer (T* pObject)
      : m_pObject(pObject)
   {}

   /*! \fn ~SlStepLogicDestroyer ();
    *
    *  Destructor
    */
   ~SlStepDestroyer ()
   {
      delete m_pObject;
   }

private:

   T* m_pObject;  //!< object to destroy

}; // <-- class SlStepDestroyer


///////////////////////////////////////////////////////////////////////////////
//    TEMPLATE CLASS  SlStepPointerMap
///////////////////////////////////////////////////////////////////////////////

/*!
 *  \class SlStepPointerMap
 *
 *  Defines a map that stores pointers to \a VALUE type together with its 
 *  \a KEY type. When the map is destoyed it call delete() on all stored 
 *  pointers.
 */
template<typename KEY, typename VALUE>
class SlStepPointerMap
{
public:

   ///////////////////////////////////////////////////////////////////////////
   // ENUMS AND TYPEDEFS 
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \typedef key_type
    *
    *  Defines the key type.
    */
   typedef KEY key_type;

   /*!
    *  \typedef value_type
    *
    *  Defines the value type.
    */
   typedef VALUE* value_type;

   /*!
    *  \typedef const_iterator
    *
    *  Defines the constant iterator type.
    */
   typedef typename QMap<KEY,VALUE*>::const_iterator const_iterator;

   /*!
    *  \typedef iterator
    *
    *  Defines the iterator type.
    */
   typedef typename QMap<KEY,VALUE*>::iterator iterator;


   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn ~SlStepPointerMap ()
    *
    *  Destuctor. Destroys map but with calling delete() on each stored 
    *  pointer.
    */
   ~SlStepPointerMap ()
   {
      clear();

   } // <-- SlStepPointerMap::~SlStepPointerMap ()


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn bool isEmpty (void) const
    *
    *  \return Returns true if the map contains no stored pointers; otherwise 
    *          it returns false.
    */
   bool isEmpty (void) const
   {
      return m_map.isEmpty();
   }

   /*!
    *  \fn int size (void) const
    *
    *  \return Returns the size of the map.
    */
   int size (void) const
   {
      return m_map.size();
   }

   /*!
    *  \fn void insert (const KEY& rKey, VALUE* pValue)
    *
    *  \param rKey      key to store pointer for
    *  \param pValue    pointer to store
    *
    *  Stores given pointer \a pValue for given key \a rKey into map. If a 
    *  pointer already exists for \a rKey delete() is called for this pointer.
    */
   void insert (const KEY& rKey, VALUE* pValue)
   {
      if (true == m_map.contains(rKey))
      {
         delete m_map.value(rKey);
      }

      m_map.insert(rKey, pValue);
   }

   /*!
    *  \fn void remove (const KEY& rKey)
    *
    *  \param rKey      key to remove pointer for
    *
    *  Removes the pointer stored for given key \a rKey from map. Before 
    *  removing delete() is called on stored pointer.
    */
   void remove (const KEY& rKey)
   {
      if (true == m_map.contains(rKey))
      {
         delete m_map.value(rKey);
         m_map.remove(rKey);
      }
   }

   /*!
    *  \fn bool contains (const KEY& rKey) const
    *
    *  \param rKey      key to query
    *  
    *  \return Returns true if a pointer is stored for given key \a rKey; 
    *          otherwise it returns false.
    */
   bool contains (const KEY& rKey) const
   {
      return m_map.contains(rKey);
   }

   /*!
    *  \fn VALUE* value (const KEY& rKey) const
    *
    *  \param rKey      key to get pointer for
    *
    *  \return Returns the pointer for given key \a rKey. If no pointer is
    *          stored for \a rKey 0 is returned.
    */
   VALUE* value (const KEY& rKey) const
   {
      if (true == m_map.contains(rKey))
      {
         return m_map.value(rKey);
      }

      return 0;
   }
   
   /*!
    *  \fn QList<KEY> keys (void) const
    *
    *  \return Returns a list of all keys pointers are stored for in map.
    */
   QList<KEY> keys (void) const
   {
      return m_map.keys();
   }
   
   /*!
    *  \return Returns a list of all pointers stored in the map.
    */
   QList<VALUE*> values (void) const
   {
      return m_map.values();
   }

   /*!
    *  \fn const_iterator constBegin() const
    *
    *  \return Returns a constant iterator on the first pointer in map.
    */
   const_iterator constBegin() const
   {
      return m_map.constBegin();
   }

   /*!
    *  \fn const_iterator constEnd() const
    *
    *  \return Returns a constant iterator to the last pointer in map.
    */
   const_iterator constEnd() const
   {
      return m_map.constEnd();
   }

   /*!
    *  \fn iterator begin() const
    *
    *  \return Returns an iterator on the first pointer in map.
    */
   iterator begin() const
   {
      return m_map.begin();
   }

   /*!
    *  \fn iterator end() const
    *
    *  \return Returns a constant iterator to the last pointer in map.
    */
   iterator end() const
   {
      return m_map.end();
   }

   /*!
    *  \fn void clear (void)
    *
    *  Clears the map but with calling delete() on each stored pointer.
    */
   void clear (void)
   {
      // are objects stored in given map?
      if (false == m_map.isEmpty())
      {
         // call delete on each stored object
         iterator it = m_map.begin();
         for (;it != m_map.end(); ++it)
         {
            delete it.value();
         }

         // all stored objects deleted 
         //  -> clear map itself
         m_map.clear();
      }
   }

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   QMap<KEY,VALUE*>  m_map;      //!< the map

}; // <-- class SlStepPointerMap

#endif // ! SL_STEP_TEMPLATES_H

