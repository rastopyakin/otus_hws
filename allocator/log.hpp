#ifndef LOG_HPP
#define LOG_HPP

class Log {
public:
    Log(std::string s = "def "): name(s) {
        std::cout << name << __PRETTY_FUNCTION__ <<
            " this = " << this << "\n";
    }
    Log(const Log &other) : name(other.name) {
        std::cout << name << __PRETTY_FUNCTION__ <<
            " this = " << this << "\n";
    }
    Log(Log && other) noexcept : name(other.name) {
        other.name = other.name + "moved ";
        std::cout << name << __PRETTY_FUNCTION__ <<
            " this = " << this << "\n";
    }
    ~Log() {
        std::cout << name << __PRETTY_FUNCTION__ <<
            " this = " << this << "\n";
    }
    const Log & operator=(const Log & other) {
        name = other.name;
        std::cout << name << __PRETTY_FUNCTION__ << "\n";
        return *this;
    }
    const Log & operator=(Log && other) {
        name = other.name;
        other.name = name + "_moved ";
        std::cout << name << __PRETTY_FUNCTION__ << "\n";
        return *this;
    }
    void show() const {
        std::cout << name << " this = " << this << "\n";
    }
private:
    std::string name;
};

struct Log_wrapper
{
    Log_wrapper(const std::string& str) : log{str} {
        std::printf("wrapper ctr, this = %p\n", this);
    }
    // Log_wrapper(const Log_wrapper & other) : log{other.log} {
        // std::printf("wrapper copy, this = %p\n", this);
    // }
    // Log_wrapper(Log_wrapper && other) : log{std::move(other.log)} {
        // std::printf("wrapper move, this = %p\n", this);
    // }
    Log_wrapper(const Log_wrapper&) = default;
    Log_wrapper(Log_wrapper&&) = default;
    Log log;
};
#endif /* LOG_HPP */
