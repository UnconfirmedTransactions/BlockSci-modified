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
include tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/depend.make

# Include the progress variables for this target.
include tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/progress.make

# Include the compile flags for this target's objects.
include tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/flags.make

tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o: tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/flags.make
tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o: ../tools/integrity_check/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daslab/BlockSci-daslab/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o"
	cd /home/daslab/BlockSci-daslab/release/tools/integrity_check && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/blocksci_check_integrity.dir/main.cpp.o -c /home/daslab/BlockSci-daslab/tools/integrity_check/main.cpp

tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/blocksci_check_integrity.dir/main.cpp.i"
	cd /home/daslab/BlockSci-daslab/release/tools/integrity_check && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daslab/BlockSci-daslab/tools/integrity_check/main.cpp > CMakeFiles/blocksci_check_integrity.dir/main.cpp.i

tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/blocksci_check_integrity.dir/main.cpp.s"
	cd /home/daslab/BlockSci-daslab/release/tools/integrity_check && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daslab/BlockSci-daslab/tools/integrity_check/main.cpp -o CMakeFiles/blocksci_check_integrity.dir/main.cpp.s

tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o.requires:

.PHONY : tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o.requires

tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o.provides: tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o.requires
	$(MAKE) -f tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/build.make tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o.provides.build
.PHONY : tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o.provides

tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o.provides.build: tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o


# Object files for target blocksci_check_integrity
blocksci_check_integrity_OBJECTS = \
"CMakeFiles/blocksci_check_integrity.dir/main.cpp.o"

# External object files for target blocksci_check_integrity
blocksci_check_integrity_EXTERNAL_OBJECTS =

tools/integrity_check/blocksci_check_integrity: tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o
tools/integrity_check/blocksci_check_integrity: tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/build.make
tools/integrity_check/blocksci_check_integrity: /usr/lib/x86_64-linux-gnu/libcrypto.so
tools/integrity_check/blocksci_check_integrity: src/libblocksci.so
tools/integrity_check/blocksci_check_integrity: src/internal/libblocksci_internal.a
tools/integrity_check/blocksci_check_integrity: /usr/lib/x86_64-linux-gnu/libcrypto.so
tools/integrity_check/blocksci_check_integrity: external/rocksdb/librocksdb.a
tools/integrity_check/blocksci_check_integrity: /usr/lib/x86_64-linux-gnu/liblz4.so
tools/integrity_check/blocksci_check_integrity: tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daslab/BlockSci-daslab/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable blocksci_check_integrity"
	cd /home/daslab/BlockSci-daslab/release/tools/integrity_check && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/blocksci_check_integrity.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/build: tools/integrity_check/blocksci_check_integrity

.PHONY : tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/build

tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/requires: tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/main.cpp.o.requires

.PHONY : tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/requires

tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/clean:
	cd /home/daslab/BlockSci-daslab/release/tools/integrity_check && $(CMAKE_COMMAND) -P CMakeFiles/blocksci_check_integrity.dir/cmake_clean.cmake
.PHONY : tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/clean

tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/depend:
	cd /home/daslab/BlockSci-daslab/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daslab/BlockSci-daslab /home/daslab/BlockSci-daslab/tools/integrity_check /home/daslab/BlockSci-daslab/release /home/daslab/BlockSci-daslab/release/tools/integrity_check /home/daslab/BlockSci-daslab/release/tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/integrity_check/CMakeFiles/blocksci_check_integrity.dir/depend

