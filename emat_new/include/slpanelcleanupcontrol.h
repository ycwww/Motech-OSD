#pragma once

class SlPanelCleanupControl
{
public:
  virtual ~SlPanelCleanupControl() {};

  virtual int lockHmiForPanelCleanup(unsigned int* pLockCount = nullptr) = 0;
  virtual int unlockHmiForPanelCleanup(unsigned int* pLockCount = nullptr) = 0;
};



