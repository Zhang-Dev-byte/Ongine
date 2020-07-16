cmake_minimum_required(VERSION 3.15)

file(GLOB IMGUI_SRC
	"*.cpp"
	"*.h"
)

add_library(imgui ${IMGUI_SRC})