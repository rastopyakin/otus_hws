#include <string>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>

template<class T>
class Logger {
public:
    Logger() {
        worker = std::thread{[this] {process();}};
    }
    template<class U>
    void push(U &&elem) {
        std::lock_guard<std::mutex> lk{buffer_mutex};
        buffer.push(std::forward<U>(elem));
        push_cv.notify_one();
    }
    auto getStat() {
        return statistics.get_future();
    }
    ~Logger() {
        stop_flag.store(true);
        while (!is_finished_flag.load())
            push_cv.notify_all();

        std::cerr << "wait join\n";
        worker.join();
    }
private:
    void process() {
        int lines_counter = 0;
        std::cerr << "processing\n";
        while (true) {
            std::unique_lock<std::mutex> lk{buffer_mutex};
            push_cv.wait(lk, [this] {return !buffer.empty() or stop_flag.load();});
            if (buffer.empty()) {
                is_finished_flag.store(true);
                break;
            }
            auto elem = buffer.front();
            buffer.pop();
            lk.unlock();

            lines_counter++;
            std::cout << elem << std::endl;
        }

        statistics.set_value(lines_counter);
        std::cerr << "value set\n";
        // while (!buffer.empty()) {
        //     std::cout << "rest\n";
        //     std::cout << buffer.front() << std::endl;
        //     buffer.pop();
        // }
    }
    std::promise<int> statistics;
    std::queue<T> buffer;
    std::mutex buffer_mutex;
    std::thread worker;
    std::condition_variable push_cv;
    std::atomic_bool stop_flag = false;
    std::atomic_bool is_finished_flag = false;
};

int main(int argc, char *argv[]) {
    std::future<int> stat;
    {
        Logger<std::string> logger;
        stat = logger.getStat();
        std::string str;
        while (std::getline(std::cin, str)) {
            logger.push(str);
        }
    }

    std::cerr << "input taken\n";
    std::cerr << stat.get() << " lines\n";
    return 0;
}
