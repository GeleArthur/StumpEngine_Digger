#pragma once

#define NO_MOVE(class)              \
    class(class && other) = delete; \
    class& operator=(class&& other) = delete;

#define NO_COPY(class)                  \
    class(const class& other) = delete; \
    class& operator=(const class& other) = delete;

// template<int length>
// struct sdbm_hash
// {
//     consteval static unsigned int calculate2(const char* const text, unsigned int& value)
//     {
//         const unsigned int character = sdbm_hash<length - 1>::calculate2(text, value);
//         value = character + (value << 6) + (value << 16) - value;
//         return text[length - 1];
//     }
//     consteval static unsigned int calculate(const char* const text)
//     {
//         unsigned int value = 0;
//         const auto   character = calculate2(text, value);
//         return character + (value << 6) + (value << 16) - value;
//     }
// };
// template<>
// struct sdbm_hash<1>
// {
//     consteval static int calculate2(const char* const text, unsigned int&)
//     {
//         return text[0];
//     }
// };
// template<size_t N>
// consteval unsigned int make_sdbm_hash(const char (&text)[N])
// {
//     return sdbm_hash<N - 1>::calculate(text);
// }