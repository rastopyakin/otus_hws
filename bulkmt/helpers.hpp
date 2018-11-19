#ifndef HELPERS_HPP
#define HELPERS_HPP

class CommaPlacer {
public:
    friend auto& operator<<(std::ostream &os, CommaPlacer &cp) {
        if (!cp.is_first)
            os << ", ";
        else
            cp.is_first = false;
        return os;
    }
private:
    bool is_first = true;
};

// statistics bundle
struct Stat {
    std::size_t blocks_num = 0;
    std::size_t cmd_num = 0;
};

#endif /* HELPERS_HPP */
