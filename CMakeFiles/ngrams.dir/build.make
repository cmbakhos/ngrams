# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying"

# Include any dependencies generated for this target.
include CMakeFiles/ngrams.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ngrams.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ngrams.dir/flags.make

CMakeFiles/ngrams.dir/main.cpp.o: CMakeFiles/ngrams.dir/flags.make
CMakeFiles/ngrams.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ngrams.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ngrams.dir/main.cpp.o -c "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying/main.cpp"

CMakeFiles/ngrams.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ngrams.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying/main.cpp" > CMakeFiles/ngrams.dir/main.cpp.i

CMakeFiles/ngrams.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ngrams.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying/main.cpp" -o CMakeFiles/ngrams.dir/main.cpp.s

# Object files for target ngrams
ngrams_OBJECTS = \
"CMakeFiles/ngrams.dir/main.cpp.o"

# External object files for target ngrams
ngrams_EXTERNAL_OBJECTS =

ngrams: CMakeFiles/ngrams.dir/main.cpp.o
ngrams: CMakeFiles/ngrams.dir/build.make
ngrams: CMakeFiles/ngrams.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ngrams"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ngrams.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ngrams.dir/build: ngrams

.PHONY : CMakeFiles/ngrams.dir/build

CMakeFiles/ngrams.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ngrams.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ngrams.dir/clean

CMakeFiles/ngrams.dir/depend:
	cd "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying" "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying" "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying" "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying" "/mnt/c/Users/cmbak/OneDrive/Desktop/Semester 5/CS 4740/A Bit of Studying/CMakeFiles/ngrams.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ngrams.dir/depend

