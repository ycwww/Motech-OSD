///////////////////////////////////////////////////////////////////////////////
/*! \file   slcapcb.h
 *  \author Mc4Hmi-Team
 *  \date   01.10.2004
 *  \brief  SlCapCB Class interface file
 *
 *  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
 *  Its not intended, to be included by SlCap clients directly, but through slcap.h
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLCAPCB_H
#define SLCAPCB_H

#include "slcapdata.h"


// forward declarations:
class SlCapCBImplInterface;
namespace caputil
{
  class RequestVariableAdapter;
  class PromiseMapEntry;
}
class SlCapCBImplSeq;
class SlCapCBImplPar;
class SlCapTB;


/*! \class SlCapCB slcapcb.h
 *  \brief Callback object class of the CAP-Server interface for use by servers
 *
 *  Objects of the SlCapCB class are called during Callbacks by the SlCap-Server. 
 *  Callbacks happen in CORBA-Threads. For Details see the SlCap-User-Manual. 
*/
class SL_CAP_EXP SlCapCB
{
  friend class SlCap;
  friend class SlCapCBImplSeq;
  friend class SlCapCBImplPar;
  friend class SlCapCbTrigger;
  friend class SlCapServiceAdapter;
  friend class caputil::RequestVariableAdapter;
  friend class caputil::PromiseMapEntry;
  friend class SlCapNamespaceImplSeq;
  friend class SlCapNamespaceImplPar;
  friend class TwoCapsResolver;

public:
  
  //! Constructor
  SlCapCB(const char* czModule = SL_TRC_STRINGIZED_MODULE);

  //! Destructor
  virtual ~SlCapCB();

private:
  // hide copy possibilities no delete to ensure generation of slhmihost_2010
  SlCapCB(const SlCapCB& other) ;
  SlCapCB& operator=(const SlCapCB& other) ;

public:
  //! Tell whether an activity is working.
  bool busy() const;

  //! Tell if an advise is working.
  bool suspended() const;

  //! Access of the creators module
  const QByteArray& module() const;


  //! Level dependent trace string.
  const char* traceString(
    SlCapTB& tb ,                     /*!< Trace buffer. */
    bool bComplete = false) const;    /*!< Trace complete information. */

protected:

  SlCapCBImplInterface* impl() const;


private:

  SlCapCBImplInterface* m_pCBImplIF;    /*!< Pointer to inner instance implementing the functionality and called via interface. */
                                      // (need no safe-pointer, because always first SlCapCB is deleted)

  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  // standard implementations of callback methods called if not implemented by the derived (client) class:

  //! Callback method indicating arrived data requested by calling readAsync(...)
  virtual void readData(SlCapErrorEnum eError, const QVariant& vData, const SlCapSupplementInfoType& supplement); 
  
  //! Callback method indicating arrived data requested by calling multiReadAsync(...)
  virtual void multiReadData(SlCapErrorEnum eError, const QVector<SlCapReadResultType>& readResult);

  //! Callback method indicating arrived/changed data requested by calling advise(...)
  virtual void adviseData(SlCapErrorEnum eError, const QVariant& vData, const SlCapSupplementInfoType& supplement); 

  //! Callback method indicating arrived/changed data requested by calling multiAdvise(...) 
  virtual void multiAdviseData(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResult);

  //! Callback method indicating completion of writing data requested by calling writeAsync(...)
  virtual void writeComplete(SlCapErrorEnum eError, const QDateTime& timestamp);

  //! Callback method indicating completion of writing data requested by calling multiWriteAsync(...)
  virtual void multiWriteComplete(SlCapErrorEnum eError, const QVector<SlCapWriteResultType>& writeResult); 

  //! Callback method indicating completion of asynchronous domain transfers and PI requests
  virtual void executeComplete(SlCapErrorEnum eError, const QVector<QVariant>& outArgs, const QDateTime& timestamp); 

  //! Callback method indicating completion of multiple asynchronous domain transfers and PI requests using the flag SL_CAP_FLAG_MULTI_CALLBACK
  virtual void multiExecuteComplete(SlCapErrorEnum eError, const QVector<SlCapExecuteResultType>& executeResult); 
  
  //! Callback method indicating the progress of domain transfers
  virtual void progress(int iPercent, const QDateTime& timestamp);

  //! Callback method requesting domain contend data to be send into the pipe to be transfered to target by
  //! calling the piped versions of download(...), downloadNc(...), downloadAsync(...) or downloadNcAsync(...)
  virtual void sendPipeData(const QDateTime& timestamp); 

  //! Callback method requesting more domain content data to be send into the pipe to be transfered to target by
  //! calling pipeWriteAsync(...)
  virtual void pipeWriteReturn(SlCapErrorEnum eError, const QDateTime& timestamp); 

  //! Callback method delivering domain content data received from target, requested by calling the 
  //! piped versions of upload(...), uploadAsync(...), uploadNc(...) or uploadNcAync(...) 
  virtual void pipeData(const QByteArray& data, bool eof);
};


#include "slcapcb.inl"


#endif // SLCAPCB_H
