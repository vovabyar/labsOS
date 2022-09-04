/*
* Runs two compiled utilities Creator.exe and Reporter.exe
*/

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Employee.h"
#include "VariadicTable.h"


/*
* The Creator utility creates a binary file of the employee structure.
*/
void startСreator(std::string binaryName, int numberEmployees) {
	const char* name = "Creator.exe";
	std::string arg = binaryName + " " + std::to_string(numberEmployees);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	CreateProcess(name, (char*)arg.c_str(), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

/*
* The Reporter utility creates a text file containing an ordered list of employees with accrued wages. 
* The report is based on a binary file, created by the Creator.exe program.
*/
void startReporter(std::string binaryName, std::string reportName, double salaryHour) {
	const char* name = "Reporter.exe";
	std::string arg = binaryName + " " + reportName + " " + std::to_string(salaryHour);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	CreateProcess(name, (char*)arg.c_str(), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

int main() {
	std::string binaryName, reportName;
	int numberEmployees;
	double salaryHour;

	std::cout << "Enter the name of the binary file: ";
	std::cin >> binaryName;
	std::cout << "Enter the number of employees: ";
	std::cin >> numberEmployees;
	std::cout << "\n";

	startСreator(binaryName, numberEmployees);
	std::ifstream in(binaryName, std::ios::binary);

	//VariadicTable used for "pretty-printing" a formatted table of data to the console.
	VariadicTable<int, std::string, int> vt({ "Employee number", "Employee name", "Hours" }, 10);
	struct employee e;
	while (in.read((char*)&e, sizeof(employee))) {
		vt.addRow(e.num, e.name, e.hours);
	}
	vt.print(std::cout);
	std::cout << "\n";
	in.close();

	std::cout << "Enter the name of the report file: ";
	std::cin >> reportName;
	std::cout << "Enter the salary per hour: ";
	std::cin >> salaryHour;
	std::cout << "\n";

	startReporter(binaryName, reportName, salaryHour);
	std::string info;
	std::cout << "File " << reportName << ":\n";
	in.open(reportName);
	std::cout << in.rdbuf();
	in.close();
	system("pause");

	return 0;
}