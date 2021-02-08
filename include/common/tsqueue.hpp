#ifndef NET_COMMON_TSQUEUE_HPP
#define NET_COMMON_TSQUEUE_HPP
#pragma once

#include <cstddef>
#include <deque>
#include <mutex>
#include <utility>

namespace net {

template<typename T>
class tsqueue
{
private:
    mutable std::mutex m_mutex;
    std::deque<T> m_queue;

public:
    tsqueue() = default;
    tsqueue(tsqueue const&) = delete;
    tsqueue(tsqueue&&) noexcept = default;
    ~tsqueue() noexcept = default;

    auto operator=(tsqueue const&) -> tsqueue& = delete;
    auto operator=(tsqueue&&) noexcept -> tsqueue& = default;

    auto front() -> T const&
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        return m_queue.front();
    }

    auto back() -> T const&
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        return m_queue.back();
    }

    auto push_back(T&& elem) -> void
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        m_queue.push_back(std::forward<T>(elem));
    }

    auto push_front(T&& elem) -> void
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        m_queue.push_front(std::forward<T>(elem));
    }

    [[nodiscard]] auto empty() const noexcept -> bool
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        return m_queue.empty();
    }

    [[nodiscard]] auto count() const noexcept -> std::size_t
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        return m_queue.size();
    }

    auto clear() -> void
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        m_queue.clear();
    }

    auto pop_front() -> T
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        auto result = std::move(m_queue.front());
        m_queue.pop_front();
        return result;
    }

    auto pop_back() -> T
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        auto result = std::move(m_queue.back());
        m_queue.pop_back();
        return result;
    }
};

} // namespace net

#endif // !NET_COMMON_TSQUEUE_HPP
