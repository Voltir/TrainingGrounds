#find_package(SFML REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++0x")

set(ENTITY_CPP_FILES
	"EntitySystem.cpp"
)

set(ENTITY_SYSTEM_TEST_FILES
	TestTable.cpp
	#TestEntitySystem.cpp
	#TestView.cpp
)

add_executable(TestEntitySystem_pointer TestEntitySystem_pointer.cpp)
add_executable(TestEntitySystem ${ENTITY_SYSTEM_TEST_FILES} ${ENTITY_CPP_FILES})

target_link_libraries(TestEntitySystem_pointer gtest_main)
target_link_libraries(TestEntitySystem_pointer gtest)

target_link_libraries(TestEntitySystem gtest_main)
target_link_libraries(TestEntitySystem gtest)

#include_directories(${SFML_INCLUDE})
#add_executable(Astroids App.cpp)

#target_link_libraries(Astroids sfml-system sfml-window)
#target_link_libraries(Astroids ${SFML_LIBRARIES})
