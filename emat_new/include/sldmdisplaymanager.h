///////////////////////////////////////////////////////////////////////////////
/*! \file	sldmdisplaymanager.h
 *  \brief	
 *  This file contains the interface to the display manager, who is
 *  responsible for layout of the display (position of operate, sidescreens, menues)
 *  
 *  (C) Copyright Siemens AG A&D MC 2003-2017. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#ifndef _SL_DM_DISPLAYMANAGER_H_
#define _SL_DM_DISPLAYMANAGER_H_


#if defined WIN32
#  if defined (SL_DM_BUILD_DLL)
#    define SlDmExport __declspec (dllexport)
#  else
#    define SlDmExport __declspec (dllimport)
#  endif
#else
#  define SlDmExport
#endif

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QColor>

class SlDmDisplayManagerPrivate;

/*! \class SlDmDisplayManager    sldmdisplaymanager.h
 *
 *  This class represents the Display manager, responsible for managing the display layouts
*/
class SlDmExport SlDmDisplayManager : public QObject
{
  Q_OBJECT
public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn  SlDmDisplayManager();
   *
   *  Constructor
   */
  SlDmDisplayManager(QObject* pParent = Q_NULLPTR);

  /*! \fn ~SlDmDisplayManager();
   *
   *  Destructor
   *
   */
  virtual ~SlDmDisplayManager();

  /*! \fn  SlDmDisplayManager(SlDmDisplayManagerPrivate* pPrivate);
   *
   *  Constructor with own private object (internal)
   */
  SlDmDisplayManager(SlDmDisplayManagerPrivate* pPrivate);

  /*! \fn  SlDmDisplayManager(const SlDmDisplayManager& rCopy);
   *
   *  Copy-Constructor
   */
  SlDmDisplayManager(const SlDmDisplayManager& rCopy);

  /*! \fn  SlDmDisplayManager& operator=(const SlDmDisplayManager& rCopy);
   *
   *  Assignment operator
   */
  SlDmDisplayManager& operator=(const SlDmDisplayManager& rCopy);


  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn  long executeAction(const QString& szAction);
   *
   *  This function executes a action command, like it is used in onClicked argument 
   *  of a menu item in a display configuration file
   *  This is ";"-separated list of the functions below.
   * 
   *  E.g. "showDisplay(myDisplay);showApp(f1, myApp);sendCmd(myApp,openFile);showMenu(f2, menu)"
   *
   *  \param  szAction                        the action string to execute
   *
   *  \retval long                            error code, >= 0 on success
   */
  long executeAction(const QString& szAction);

  /*! \fn  long showDisplay(const QString& szDisplay, bool bNoRefresh = false);
   *
   *  Switches to the display layout with the given name (and extension).
   *
   *  \param  szDisplay                       the name of the display layout to show
   *  \param  bNoRefresh                      if true, the needed display refresh is permitted (call refreshDisplay() later)
   *
   *  \retval long                            error code, >= 0 on success
   */
  long showDisplay(const QString& szDisplay, bool bNoRefresh = false);

  /*! \fn  long getActiveDisplay(QString& rszDisplay);
   *
   *  Gets the name of the currently active display layout
   *
   *  \param  rszDisplay                      buffer for the active display layout
   *
   *  \retval long                            error code, >= 0 on success
   */
  long getActiveDisplay(QString& rszDisplay) const;

  /*! \fn  long showApp(const QString& szDestFrame, const QString& szApp, bool bNoRefresh = false);
   *
   *  Shows the app szApp in the given destination frame. If possible the app, that has been in the destination
   *  frame before, swaps the position with szApp
   *
   *  \param  szDestFrame                     the name of the destination frame
   *  \param  szApp                           the name of the app to show
   *  \param  bNoRefresh                      if true, the needed display refresh is permitted (call refreshDisplay() later)
   *
   *  \retval long                            error code, >= 0 on success
   */
  long showApp(const QString& szDestFrame, const QString& szApp, bool bNoRefresh = false);

  /*! \fn  long showPopup(const QString& szPopupFrame, const QString& szApp, bool bNoRefresh = false);
   *
   *  Shows the app szApp in the given destination popup frame. In contrast to showApp(), the destination 
   *  frame need not be part of the active display layout. Instead it is shown as an overlapped window.
   *
   *  \param  szPopupFrame                    the name of the destination frame
   *  \param  szApp                           the name of the app to show
   *  \param  bNoRefresh                      if true, the needed display refresh is permitted (call refreshDisplay() later)
   *
   *  \retval long                            error code, >= 0 on success
   */
  long showPopup(const QString& szPopupFrame, const QString& szApp, bool bNoRefresh = false);

  /*! \fn  long hidePopup(const QString& szApp, bool bNoRefresh = false);
   *
   *  Hides the give app in a popup
   *
   *  \param  szApp                           the name of the app to hide, if "" hide all popups
   *  \param  bNoRefresh                      if true, the needed display refresh is permitted (call refreshDisplay() later)
   *
   *  \retval long                            error code, >= 0 on success
   */
  long hidePopup(const QString& szApp, bool bNoRefresh = false);

  /*! \fn  long togglePopup(const QString& szPopupFrame, const QString& szApp, bool bNoRefresh = false);
   *
   *  If the app szApp is not shown in the popup frame, it is shown there (like showPopup). Else it will be hidden.
   *
   *  \param  szPopupFrame                    the name of the destination frame
   *  \param  szApp                           the name of the app to show
   *  \param  bNoRefresh                      if true, the needed display refresh is permitted (call refreshDisplay() later)
   *
   *  \retval long                            error code, >= 0 on success
   */
  long togglePopup(const QString& szPopupFrame, const QString& szApp, bool bNoRefresh = false);

  /*! \fn  long showMenu(const QString& szDestFrame, const QString& szMenu, bool bNoRefresh = false);
   *
   *  Shows the menu szMenu in the given destination frame. 
   *
   *  \param  szDestFrame                     the name of the destination frame
   *  \param  szMenu                          the name of the menu to show
   *  \param  bNoRefresh                      if true, the needed display refresh is permitted (call refreshDisplay() later)
   *
   *  \retval long                            error code, >= 0 on success
   */
  long showMenu(const QString& szDestFrame, const QString& szMenu, bool bNoRefresh = false);

  /*! \fn  long showPopupMenu(const QString& szPopupFrame, const QString& szMenu, bool bNoRefresh = false);
   *
   *  Shows the app szMenu in the given destination popup frame. In contrast to showMenu(), the destination 
   *  frame need not be part of the active display layout. Instead it is shown as an overlapped window.
   *
   *  \param  szPopupFrame                    the name of the destination frame
   *  \param  szMenu                          the name of the menu to show
   *  \param  bNoRefresh                      if true, the needed display refresh is permitted (call refreshDisplay() later)
   *
   *  \retval long                            error code, >= 0 on success
   */
  long showPopupMenu(const QString& szPopupFrame, const QString& szMenu, bool bNoRefresh = false);

  /*! \fn  long hidePopupMenu(const QString& szMenu, bool bNoRefresh = false);
   *
   *  Hides the give menu in a popup
   *
   *  \param  szMenu                          the name of the menu to hide, if "" hide all popups
   *  \param  bNoRefresh                      if true, the needed display refresh is permitted (call refreshDisplay() later)
   *
   *  \retval long                            error code, >= 0 on success
   */
  long hidePopupMenu(const QString& szMenu, bool bNoRefresh = false);

  /*! \fn  long togglePopupMenu(const QString& szPopupFrame, const QString& szMenu, bool bNoRefresh = false);
   *
   *  If the menu szMenu is not shown in the popup frame, it is shown there (like showPopupMenu). Else it will be hidden.
   *
   *  \param  szPopupFrame                    the name of the destination frame
   *  \param  szMenu                          the name of the menu to show
   *  \param  bNoRefresh                      if true, the needed display refresh is permitted (call refreshDisplay() later)
   *
   *  \retval long                            error code, >= 0 on success
   */
  long togglePopupMenu(const QString& szPopupFrame, const QString& szMenu, bool bNoRefresh = false);

  /*! \fn  long sendCmd(const QString& szApp, const QStringList& szArgs);
   *
   *  Sends a command to the given dialog app (commands to process apps are not possible). The dialog 
   *  receives this command in its onMessage() implementation with message type SL_GFW_MSG_DISPCONFIG_CMD.
   *
   *  If the destination app is "OPERATE", the HMI executes a switchToHmiTarget(Area, Dialog, Target, Args) call.
   *
   *  \param  szApp                           the name of the app, that should receive the command
   *  \param  szArgs                          the command arguments of the command
   *
   *  \retval long                            error code, >= 0 on success
   */
  long sendCmd(const QString& szApp, const QStringList& szArgs);

  /*! \fn  long setMirrorMode(bool bMirror, bool bNoRefresh = false);
   *
   *  Activates/Deactivates the mirror mode. If mirror mode is active, all frames of the active display are
   *  mirrored horizontally (frames configured at a left position are shown on the right and vice versa)
   *  You could disable the mirror mode for some displays with the enableMirrorMode property
   *
   *  \param  bMirror                         true activates the mirror mode, false deactivates it
   *  \param  bNoRefresh                      if true, the needed display refresh is permitted (call refreshDisplay() later)
   *
   *  \retval long                            error code, >= 0 on success
   */
  long setMirrorMode(bool bMirror, bool bNoRefresh = false);

  /*! \fn  long getMirrorMode(bool& rbMirror);
   *
   *  Gets the current state of the mirror mode
   *
   *  \param  rbMirror                        buffer for the mirror mode flag
   *
   *  \retval long                            error code, >= 0 on success
   */
  long getMirrorMode(bool& rbMirror) const;

  /*! \fn long getBackgroundColor(QColor& rColor) const;
   *
   *  Gets the configured background color of the current display configuration.
   *
   *  \param  rColor                          buffer for the color
   *
   *  \retval long                            error code, >= 0 on success
   */
  long getBackgroundColor(QColor& rColor) const;

  /*! \fn  long refreshDisplay();
   *
   *  Refreshes the current display layout. Is necessary if you permitted the refresh with the bNoRefresh parameter
   *
   *  \retval long                            error code, >= 0 on success
   */
  long refreshDisplay();

  /*! \fn  long moveTopLevelWindow(const QString& szWindowTitle, const QRect& newGeometry);
   *
   *  Moves and resizes a top level window
   *
   *
   *  \param  szWindowTitle                   unique window title of the top level window
   *  \param  newGeometry                     new geometry of the window in absolute coordinates
   *
   *  \retval long                            error code, >= 0 on success
   */
#ifdef LINUX
  long moveTopLevelWindow(const QString& szWindowTitle, const QRect& newGeometry);
#endif

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
signals:
  /*! \fn  void displayConfigurationChanged(const QString& szDisplayConfig);
   *
   *  This signal is emitted when the display configuration changes e.g. after a tcu switch
   *  szDisplayConfig is empty if there is no display configuration for the active panel
   *
   *  \param  szDisplayConfig         the new display configuration
   */
  void displayConfigurationChanged(const QString& szDisplayConfig);

  /*! \fn  void displayChanged(const QString& szDisplay, const QStringList& szVisibleApps, const QStringList& szVisibleFrames);
   *
   *  This signal is emitted when the shown display and/or shown apps changed. The app and the frame
   *  list have the same length, so e.g. the app szVisibleApps.at(3) is shown in frame szVisibleFrames.at(3)
   *  The mirror mode has no effect on the element order in the lists.
   *
   *  \param  szDisplay         the active display of the current display configuration
   *  \param  szVisibleApps     the list of the visible apps
   *  \param  szVisibleFrames   the list of the visible frames
   */
  void displayChanged(const QString& szDisplay, const QStringList& szVisibleApps, const QStringList& szVisibleFrames);

  /*! \fn  void mirrorModeChanged(bool bMirrorMode);
   *
   *  This signal is emitted when the mirror mode changes
   *
   *  \param  bMirrorMode         new mirror mode
   */
  void mirrorModeChanged(bool bMirrorMode);

protected:
  virtual void customEvent(QEvent* customEvent);

private:
  friend class SlDmDisplayManagerPrivate;
  SlDmDisplayManagerPrivate* m_pData;
};


class SlDmDisplayManagerCallbackV0Private;

/*! \class SlDmDisplayManagerCallbackV0    sldmdisplaymanager.h
 *
 *  This class represents the callback class for display manager signals
*/
class SlDmExport SlDmDisplayManagerCallbackV0
{
public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn  SlDmDisplayManagerCallbackV0();
   *
   *  Constructor
   */
  SlDmDisplayManagerCallbackV0();

  /*! \fn ~SlDmDisplayManagerCallbackV0();
   *
   *  Destructor
   *
   */
  virtual ~SlDmDisplayManagerCallbackV0();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn  void enableCallbacks(bool bEnable);
   *
   *  Enables or disables the call of the virtual function callbacks. 
   *  The callbacks are disabled as default.
   *  The callbacks MUST be disabled before destruction of this object.
   *
   *  \param  bEnable         true: enable callbacks, false: disable it
   */
  void enableCallbacks(bool bEnable);
  
  ///////////////////////////////////////////////////////////////////////////
  // CALLBACKS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn  void displayConfigurationChanged(const QString& szDisplayConfig);
   *
   *  This signal is emitted when the display configuration changes e.g. after a tcu switch
   *  szDisplayConfig is empty if there is no display configuration for the active panel
   *
   *  \param  szDisplayConfig         the new display configuration
   */
  virtual void displayConfigurationChanged(const QString& szDisplayConfig);

  /*! \fn  void displayChanged(const QString& szDisplay, const QStringList& szVisibleApps, const QStringList& szVisibleFrames);
   *
   *  This signal is emitted when the shown display and/or shown apps changed. The app and the frame
   *  list have the same length, so e.g. the app szVisibleApps.at(3) is shown in frame szVisibleFrames.at(3)
   *  The mirror mode has no effect on the element order in the lists.
   *
   *  \param  szDisplay         the active display of the current display configuration
   *  \param  szVisibleApps     the list of the visible apps
   *  \param  szVisibleFrames   the list of the visible frames
   */
  virtual void displayChanged(const QString& szDisplay, const QStringList& szVisibleApps, const QStringList& szVisibleFrames);

  /*! \fn  void mirrorModeChanged(bool bMirrorMode);
   *
   *  This signal is emitted when the mirror mode changes
   *
   *  \param  bMirrorMode         new mirror mode
   */
  virtual void mirrorModeChanged(bool bMirrorMode);

private:
  SlDmDisplayManagerCallbackV0Private* m_pData;
};

#endif // _SL_DM_DISPLAYMANAGER_H_
