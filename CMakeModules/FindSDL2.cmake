find_library(SDL2_LIBRARY NAMES SDL2 libSDL2)
find_path(SDL2_INCLUDE_DIR SDL2/SDL.h)
set(SDL2_LIBRARIES ${SDL2_LIBRARY})
set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2 REQUIRED_VARS
	SDL2_LIBRARIES
	SDL2_INCLUDE_DIRS)
	
mark_as_advanced(SDL2_LIBRARY SDL2_INCLUDE_DIR)