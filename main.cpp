#include <print>
#include <string>
#include <type_traits>
#include <vector>
#include "hyper_auto.hpp"

int f(AUTO x) {
    return x;  // int の戻り値型で a を返すので a の型は int
}

AUTO g(AUTO x, AUTO y) {
    const auto id_str = [](const std::string& x) -> const std::string& { return x; };
    return id_str(x) + id_str(y);  // 使われ方(id_str に渡していること)から x と y は std::string になる
                                   // std::string 同士の加算なので戻り値も std::string
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

    std::println("{}", g("4", "2"));  // const char* は std::string に暗黙変換可能なので渡せる
    // std::println("{}", g(4, 2));   // int は std::string に変換不可能なので呼び出せない
}
