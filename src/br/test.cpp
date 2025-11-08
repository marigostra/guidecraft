
#include "os.h"
#include "RwLock.h"
#include <cstring>
#include "test.h"

namespace GuideCraft {

    void test::read(void* shmem, void* usrmem, size_t size) 
    {
       lock.lock_sharable(); 
       std::memcpy(usrmem, shmem, size);
       lock.unlock_sharable();
       
    }

    void test::write(void* shmem, void* usrmem, size_t size) 
    {
       lock.lockWrite(); 
       std::memcpy(shmem, usrmem, size);
       lock.unlockWrite();
    }


}
