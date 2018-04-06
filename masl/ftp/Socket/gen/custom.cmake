if( TARGET Socket_interface )
target_sources( Socket_interface PRIVATE ${CMAKE_CURRENT_LIST_DIR}/socket_services.cc )
endif()
