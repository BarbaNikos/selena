set(unit_tests_SOURCES
        stream_dsms_test.cc
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(unit_tests ${unit_tests_SOURCES})

target_link_libraries(unit_tests dsms generic_client gtest gtest_main)
