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
    Log(Log && other) : name(other.name) {
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
