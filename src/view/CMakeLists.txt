add_library(view_obj OBJECT
    cli.cpp model_subscriber.cpp
)
# for include headers
target_link_libraries(view_obj PUBLIC utility_obj model_obj)

# PUBLIC is needed here
target_include_directories(view_obj PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# split string to multiple lines
set_target_properties(view_obj PROPERTIES
    PUBLIC_HEADER "src/view/include/view/view_base.h; \
    src/view/include/view/cli.h; \
    src/view/include/view/model_subscriber.h"
    POSITION_INDEPENDENT_CODE 1
)

add_library(view_shared SHARED)
target_link_libraries(view_shared view_obj)
add_library(view_static STATIC)
target_link_libraries(view_static PUBLIC view_obj)
