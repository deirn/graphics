function(lib name)
    add_subdirectory(${name} EXCLUDE_FROM_ALL)
    target_link_libraries(main PRIVATE ${name})
endfunction()

lib(glad)
lib(glfw)
