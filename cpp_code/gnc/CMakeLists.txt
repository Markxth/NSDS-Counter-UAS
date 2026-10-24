add_library(gnc STATIC
	controls.cpp
	controls.h
	gnc.cpp
	gnc.h
	guidance.cpp
	guidance.h
	Heuristic.h
	HeuristicConfigLoader.cpp
	HeuristicConfigLoader.h
	HeuristicRuleRegistry.cpp
	HeuristicRuleRegistry.h
	HeuristicRules.cpp
	navigation.cpp
	navigation.h
)

target_include_directories(gnc
	PUBLIC
		${CMAKE_SOURCE_DIR}
)

target_link_libraries(gnc
	PUBLIC
		util
)