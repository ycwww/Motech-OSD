#ifndef WIN32

#ifndef _LINUXSIGNALS_H
#define _LINUXSIGNALS_H

#include <ace/Signal.h>

typedef struct
{
  int         iSignal;
  const char* pszSignalName;
}s_SlHmiReservedLinuxSignalsEntry;
const s_SlHmiReservedLinuxSignalsEntry s_SlHmiReservedLinuxSignals[] = {
  {SIGRTMIN + 9,  "SlCap-Classic 1"},
  {SIGRTMIN + 10, "SlCap-Classic 2"},
  {SIGRTMIN + 11, "SlCap-Classic 3"},
  {SIGRTMIN + 12, "SlCap-Classic 4"},
  {SIGRTMIN + 13, "SlCap-MultiCore 1"},
  {SIGRTMIN + 14, "SlCap-MultiCore 2"},
  {SIGRTMIN + 15, "SlCap-MultiCore 3"},
  {SIGRTMIN + 16, "SlCap-MultiCore 4"}
};
const int s_SlHmiReservedLinuxSignalsCount = (int)(sizeof(s_SlHmiReservedLinuxSignals) / sizeof(s_SlHmiReservedLinuxSignalsEntry));

#endif // _LINUXSIGNALS_H

#endif // WIN32
