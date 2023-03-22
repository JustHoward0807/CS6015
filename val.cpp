//
// Created by Howard Tung on 3/11/23.
//

#include "val.h"
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

Val *NumVal::mult_with(Val *otherVal) {
  NumVal *other_num = dynamic_cast<NumVal *>(otherVal);
  if (other_num == NULL)
    throw std::runtime_error("MultExpr of non-number");
  return new NumVal((unsigned)this->val * (unsigned)other_num->val);
}

Val *NumVal::add_to(Val *otherVal) {
  NumVal *other_num = dynamic_cast<NumVal *>(otherVal);
  if (other_num == NULL)
    throw std::runtime_error("AddExpr of non-number");
  return new NumVal((unsigned)this->val + (unsigned)other_num->val);
}

Expr *NumVal::to_expr() { return new NumExpr(this->val); }

bool NumVal::equals(Val *otherVal) {
  NumVal *otherNum = dynamic_cast<NumVal *>(otherVal);
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

Val *NumVal::call(Val *actual_arg) { return nullptr; }

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

Val *BoolVal::add_to(Val *otherVal) {
  throw std::runtime_error("add of non-number");
}

Val *BoolVal::mult_with(Val *otherVal) {
  throw std::runtime_error(
      "ERROR!! What do you want to do with BoolVal mult with?");
}

Expr *BoolVal::to_expr() { return new BoolExpr(this->is_True); }

bool BoolVal::equals(Val *otherVal) {
  BoolVal *otherNum = dynamic_cast<BoolVal *>(otherVal);
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

Val *BoolVal::call(Val *actual_arg) { return nullptr; }

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

Val *FunVal::add_to(Val *otherVal) {
  // TODO: Check this
  throw std::runtime_error("add of non-number");
}

FunVal::FunVal(std::string formal_arg, Expr *body) {
  this->formal_arg = formal_arg;
  this->body = body;
}

bool FunVal::is_true() {
  throw std::runtime_error("It's not equal expression doable");
}

Val *FunVal::mult_with(Val *otherVal) {
  // TODO: Check this
  throw std::runtime_error(
      "ERROR!! What do you want to do with BoolVal mult with?");
}

Expr *FunVal::to_expr() {
  // TODO: Change this
  //  return new NumExpr(10);
  return nullptr;
}

bool FunVal::equals(Val *otherVal) {
  // TODO: Change this
  FunVal *otherNum = dynamic_cast<FunVal *>(otherVal);
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

Val *FunVal::call(Val *actual_arg) {
  return this->body->subst(this->formal_arg, actual_arg->to_expr())->interp();
}
