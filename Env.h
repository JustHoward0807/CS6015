//
// Created by Howard Tung on 4/3/23.
//

#include "pointer.h"

#include "string"

class Val;
CLASS(Env) {
public:
  virtual PTR(Val) lookup(std::string find_name) = 0;
  static PTR(Env) empty;
};

class EmptyEnv : public Env {
public:
  PTR(Val) lookup(std::string find_name) override {
    throw std::runtime_error("free variable: " + find_name);
  }
};

class ExtendedEnv : public Env {
public:
  std::string name;
  PTR(Val) val;
  PTR(Env) rest;

  ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest);
  PTR(Val) lookup(std::string find_name) override {
    if (find_name == name) {
      return val;
    } else {
      return rest->lookup(find_name);
    }
  }
};
