# Add the executable
add_executable(${PROJECT_NAME} main.cpp game_system.cpp ship.cpp invader.cpp
                               player.cpp bullet.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE lib/SFML/include
                                                   lib/box2d/include)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Windows Only
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:sfml-graphics>
      $<TARGET_FILE:sfml-window> $<TARGET_FILE:sfml-system>
      $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# Move Resource folder to executable folder
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
