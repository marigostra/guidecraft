// SPDX-License-Identifier: BUSL-1.1
// Copyright 2024-2025 Michael Pozhidaev <msp@luwrain.org>
// Copyright 2024 Andrey Cheprasov <andreycheprasov54@gmail.com>

#include "os.h"
#include "RwLock.h"

using namespace std;


namespace GuideCraft {

  RwLock::RwLock()
  {
    if (pthread_rwlockattr_init(&attr) != 0)
      throw runtime_error("pthread_rwlockattr_init() failed");
    if (pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_SHARED) != 0)
      throw runtime_error("pthread_rwlockattr_setpshared() failed");
    if (pthread_rwlock_init(&rwlock, &attr) != 0)
      throw runtime_error("pthread_rwlock_init() failed ");
  }
  
  RwLock::~RwLock()
  {
    pthread_rwlock_destroy(&rwlock);
    pthread_rwlockattr_destroy(&attr);
  }

void RwLock::lockWrite()
{
  pthread_rwlock_wrlock(&rwlock);
}
  
bool RwLock::tryLockWrite()
{
  return (!pthread_rwlock_trywrlock(&rwlock));
}
  
void RwLock::unlockWrite()
{
  pthread_rwlock_unlock(&rwlock);
}
  
void RwLock::lock_sharable()
{
  pthread_rwlock_rdlock(&rwlock);
}
  
bool RwLock::try_lock_sharable()
{
  return (!pthread_rwlock_tryrdlock(&rwlock));
}
  
void RwLock::unlock_sharable()
{
  pthread_rwlock_unlock(&rwlock);
}

void RwLock::reset()
{
  pthread_rwlock_destroy(&rwlock);
  pthread_rwlock_init(&rwlock, &attr);
}
}
