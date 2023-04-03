//
//  Expr.hpp
//  MSDScript
//
//  Created by Howard Tung on 1/12/23.
//

/**
 * \file Expr.hpp
 * \brief contains expression class definition
 * \author Howard Tung
 */
#include "pointer.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#pragma once

typedef enum {
  prec_equal,
  prec_none, // = 0
  prec_add,  // = 1
  prec_mult  // = 2
} precedence_t;

class Val;
class Env;
CLASS(Expr) {

public:
  virtual bool equals(PTR(Expr) expr) = 0;

  virtual PTR(Val) interp(PTR(Env) env) = 0;

  //    virtual bool hasVariable() = 0;

//  virtual PTR(Expr) subst(std::string s, PTR(Expr) expr) = 0;

  virtual void print(std::ostream & ostream) = 0;

  std::string to_string();

  std::string pretty_print_to_string();

  virtual void pretty_print(std::ostream & ostream) = 0;

  virtual void pretty_print_at(precedence_t precedence_t,
                               std::ostream & ostream,
                               std::streampos & streamPos, bool addParent) = 0;
};

class NumExpr : public Expr {
public:
  int val;

  explicit NumExpr(int val);

  bool equals(PTR(Expr) expr) override;

  PTR(Val) interp(PTR(Env) env) override;

  //    bool hasVariable();

//  PTR(Expr) subst(std::string s, PTR(Expr) expr) override;

  void print(std::ostream &ostream) override;

  void pretty_print(std::ostream &ostream) override;

  void pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                       std::streampos &streamPos, bool addParent) override;
};

class AddExpr : public Expr {
public:
  PTR(Expr) lhs; //!< lhs of Expression
  PTR(Expr) rhs; //!< rhs of Expression

  AddExpr(PTR(Expr) lhs, PTR(Expr) rhs);

  bool equals(PTR(Expr) expr) override;

  PTR(Val) interp(PTR(Env) env) override;

  //    bool hasVariable();

//  PTR(Expr) subst(std::string s, PTR(Expr) expr) override;

  void print(std::ostream &ostream) override;

  void pretty_print(std::ostream &ostream) override;

  void pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                       std::streampos &streamPos, bool addParent) override;
};

class MultiExpr : public Expr {
public:
  PTR(Expr) lhs; //!< lhs of Expression
  PTR(Expr) rhs; //!< rhs of Expression

  MultiExpr(PTR(Expr) lhs, PTR(Expr) rhs);

  bool equals(PTR(Expr) expr) override;

  PTR(Val) interp(PTR(Env) env) override;

  //    bool hasVariable();

//  PTR(Expr) subst(std::string s, PTR(Expr) expr) override;

  void print(std::ostream &ostream) override;

  void pretty_print(std::ostream &ostream) override;

  void pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                       std::streampos &streamPos, bool addParent) override;
};

class VariableExpr : public Expr {
public:
  std::string string;

  explicit VariableExpr(std::string string);

  bool equals(PTR(Expr) expr) override;

  PTR(Val) interp(PTR(Env) env) override;

  //    bool hasVariable();

//  PTR(Expr) subst(std::string s, PTR(Expr) expr) override;

  void print(std::ostream &ostream) override;

  void pretty_print(std::ostream &ostream) override;

  void pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                       std::streampos &streamPos, bool addParent) override;
};

class LetExpr : public Expr {
public:
  std::string lhs;
  PTR(Expr) rhs;
  PTR(Expr) body;

  LetExpr(std::string lhs, PTR(Expr) rhs, PTR(Expr) body);

  bool equals(PTR(Expr) expr) override;

  PTR(Val) interp(PTR(Env) env) override;

  //    bool hasVariable();

//  PTR(Expr) subst(std::string s, PTR(Expr) expr) override;

  void print(std::ostream &ostream) override;

  void pretty_print(std::ostream &ostream) override;

  void pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                       std::streampos &streamPos, bool addParent) override;
};

class BoolExpr : public Expr {
public:
  bool is_True;

  explicit BoolExpr(bool is_True);

  bool equals(PTR(Expr) expr) override;

  PTR(Val) interp(PTR(Env) env) override;

  //    bool hasVariable();

//  PTR(Expr) subst(std::string s, PTR(Expr) expr) override;

  void print(std::ostream &ostream) override;

  void pretty_print(std::ostream &ostream) override;

  void pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                       std::streampos &streamPos, bool addParent) override;
};

class IfExpr : public Expr {
public:
  PTR(Expr) boolExpr;
  PTR(Expr) firstNumExpr;
  PTR(Expr) secondNumExpr;

  IfExpr(PTR(Expr) boolExpr, PTR(Expr) firstNumExpr, PTR(Expr) secondNumExpr);

  bool equals(PTR(Expr) expr) override;

  PTR(Val) interp(PTR(Env) env) override;

  //    bool hasVariable();

//  PTR(Expr) subst(std::string s, PTR(Expr) expr) override;

  void print(std::ostream &ostream) override;

  void pretty_print(std::ostream &ostream) override;

  void pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                       std::streampos &streamPos, bool addParent) override;
};

class EqExpr : public Expr {
public:
  PTR(Expr) lhs;
  PTR(Expr) rhs;

  EqExpr(PTR(Expr) lhs, PTR(Expr) rhs);

  bool equals(PTR(Expr) expr) override;

  PTR(Val) interp(PTR(Env) env) override;

  //    bool hasVariable();

//  PTR(Expr) subst(std::string s, PTR(Expr) expr) override;

  void print(std::ostream &ostream) override;

  void pretty_print(std::ostream &ostream) override;

  void pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                       std::streampos &streamPos, bool addParent) override;
};

class FunExpr : public Expr {
public:
  std::string formal_arg;
  PTR(Expr) body;
  FunExpr(std::string formal_arg, PTR(Expr) body);

  bool equals(PTR(Expr) expr) override;

  PTR(Val) interp(PTR(Env) env) override;

//  PTR(Expr) subst(std::string s, PTR(Expr) expr) override;

  void print(std::ostream &ostream) override;

  void pretty_print(std::ostream &ostream) override;

  void pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                       std::streampos &streamPos, bool addParent) override;
};

class CallExpr : public Expr {
public:
  PTR(Expr) to_be_called;
  PTR(Expr) actual_arg;
  CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg);

  bool equals(PTR(Expr) expr) override;

  PTR(Val) interp(PTR(Env) env) override;

//  PTR(Expr) subst(std::string s, PTR(Expr) expr) override;

  void print(std::ostream &ostream) override;

  void pretty_print(std::ostream &ostream) override;

  void pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                       std::streampos &streamPos, bool addParent) override;
};

PTR(Expr) parse_Expr(std::istream &instream);

PTR(Expr) parse_Str(std::string string);

PTR(Expr) parse_Num(std::istream &instream);

PTR(Expr) parse_Addend(std::istream &instream);

PTR(Expr) parse_Multicand(std::istream &instream);

PTR(Expr) parse_Var(std::istream &instream);

PTR(Expr) parse_Let(std::istream &instream);

PTR(Expr) parse_If(std::istream &instream);

PTR(Expr) parse_Bool(std::istream &instream);

PTR(Expr) parse_comparg(std::istream &instream);

PTR(Expr) parse_inner(std::istream &instream);

PTR(Expr) parse_Fun(std::istream &instream);

static void consume(std::istream &instream, int expect);

static void skip_whitespace(std::istream &instream);
