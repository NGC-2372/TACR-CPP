# 指定CMake的最低版本要求
cmake_minimum_required(VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# 设置项目名称
project("TACR-CPP")

# 设置Qt的安装路径，确保CMake能够在正确的位置找到Qt模块
# 这里指定了Qt的安装路径，特别是针对MSVC 2022 64位编译器的路径
set(CMAKE_PREFIX_PATH "C:/Program1/Qt/Qt6.9/6.9.0/msvc2022_64")

# 1. 先查找 Qt 模块，再处理子目录
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Charts)  # 必须在 add_subdirectory 前

# 2. 启用 C++20 标准和自动代码生成
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 定义项目的版本号（可选，按需调整）
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

# 3. 启用CMake的自动处理功能
set(CMAKE_AUTOMOC ON)# 自动处理MOC（元对象编译器）生成的代码
set(CMAKE_AUTORCC ON)# 自动处理RCC（资源编译器）生成的代码
set(CMAKE_AUTOUIC ON)# 自动处理UIC（用户界面编译器）生成的代码，如果项目中使用了.ui文件

# 4. 添加头文件路径（可选，按需调整）
include_directories(
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/Library
    ${PROJECT_SOURCE_DIR}/Lbrary/eigen
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/Qtgui
)

# 5. 最后添加子目录（确保 Qt 已找到）
add_subdirectory(src)
add_subdirectory(Qtgui)

# 6. 设置可执行文件的输出目录
# 将生成的可执行文件放在项目的`bin`目录下
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 7. 启用自动包含当前目录的头文件路径，避免在代码中手动指定头文件路径
set(CMAKE_INCLUDE_CURRENT_DIR ON)