cmake_minimum_required(VERSION 3.13.0)
project(RoboticsUltrasoundDemo)

# Locate the ImFusion SDK.
# List required modules/plugins in the COMPONENTS section (e.g. COMPONENTS ImFusionSeg ImFusionReg).
find_package(ImFusionLib REQUIRED)

# Enable automatic MOC, RCC and UIC preprocessing for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# Define and configure the CMake target
set(Sources
	CTToMediumAlgorithm.cpp
	RoboticsUltrasoundDemoPlugin.cpp
	RoboticsUltrasoundDemoFactory.cpp
)
set(Headers
	CTToMediumAlgorithm.h
	RoboticsUltrasoundDemoPlugin.h
	RoboticsUltrasoundDemoFactory.h
)

# Define target library
add_library(RoboticsUltrasoundDemo SHARED ${Sources} ${Headers})
target_include_directories(RoboticsUltrasoundDemo PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)
# Link against the ImFusionLib and selected modules/plugins
target_link_libraries(RoboticsUltrasoundDemo PRIVATE
	ImFusionLib
	)

install(TARGETS RoboticsUltrasoundDemo)

# Define output target directories
# These functions are provided by the ImFusionLib target config.
imfusion_set_common_target_properties()

