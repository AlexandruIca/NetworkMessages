#ifndef NET_COMMON_CLIENT_INTERFACE_HPP
#define NET_COMMON_CLIENT_INTERFACE_HPP
#pragma once

#include <asio.hpp>
#include <spdlog/spdlog.h>

#include <cstdint>
#include <exception>
#include <memory>
#include <string>
#include <thread>

#include "connection.hpp"
#include "message.hpp"
#include "tsqueue.hpp"

namespace net {

template<typename T>
class client_interface
{
private:
    tsqueue<owned_message<T>> m_messages_in;

protected:
    asio::io_context m_context;
    std::thread m_thr_context;
    asio::ip::tcp::socket m_socket;
    std::unique_ptr<connection<T>> m_connection;

public:
    client_interface()
        : m_socket{ m_context }
    {
    }

    virtual ~client_interface()
    {
        this->disconnect();
    }

    auto connect(std::string const& host, std::uint16_t const port) -> bool
    {
        try {
            m_connection = std::make_unique<connection<T>>();

            asio::ip::tcp::resolver resolver{ m_context };

            // m_endpoints = resolver.resolve(host, std::to_string(port));
            m_connection->connect_to_server(/*m_endpoints*/);
            m_thr_context = std::thread([this]() { m_context.run(); });
        }
        catch(std::exception const& e) {
            spdlog::error("[net::client_interface] Exception thrown: {}", e.what());
            return false;
        }

        return true;
    }

    auto disconnect() -> bool
    {
        if(this->is_connected()) {
            m_connection->disconnect();
        }

        m_context.stop();
        if(m_thr_context.joinable()) {
            m_thr_context.join();
        }
    }

    auto is_connected() -> bool
    {
        if(m_connection) {
            return m_connection->is_connected();
        }

        return false;
    }

    auto incoming() -> tsqueue<owned_message<T>>&
    {
        return m_messages_in;
    }
};

} // namespace net

#endif // !NET_COMMON_CLIENT_INTERFACE_HPP
