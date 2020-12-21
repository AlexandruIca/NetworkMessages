add_executable(asio_example ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(asio_example PRIVATE project::warnings project::options asio::asio spdlog::spdlog)
