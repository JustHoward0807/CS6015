//
// Created by Howard Tung on 3/11/23.
//

#pragma once

#include <string>
class Expr;
class Val {
public:
    virtual Val* add_to(Val *otherVal) = 0;
    virtual Val* mult_with(Val *otherVal) = 0;
    virtual Expr* to_expr() = 0;
    virtual bool equals(Val *otherVal) = 0;
    std::string to_string();
    virtual void print(std::ostream &ostream) = 0;
    virtual bool is_true() = 0;
    virtual Val * call(Val *actual_arg) = 0;
};


class NumVal : public Val {
public:
    int val;
    NumVal(int val);
    Val* mult_with(Val *otherVal);
    Val* add_to(Val *otherVal);
    Expr* to_expr();
    bool equals(Val *otherVal);
    void print(std::ostream &ostream);
    bool is_true();
    Val * call(Val *actual_arg);
};

class BoolVal : public Val {
public:
    bool is_True;
    explicit BoolVal(bool is_True);

    Val* add_to(Val *otherVal) override;
    Val* mult_with(Val *otherVal) override;
    Expr* to_expr() override;
    bool equals(Val *otherVal) override;
    void print(std::ostream &ostream) override;
    bool is_true() override;
    Val * call(Val *actual_arg) override;
};

class FunVal : public Val {
  public:
    std::string formal_arg;
    Expr *body;
    explicit FunVal(std::string formal_arg, Expr* body);

    Val* mult_with(Val *otherVal) override;
    Val* add_to(Val *otherVal) override;
    Expr* to_expr() override;
    bool equals(Val *otherVal) override;
    void print(std::ostream &ostream) override;
    bool is_true() override;
    Val * call(Val *actual_arg) override;
};
