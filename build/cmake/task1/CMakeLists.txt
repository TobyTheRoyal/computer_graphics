cmake_minimum_required(VERSION 3.2)

project(task1)

find_package(Threads REQUIRED)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../source/task1")

add_task(task1
	"${SOURCE_DIR}/task_builder.h"
	"${SOURCE_DIR}/task_builder.cpp"
	"${SOURCE_DIR}/RayTracer.h"
	"${SOURCE_DIR}/RayTracer.cpp"
	"${SOURCE_DIR}/BVH.h"
	"${SOURCE_DIR}/BVH.cpp"
	"${SOURCE_DIR}/Scene.h"
	"${SOURCE_DIR}/Scene.cpp"
	"${SOURCE_DIR}/SceneBuilder.h"
	"${SOURCE_DIR}/SceneBuilder.cpp"
	"${SOURCE_DIR}/Task.h"
	"${SOURCE_DIR}/Task.cpp"
	"${SOURCE_DIR}/main.cpp"
	"${SOURCE_DIR}/task1.h"
	"${SOURCE_DIR}/task1.cpp"
)

target_link_libraries(task1 Threads::Threads)

set_directory_properties(${CMAKE_CURRENT_SOURCE_DIR} VS_STARTUP_PROJECT task1)
