#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
public:
    static T & getInstance()
    {
        static T instance;
        return instance;
    }

private:
    void operator=(Singleton const &) {}
};

#endif
