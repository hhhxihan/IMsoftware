cmake_minimum_required(VERSION 3.15)

project(IMsoftware)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
include_directories(Model)
add_executable(${PROJECT_NAME} DBconnPool.cpp IMThread.cpp ThreadPool.cpp utils.cpp MYSQL_DB.cpp 
 Model/friendModel.cpp Model/offlineMsgModel.cpp Model/userModel.cpp IMServer.cpp main.cpp)


# 添加 libevent 的链接库
target_link_libraries(${PROJECT_NAME} PRIVATE -levent  stdc++fs)
