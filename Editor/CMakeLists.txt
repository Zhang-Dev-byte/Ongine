cmake_minimum_required(VERSION 3.15)

file(GLOB EDITOR_SRC
	"src/**.cpp"
	"src/**.h"
)
project(Editor)

add_executable(Editor ${EDITOR_SRC})