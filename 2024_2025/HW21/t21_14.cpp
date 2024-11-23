#include <iostream>
#include <algorithm>
#include <tuple>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

std::map<int, int> valid_date_dict = {
        {1, 31}, {2, 29}, {3, 31}, {4, 30},
        {5, 31}, {6, 30}, {7, 31}, {8, 31},
        {9, 30}, {10, 31}, {11, 30}, {12, 31}
};


int month_to_number(const std::string& month) {
    static std::map<std::string, int> month_map = {
            {"January", 1}, {"February", 2}, {"March", 3}, {"April", 4},
            {"May", 5}, {"June", 6}, {"July", 7}, {"August", 8},
            {"September", 9}, {"October", 10}, {"November", 11}, {"December", 12}, {"1", 1},
            {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7},
            {"8", 8}, {"9", 9}, {"10", 10}, {"11", 11}, {"12", 12}
    };
    return month_map[month];
}


bool is_leap(int year) {
    return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}


bool is_date_valid(const std::tuple<int, std::string, int>& date){

    int day = std::get<0>(date);
    int month = month_to_number(std::get<1>(date));
    int year = std::get<2>(date);

    if (month < 1 || month > 12)
        return false;
    else if (day == 29 && month == 2 && !is_leap(year))
        return false;
    else
        return day <= valid_date_dict[month];
}


auto read_dates(const std::string& filename){
    std::vector<std::tuple<int, std::string, int>> datebook;
    std::ifstream f_in(filename);
    if (!f_in){
        throw std::runtime_error("Could not open the file.");
    }
    std::string line;
    while(std::getline(f_in, line)){
        std::stringstream ss(line);
        std::string date;
        while (std::getline(ss, date, ',')){
            std::stringstream ds(date);
            int day;
            std::string month;
            int year;
            ds >> day >> month >> year;
            auto date_ = std::make_tuple(day, month, year);
            if (is_date_valid(date_))
                datebook.emplace_back(date_);
            else {
                std::cout << "Impossible date ignored.\n";
                continue;
            }
        }
    }
    return datebook;
}


bool sort_datebook(const std::tuple<int, std::string, int>& date1,
                   const std::tuple<int, std::string, int>& date2){
    int year1 = std::get<2>(date1);
    int year2 = std::get<2>(date2);

    int month1 = month_to_number(std::get<1>(date1));
    int month2 = month_to_number(std::get<1>(date2));

    int day1 = std::get<0>(date1);
    int day2 = std::get<0>(date2);

    if (year1 != year2)
        return year1 < year2;
    if (month1 != month2)
        return month1 < month2;
    return day1 < day2;
}

void print_dates(const std::vector<std::tuple<int, std::string, int>>& datebook){
    for (auto date: datebook){
        int year = std::get<2>(date);
        std::string month = std::get<1>(date);
        int day = std::get<0>(date);
        std::cout << year << '/' << month << '/' << day << ", ";
    }
    std::cout << "\b\b";
}


int main(){
    auto databook = read_dates("input2114.txt");

    std::sort(databook.begin(), databook.end(), sort_datebook);

    print_dates(databook);
}