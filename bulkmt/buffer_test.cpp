#include <string>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>

template<class T>
class Buffer {
public:
    template<class U>
    void push(U &&elem) {
        std::lock_guard<std::mutex> lk{buffer_lock};
        buffer.push(std::forward<U>(elem));
        push_cond.notify_one();
    }

    std::shared_ptr<T> pop_or_wait() {
        std::unique_lock<std::mutex> lk{buffer_lock};
        push_cond.wait(lk, [this] {return !buffer.empty() or stop_flag.load();});
        if (buffer.empty()) {
            return std::shared_ptr<T>{};
        }
        auto elem = std::make_shared<T>(std::move(buffer.front()));
        buffer.pop();
        return elem;
    }
    void disable_waiting() {
        stop_flag.store(true);
        std::lock_guard<std::mutex> lk{buffer_lock};
        push_cond.notify_all();
    }
private:
    std::queue<T> buffer;
    std::mutex buffer_lock;
    std::condition_variable push_cond;
    std::atomic_bool stop_flag = false;
};

template<class T>
class Logger {
public:
    Logger() {
        worker = std::thread{[this] {process();}};
    }
    auto getStat() {
        return statistics.get_future();
    }
    void notify(const std::string &str) {
        buffer.push(str);
    }
    ~Logger() {
        buffer.disable_waiting();
        // while (!is_finished_flag.load());
            // push_cv.notify_all();
        std::cerr << "wait join\n";
        worker.join();
    }
private:
    void process() {
        int lines_counter = 0;
        std::cerr << "processing\n";
        while (true) {
            auto elem = buffer.pop_or_wait();
            if (!elem)
                break;

            lines_counter++;
            std::cout << *elem << std::endl;
        }

        statistics.set_value(lines_counter);
        std::cerr << "value set\n";
    }
    Buffer<std::string> buffer;
    std::promise<int> statistics;
    std::thread worker;
};

int main(int argc, char *argv[]) {
    std::future<int> stat;
    {
        Logger<std::string> logger;
        stat = logger.getStat();
        std::string str;
        while (std::getline(std::cin, str)) {
            logger.notify(str);
        }
    }

    std::cerr << stat.get() << " lines\n";
    return 0;
}
