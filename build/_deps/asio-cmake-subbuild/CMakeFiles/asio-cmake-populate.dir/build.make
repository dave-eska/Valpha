# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild

# Utility rule file for asio-cmake-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/asio-cmake-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/asio-cmake-populate.dir/progress.make

CMakeFiles/asio-cmake-populate: CMakeFiles/asio-cmake-populate-complete

CMakeFiles/asio-cmake-populate-complete: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-install
CMakeFiles/asio-cmake-populate-complete: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-mkdir
CMakeFiles/asio-cmake-populate-complete: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-download
CMakeFiles/asio-cmake-populate-complete: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update
CMakeFiles/asio-cmake-populate-complete: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-patch
CMakeFiles/asio-cmake-populate-complete: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-configure
CMakeFiles/asio-cmake-populate-complete: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-build
CMakeFiles/asio-cmake-populate-complete: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-install
CMakeFiles/asio-cmake-populate-complete: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'asio-cmake-populate'"
	/usr/bin/cmake -E make_directory /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles
	/usr/bin/cmake -E touch /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles/asio-cmake-populate-complete
	/usr/bin/cmake -E touch /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-done

asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update:
.PHONY : asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update

asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-build: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'asio-cmake-populate'"
	cd /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-build && /usr/bin/cmake -E echo_append
	cd /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-build && /usr/bin/cmake -E touch /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-build

asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-configure: asio-cmake-populate-prefix/tmp/asio-cmake-populate-cfgcmd.txt
asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-configure: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'asio-cmake-populate'"
	cd /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-build && /usr/bin/cmake -E echo_append
	cd /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-build && /usr/bin/cmake -E touch /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-configure

asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-download: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-gitinfo.txt
asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-download: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'asio-cmake-populate'"
	cd /home/dave/Documents/c++/Valpha/build/_deps && /usr/bin/cmake -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE -P /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/tmp/asio-cmake-populate-gitclone.cmake
	cd /home/dave/Documents/c++/Valpha/build/_deps && /usr/bin/cmake -E touch /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-download

asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-install: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'asio-cmake-populate'"
	cd /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-build && /usr/bin/cmake -E echo_append
	cd /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-build && /usr/bin/cmake -E touch /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-install

asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'asio-cmake-populate'"
	/usr/bin/cmake -Dcfgdir= -P /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/tmp/asio-cmake-populate-mkdirs.cmake
	/usr/bin/cmake -E touch /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-mkdir

asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-patch: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-patch-info.txt
asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-patch: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'asio-cmake-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-patch

asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update:
.PHONY : asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update

asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-test: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'asio-cmake-populate'"
	cd /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-build && /usr/bin/cmake -E echo_append
	cd /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-build && /usr/bin/cmake -E touch /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-test

asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update: asio-cmake-populate-prefix/tmp/asio-cmake-populate-gitupdate.cmake
asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update-info.txt
asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'asio-cmake-populate'"
	cd /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-src && /usr/bin/cmake -Dcan_fetch=YES -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE -P /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/tmp/asio-cmake-populate-gitupdate.cmake

CMakeFiles/asio-cmake-populate.dir/codegen:
.PHONY : CMakeFiles/asio-cmake-populate.dir/codegen

asio-cmake-populate: CMakeFiles/asio-cmake-populate
asio-cmake-populate: CMakeFiles/asio-cmake-populate-complete
asio-cmake-populate: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-build
asio-cmake-populate: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-configure
asio-cmake-populate: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-download
asio-cmake-populate: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-install
asio-cmake-populate: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-mkdir
asio-cmake-populate: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-patch
asio-cmake-populate: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-test
asio-cmake-populate: asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/asio-cmake-populate-update
asio-cmake-populate: CMakeFiles/asio-cmake-populate.dir/build.make
.PHONY : asio-cmake-populate

# Rule to build all files generated by this target.
CMakeFiles/asio-cmake-populate.dir/build: asio-cmake-populate
.PHONY : CMakeFiles/asio-cmake-populate.dir/build

CMakeFiles/asio-cmake-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/asio-cmake-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/asio-cmake-populate.dir/clean

CMakeFiles/asio-cmake-populate.dir/depend:
	cd /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild /home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/CMakeFiles/asio-cmake-populate.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/asio-cmake-populate.dir/depend

