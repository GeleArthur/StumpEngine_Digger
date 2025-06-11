#pragma once

template<typename T>
class Singleton
{
public:
    static T& instance()
    {
        static T instance;
        return instance;
    };

    Singleton(const Singleton& other) = delete;
    Singleton(Singleton&& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;
    Singleton& operator=(Singleton&& other) = delete;

protected:
    ~Singleton() = default;
    Singleton() = default;
};
