SET(csm_options_sources csm_options.c csm_options_interface.c )
ADD_LIBRARY(csm_options STATIC ${csm_options_sources})

ADD_EXECUTABLE(test_csm_options test_csm_options.c)
TARGET_LINK_LIBRARIES(test_csm_options csm_options)


# installation

FILE(GLOB headers "*.h")
MESSAGE("INSTALLING csm_options headers: ${headers}")
INSTALL(FILES ${headers} DESTINATION include/csm_options)
INSTALL(TARGETS csm_options ARCHIVE DESTINATION lib)
