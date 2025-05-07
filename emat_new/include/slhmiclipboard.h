/*! \file slhmiclipboard.h
 *  \author Laszlo Federics, Mario Roessel
 *  \date   19.03.2013
 *  \brief  Header file for class SlHmiClipboard
 *  This file is part of the solution line editor widget.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */

#ifndef SL_HMI_CLIPBOARD_H_INCLUDED
#define SL_HMI_CLIPBOARD_H_INCLUDED

#if !defined(SL_HMI_EXPORT)
#   if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT  __declspec(dllexport)
#       else
#           define SL_HMI_EXPORT  __declspec(dllimport)
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif


#include <QtCore/QString>

/*! \class SlHmiClipboard
    \brief A thin wrapper class for accessing the global clipboard for large texts

    This class is used to access the global application clipboard (QClipboard) for texts.
    The global application clipboard should only be accessed from the GUI thread
    (main thread of the application). This class ensures that the clipboard is
    accessed only from the main thread. If a function of this class is called from
    a thread other than the main thread, it won't do anything, just raise an assert.\n
    Linux embedded has only a very limited global clipboard (8KB resp. 4KB unicode string).
    If the text for the clipboard is larger than the size QClipboard can handle then this
    class will use an internal clipboard.\n
*/
class SL_HMI_EXPORT SlHmiClipboard
{
public:

  /*! Sets the text of the clipboard.\n
      This function should only be called from the GUI thread.
  */
  static void setText(const QString& strText);


  /*! Gets the text from the clipboard.
      This function should only be called from the GUI thread.
  */
  static QString text(void);


  /*! Clears the content of the clipboard.
      This function should only be called from the GUI thread.
  */
  static void clear(void);

private:
  /*! Creates the clipboard object.
   */
  SlHmiClipboard(void);


  /*! Destroys the object. The signals are automatically disconnected.
  */
  ~SlHmiClipboard(void);


  /*! Disable creating a copy is this class by declaring the copy constructor
      as a private member. The copy constructor is not implemented
  */
  SlHmiClipboard(const SlHmiClipboard& copy);


  /*! Disable creating a copy is this class by declaring the operator=
      as a private member. The operator= is not implemented
  */
  SlHmiClipboard& operator=(const SlHmiClipboard& copy);

private:

  /*! Internal helper function used for tracing.
      Returns the content of the clipboard(\a strClipboard) in an elided format:
      - if the clipboard contains only one line, then the first 10 characters of
        that line
      - if the clipboard contains more lines, then the first 10 charaters of the
        first line and the first chacters of the last line; and also the number of
        lines
  */
  static QString elidedClipboardContent(const QString& strClipboard);


  /*! The one an only instance of the clipboard.
  */
  static SlHmiClipboard m_s_instance;


  /*! If the global application clipboad would be too small for us
      (on Linux Embedded it is only 4K), then we use this internal string
      as our own clipboard
  */
  static QString m_strOwnClipboard;

};

#endif // SL_HMI_CLIPBOARD_H_INCLUDED
