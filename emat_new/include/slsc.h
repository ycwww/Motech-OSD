///////////////////////////////////////////////////////////////////////////////
/*! \file   slsc.h
 *  \author Zapf Joachim
 *  \date   09.04.2009
 *  \brief  Headerfile for the class SlScIface
 *
 *  This file is part of the HMI Solutionline Service/Shell Command Interface.
 *
 *  (C) Copyright Siemens AG A&D MC 2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_SC_H_INCLUDED)
#define SL_SC_H_INCLUDED

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <QtCore/QString>

#include "slsfwserviceadapterptr.h"


#if !defined(LINUX)
  #if defined(SL_SC_EXPORTS)
    #define SL_SC_EXPORT         __declspec(dllexport)
  #else  // SL_SC_EXPORTS
    #define SL_SC_EXPORT         __declspec(dllimport)
  #endif // SL_SC_EXPORTS
#else  // LINUX
  #define SL_SC_EXPORT
#endif // LINUX

///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////
class SlScCb;

///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////


/*! \class SlScIface slsc.h
 *  \brief Interface for Service/Shell Command
 */
class SL_SC_EXPORT SlScIface
{
public:
  /////////////////////////////////////////////////////////////////////////////
  // public METHODS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual int serviceCommand(const QString& rszNcuName, const QString& rszCommand, QString& rszReturnString)
   *
   *  \param  rszNcuName:      NCU name (from mmc.ini, DNS name or IP-Adress)
   *  \param  rszCommand:      command string
   *  \param  rszReturnString: string returned by the command
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  Executes synchronous a service command in the shell for the given ncu
   */
  virtual int serviceCommand(const QString& rszNcuName, const QString& rszCommand, QString& rszReturnString) = 0;

  /*! \fn virtual int serviceCommand(const QString& rszNcuName, const QString& rszCommand, SlScCb *pCallback)
   *
   *  \param  rszNcuName:      NCU name (from mmc.ini, DNS name or IP-Adress)
   *  \param  rszCommand:      command string
   *  \param  pCallback:       Pointer to callback object. The operation is called asynchronous and the client 
   *                           will be notified by calling serviceCommandFinished().
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  Executes asynchronous a service command in the shell for the given ncu and notify the client 
   *  by calling serviceCommandFinished of the callback object
   */
  virtual int serviceCommand(const QString& rszNcuName, const QString& rszCommand, SlScCb *pCallback) = 0;

  /*! \fn virtual int inifile(const QString& rszNcuName, const QString& rszArgs, QString& rszReturnString)
   *
   *  \param  rszNcuName:      NCU name (from mmc.ini, DNS name or IP-Adress)
   *  \param  rszArgs:         command argument string
   *  \param  rszReturnString: string returned by the command
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  Executes synchronous a inifile command in the shell for the given ncu
   */
  virtual int inifile(const QString& rszNcuName, const QString& rszArgs, QString& rszReturnString) = 0;

  /*! \fn virtual int inifile(const QString& rszNcuName, const QString& rszArgs, SlScCb *pCallback)
   *
   *  \param  rszNcuName:      NCU name (from mmc.ini, DNS name or IP-Adress)
   *  \param  rszArgs:         command argument string
   *  \param  pCallback:       Pointer to callback object. The operation is called asynchronous and the client 
   *                           will be notified by calling inifileFinished().
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  Executes asynchronous a inifile command in the shell for the given ncu and notify the client 
   *  by calling inifileFinished of the callback object
   */
  virtual int inifile(const QString& rszNcuName, const QString& rszArgs, SlScCb *pCallback) = 0;

  /*! \fn virtual int ifconfig(const QString& rszNcuName, const QString& rszArgs, QString& rszReturnString)
   *
   *  \param  rszNcuName:      NCU name (from mmc.ini, DNS name or IP-Adress)
   *  \param  rszArgs:         command argument string
   *  \param  rszReturnString: string returned by the command
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  Executes synchronous a ifconfig command in the shell for the given ncu
   */
  virtual int ifconfig(const QString& rszNcuName, const QString& rszArgs, QString& rszReturnString) = 0;

  /*! \fn virtual int ifconfig(const QString& rszNcuName, const QString& rszArgs, SlScCb *pCallback)
   *
   *  \param  rszNcuName:      NCU name (from mmc.ini, DNS name or IP-Adress)
   *  \param  rszArgs:         command argument string
   *  \param  pCallback:       Pointer to callback object. The operation is called asynchronous and the client 
   *                           will be notified by calling ifconfigFinished().
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  Executes asynchronous a ifconfig command in the shell for the given ncu and notify the client 
   *  by calling ifconfigFinished of the callback object
   */
  virtual int ifconfig(const QString& rszNcuName, const QString& rszArgs, SlScCb *pCallback) = 0;

  /*! \fn virtual int ping(const QString& rszNcuName, const QString& rszArgs, QString& rszReturnString)
   *
   *  \param  rszNcuName:      NCU name (from mmc.ini, DNS name or IP-Adress)
   *  \param  rszArgs:         command argument string
   *  \param  rszReturnString: string returned by the command
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  Executes synchronous a ping command in the shell for the given ncu
   */
  virtual int ping(const QString& rszNcuName, const QString& rszArgs, QString& rszReturnString) = 0;

  /*! \fn virtual int ping(const QString& rszNcuName, const QString& rszArgs, SlScCb *pCallback)
   *
   *  \param  rszNcuName:      NCU name (from mmc.ini, DNS name or IP-Adress)
   *  \param  rszArgs:         command argument string
   *  \param  pCallback:       Pointer to callback object. The operation is called asynchronous and the client 
   *                           will be notified by calling pingFinished().
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  Executes asynchronous a ping command in the shell for the given ncu and notify the client 
   *  by calling pingFinished of the callback object
   */
  virtual int ping(const QString& rszNcuName, const QString& rszArgs, SlScCb *pCallback) = 0;

  /*! \fn virtual int ncuSwVersion(const QString& rszNcuName, QString& rszReturnString)
   *
   *  \param  rszNcuName:      NCU name (from mmc.ini, DNS name or IP-Adress)
   *  \param  rszReturnString: string returned by the command
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  Reades synchronous the ncu software version in the shell for the given ncu
   */
  virtual int ncuSwVersion(const QString& rszNcuName, QString& rszReturnString) = 0;

  /*! \fn virtual int ncuSwVersion(const QString& rszNcuName, SlScCb *pCallback)
   *
   *  \param  rszNcuName:      NCU name (from mmc.ini, DNS name or IP-Adress)
   *  \param  pCallback:       Pointer to callback object. The operation is called asynchronous and the client 
   *                           will be notified by calling pingFinished().
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  Reades asynchronous the ncu software version in the shell for the given ncu and notify the client 
   *  by calling ncuSwVersionFinished of the callback object
   */
  virtual int ncuSwVersion(const QString& rszNcuName, SlScCb *pCallback) = 0;


  /////////////////////////////////////////////////////////////////////////////
  // CREATORS (static)
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn static long getObject(SlScIface*& rpAdapter, int argc = 0, char* pArgv[] = 0);
   *
   *  \param  rpAdapter   a reference to the pointer to be filled with an
   *                      instance of Command Shell Interface.
   *  \param  argc        number of arguments
   *  \param  pArgv       arguments
   *
   *  \retval error code, if an error occurred, otherwise
   *
   *  This static function creates a Command Shell Interface.
   */
  static long getObject(SlScIface*& rpAdapter, int argc = 0, char* pArgv[] = 0);

  /*! \fn static long releaseObject(SlScIface*& rpInstance);
   *
   *  \param  rpInstance   instance of Command Shell Interface
   *
   *  \retval error code, if an error occurred, otherwise 0
   *
   *  This static function removes a Command Shell Interface.
   */
  static long releaseObject(SlScIface*& rpInstance);

protected:
  /////////////////////////////////////////////////////////////////////////////
  // protected CREATORS (Singleton)
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlScIface(void);
   *
   *  Constructor
   */
  SlScIface();
  
  /*! \fn ~SlScIface(void);
   *
   *  Destructor
   */
  virtual ~SlScIface();

  /////////////////////////////////////////////////////////////////////////////
  // protected METHODS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // protected MEMBERS
  /////////////////////////////////////////////////////////////////////////////

private:
  /////////////////////////////////////////////////////////////////////////////
  // private METHODS
  /////////////////////////////////////////////////////////////////////////////

  /*! copy constructor not allowed */
  SlScIface(const SlScIface& rCopy);
  /*! assignment operator not allowed */
  SlScIface& operator=(const SlScIface& rCopy);

  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////
};

class SL_SC_EXPORT SlScCb
{
public:
  /////////////////////////////////////////////////////////////////////////////
  // CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlScCb(void);
   *
   *  Constructor
   */
  SlScCb();
  
  /*! \fn ~SlScCb(void);
   *
   *  Destructor
   */
  virtual ~SlScCb();

  /////////////////////////////////////////////////////////////////////////////
  // public METHODS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual void serviceCommandFinished(const int iError, const QString& rszReturnString)
   *
   *  \param  iError:          Error code of operation
   *  \param  rszReturnString: string returned by the command
   *
   *  Notifies the client about SlSc operation finished
   */
  virtual void serviceCommandFinished(const int iError, const QString& rszReturnString);

  /*! \fn virtual void inifileFinished(const int iError, const QString& rszReturnString)
   *
   *  \param  iError:          Error code of operation
   *  \param  rszReturnString: string returned by the command
   *
   *  Notifies the client about SlSc operation finished
   */
  virtual void inifileFinished(const int iError, const QString& rszReturnString);

  /*! \fn virtual void ifconfigFinished(const int iError, const QString& rszReturnString)
   *
   *  \param  iError:          Error code of operation
   *  \param  rszReturnString: string returned by the command
   *
   *  Notifies the client about SlSc operation finished
   */
  virtual void ifconfigFinished(const int iError, const QString& rszReturnString);

  /*! \fn virtual void pingFinished(const int iError, const QString& rszReturnString)
   *
   *  \param  iError:          Error code of operation
   *  \param  rszReturnString: string returned by the command
   *
   *  Notifies the client about SlSc operation finished
   */
  virtual void pingFinished(const int iError, const QString& rszReturnString);

  /*! \fn virtual void ncuSwVersionFinished(const int iError, const QString& rszReturnString)
   *
   *  \param  iError:          Error code of operation
   *  \param  rszReturnString: string returned by the command
   *
   *  Notifies the client about SlSc operation finished
   */
  virtual void ncuSwVersionFinished(const int iError, const QString& rszReturnString);

protected:
  /////////////////////////////////////////////////////////////////////////////
  // protected METHODS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // protected MEMBERS
  /////////////////////////////////////////////////////////////////////////////

private:
  /////////////////////////////////////////////////////////////////////////////
  // private METHODS
  /////////////////////////////////////////////////////////////////////////////

  /*! copy constructor not allowed */
  SlScCb(const SlScCb& rCopy);
  /*! assignment operator not allowed */
  SlScCb& operator=(const SlScCb& rCopy);

  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////
};

typedef SlSfwServiceAdapterPtr<SlScIface> SlSc;


#endif // !defined(SL_SC_H_INCLUDED)
