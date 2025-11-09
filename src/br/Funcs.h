// SPDX-License-Identifier: BUSL-1.1
// Copyright 2024-2025 Michael Pozhidaev <msp@luwrain.org>


#pragma once

#include"os.h"

namespace GuideCraft
{

  class Funcs
  {
  public:
    virtual ~Funcs() {}

  public:
    //Condition variable
    void pthreadCondAttrInit(pthread_condattr_t& attr);
    void pthreadCondInit(pthread_cond_t& cond, pthread_condattr_t& attr);
    void pthreadCondDestroy(pthread_cond_t& cond);
    void pthreadCondSignal(pthread_cond_t& cond);
    void pthreadCondBroadcast(pthread_cond_t& cond);
    void pthreadCondWait(pthread_cond_t& cond, pthread_mutex_t& lock);

    //Mutex
        void pthreadMutexAttrInit(pthread_mutexattr_t& attr);
    void pthreadMutexInit(pthread_mutex_t& lock, pthread_mutexattr_t& attr);
    void pthreadMutexDestroy(pthread_mutex_t& cond);

    
    
  };
  
}
