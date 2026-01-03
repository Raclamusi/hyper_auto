#include <print>
#include <type_traits>
#include <vector>
#include "hyper_auto.hpp"

int f(AUTO x) {
    return x;  // int の戻り値型で a を返すので a の型は int
}

int main() {
    AUTO x;
    x = 42;  // ここで x の型がが int とわかる
    std::println("{}", x);

    std::vector<AUTO> vec;
    vec.push_back(3.14);  // ここで vec の型が std::vector<double> とわかる
    std::println("{}", vec);

    AUTO y;
    [](double&){}(y);  // double 型の引数として y を渡しているので y の型は double
    static_assert(std::is_same_v<decltype(y), double>);

    static_assert(std::is_same_v<decltype(&f), int (*)(int)>);
}
