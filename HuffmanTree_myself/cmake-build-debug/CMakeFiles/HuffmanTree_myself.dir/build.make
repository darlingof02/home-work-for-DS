# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HuffmanTree_myself.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HuffmanTree_myself.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HuffmanTree_myself.dir/flags.make

CMakeFiles/HuffmanTree_myself.dir/main.cpp.o: CMakeFiles/HuffmanTree_myself.dir/flags.make
CMakeFiles/HuffmanTree_myself.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HuffmanTree_myself.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HuffmanTree_myself.dir/main.cpp.o -c /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself/main.cpp

CMakeFiles/HuffmanTree_myself.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HuffmanTree_myself.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself/main.cpp > CMakeFiles/HuffmanTree_myself.dir/main.cpp.i

CMakeFiles/HuffmanTree_myself.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HuffmanTree_myself.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself/main.cpp -o CMakeFiles/HuffmanTree_myself.dir/main.cpp.s

# Object files for target HuffmanTree_myself
HuffmanTree_myself_OBJECTS = \
"CMakeFiles/HuffmanTree_myself.dir/main.cpp.o"

# External object files for target HuffmanTree_myself
HuffmanTree_myself_EXTERNAL_OBJECTS =

HuffmanTree_myself: CMakeFiles/HuffmanTree_myself.dir/main.cpp.o
HuffmanTree_myself: CMakeFiles/HuffmanTree_myself.dir/build.make
HuffmanTree_myself: CMakeFiles/HuffmanTree_myself.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HuffmanTree_myself"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HuffmanTree_myself.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HuffmanTree_myself.dir/build: HuffmanTree_myself

.PHONY : CMakeFiles/HuffmanTree_myself.dir/build

CMakeFiles/HuffmanTree_myself.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HuffmanTree_myself.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HuffmanTree_myself.dir/clean

CMakeFiles/HuffmanTree_myself.dir/depend:
	cd /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself/cmake-build-debug /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself/cmake-build-debug /Users/pengyizhuang/Code/Clion_Code/HuffmanTree_myself/cmake-build-debug/CMakeFiles/HuffmanTree_myself.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HuffmanTree_myself.dir/depend

