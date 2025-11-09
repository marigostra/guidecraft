// SPDX-License-Identifier: BUSL-1.1
// Copyright 2024-2025 Michael Pozhidaev <msp@luwrain.org>


#include"os.h"
#include"Funcs.h"

using namespace std;
using namespace GuideCraft;

void Funcs::pthreadCondAttrInit(pthread_condattr_t& attr)
{
  if (pthread_condattr_init(&attr) != 0)
    throw runtime_error("pthread_condattr_init() failed");
}

void Funcs::pthreadCondInit(pthread_cond_t& cond, pthread_condattr_t& attr)
{
  if (pthread_cond_init(&cond, &attr) != 0)
    throw runtime_error("pthread_cond_init()() failed");
}

void Funcs::pthreadCondDestroy(pthread_cond_t& cond)
{
    if (pthread_cond_destroy(&cond) != 0)
    throw runtime_error("pthread_cond_destroy()() failed");
}

void Funcs::pthreadCondSignal(pthread_cond_t& cond)
{
    if (pthread_cond_signal(&cond) != 0)
    throw runtime_error("pthread_cond_signal()() failed");
}

void Funcs::pthreadCondBroadcast(pthread_cond_t& cond)
{
      if (pthread_cond_broadcast(&cond) != 0)
    throw runtime_error("pthread_cond_broadcast()() failed");
}

void Funcs::pthreadCondWait(pthread_cond_t& cond, pthread_mutex_t& lock)
{
  if (pthread_cond_wait(&cond, &lock) != 0)
    throw runtime_error("pthread_cond_wait()() failed");
}

//Mutex

void Funcs::pthreadMutexAttrInit(pthread_mutexattr_t& attr)
{
  if (pthread_mutexattr_init(&attr) != 0)
    throw runtime_error("pthread_mutexattr_init() failed");
}

void Funcs::pthreadMutexInit(pthread_mutex_t& lock, pthread_mutexattr_t& attr)
{
  if (pthread_mutex_init(&lock, &attr) != 0)
    throw runtime_error("pthread_mutex_init()() failed");
}

void Funcs::pthreadMutexDestroy(pthread_mutex_t& lock)
{
    if (pthread_mutex_destroy(&lock) != 0)
    throw runtime_error("pthread_mutex_destroy()() failed");
}




