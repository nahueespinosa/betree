include(GoogleTest)

add_executable(basic_test)
target_sources(basic_test PRIVATE test.cc)
target_link_libraries(basic_test PRIVATE gtest_main)

gtest_discover_tests(basic_test)
