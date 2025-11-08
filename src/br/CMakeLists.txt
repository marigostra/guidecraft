

add_executable (gcr
  Broker.cpp
  CompatTest.cpp
  BusClient.cpp
  Bus.cpp
  CircularQueue.cpp
  Client.cpp
  main.cpp
  Service.cpp
  Message.cpp
  test.cpp
  RwLock.cpp
  )

target_link_libraries(gcr pthread rt)
