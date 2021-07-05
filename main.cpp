#include <iostream>
#include <string>
#include <fstream>

struct data {
    std::string firstName = "unknown";
    std::string lastName = "unknown";
    std::string date = "01.01.2000";
    double salary = 0;
};

bool correct_date (data &statement) {
    if (statement.date.length() != 10) return false;
    else {
        int DD[12]={31,28,31,30,31,30,31,31,30,31,30,31};
        int month = std::stoi(statement.date.substr(3,2));
        int day = std::stoi(statement.date.substr(0,2));
        int year = std::stoi(statement.date.substr(6,4));
        if ((month > 12 || month < 1) || (year < 1970 || year > 2038)
            || (day < 1 || day > DD[month - 1])) return false;
        else return true;
    }
}

void add_bill (std::ofstream &file, data &statement) {
    file << statement.firstName << " " << statement.lastName << " " << statement.date << " " << statement.salary << std::endl;
    file.close();
}

void read_bill (std::ifstream &file, data &statement) {
    std::string tempName = "unknown";
    while (!file.eof()) {
        file >> statement.firstName >> statement.lastName >> statement.date >> statement.salary;
        if (tempName == statement.firstName + " " + statement.lastName) break;
        std::cout << statement.firstName << " " << statement.lastName << " " << statement.date << " " << statement.salary << std::endl;
        tempName = statement.firstName + " " + statement.lastName;
    }
}

int main() {

    data statement;
    std::string command;
    std::cout << "Input the command ('add' or 'read'):";
    std::cin >> command;


    if (command == "read") {
        std::ifstream bill ("bill.txt");
        read_bill(bill,statement);
        bill.close();
    } else if (command == "add") {
        std::ofstream bill ("bill.txt",std::ios::app);
        std::cout << "Enter first and last name:";
        std::cin >> statement.firstName >> statement.lastName;
        do {
            std::cout << "Date of issue of money (DD.MM.YYYY):";
            std::cin >> statement.date;
            if (!correct_date(statement)) std::cout << "Incorrect date.";
        } while (!correct_date(statement));
        do {
            std::cout << "Payout amount:";
            std::cin >> statement.salary;
            if (statement.salary < 0) std::cout << "Incorrect amount.";
        } while (statement.salary < 0);
        add_bill(bill, statement);
        bill.close();
    } else std::cout << "Incorrect command" << std::endl;

    return 0;
}