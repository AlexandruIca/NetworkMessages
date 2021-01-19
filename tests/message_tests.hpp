#ifndef NET_TEST_MESSAGE_HPP
#define NET_TEST_MESSAGE_HPP
#pragma once

#include <doctest/doctest.h>

#include "common/message.hpp"
#include "example_message_type.hpp"

TEST_CASE("[net::message<T>] Make sure the header size is set accordingly")
{
    net::message<test::msg_type> msg{};
}

#endif // !NET_TEST_MESSAGE_HPP
