#include <iostream>
#include <vector>
#include <algorithm>

struct team {
    int id;
    int m;
};
int main(int argc, char *argv[]) {
    int N;
    std::cin >> N;
    std::vector<team> teams;
    teams.reserve(N);
    teams.resize(N);

    for (auto &t : teams)
        std::cin >> t.id >> t.m;

    std::stable_sort(teams.begin(), teams.end(),
                     [] (const auto &t1, const auto &t2) -> bool {
                         return t1.m > t2.m;
                     });

    for (const auto &t : teams)
        std::cout << t.id << ' ' << t.m << std::endl;

    return 0;
}
