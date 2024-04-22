add_library(controller_obj OBJECT
    cmd.cpp
    cmd_factory.cpp
    cmd_manager.cpp
    cmd.cpp
    cmd_api.cpp
    cmd_subscriber.cpp
)
# for include headers
# PUBLIC will let consumer of controller without link to utility and model
target_link_libraries(controller_obj PUBLIC utility_obj model_obj view_obj)

# PUBLIC is needed here
target_include_directories(controller_obj PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# split string to multiple lines
set_target_properties(controller_obj PROPERTIES
    PUBLIC_HEADER "src/controller/include/controller/cmd_api.h;\
    src/controller/include/controller/cmd.h;\
    src/controller/include/controller/cmd_manager.h;\
    src/controller/include/controller/cmd_factory.h;\
    src/controller/include/controller/cmd_subscriber.h"
    POSITION_INDEPENDENT_CODE 1
)

add_library(controller_shared SHARED)
target_link_libraries(controller_shared controller_obj)
add_library(controller_static STATIC)
target_link_libraries(controller_static controller_obj)
