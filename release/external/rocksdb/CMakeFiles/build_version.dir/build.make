# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/daslab/BlockSci-daslab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daslab/BlockSci-daslab/release

# Include any dependencies generated for this target.
include external/rocksdb/CMakeFiles/build_version.dir/depend.make

# Include the progress variables for this target.
include external/rocksdb/CMakeFiles/build_version.dir/progress.make

# Include the compile flags for this target's objects.
include external/rocksdb/CMakeFiles/build_version.dir/flags.make

external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o: external/rocksdb/CMakeFiles/build_version.dir/flags.make
external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o: build_version.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daslab/BlockSci-daslab/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o"
	cd /home/daslab/BlockSci-daslab/release/external/rocksdb && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/build_version.dir/__/__/build_version.cc.o -c /home/daslab/BlockSci-daslab/release/build_version.cc

external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/build_version.dir/__/__/build_version.cc.i"
	cd /home/daslab/BlockSci-daslab/release/external/rocksdb && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daslab/BlockSci-daslab/release/build_version.cc > CMakeFiles/build_version.dir/__/__/build_version.cc.i

external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/build_version.dir/__/__/build_version.cc.s"
	cd /home/daslab/BlockSci-daslab/release/external/rocksdb && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daslab/BlockSci-daslab/release/build_version.cc -o CMakeFiles/build_version.dir/__/__/build_version.cc.s

external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o.requires:

.PHONY : external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o.requires

external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o.provides: external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o.requires
	$(MAKE) -f external/rocksdb/CMakeFiles/build_version.dir/build.make external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o.provides.build
.PHONY : external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o.provides

external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o.provides.build: external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o


build_version: external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o
build_version: external/rocksdb/CMakeFiles/build_version.dir/build.make

.PHONY : build_version

# Rule to build all files generated by this target.
external/rocksdb/CMakeFiles/build_version.dir/build: build_version

.PHONY : external/rocksdb/CMakeFiles/build_version.dir/build

external/rocksdb/CMakeFiles/build_version.dir/requires: external/rocksdb/CMakeFiles/build_version.dir/__/__/build_version.cc.o.requires

.PHONY : external/rocksdb/CMakeFiles/build_version.dir/requires

external/rocksdb/CMakeFiles/build_version.dir/clean:
	cd /home/daslab/BlockSci-daslab/release/external/rocksdb && $(CMAKE_COMMAND) -P CMakeFiles/build_version.dir/cmake_clean.cmake
.PHONY : external/rocksdb/CMakeFiles/build_version.dir/clean

external/rocksdb/CMakeFiles/build_version.dir/depend:
	cd /home/daslab/BlockSci-daslab/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daslab/BlockSci-daslab /home/daslab/BlockSci-daslab/external/rocksdb /home/daslab/BlockSci-daslab/release /home/daslab/BlockSci-daslab/release/external/rocksdb /home/daslab/BlockSci-daslab/release/external/rocksdb/CMakeFiles/build_version.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/rocksdb/CMakeFiles/build_version.dir/depend

