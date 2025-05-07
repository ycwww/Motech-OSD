///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   15.08.2012
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG I DT MC 2012. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_SIM_POINTER_H
#define SL_SIM_POINTER_H

/// @brief C++-style auto_ptr / unique_ptr
///
/// Features:
/// @li default-constructed to 0
/// @li automatic conversion to plain pointer
/// @li delete upon destruction
/// @li no copying, no assignment, except through #release()
/// @li assignment of plain pointers for SL_NEW macro
template<typename T>
class SlSimPointer
{
public:
   SlSimPointer(T* p = 0)
      : m_p(p)
   {
   }

   T* get() const
   {
      return m_p;
   }

   operator T*() const
   {
      return get();
   }

   T* operator->() const
   {
      return get();
   }

   T& operator*() const
   {
      return *get();
   }

   T* release()
   {
      T* p = m_p;
      m_p = 0;
      return p;
   }

   void reset(T* p = 0)
   {
      if (get())
      {
         delete get();
      }
      m_p = p;
   }

   T* operator=(T* p)
   {
      reset(p);
      return p;
   }

   ~SlSimPointer()
   {
      reset();
   }

private:

   // no copying
   SlSimPointer(const SlSimPointer&);
   // no assignment
   SlSimPointer& operator=(const SlSimPointer&);

   T* m_p;
};

template<class T>
void SL_SIM_DELETE(SlSimPointer<T> &p)
{
   p.reset();
}

#define SL_SIM_HEAP_VAR(type, name) \
  SlSimPointer<type> name ## _p; \
  SL_NEW_RETURN(name ## _p, type, SL_ERR_FAIL); \
  type& name = *name ## _p;

/// Resets a pointer to null when it goes out of scope.
template<typename T>
class SlSimPointerResetter
{
public:
   SlSimPointerResetter(T*& p)
      : m_p(p)
   {
   }

   ~SlSimPointerResetter()
   {
      m_p = 0;
   }

private:
   T*& m_p;
};

#endif // SL_SIM_POINTER_H
