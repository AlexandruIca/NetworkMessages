#include <asio.hpp>
#include <asio/executor_work_guard.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include <spdlog/spdlog.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

constexpr std::size_t g_default_buffer_size = 1 * 1024;
std::vector<char> g_buffer(g_default_buffer_size);

auto grab_some_data(asio::ip::tcp::socket& socket) noexcept -> void
{
    socket.async_read_some(asio::buffer(g_buffer.data(), g_buffer.size()),
                           [&](std::error_code const ec, std::size_t const length) {
                               if(!ec) {
                                   spdlog::info("\nRead {} bytes!\n", length);
                               }
                               std::string result{};
                               result.reserve(g_buffer.size() + 1);

                               for(auto const ch : g_buffer) {
                                   result += ch;
                               }

                               spdlog::info("[Part] {}", result);
                               grab_some_data(socket);
                           });
}

auto main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) noexcept -> int
{
    asio::error_code ec;
    asio::io_context context;

    using executor_t = decltype(context.get_executor());

    // prevent `context.run()` to return when there is no more work to do
    asio::executor_work_guard<executor_t> idle_work{ context.get_executor() };
    std::thread context_thread{ [&context]() { context.run(); } };

    constexpr int port = 80;
    asio::ip::tcp::endpoint endpoint{ asio::ip::make_address("51.38.81.49", ec), port };

    asio::ip::tcp::socket socket{ context };

    socket.connect(endpoint, ec);

    if(!ec) {
        spdlog::info("Connected!");
    }
    else {
        spdlog::error("Failed to connect to address: {}", ec.message());
    }

    if(socket.is_open()) {
        grab_some_data(socket);

        std::string req{ "GET /index.html HTTP/1.1\r\n"
                         "Host: example.com\r\n"
                         "Connected: close\r\n\r\n" };

        socket.write_some(asio::buffer(req.data(), req.size()), ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(7s);

        context.stop();

        if(context_thread.joinable()) {
            context_thread.join();
        }
    }
}
