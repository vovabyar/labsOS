#include <Windows.h>
#include <iostream>
#include <vector>

struct parameters {
    parameters(std::vector<int>& arr) : arr(arr) {};
    std::vector<int> arr;
    int min = 0;
    int max = 0;
    int average = 0;
};

DWORD WINAPI findMinAndMax(LPVOID arg) {
    parameters* pArr = static_cast<parameters*>(arg);
    pArr->max = pArr->min = pArr->arr[0];
    for (int i = 1; i < pArr->arr.size(); i++) {
        if (pArr->max < pArr->arr[i]) {
            pArr->max = pArr->arr[i];
        }
        Sleep(7);
        if (pArr->min > pArr->arr[i]) {
            pArr->min = pArr->arr[i];
        }
        Sleep(7);
    }
    std::cout << "Max element: " << pArr->max << "\n";
    std::cout << "Min element: " << pArr->min << "\n";
    return 0;
}

DWORD WINAPI average(LPVOID arg) {
    parameters* pArr = (parameters*)arg;
    for (int i = 0; i < pArr->arr.size(); ++i) {
        pArr->average += pArr->arr[i];
        Sleep(12);
    }
    pArr->average = pArr->average / pArr->arr.size();
    std::cout << "Average: " << pArr->average << "\n";
    return 0;
}

void print(parameters* pArr) {
    std::cout << "\nResult: ";
    for (int i = 0; i < pArr->arr.size(); ++i) {
        std::cout << pArr->arr[i] << " ";
    }
}

int main() {
    int size;
    std::cout << "Enter array size:";
    std::cin >> size;
    std::vector<int> arr;
    std::cout << "Enter elements:";
    int number = 0;
    for (int i = 0; i < size; i++) {
        std::cin >> number;
        arr.push_back(number);
    }

    parameters* structParameters = new parameters(arr);
    HANDLE hThreadFindMinAndMax, hThreadAverage;

    hThreadFindMinAndMax = CreateThread(NULL, 0, &findMinAndMax, LPVOID(structParameters), NULL, NULL);
    hThreadAverage = CreateThread(NULL, 0, &average, LPVOID(structParameters), NULL, NULL);
    if (hThreadFindMinAndMax == NULL || hThreadAverage == NULL) {
        return GetLastError();
    }

    WaitForSingleObject(hThreadFindMinAndMax, INFINITE);
    CloseHandle(hThreadFindMinAndMax);
    WaitForSingleObject(hThreadAverage, INFINITE);
    CloseHandle(hThreadAverage);

    for (int i = 0; i < structParameters->arr.size(); i++) {
        if (structParameters->arr[i] == structParameters->max ||
            structParameters->arr[i] == structParameters->min) {
            structParameters->arr[i] = structParameters->average;
        }
    }

    print(structParameters);
    delete structParameters;

    return 0;
}
