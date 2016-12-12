SET(SOURCES
  igtl_header.c
  igtl_tdata.c
  igtl_util.c
  )

SET(INCLUDE_FILES
  igtl_header.h
  igtl_typeconfig.h
  igtl_types.h
  igtl_util.h
  igtl_win32header.h
)

ADD_LIBRARY(tslib
  ${SOURCES}
  ${INCLUDE_FILES}
  )

ADD_EXECUTABLE(igtl_image_test time_stamp_demo.c)

TARGET_LINK_LIBRARIES(igtl_image_test tslib)
