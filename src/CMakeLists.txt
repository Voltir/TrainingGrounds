add_executable(TestSample1 sample1.cc sample1_unittest.cc)

target_link_libraries(TestSample1 gtest_main)
target_link_libraries(TestSample1 gtest)

add_subdirectory(Astroids)
