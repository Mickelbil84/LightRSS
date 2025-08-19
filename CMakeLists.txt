cmake_minimum_required(VERSION 3.13) # Fun fact: 3.13 is the latest version working on Windows XP (that I know of, at least)

project(LightRSS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# TODO: Check if we need to use the /bigobj compile option for Windows (probably not)

##########################

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(fmt REQUIRED) # Note that Windows XP needs to use fmt version 4
find_package(CURL REQUIRED)
find_package(Catch2 REQUIRED)

set(LIGHTRSS_LIBRARIES fmt::fmt CURL::libcurl)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
    src/main.cpp

    src/core/lrss_parser.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIGHTRSS_LIBRARIES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

add_executable(tests
    tests/main.cpp
    tests/test_curl.cpp
)
target_link_libraries(tests PRIVATE ${LIGHTRSS_LIBRARIES} Catch2::Catch2 Catch2::Catch2WithMain)
target_compile_features(tests PUBLIC cxx_std_11)