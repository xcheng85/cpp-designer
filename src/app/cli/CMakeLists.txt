#add_library(cli_obj OBJECT app.cpp)

# for include headers
# no PRIVATE
#target_link_libraries(cli_obj view_obj utility_obj)

add_library(cli_static STATIC app.cpp)
target_link_libraries(cli_static PUBLIC view_static utility_static model_static controller_static)
target_include_directories(cli_static PUBLIC include)

add_executable(cli bootstrap.cpp)
target_link_libraries(cli PUBLIC cli_static)