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

    // 異なる型で複数回推論される場合の例
    {
        AUTO z;
        z = 0;  // ここで z の型が int と推論される
        z = 2.718;  // ここで z の型が double と推論される
        // 最終的に z の型は int と double の共通型である double になる
        static_assert(std::is_same_v<decltype(z), double>);

        AUTO s;
        s = "Hello!";  // ここで s の型が const char* と推論される
        [](std::string&){}(s);  // ここで s の型が std::string と推論される
        // 最終的に s の型は const char* と std::string の共通型である std::string になる
        static_assert(std::is_same_v<decltype(s), std::string>);
    }
}
