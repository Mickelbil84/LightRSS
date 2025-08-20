project(tests)

find_package(Catch2 REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/constants.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test_fetcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test_parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test_storage.cpp

    # TODO: Consider making the core into a static/dynamic library
    ${LIGHTRSS_SOURCES_CORE}
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIGHTRSS_LIBRARIES} Catch2::Catch2 Catch2::Catch2WithMain)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})