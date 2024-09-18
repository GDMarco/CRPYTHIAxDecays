# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build

# Include any dependencies generated for this target.
include CMakeFiles/Decays.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Decays.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Decays.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Decays.dir/flags.make

Decays_wrap.cxx:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating Decays_wrap.cxx"
	swig -builtin -c++ -python -I/Applications/CRPropa/NuGammaInteraction/CRPropa3/build/share/crpropa/swig_interface -I/Applications/CRPropa/NuGammaInteraction/CRPropa3/build/include -I/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/include -I/opt/homebrew/Frameworks/Python.framework/Versions/3.11/include/python3.11 -I/Applications/PYTHIA/pythia8311/include/Pythia8 -dirprot -o /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/Decays_wrap.cxx -outdir /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/Decays.i

CMakeFiles/Decays.dir/Decays_wrap.cxx.o: CMakeFiles/Decays.dir/flags.make
CMakeFiles/Decays.dir/Decays_wrap.cxx.o: Decays_wrap.cxx
CMakeFiles/Decays.dir/Decays_wrap.cxx.o: CMakeFiles/Decays.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Decays.dir/Decays_wrap.cxx.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Decays.dir/Decays_wrap.cxx.o -MF CMakeFiles/Decays.dir/Decays_wrap.cxx.o.d -o CMakeFiles/Decays.dir/Decays_wrap.cxx.o -c /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/Decays_wrap.cxx

CMakeFiles/Decays.dir/Decays_wrap.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Decays.dir/Decays_wrap.cxx.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/Decays_wrap.cxx > CMakeFiles/Decays.dir/Decays_wrap.cxx.i

CMakeFiles/Decays.dir/Decays_wrap.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Decays.dir/Decays_wrap.cxx.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/Decays_wrap.cxx -o CMakeFiles/Decays.dir/Decays_wrap.cxx.s

CMakeFiles/Decays.dir/Decays.cc.o: CMakeFiles/Decays.dir/flags.make
CMakeFiles/Decays.dir/Decays.cc.o: /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/Decays.cc
CMakeFiles/Decays.dir/Decays.cc.o: CMakeFiles/Decays.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Decays.dir/Decays.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Decays.dir/Decays.cc.o -MF CMakeFiles/Decays.dir/Decays.cc.o.d -o CMakeFiles/Decays.dir/Decays.cc.o -c /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/Decays.cc

CMakeFiles/Decays.dir/Decays.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Decays.dir/Decays.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/Decays.cc > CMakeFiles/Decays.dir/Decays.cc.i

CMakeFiles/Decays.dir/Decays.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Decays.dir/Decays.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/Decays.cc -o CMakeFiles/Decays.dir/Decays.cc.s

# Object files for target Decays
Decays_OBJECTS = \
"CMakeFiles/Decays.dir/Decays_wrap.cxx.o" \
"CMakeFiles/Decays.dir/Decays.cc.o"

# External object files for target Decays
Decays_EXTERNAL_OBJECTS =

_Decays.so: CMakeFiles/Decays.dir/Decays_wrap.cxx.o
_Decays.so: CMakeFiles/Decays.dir/Decays.cc.o
_Decays.so: CMakeFiles/Decays.dir/build.make
_Decays.so: /Applications/CRPropa/NuGammaInteraction/CRPropa3/build/lib/libcrpropa.dylib
_Decays.so: /opt/homebrew/Frameworks/Python.framework/Versions/3.11/lib/libpython3.11.dylib
_Decays.so: /Applications/PYTHIA/pythia8311/lib/libpythia8.dylib
_Decays.so: /Applications/PYTHIA/pythia8311/bin/pythia8-config
_Decays.so: CMakeFiles/Decays.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared module _Decays.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Decays.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Decays.dir/build: _Decays.so
.PHONY : CMakeFiles/Decays.dir/build

CMakeFiles/Decays.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Decays.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Decays.dir/clean

CMakeFiles/Decays.dir/depend: Decays_wrap.cxx
	cd /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/CMakeFiles/Decays.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Decays.dir/depend

