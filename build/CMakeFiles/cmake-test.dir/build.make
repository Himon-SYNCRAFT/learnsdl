# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/danzaw/CLionProjects/cm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danzaw/CLionProjects/cm/build

# Include any dependencies generated for this target.
include CMakeFiles/cmake-test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmake-test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmake-test.dir/flags.make

CMakeFiles/cmake-test.dir/src/Utils.cpp.o: CMakeFiles/cmake-test.dir/flags.make
CMakeFiles/cmake-test.dir/src/Utils.cpp.o: ../src/Utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danzaw/CLionProjects/cm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cmake-test.dir/src/Utils.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cmake-test.dir/src/Utils.cpp.o -c /home/danzaw/CLionProjects/cm/src/Utils.cpp

CMakeFiles/cmake-test.dir/src/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmake-test.dir/src/Utils.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danzaw/CLionProjects/cm/src/Utils.cpp > CMakeFiles/cmake-test.dir/src/Utils.cpp.i

CMakeFiles/cmake-test.dir/src/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmake-test.dir/src/Utils.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danzaw/CLionProjects/cm/src/Utils.cpp -o CMakeFiles/cmake-test.dir/src/Utils.cpp.s

CMakeFiles/cmake-test.dir/src/Utils.cpp.o.requires:

.PHONY : CMakeFiles/cmake-test.dir/src/Utils.cpp.o.requires

CMakeFiles/cmake-test.dir/src/Utils.cpp.o.provides: CMakeFiles/cmake-test.dir/src/Utils.cpp.o.requires
	$(MAKE) -f CMakeFiles/cmake-test.dir/build.make CMakeFiles/cmake-test.dir/src/Utils.cpp.o.provides.build
.PHONY : CMakeFiles/cmake-test.dir/src/Utils.cpp.o.provides

CMakeFiles/cmake-test.dir/src/Utils.cpp.o.provides.build: CMakeFiles/cmake-test.dir/src/Utils.cpp.o


CMakeFiles/cmake-test.dir/src/main.cpp.o: CMakeFiles/cmake-test.dir/flags.make
CMakeFiles/cmake-test.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danzaw/CLionProjects/cm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cmake-test.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cmake-test.dir/src/main.cpp.o -c /home/danzaw/CLionProjects/cm/src/main.cpp

CMakeFiles/cmake-test.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmake-test.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danzaw/CLionProjects/cm/src/main.cpp > CMakeFiles/cmake-test.dir/src/main.cpp.i

CMakeFiles/cmake-test.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmake-test.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danzaw/CLionProjects/cm/src/main.cpp -o CMakeFiles/cmake-test.dir/src/main.cpp.s

CMakeFiles/cmake-test.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/cmake-test.dir/src/main.cpp.o.requires

CMakeFiles/cmake-test.dir/src/main.cpp.o.provides: CMakeFiles/cmake-test.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/cmake-test.dir/build.make CMakeFiles/cmake-test.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/cmake-test.dir/src/main.cpp.o.provides

CMakeFiles/cmake-test.dir/src/main.cpp.o.provides.build: CMakeFiles/cmake-test.dir/src/main.cpp.o


# Object files for target cmake-test
cmake__test_OBJECTS = \
"CMakeFiles/cmake-test.dir/src/Utils.cpp.o" \
"CMakeFiles/cmake-test.dir/src/main.cpp.o"

# External object files for target cmake-test
cmake__test_EXTERNAL_OBJECTS =

cmake-test: CMakeFiles/cmake-test.dir/src/Utils.cpp.o
cmake-test: CMakeFiles/cmake-test.dir/src/main.cpp.o
cmake-test: CMakeFiles/cmake-test.dir/build.make
cmake-test: CMakeFiles/cmake-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danzaw/CLionProjects/cm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable cmake-test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmake-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmake-test.dir/build: cmake-test

.PHONY : CMakeFiles/cmake-test.dir/build

CMakeFiles/cmake-test.dir/requires: CMakeFiles/cmake-test.dir/src/Utils.cpp.o.requires
CMakeFiles/cmake-test.dir/requires: CMakeFiles/cmake-test.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/cmake-test.dir/requires

CMakeFiles/cmake-test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmake-test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmake-test.dir/clean

CMakeFiles/cmake-test.dir/depend:
	cd /home/danzaw/CLionProjects/cm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danzaw/CLionProjects/cm /home/danzaw/CLionProjects/cm /home/danzaw/CLionProjects/cm/build /home/danzaw/CLionProjects/cm/build /home/danzaw/CLionProjects/cm/build/CMakeFiles/cmake-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cmake-test.dir/depend

