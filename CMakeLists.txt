cmake_minimum_required (VERSION 3.0)

set (CMAKE_CXX_STANDARD 11)

project (Task1)

find_package(OpenGL REQUIRED)

add_subdirectory (external)

include_directories(
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/stb_image
	src
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW
)

file(GLOB src
     "src/*.hpp"
     "src/*.cpp"
     "src/*.glsl"
     "src/*.glsl"
)

add_executable(Task1
	${src}
)
target_link_libraries(Task1
	${ALL_LIBS}
)


