# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/ld/yvhqbat.github.io/CPP/network

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ld/yvhqbat.github.io/CPP/network/build

# Include any dependencies generated for this target.
include src/CMakeFiles/tcpclient.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/tcpclient.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/tcpclient.dir/flags.make

src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o: src/CMakeFiles/tcpclient.dir/flags.make
src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o: ../src/TcpClient.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ld/yvhqbat.github.io/CPP/network/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o"
	cd /home/ld/yvhqbat.github.io/CPP/network/build/src && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tcpclient.dir/TcpClient.cpp.o -c /home/ld/yvhqbat.github.io/CPP/network/src/TcpClient.cpp

src/CMakeFiles/tcpclient.dir/TcpClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpclient.dir/TcpClient.cpp.i"
	cd /home/ld/yvhqbat.github.io/CPP/network/build/src && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ld/yvhqbat.github.io/CPP/network/src/TcpClient.cpp > CMakeFiles/tcpclient.dir/TcpClient.cpp.i

src/CMakeFiles/tcpclient.dir/TcpClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpclient.dir/TcpClient.cpp.s"
	cd /home/ld/yvhqbat.github.io/CPP/network/build/src && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ld/yvhqbat.github.io/CPP/network/src/TcpClient.cpp -o CMakeFiles/tcpclient.dir/TcpClient.cpp.s

src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o.requires:
.PHONY : src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o.requires

src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o.provides: src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/tcpclient.dir/build.make src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o.provides.build
.PHONY : src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o.provides

src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o.provides.build: src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o

# Object files for target tcpclient
tcpclient_OBJECTS = \
"CMakeFiles/tcpclient.dir/TcpClient.cpp.o"

# External object files for target tcpclient
tcpclient_EXTERNAL_OBJECTS =

../lib/libtcpclient.a: src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o
../lib/libtcpclient.a: src/CMakeFiles/tcpclient.dir/build.make
../lib/libtcpclient.a: src/CMakeFiles/tcpclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../lib/libtcpclient.a"
	cd /home/ld/yvhqbat.github.io/CPP/network/build/src && $(CMAKE_COMMAND) -P CMakeFiles/tcpclient.dir/cmake_clean_target.cmake
	cd /home/ld/yvhqbat.github.io/CPP/network/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcpclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/tcpclient.dir/build: ../lib/libtcpclient.a
.PHONY : src/CMakeFiles/tcpclient.dir/build

src/CMakeFiles/tcpclient.dir/requires: src/CMakeFiles/tcpclient.dir/TcpClient.cpp.o.requires
.PHONY : src/CMakeFiles/tcpclient.dir/requires

src/CMakeFiles/tcpclient.dir/clean:
	cd /home/ld/yvhqbat.github.io/CPP/network/build/src && $(CMAKE_COMMAND) -P CMakeFiles/tcpclient.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/tcpclient.dir/clean

src/CMakeFiles/tcpclient.dir/depend:
	cd /home/ld/yvhqbat.github.io/CPP/network/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ld/yvhqbat.github.io/CPP/network /home/ld/yvhqbat.github.io/CPP/network/src /home/ld/yvhqbat.github.io/CPP/network/build /home/ld/yvhqbat.github.io/CPP/network/build/src /home/ld/yvhqbat.github.io/CPP/network/build/src/CMakeFiles/tcpclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/tcpclient.dir/depend

