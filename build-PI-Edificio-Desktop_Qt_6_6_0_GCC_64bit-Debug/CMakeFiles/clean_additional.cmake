# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/PI-Edificio_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/PI-Edificio_autogen.dir/ParseCache.txt"
  "PI-Edificio_autogen"
  )
endif()
