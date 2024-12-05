#include <iostream>
#include <mutex>

class Data {
public:
    int value = 0;
    std::mutex mtx;
};


void lock(Data& x, Data& y) {

    std::lock(x.mtx, y.mtx);

    std::swap(x.value, y.value);
}


void scoped_lock(Data& x, Data& y) {

    std::scoped_lock<std::mutex, std::mutex> lock(x.mtx, y.mtx);

    std::swap(x.value, y.value);
}


void unique_lock(Data& x, Data& y) {

    std::unique_lock<std::mutex> lock_a(x.mtx, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(y.mtx, std::defer_lock);
    std::lock(lock_a, lock_b);

    std::swap(x.value, y.value);
}

int main() {
    setlocale(LC_ALL, "Russian");

    Data a{ 10 }, b{ 20 }, c{ 100 }, d{ 200 }, e{ 30 }, f{ 300 };


    std::cout << "До обмена:\n";
    std::cout << "a.value: " << a.value << "\n";
    std::cout << "b.value: " << b.value << "\n";
    std::cout << "c.value: " << c.value << "\n";
    std::cout << "d.value: " << d.value << "\n";
    std::cout << "e.value: " << e.value << "\n";
    std::cout << "f.value: " << f.value << "\n\n";


    lock(a, b);
    scoped_lock(c, d);
    unique_lock(e, f);

    std::cout << "После обмена:\n";
    std::cout << "a.value: " << a.value << "\n";
    std::cout << "b.value: " << b.value << "\n";
    std::cout << "c.value: " << c.value << "\n";
    std::cout << "d.value: " << d.value << "\n";
    std::cout << "e.value: " << e.value << "\n";
    std::cout << "f.value: " << f.value << "\n";

    return 0;
}
