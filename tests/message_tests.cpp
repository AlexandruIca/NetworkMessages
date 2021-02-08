#include <doctest/doctest.h>

#include "common/message.hpp"
#include "example_message_type.hpp"

TEST_CASE("[net::message<T>] Make sure the header/body size is set accordingly")
{
    using namespace net::operators;

    net::message<test::msg_type> msg{};
    std::uint64_t header_size = 0;
    int tmp = 0;

    REQUIRE(msg.header.size == sizeof(msg.header));
    REQUIRE(msg.body.size() == header_size);

    msg << tmp;
    header_size += sizeof(tmp);

    REQUIRE(msg.header.size == sizeof(msg.header) + header_size);
    REQUIRE(msg.body.size() == header_size);

    msg >> tmp;
    header_size -= sizeof(tmp);

    REQUIRE(msg.header.size == sizeof(msg.header));
    REQUIRE(msg.body.size() == header_size);
}

TEST_CASE("[net::message<T>] Make sure the values are set/read accordingly")
{
    using namespace net::operators;

    net::message<test::msg_type> msg{};
    int tmp_int = 0;
    bool tmp_bool = false;

    msg << tmp_int << tmp_bool;

    REQUIRE(msg.header.size == sizeof(msg.header) + sizeof(int) + sizeof(bool));
    REQUIRE(tmp_int == 0);
    REQUIRE(tmp_bool == false);

    tmp_int = -1;
    tmp_bool = true;

    msg >> tmp_bool >> tmp_int;

    REQUIRE(msg.header.size == sizeof(msg.header));
    REQUIRE(tmp_int == 0);
    REQUIRE(tmp_bool == false);
}
