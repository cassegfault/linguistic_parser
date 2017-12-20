# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /var/linguistic_processor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /var/linguistic_processor

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /var/linguistic_processor/CMakeFiles /var/linguistic_processor/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /var/linguistic_processor/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named linguistic_parser

# Build rule for target.
linguistic_parser: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 linguistic_parser
.PHONY : linguistic_parser

# fast build rule for target.
linguistic_parser/fast:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/build
.PHONY : linguistic_parser/fast

linguistic_parser/main.o: linguistic_parser/main.cpp.o

.PHONY : linguistic_parser/main.o

# target to build an object file
linguistic_parser/main.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/linguistic_parser/main.cpp.o
.PHONY : linguistic_parser/main.cpp.o

linguistic_parser/main.i: linguistic_parser/main.cpp.i

.PHONY : linguistic_parser/main.i

# target to preprocess a source file
linguistic_parser/main.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/linguistic_parser/main.cpp.i
.PHONY : linguistic_parser/main.cpp.i

linguistic_parser/main.s: linguistic_parser/main.cpp.s

.PHONY : linguistic_parser/main.s

# target to generate assembly for a file
linguistic_parser/main.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/linguistic_parser/main.cpp.s
.PHONY : linguistic_parser/main.cpp.s

linguistic_parser/parser.o: linguistic_parser/parser.cpp.o

.PHONY : linguistic_parser/parser.o

# target to build an object file
linguistic_parser/parser.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/linguistic_parser/parser.cpp.o
.PHONY : linguistic_parser/parser.cpp.o

linguistic_parser/parser.i: linguistic_parser/parser.cpp.i

.PHONY : linguistic_parser/parser.i

# target to preprocess a source file
linguistic_parser/parser.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/linguistic_parser/parser.cpp.i
.PHONY : linguistic_parser/parser.cpp.i

linguistic_parser/parser.s: linguistic_parser/parser.cpp.s

.PHONY : linguistic_parser/parser.s

# target to generate assembly for a file
linguistic_parser/parser.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/linguistic_parser/parser.cpp.s
.PHONY : linguistic_parser/parser.cpp.s

linguistic_parser/word_stats.o: linguistic_parser/word_stats.cpp.o

.PHONY : linguistic_parser/word_stats.o

# target to build an object file
linguistic_parser/word_stats.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/linguistic_parser/word_stats.cpp.o
.PHONY : linguistic_parser/word_stats.cpp.o

linguistic_parser/word_stats.i: linguistic_parser/word_stats.cpp.i

.PHONY : linguistic_parser/word_stats.i

# target to preprocess a source file
linguistic_parser/word_stats.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/linguistic_parser/word_stats.cpp.i
.PHONY : linguistic_parser/word_stats.cpp.i

linguistic_parser/word_stats.s: linguistic_parser/word_stats.cpp.s

.PHONY : linguistic_parser/word_stats.s

# target to generate assembly for a file
linguistic_parser/word_stats.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/linguistic_parser/word_stats.cpp.s
.PHONY : linguistic_parser/word_stats.cpp.s

server/authenticate.o: server/authenticate.cpp.o

.PHONY : server/authenticate.o

# target to build an object file
server/authenticate.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/authenticate.cpp.o
.PHONY : server/authenticate.cpp.o

server/authenticate.i: server/authenticate.cpp.i

.PHONY : server/authenticate.i

# target to preprocess a source file
server/authenticate.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/authenticate.cpp.i
.PHONY : server/authenticate.cpp.i

server/authenticate.s: server/authenticate.cpp.s

.PHONY : server/authenticate.s

# target to generate assembly for a file
server/authenticate.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/authenticate.cpp.s
.PHONY : server/authenticate.cpp.s

server/bitcoin.o: server/bitcoin.cpp.o

.PHONY : server/bitcoin.o

# target to build an object file
server/bitcoin.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/bitcoin.cpp.o
.PHONY : server/bitcoin.cpp.o

server/bitcoin.i: server/bitcoin.cpp.i

.PHONY : server/bitcoin.i

# target to preprocess a source file
server/bitcoin.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/bitcoin.cpp.i
.PHONY : server/bitcoin.cpp.i

server/bitcoin.s: server/bitcoin.cpp.s

.PHONY : server/bitcoin.s

# target to generate assembly for a file
server/bitcoin.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/bitcoin.cpp.s
.PHONY : server/bitcoin.cpp.s

server/channels.o: server/channels.cpp.o

.PHONY : server/channels.o

# target to build an object file
server/channels.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/channels.cpp.o
.PHONY : server/channels.cpp.o

server/channels.i: server/channels.cpp.i

.PHONY : server/channels.i

# target to preprocess a source file
server/channels.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/channels.cpp.i
.PHONY : server/channels.cpp.i

server/channels.s: server/channels.cpp.s

.PHONY : server/channels.s

# target to generate assembly for a file
server/channels.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/channels.cpp.s
.PHONY : server/channels.cpp.s

server/crypto.o: server/crypto.cpp.o

.PHONY : server/crypto.o

# target to build an object file
server/crypto.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/crypto.cpp.o
.PHONY : server/crypto.cpp.o

server/crypto.i: server/crypto.cpp.i

.PHONY : server/crypto.i

# target to preprocess a source file
server/crypto.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/crypto.cpp.i
.PHONY : server/crypto.cpp.i

server/crypto.s: server/crypto.cpp.s

.PHONY : server/crypto.s

# target to generate assembly for a file
server/crypto.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/crypto.cpp.s
.PHONY : server/crypto.cpp.s

server/email.o: server/email.cpp.o

.PHONY : server/email.o

# target to build an object file
server/email.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/email.cpp.o
.PHONY : server/email.cpp.o

server/email.i: server/email.cpp.i

.PHONY : server/email.i

# target to preprocess a source file
server/email.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/email.cpp.i
.PHONY : server/email.cpp.i

server/email.s: server/email.cpp.s

.PHONY : server/email.s

# target to generate assembly for a file
server/email.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/email.cpp.s
.PHONY : server/email.cpp.s

server/http_base.o: server/http_base.cpp.o

.PHONY : server/http_base.o

# target to build an object file
server/http_base.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/http_base.cpp.o
.PHONY : server/http_base.cpp.o

server/http_base.i: server/http_base.cpp.i

.PHONY : server/http_base.i

# target to preprocess a source file
server/http_base.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/http_base.cpp.i
.PHONY : server/http_base.cpp.i

server/http_base.s: server/http_base.cpp.s

.PHONY : server/http_base.s

# target to generate assembly for a file
server/http_base.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/http_base.cpp.s
.PHONY : server/http_base.cpp.s

server/location.o: server/location.cpp.o

.PHONY : server/location.o

# target to build an object file
server/location.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/location.cpp.o
.PHONY : server/location.cpp.o

server/location.i: server/location.cpp.i

.PHONY : server/location.i

# target to preprocess a source file
server/location.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/location.cpp.i
.PHONY : server/location.cpp.i

server/location.s: server/location.cpp.s

.PHONY : server/location.s

# target to generate assembly for a file
server/location.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/location.cpp.s
.PHONY : server/location.cpp.s

server/notifications.o: server/notifications.cpp.o

.PHONY : server/notifications.o

# target to build an object file
server/notifications.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/notifications.cpp.o
.PHONY : server/notifications.cpp.o

server/notifications.i: server/notifications.cpp.i

.PHONY : server/notifications.i

# target to preprocess a source file
server/notifications.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/notifications.cpp.i
.PHONY : server/notifications.cpp.i

server/notifications.s: server/notifications.cpp.s

.PHONY : server/notifications.s

# target to generate assembly for a file
server/notifications.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/notifications.cpp.s
.PHONY : server/notifications.cpp.s

server/request.o: server/request.cpp.o

.PHONY : server/request.o

# target to build an object file
server/request.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/request.cpp.o
.PHONY : server/request.cpp.o

server/request.i: server/request.cpp.i

.PHONY : server/request.i

# target to preprocess a source file
server/request.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/request.cpp.i
.PHONY : server/request.cpp.i

server/request.s: server/request.cpp.s

.PHONY : server/request.s

# target to generate assembly for a file
server/request.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/request.cpp.s
.PHONY : server/request.cpp.s

server/response.o: server/response.cpp.o

.PHONY : server/response.o

# target to build an object file
server/response.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/response.cpp.o
.PHONY : server/response.cpp.o

server/response.i: server/response.cpp.i

.PHONY : server/response.i

# target to preprocess a source file
server/response.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/response.cpp.i
.PHONY : server/response.cpp.i

server/response.s: server/response.cpp.s

.PHONY : server/response.s

# target to generate assembly for a file
server/response.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/response.cpp.s
.PHONY : server/response.cpp.s

server/sms.o: server/sms.cpp.o

.PHONY : server/sms.o

# target to build an object file
server/sms.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/sms.cpp.o
.PHONY : server/sms.cpp.o

server/sms.i: server/sms.cpp.i

.PHONY : server/sms.i

# target to preprocess a source file
server/sms.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/sms.cpp.i
.PHONY : server/sms.cpp.i

server/sms.s: server/sms.cpp.s

.PHONY : server/sms.s

# target to generate assembly for a file
server/sms.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/sms.cpp.s
.PHONY : server/sms.cpp.s

server/string_utils.o: server/string_utils.cpp.o

.PHONY : server/string_utils.o

# target to build an object file
server/string_utils.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/string_utils.cpp.o
.PHONY : server/string_utils.cpp.o

server/string_utils.i: server/string_utils.cpp.i

.PHONY : server/string_utils.i

# target to preprocess a source file
server/string_utils.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/string_utils.cpp.i
.PHONY : server/string_utils.cpp.i

server/string_utils.s: server/string_utils.cpp.s

.PHONY : server/string_utils.s

# target to generate assembly for a file
server/string_utils.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/string_utils.cpp.s
.PHONY : server/string_utils.cpp.s

server/websocket_base.o: server/websocket_base.cpp.o

.PHONY : server/websocket_base.o

# target to build an object file
server/websocket_base.cpp.o:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/websocket_base.cpp.o
.PHONY : server/websocket_base.cpp.o

server/websocket_base.i: server/websocket_base.cpp.i

.PHONY : server/websocket_base.i

# target to preprocess a source file
server/websocket_base.cpp.i:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/websocket_base.cpp.i
.PHONY : server/websocket_base.cpp.i

server/websocket_base.s: server/websocket_base.cpp.s

.PHONY : server/websocket_base.s

# target to generate assembly for a file
server/websocket_base.cpp.s:
	$(MAKE) -f CMakeFiles/linguistic_parser.dir/build.make CMakeFiles/linguistic_parser.dir/server/websocket_base.cpp.s
.PHONY : server/websocket_base.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... linguistic_parser"
	@echo "... linguistic_parser/main.o"
	@echo "... linguistic_parser/main.i"
	@echo "... linguistic_parser/main.s"
	@echo "... linguistic_parser/parser.o"
	@echo "... linguistic_parser/parser.i"
	@echo "... linguistic_parser/parser.s"
	@echo "... linguistic_parser/word_stats.o"
	@echo "... linguistic_parser/word_stats.i"
	@echo "... linguistic_parser/word_stats.s"
	@echo "... server/authenticate.o"
	@echo "... server/authenticate.i"
	@echo "... server/authenticate.s"
	@echo "... server/bitcoin.o"
	@echo "... server/bitcoin.i"
	@echo "... server/bitcoin.s"
	@echo "... server/channels.o"
	@echo "... server/channels.i"
	@echo "... server/channels.s"
	@echo "... server/crypto.o"
	@echo "... server/crypto.i"
	@echo "... server/crypto.s"
	@echo "... server/email.o"
	@echo "... server/email.i"
	@echo "... server/email.s"
	@echo "... server/http_base.o"
	@echo "... server/http_base.i"
	@echo "... server/http_base.s"
	@echo "... server/location.o"
	@echo "... server/location.i"
	@echo "... server/location.s"
	@echo "... server/notifications.o"
	@echo "... server/notifications.i"
	@echo "... server/notifications.s"
	@echo "... server/request.o"
	@echo "... server/request.i"
	@echo "... server/request.s"
	@echo "... server/response.o"
	@echo "... server/response.i"
	@echo "... server/response.s"
	@echo "... server/sms.o"
	@echo "... server/sms.i"
	@echo "... server/sms.s"
	@echo "... server/string_utils.o"
	@echo "... server/string_utils.i"
	@echo "... server/string_utils.s"
	@echo "... server/websocket_base.o"
	@echo "... server/websocket_base.i"
	@echo "... server/websocket_base.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

