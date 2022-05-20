add_executable(Task5 main.cpp)

# Outputs executable to current @Task_n/bin directory
set_target_properties(Task5
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin
        )

# Copies all shaders from contents of shader folder to a @Task_n/bin directory
add_custom_target(CopyGlslShaders5
        COMMAND bash -c "cp -r ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl ${CMAKE_CURRENT_SOURCE_DIR}/bin/"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

add_dependencies(Task5 CopyGlslShaders5)

if (APPLE)
    target_link_libraries(Task5 "-framework OpenGL")
    target_link_libraries(Task5 "-framework GLUT")
endif()