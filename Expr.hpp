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

class Expr {
public:
    virtual bool equals(Expr *expr) = 0;
    virtual int interp() = 0;
    virtual bool hasVariable() = 0;
    virtual Expr* subst(std::string s, Expr* expr) = 0;
//    virtual void print(std::ostream &ostream) = 0;
};

class Num: public Expr{
public:
    int val;
    Num(int val);
    bool equals(Expr *expr);
    int interp();
    bool hasVariable();
    Expr* subst(std::string s, Expr* expr);
//    void print(std::ostream &ostream);
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
//    void print(std::ostream &ostream);
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
//    void print(std::ostream &ostream);
    
};

class Variable : public Expr {
public:
    std::string string;
    
    Variable(std::string string);
    bool equals(Expr *expr);
    int interp();
    bool hasVariable();
    Expr* subst(std::string s, Expr* expr);
//    void print(std::ostream &ostream);
    
};
