add_library(model_obj OBJECT
    stack.cpp
)
# for include headers
target_link_libraries(model_obj PRIVATE utility_obj)

# PUBLIC is needed here
target_include_directories(model_obj PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

set(MODEL_PUBLIC_HEADERS
    "src/model/include/model/stack.h"
    )

set_target_properties(model_obj PROPERTIES
    PUBLIC_HEADER ${MODEL_PUBLIC_HEADERS}
    POSITION_INDEPENDENT_CODE 1
)

add_library(model_shared SHARED)
target_link_libraries(model_shared model_obj)
add_library(model_static STATIC)
target_link_libraries(model_static model_obj)
