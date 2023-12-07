#pragma once

#include <thread>
#include <condition_variable>
#include <atomic>
#include <deque>
#include <chrono>
#include <bulkprinter.hpp>

template <typename T>
class AsyncBulkPrinter: public bulk_defs::BulkPrinter
{
public:
    AsyncBulkPrinter(std::size_t threadsCount = 1)
    {
        if (threadsCount == 0)
            threadsCount = 1;

        while (threadsCount > 0) {
            m_threads.emplace_back([this, printer = std::make_unique<T>()](std::stop_token stop_token) mutable
            {
                while (!stop_token.stop_requested()) {
                    std::unique_lock lk(m_mutex);
                    m_cv.wait(lk, [this, &stop_token]
                    {
                        return stop_token.stop_requested()
                            || (m_bulksQ.size() > 0);
                    });

                    if (!m_bulksQ.empty()) {
                        printer->printBulk(m_bulksQ.front());
                        m_bulksQ.pop_front();
                    }

                    using namespace std::chrono_literals;
                }

                std::lock_guard m {m_mutex};
                if (!m_bulksQ.empty()) {
                    printer->printBulk(m_bulksQ.front());
                    m_bulksQ.pop_front();
                }

                std::cerr << "THREAD FINISHED" << std::endl << std::flush;
            });
            --threadsCount;
        }
            
    }
    ~AsyncBulkPrinter() override
    {
        // std::lock_guard m {m_mutex};
        // for (auto &&t : m_threads) {
        //     t.request_stop();
        //     if (t.joinable())
        //         t.join();
        // }
        // m_cv.notify_all();
    };

    void printBulk(std::shared_ptr<const bulk_defs::Bulk> bulk) override final
    {
        std::lock_guard m {m_mutex};
        std::cerr << "printBulk" << std::endl << std::flush;
        m_bulksQ.push_back(bulk);
        m_cv.notify_all();
    }

protected:
    void print(const std::string &) override final {}

private:
    // std::atomic_bool m_finished {false};
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::deque<std::shared_ptr<const bulk_defs::Bulk>> m_bulksQ;
    std::vector<std::jthread> m_threads;
};
