#ifndef SLTRCFORM_H
#define SLTRCFORM_H

#include <QtCore/QString>

const QString SLTRC_OUTPUTFORMSHAREDMEM_KEY  ("SlTrcOutputFormShMem");
#define SLTRC_OUTPUTFORMSENDSEMAPHORE_KEY    "SlTrcOutputFormSendSema" 
#define SLTRC_OUTPUTFORMRECEIVESEMAPHORE_KEY "SlTrcOutputFormReceiveSema" 
const int     SLTRC_MAXNUMBYTESHMITRACESHM = 15360; 

enum _status
{
	eInactive  = 0,
	eActive    = 1,
	eTraceLost = 2
};

typedef struct SlTrcOutputFormSharedMem
{
    int  status; // is set by the SlTrcUserTraceForm and indicates the status of the OutputFormThread
    int  numBytes; // length of the current trace buffer in bytes
    char pTraceData[SLTRC_MAXNUMBYTESHMITRACESHM]; // contains trace data 
}SlTrcOutputFormShMem;



#endif // SLTRCFORM_H
