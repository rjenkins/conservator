include (CheckIncludeFiles)
include (CheckCXXSourceRuns)
include (CheckCXXCompilerFlag)

# just as an idea
check_include_files(pthread.h HAS_PTHREAD_H)

check_include_files(sys/eventfd.h HAS_EVENTFD)
check_include_files(sys/epoll.h HAS_EPOLL)
check_cxx_compiler_flag(-std=c++0x HAS_CPP11FLAG)

