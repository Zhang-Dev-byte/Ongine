cmake_minimum_required(VERSION 3.15)

file(GLOB SANDBOX_SRC
	"src/**.cpp"
	"src/**.h"
)
project(Sandbox)

add_executable(Sandbox ${SANDBOX_SRC})