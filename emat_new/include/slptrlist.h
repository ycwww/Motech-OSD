/*! \file	sledptrlist.h
*  \author Laszlo Federics
*  \date   26.01.2006
*  \brief	List of pointers.
*  This file is part of the solution line editor widget.
*
*  Implementation of a pointer list using the Qt QList template.
*
*  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/

#ifndef SLEDPTRLIST_H
#define SLEDPTRLIST_H

#include <QtCore/QList>

template <typename T>
class SlPtrList
{
public:

  SlPtrList() : m_bAutoDelete(false)
  {
  }

  void setAutoDelete(bool bAutoDelete)
  {
    m_bAutoDelete = bAutoDelete;
  }

  ~SlPtrList()
  {
    if (m_bAutoDelete)
    {
      int nIdx;

      for (nIdx = 0; nIdx < m_PointerList.size(); nIdx++)
      {
        T* ptr = m_PointerList.at(nIdx);
        delete ptr;
      }

      m_PointerList.clear();
    }
  }

  bool remove(uint index)
  {
    T* pT = m_PointerList.takeAt(index);
    if (m_bAutoDelete)
    {
      delete pT;
    }
    return true;
  }

  void clear()
  {
    int nIdx;

    for (nIdx = 0; nIdx < m_PointerList.size(); nIdx++)
    {
      T* ptr = m_PointerList.at(nIdx);
      delete ptr;
    }

    m_PointerList.clear();
  }

  int count() const
  {
    return m_PointerList.count();
  }

  int size() const
  {
    return m_PointerList.size();
  }

  T* at(int nIndex) const
  {
    return m_PointerList.at(nIndex);
  }

  void insert(int nIndex, T* value)
  {
    m_PointerList.insert(nIndex, value);
  }

  T* takeAt(int nIndex)
  {
    return m_PointerList.takeAt(nIndex);
  }

  T* takeLast()
  {
    return m_PointerList.takeLast();
  }

  T* first()
  {
    return m_PointerList.first();
  }

  T* last()
  {
    return m_PointerList.last();
  }

  bool isEmpty() const
  {
    return m_PointerList.isEmpty();
  }

  void append(T* value) 
  {
    m_PointerList.append(value);
  }

  void prepend(T* value) 
  {
    m_PointerList.prepend(value);
  }

  void removeFirst()
  {
    remove(0);
  }

  void removeLast()
  {
    remove(m_PointerList.size()-1);
  }

private:

  QList<T*> m_PointerList;
  
  bool m_bAutoDelete;
};

#endif
