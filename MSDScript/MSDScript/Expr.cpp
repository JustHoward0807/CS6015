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

int Variable::interp() {
    //Variable cannot be interp, ex: cannot add or multiply
    throw std::runtime_error("message");
}

//(2 + (3 * 4))
int Add::interp() {
//    Num *nlhs = dynamic_cast<Num *>(this->lhs);
//    Num *nrhs = dynamic_cast<Num *>(this->rhs);
//    if (nlhs == NULL && nrhs == NULL) {
        return this->rhs->interp() + this->lhs->interp();
//    } else if (nlhs == NULL) {
//        return this->lhs->interp() + nrhs->val;
//    } else if (nrhs == NULL) {
//        return this->rhs->interp() + nlhs->val;
//    }

//    return nlhs->val + nrhs->val;
}

int Multi::interp() {
//    Num *nlhs = dynamic_cast<Num *>(this->lhs);
//    Num *nrhs = dynamic_cast<Num *>(this->rhs);
//    if (nlhs == NULL && nrhs == NULL) {
        return this->rhs->interp() * this->lhs->interp();
//    } else if (nlhs == NULL) {
//        return this->lhs->interp() * nrhs->val;
//    } else if (nrhs == NULL) {
//        return this->rhs->interp() * nlhs->val;
//    }
//
//    return nlhs->val * nrhs->val;
}

int Num::interp() {
    return this->val;
}

bool Variable::hasVariable() {
    return true;
}

bool Num::hasVariable() {
    return false;
}

bool Multi::hasVariable() {
    Variable *v = dynamic_cast<Variable *>(this->lhs);
    Variable *v2 = dynamic_cast<Variable *>(this->rhs);
    if (v != NULL || v2 != NULL) {
        return true;
    } else {
        return false;
    }
}

bool Add::hasVariable() {
    Variable *v = dynamic_cast<Variable *>(this->lhs);
    Variable *v2 = dynamic_cast<Variable *>(this->rhs);
    if (v != NULL || v2 != NULL) {
        return true;
    } else {
        return false;
    }
}

//(new Add(new Variable("x"), new Num(7)))
//                       ->subst("x", new Variable("y"))
//                       ->equals(new Add(new Variable("y"), new Num(7)))

//(new Add(new Num(7), new Variable("x")))
//                       ->subst("x", new Variable("y"))
//                       ->equals(new Add(new Num(7), new Variable("y")))

//(new Add(new Variable("x"), new Variable("x")))
//                       ->subst("x", new Variable("y"))
//                       ->equals(new Add(new Variable("y"), new Variable("y")))

//CHECK( (new VarExpr("x"))
//               ->subst("x", new AddExpr(new VarExpr("y"),new NumExpr(7)))
//               ->equals(new AddExpr(new VarExpr("y"),new NumExpr(7))) );


Expr *Variable::subst(std::string s, Expr *expr) {
    if (this->string == s) {
        return expr;
    }
    return new Variable(this->string);
}

//Subst can one line

//(new Add((new Multi(new Num(10), new Variable("x"))), new Num (7))) -> subst("x", new Variable("y"))
//                       -> equals((new Add((new Multi(new Num(10), new Variable("y"))), new Num (7))))
Expr *Multi::subst(std::string s, Expr *expr) {
    return new Multi(this->lhs->subst(s, expr), this->rhs->subst(s,expr));
//    Variable *nlhs = dynamic_cast<Variable *>(this->lhs);
//    Variable *nrhs = dynamic_cast<Variable *>(this->rhs);
//    if (nlhs != NULL && nrhs != NULL) {
//        if (nlhs->string == s && nrhs->string == s) {
//
//            nlhs = dynamic_cast<Variable *> (expr);
//            nrhs = dynamic_cast<Variable *> (expr);
//            return new Multi(nlhs, nrhs);
//        }

//    } else if (nlhs != NULL) {
//        if (nlhs->string == s) {

//            nlhs = dynamic_cast<Variable *> (expr);
//            return new Multi(nlhs, this->rhs);
//        }
//    } else if (nrhs != NULL) {
//        if (nrhs->string == s) {
//            nrhs = dynamic_cast<Variable *> (expr);
//            return new Multi(this->lhs, nrhs);
//        }
//    }
//    return new Multi(this->lhs, this->rhs);
}

Expr *Add::subst(std::string s, Expr *expr) {
    return new Add(this->lhs->subst(s, expr), this->rhs->subst(s,expr));
//    Variable *nlhs = dynamic_cast<Variable *>(this->lhs);
//    Variable *nrhs = dynamic_cast<Variable *>(this->rhs);
//    if (nlhs != NULL && nrhs != NULL) {
//        if (nlhs->string == s && nrhs->string == s) {
//
//            nlhs = dynamic_cast<Variable *> (expr);
//            nrhs = dynamic_cast<Variable *> (expr);
//            return new Add(nlhs, nrhs);
//        }
//
//    } else if (nlhs != NULL) {
//        if (nlhs->string == s) {
//
//            nlhs = dynamic_cast<Variable *> (expr);
//            return new Add(nlhs, this->rhs);
//        }
//    } else if (nrhs != NULL) {
//        if (nrhs->string == s) {
//            nrhs = dynamic_cast<Variable *> (expr);
//            return new Add(this->lhs, nrhs);
//        }
//    }
//    return new Add(this->lhs, this->rhs);


}

Expr *Num::subst(std::string s, Expr *expr) {
    return new Num(this->val);
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
    SECTION("Equals") {
        CHECK((new Num(1))->equals(new Num(1)) == true);
        CHECK((new Variable("x"))->equals(new Variable("y")) == false);
        CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new Num(2), new Num(3))) == true);
        CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new Num(3), new Num(2))) == false);
        CHECK((new Multi(new Num(2), new Num(2)))->equals(new Add(new Num(1), new Num(2))) == false);
    }
    SECTION("Add Test") {
        REQUIRE(add->equals(add2));
        REQUIRE(add->equals(add3) == 0);
    }

    SECTION("Multi Add Variable Test") {
        REQUIRE(mav->equals(mav2));
        REQUIRE(mav->equals(mav3) == 0);


    }

    SECTION("Interpret check") {
        //        CHECK_THROWS_WITH( (new Variable("x"))->interp(), "no value for variable" );

        //3 * 2
        CHECK((new Multi(new Num(3), new Num(2)))->interp() == 6);
        //3 + 2
        CHECK((new Add(new Num(3), new Num(2)))->interp() == 5);
        //2 * (3 * 4)
        CHECK((new Multi(new Num(2), new Multi(new Num(3), new Num(4))))->interp() == 24);

        //(5*5) * 2
        CHECK((new Multi(new Multi(new Num(5), new Num(5)), new Num(2)))->interp() == 50);

        //(2 * 3) * (2 * 3)
        CHECK((new Multi(new Multi(new Num(2), new Num(3)), new Multi(new Num(2), new Num(3))))->interp() == 36);


        //(2 + (3 * 4))
        CHECK((new Add(new Num(2), new Multi(new Num(3), new Num(4))))->interp() == 14);

        //(10+15) + (20 + 20))
        CHECK((new Add(new Add(new Num(10), new Num(15)), new Add(new Num(20), new Num(20))))->interp() == 65);

        //(10*10) * (30+15)
        CHECK((new Multi(new Multi(new Num(10), new Num(10)), new Add(new Num(30), new Num(15))))->interp() == 4500);

        // (10 + 10) + (20+ 20) * (30 + 30) + (40 * 40)
        CHECK((new Multi(
                new Add(
                        new Add(new Num(10), new Num(10)),
                        new Add(new Num(20), new Num(20))
                ),
                new Add(
                        new Add(new Num(30), new Num(30)),
                        new Multi(new Num(40), new Num(40))
                )
        ))->interp() == 99600);
    }

    SECTION("HasVariable check") {
        CHECK((new Multi(new Variable("x"), new Num(2)))->hasVariable() == true);
        CHECK((new Variable("q"))->hasVariable() == true);
        CHECK((new Num(6))->hasVariable() == false);
    }

    SECTION("Subst check") {
        CHECK((new Add(new Variable("x"), new Num(7)))
                      ->subst("x", new Variable("y"))
                      ->equals(new Add(new Variable("y"), new Num(7))));

        CHECK((new Add(new Num(7), new Variable("x")))
                      ->subst("x", new Variable("y"))
                      ->equals(new Add(new Num(7), new Variable("y"))));

        CHECK((new Add(new Variable("x"), new Variable("x")))
                      ->subst("x", new Variable("y"))
                      ->equals(new Add(new Variable("y"), new Variable("y"))));

        CHECK((new Multi(new Variable("x"), new Num(7)))
                      ->subst("x", new Variable("y"))
                      ->equals(new Multi(new Variable("y"), new Num(7))));

        CHECK((new Multi(new Num(7), new Variable("x")))
                      ->subst("x", new Variable("y"))
                      ->equals(new Multi(new Num(7), new Variable("y"))));

        CHECK((new Multi(new Variable("x"), new Variable("x")))
                      ->subst("x", new Variable("y"))
                      ->equals(new Multi(new Variable("y"), new Variable("y"))));

        CHECK((new Num(2))
                      ->subst("x", new Num(3))
                      ->equals(new Num(3)) == false);
//        CHECK((new Num(2) ->subst("x", new Num(2)) ->equals(new Num(2))) == false);

        CHECK( (new Variable("x"))
                       ->subst("x", new Add(new Variable("y"),new Num(7)))
                       ->equals(new Add(new Variable("y"),new Num(7))) );

        CHECK( (new Add((new Multi(new Num(10), new Variable("x"))), new Num (7))) -> subst("x", new Variable("y"))
                       -> equals((new Add((new Multi(new Num(10), new Variable("y"))), new Num (7)))) );
    }
}