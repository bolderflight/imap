cmake_minimum_required(VERSION 3.13)
# Project information
project(Imap
  VERSION 2.0.0
  DESCRIPTION "Floating point to integer mapping."
  LANGUAGES CXX
)
# Add the library target
add_library(imap INTERFACE)
# Setup include directories 
target_include_directories(imap INTERFACE src/)

# Example and unit testing if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	# Add the example target
	add_executable(imap_example examples/cmake/imap_example.cc)
	# Add the includes
	target_include_directories(imap_example PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
	# Link libraries to the example target
	target_link_libraries(imap_example
		PRIVATE 
			imap
	)
	# Fetch google test
	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG release-1.10.0
	)
	FetchContent_MakeAvailable(googletest)
	enable_testing()
	include(GoogleTest)
	# Add the test target
	add_executable(imap_test tests/imap_test.cc)
	# Add the includes
	target_include_directories(imap_test PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
	# Link libraries to the test target
	target_link_libraries(imap_test
		PRIVATE 
			imap
			gtest_main 
			gtest
			gmock
	)
	# Discover unit tests
	gtest_discover_tests(imap_test)
endif()
