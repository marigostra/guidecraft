// SPDX-License-Identifier: GPL-3.0
// Copyright 2024-2025 Michael Pozhidaev <msp@luwrain.org>

#include "os.h"
#include "CompatTest.h"

#define SHM_NAME "gc-compad-test"
#define SHM_SIZE 4096

struct SyncData
{
  pthread_cond_t cond;
  pthread_mutex_t lock;
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
  pthread_condattr_t condattr;
  pthread_mutexattr_t lockattr;
  if (pthread_condattr_init(&condattr) != 0)
    throw runtime_error("pthread_condattr_init() failed");
  if (pthread_mutexattr_init(&lockattr) != 0)
      throw runtime_error("pthread_mutex_init() failed");
  if (pthread_condattr_setpshared(&condattr, PTHREAD_PROCESS_SHARED) != 0)
    throw runtime_error("pthread_condattr_setpshared() failed");
    if (pthread_mutexattr_setpshared(&lockattr, PTHREAD_PROCESS_SHARED) != 0)
    throw runtime_error("pthread_mutexattr_setpshared() failed");
    struct SyncData* syncData = (SyncData*)ptr;
    if (pthread_cond_init(&syncData->cond, &condattr) != 0)
      throw runtime_error("pthread_cond_init() failed");
    if (pthread_mutex_init(&syncData->lock, &lockattr) != 0)
      throw runtime_error("pthread_mutex_init() failed");
    munmap(ptr, SHM_SIZE);
      cout << "Sync data block created" << endl;
}


void CompatTest::close()
{
  /*


    if (shmdt(ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
    */
}

  void CompatTest::run()
  {
    init();
    const pid_t pid = fork();
    if (pid == (pid_t)-1)
      throw runtime_error(string("fork: ") + strerror(errno));
    cout << "Child process pid is " << pid << endl;
    if (pid == 0)
      {
	cout << "Starting the child process" << endl;
	exit(EXIT_SUCCESS);
      }
    cout << "Waiting" << endl;
    int exitCode;
    wait(&exitCode);
    cout << "Finished" << endl;
    cout << exitCode << endl;

    
  }
