# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_SOURCE_DIR = /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania

# Include any dependencies generated for this target.
include external/CMakeFiles/external.dir/depend.make

# Include the progress variables for this target.
include external/CMakeFiles/external.dir/progress.make

# Include the compile flags for this target's objects.
include external/CMakeFiles/external.dir/flags.make

external/CMakeFiles/external.dir/isPrime.cpp.o: external/CMakeFiles/external.dir/flags.make
external/CMakeFiles/external.dir/isPrime.cpp.o: external/isPrime.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/CMakeFiles/external.dir/isPrime.cpp.o"
	cd /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/external.dir/isPrime.cpp.o -c /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external/isPrime.cpp

external/CMakeFiles/external.dir/isPrime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/external.dir/isPrime.cpp.i"
	cd /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external/isPrime.cpp > CMakeFiles/external.dir/isPrime.cpp.i

external/CMakeFiles/external.dir/isPrime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/external.dir/isPrime.cpp.s"
	cd /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external/isPrime.cpp -o CMakeFiles/external.dir/isPrime.cpp.s

external/CMakeFiles/external.dir/isPrime.cpp.o.requires:

.PHONY : external/CMakeFiles/external.dir/isPrime.cpp.o.requires

external/CMakeFiles/external.dir/isPrime.cpp.o.provides: external/CMakeFiles/external.dir/isPrime.cpp.o.requires
	$(MAKE) -f external/CMakeFiles/external.dir/build.make external/CMakeFiles/external.dir/isPrime.cpp.o.provides.build
.PHONY : external/CMakeFiles/external.dir/isPrime.cpp.o.provides

external/CMakeFiles/external.dir/isPrime.cpp.o.provides.build: external/CMakeFiles/external.dir/isPrime.cpp.o


# Object files for target external
external_OBJECTS = \
"CMakeFiles/external.dir/isPrime.cpp.o"

# External object files for target external
external_EXTERNAL_OBJECTS =

external/libexternal.a: external/CMakeFiles/external.dir/isPrime.cpp.o
external/libexternal.a: external/CMakeFiles/external.dir/build.make
external/libexternal.a: external/CMakeFiles/external.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libexternal.a"
	cd /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external && $(CMAKE_COMMAND) -P CMakeFiles/external.dir/cmake_clean_target.cmake
	cd /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/external.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/CMakeFiles/external.dir/build: external/libexternal.a

.PHONY : external/CMakeFiles/external.dir/build

external/CMakeFiles/external.dir/requires: external/CMakeFiles/external.dir/isPrime.cpp.o.requires

.PHONY : external/CMakeFiles/external.dir/requires

external/CMakeFiles/external.dir/clean:
	cd /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external && $(CMAKE_COMMAND) -P CMakeFiles/external.dir/cmake_clean.cmake
.PHONY : external/CMakeFiles/external.dir/clean

external/CMakeFiles/external.dir/depend:
	cd /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external /home/wb/ace/code/Studia/Semestr2/PARO/programowanie_wspolbiezne/paro-master/programowanie_wspolbiezne_w_cpp/zadania/external/CMakeFiles/external.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/CMakeFiles/external.dir/depend
