# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wlk/learn/Qt/QComboBox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wlk/learn/Qt/build-QComboBox-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/QComboBox.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/QComboBox.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/QComboBox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QComboBox.dir/flags.make

/home/wlk/learn/Qt/QComboBox/QComboBox_zh_CN.ts: /home/wlk/learn/Qt/QComboBox
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/wlk/learn/Qt/build-QComboBox-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating /home/wlk/learn/Qt/QComboBox/QComboBox_zh_CN.ts"
	/home/wlk/anaconda3/bin/lupdate @/home/wlk/learn/Qt/build-QComboBox-Desktop-Debug/CMakeFiles/QComboBox_zh_CN.ts_lst_file -ts /home/wlk/learn/Qt/QComboBox/QComboBox_zh_CN.ts

CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.o: CMakeFiles/QComboBox.dir/flags.make
CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.o: QComboBox_autogen/mocs_compilation.cpp
CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.o: CMakeFiles/QComboBox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wlk/learn/Qt/build-QComboBox-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.o -MF CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.o -c /home/wlk/learn/Qt/build-QComboBox-Desktop-Debug/QComboBox_autogen/mocs_compilation.cpp

CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wlk/learn/Qt/build-QComboBox-Desktop-Debug/QComboBox_autogen/mocs_compilation.cpp > CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.i

CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wlk/learn/Qt/build-QComboBox-Desktop-Debug/QComboBox_autogen/mocs_compilation.cpp -o CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.s

CMakeFiles/QComboBox.dir/main.cpp.o: CMakeFiles/QComboBox.dir/flags.make
CMakeFiles/QComboBox.dir/main.cpp.o: /home/wlk/learn/Qt/QComboBox/main.cpp
CMakeFiles/QComboBox.dir/main.cpp.o: CMakeFiles/QComboBox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wlk/learn/Qt/build-QComboBox-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/QComboBox.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QComboBox.dir/main.cpp.o -MF CMakeFiles/QComboBox.dir/main.cpp.o.d -o CMakeFiles/QComboBox.dir/main.cpp.o -c /home/wlk/learn/Qt/QComboBox/main.cpp

CMakeFiles/QComboBox.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QComboBox.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wlk/learn/Qt/QComboBox/main.cpp > CMakeFiles/QComboBox.dir/main.cpp.i

CMakeFiles/QComboBox.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QComboBox.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wlk/learn/Qt/QComboBox/main.cpp -o CMakeFiles/QComboBox.dir/main.cpp.s

CMakeFiles/QComboBox.dir/widget.cpp.o: CMakeFiles/QComboBox.dir/flags.make
CMakeFiles/QComboBox.dir/widget.cpp.o: /home/wlk/learn/Qt/QComboBox/widget.cpp
CMakeFiles/QComboBox.dir/widget.cpp.o: CMakeFiles/QComboBox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wlk/learn/Qt/build-QComboBox-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/QComboBox.dir/widget.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QComboBox.dir/widget.cpp.o -MF CMakeFiles/QComboBox.dir/widget.cpp.o.d -o CMakeFiles/QComboBox.dir/widget.cpp.o -c /home/wlk/learn/Qt/QComboBox/widget.cpp

CMakeFiles/QComboBox.dir/widget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QComboBox.dir/widget.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wlk/learn/Qt/QComboBox/widget.cpp > CMakeFiles/QComboBox.dir/widget.cpp.i

CMakeFiles/QComboBox.dir/widget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QComboBox.dir/widget.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wlk/learn/Qt/QComboBox/widget.cpp -o CMakeFiles/QComboBox.dir/widget.cpp.s

# Object files for target QComboBox
QComboBox_OBJECTS = \
"CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/QComboBox.dir/main.cpp.o" \
"CMakeFiles/QComboBox.dir/widget.cpp.o"

# External object files for target QComboBox
QComboBox_EXTERNAL_OBJECTS =

QComboBox: CMakeFiles/QComboBox.dir/QComboBox_autogen/mocs_compilation.cpp.o
QComboBox: CMakeFiles/QComboBox.dir/main.cpp.o
QComboBox: CMakeFiles/QComboBox.dir/widget.cpp.o
QComboBox: CMakeFiles/QComboBox.dir/build.make
QComboBox: /home/wlk/anaconda3/lib/libQt5Widgets.so.5.15.2
QComboBox: /home/wlk/anaconda3/lib/libQt5Gui.so.5.15.2
QComboBox: /home/wlk/anaconda3/lib/libQt5Core.so.5.15.2
QComboBox: CMakeFiles/QComboBox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wlk/learn/Qt/build-QComboBox-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable QComboBox"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QComboBox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QComboBox.dir/build: QComboBox
.PHONY : CMakeFiles/QComboBox.dir/build

CMakeFiles/QComboBox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QComboBox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QComboBox.dir/clean

CMakeFiles/QComboBox.dir/depend: /home/wlk/learn/Qt/QComboBox/QComboBox_zh_CN.ts
	cd /home/wlk/learn/Qt/build-QComboBox-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wlk/learn/Qt/QComboBox /home/wlk/learn/Qt/QComboBox /home/wlk/learn/Qt/build-QComboBox-Desktop-Debug /home/wlk/learn/Qt/build-QComboBox-Desktop-Debug /home/wlk/learn/Qt/build-QComboBox-Desktop-Debug/CMakeFiles/QComboBox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/QComboBox.dir/depend

