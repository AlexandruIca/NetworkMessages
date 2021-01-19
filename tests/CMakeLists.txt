function(build_test TEST_NAME)
  add_executable(${TEST_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.cpp)
  target_link_libraries(${TEST_NAME} PRIVATE project::options project::warnings asio::asio spdlog::spdlog net::common)
  add_test(${TEST_NAME} ${TEST_NAME})
endfunction()

build_test(basic_version)
build_test(message_test)
