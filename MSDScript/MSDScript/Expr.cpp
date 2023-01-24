//
//  Expr.cpp
//  MSDScript
//
//  Created by Howard Tung on 1/12/23.
//


#include "Expr.hpp"
#include "catch.h"

Num::Num(int val) {
    this->val = val;
}

Variable::Variable(std::string string) {
    this->string = string;
}

bool Variable::equals(Expr *expr) {
    Variable *v = dynamic_cast<Variable *>(expr);
    if (v == NULL) {
        return false;
    } else {
        return this->string == v->string;
    }
}

bool Num::equals(Expr *expr) {
    Num *n = dynamic_cast<Num *>(expr);
    if (n == NULL) {
        return false;
    } else {
        return this->val == n->val;
    }
}

Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}


bool Add::equals(Expr *expr) {
    Add *n = dynamic_cast<Add *>(expr);
    if (n == NULL) {
        return false;
    } else {
        return lhs->equals(n->lhs) && rhs->equals(n->rhs);
    }
}

Multi::Multi(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}


bool Multi::equals(Expr *expr) {
    Multi *n = dynamic_cast<Multi *>(expr);
    if (n == NULL) {
        return false;
    } else {

        return this->lhs->equals(n->lhs) && this->rhs->equals(n->rhs);
    }
}

TEST_CASE("Test for expression") {
    Add *add = new Add(new Num(2), new Num(3));
    Add *add2 = new Add(new Num(2), new Num(3));
    Add *add3 = new Add(new Num(2), new Num(4));
    Multi *mav = new Multi(new Num(6), new Add(new Num(6), new Variable("Hello")));
    Multi *mav2 = new Multi(new Num(6), new Add(new Num(6), new Variable("Hello")));
    Multi *mav3 = new Multi(new Num(6), new Add(new Num(6), new Variable("World")));
//    Add *edge = new Add(new Num(0), new Num(1));
    SECTION("Equals") {
        CHECK( (new Num(1))->equals(new Num(1)) == true );
        CHECK( (new Variable("x"))->equals(new Variable("y")) == false );
        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(2),new Num(3)))==true );
        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(3),new Num(2)))==false );
        CHECK( (new Multi(new Num(2),new Num(2)))->equals(new Add(new Num(1),new Num(2)))==false );
    }
    SECTION("Add Test") {
        REQUIRE(add->equals(add2));
        REQUIRE(add->equals(add3) == 0);
    }

    SECTION("Multi Add Variable Test") {
        REQUIRE(mav->equals(mav2));
        REQUIRE(mav->equals(mav3) == 0);
    }

}