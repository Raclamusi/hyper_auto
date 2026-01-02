#pragma once

#include <charconv>
#include <concepts>
#include <string>
#include <string_view>
#include <source_location>
#include <type_traits>
#include <cstdint>


#define HPA_STR_IMPL(...) #__VA_ARGS__
#define HPA_STR(...) HPA_STR_IMPL(__VA_ARGS__)
#define HPA_IGNORE(...)

#ifndef HPA_TYPEFILE
    #define HPA_TYPEFILE typefile.inc
#endif
#define HPA_TYPEFILE_STR HPA_STR(HPA_TYPEFILE)


namespace hpa {

inline namespace details {
    template <class T>
    constexpr std::string type_name_of() {
        using namespace std::string_view_literals;
        std::string_view s = std::source_location::current().function_name();
    #if defined(__clang__)
        s.remove_prefix("std::string hpa::type_name_of() [T = "sv.size());
        s.remove_suffix("]"sv.size());
    #elif defined(__GNUC__)
        s.remove_prefix("constexpr std::string hpa::details::type_name_of() [with T = "sv.size());
        s.remove_suffix("; std::string = std::__cxx11::basic_string<char>]"sv.size());
    #else
        #error This platform is not supported.
    #endif
        return std::string{ s };
    }

    template <class T, class U>
    concept not_same_as_impl = not std::is_same_v<T, U>;
    template <class T, class U>
    concept not_same_as = not_same_as_impl<T, U> && not_same_as_impl<U, T>;

    struct any {
        template <typename T>
        operator T();
    };

    inline constexpr std::uintmax_t max_depth = 128;

    template<std::integral T>
    consteval std::string to_string(T x) {
        char t[64] = {};
        std::to_chars(t, t + sizeof(x), x);
        return t;
    }
} // inline namespace details

template <std::uintmax_t, std::uintmax_t>
struct hyper_auto;

#define SPECIALIZED_HYPER_AUTO(ID) \
    (std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 0>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 1>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 2>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 3>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 4>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 5>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 6>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 7>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 8>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 9>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 10>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 11>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 12>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 13>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 14>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 15>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 16>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 17>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 18>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 19>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 20>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 21>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 22>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 23>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 24>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 25>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 26>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 27>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 28>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 29>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 30>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 31>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 32>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 33>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 34>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 35>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 36>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 37>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 38>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 39>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 40>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 41>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 42>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 43>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 44>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 45>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 46>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 47>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 48>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 49>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 50>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 51>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 52>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 53>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 54>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 55>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 56>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 57>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 58>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 59>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 60>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 61>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 62>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 63>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 64>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 65>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 66>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 67>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 68>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 69>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 70>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 71>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 72>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 73>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 74>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 75>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 76>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 77>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 78>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 79>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 80>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 81>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 82>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 83>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 84>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 85>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 86>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 87>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 88>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 89>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 90>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 91>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 92>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 93>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 94>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 95>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 96>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 97>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 98>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 99>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 100>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 101>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 102>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 103>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 104>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 105>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 106>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 107>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 108>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 109>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 110>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 111>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 112>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 113>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 114>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 115>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 116>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 117>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 118>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 119>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 120>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 121>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 122>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 123>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 124>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 125>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 126>>{}) + \
     std::__is_complete_or_unbounded(std::__type_identity<::hpa::hyper_auto<ID, 127>>{}))

template <std::uintmax_t ID>
struct unknown {
    static constexpr std::uintmax_t id = ID;

    template <class T>
    static constexpr void infer() {
    #ifdef HPA_DUMPTYPES
        static_assert(false, []{
            const auto id = ::hpa::details::to_string(ID);
            return "\n*/\ntemplate <> struct hpa::hyper_auto<" + id + ", SPECIALIZED_HYPER_AUTO(" + id + ")> { using type = std::common_type_t<" + type_name_of<T>() + ", typename ::hpa::hyper_auto<" + id + ", SPECIALIZED_HYPER_AUTO(" + id + ") - 1>::type>; };\n/*";
        }());
    #else
        static_assert(false, "Type inference not yet completed. Define HPA_DUMPTYPES and compile to append to " HPA_TYPEFILE_STR ".");
    #endif
    }

    constexpr unknown() = default;

    template <class T>
        requires not_same_as<std::remove_cvref_t<T>, unknown>
    constexpr unknown(T&&) {
        infer<std::decay_t<T>>();
    }

    template <class T>
        requires not_same_as<std::remove_cvref_t<T>, unknown>
    constexpr unknown& operator=(T&&) {
        infer<std::decay_t<T>>();
        return *this;
    }

    template <class T>
        requires not_same_as<std::remove_cvref_t<T>, unknown>
    constexpr operator T() {
        infer<std::decay_t<T>>();
        return std::declval<T>();
    }
};

template <class T>
struct is_unknown : std::false_type {};
template <std::uintmax_t ID>
struct is_unknown<unknown<ID>> : std::true_type {};

template <class T>
inline constexpr bool is_unknown_v = is_unknown<T>::value;

#ifdef HPA_DUMPTYPES
template <std::uintmax_t ID, std::uintmax_t>
struct hyper_auto {
    using type = unknown<ID>;
};
#else
template <std::uintmax_t ID>
struct hyper_auto<ID, 0> {
    using type = details::any;
};
#endif

template <std::uintmax_t ID, std::uintmax_t Depth>
using hyper_auto_t = hyper_auto<ID, Depth>::type;


template <std::uintmax_t ID>
struct hyper_auto_transitive : hyper_auto<ID, SPECIALIZED_HYPER_AUTO(ID) - 1> {};
template <std::uintmax_t ID>
    requires is_unknown_v<hyper_auto_t<ID, SPECIALIZED_HYPER_AUTO(ID) - 1>> && (ID != hyper_auto_t<ID, SPECIALIZED_HYPER_AUTO(ID) - 1>::id)
struct hyper_auto_transitive<ID> : hyper_auto_transitive<hyper_auto_t<ID, SPECIALIZED_HYPER_AUTO(ID) - 1>::id> {};

template <std::uintmax_t ID>
using hyper_auto_transitive_t = hyper_auto_transitive<ID>::type;


} // namespace hpa


#if __has_include(HPA_TYPEFILE_STR)
    #define In HPA_IGNORE(
    #include HPA_TYPEFILE_STR
    #undef In
#endif

#ifdef HPA_DUMPTYPES
    static_assert(false, ")\n#pragma GCC diagnostic push\n#pragma GCC diagnostic ignored \"-Wpragmas\"\n#pragma GCC diagnostic ignored \"-Wsfinae-incomplete\"\n/*");
#endif


#define AUTO ::hpa::hyper_auto_transitive_t<__COUNTER__>
