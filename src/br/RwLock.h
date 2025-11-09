// SPDX-License-Identifier: BBUSL-1.1
// Copyright 2024-2025 Michael Pozhidaev <msp@luwrain.org>
// Copyright 2024 Andrey Cheprasov <andreycheprasov54@gmail.com>

#pragma once

#include "os.h"

namespace GuideCraft {

  class RwLock
  {
  public:
    RwLock();
    virtual ~RwLock();

    void lockWrite();
    bool tryLockWrite();
    void unlockWrite();
    void lock_sharable();
    bool try_lock_sharable();
    void unlock_sharable();
    void reset();

  private:
    pthread_rwlock_t rwlock{};
  pthread_rwlockattr_t attr{};
  };

}
