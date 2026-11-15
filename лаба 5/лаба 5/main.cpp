// Програмний проєкт 5, варіант 9
// Обчислення: A, B, C1, C2, D1, D2, F
// Повільні: A, B. Залежності: B(A), C1(B), D1(C1, C2), F(D1, D2)

#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <syncstream>
#include <thread>

using namespace std;
using namespace chrono;

void calc(const string& name, int sec) {
    this_thread::sleep_for(chrono::seconds(sec));
    osyncstream(cout) << name << endl;
}

void slow(const string& name) { calc(name, 7); }
void quick(const string& name) { calc(name, 1); }

void work() {
    auto start = steady_clock::now();

    auto fCD = async(launch::async, [] {
        quick("C2");
        quick("D2");
        });

    slow("A");
    slow("B");
    quick("C1");
    fCD.get();       
    quick("D1");
    quick("F");

    double t = duration<double>(steady_clock::now() - start).count();
    osyncstream(cout) << "Time: " << t << " s" << endl;
    osyncstream(cout) << "Work is done!" << endl;
}

int main() {
    work();
    return 0;
}