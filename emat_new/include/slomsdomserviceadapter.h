#ifndef OmsDomServiceAdapter_h
#define OmsDomServiceAdapter_h

#define CORBA_Object CORBA::Object

#include <string>
#include <vector>

#include <QtCore/QVector>
#include <QtCore/QList>
#include <QtCore/QMutex>
#include <QtCore/QMap>

#include "slomsdomenum.h"

class SlOmsDomIClient;
class SlSfwOrbManager;
class SlOmsDomComSinkImpl;

class OmsDomServiceAdapter
{
		
public:
  static long getObject(OmsDomServiceAdapter*& rpAdapter);
  static long releaseObject(OmsDomServiceAdapter* pAdapter);

	virtual long executeCommand(long lCommandId,
                              const std::vector<std::string>& rstrlstInParam,
                              std::vector<std::string>& rstrlstOut) = 0;

  virtual long executeCommandAsync(long lCommandId,
                                   const std::vector<std::string>& rstrlstInParam,
                                   long& lRequestId,
                                   SlOmsDomIClient* pClientSink) = 0;
	
  virtual long cancel(long lRequestID) = 0;

	virtual void finiCalled(SlOmsDomIClient* pClientSink) = 0;

	virtual void finiCalledId(long lRequestID) = 0;
};

class CORBA_Object;

#endif
