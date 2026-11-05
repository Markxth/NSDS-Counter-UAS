add_library(ext STATIC
	doctest.h
	toml.h
)

set_target_properties(ext PROPERTIES LINKER_LANGUAGE CXX)