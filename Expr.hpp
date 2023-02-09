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
#include <stdio.h>
#include <stdexcept>
#include <string>
#include <iostream>
#pragma once

typedef enum {
    prec_none,      // = 0
    prec_add,       // = 1
    prec_mult       // = 2
} precedence_t;
class Expr {

public:
    virtual bool equals(Expr *expr) = 0;
    virtual int interp() = 0;
    virtual bool hasVariable() = 0;
    virtual Expr* subst(std::string s, Expr* expr) = 0;
    virtual void print(std::ostream &ostream) = 0;
    std::string to_string();
    std::string pretty_print_to_string();
    virtual void pretty_print(std::ostream &ostream) = 0;
    virtual void pretty_print_at(precedence_t precedence_t, std::ostream &ostream) = 0;
};

class Num: public Expr{
public:
    int val;
    Num(int val);
    bool equals(Expr *expr);
    int interp();
    bool hasVariable();
    Expr* subst(std::string s, Expr* expr);
    void print(std::ostream &ostream);
    void pretty_print(std::ostream &ostream);
    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream);
};

class Add : public Expr {
public:
    Expr *lhs; //!< lhs of Expression
    Expr *rhs; //!< rhs of Expression
    
    Add(Expr *lhs,Expr *rhs);
    bool equals(Expr *expr);
    int interp();
    bool hasVariable();
    Expr* subst(std::string s, Expr* expr);
    void print(std::ostream &ostream);
    void pretty_print(std::ostream &ostream);
    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream);
};

class Multi : public Expr {
public:
    Expr *lhs; //!< lhs of Expression
    Expr *rhs; //!< rhs of Expression
    
    Multi(Expr *lhs, Expr *rhs);
    bool equals(Expr *expr);
    int interp();
    bool hasVariable();
    Expr* subst(std::string s, Expr* expr);
    void print(std::ostream &ostream);
    void pretty_print(std::ostream &ostream);
    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream);
};

class Variable : public Expr {
public:
    std::string string;
    
    Variable(std::string string);
    bool equals(Expr *expr);
    int interp();
    bool hasVariable();
    Expr* subst(std::string s, Expr* expr);
    void print(std::ostream &ostream);
    void pretty_print(std::ostream &ostream);
    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream);
};

//class _let : public Expr {
//public:
//    std::string lhs;
//    Expr* rhs;
//    Expr* body;
//    _let();
//    bool equals(Expr *expr);
//    int interp();
//    bool hasVariable();
//    Expr* subst(std::string s, Expr* expr);
//    void print(std::ostream &ostream);
//    void pretty_print(std::ostream &ostream);
//    void pretty_print_at(precedence_t precedence_t, std::ostream &ostream);
//};
