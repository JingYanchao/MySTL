# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/jyc/software/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/jyc/software/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jyc/mygithub/MySTL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jyc/mygithub/MySTL/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Test_simple_allocator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Test_simple_allocator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Test_simple_allocator.dir/flags.make

CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o: CMakeFiles/Test_simple_allocator.dir/flags.make
CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o: ../test/test_simple_allocator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jyc/mygithub/MySTL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o -c /home/jyc/mygithub/MySTL/test/test_simple_allocator.cpp

CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jyc/mygithub/MySTL/test/test_simple_allocator.cpp > CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.i

CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jyc/mygithub/MySTL/test/test_simple_allocator.cpp -o CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.s

CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o.requires:

.PHONY : CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o.requires

CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o.provides: CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o.requires
	$(MAKE) -f CMakeFiles/Test_simple_allocator.dir/build.make CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o.provides.build
.PHONY : CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o.provides

CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o.provides.build: CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o


# Object files for target Test_simple_allocator
Test_simple_allocator_OBJECTS = \
"CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o"

# External object files for target Test_simple_allocator
Test_simple_allocator_EXTERNAL_OBJECTS =

Test_simple_allocator: CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o
Test_simple_allocator: CMakeFiles/Test_simple_allocator.dir/build.make
Test_simple_allocator: CMakeFiles/Test_simple_allocator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jyc/mygithub/MySTL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Test_simple_allocator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test_simple_allocator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Test_simple_allocator.dir/build: Test_simple_allocator

.PHONY : CMakeFiles/Test_simple_allocator.dir/build

CMakeFiles/Test_simple_allocator.dir/requires: CMakeFiles/Test_simple_allocator.dir/test/test_simple_allocator.cpp.o.requires

.PHONY : CMakeFiles/Test_simple_allocator.dir/requires

CMakeFiles/Test_simple_allocator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Test_simple_allocator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Test_simple_allocator.dir/clean

CMakeFiles/Test_simple_allocator.dir/depend:
	cd /home/jyc/mygithub/MySTL/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jyc/mygithub/MySTL /home/jyc/mygithub/MySTL /home/jyc/mygithub/MySTL/cmake-build-debug /home/jyc/mygithub/MySTL/cmake-build-debug /home/jyc/mygithub/MySTL/cmake-build-debug/CMakeFiles/Test_simple_allocator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Test_simple_allocator.dir/depend

