# Add the executable
add_executable(
  ${PROJECT_NAME}
  main.cpp
  game_system.cpp
  # Components
  game_objects/components/collision_component.cpp
  game_objects/components/input_component.cpp
  game_objects/components/light_component.cpp
  game_objects/components/shape_component.cpp
  game_objects/components/sprite_component.cpp
  game_objects/components/transform_component.cpp
  # Systems
  systems/physics_system.cpp
  # Managers
  managers/entity_manager.cpp
  # Utils
  utils/color_utils.cpp)

target_include_directories(
  ${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} lib/SFML/include
                          lib/box2d/include)
target_link_libraries(${PROJECT_NAME} box2d sfml-graphics sfml-window
                      sfml-system)

# Windows Only
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:sfml-graphics>
      $<TARGET_FILE:sfml-window> $<TARGET_FILE:sfml-system>
      $<TARGET_FILE:box2d> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# Move Resource folder to executable folder
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
