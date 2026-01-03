# Hyper Auto

> [!NOTE]
> こちらのブランチは、異なる型で複数回推論される場合に対応したバージョンです。
> Qiita の記事で説明されているものと異なる方針で実装されています。
> ```cpp
> #include <string>
> #include <type_traits>
> #include "hyper_auto.hpp"
> 
> int main() {
>     AUTO z;
>     z = 0;  // ここで z の型が int と推論される
>     z = 2.718;  // ここで z の型が double と推論される
>     // 最終的に z の型は int と double の共通型である double になる
>     static_assert(std::is_same_v<decltype(z), double>);
> 
>     AUTO s;
>     s = "Hello!";  // ここで s の型が const char* と推論される
>     [](std::string&){}(s);  // ここで s の型が std::string と推論される
>     // 最終的に s の型は const char* と std::string の共通型である std::string になる
>     static_assert(std::is_same_v<decltype(s), std::string>);
> }
> ```

C++26で、先を見通す**強力な型推論**！

```cpp
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
```

## コンパイルは2回！

```bash
g++ -std=c++26 main.cpp -DHPA_DUMPTYPES -fno-diagnostics-show-caret hpa_end.cpp 2> typefile.inc
g++ -std=c++26 main.cpp
```

```bash
clang++ -std=c++26 main.cpp -DHPA_DUMPTYPES -fno-caret-diagnostics hpa_end.cpp 2> typefile.inc
clang++ -std=c++26 main.cpp
```

コンパイルを2回行うことで高度な型推論を実現します。

1回目は、以下の表に示すコマンドライン引数を指定した上で、標準エラー出力を typefile.inc にリダイレクトして型情報を保存します。
2回目は、必要な型情報がすべて揃っていると、通常通りコンパイルできます。
ファイル名を typefile.inc 以外にする場合は、2回目も `-DHPA_TYPEFILE=tmy_typefile.inc` のように指定してください。

|コマンドライン引数|説明|
|:--|:--|
|`-DHPA_DUMPTYPES`|型情報を出力します。|
|`-fno-diagnostics-show-caret` (gcc)<br>`-fno-caret-diagnostics` (clang)|キャレット（コードの断片）を非表示にします。|
|`hpa_end.cpp`|型情報の出力を終了します。|
|`-DHPA_TYPEFILE=my_typefile.inc`|（任意）型情報として読み込むファイルを指定します。デフォルトは typefile.inc です。デフォルト以外のファイル名を使用する場合、コンパイル2回目にも指定する必要があります。|

## 解説記事

https://qiita.com/Raclamusi/items/6a0fe8134e2bba6dbf59
