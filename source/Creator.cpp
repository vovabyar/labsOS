/*
* Creator utility.
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Employee.h"

int main(int argc, char* argv[]) {
	std::fstream out(argv[0], std::ios::out | std::ios::binary);
	int numberEmployees = atoi(argv[1]);

	struct employee emp;
	for (int i = 0; i < numberEmployees; ++i) {
		std::cout << "Enter employee number: ";
		std::cin >> emp.num;
		if (emp.num < 0) throw std::invalid_argument("negative value!");

		std::cout << "Enter employee name (less than 10): ";
		std::cin.ignore();
		std::cin.getline(emp.name, 10);
		if (emp.name == 0) throw std::invalid_argument("Name must contains letters!");

		std::cout << "Enter working hours: ";
		std::cin >> emp.hours;
		if (emp.hours < 0) throw std::invalid_argument("negative value!");
		out.write((char*)&emp, sizeof(employee));
	}
	out.close();

	return 0;
}
