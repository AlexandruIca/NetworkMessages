#include <asio.hpp>
#include <spdlog/spdlog.h>

#include <iostream>

auto main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) noexcept -> int
{
    spdlog::info("Hello there!");
}
