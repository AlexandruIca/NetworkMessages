#include <spdlog/spdlog.h>

#include "common/message.hpp"

enum class msg_type
{
    fire_bullet,
    move_player
};

auto main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> int
{
    net::message<msg_type> msg{};
    msg.header.id = msg_type::fire_bullet;

    int a = 1;
    bool b = true;
    float c = -1.0F;

    constexpr auto array_size = 5;

    using position_t = struct
    {
        float x = 0.0F;
        float y = 0.0F;
    };

    std::array<position_t, array_size> pos{};

    {
        using namespace net::operators;
        msg << a << b << c << pos;

        spdlog::info("Message: {}", msg);

        a = 0;
        b = false;
        c = 0.0F;

        msg >> pos >> c >> b >> a;

        spdlog::info("a: {}, b: {}, c: {}, pos[0].x: {}", a, b, c, pos[0].x);
    }
}
