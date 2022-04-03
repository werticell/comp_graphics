add_executable(Task2
    main.cpp
)

# Outputs executable to current @Task_n/bin directory
set_target_properties(Task2
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Deletes all shader files with .glsl extension from previous runs
execute_process(
    COMMAND bash -c "rm ${CMAKE_CURRENT_SOURCE_DIR}/bin/*.glsl"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Copies all shaders from contents of shader folder to a @Task_n/bin directory
execute_process(
    COMMAND bash -c "cp -r ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl ${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Task2 "-framework OpenGL")
target_link_libraries(Task2 "-framework GLUT")
