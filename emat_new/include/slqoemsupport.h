///////////////////////////////////////////////////////////////////////////////
/*! \file	slqoemsupport.h
 *  \author Hans-Jürgen Hümmer
 *  \date   01.03.2012
 *  \brief	Class declaration file for class SlQOemSupport
 *
 *  This file is part of the HMI Solutionline GUI Framework.
 *
 *  (C) Copyright Siemens AG A&D MC 2012. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_Q_OEM_SUPPORT_H
#define SL_Q_OEM_SUPPORT_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QString>

#include "slspserviceadapter.h"
#include "sloemsupportexport.h"
#include "slpmarchiveinfo.h"

class SlQOemSupportData;

/*! \class SlQOemSupport slqoemsupport.h
 *  \brief This form is used to ask input form the user.
*/
class SL_OEM_SUPPORT_EXPORTS SlQOemSupport : public QObject
{
    Q_OBJECT

public:
    
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlQOemSupport()
     *
     *  Constructor
    */
    SlQOemSupport();

    /*! \fn virtual ~SlQOemSupport(void)
     *
     *  Destructor
    */
    virtual ~SlQOemSupport(void);

    /*! \fn long selectJoblist(const QString& sJobList)
     *  \param joblist for select
     *  \retval 0 for success (job has been started)
     *
     *  select the joblist asynchrone, 'supports simplified user interface'
     *    job has been finished after received signal canceled() or completed()
    */
    long selectJoblist(const QString& sJobList);

    ///////////////////////////////////////////////////////////////////////////
    // signals
    ///////////////////////////////////////////////////////////////////////////
signals:

    void started(void);
    void finished(void);

    /*  SL_SUCCEEDED(lRetVal) -> see also slpmarchiveinfo.h                         */
    /*                error accessing file attributes                               */
    /*  SLPMFILECOPYRET(SLPM_READ_ACCESS_SYSTEM)                                    */
    /*     minimum read access is SIEMENS                                           */
    /*  SLPMFILECOPYRET(SLPM_READ_ACCESS_MANUFACT)                                  */
    /*     minimum read access is manufacturer                                      */
    /*  SLPMFILECOPYRET(SLPM_READ_ACCESS_SERVICE)                                   */
    /*     minimum read access is service                                           */
    /*  SLPMFILECOPYRET(SLPM_READ_ACCESS_USER)                                      */
    /*     minimum read access is user                                              */
    /*  SLPMFILECOPYRET(SLPM_READ_ACCESS_KEY3)                                      */
    /*     minimum read access is key 3                                             */
    /*  SLPMFILECOPYRET(SLPM_READ_ACCESS_KEY2)                                      */
    /*     minimum read access is key 2                                             */
    /*  SLPMFILECOPYRET(SLPM_READ_ACCESS_KEY1)                                      */
    /*     minimum read access is key 1                                             */
    /*  SLPMFILECOPYRET(SLPM_SELECT_ACCESS_SYSTEM)                                  */
    /*     minimum execute access is SIEMENS                                        */
    /*  SLPMFILECOPYRET(SLPM_SELECT_ACCESS_MANUFACT)                                */
    /*     minimum execute access is manufacturer                                   */
    /*  SLPMFILECOPYRET(SLPM_SELECT_ACCESS_SERVICE)                                 */
    /*     minimum execute access is service                                        */
    /*  SLPMFILECOPYRET(SLPM_SELECT_ACCESS_USER)                                    */
    /*     minimum execute access is user                                           */
    /*  SLPMFILECOPYRET(SLPM_SELECT_ACCESS_KEY3)                                    */
    /*     minimum execute access is key 3                                          */
    /*  SLPMFILECOPYRET(SLPM_SELECT_ACCESS_KEY2)                                    */
    /*     minimum execute access is key 2                                          */
    /*  SLPMFILECOPYRET(SLPM_SELECT_ACCESS_KEY1)                                    */
    /*     minimum execute access is key 1                                          */
    /*                error scanning and executing joblist                          */
    /*  SL_JOBLIST_RET(SLSP_NO_CHANNELRESET)                                        */
    /*     not all channels in state RESET                                          */
    /*     see rErrorVec[].m_strText  SELECT <channel> <ncu program> [ncuname]      */
    /*  SL_JOBLIST_RET(SLSP_IS_SELECTED)                                            */
    /*     program is selected for another channel or for extern                    */
    /*  0x8300C4BC                                                                  */
    /*     program is locked by application as example by editor                    */
    /*  0xFFFFFFFF            see rErrorVec[]                                       */
    /*            m_lNr                                                             */
    /*  SL_JOBLIST_RET(SLSP_WRONG_NCU_NAME)                                         */
    /*     ncuname not found: joblist line .m_strText                               */
    /*  SL_JOBLIST_RET(SLSP_SRC_FAILED)                                             */
    /*     program name not found: joblist line .m_strText                          */
    /*  SL_JOBLIST_RET(SLSP_CHANNEL_FAILED)                                         */
    /*  SL_JOBLIST_RET(SLSP_DEST_FAILED)                                            */
    /*     channel is missing or wrong: joblist line .m_strText                     */
    /*  SL_JOBLIST_RET(SLSP_WRONG_SYNTAX)                                           */
    /*     syntax error in joblist: joblist line .m_strText                         */
    /*  SL_JOBLIST_RET(SL_PM_JOBLIST_MULTIPLE_SELECT)                               */
    /*     the SELECT-statement is multiple used for channel: .m_strText            */
    /*  SL_JOBLIST_RET(SL_PM_JOBLIST_NOT_IMPL)                                      */
    /*     the command is not implemented: joblist line .m_strText                  */
    /*  SL_JOBLIST_RET(SL_PM_JOBLIST_NAME_TOO_LONG)                                 */
    /*     filename exceeds 28 characters: joblist line .m_strText                  */
    /*  SL_JOBLIST_RET(SLSP_NO_EXECUTE_RIGHT)                                       */
    /*     missing execution right: .m_strText                                      */
    /*  SL_JOBLIST_RET(SLSP_SKIPPING_DATA_FAILED)                                   */
    /*     missing execution right: .m_strText                                      */
    /*  SL_JOBLIST_RET(SLSP_LIST_EMPTY)                                             */
    /*     joblist doesn't contains a valid statement                               */
    /*                                                                              */
    /*  job has been finished, lRetVal: return state, rErrorVec: error information  */
    void completed(SlSpErrorVec& /* rErrorVec */, long /* lRetVal */);

    /* job has been canceled                                                        */
    void canceled();

    /* lPercentage: 0..99: progress state, -1: no value longer than 2 seconds       */
    void progress(long /* lPercentage */, QString& /* sInput */);

    void info(SlSpInfo&  /* sInfo */) ;

    void error(SlSpError& /* sError */);

    ///////////////////////////////////////////////////////////////////////////
    // PUBLIC SLOTS
    ///////////////////////////////////////////////////////////////////////////
public slots:
 
    /*! \fn void cancel(void)
     *
     *  cancels an active asynchron job
     *
    */
    void cancel(void);

    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE SLOTS
    ///////////////////////////////////////////////////////////////////////////
private slots:

  void listCompletedSpSlot(int /* nId*/, SlSpErrorVec& /* rErrorVec */, long /* lErrno */);
  void joblistCompletedSlot(int /* nId*/, SlSpJoblistVec& /* rJoblistVec */, long /* lErrno */);
  void canceledSpSlot(int /* nId*/);
  void progressSpSlot(int /* nId*/, long /* lPercentage */, QString&  /* sInput */);
  void infoSpSlot(int /* nId*/, SlSpInfo& /* sInfo */) ;
  void errorSpSlot(int /* nId*/, SlSpError& /* sError */);
  // timer
  void timeoutSlot();

    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE MEMBER DATA
    ///////////////////////////////////////////////////////////////////////////
private:
    SlQOemSupportData* m_pData; //!< Private member data (D-Pointer)
};


#endif // SL_Q_OEM_SUPPORT_H
