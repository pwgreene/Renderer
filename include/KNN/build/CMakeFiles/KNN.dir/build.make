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
include CMakeFiles/KNN.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/KNN.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KNN.dir/flags.make

CMakeFiles/KNN.dir/kdTree.cpp.o: CMakeFiles/KNN.dir/flags.make
CMakeFiles/KNN.dir/kdTree.cpp.o: ../kdTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/KNN.dir/kdTree.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KNN.dir/kdTree.cpp.o -c "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/kdTree.cpp"

CMakeFiles/KNN.dir/kdTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KNN.dir/kdTree.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/kdTree.cpp" > CMakeFiles/KNN.dir/kdTree.cpp.i

CMakeFiles/KNN.dir/kdTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KNN.dir/kdTree.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/kdTree.cpp" -o CMakeFiles/KNN.dir/kdTree.cpp.s

CMakeFiles/KNN.dir/kdTree.cpp.o.requires:

.PHONY : CMakeFiles/KNN.dir/kdTree.cpp.o.requires

CMakeFiles/KNN.dir/kdTree.cpp.o.provides: CMakeFiles/KNN.dir/kdTree.cpp.o.requires
	$(MAKE) -f CMakeFiles/KNN.dir/build.make CMakeFiles/KNN.dir/kdTree.cpp.o.provides.build
.PHONY : CMakeFiles/KNN.dir/kdTree.cpp.o.provides

CMakeFiles/KNN.dir/kdTree.cpp.o.provides.build: CMakeFiles/KNN.dir/kdTree.cpp.o


CMakeFiles/KNN.dir/main.cpp.o: CMakeFiles/KNN.dir/flags.make
CMakeFiles/KNN.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/KNN.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KNN.dir/main.cpp.o -c "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/main.cpp"

CMakeFiles/KNN.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KNN.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/main.cpp" > CMakeFiles/KNN.dir/main.cpp.i

CMakeFiles/KNN.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KNN.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/main.cpp" -o CMakeFiles/KNN.dir/main.cpp.s

CMakeFiles/KNN.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/KNN.dir/main.cpp.o.requires

CMakeFiles/KNN.dir/main.cpp.o.provides: CMakeFiles/KNN.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/KNN.dir/build.make CMakeFiles/KNN.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/KNN.dir/main.cpp.o.provides

CMakeFiles/KNN.dir/main.cpp.o.provides.build: CMakeFiles/KNN.dir/main.cpp.o


CMakeFiles/KNN.dir/stb.cpp.o: CMakeFiles/KNN.dir/flags.make
CMakeFiles/KNN.dir/stb.cpp.o: ../stb.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/KNN.dir/stb.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KNN.dir/stb.cpp.o -c "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/stb.cpp"

CMakeFiles/KNN.dir/stb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KNN.dir/stb.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/stb.cpp" > CMakeFiles/KNN.dir/stb.cpp.i

CMakeFiles/KNN.dir/stb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KNN.dir/stb.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/stb.cpp" -o CMakeFiles/KNN.dir/stb.cpp.s

CMakeFiles/KNN.dir/stb.cpp.o.requires:

.PHONY : CMakeFiles/KNN.dir/stb.cpp.o.requires

CMakeFiles/KNN.dir/stb.cpp.o.provides: CMakeFiles/KNN.dir/stb.cpp.o.requires
	$(MAKE) -f CMakeFiles/KNN.dir/build.make CMakeFiles/KNN.dir/stb.cpp.o.provides.build
.PHONY : CMakeFiles/KNN.dir/stb.cpp.o.provides

CMakeFiles/KNN.dir/stb.cpp.o.provides.build: CMakeFiles/KNN.dir/stb.cpp.o


# Object files for target KNN
KNN_OBJECTS = \
"CMakeFiles/KNN.dir/kdTree.cpp.o" \
"CMakeFiles/KNN.dir/main.cpp.o" \
"CMakeFiles/KNN.dir/stb.cpp.o"

# External object files for target KNN
KNN_EXTERNAL_OBJECTS =

libKNN.a: CMakeFiles/KNN.dir/kdTree.cpp.o
libKNN.a: CMakeFiles/KNN.dir/main.cpp.o
libKNN.a: CMakeFiles/KNN.dir/stb.cpp.o
libKNN.a: CMakeFiles/KNN.dir/build.make
libKNN.a: CMakeFiles/KNN.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libKNN.a"
	$(CMAKE_COMMAND) -P CMakeFiles/KNN.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KNN.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KNN.dir/build: libKNN.a

.PHONY : CMakeFiles/KNN.dir/build

CMakeFiles/KNN.dir/requires: CMakeFiles/KNN.dir/kdTree.cpp.o.requires
CMakeFiles/KNN.dir/requires: CMakeFiles/KNN.dir/main.cpp.o.requires
CMakeFiles/KNN.dir/requires: CMakeFiles/KNN.dir/stb.cpp.o.requires

.PHONY : CMakeFiles/KNN.dir/requires

CMakeFiles/KNN.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/KNN.dir/cmake_clean.cmake
.PHONY : CMakeFiles/KNN.dir/clean

CMakeFiles/KNN.dir/depend:
	cd "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN" "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN" "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build" "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build" "/Users/Parker/Documents/MIT/Junior Fall/6.837/project/include/KNN/build/CMakeFiles/KNN.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/KNN.dir/depend

