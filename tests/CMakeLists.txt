add_executable(project_tests ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/message_tests.cpp
                             ${CMAKE_CURRENT_SOURCE_DIR}/tsqueue_tests.cpp)

target_include_directories(project_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(project_tests PRIVATE doctest::doctest asio::asio spdlog::spdlog net::common)

add_test(project_tests project_tests)
