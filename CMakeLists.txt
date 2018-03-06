cmake_minimum_required(VERSION 3.2)

project(bulk_zeromq VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/async)
include_directories(${PROJECT_SOURCE_DIR}/async/async_otus)
include_directories(${PROJECT_SOURCE_DIR}/async/bulkmt)

configure_file(version.h.in version.h)

add_library(bulkmt SHARED
        async/bulkmt/console_logger.cpp
        async/bulkmt/file_logger.cpp
        async/bulkmt/interpreter.cpp
        async/bulkmt/observer.h
        async/bulkmt/commands_storage.cpp
        async/bulkmt/metricks.cpp
        async/bulkmt/third_party/picosha2/picosha2.h
        )
target_link_libraries(bulkmt -pthread)

add_library(async SHARED
        async/async_otus/async.cpp
        async/async_otus/handles_storage.cpp
        async/async_otus/handle.cpp)
target_link_libraries(async bulkmt)

add_executable(bulk_zeromq_server bulk_server.cpp)
target_link_libraries(bulk_zeromq_server async zmq)

add_executable(bulk_zeromq_client bulk_client.cpp)
target_link_libraries(bulk_zeromq_client zmq)

set_target_properties(bulkmt async bulk_zeromq_server bulk_zeromq_client PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

install(TARGETS
        bulkmt async bulk_zeromq_server bulk_zeromq_client

        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artyom.sorokoumov@gmail.com)

include(CPack)
