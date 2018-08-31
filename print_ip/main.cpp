#include <iostream>
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>
#include <utility>
#include <list>
#include <tuple>

using byte_t = uint8_t;

class dot_placer {
public:
    template<class T>
    auto operator()(T&& pass_me) {
        if (!is_first)
            std::cout << '.';
        else
            is_first = false;
        return std::forward<T>(pass_me);
    }

private:
    bool is_first = true;
};

template <class T>
std::enable_if_t<std::is_integral<T>::value>
print_ip(T val) {
    constexpr std::size_t n_bytes = sizeof(val);
    dot_placer dp;
    const byte_t * p_val = reinterpret_cast<byte_t*>(&val);
    for (std::size_t i = 0; i < n_bytes; i++) {
        std::cout << dp(static_cast<uint16_t>(p_val[i]));
    }
    std::cout << std::endl;
}

template<class, class = void>
struct is_iterable {
    static const bool value = false;
};

template<class T>
struct is_iterable<T, decltype(std::declval<T>().begin(), std::declval<T>().end(), void())> {
    static const bool value = true;
};

template <class T>
constexpr bool is_iterable_v = is_iterable<T>::value;

template<class T>
std::enable_if_t<is_iterable_v<T>> print_ip(T container) {
    dot_placer dp;
    for (auto i : container)
        std::cout << dp(i);
    std::cout << std::endl;
}

void print_ip(std::string val) {
    std::cout << val << std::endl;
}

template <std::size_t ind, class ... Ts>
struct print_tuple {
    static void as_ip(const std::tuple<Ts...> &t) {
        print_tuple<ind-1, Ts...>::as_ip(t);
        std::cout << '.' << std::get<ind>(t);
    }
};

template<class ... Ts>
struct print_tuple<0, Ts...> {
    static void as_ip(const std::tuple<Ts...> &t) {
        std::cout << std::get<0>(t);
    }
};

template<class ... Ts>
void print_ip(const std::tuple<Ts...> &t) { // forwarding ref??
    static_assert(sizeof...(Ts), "empty tuple");
    print_tuple<sizeof...(Ts)-1, Ts...>::as_ip(t);
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));
    print_ip("127.0.0.1");

    std::vector<int> v {87, 250, 250, 242};
    std::list<int> l {64, 233, 164, 139};
    print_ip(v);
    print_ip(l);
    auto t = std::make_tuple(80, 87, 192, 10);
    print_ip(t);
}
