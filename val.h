//
// Created by Howard Tung on 3/11/23.
//

#pragma once

#include "pointer.h"
#include <string>

class Expr;
CLASS(Val) {
public:
  virtual PTR(Val) add_to(PTR(Val) otherVal) = 0;
  virtual PTR(Val) mult_with(PTR(Val) otherVal) = 0;
  virtual PTR(Expr) to_expr() = 0;
  virtual bool equals(PTR(Val) otherVal) = 0;
  std::string to_string();
  virtual void print(std::ostream & ostream) = 0;
  virtual bool is_true() = 0;
  virtual PTR(Val) call(PTR(Val) actual_arg) = 0;
};

class NumVal : public Val {
public:
  int val;
  explicit NumVal(int val);
  PTR(Val) mult_with(PTR(Val) otherVal) override;
  PTR(Val) add_to(PTR(Val) otherVal) override;
  PTR(Expr) to_expr() override;
  bool equals(PTR(Val) otherVal) override;
  void print(std::ostream &ostream) override;
  bool is_true() override;
  PTR(Val) call(PTR(Val) actual_arg) override;
};

class BoolVal : public Val {
public:
  bool is_True;
  explicit BoolVal(bool is_True);

  PTR(Val) add_to(PTR(Val) otherVal) override;
  PTR(Val) mult_with(PTR(Val) otherVal) override;
  PTR(Expr) to_expr() override;
  bool equals(PTR(Val) otherVal) override;
  void print(std::ostream &ostream) override;
  bool is_true() override;
  PTR(Val) call(PTR(Val) actual_arg) override;
};

class FunVal : public Val {
public:
  std::string formal_arg;
  PTR(Expr) body;
  explicit FunVal(std::string formal_arg, PTR(Expr) body);

  PTR(Val) mult_with(PTR(Val) otherVal) override;
  PTR(Val) add_to(PTR(Val) otherVal) override;
  PTR(Expr) to_expr() override;
  bool equals(PTR(Val) otherVal) override;
  void print(std::ostream &ostream) override;
  bool is_true() override;
  PTR(Val) call(PTR(Val) actual_arg) override;
};
