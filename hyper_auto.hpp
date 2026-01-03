#pragma once

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
} // inline namespace details


template <std::uintmax_t>
struct hyper_auto;


template <std::uintmax_t ID>
struct unknown {
    static constexpr std::uintmax_t id = ID;

    template <class T>
    static constexpr void infer() {
    #ifdef HPA_DUMPTYPES
        static_assert(false, "\n*/\ntemplate <> struct " + type_name_of<hyper_auto<ID>>() + " { using type = " + type_name_of<T>() + "; };\n/*");
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
    constexpr operator T&() {
        infer<std::decay_t<T>>();
        return std::declval<T&>();
    }

    template <class T>
        requires not_same_as<std::remove_cvref_t<T>, unknown> && std::is_rvalue_reference_v<T&&>
    constexpr operator T&&() {
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


template <std::uintmax_t ID>
struct hyper_auto {
    using type = unknown<ID>;
};

template <std::uintmax_t ID>
using hyper_auto_t = hyper_auto<ID>::type;


template <std::uintmax_t ID>
struct hyper_auto_transitive : hyper_auto<ID> {};
template <std::uintmax_t ID>
    requires is_unknown_v<hyper_auto_t<ID>> && (ID != hyper_auto_t<ID>::id)
struct hyper_auto_transitive<ID> : hyper_auto_transitive<hyper_auto_t<ID>::id> {};

template <std::uintmax_t ID>
using hyper_auto_transitive_t = hyper_auto_transitive<ID>::type;


} // namespace hpa


#if __has_include(HPA_TYPEFILE_STR)
    #define In HPA_IGNORE(
    #include HPA_TYPEFILE_STR
    #undef In
#endif

#ifdef HPA_DUMPTYPES
    static_assert(false, ")/*");
#endif


#define AUTO ::hpa::hyper_auto_transitive_t<__COUNTER__>
