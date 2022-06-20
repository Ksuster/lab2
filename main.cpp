#include <iostream>
#include <Windows.h>
#include <cstdio>

using namespace std;

struct data {
    int min = 0;
    int max = 0;
    int size = 0;
    int average = 0;
    int *arr = NULL;
};

DWORD WINAPI min_max(LPVOID b) {
    data *a = (data *) b;
    int min = a->arr[0];
    int max = a->arr[0];
    int size = a->size;

    for (int i = 1; i < size; i++) {
        if (min > a->arr[i]) {
            min = a->arr[i];
            Sleep(7);
        }
        if (max < a->arr[i]) {
            max = a->arr[i];
            Sleep(7);
        }
    }

    a->max = max;
    a->min = min;

    cout << "Max: " << max << endl << "Min: " << min << endl;

    return 0;
}

DWORD WINAPI average(LPVOID b) {
    data *a = (data *) b;
    int sum = 0;
    int size = a->size;
    for (int i = 0; i < size; i++) {
        sum += a->arr[i];
        Sleep(12);
    }

    a->average = sum / size;

    cout << "Average: " << sum / size << endl;

    return 0;
}

int main() {
    int size;
    cout << "Enter array size:";
    cin >> size;
    int* arr = new int[size];
    cout << "Enter array:";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    struct data* d = new data;
    d->arr = arr;
    d->size = size;

    LPTHREAD_START_ROUTINE mm = (LPTHREAD_START_ROUTINE)min_max;
    HANDLE hThread_mm;
    DWORD IDThread_mm;
    hThread_mm = CreateThread(NULL, 0, mm, (LPVOID)d, 0, &IDThread_mm);
    if (hThread_mm == NULL)
        return GetLastError();


    LPTHREAD_START_ROUTINE av = (LPTHREAD_START_ROUTINE)average;
    HANDLE hThread_av;
    DWORD IDThread_av;
    hThread_av = CreateThread(NULL, 0, av, (LPVOID)d, 0, &IDThread_av);
    if (hThread_av == NULL)
        return GetLastError();

    WaitForSingleObject(hThread_mm, INFINITE);
    WaitForSingleObject(hThread_av, INFINITE);

    CloseHandle(hThread_mm);
    CloseHandle(hThread_av);

    for (int i = 0; i < size; i++) {
        if (arr[i] == d->max) arr[i] = d->average;
        if (arr[i] == d->min) arr[i] = d->average;
    }

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    delete[] arr;
    delete d;

    return 0;
}