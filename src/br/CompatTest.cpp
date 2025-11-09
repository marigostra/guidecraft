// SPDX-License-Identifier: BUSL-1.1
// Copyright 2024-2025 Michael Pozhidaev <msp@luwrain.org>

#include "os.h"
#include "CompatTest.h"

#define SHM_NAME "gc-compad-test"
#define SHM_SIZE 4096

struct SyncData
{
  pthread_cond_t cond;
  pthread_mutex_t lock;
  int event;
};

using namespace std;
using namespace GuideCraft;

void CompatTest::init()
{
  const int shmFd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0600);
  if (shmFd == -1)
    throw runtime_error(string("shm_open: ") + strerror(errno));
  if (ftruncate(shmFd, SHM_SIZE) == -1)
    {
      string info = strerror(errno);
      ::close(shmFd);
      throw runtime_error("ftruncate: " + info);
    }
  void* const ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
  if (ptr == MAP_FAILED)
    {
      string info = strerror(errno);
      ::close(shmFd);
      throw runtime_error("mmap: " + info);
    }
  ::close(shmFd);
  pthread_condattr_t condAttr;
  pthread_mutexattr_t lockattr;
  if (pthread_condattr_init(&condAttr) != 0)
    throw runtime_error("pthread_condattr_init() failed");
  if (pthread_mutexattr_init(&lockattr) != 0)
    throw runtime_error("pthread_mutex_init() failed");
  if (pthread_condattr_setpshared(&condAttr, PTHREAD_PROCESS_SHARED) != 0)
    throw runtime_error("pthread_condattr_setpshared() failed");
  if (pthread_mutexattr_setpshared(&lockattr, PTHREAD_PROCESS_SHARED) != 0)
    throw runtime_error("pthread_mutexattr_setpshared() failed");
  struct SyncData* syncData = (struct SyncData*)ptr;
  if (pthread_cond_init(&syncData->cond, &condAttr) != 0)
    throw runtime_error("pthread_cond_init() failed");
  if (pthread_mutex_init(&syncData->lock, &lockattr) != 0)
    throw runtime_error("pthread_mutex_init() failed");
  syncData->event = -1;
  munmap(ptr, SHM_SIZE);
  cout << "Sync data block created" << endl;
}

void CompatTest::close()
{
}

void CompatTest::run()
{
  init();
  const pid_t pid = fork();
  if (pid == (pid_t)-1)
    throw runtime_error(string("fork: ") + strerror(errno));
  if (pid != 0)
    cout << "Child process pid is " << pid << endl;
  if (pid == 0)
    {
      cout << "Starting the child process" << endl;
      
      const int shmFd = shm_open(SHM_NAME, O_RDWR, 0600);
      if (shmFd == -1)
	throw runtime_error(string("shm_open: ") + strerror(errno));
      void* const ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
      if (ptr == MAP_FAILED)
	{
	  string info = strerror(errno);
	  ::close(shmFd);
	  throw runtime_error("mmap: " + info);
	}
      ::close(shmFd);
      struct SyncData* const syncData = (struct SyncData*)ptr;
      
      while(1)
	{
	  
	  if (pthread_mutex_lock(&syncData->lock) != 0)
	    throw runtime_error("pthread_mutex_lock() failed");
	  while(syncData->event < 0)
	    if (pthread_cond_wait(&syncData->cond, &syncData->lock) != 0)
	      throw runtime_error("pthread_cond_wait() failed");
	  const int event = syncData->event;
	  syncData->event = -1;
	  if (pthread_mutex_unlock(&syncData->lock) != 0)
	    throw runtime_error("pthread_mutex_unlock() failed");
	  cout << "Catching " << event << endl;
	  if (event == 9)
	    {
	      cout << "Exiting the child process, caught 10 events" << endl;
	      exit(EXIT_SUCCESS);      
	    }
	}
    }
  
  const int shmFd = shm_open(SHM_NAME, O_RDWR, 0600);
  if (shmFd == -1)
    throw runtime_error(string("shm_open: ") + strerror(errno));
  void* const ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
  if (ptr == MAP_FAILED)
    {
      string info = strerror(errno);
      ::close(shmFd);
      throw runtime_error("mmap: " + info);
    }
  ::close(shmFd);
  struct SyncData* const syncData = (struct SyncData*)ptr;
  for(int i = 0;i < 10;++i)
    {
      cout << "Sending " << i << endl;;
      if (pthread_mutex_lock(&syncData->lock) != 0)
	throw runtime_error("pthread_mutex_lock() failed");
      syncData->event = i;
      if (pthread_cond_signal(&syncData->cond) != 0)
	throw runtime_error("pthread_cond_signal() failed");
      if (pthread_mutex_unlock(&syncData->lock) != 0)
	throw runtime_error("pthread_mutex_unlock() failed");
      this_thread::sleep_for(std::chrono::seconds(1));
    }
  
  
  cout << "Waiting" << endl;
  int exitCode;
  wait(&exitCode);
  cout << "Finished" << endl;
  cout << exitCode << endl;
  
  
}
