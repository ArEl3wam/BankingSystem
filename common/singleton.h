#pragma once

template <class T> class Singleton
{

protected:
  Singleton() = default;
  virtual ~Singleton() = default;

public:
  T instance;
  static T &getInstance()
  {
    static T instance;
    return instance;
  }
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;
};