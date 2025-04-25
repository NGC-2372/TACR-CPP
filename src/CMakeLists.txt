# 原错误：直接链接 Qt6::Core 但未通过顶层 find_package 引入
# 将源代码文件添加到项目的可执行文件中
# 使用`add_executable`函数创建一个可执行目标，并指定源文件
# WIN32表示这是一个Windows平台的应用程序,调试时不显示控制台窗口
add_executable(${PROJECT_NAME} #WIN32
    main.cpp       # 主入口文件
    # TACR.cpp      # 其他源文件
 "TACR.cpp")

# 正确链接：依赖顶层已找到的 Qt 模块 + 自定义库（如 QtGuiLib）
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Charts
    QtGuiLib       # 链接 UI 库（若存在）
)