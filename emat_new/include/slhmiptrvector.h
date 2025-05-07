///////////////////////////////////////////////////////////////////////////////
/*! \file	slhmiptrvector.h
 *  \author Mario Roessel
 *  \date   06.07.2004
 *  \brief	Class definition file for class SlHmiPtrVector.
 *
 *  This file is part of the HMI Solutionline GUI Framework.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_GFW_PTR_VECTOR_H
#define SL_GFW_PTR_VECTOR_H

#include <QtCore/QVector>

/*! \class SlHmiPtrVector slhmiptrvector.h
 *  \brief An extended vector class for the GUI Framework.
 *
 *  This class is an extended vector class for the GUI Framework.
*/
template <class type>
class SlHmiPtrVector : public QVector<type*>
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // DATASTREAM OPERATORS
    ///////////////////////////////////////////////////////////////////////////

    friend QDataStream& operator<<(QDataStream& rStream, SlHmiPtrVector& rPtrVector)
    {
        rStream << rPtrVector.count();
        for (int i = 0; i < rPtrVector.count(); i++)
        {
            type* pType = rPtrVector[i];
            rStream << *pType;
        }
        return rStream;
    }

    friend QDataStream& operator>>(QDataStream& rStream, SlHmiPtrVector& rPtrVector)
    {
        qint32 nCount = 0;
        rStream >> nCount;
        rPtrVector.resize(nCount);
        for (int i = 0; i < rPtrVector.count(); i++)
        {
            type* pType = new type;
            rStream >> *pType;
            rPtrVector[i] = pType;
        }
        return rStream;
    }
};

#endif // SL_GFW_PTR_VECTOR_H

