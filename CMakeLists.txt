cmake_minimum_required(VERSION 3.20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

project(camera_recorder)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# 设置QT路径
set(QT_BIN_DIR D:/Qt/Qt5.12.12/5.12.12/msvc2017_64/bin)
#set(Qt5_DIR C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake/Qt5)
#set(CMAKE_MODULE_PATH C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake/Qt5)
set(Qt5_DIR D:/Qt/Qt5.12.12/5.12.12/msvc2017_64/lib/cmake/Qt5)

#set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DUNICODE)

if (CMAKE_CL_64) 
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(BUILD_TYPE "x64-Debug")
    else()
        set(BUILD_TYPE "x64-Release")
    endif()
else()
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(BUILD_TYPE "x86-Debug")
    else()
        set(BUILD_TYPE "x86-Release")
    endif()
endif()

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
set(CMAKE_CXX_STANDARD 17)

set(SDK_DIR ${CMAKE_CURRENT_SOURCE_DIR})
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../cotton-third_party/out/install/${BUILD_TYPE}/${CMAKE_SYSTEM_NAME})
    # set(THIRD_PARTY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../cotton-third_party/out/install/${BUILD_TYPE}/${CMAKE_SYSTEM_NAME}/include)

    # set(CATCH2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../cotton-third_party/Catch2/src)
    # set(CATCH2_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../cotton-third_party/out/build/${BUILD_TYPE}/${CMAKE_SYSTEM_NAME}/lib)
endif()

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/build/${BUILD_TYPE})
message(STATUS ${CMAKE_BINARY_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}/bin)

set(COTTON_STATIC ON)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

	add_definitions(-DWIN32)
	# set(BOOST_LIBS 
	# 	libboost_filesystem-vc143-mt-gd-x64-1_83.lib
	# )
	# set(BOOST_LIBS_DIR
	# 	${SDK_DIR}/../../boost_1_83_0/stage/lib
	# )
	# set(BOOST_INCLUDE_DIR
	# 	${SDK_DIR}/../../boost_1_83_0
	# )
    # set(COTTON_THIRD_STATIC_LIB 
    #     cotton.lib 
    #     Catch2d.lib
    #     Catch2Maind.lib
    #     jsoncpp_static.lib
    # )
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${SDK_DIR})
#add_definitions(-D_NO_CRT_STDIO_INLINE)

# 包含Q_OBJECT的头文件也要添加到这里
file(GLOB SRCS 
./*.cpp
ui/*.h
ui/*.cpp
win_capturer/*.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${SRCS})

#set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)

target_link_libraries(${PROJECT_NAME}
Qt5::Widgets
)

if (EXISTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/translations/qt_zh_CN.qm)
    message("file exists")
else ()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
        COMMAND ${QT_BIN_DIR}/windeployqt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()