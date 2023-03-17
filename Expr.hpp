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
#include <cstdio>
#include <stdexcept>
#include <string>
#include <iostream>

#pragma once

typedef enum {
    prec_equal,
    prec_none,      // = 0

    prec_add,       // = 1
    prec_mult       // = 2
} precedence_t;

class Val;

class Expr {

public:
    virtual bool equals(Expr *expr) = 0;

    virtual Val *interp() = 0;

    virtual bool hasVariable() = 0;

    virtual Expr *subst(std::string s, Expr *expr) = 0;

    virtual void print(std::ostream &ostream) = 0;

    std::string to_string();

    std::string pretty_print_to_string();

    virtual void pretty_print(std::ostream &ostream) = 0;

    virtual void
    pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent) = 0;
};

class NumExpr : public Expr {
public:
    int val;

    NumExpr(int val);

    bool equals(Expr *expr);

    Val *interp();

    bool hasVariable();

    Expr *subst(std::string s, Expr *expr);

    void print(std::ostream &ostream);

    void pretty_print(std::ostream &ostream);

    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent);
};

class AddExpr : public Expr {
public:
    Expr *lhs; //!< lhs of Expression
    Expr *rhs; //!< rhs of Expression

    AddExpr(Expr *lhs, Expr *rhs);

    bool equals(Expr *expr);

    Val *interp();

    bool hasVariable();

    Expr *subst(std::string s, Expr *expr);

    void print(std::ostream &ostream);

    void pretty_print(std::ostream &ostream);

    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent);
};

class MultiExpr : public Expr {
public:
    Expr *lhs; //!< lhs of Expression
    Expr *rhs; //!< rhs of Expression

    MultiExpr(Expr *lhs, Expr *rhs);

    bool equals(Expr *expr);

    Val *interp();

    bool hasVariable();

    Expr *subst(std::string s, Expr *expr);

    void print(std::ostream &ostream);

    void pretty_print(std::ostream &ostream);

    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent);
};

class VariableExpr : public Expr {
public:
    std::string string;

    VariableExpr(std::string string);

    bool equals(Expr *expr);

    Val *interp();

    bool hasVariable();

    Expr *subst(std::string s, Expr *expr);

    void print(std::ostream &ostream);

    void pretty_print(std::ostream &ostream);

    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent);
};

class LetExpr : public Expr {
public:
    std::string lhs;
    Expr *rhs;
    Expr *body;

    LetExpr(std::string lhs, Expr *rhs, Expr *body);

    bool equals(Expr *expr);

    Val *interp();

    bool hasVariable();

    Expr *subst(std::string s, Expr *expr);

    void print(std::ostream &ostream);

    void pretty_print(std::ostream &ostream);

    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent);
};

class BoolExpr : public Expr {
public:
    bool is_True;

    BoolExpr(bool is_True);

    bool equals(Expr *expr);

    Val *interp();

    bool hasVariable();

    Expr *subst(std::string s, Expr *expr);

    void print(std::ostream &ostream);

    void pretty_print(std::ostream &ostream);

    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent);
};

class IfExpr : public Expr {
public:
    Expr *boolExpr;
    Expr *firstNumExpr;
    Expr *secondNumExpr;

    IfExpr(Expr *boolExpr, Expr *firstNumExpr, Expr *secondNumExpr);

    bool equals(Expr *expr);

    Val *interp();

    bool hasVariable();

    Expr *subst(std::string s, Expr *expr);

    void print(std::ostream &ostream);

    void pretty_print(std::ostream &ostream);

    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent);
};

class EqExpr : public Expr {
public:
    Expr *lhs;
    Expr *rhs;

    EqExpr(Expr *lhs, Expr *rhs);

    bool equals(Expr *expr);

    Val *interp();

    bool hasVariable();

    Expr *subst(std::string s, Expr *expr);

    void print(std::ostream &ostream);

    void pretty_print(std::ostream &ostream);

    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent);
};


Expr *parse_Expr(std::istream &instream);

Expr *parse_Str(std::string string);

Expr *parse_Num(std::istream &instream);

Expr *parse_Addend(std::istream &instream);

Expr *parse_Multicand(std::istream &instream);

Expr *parse_Var(std::istream &instream);

Expr *parse_Let(std::istream &instream);

Expr *parse_If(std::istream &instream);

Expr *parse_Bool(std::istream &instream);

Expr *parse_comparg(std::istream &instream);

static void consume(std::istream &instream, int expect);

static void skip_whitespace(std::istream &instream);
