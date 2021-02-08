#include <doctest/doctest.h>

#include "common/tsqueue.hpp"

#include <chrono>
#include <thread>

TEST_CASE("[net::tsqueue] push_back() + back() + count() + empty()")
{
    net::tsqueue<int> q;

    REQUIRE(q.count() == 0);
    REQUIRE(q.empty());

    q.push_back(0);
    REQUIRE(q.count() == 1);
    REQUIRE(q.back() == 0);
    q.push_back(1);
    REQUIRE(q.count() == 2);
    REQUIRE(q.back() == 1);
    q.push_back(2);
    REQUIRE(q.count() == 3);
    REQUIRE(q.back() == 2);
    REQUIRE(!q.empty());
}

TEST_CASE("[net::tsqueue] pop_back() + back() + count() + empty()")
{
    net::tsqueue<int> q;

    q.push_back(0);
    q.push_back(1);
    q.push_back(2);

    REQUIRE(q.count() == 3);
    REQUIRE(q.back() == 2);
    q.pop_back();
    REQUIRE(q.count() == 2);
    REQUIRE(q.back() == 1);
    q.pop_back();
    REQUIRE(q.count() == 1);
    REQUIRE(q.back() == 0);
    q.pop_back();
    REQUIRE(q.count() == 0);
    REQUIRE(q.empty());
}

TEST_CASE("[net::tsqueue] push_front() + front() + count() + empty()")
{
    net::tsqueue<int> q;

    REQUIRE(q.count() == 0);
    REQUIRE(q.empty());

    q.push_front(0);
    REQUIRE(q.count() == 1);
    REQUIRE(q.front() == 0);
    q.push_front(1);
    REQUIRE(q.count() == 2);
    REQUIRE(q.front() == 1);
    q.push_front(2);
    REQUIRE(q.count() == 3);
    REQUIRE(q.front() == 2);
}

TEST_CASE("[net::tsqueue] pop_front() + front() + count() + empty()")
{
    net::tsqueue<int> q;

    REQUIRE(q.count() == 0);
    REQUIRE(q.empty());

    q.push_front(0);
    q.push_front(1);
    q.push_front(2);

    REQUIRE(q.count() == 3);
    REQUIRE(q.front() == 2);
    q.pop_front();
    REQUIRE(q.count() == 2);
    REQUIRE(q.front() == 1);
    q.pop_front();
    REQUIRE(q.count() == 1);
    REQUIRE(q.front() == 0);
    q.pop_front();
    REQUIRE(q.count() == 0);
    REQUIRE(q.empty());
}

TEST_CASE("[net::tsqueue] multiple threads")
{
    constexpr int num_elements = 10;
    net::tsqueue<int> q;

    std::thread t1{ [&q] {
        for(int i = 0; i < num_elements; ++i) {
            q.push_back(i * 2);
        }
    } };

    std::thread t2{ [&q] {
        for(int i = num_elements; i < num_elements * 2; ++i) {
            q.push_back(i * 2);
        }
    } };

    std::thread t3{ [&q] {
        static_cast<void>(q.back());
        static_cast<void>(q.front());
        static_cast<void>(q.count());
        static_cast<void>(q.empty());
    } };

    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(50ms);
    }

    t1.join();
    t2.join();
    t3.join();

    REQUIRE(q.count() == 20);
    REQUIRE(!q.empty());
}
