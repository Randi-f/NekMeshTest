cmake_minimum_required(VERSION 3.10)

# 项目名称
project(test)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Nektar++
FIND_PACKAGE(Nektar++ REQUIRED)
ADD_DEFINITIONS(${NEKTAR++_DEFINITIONS})
INCLUDE_DIRECTORIES(SYSTEM ${NEKTAR++_INCLUDE_DIRS} ${NEKTAR++_TP_INCLUDE_DIRS})
LINK_DIRECTORIES(${NEKTAR++_LIBRARY_DIRS} ${NEKTAR++_TP_LIBRARY_DIRS})
MESSAGE(STATUS "Found Nektar++: version ${NEKTAR++_VERSION}")

# 添加库的头文件路径
#include_directories("/Users/shihan/D/IC/Individual_project/codes/nektar++/build/dist/include")

# 添加库文件路径
#link_directories("/Users/shihan/D/IC/Individual_project/codes/nektar++/build/dist/lib")

# 输出库文件目录内容
#file(GLOB LIB_FILES "/Users/shihan/D/IC/Individual_project/codes/nektar++/build/dist/lib/*")
#message(STATUS "Library files: ${LIB_FILES}")

# 查找并添加所有必要的库文件
#find_library(LIBUTILITIES_LIBRARY LibUtilities /Users/shihan/D/IC/Individual_project/codes/#nektar++/build/dist/lib)

#if (LIBUTILITIES_LIBRARY)
#    message(STATUS "Found LibUtilities: ${LIBUTILITIES_LIBRARY}")
#else()
#    message(FATAL_ERROR "LibUtilities not found")
#endif()

# 手动指定库文件路径
#set(LIBUTILITIES_LIBRARY "/Users/shihan/D/IC/Individual_project/codes/nektar++/build/dist/lib/#libLibUtilities.dylib")
# 输出调试信息
#message(STATUS "LibUtilities library: ${LIBUTILITIES_LIBRARY}")

# 添加可执行文件
add_executable(test cad.cpp)

# 链接库文件
target_link_libraries(test ${NEKTAR++_LIBRARIES} ${NEKTAR++_TP_LIBRARIES})

