//
//  Expr.cpp
//  MSDScript
//
//  Created by Howard Tung on 1/12/23.
//

/**
* \file Expr.cpp
* \brief contains expression class function implementation
* \author Howard Tung
*/

#include "Expr.hpp"
#include "catch.h"

/*
 88888888                      d8b       888          d8b                      888       d8b
   888                        Y8P       888          Y8P                      888       Y8P
   888                                  888                                   888
   888         88888b.        888       888888       888        8888b.        888       888       88888888        .d88b.
   888         888 "88b       888       888          888           "88b       888       888          d88P        d8P  Y8b
   888         888  888       888       888          888       .d888888       888       888         d88P         88888888
   888         888  888       888       Y88b.        888       888  888       888       888        d88P          Y8b.
 88888888      888  888        888       "Y888        888       "Y888888       888       888       88888888        "Y8888
*/

Num::Num(int val) {
    this->val = val;
}

Variable::Variable(std::string string) {
    this->string = string;
}

Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}


Multi::Multi(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
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
* \brief Check if this class string is equals to Expr class provided in parentheses
* \param *expr - Provide expression
* \return true if both equals string, false otherwise.
*/
bool Variable::equals(Expr *expr) {
    Variable *v = dynamic_cast<Variable *>(expr);
    if (v == NULL) {
        return false;
    } else {
        return this->string == v->string;
    }
}

/**
* \brief Check if this class val is equals to Expr class provided in parentheses
* \param *expr - Provide expression
* \return true if both equals val, false otherwise.
*/

bool Num::equals(Expr *expr) {
    Num *n = dynamic_cast<Num *>(expr);
    if (n == NULL) {
        return false;
    } else {
        return this->val == n->val;
    }
}

/**
* \brief Check if this class lhs is equals to Expr class rhs provided in parentheses
* \param *expr - Provide expression
* \return true if both equals val, false otherwise.
*/

bool Add::equals(Expr *expr) {
    Add *n = dynamic_cast<Add *>(expr);
    if (n == NULL) {
        return false;
    } else {
        return lhs->equals(n->lhs) && rhs->equals(n->rhs);
    }
}

/**
* \brief Check if this class lhs is equals to Expr class rhs provided in parentheses
* \param *expr - Provide expression
* \return true if both equals val, false otherwise.
*/

bool Multi::equals(Expr *expr) {
    Multi *n = dynamic_cast<Multi *>(expr);
    if (n == NULL) {
        return false;
    } else {

        return this->lhs->equals(n->lhs) && this->rhs->equals(n->rhs);
    }
}

/*
888                        888     888                  d8b          888      888
888                        888     888                  Y8P          888      888
888                        888     888                               888      888
88888b.   8888b.  .d8888b  Y88b   d88P  8888b.  888d888 888  8888b.  88888b.  888  .d88b.
888 "88b     "88b 88K       Y88b d88P      "88b 888P"   888     "88b 888 "88b 888 d8P  Y8b
888  888 .d888888 "Y8888b.   Y88o88P   .d888888 888     888 .d888888 888  888 888 88888888
888  888 888  888      X88    Y888P    888  888 888     888 888  888 888 d88P 888 Y8b.
888  888 "Y888888  88888P'     Y8P     "Y888888 888     888 "Y888888 88888P"  888  "Y8888
*/

/**
* \brief Bc Variable has variable so always return true
* \return always true bc it is an Variable class.
*/
bool Variable::hasVariable() {
    return true;
}

/**
* \brief Num has no variable so always return false
* \return always false bc it is an Num class.
*/

bool Num::hasVariable() {
    return false;
}

/**
* \brief Check both lhs and rhs Expression class to see if they have variable.
* \return true or false based on if it has variables
*/
bool Multi::hasVariable() {
    return this->lhs->hasVariable() || this->rhs->hasVariable();
}

/**
* \brief Check both lhs and rhs Expression class to see if they have variable.
* \return true or false based on if it has variables
*/

bool Add::hasVariable() {
    return this->lhs->hasVariable() || this->rhs->hasVariable();
}

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
* \return Bc interp will return an interger
*/
int Variable::interp() {
    //Variable cannot be interp, ex: cannot add or multiply
    throw std::runtime_error("message");
}

/**
* \brief Add both side
* \return return the integer added value
*/
int Add::interp() {
    //(2 + (3 * 4))
    return this->rhs->interp() + this->lhs->interp();
}
/**
* \brief Multiply both side
* \return return the integer multiply value
*/
int Multi::interp() {
    return this->rhs->interp() * this->lhs->interp();
}

/**
* \brief return its value
* \return return its value
*/
int Num::interp() {
    return this->val;
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
Expr *Variable::subst(std::string s, Expr *expr) {
    if (this->string == s) {
        return expr;
    }
    return new Variable(this->string);
}

/**
* \brief Replace the lhs variable or rhs that has the string provided in parentheses and replace with the expression that provided
* \return return the expression
*/
Expr *Multi::subst(std::string s, Expr *expr) {
    //(new Add((new Multi(new Num(10), new Variable("x"))), new Num (7))) -> subst("x", new Variable("y"))
// -> equals((new Add((new Multi(new Num(10), new Variable("y"))), new Num (7))))
    return new Multi(this->lhs->subst(s, expr), this->rhs->subst(s, expr));
}

/**
* \brief Replace the lhs variable or rhs that has the string provided in parentheses and replace with the expression that provided
* \return return the expression
*/
Expr *Add::subst(std::string s, Expr *expr) {
    return new Add(this->lhs->subst(s, expr), this->rhs->subst(s, expr));
}

/**
* \brief Directly return the Num expression bc Num class have only val Integer member, so can't be replaced.
* \return return the expression
*/
Expr *Num::subst(std::string s, Expr *expr) {
    return new Num(this->val);
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


//void Num::print(std::ostream &ostream) {
//}
//
//void Add::print(std::ostream &ostream) {
//}
//
//void Multi::print(std::ostream &ostream) {}
//
//void Variable::print(std::ostream &ostream) {}








/*
88888888888                   888    d8b
    888                       888    Y8P
    888                       888
    888      .d88b.  .d8888b  888888 888 88888b.   .d88b.
    888     d8P  Y8b 88K      888    888 888 "88b d88P"88b
    888     88888888 "Y8888b. 888    888 888  888 888  888
    888     Y8b.          X88 Y88b.  888 888  888 Y88b 888
    888      "Y8888   88888P'  "Y888 888 888  888  "Y88888
                                                       888
                                                  Y8b d88P
                                                   "Y88P"
*/

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
        CHECK((new Add(new Variable("d"), new Num(4)))->hasVariable() == true);
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

        CHECK((new Variable("x"))
                      ->subst("x", new Add(new Variable("y"), new Num(7)))
                      ->equals(new Add(new Variable("y"), new Num(7))));

        CHECK((new Add((new Multi(new Num(10), new Variable("x"))), new Num(7)))->subst("x", new Variable("y"))
                      ->equals((new Add((new Multi(new Num(10), new Variable("y"))), new Num(7)))));
    }

    SECTION("Check Print") {
//        std::ostream& ostream = std::cout;
//        Num* n = new Num(5);
//        Add* a = new Add(n,n);
//        a -> print(ostream);
    }
}