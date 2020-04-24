#include <iostream>
#include <string>

int sum_of_digits(std::string number) {
    int sum = 0;
    for (char digit : number)
	sum += digit - '0';
    return sum;
}

bool is_lucky(std::string number) {
    auto head = number.substr(0, 3);
    auto tail = number.substr(3, 3);
    return sum_of_digits(head) == sum_of_digits(tail);
}

std::string add_heading_zeros(std::string number) {
    int n_zeros = 6 - number.length();
    std::string zeros(n_zeros, '0');
    return zeros + number;
}

int main(int argc, char *argv[])
{
    int number = 0;
    std::cin >> number;

    auto next = std::to_string(number + 1);
    auto prev = std::to_string(number - 1);

    if (is_lucky(add_heading_zeros(next)) or is_lucky(add_heading_zeros(prev)))
	std::cout << "Yes\n";
    else
	std::cout << "No\n";
    return 0;
}
