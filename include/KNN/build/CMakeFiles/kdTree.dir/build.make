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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.5.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.5.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build"

# Include any dependencies generated for this target.
include CMakeFiles/kdTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kdTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kdTree.dir/flags.make

CMakeFiles/kdTree.dir/kdTree.cpp.o: CMakeFiles/kdTree.dir/flags.make
CMakeFiles/kdTree.dir/kdTree.cpp.o: ../kdTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/kdTree.dir/kdTree.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kdTree.dir/kdTree.cpp.o -c "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/kdTree.cpp"

CMakeFiles/kdTree.dir/kdTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kdTree.dir/kdTree.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/kdTree.cpp" > CMakeFiles/kdTree.dir/kdTree.cpp.i

CMakeFiles/kdTree.dir/kdTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kdTree.dir/kdTree.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/kdTree.cpp" -o CMakeFiles/kdTree.dir/kdTree.cpp.s

CMakeFiles/kdTree.dir/kdTree.cpp.o.requires:

.PHONY : CMakeFiles/kdTree.dir/kdTree.cpp.o.requires

CMakeFiles/kdTree.dir/kdTree.cpp.o.provides: CMakeFiles/kdTree.dir/kdTree.cpp.o.requires
	$(MAKE) -f CMakeFiles/kdTree.dir/build.make CMakeFiles/kdTree.dir/kdTree.cpp.o.provides.build
.PHONY : CMakeFiles/kdTree.dir/kdTree.cpp.o.provides

CMakeFiles/kdTree.dir/kdTree.cpp.o.provides.build: CMakeFiles/kdTree.dir/kdTree.cpp.o


CMakeFiles/kdTree.dir/main.cpp.o: CMakeFiles/kdTree.dir/flags.make
CMakeFiles/kdTree.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/kdTree.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kdTree.dir/main.cpp.o -c "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/main.cpp"

CMakeFiles/kdTree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kdTree.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/main.cpp" > CMakeFiles/kdTree.dir/main.cpp.i

CMakeFiles/kdTree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kdTree.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/main.cpp" -o CMakeFiles/kdTree.dir/main.cpp.s

CMakeFiles/kdTree.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/kdTree.dir/main.cpp.o.requires

CMakeFiles/kdTree.dir/main.cpp.o.provides: CMakeFiles/kdTree.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/kdTree.dir/build.make CMakeFiles/kdTree.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/kdTree.dir/main.cpp.o.provides

CMakeFiles/kdTree.dir/main.cpp.o.provides.build: CMakeFiles/kdTree.dir/main.cpp.o


CMakeFiles/kdTree.dir/stb.cpp.o: CMakeFiles/kdTree.dir/flags.make
CMakeFiles/kdTree.dir/stb.cpp.o: ../stb.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/kdTree.dir/stb.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kdTree.dir/stb.cpp.o -c "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/stb.cpp"

CMakeFiles/kdTree.dir/stb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kdTree.dir/stb.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/stb.cpp" > CMakeFiles/kdTree.dir/stb.cpp.i

CMakeFiles/kdTree.dir/stb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kdTree.dir/stb.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/stb.cpp" -o CMakeFiles/kdTree.dir/stb.cpp.s

CMakeFiles/kdTree.dir/stb.cpp.o.requires:

.PHONY : CMakeFiles/kdTree.dir/stb.cpp.o.requires

CMakeFiles/kdTree.dir/stb.cpp.o.provides: CMakeFiles/kdTree.dir/stb.cpp.o.requires
	$(MAKE) -f CMakeFiles/kdTree.dir/build.make CMakeFiles/kdTree.dir/stb.cpp.o.provides.build
.PHONY : CMakeFiles/kdTree.dir/stb.cpp.o.provides

CMakeFiles/kdTree.dir/stb.cpp.o.provides.build: CMakeFiles/kdTree.dir/stb.cpp.o


# Object files for target kdTree
kdTree_OBJECTS = \
"CMakeFiles/kdTree.dir/kdTree.cpp.o" \
"CMakeFiles/kdTree.dir/main.cpp.o" \
"CMakeFiles/kdTree.dir/stb.cpp.o"

# External object files for target kdTree
kdTree_EXTERNAL_OBJECTS =

kdTree: CMakeFiles/kdTree.dir/kdTree.cpp.o
kdTree: CMakeFiles/kdTree.dir/main.cpp.o
kdTree: CMakeFiles/kdTree.dir/stb.cpp.o
kdTree: CMakeFiles/kdTree.dir/build.make
kdTree: vecmath/libvecmath2.a
kdTree: CMakeFiles/kdTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable kdTree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kdTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kdTree.dir/build: kdTree

.PHONY : CMakeFiles/kdTree.dir/build

CMakeFiles/kdTree.dir/requires: CMakeFiles/kdTree.dir/kdTree.cpp.o.requires
CMakeFiles/kdTree.dir/requires: CMakeFiles/kdTree.dir/main.cpp.o.requires
CMakeFiles/kdTree.dir/requires: CMakeFiles/kdTree.dir/stb.cpp.o.requires

.PHONY : CMakeFiles/kdTree.dir/requires

CMakeFiles/kdTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kdTree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kdTree.dir/clean

CMakeFiles/kdTree.dir/depend:
	cd "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN" "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN" "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build" "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build" "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build/CMakeFiles/kdTree.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/kdTree.dir/depend

