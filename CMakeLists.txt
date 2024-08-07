cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME GoooalHeads)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_definitions(-DSFML_STATIC)

include_directories(
	"ext/SFML-2.6.1/include/"
	"inc/"
)
link_directories(
	"ext/SFML-2.6.1/lib/"
	"ext/SFML-2.6.1/lib/Debug/"
)	

add_executable("${PROJECT_NAME}" 
	src/main.cpp
	inc/Game.hpp src/Game.cpp
	inc/Object.hpp src/Object.cpp
	inc/Ball.hpp src/Ball.cpp
	inc/Player.hpp src/Player.cpp
	inc/Bonus.hpp src/Bonus.cpp
	inc/TextureHolder.hpp src/TextureHolder.cpp
	inc/Vector2f.hpp src/Vector2f.cpp
	inc/functions.hpp src/functions.cpp
	inc/globalConsts.hpp
)

target_link_libraries("${PROJECT_NAME}"
	sfml-system-s-d
	sfml-window-s-d
	sfml-graphics-s-d
	sfml-audio-s-d
	flac
	freetype
	gdi32
	ogg
	openal32
	opengl32
	vorbis
	vorbisenc
	vorbisfile
	winmm
)

file(COPY "ext/SFML-2.6.1/bin/openal32.dll" DESTINATION "/")
file(COPY "media" DESTINATION "/")