#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char *argv[])
{
    int teacher_n = 0, student_n = 0;
    std::cin >> teacher_n;
    std::vector<int> teacher_list;
    teacher_list.reserve(teacher_n);
    teacher_list.resize(teacher_n);

    for (auto & date : teacher_list)
	std::cin >> date;

    // teacher_list.erase(
    // 	std::unique(teacher_list.begin(), teacher_list.end()),
    // 	teacher_list.end());

    int matched_dates_number = 0;
    int date;
    std::cin >> student_n;
    auto beg = teacher_list.begin();
    auto end = teacher_list.end();
    for (int i = 0; i < student_n; ++i) {
	std::cin >> date;
	matched_dates_number +=
	    std::binary_search(beg, end, date);

    }

    std::printf("%d\n", matched_dates_number);
    return 0;
}
