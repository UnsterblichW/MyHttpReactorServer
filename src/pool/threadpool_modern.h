#pragma once
#ifndef __THREAD_POOL_MORDERN_H__
#define __THREAD_POOL_MORDERN_H__

#include <atomic>
#include <condition_variable>
//#include <algorithm>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <functional>

class ThreadPool_Modern {
public:
    ThreadPool_Modern(const ThreadPool_Modern&) = delete;
    ThreadPool_Modern& operator=(const ThreadPool_Modern&) = delete;

    static ThreadPool_Modern& instance() {
        static ThreadPool_Modern ins;
        return ins;
    }

    using Task = std::packaged_task<void()>;


    ~ThreadPool_Modern() {
        stop();
    }

    // 要接受一个可调用的函数func，和它的参数列表args，要通用，所以是模板函数+万能引用+auto+变长模板
    // 同时要显式地告诉auto，需要返回一个future类型给外部，future包装的就是函数调用func(args...)的返回值
    template <class F, class... Args>
    auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using RetType = decltype(f(args...));
        if (stop_.load())
            return std::future<RetType>{};

        // 每个具体的task，应该保证它的生命周期在未来被调用的时候依然存在，所以需要make_shared，
        // 否则一旦CommitOneTask结束，task也就死亡了，这是不合理的
        // std::packaged_task必须接收一个可调用的对象，所以RetType后面跟着()
        auto task = std::make_shared<std::packaged_task<RetType()>>(
            // 万能引用搭配完美转发，很有必要
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<RetType> ret = task->get_future();
        {
            std::lock_guard<std::mutex> cv_mt(cv_mt_);
            tasks_.emplace([task] { (*task)(); });
        }
        // 任务队列里面新加了一个任务，唤醒一个在等待（卡在条件变量wait）的线程
        cv_lock_.notify_one();
        // 返回一个此次加入的任务的future对象
        return ret;
    }

    int idleThreadCount() {
        return thread_num_;
    }

private:
    ThreadPool_Modern(unsigned int num = 5)
        : stop_(false) {
            {
                if (num < 1)
                    thread_num_ = 1;
                else
                    thread_num_ = num;
            }
            start();
    }

    // 启动线程池，一个个创建线程，然后放到池里面
    void start() {
        for (int i = 0; i < thread_num_; ++i) {
            pool_.emplace_back([this]() {
                // 每个线程内具体在干什么
                while (!this->stop_.load()) {
                    Task task;
                    {
                        // 从任务队列里面取出来一个任务，得先确定线程池没停下，而且队列里面真的还有任务
                        std::unique_lock<std::mutex> cv_mt(cv_mt_);
                        this->cv_lock_.wait(cv_mt, [this] {
                            return this->stop_.load() || !this->tasks_.empty();
                            });
                        // 避免被cv_lock_条件变量异常唤醒
                        if (this->tasks_.empty())
                            return;
                        // 必须得move出来，因为package_task是不可复制的（这很合理）
                        task = std::move(this->tasks_.front());
                        this->tasks_.pop();
                    }
                    this->thread_num_--;
                    // 已经取出一个任务了，执行它，
                    // 这个任务在执行的时候，咱们pool_里面的可以用的线程其实就少了一个，因为这个现在这个线程在跑task这个任务
                    // 所以跑task之前要thread_num_--，跑完了task要处理的事情后，thread_num_++
                    task();
                    this->thread_num_++;
                }
                });
        }
    }

    // 停止线程池，先得把所有还阻塞住的线程唤醒，唤醒后才能join
    void stop() {
        stop_.store(true);
        cv_lock_.notify_all();
        for (auto& td : pool_) {
            if (td.joinable()) {
                std::cout << "join thread " << td.get_id() << std::endl;
                td.join();
            }
        }
    }

private:
    std::mutex               cv_mt_;
    std::condition_variable  cv_lock_;
    std::atomic_bool         stop_;
    std::atomic_int          thread_num_;
    std::queue<Task>         tasks_;
    std::vector<std::thread> pool_;
};

#endif  // !__THREAD_POOL_H__

