#find_package(SFML REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++0x")

add_executable(TestEntitySystem TestEntitySystem.cpp)

target_link_libraries(TestEntitySystem gtest_main)
target_link_libraries(TestEntitySystem gtest)

#include_directories(${SFML_INCLUDE})
#add_executable(Astroids App.cpp)

#target_link_libraries(Astroids sfml-system sfml-window)
#target_link_libraries(Astroids ${SFML_LIBRARIES})
