cmake_minimum_required(VERSION 3.13...3.20) # Fun fact: 3.13 is the latest version working on Windows XP (that I know of, at least)

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
find_package(LibXml2 REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/include)
set(LIGHTRSS_SOURCES_CORE
    ${CMAKE_SOURCE_DIR}/src/core/lrss_parser.cpp
    ${CMAKE_SOURCE_DIR}/src/core/lrss_parser_rss.cpp
    ${CMAKE_SOURCE_DIR}/src/core/lrss_parser_atom.cpp
    ${CMAKE_SOURCE_DIR}/src/core/lrss_fetcher.cpp
)
set(LIGHTRSS_LIBRARIES fmt::fmt CURL::libcurl LibXml2::LibXml2)

add_executable(${PROJECT_NAME} src/main.cpp ${LIGHTRSS_SOURCES_CORE})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIGHTRSS_LIBRARIES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

if (NOT DEFINED LRSS_WITH_TESTS)
    set (LRSS_WITH_TESTS true)
endif()

if (LRSS_WITH_TESTS)
    add_subdirectory(tests)
endif()