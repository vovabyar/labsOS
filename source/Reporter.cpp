/*
* Reporter utility.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Employee.h"
#include "VariadicTable.h"

int main(int argc, char* argv[]) {
	std::ifstream in(argv[0], std::ios::binary);
	std::ofstream out(argv[1]);
	double salaryHour = atof(argv[2]);
	struct employee emp;

	VariadicTable<int, std::string, int, double> vt({ "Employee number", "Employee name", "Hours",  "Employee salary" }, 10);
	while (in.read((char*)&emp, sizeof(employee))) {
		vt.addRow(emp.num, emp.name, emp.hours, emp.hours * salaryHour);
	}
	in.close();
	vt.print(out);
	out.close();

	return 0;
}