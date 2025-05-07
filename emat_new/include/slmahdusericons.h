///////////////////////////////////////////////////////////////////////////////
/*! \file   slmahdusericons.h
 *  \author Ralf Wagner
 *  \date   14.06.2010
 *  \brief  Definition file for class SlMaHdUserIcons
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2010. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_HEADER_USERICONS_H_INCLUDED
#define SL_MA_HEADER_USERICONS_H_INCLUDED

#include <QtCore/QString>
#include <QtCore/QVariant>

#include "slcapdata.h"
#include "slmaformlogicbase.h"
#include "slmalogic.h"
#include "slmalogicdefs.h"

// forward declarations
class SlMaHdUserIconsPrivate;
class SlMaHdUserIconsSingelton;
class SlMaHdUserIconsSingeltonPrivate;

/*! \class  SlMaHdUserIcons
 *  \brief  Gets the settings for the user icons shown in the machine header forms (SlMaHdActProgForm)
 */
class SL_MA_LOGIC_EXPORT SlMaHdUserIcons : public SlMaFormLogicBase
{
  Q_OBJECT
  friend class SlMaHdUserIconsPrivate;
  friend class SlMaHdUserIconsSingelton;

  ///////////////////////////////////////////°////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
public:
  /*! \fn SlMaHdUserIcons (const QString& rInstancePath = 0, QObject* pParent = 0);
   *
   *  constructor
  */
  SlMaHdUserIcons(const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaHdUserIcons ();
   *
   *  destructor
  */
  virtual ~SlMaHdUserIcons();


  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
public:
  /*! \fn static bool hasUserIcons(const QSize& resolution);
   *
   *  Checks if user icons are configured
   *
   *  \param    resolution        IN:  screen resolution (user icons configuration is resolution specific)
   *
   *  \retval   bool              true: user icons are configured
  */
  static bool hasUserIcons();
  static bool hasUserIcons(const QSize& resolution);

  /*! \fn static unsigned int numUserIcons();
   *
   *  Gets the number of configured user icons
   *
   *  \param    resolution        IN:  screen resolution (user icons configuration is resolution specific)
   *
   *  \retval   unsigned int      number of user icons, 0 if user icons are disabled
  */
  static unsigned int numUserIcons(const QSize& resolution);  

  /*! \fn static unsigned int maxUserIcons();
   *
   *  Gets the maximum number of configured user icons
   *
   *  \retval   unsigned int      number of user icons, 0 if user icons are disabled
  */
  static unsigned int maxUserIcons();  

  /*! \fn long getIcon(const QSize& resolution, unsigned int iconIndex, bool& rDouble, QString& rText, QString& rIconName);
   *
   *  Gets the icon data of a user icon.
   *
   *  \param    resolution        IN:  screen resolution (user icons configuration is resolution specific)
   *  \param    iconIndex         IN:  index of icon to get (from 0 to maxUserIcons()-1)
   *  \param    rDouble           OUT: true: icon is a double wide icon with a leading text (channel state icon) else false
   *  \param    rText             OUT: leading text (only for double wide icons)
   *  \param    rIconName         OUT: file name of icon to show
   *
   *  \retval   long              errorcode
  */
  static long getIcon(const QSize& resolution, unsigned int iconIndex, bool& rDouble, QString& rText, QString& rIconName);

  /*! \fn static QStringList getIconList(void);
   *
   *  Gets the complete list of used icons (including actually not shown icons).
   *
   *  \retval   QStringList       list of icon file names
  */
  static QStringList getIconList(void);

  /*! \fn static bool isDoubleIcon(unsigned int iconIndex);
   *
   *  Checks if the icon is a double-wide icon with a leading text (channel state icon)
   *
   *  \param    resolution        IN:  screen resolution (user icons configuration is resolution specific)
   *  \param    iconIndex         IN:  index of icon to get (from 0 to maxUserIcons()-1)
   *
   *  \retval   bool              true: icon is double wide
  */
  static bool isDoubleIcon(const QSize& resolution, unsigned int iconIndex);


  ///////////////////////////////////////////////////////////////////////////
  // public MANIPULATORs
  ///////////////////////////////////////////////////////////////////////////
public:
  /*! \fn bool setConfigResolution(const QSize& resolution);
   *
   *  Sets the resolution used for user icon configuration (it is possible to have 
   *  resolution-specific user icon configurations
   *
   *  \param    resolution        IN:  new resolution to use
   *
   *  \retval   bool              true: configuration has changed, false: no change
  */
  bool setConfigResolution(const QSize& resolution);
  

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
signals:
  /*! \fn void userIconChanged(unsigned int iconIndex, bool isDouble, const QString& text, const QString& iconName);
   *
   *  Signal is emitted if the value of a user icon has changed
   *
   *  \param    iconIndex         index of icon that has changed (from 0 to maxUserIcons()-1)
   *  \param    isDouble          true: icon is a double wide icon with a leading text (channel state icon) else false
   *  \param    text              leading text (only for double wide icons)
   *  \param    iconName          file name of icon that has changed
  */
  void userIconChanged(unsigned int iconIndex, bool isDouble, const QString& text, const QString& iconName);


  ///////////////////////////////////////////////////////////////////////////
  // protected MEMBERS
  ///////////////////////////////////////////////////////////////////////////
protected:
  /*! \fn void initStaticValues(void)
   *
   *  init static values needed in form logic object
  */
  virtual void initStaticValues(void);

  /*! \fn void initDummyValues(void)
   *
   *  init dummy values needed in form logic object, when no ncu connection exists
  */
  virtual void initDummyValues(void);

  /*! \fn void connectToNck(void)
   *
   *  start hotlinks to ncu for dynamic value
  */
  virtual void connectToNck(bool isInit = true);

  /*! \fn void resumeToNck(void)
   *
   *  restarts suspended hotlinks to ncu for dynamic value
  */
  virtual void resumeToNck (void);

  /*! \fn void disconnectToNck(void)
   *
   *  stop hotlinks to ncu for dynamic value
  */
  virtual void disconnectToNck(void);

  /*! \fn void suspendToNck(void)
   *
   *  suspends hotlinks to ncu for dynamic value
  */
  virtual void suspendToNck (void);

  /*! \fn void connectToLogic(void)
   *
   *  connect needed signals from central logic to form logic slots
  */
  virtual void connectToLogic(void);

  /*! \fn void connectToLogic(void)
   *
   *  disconnect signals from central logic to form logic slots
  */
  virtual void disconnectToLogic(void);

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
private:
  /*! copy constructor not allowed */
  SlMaHdUserIcons (const SlMaHdUserIcons& rCopy);
  /*! assignment operator not allowed */
  SlMaHdUserIcons & operator=(const SlMaHdUserIcons& rCopy);


  ///////////////////////////////////////////////////////////////////////////
  // private SLOTs
  ///////////////////////////////////////////////////////////////////////////
private slots:
  void onConnectStateChanged(SlMaConnectStateEnum connectState);

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
private:
  SlMaHdUserIconsPrivate* m_pData; // d-pointer
};


/*! \class  SlMaHdUserIconsSingelton
 *  \brief  Singelton logic object of SlMaHdUserIcons
*/
class SlMaHdUserIconsSingelton : public QObject
{
  Q_OBJECT
  friend class SlMaHdUserIcons;

  ///////////////////////////////////////////°////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
private:
  /*! \fn SlMaHdUserIconsSingelton ();
   *
   *  constructor
  */
  SlMaHdUserIconsSingelton();

  /*! \fn ~SlMaHdUserIconsSingelton ();
   *
   *  destructor
  */
  ~SlMaHdUserIconsSingelton();

  /*! \fn long addRef();
   *
   *  Increments the singelton reference counter
   *
   *  \retval   long      the new reference count
  */
  long addRef();

  /*! \fn long relRef();
   *
   *  Decrements the singelton reference counter
   *
   *  \retval   long      the new reference count
  */
  long relRef();

  /*! \fn long connect(SlMaHdUserIcons* pUserIconLogic)();
   *
   *  Establishes the needed advises (if not done yet) and
   *  adds the logic object to the callback list
   *
   *  \retval   long      errorcode
  */
  static long connect(SlMaHdUserIcons* pUserIconLogic);

  /*! \fn long connect(SlMaHdUserIcons* pUserIconLogic)();
   *
   *  Removes the logic object from the callback list
   *
   *  \retval   long      errorcode
  */
  static long disconnect(SlMaHdUserIcons* pUserIconLogic);

  ///////////////////////////////////////////////////////////////////////////
  // private SLOTs
  ///////////////////////////////////////////////////////////////////////////
private slots:
  void activeChanChanged(const QString&);
  void onTimerEvent();
  void adviseUserIconsSlot(SlCapErrorEnum, const QVector<SlCapAdviseResultType>&);
  void chanStateChanged(SlMaChanStateEnum);
  void chanFeedLockedChanged(bool);
  void spindleTurnStateChanged(unsigned int, SlMaSpinTurnStateEnum);

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
private:
  SlMaHdUserIconsSingeltonPrivate* m_pData; // d-pointer
};

#endif // SL_MA_HEADER_USERICONS_H_INCLUDED
