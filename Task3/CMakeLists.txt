add_executable(Task3 main.cpp)

# Outputs executable to current @Task_n/bin directory
set_target_properties(Task3
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Copies all shaders from contents of shader folder to a @Task_n/bin directory
add_custom_target(CopyGlslShaders3
    COMMAND bash -c "cp -r ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl ${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_dependencies(Task3 CopyGlslShaders3)

if (APPLE)
  target_link_libraries(Task3 "-framework OpenGL")
  target_link_libraries(Task3 "-framework GLUT")
endif()
