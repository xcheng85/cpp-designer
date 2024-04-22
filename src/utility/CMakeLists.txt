add_library(utility_obj OBJECT
    publisher.cpp subscriber.cpp tokenizer.cpp
)

# PUBLIC is needed here

target_include_directories(utility_obj PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

set_target_properties(utility_obj PROPERTIES
    PUBLIC_HEADER "src/utility/include/utility/event_system_exception.h;\
    src/utility/include/utility/publisher.h;\
    src/utility/include/utility/subscriber.h;\
    src/utility/include/utility/tokenizer.h"
    POSITION_INDEPENDENT_CODE 1
)

add_library(utility_shared SHARED)
target_link_libraries(utility_shared utility_obj)
add_library(utility_static STATIC)
target_link_libraries(utility_static PUBLIC utility_obj)
