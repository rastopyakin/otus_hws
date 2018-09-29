#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

int main(int argc, char *argv[]) {
    int N;
    std::cin >> N;
    std::cin.ignore();

    std::unordered_map<std::string, std::size_t> scores;
    std::string note;
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, note);
        scores[note]++;
    }

    auto most_popular = std::max_element(scores.begin(), scores.end(),
                                         [] (const auto& p1, const auto &p2){return p1.second < p2.second;});

    std::cout << most_popular->first << std::endl;
    return 0;
}
