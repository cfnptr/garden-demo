# Copyright 2024-2024 Nikita Fediuchin. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#***********************************************************************************************************************
cmake_minimum_required(VERSION 3.24)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "Prevented in-tree build")
endif()

if(TARGET garden-demo)
	return()
endif()

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/libraries/garden/CMakeLists.txt)
	message(FATAL_ERROR "Use 'git submodule update --init --recursive' to download Garden engine.")
endif()

include(libraries/garden/cmake/package-managers.cmake)

project(GardenDemo VERSION 0.0.1 LANGUAGES CXX
	DESCRIPTION "Garden game engine demo application."
	HOMEPAGE_URL "https://github.com/cfnptr/garden-demo")

string(TIMESTAMP GARDEN_DEMO_CURRENT_YEAR "%Y")
set(GARDEN_APP_NAME "Garden Demo")
set(GARDEN_APP_NAME_LOWERCASE "garden-demo")
set(GARDEN_APP_NAMESPACE "garden::demo")
set(GARDEN_APP_FILE_NAME "Garden Demo")
set(GARDEN_APP_DESCRIPTION ${GardenDemo_DESCRIPTION})
set(GARDEN_APP_CREATOR "Nikita Fediuchin")
set(GARDEN_APP_COPYRIGHT "2022-${GARDEN_DEMO_CURRENT_YEAR} ${GARDEN_APP_CREATOR}. All rights reserved.")
set(GARDEN_APP_VERSION_MAJOR ${GardenDemo_VERSION_MAJOR})
set(GARDEN_APP_VERSION_MINOR ${GardenDemo_VERSION_MINOR})
set(GARDEN_APP_VERSION_PATCH ${GardenDemo_VERSION_PATCH})
set(GARDEN_APP_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)
set(GARDEN_APP_CACHES_DIR ${PROJECT_SOURCE_DIR}/.caches)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(GARDEN_DEMO_INCLUDE_DIRS ${PROJECT_BINARY_DIR}/include ${PROJECT_SOURCE_DIR}/include)
set(GARDEN_DEMO_LINK_LIBS garden)

include(libraries/garden/cmake/compile-options.cmake)
include(libraries/garden/cmake/publish-functions.cmake)

# Use these setters for application debugging
#set(GARDEN_RELEASE_EDITOR OFF CACHE BOOL "" FORCE)
#set(GARDEN_RELEASE_DEBUGGING OFF CACHE BOOL "" FORCE)
#set(GARDEN_DEBUG_PACK_RESOURCES ON CACHE BOOL "" FORCE)
#set(GARDEN_USE_GAPI_VALIDATIONS OFF CACHE BOOL "" FORCE)
#set(GARDEN_USE_TRACY_PROFILER ON CACHE BOOL "" FORCE)
add_subdirectory(libraries/garden)

configure_file(libraries/garden/cmake/app-defines.hpp.in include/demo/app-defines.hpp)

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/resources/images/cubemaps/puresky.hdr)
	file(DOWNLOAD https://dl.polyhaven.org/file/ph-assets/HDRIs/hdr/1k/kloofendal_48d_partly_cloudy_puresky_1k.hdr
		${PROJECT_SOURCE_DIR}/resources/images/cubemaps/puresky.hdr)
endif()

#***********************************************************************************************************************
file(GLOB_RECURSE GARDEN_DEMO_SOURCES source/*.cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	configure_file(libraries/garden/cmake/windows.rc.in garden-demo.rc)
	list(APPEND GARDEN_DEMO_SOURCES ${PROJECT_BINARY_DIR}/garden-demo.rc)
	if(GARDEN_DEBUG)
		add_executable(garden-demo ${GARDEN_DEMO_SOURCES})
	else()
		add_executable(garden-demo WIN32 ${GARDEN_DEMO_SOURCES})
	endif()
else()
	add_executable(garden-demo ${GARDEN_DEMO_SOURCES})
endif()

target_include_directories(garden-demo PUBLIC ${GARDEN_DEMO_INCLUDE_DIRS})
target_link_libraries(garden-demo ${GARDEN_DEMO_LINK_LIBS})
set_target_properties(garden-demo PROPERTIES OUTPUT_NAME ${GARDEN_APP_NAME})
add_dependencies(garden-demo packer gslc equi2cube)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	stripExecutable(garden-demo)
endif()
if(GARDEN_PACK_RESOURCES)
	packResources(garden-demo ${GARDEN_APP_CACHES_DIR}
		${GARDEN_APP_RESOURCES_DIR} ${Garden_SOURCE_DIR}/resources
		${GARDEN_RELEASE_EDITOR} ${GARDEN_RELEASE_DEBUGGING})
endif()