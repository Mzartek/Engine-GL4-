find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image libSDL2_image)
find_path(SDL2_IMAGE_INCLUDE_DIR SDL2/SDL_image.h)
set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARY})
set(SDL2_IMAGE_INCLUDE_DIRS ${SDL2_IMAGE_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_image REQUIRED_VARS
	SDL2_IMAGE_LIBRARIES
	SDL2_IMAGE_INCLUDE_DIRS)
	
mark_as_advanced(SDL2_IMAGE_LIBRARY SDL2_IMAGE_INCLUDE_DIR)