include(GoogleTest)

add_executable(test_betree)
target_sources(test_betree PRIVATE test_build.cc test_runtime.cc)
target_link_libraries(test_betree PRIVATE gmock_main betree)
target_compile_features(test_betree PRIVATE cxx_std_20)
target_compile_options(test_betree PRIVATE -Wall -Werror -Wno-unknown-warning-option)

gtest_discover_tests(test_betree)
