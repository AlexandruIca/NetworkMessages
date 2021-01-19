function(build_example EXEC_NAME)
  add_executable(${EXEC_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${EXEC_NAME}.cpp)
  target_link_libraries(${EXEC_NAME} PRIVATE asio::asio spdlog::spdlog net::common)
endfunction()

build_example(basic_version)
build_example(message_basic)
