add_executable(Task1 main.cpp)

# Outputs executable to current @Task_n/bin directory
set_target_properties(Task1
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Deletes all shader files with .glsl extension from previous runs
add_custom_target(DeleteGlslFilesTask1
    COMMAND bash -c "rm ${CMAKE_CURRENT_SOURCE_DIR}/bin/*.glsl"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Copies all shaders from contents of shader folder to a @Task_n/bin directory
add_custom_target(CopyGlslFilesTask1
    COMMAND bash -c "cp -r ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ ${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_dependencies(Task1 DeleteGlslFilesTask1)
add_dependencies(Task1 CopyGlslFilesTask1)

if (APPLE)
  target_link_libraries(Task1 "-framework OpenGL")
  target_link_libraries(Task1 "-framework GLUT")
endif()
