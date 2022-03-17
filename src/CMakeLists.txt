add_library(backburner backburner.c)
target_include_directories(backburner PUBLIC ../inc)
target_link_libraries(backburner PUBLIC pthread)
