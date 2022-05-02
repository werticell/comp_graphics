add_executable(Task4 main.cpp)

# Outputs executable to current @Task_n/bin directory
set_target_properties(Task4
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Deletes all shader files with .glsl extension from previous runs
add_custom_target(DeleteGlslFiles
    COMMAND bash -c "rm ${CMAKE_CURRENT_SOURCE_DIR}/bin/*.glsl"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Copies all shaders from contents of shader folder to a @Task_n/bin directory
add_custom_target(CopyGlslShaders
    COMMAND bash -c "cp -r ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl ${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_dependencies(Task4 CopyGlslShaders)
add_dependencies(Task4 DeleteGlslFiles)

if (APPLE)
  target_link_libraries(Task4 "-framework OpenGL")
  target_link_libraries(Task4 "-framework GLUT")
endif()