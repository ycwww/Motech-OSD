///////////////////////////////////////////////////////////////////////////////
/*! \file	slrsstarter.h
 *  \author Gerolf Kuehnel
 *  \date   12.10.2004
 *  \brief	Header file for class SlRsStarter
 *
 *  This file is part of the HMI Solutionline resource service
 *
 *  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_RS_STARTER_H)
#define SL_RS_STARTER_H

#if defined(WIN32)
#	ifdef SLRSSTARTER_EXPORTS
#		 define SL_RS_SVC_STARTER_EXPORT  __declspec(dllexport)
#	else
#		 define SL_RS_SVC_STARTER_EXPORT  __declspec(dllimport)
#	endif
#else
#	define SL_RS_SVC_STARTER_EXPORT
#endif

/*! \class SlRsStarter slrsstarter.h
 *  \brief installs the resourceservice
 *
 *  \code
 *  ... fkt(...)
 *  {
 *      SlRsStarter::installService();
 *      ...
 *  }
 *  \endcode
*/
class SL_RS_SVC_STARTER_EXPORT SlRsStarter  
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // static Members
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn static void installService(void);
     *
     *  installs the service, if not already installed
     */
    static void installService(void);

    /*! \fn static void removeService(void);
     *
     *  removes the service, if nessaccary
     */
    static void removeService(void);
};

/*! \class SlRsStarterSingleton slrsstarter.h
 *  \brief installs the resourceservice
 *
 *  \code
 *  ... fkt(...)
 *  {
 *      SlRsStarterSingleton var;
 *      ...
 *  }
 *  \endcode
*/
class SL_RS_SVC_STARTER_EXPORT SlRsStarterSingleton
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // Constructors
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlRsStarterSingleton(bool bDelayedStartup = false);
     *  \param bDelayedStartup  if set to true, you have to start the services by calling 
     *                          installServices() yourself, otherwise the services are installed 
     *                          by the Constructor
     *
     *  Constructor
     */
    SlRsStarterSingleton(bool bDelayedStartup = false);
    
    /*! \fn ~SlRsStarterSingleton();
     *
     *  Destructor
     */
    ~SlRsStarterSingleton();

    /*! \fn void installServices(void);
     *
     *  installs the services
     */
    void installServices(void);

private:
    /*! \fn void removeServices(void);
     *
     *  removes the services (called by D'tor)
     */
    void removeServices(void);
    
    bool m_bCalledInstall;
};

#endif // !defined(SL_RS_STARTER_H)
