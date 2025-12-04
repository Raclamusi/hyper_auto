#include <print>
#include <vector>
#include "hyper_auto.hpp"

int main() {
    AUTO x;
    x = 42;  // ここで x の型がが int とわかる
    std::println("{}", x);

    std::vector<AUTO> vec;
    vec.push_back(3.14);  // ここで vec の型が std::vector<double> とわかる
    std::println("{}", vec);
}
