add_library(util STATIC
	datatypes/TargetPackage.h

	math/CoordinateConversions.cpp
	math/CoordinateConversions.h
	math/Math.h
	math/Matrix.h
	math/Vector.h
)

target_include_directories(util
	PUBLIC
		${CMAKE_SOURCE_DIR}
)