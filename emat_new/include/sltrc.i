
///////////////////////////////////////////////////////////////////////////////////////////
// SlTrc implementation
///////////////////////////////////////////////////////////////////////////////////////////

inline bool SlTrc::ok() const
{
  return !SL_TRC_IS_NOTUSABLE(this);
}

inline const char* SlTrc::moduleName()
{
  return m_pczModuleName;
}


inline void SlTrc::nop() 
{
}

inline bool SlTrc::always()
{
  return true;
}

inline bool SlTrc::never()
{
  return false;
}

// trace() and traceModule() were moved to sltrcdll.cpp because "..." AND "inline" doesn't work

///////////////////////////////////////////////////////////////////////////////////////////
// SlTrcShmAdmin implementation (iLineAdmin access)
///////////////////////////////////////////////////////////////////////////////////////////

inline int SlTrcShmAdmin::addLineCount(int cnt)
{
  return SlTrc::atomicAdd(&iLineAdmin, cnt * 0x10000) / 0x10000;
}

inline int SlTrcShmAdmin::lineCount(int iLineAdmin)
{
  return iLineAdmin / 0x10000;
}

inline int SlTrcShmAdmin::addLineOutput(int cnt)
{
  return SlTrc::atomicAdd(&iLineAdmin, cnt) % 0x10000;
}

inline int SlTrcShmAdmin::lineOutput(int iLineAdmin)
{
  return iLineAdmin % 0x10000;
}

inline void SlTrcShmAdmin::subBoth(int cnt)
{
  SlTrc::atomicAdd(&iLineAdmin, -(cnt * 0x10000 + cnt));
}

inline int SlTrcShmAdmin::freeCount()
{
  int iAdmin = iLineAdmin;
  return iLineAlloc - (lineCount(iAdmin) - lineOutput(iAdmin)) - 1;  
}

inline bool SlTrcShmAdmin::empty()
{
  int iAdmin = iLineAdmin;	// we take a copy to get a threadsave answer
  return lineCount(iAdmin) == lineOutput(iAdmin);
}

