#ifndef NET_COMMON_MESSAGE_HPP
#define NET_COMMON_MESSAGE_HPP
#pragma once

#include <fmt/format.h>

#include <cstdint>
#include <cstring>
#include <type_traits>
#include <vector>

namespace net {

template<typename T>
struct message_header
{
public:
    T id{};
    std::uint64_t size{ sizeof(message_header) };
};

template<typename T>
struct message
{
public:
    message_header<T> header{};
    std::vector<std::uint8_t> body{};

    [[nodiscard]] auto size() const noexcept -> std::size_t
    {
        return sizeof(message_header<T>) + body.size();
    }
};

namespace operators {

template<typename T, typename DataType>
auto operator<<(message<T>& msg, DataType const& data) -> message<T>&
{
    static_assert(std::is_standard_layout_v<T>, "Data must have standard layout for `message<T>`!");

    auto const offset = msg.body.size();

    msg.body.resize(offset + sizeof(DataType));
    std::memcpy(msg.body.data() + offset, &data, sizeof(DataType));
    msg.header.size = msg.size();

    return msg;
}

template<typename T, typename DataType>
auto operator>>(message<T>& msg, DataType& data) -> message<T>&
{
    static_assert(std::is_standard_layout_v<T>, "Data must have standard layout for `message<T>`!");

    auto const offset = msg.body.size() - sizeof(DataType);

    std::memcpy(&data, msg.body.data() + offset, sizeof(DataType));
    msg.body.resize(offset);
    msg.header.size = msg.size();

    return msg;
}

} // namespace operators

} // namespace net

template<typename T>
struct fmt::formatter<net::message<T>>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(net::message<T> const& msg, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "ID: {} Size: {}", static_cast<int>(msg.header.id), msg.header.size);
    }
};

#endif // !NET_COMMON_MESSAGE_HPP
