add_library(
  ai
  STATIC
  aitraits.cpp
  classic
  difficulty.cpp
  handicaps.cpp
)

target_include_directories(ai PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ai PUBLIC common)

add_subdirectory(default)
add_subdirectory(classic)
