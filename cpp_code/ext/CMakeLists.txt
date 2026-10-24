add_library(ext STATIC
	toml.h
)

set_target_properties(ext PROPERTIES LINKER_LANGUAGE CXX)