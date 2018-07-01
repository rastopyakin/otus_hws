#include <iostream>
#include <map>
#include <set>

using name_t = std::string;

struct player_t {
    player_t(const name_t & name_ = "") : name(name_) {}
    name_t name;
    mutable bool is_defined = false;
    mutable int rank = 0;
    bool operator<(const player_t & other) const {
	return this->name < other.name;
    }
};

using relation_t = std::map<player_t, std::set<player_t>>;

std::ostream & operator<<(std::ostream & os, const player_t & p) {
    os << p.name;
    return os;
}
std::istream & operator>>(std::istream & is, player_t & p) {
    is >> p.name;
    return is;
}

void define_ranks(relation_t & relations, const player_t & p, int rank = 0) {
    auto pp = relations.find(p);
    if (pp != relations.end())
	if ( !pp->first.is_defined || pp->first.rank > rank) {
	    pp->first.is_defined = true;
	    pp->first.rank = rank;
	    for (const auto & mate : pp->second) {
		define_ranks(relations, mate, rank + 1);
	    }
	}
}

int main(int argc, char *argv[])
{
    int teams_num = 0;
    std::cin >> teams_num;
    player_t n1, n2, n3;
    relation_t relations;

    for (int i = 0; i < teams_num; ++i) {
	std::cin >> n1 >> n2 >> n3;
	relations[n1].insert(n2);
	relations[n1].insert(n3);
	relations[n2].insert(n1);
	relations[n2].insert(n3);
	relations[n3].insert(n1);
	relations[n3].insert(n2);
    }
    auto p = player_t{"Isenbaev"};
    define_ranks(relations, p);

    for (const auto & p : relations) {
	std::cout << p.first << " ";
	if (p.first.is_defined)
	    std::cout << p.first.rank;
	else
	    std::cout << "undefined";
	std::cout << std::endl;
    }
    return 0;
}
