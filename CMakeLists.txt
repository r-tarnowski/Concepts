cmake_minimum_required(VERSION 3.0.2)
project(Concepts)

set(CMAKE_BUILD_TYPE Release)

set(SRC_DIR src)
set(LIB_DIR lib)
set(BIN_DIR bin)
set(INCLUDE_DIR include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

set(TARGET_MOTIVATING_EXAMPLE motivating_example)
set(TARGET_COMPLETE_EXAMPLE complete_example)


include_directories(${INCLUDE_DIR} "/export/devel/platform/boost/$ENV{BOOST_VERSION}/boost/include")

link_directories( ${LIB_DIR} )
#set(APP_LINK_LIBS ${TARGET_LIB} dcpsisocpp2 ddskernel dl pthread)

set(CMAKE_CXX_FLAGS "-fPIC -O3 -Wall -Wno-unused-function -std=c++20")

set(SOURCES_MOTIVATING_EXAMPLE ${SRC_DIR}/MotivatingExample.cpp)
set(SOURCES_COMPLETE_EXAMPLE ${SRC_DIR}/CompleteExample.cpp)



#add_library(${TARGET_LIB} STATIC ${SOURCES_LIB})

add_executable(${TARGET_MOTIVATING_EXAMPLE} ${SOURCES_MOTIVATING_EXAMPLE})
add_executable(${TARGET_COMPLETE_EXAMPLE} ${SOURCES_COMPLETE_EXAMPLE})


#target_link_libraries(${TARGET_SUB} ${APP_LINK_LIBS})

#add_dependencies( ${TARGET_SUB} ${TARGET_LIB} )
