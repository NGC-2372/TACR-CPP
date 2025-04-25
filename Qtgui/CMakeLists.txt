# 定义项目的源代码文件
# 包括C++源文件、头文件和Qt的UI文件
# set(PROJECT_SOURCE 
#    "src/widget.cpp"
#    "src/widget.h"
#    "src/main.cpp"
#    "src/widget.ui"
#)
# 原错误：未通过顶层配置获取 Qt 模块目标
add_library(QtGuiLib STATIC
    widget.cpp
    widget.h
    widget.ui
)

# 正确链接：直接使用顶层已找到的 Qt 模块
# 将找到的Qt模块链接到项目的可执行文件
# 使用`target_link_libraries`函数将Qt模块链接到目标
target_link_libraries(QtGuiLib
    Qt6::Widgets   # 必需的 UI 模块
    Qt6::Charts    # 图表模块（若使用）
    Qt6::Gui       # 补充 GUI 核心模块（避免 AUTOGEN 警告）
    Qt6::Charts
)

# 暴露头文件路径（供主程序调用 UI 类）
target_include_directories(QtGuiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})