add_library(net_common INTERFACE)
add_library(net::common ALIAS net_common)

target_include_directories(net_common INTERFACE ${PROJECT_INCLUDE_DIR})
target_link_libraries(net_common INTERFACE project::options project::warnings spdlog::spdlog)
