add_executable(sdb sdb.cpp)
target_link_libraries(sdb PRIVATE sdb::libsdb)

include(GNUInstallDirs)
install(
    TARGETS sdb
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
