#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    int n_candidates, n_voters;
    std::cin >> n_candidates >> n_voters;
    std::vector<int> votes;
    votes.reserve(n_voters); votes.resize(n_voters);

    for (int &vote : votes)
        std::cin >> vote;

    std::vector<double> rates;
    rates.reserve(n_candidates); rates.resize(n_candidates, 0.0);

    for (int vote : votes)
        rates[vote - 1]++;

    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    for (double rate : rates)
        std::cout  << 100*rate/n_voters << '%' << std::endl;

    return 0;
}
