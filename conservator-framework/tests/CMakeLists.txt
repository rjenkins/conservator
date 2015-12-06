
include_directories(.)

add_executable(ConservatorFrameworkFactoryTest ConservatorFrameworkFactoryTest.cpp)
add_test(ConservatorFrameworkFactoryTest ${CMAKE_BINARY_DIR}/ConservatorFrameworkFactoryTest)
target_link_libraries(ConservatorFrameworkFactoryTest conservator-framework ${ZOOKEEPER_LIBRARY} ${CHECK_LDFLAGS} ${CHECK_CFLAGS})
