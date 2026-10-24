add_library(lidar STATIC
	clustering.cpp
	clustering.h
	detection.cpp
	detection.h
	lidar.cpp
	lidar.h
	preprocessing.cpp
	preprocessing.h
)

target_include_directories(lidar
	PUBLIC
		${CMAKE_SOURCE_DIR}
)