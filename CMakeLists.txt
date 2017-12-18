cmake_minimum_required(VERSION 2.8)

# avoid some cmake warnings
IF(POLICY CMP0026)
    CMAKE_POLICY(SET CMP0026 OLD)
ENDIF()

MESSAGE(STATUS ">>>>>>  This is tiny lib")  
# MESSAGE (STATUS "a: ${a}")

# 查找当前目录下的所有源文件,并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS) # 其实只添加了 main.c

MESSAGE (STATUS ">>>>>>  PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

file(GLOB TH_src
${PROJECT_SOURCE_DIR}/TH/*.c) # 添加 TH 文件夹下的c文件到变量 TH_src 中，不递归

MESSAGE (STATUS ">>>>>>  TH_src:\n${TH_src}")

set(DIR_SRCS ${DIR_SRCS} ${TH_src})

MESSAGE (STATUS ">>>>>>  DIR_SRCS:${DIR_SRCS}")

# 所有变量 DIR_SRCS 中的源文件需要编译成一个名称为 demo 的可执行文件。
add_executable(demo ${DIR_SRCS})
