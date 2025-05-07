///////////////////////////////////////////////////////////////////////////////
/*! \file   slardtree.h
*  \author Sven Illner, Harald Amrehn
*  \date   11.01.2010
*  \brief  Class definition file for class SlArdTree.
*
*  This file is part of the HMI Solutionline services.
*
*  (C) Copyright Siemens AG A&D MC 2010. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_ARDTREE_H_
#define SL_ARDTREE_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if !defined(SL_ARD_TREE_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#     ifdef SLARDTREE_EXPORTS
#       define SL_ARD_TREE_EXPORT  __declspec(dllexport)
#     else
#       define SL_ARD_TREE_EXPORT  __declspec(dllimport)
#     endif
#   else// Linux / MAC: no Export Makro
#     define SL_ARD_TREE_EXPORT
#   endif
#endif

#if !defined(SL_ARD_TREE_EXTERN)
#   if defined(WIN32) || defined(WIN64)
#     ifdef SLARDTREE_EXPORTS
#       define SL_ARD_TREE_EXTERN
#     else
#       define SL_ARD_TREE_EXTERN  extern
#     endif
#   else// Linux / MAC: no Export Makro
#     define SL_ARD_TREE_EXTERN
#   endif
#endif

#include <QtCore/QString>
#include <QtCore/QFile>


//////////////////////////////////////////////////////////////////////////////
// Class-definition of archive-tree handler
//////////////////////////////////////////////////////////////////////////////
class SL_ARD_TREE_EXPORT SlArdTree
{
public:

  SlArdTree();
  ~SlArdTree();

  /*! \fn createObject(const char* szCallerName);
  *  \retval the pointer to the created SlArdTree;  don't forget to delete this pointer after use with deleteObject
  *   creator function
  */
  static SlArdTree* createObject(const QString strCallerName);

  /*! \fn deleteObject(SlArdTree*& rpSlArdTree);
  *   deletes the pointer returned from createObject and set it to zero;
  *   delete function
  */
  static void deleteObject(SlArdTree*& rpSlArdTree);

  static long Pack(const QString& rstrFile, const QString& rstrDir, const char *creator, const char *comment);
  static long Unpack(const QString& rstrFile, const QString& rstrDir, char *creator, char *comment);
};

#endif // SL_ARDTREE_H_
