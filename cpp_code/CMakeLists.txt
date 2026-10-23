cmake_minimum_required(VERSION 3.15)
project(NSDS_CUAS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(utility)
add_subdirectory(gnc)
add_subdirectory(lidar)

add_executable(NSDS_CUAS sentry.cpp)

target_link_libraries(NSDS_CUAS 
	PRIVATE 
		util
		gnc
		lidar
)