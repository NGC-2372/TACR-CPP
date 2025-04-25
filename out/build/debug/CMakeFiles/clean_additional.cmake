# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Qtgui\\CMakeFiles\\QtGuiLib_autogen.dir\\AutogenUsed.txt"
  "Qtgui\\CMakeFiles\\QtGuiLib_autogen.dir\\ParseCache.txt"
  "Qtgui\\QtGuiLib_autogen"
  "src\\CMakeFiles\\TACR-CPP_autogen.dir\\AutogenUsed.txt"
  "src\\CMakeFiles\\TACR-CPP_autogen.dir\\ParseCache.txt"
  "src\\TACR-CPP_autogen"
  )
endif()
