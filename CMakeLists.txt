cmake_minimum_required(VERSION 3.5)
project(linguistic_parser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -DDEBUG -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Wall -msse4.2 -march=corei7 -mtune=corei7 -O3 -DNDEBUG -g")

include_directories(linguistic_parser server /usr/local/include)
set(SOURCE_FILES
	linguistic_parser/main.cpp
	linguistic_parser/word_stats.cpp
	linguistic_parser/parser.cpp
	server/authenticate.cpp
	server/channels.cpp
	server/crypto.cpp
	server/http_base.cpp
	server/request.cpp
	server/response.cpp
	server/string_utils.cpp
	server/bitcoin.cpp
	server/sms.cpp
	server/email.cpp
	server/location.cpp
	server/notifications.cpp
	server/websocket_base.cpp)

add_executable(linguistic_parser ${SOURCE_FILES} /usr/local/lib/libchris.a /usr/local/lib/civetweb.o /usr/local/lib/CivetServer.o)
target_link_libraries(linguistic_parser PRIVATE pthread dl ssl crypto boost_system boost_thread mysqlcppconn)
