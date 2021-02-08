#ifndef NET_COMMON_CONNECTION
#define NET_COMMON_CONNECTION
#pragma once

#include <asio.hpp>

#include <memory>

#include "message.hpp"
#include "tsqueue.hpp"

namespace net {

template<typename T>
class connection : public std::enable_shared_from_this<connection<T>>
{
public:
    connection() = default;
    virtual ~connection() = default;

    auto connect_to_server() -> bool;
    auto disconnect() -> bool;
    auto is_connected() const -> bool;

    auto send(message<T> const& msg) -> bool;

protected:
    asio::ip::tcp::socket m_socket;
    asio::io_context& m_asio_context;
    tsqueue<message<T>> m_messages_out;
    tsqueue<owned_message<T>> m_messages_in;
};

} // namespace net

#endif // !NET_COMMON_CONNECTION
