add_subdirectory(glad EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glad)

add_subdirectory(glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)
