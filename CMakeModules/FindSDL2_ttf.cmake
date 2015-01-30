find_path(SDL2_TTF_INCLUDE_DIR SDL2/SDL_ttf.h)
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf libSDL2_ttf)
set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_INCLUDE_DIR})
set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARY})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_ttf REQUIRED_VARS
	SDL2_TTF_INCLUDE_DIRS
	SDL2_TTF_LIBRARIES)
	
mark_as_advanced(SDL2_TTF_INCLUDE_DIR SDL2_TTF_LIBRARY)