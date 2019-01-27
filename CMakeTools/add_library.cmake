# Auxiliary functions


# LIB_NAME must be like boost, zip, e.t.c.
# Not like libzip, libboost and so on
function(add_library_interface LIB_NAME LIB_TYPE)
  if(${LIB_TYPE} STREQUAL "SHARED")
    set(LIB_EXT ".so")
  elseif(${LIB_TYPE} STREQUAL "STATIC")
    set(LIB_EXT ".a")
  else()
    message(FATAL_ERROR "Unknown lib type ${LIB_TYPE} for library ${LIB_NAME}")
  endif()

  if(NOT EXISTS "${CMAKE_SOURCE_DIR}/3PP/lib${LIB_NAME}/")
    message(FATAL_ERROR "No library ${LIB_NAME} in directory ${CMAKE_SOURCE_DIR}/3PP/")
  endif()

  add_library(${LIB_NAME} ${LIB_TYPE} IMPORTED)
  set_target_properties( ${LIB_NAME} PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/3PP/lib${LIB_NAME}/lib/lib${LIB_NAME}.so"
    )
  set(${LIB_NAME}_include "${CMAKE_SOURCE_DIR}/3PP/lib${LIB_NAME}/include" PARENT_SCOPE)

endfunction(add_library_interface)
