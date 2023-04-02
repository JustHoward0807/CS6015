//
//  PTR(Expr).cpp
//  MSDScript
//
//  Created by Howard Tung on 1/12/23.
//

/**
 * \file PTR(Expr).cpp
 * \brief contains expression class function implementation
 * \author Howard Tung
 */

#include "Expr.hpp"
#include "sstream"
#include "val.h"

/*
 8888888          d8b 888    d8b          888 d8b
  888            Y8P 888    Y8P          888 Y8P
  888                888                 888
  888   88888b.  888 888888 888  8888b.  888 888 88888888  .d88b.
  888   888 "88b 888 888    888     "88b 888 888    d88P  d8P  Y8b
  888   888  888 888 888    888 .d888888 888 888   d88P   88888888
  888   888  888 888 Y88b.  888 888  888 888 888  d88P    Y8b.
 8888888 888  888 888  "Y888 888 "Y888888 888 888 88888888  "Y8888
*/

VariableExpr::VariableExpr(std::string string) { this->string = string; }

NumExpr::NumExpr(int val) { this->val = val; }

AddExpr::AddExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
  this->lhs = lhs;
  this->rhs = rhs;
}

MultiExpr::MultiExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
  this->lhs = lhs;
  this->rhs = rhs;
}

LetExpr::LetExpr(std::string lhs, PTR(Expr) rhs, PTR(Expr) body) {
  this->lhs = lhs;
  this->rhs = rhs;
  this->body = body;
}

IfExpr::IfExpr(PTR(Expr) boolExpr, PTR(Expr) firstNumExpr, PTR(Expr)
                                                             secondNumExpr) {
  this->boolExpr = boolExpr;
  this->firstNumExpr = firstNumExpr;
  this->secondNumExpr = secondNumExpr;
}

BoolExpr::BoolExpr(bool is_True) { this->is_True = is_True; }

EqExpr::EqExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
  this->lhs = lhs;
  this->rhs = rhs;
}

FunExpr::FunExpr(std::string formal_arg, PTR(Expr) body) {
  this->formal_arg = formal_arg;
  this->body = body;
}

CallExpr::CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg) {
  this->to_be_called = to_be_called;
  this->actual_arg = actual_arg;
}

/*
8888888888                            888
888                                   888
888                                   888
8888888     .d88888 888  888  8888b.  888 .d8888b
888        d88" 888 888  888     "88b 888 88K
888        888  888 888  888 .d888888 888 "Y8888b.
888        Y88b 888 Y88b 888 888  888 888      X88
8888888888  "Y88888  "Y88888 "Y888888 888  88888P'
                888
                888
                888
*/

/**
 * \brief Check if this class string is equals to PTR(Expr) class provided in
 * parentheses \param *expr - Provide expression \return true if both equals
 * string, false otherwise.
 */
bool VariableExpr::equals(PTR(Expr) expr) {
  PTR(VariableExpr) v = CAST(VariableExpr)(expr);
  if (v == NULL) {
    return false;
  } else {
    return this->string == v->string;
  }
}

/**
 * \brief Check if this class val is equals to PTR(Expr) class provided in
 * parentheses \param *expr - Provide expression \return true if both equals
 * val, false otherwise.
 */

bool NumExpr::equals(PTR(Expr) expr) {
  PTR(NumExpr) n = CAST(NumExpr)(expr);
  if (n == NULL) {
    return false;
  } else {
    return this->val == n->val;
  }
}

/**
 * \brief Check if this class lhs is equals to PTR(Expr) class rhs provided in
 * parentheses \param *expr - Provide expression \return true if both equals
 * val, false otherwise.
 */

bool AddExpr::equals(PTR(Expr) expr) {
  PTR(AddExpr) n = CAST(AddExpr)(expr);
  if (n == NULL) {
    return false;
  } else {
    return lhs->equals(n->lhs) && rhs->equals(n->rhs);
  }
}


/**
 * \brief Check if this class lhs is equals to PTR(Expr) class rhs provided in
 * parentheses \param *expr - Provide expression \return true if both equals
 * val, false otherwise.
 */

bool MultiExpr::equals(PTR(Expr) expr) {
  PTR(MultiExpr) n = CAST(MultiExpr)(expr);
  if (n == NULL) {
    return false;
  } else {

    return this->lhs->equals(n->lhs) && this->rhs->equals(n->rhs);
  }
}

bool LetExpr::equals(PTR(Expr) expr) {
  PTR(LetExpr) n = CAST(LetExpr)(expr);
  if (n == NULL) {
    return false;
  } else {
    return this->lhs == n->lhs && this->rhs->equals(n->rhs) &&
           this->body->equals(n->body);
  }
}

bool IfExpr::equals(PTR(Expr) expr) {
  PTR(IfExpr) otherExpr = CAST(IfExpr)(expr);
  if (otherExpr == NULL) {
    return false;
  } else {
    return this->boolExpr->equals(otherExpr->boolExpr) &&
           this->firstNumExpr->equals(otherExpr->firstNumExpr) &&
           this->secondNumExpr->equals(otherExpr->secondNumExpr);
  }
}

bool BoolExpr::equals(PTR(Expr) expr) {

  PTR(BoolExpr) otherExpr = CAST(BoolExpr)(expr);
  if (otherExpr == NULL) {
    return false;
  } else {
    return this->is_True == otherExpr->is_True;
  }
}

bool EqExpr::equals(PTR(Expr) expr) {
  PTR(EqExpr) otherExpr = CAST(EqExpr)(expr);
  if (otherExpr == NULL) {
    return false;
  } else {
    return this->lhs->equals(otherExpr->lhs) &&
           this->rhs->equals(otherExpr->rhs);
  }
}

bool FunExpr::equals(PTR(Expr) expr) { return false; }

bool CallExpr::equals(PTR(Expr) expr) { return false; }

/*
 888                        888     888
 888                        888     888
 888                        888     888
 88888b.   8888b.  .d8888b  Y88b   d88P  8888b.  888d888
 888 "88b     "88b 88K       Y88b d88P      "88b 888P"
 888  888 .d888888 "Y8888b.   Y88o88P   .d888888 888
 888  888 888  888      X88    Y888P    888  888 888
 888  888 "Y888888  88888P'     Y8P     "Y888888 888
*/

/**
 * \brief Bc VariableExpr has variable so always return true
 * \return always true bc it is an VariableExpr class.
 */
// bool VariableExpr::hasVariable() {
//     return true;
// }

/**
 * \brief NumExpr has no variable so always return false
 * \return always false bc it is an NumExpr class.
 */

// bool NumExpr::hasVariable() {
//     return false;
// }

/**
 * \brief Check both lhs and rhs Expression class to see if they have variable.
 * \return true or false based on if it has variables
 */
// bool MultiExpr::hasVariable() {
//     return this->lhs->hasVariable() || this->rhs->hasVariable();
// }

/**
 * \brief Check both lhs and rhs Expression class to see if they have variable.
 * \return true or false based on if it has variables
 */

// bool AddExpr::hasVariable() {
//     return this->lhs->hasVariable() || this->rhs->hasVariable();
// }
//
// bool LetExpr::hasVariable() {
//     return this->rhs->hasVariable() || this->body->hasVariable();
// }
//
// bool IfExpr::hasVariable() {
//     return this->boolExpr->hasVariable() ||
//     this->secondNumExpr->hasVariable() || this->firstNumExpr->hasVariable();
// }
//
// bool BoolExpr::hasVariable() {
//     return false;
// }
//
// bool EqExpr::hasVariable() {
//     return this->lhs->hasVariable() || this->rhs->hasVariable();
// }

/*
8888888          888
  888            888
  888            888
  888   88888b.  888888  .d88b.  888d888 88888b.
  888   888 "88b 888    d8P  Y8b 888P"   888 "88b
  888   888  888 888    88888888 888     888  888
  888   888  888 Y88b.  Y8b.     888     888 d88P
8888888 888  888  "Y888  "Y8888  888     88888P"
                                         888
                                         888
                                         888
*/

/**
 * \brief Interp cannot be interp so give an error msg.
 * \return Bc interp will return an integer
 */
PTR(Val) VariableExpr::interp() {
  // VariableExpr cannot be interp, ex: cannot add or multiply
  throw std::runtime_error("Variable interp");
}

/**
 * \brief AddExpr both side
 * \return return the integer added value
 */

PTR(Val) AddExpr::interp() {
  //(2 + (3 * 4))
  return this->lhs->interp()->add_to(this->rhs->interp());
  //    return this->rhs->interp() * this->lhs->interp();
}

/**
 * \brief Multiply both side
 * \return return the integer multiply value
 */

PTR(Val) MultiExpr::interp() {
  return this->lhs->interp()->mult_with(this->rhs->interp());
  //    return this->rhs->interp() * this->lhs->interp();
}

/**
 * \brief return its value
 * \return return its value
 */
PTR(Val) NumExpr::interp() {
  return NEW(NumVal)(this->val);
  //    return this->val;
}

/**
 * \brief //Interp the rhs first then sub the body and interp again
 * \return return integer
 */

PTR(Val) LetExpr::interp() {
  PTR(Val) rhs_val = this->rhs->interp();
  return body->subst(this->lhs, rhs_val->to_expr())->interp();
}

PTR(Val) IfExpr::interp() {
  if (this->boolExpr->interp()->is_true())
    return this->firstNumExpr->interp();
  else
    return this->secondNumExpr->interp();
}

PTR(Val) BoolExpr::interp() { return NEW (BoolVal)(this->is_True); }

PTR(Val) EqExpr::interp() {
  if (this->lhs->interp()->to_string() != this->rhs->interp()->to_string())
    return NEW (BoolVal)(false);
  else
    return NEW (BoolVal)(true);
}

//_fun (x) x + 1
//_let f = _fun (x) x + 1
//_in  f(10)
PTR(Val) FunExpr::interp() { return NEW (FunVal)(formal_arg, body); }

PTR(Val) CallExpr::interp() {
  return this->to_be_called->interp()->call(actual_arg->interp());
}

/*
 .d8888b.           888               888
d88P  Y88b          888               888
Y88b.               888               888
 "Y888b.   888  888 88888b.  .d8888b  888888 888d888
    "Y88b. 888  888 888 "88b 88K      888    888P"
      "888 888  888 888  888 "Y8888b. 888    888
Y88b  d88P Y88b 888 888 d88P      X88 Y88b.  888
 "Y8888P"   "Y88888 88888P"   88888P'  "Y888 888
*/

/**
 * \brief Replace the variable with the expression that provided
 * \return return the expression
 */
PTR(Expr) VariableExpr::subst(std::string s, PTR(Expr) expr) {
  if (this->string == s) {
    return expr;
  }
  return NEW (VariableExpr)(this->string);
}

/**
 * \brief Replace the lhs variable or rhs that has the string provided in
 * parentheses and replace with the expression that provided \return return the
 * expression
 */
PTR(Expr) MultiExpr::subst(std::string s, PTR(Expr) expr) {
  //(new AddExpr((new MultiExpr(new NumExpr(10), new VariableExpr("x"))), new
  // NumExpr (7))) -> subst("x", new VariableExpr("y"))
  // -> equals((new AddExpr((new MultiExpr(new NumExpr(10), new
  // VariableExpr("y"))), new NumExpr (7))))
  return NEW (MultiExpr)(this->lhs->subst(s, expr), this->rhs->subst(s, expr));
}

/**
 * \brief Replace the lhs variable or rhs that has the string provided in
 * parentheses and replace with the expression that provided \return return the
 * expression
 */
PTR(Expr) AddExpr::subst(std::string s, PTR(Expr) expr) {
  return NEW (AddExpr)(this->lhs->subst(s, expr), this->rhs->subst(s, expr));
}

/**
 * \brief Directly return the NumExpr expression bc NumExpr class have only val
 * Integer member, so can't be replaced. \return return the expression
 */
PTR(Expr) NumExpr::subst(std::string s, PTR(Expr) expr) {
  return NEW (NumExpr)(this->val);
}

PTR(Expr) LetExpr::subst(std::string s, PTR(Expr) expr) {
  if (s == lhs) {
    return NEW (LetExpr)(s, rhs->subst(s, expr), this->body);
  } else {
    return this->body->subst(this->lhs, this->rhs)->subst(s, expr);
  }
}

//_let same = 1 == 2
//_in  _if 1 == 2
//     _then _false + 5
//     _else 88

PTR(Expr) IfExpr::subst(std::string s, PTR(Expr) expr) {
  return NEW (IfExpr)(this->boolExpr->subst(s, expr),
                    this->firstNumExpr->subst(s, expr),
                    this->secondNumExpr->subst(s, expr));
}

PTR(Expr) BoolExpr::subst(std::string s, PTR(Expr) expr) {
  return NEW (BoolExpr)(this->is_True);
}

PTR(Expr) EqExpr::subst(std::string s, PTR(Expr) expr) {
  return NEW (EqExpr)(this->rhs->subst(s, expr), this->lhs->subst(s, expr));
}

PTR(Expr) FunExpr::subst(std::string s, PTR(Expr) expr) {
  if (s == this->formal_arg) {
    return NEW (FunExpr)(this->formal_arg, this->body);

  } else {
    return NEW (FunExpr)(this->formal_arg, this->body->subst(s, expr));
  }
}

PTR(Expr) CallExpr::subst(std::string s, PTR(Expr) expr) {
  return NEW (CallExpr)(this->to_be_called->subst(s, expr),
                      this->actual_arg->subst(s, expr));
}

/*
8888888b.          d8b          888
888   Y88b         Y8P          888
888    888                      888
888   d88P 888d888 888 88888b.  888888
8888888P"  888P"   888 888 "88b 888
888        888     888 888  888 888
888        888     888 888  888 Y88b.
888        888     888 888  888  "Y888
*/

void NumExpr::print(std::ostream &ostream) { ostream << std::to_string(val); }

void AddExpr::print(std::ostream &ostream) {
  ostream << "(";
  this->lhs->print(ostream);
  ostream << "+";
  this->rhs->print(ostream);
  ostream << ")";
}

void MultiExpr::print(std::ostream &ostream) {
  ostream << "(";
  this->lhs->print(ostream);
  ostream << "*";
  this->rhs->print(ostream);
  ostream << ")";
}

void VariableExpr::print(std::ostream &ostream) { ostream << this->string; }

void LetExpr::print(std::ostream &ostream) {
  ostream << "(_let ";
  ostream << this->lhs;
  ostream << "=";
  this->rhs->print(ostream);
  ostream << " _in ";
  this->body->print(ostream);
  ostream << ")";
}

void IfExpr::print(std::ostream &ostream) {
  ostream << "(_if ";
  this->boolExpr->print(ostream);
  ostream << " _then ";
  this->firstNumExpr->print(ostream);
  ostream << " _else ";
  this->secondNumExpr->print(ostream);
  ostream << ")";
}

void BoolExpr::print(std::ostream &ostream) {
  if (this->is_True)
    ostream << "_true";
  else
    ostream << "_false";
}

void EqExpr::print(std::ostream &ostream) {
  ostream << "(";
  this->lhs->print(ostream);
  ostream << "==";
  this->rhs->print(ostream);
  ostream << ")";
}

void FunExpr::print(std::ostream &ostream) {
  ostream << "(_fun ";
  ostream << "(";
  ostream << this->formal_arg;
  ostream << ") ";
  this->body->print(ostream);
  ostream << ") ";
}

void CallExpr::print(std::ostream &ostream) {
  ostream << "(";
  this->to_be_called->print(ostream);
  ostream << "(";
  this->actual_arg->print(ostream);
  ostream << ")";
  ostream << ")";
}

/*
d888                               888            d8b
888                               888            Y8P
888                               888
888888  .d88b.           .d8888b  888888 888d888 888 88888b.   .d88b.
888    d88""88b          88K      888    888P"   888 888 "88b d88P"88b
888    888  888          "Y8888b. 888    888     888 888  888 888  888
Y88b.  Y88..88P               X88 Y88b.  888     888 888  888 Y88b 888
 "Y888  "Y88P"  88888888  88888P'  "Y888 888     888 888  888  "Y88888
                                                                   888
                                                              Y8b d88P
                                                               "Y88P"
*/

std::string Expr::to_string() {
  std::stringstream st("");
  this->print(st);
  return st.str();
}

std::string Expr::pretty_print_to_string() {
  std::stringstream st("");
  this->pretty_print(st);
  return st.str();
}

/*
                          888    888
                          888    888
                          888    888
 88888b.  888d888  .d88b.  888888 888888 888  888          88888b.
 888 "88b 888P"   d8P  Y8b 888    888    888  888          888 "88b
 888  888 888     88888888 888    888    888  888          888  888
 888 d88P 888     Y8b.     Y88b.  Y88b.  Y88b 888          888 d88P
 88888P"  888      "Y8888   "Y888  "Y888  "Y88888 88888888 88888P"
 888                                          888          888
 888                                     Y8b d88P          888
 888                                      "Y88P"           888
*/

void NumExpr::pretty_print(std::ostream &ostream) {
  std::streampos streamPos;
  pretty_print_at(prec_none, ostream, streamPos, false);
}

void NumExpr::pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                              std::streampos &streamPos, bool addParent) {
  ostream << std::to_string(this->val);
}

void VariableExpr::pretty_print(std::ostream &ostream) {
  std::streampos streamPos;
  pretty_print_at(prec_none, ostream, streamPos, false);
}

void VariableExpr::pretty_print_at(precedence_t precedence_t,
                                   std::ostream &ostream,
                                   std::streampos &streamPos, bool addParent) {
  ostream << this->string;
}

void AddExpr::pretty_print(std::ostream &ostream) {
  std::streampos streamPos;
  pretty_print_at(prec_none, ostream, streamPos, false);
}

void AddExpr::pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                              std::streampos &streamPos, bool addParent) {
  if (precedence_t > prec_add) {
    ostream << "(";
  }
  this->lhs->pretty_print_at(static_cast<::precedence_t>(prec_add + 1), ostream,
                             streamPos, true);
  ostream << " + ";
  this->rhs->pretty_print_at(static_cast<::precedence_t>(prec_add), ostream,
                             streamPos, false);

  if (precedence_t > prec_add) {
    ostream << ")";
  }
}

void MultiExpr::pretty_print(std::ostream &ostream) {
  std::streampos streamPos;
  pretty_print_at(prec_none, ostream, streamPos, false);
}

void MultiExpr::pretty_print_at(precedence_t precedence_t,
                                std::ostream &ostream,
                                std::streampos &streamPos, bool addParent) {
  if (precedence_t > prec_mult) {
    ostream << "(";
  }
  this->lhs->pretty_print_at(static_cast<::precedence_t>(prec_mult + 1),
                             ostream, streamPos, false);
  ostream << " * ";
  PTR(LetExpr) t = CAST(LetExpr)(this->rhs);

  this->rhs->pretty_print_at(
      static_cast<::precedence_t>(prec_mult), ostream, streamPos,
      t == NULL ? addParent : (precedence_t > prec_none) && addParent);

  if (precedence_t > prec_mult) {
    ostream << ")";
  }
}

void LetExpr::pretty_print(std::ostream &ostream) {
  std::streampos streamPos;
  pretty_print_at(prec_none, ostream, streamPos, false);
}

void LetExpr::pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                              std::streampos &streamPos, bool addParent) {
  if (precedence_t > prec_add && addParent) {
    ostream << "(";
  }

  int temp = ostream.tellp();
  ostream << "_let ";
  ostream << this->lhs;
  ostream << " = ";

  this->rhs->pretty_print_at(prec_none, ostream, streamPos, false);
  ostream << "\n";
  std::streampos newStreamPos = ostream.tellp();
  int indent = temp - streamPos;
  for (int i = 0; i < indent; i++) {
    ostream << " ";
  }
  ostream << "_in  ";
  this->body->pretty_print_at(prec_none, ostream, newStreamPos, false);

  if (precedence_t > prec_add && addParent) {
    ostream << ")";
  }
}

void IfExpr::pretty_print(std::ostream &ostream) {
  std::streampos streamPos;
  pretty_print_at(prec_none, ostream, streamPos, false);
}

void IfExpr::pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                             std::streampos &streamPos, bool addParent) {
  if (precedence_t > prec_add && addParent) {
    ostream << "(";
  }

  int temp = ostream.tellp();
  ostream << "_if ";
  this->boolExpr->pretty_print_at(prec_none, ostream, streamPos, false);
  ostream << "\n";
  std::streampos newStreamPos = ostream.tellp();
  int indent = temp - streamPos;
  for (int i = 0; i < indent; i++) {
    ostream << " ";
  }
  ostream << "_then ";

  this->firstNumExpr->pretty_print_at(prec_none, ostream, streamPos, false);
  ostream << "\n";
  newStreamPos = ostream.tellp();
  indent = temp - streamPos;
  for (int i = 0; i < indent; i++) {
    ostream << " ";
  }
  ostream << "_else ";
  this->secondNumExpr->pretty_print_at(prec_none, ostream, newStreamPos, false);

  if (precedence_t > prec_add && addParent) {
    ostream << ")";
  }
}

void BoolExpr::pretty_print(std::ostream &ostream) {
  std::streampos streamPos;
  pretty_print_at(prec_none, ostream, streamPos, false);
}

void BoolExpr::pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                               std::streampos &streamPos, bool addParent) {

  if (this->is_True == 0)
    ostream << "_false";
  else
    ostream << "true";
}

void EqExpr::pretty_print(std::ostream &ostream) {
  std::streampos streamPos;
  pretty_print_at(prec_none, ostream, streamPos, false);
}

void EqExpr::pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                             std::streampos &streamPos, bool addParent) {
  //    if (precedence_t > prec_equal) {
  //        ostream << "(";
  //    }
  this->lhs->pretty_print_at(static_cast<::precedence_t>(prec_equal), ostream,
                             streamPos, true);
  ostream << " == ";
  PTR(LetExpr) t = CAST(LetExpr)(this->rhs);

  this->rhs->pretty_print_at(static_cast<::precedence_t>(prec_equal), ostream,
                             streamPos, true);

  //    if (precedence_t > prec_equal) {
  //        ostream << ")";
  //    }
}

void FunExpr::pretty_print(std::ostream &ostream) {
  std::streampos streamPos;
  pretty_print_at(prec_none, ostream, streamPos, false);
}

void FunExpr::pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                              std::streampos &streamPos, bool addParent) {
  print(ostream);
}

void CallExpr::pretty_print(std::ostream &ostream) {
  std::streampos streamPos;
  pretty_print_at(prec_none, ostream, streamPos, false);
}

void CallExpr::pretty_print_at(precedence_t precedence_t, std::ostream &ostream,
                               std::streampos &streamPos, bool addParent) {
  print(ostream);
}

// 8888888b.
// 888   Y88b
// 888    888
// 888   d88P  8888b.  888d888 .d8888b   .d88b.
// 8888888P"      "88b 888P"   88K      d8P  Y8b
// 888        .d888888 888     "Y8888b. 88888888
// 888        888  888 888          X88 Y8b.
// 888        "Y888888 888      88888P'  "Y8888

PTR(Expr) parse_Str(std::string string) {
  std::istringstream s(string);
  return parse_Expr(s);
}

PTR(Expr) parse_Expr(std::istream &instream) {
  PTR(Expr) e = parse_comparg(instream);
  skip_whitespace(instream);

  int peek = instream.peek();
  if (peek == '=') {
    consume(instream, '=');
    consume(instream, '=');
    // PTR(Expr) *rhs = parse_Expr(instream);
    // PTR(Expr) *rhs = parse_Multicand(instream);
    PTR(Expr) rhs = parse_Expr(instream);
    return NEW (EqExpr)(e, rhs);
  } else {
    return e;
  }
}

PTR(Expr) parse_comparg(std::istream &instream) {
  PTR(Expr) e = parse_Addend(instream);
  skip_whitespace(instream);

  int peek = instream.peek();
  if (peek == '+') {
    consume(instream, '+');
    PTR(Expr) rhs = parse_comparg(instream);

    return NEW (AddExpr)(e, rhs);
  } else if (peek == '-') {
    throw std::runtime_error("Don't know how to handle subtraction");
  } else {
    return e;
  }
}

PTR(Expr) parse_Addend(std::istream &instream) {
  PTR(Expr) e = parse_Multicand(instream);
  skip_whitespace(instream);

  int peek = instream.peek();
  if (peek == '*') {
    consume(instream, '*');
    // PTR(Expr) *rhs = parse_Expr(instream);
    // PTR(Expr) *rhs = parse_Multicand(instream);
    PTR(Expr) rhs = parse_Addend(instream);
    return NEW (MultiExpr)(e, rhs);
  } else {
    return e;
  }
}

PTR(Expr) parse_Multicand(std::istream &instream) {
  PTR(Expr) e = parse_inner(instream);
  skip_whitespace(instream);
  if (instream.peek() != '(' && isdigit(instream.peek())) {
    throw std::runtime_error("[ERROR] : Invalid input");
  }

  while (instream.peek() == '(') {
    consume(instream, '(');
    PTR(Expr) actual_arg = parse_Expr(instream);
    consume(instream, ')');
    e = NEW (CallExpr)(e, actual_arg);
  }
  return e;
}

PTR(Expr) parse_inner(std::istream &instream) {
  skip_whitespace(instream);

  int peek = instream.peek();
  if ((peek == '-') || isdigit(peek)) {
    return parse_Num(instream);
  } else if (peek == '(') {
    consume(instream, '(');
    PTR(Expr) e = parse_Expr(instream);
    skip_whitespace(instream);
    peek = instream.get();
    if (peek != ')') {
      throw std::runtime_error("Missing close parenthesis");
    }
    return e;
  } else if (isalpha(peek)) {
    return parse_Var(instream);
  } else if (peek == '_') {
    consume(instream, '_');
    peek = instream.peek();
    if (instream.peek() == 'l') {
      return parse_Let(instream);
    }

    else if (peek == 'f' || peek == 't') {
      consume(instream, peek);
      peek = instream.peek();

      if (peek == 'a' || peek == 'r') {
        return parse_Bool(instream);
      }

      else if (peek == 'u') {
        return parse_Fun(instream);
      }

    } else {
      return parse_If(instream);
    }

  } else {
    consume(instream, peek);
    throw std::runtime_error("Invalid input");
  }

  throw std::runtime_error("Invalid input");
}

PTR(Expr) parse_Var(std::istream &instream) {
  std::string s;
  while (true) {
    int peek = instream.peek();
    if (isalpha(peek)) {
      consume(instream, peek);

      if (instream.peek() == '_') {
        throw std::runtime_error("Invalid input");
      }
      s += peek;
    } else {
      break;
    }
  }
  return NEW (VariableExpr)(s);
}

PTR(Expr) parse_Let(std::istream &instream) {

  consume(instream, 'l');
  consume(instream, 'e');
  consume(instream, 't');

  skip_whitespace(instream);
  std::string lhs;
  while (!isspace(instream.peek()) && instream.peek() != '=') {
    lhs = parse_Var(instream)->to_string();
//    std::cout << "lhs: " << lhs << std::endl;
  }
  skip_whitespace(instream);
  consume(instream, '=');
  skip_whitespace(instream);
  PTR(Expr) rhs = parse_Expr(instream);
//  std::cout << "rhs: " << rhs->to_string() << std::endl;
  consume(instream, '_');
  consume(instream, 'i');
  consume(instream, 'n');

  skip_whitespace(instream);
  PTR(Expr) body = parse_Expr(instream);
//  std::cout << "body: " << body->to_string() << std::endl;
  return NEW (LetExpr)(lhs, rhs, body);
}

PTR(Expr) parse_If(std::istream &instream) {

  consume(instream, 'i');
  consume(instream, 'f');
  skip_whitespace(instream);

  PTR(Expr) ifExpr = parse_Expr(instream);
  skip_whitespace(instream);
  consume(instream, '_');
  consume(instream, 't');
  consume(instream, 'h');
  consume(instream, 'e');
  consume(instream, 'n');
  skip_whitespace(instream);
  PTR(Expr) lhs = parse_Expr(instream);

  consume(instream, '_');
  consume(instream, 'e');
  consume(instream, 'l');
  consume(instream, 's');
  consume(instream, 'e');
  PTR(Expr) rhs = parse_Expr(instream);

  return NEW (IfExpr)(ifExpr, lhs, rhs);
}

PTR(Expr) parse_Bool(std::istream &instream) {
  if (instream.peek() == 'a') {
    consume(instream, 'a');
    consume(instream, 'l');
    consume(instream, 's');
    consume(instream, 'e');

    return NEW (BoolExpr)(false);
  } else if (instream.peek() == 'r') {
    consume(instream, 'r');
    consume(instream, 'u');
    consume(instream, 'e');
    return NEW (BoolExpr)(true);
  } else {
    throw std::runtime_error("Parsing Bool wrong");
  }
}

PTR(Expr) parse_Fun(std::istream &instream) {
  //  std::cout << (char)instream.peek() << std::endl;

  consume(instream, 'u');
  consume(instream, 'n');
  skip_whitespace(instream);
  consume(instream, '(');
  std::string lhs;

  //  while (instream.peek() != ')') {
  lhs = parse_Var(instream)->to_string();
  //    std::cout << "lhs: " << lhs << std::endl;
  //  }

  //      std::cout << varExpr->to_string() << std::endl;
  consume(instream, ')');
  skip_whitespace(instream);
  PTR(Expr) body = parse_Expr(instream);
  //    body->print(std::cout);

  return NEW (FunExpr)(lhs, body);
  //  return nullptr;
}

PTR(Expr) parse_Num(std::istream &instream) {
  int numFromStream = 0;
  bool negative = false;
  if (instream.peek() == '-') {

    negative = true;
    consume(instream, '-');
    if (isspace(instream.peek())) {
      throw std::runtime_error("unexpected input after expression");
    }
    if (instream.peek() == EOF) {
      throw std::runtime_error("Invalid input");
    }
  }

  if (isspace(instream.peek())) {
    throw std::runtime_error("unexpected input after expression");
  }

  while (true) {
    int peek = instream.peek();
    if (isdigit(peek)) {
      consume(instream, peek);
      numFromStream = numFromStream * 10 + (peek - '0');
    } else {
      break;
    }
  }

  //    if (num > INT_FAST64_MAX || num < )

  if (negative) {
    numFromStream = -numFromStream;
  }

  return NEW (NumExpr)(numFromStream);
}

static void consume(std::istream &instream, int expect) {
  int temp = instream.get();
  if (temp != expect) {
    throw std::runtime_error("Consume mismatch");
  }
}

static void skip_whitespace(std::istream &instream) {
  while (true) {
    int peek = instream.peek();
    if (!isspace(peek)) {
      break;
    } else {
      consume(instream, peek);
    }
  }
}
