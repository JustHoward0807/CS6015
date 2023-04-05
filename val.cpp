//
// Created by Howard Tung on 3/11/23.
//

#include "val.h"
#include "Env.h"
#include "Expr.hpp"
#include "sstream"

// 888b    888                        888     888          888
// 8888b   888                        888     888          888
// 88888b  888                        888     888          888
// 888Y88b 888 888  888 88888b.d88b.  Y88b   d88P  8888b.  888
// 888 Y88b888 888  888 888 "888 "88b  Y88b d88P      "88b 888
// 888  Y88888 888  888 888  888  888   Y88o88P   .d888888 888
// 888   Y8888 Y88b 888 888  888  888    Y888P    888  888 888
// 888    Y888  "Y88888 888  888  888     Y8P     "Y888888 888

PTR(Val) NumVal::mult_with(PTR(Val) otherVal) {
  PTR(NumVal) other_num = CAST(NumVal)(otherVal);
  if (other_num == NULL)
    throw std::runtime_error("MultExpr of non-number");
  return NEW(NumVal)((unsigned)this->val * (unsigned)other_num->val);
}

PTR(Val) NumVal::add_to(PTR(Val) otherVal) {
  PTR(NumVal) other_num = CAST(NumVal)(otherVal);
  if (other_num == NULL)
    throw std::runtime_error("AddExpr of non-number");
  return NEW(NumVal)((unsigned)this->val + (unsigned)other_num->val);
}

// PTR(Expr) NumVal::to_expr() { return NEW(NumExpr)(this->val); }

bool NumVal::equals(PTR(Val) otherVal) {
  PTR(NumVal) otherNum = CAST(NumVal)(otherVal);
  if (otherNum == NULL) {
    return false;
  } else {
    return this->val == otherNum->val;
  }
}

std::string Val::to_string() {
  std::stringstream st("");
  this->print(st);
  return st.str();
}

void NumVal::print(std::ostream &ostream) { ostream << std::to_string(val); }

bool NumVal::is_true() {
  throw std::runtime_error("It's not equal expression doable");
  //    return false;
}

PTR(Val) NumVal::call(PTR(Val) actual_arg) { return nullptr; }

NumVal::NumVal(int val) { this->val = val; }

// 888888b.                     888 888     888          888
// 888  "88b                    888 888     888          888
// 888  .88P                    888 888     888          888
// 8888888K.   .d88b.   .d88b.  888 Y88b   d88P  8888b.  888
// 888  "Y88b d88""88b d88""88b 888  Y88b d88P      "88b 888
// 888    888 888  888 888  888 888   Y88o88P   .d888888 888
// 888   d88P Y88..88P Y88..88P 888    Y888P    888  888 888
// 8888888P"   "Y88P"   "Y88P"  888     Y8P     "Y888888 888

BoolVal::BoolVal(bool is_True) { this->is_True = is_True; }

bool BoolVal::is_true() { return this->is_True; }

PTR(Val) BoolVal::add_to(PTR(Val) otherVal) {
  throw std::runtime_error("add of non-number");
}

PTR(Val) BoolVal::mult_with(PTR(Val) otherVal) {
  throw std::runtime_error(
      "ERROR!! What do you want to do with BoolVal mult with?");
}

// PTR(Expr) BoolVal::to_expr() { return NEW(BoolExpr)(this->is_True); }

bool BoolVal::equals(PTR(Val) otherVal) {
  PTR(BoolVal) otherNum = CAST(BoolVal)(otherVal);
  if (otherNum == NULL) {
    return false;
  } else {
    return this->is_True == otherNum->is_True;
  }
}

void BoolVal::print(std::ostream &ostream) {
  if (this->is_True)
    ostream << "_true";
  else
    ostream << "_false";
}

PTR(Val) BoolVal::call(PTR(Val) actual_arg) { return nullptr; }

/*
 8888888888                   888     888          888
 888                          888     888          888
 888                          888     888          888
 8888888    888  888 88888b.  Y88b   d88P  8888b.  888
 888        888  888 888 "88b  Y88b d88P      "88b 888
 888        888  888 888  888   Y88o88P   .d888888 888
 888        Y88b 888 888  888    Y888P    888  888 888
 888         "Y88888 888  888     Y8P     "Y888888 888
*/

PTR(Val) FunVal::add_to(PTR(Val) otherVal) {
  throw std::runtime_error("[ERROR] Cannot not add_to");
}

std::string FunVal::to_string() {
  return "FunVal";
}
FunVal::FunVal(std::string formal_arg, PTR(Expr) body, PTR(Env) env) {
  this->formal_arg = formal_arg;
  this->body = body;
  this->env = env;
}

bool FunVal::is_true() { throw std::runtime_error("[ERROR] Cannot is_true"); }

PTR(Val) FunVal::mult_with(PTR(Val) otherVal) {
  throw std::runtime_error("[ERROR] Cannot not mult_with");
}

// PTR(Expr) FunVal::to_expr() {
//   return NEW(FunExpr)(this->formal_arg, this->body);
// }

bool FunVal::equals(PTR(Val) otherVal) {
  PTR(FunVal) otherNum = CAST(FunVal)(otherVal);
  if (otherNum == nullptr) {
    return false;
  } else {
    return this->formal_arg == otherNum->formal_arg ||
           this->body->equals(otherNum->body);
  }
}

void FunVal::print(std::ostream &ostream) {
  ostream << "(";
  ostream << this->formal_arg;
  ostream << ")";
  ostream << this->body->to_string();
}

PTR(Val) FunVal::call(PTR(Val) actual_arg) {
  //  return this->body->subst(this->formal_arg,
  //  actual_arg->to_expr())->interp();
  return body->interp(NEW(ExtendedEnv)(formal_arg, actual_arg, env));
}
