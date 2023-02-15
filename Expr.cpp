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
#include "sstream"

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

_let::_let(std::string lhs, Expr *rhs, Expr *body) {
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
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

bool _let::equals(Expr *expr) {
    _let *n = dynamic_cast<_let *>(expr);
    if (n == NULL) {
        return false;
    } else {
        return this->lhs == n->lhs && this->rhs->equals(n->rhs) && this->body->equals(n->body);
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

bool _let::hasVariable() {
    return this->rhs->hasVariable() || this->body->hasVariable();
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

//_let x = 5 + 2
//_in x + 1
//(_let x=5 _in ((_let y=3 _in (y+2))+x))
/**
* \brief //Interp the rhs first then sub the body and interp again
* \return return integer
*/
int _let::interp() {
    return this->body->subst(this->lhs, this->rhs)->interp();
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

Expr *_let::subst(std::string s, Expr *expr) {
    if (s == lhs) {
        return new _let(s, rhs->subst(s, expr), this->body);
    } else {
        return new _let(lhs, rhs->subst(s, expr), this->body->subst(s, expr));
    }
//    else {
//        return this->body->subst(this->lhs, this->rhs)->subst(s, expr);
//    }


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


void Num::print(std::ostream &ostream) {
    ostream << std::to_string(val);
}

void Add::print(std::ostream &ostream) {
    ostream << "(";
    this->lhs->print(ostream);
    ostream << "+";
    this->rhs->print(ostream);
    ostream << ")";
}

void Multi::print(std::ostream &ostream) {
    ostream << "(";
    this->lhs->print(ostream);
    ostream << "*";
    this->rhs->print(ostream);
    ostream << ")";
}

void Variable::print(std::ostream &ostream) {
    ostream << this->string;
}

void _let::print(std::ostream &ostream) {
    ostream << "(_let ";
    ostream << this->lhs;
    ostream << "=";
    this->rhs->print(ostream);
    ostream << " _in ";

//    ostream << "(";
    this->body->print(ostream);
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
                          888    888                                       d8b          888
                          888    888                                       Y8P          888
                          888    888                                                    888
88888b.  888d888  .d88b.  888888 888888 888  888          88888b.  888d888 888 88888b.  888888
888 "88b 888P"   d8P  Y8b 888    888    888  888          888 "88b 888P"   888 888 "88b 888
888  888 888     88888888 888    888    888  888          888  888 888     888 888  888 888
888 d88P 888     Y8b.     Y88b.  Y88b.  Y88b 888          888 d88P 888     888 888  888 Y88b.
88888P"  888      "Y8888   "Y888  "Y888  "Y88888 88888888 88888P"  888     888 888  888  "Y888
888                                          888          888
888                                     Y8b d88P          888
888                                      "Y88P"           888
*/

void Num::pretty_print(std::ostream &ostream) {
    std::streampos streamPos;
    pretty_print_at(prec_none, ostream, streamPos, false);
}

void Num::pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent) {
    ostream << std::to_string(this->val);
}

void Variable::pretty_print(std::ostream &ostream) {
    std::streampos streamPos;
    pretty_print_at(prec_none, ostream, streamPos, false);
}

void
Variable::pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent) {
    ostream << this->string;
}

void Add::pretty_print(std::ostream &ostream) {
    std::streampos streamPos;
    pretty_print_at(prec_none, ostream, streamPos, false);
}

void Add::pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent) {
    if (precedence_t > prec_add) {
        ostream << "(";
    }
    this->lhs->pretty_print_at(static_cast<::precedence_t>(prec_add + 1), ostream, streamPos, true);
    ostream << " + ";
    this->rhs->pretty_print_at(static_cast<::precedence_t>(prec_add), ostream, streamPos, false);

    if (precedence_t > prec_add) {
        ostream << ")";
    }
}

void Multi::pretty_print(std::ostream &ostream) {
    std::streampos streamPos;
    pretty_print_at(prec_none, ostream, streamPos, false);
}

//CHECK((new Multi(new Num(1), new Add(new Num(2), new Num(3)))) -> pretty_print_to_string() == "1 * (2 + 3)");
// CHECK((new Multi (new Num(2), new Multi(new Num(3), new Num(4)))) -> pretty_print_to_string() == "2 * 3 * 4");
void
Multi::pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent) {
    if (precedence_t > prec_mult) {
        ostream << "(";
    }
    this->lhs->pretty_print_at(static_cast<::precedence_t>(prec_mult + 1), ostream, streamPos, false);
    ostream << " * ";
    _let *t = dynamic_cast<_let *>(this->rhs);

    this->rhs->pretty_print_at(static_cast<::precedence_t>(prec_mult), ostream, streamPos,
                               t == NULL ? addParent : (precedence_t > prec_none) && addParent);

    if (precedence_t > prec_mult) {
        ostream << ")";
    }
}

void _let::pretty_print(std::ostream &ostream) {
    std::streampos streamPos;
    pretty_print_at(prec_none, ostream, streamPos, false);
}

void
_let::pretty_print_at(precedence_t precedence_t, std::ostream &ostream, std::streampos &streamPos, bool addParent) {
    if (precedence_t > prec_add  && addParent) {
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

    if (precedence_t > prec_add  && addParent) {
        ostream << ")";
    }
}














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
        CHECK((new Add(new Num(1), new Add(new Num(2), new Num(3))))->to_string() == "(1+(2+3))");
        CHECK((new Add(new Add(new Num(1), new Num(2)), new Num(3)))->to_string() == "((1+2)+3)");
        CHECK((new Num(10))->to_string() == "10");
        CHECK((new Variable("x"))->to_string() == "x");
        CHECK((new Add(new Num(5), new Num(5)))->to_string() == "(5+5)");
        CHECK((new Multi(new Num(10), new Num(10)))->to_string() == "(10*10)");
        CHECK((new Add(new Num(5), new Multi(new Num(5), new Num(5))))->to_string() == "(5+(5*5))");


        CHECK((new Multi(new Multi(new Num(2), new Num(3)), new Num(4)))->pretty_print_to_string() == "(2 * 3) * 4");
        CHECK((new Add(new Num(1), new Multi(new Num(2), new Num(3))))->pretty_print_to_string() == "1 + 2 * 3");
        CHECK((new Add(new Num(1), new Add(new Num(2), new Num(3))))->pretty_print_to_string() == "1 + 2 + 3");
        CHECK((new Multi(new Num(2), new Multi(new Num(3), new Num(4))))->pretty_print_to_string() == "2 * 3 * 4");
        CHECK((new Multi(new Num(1), new Add(new Num(2), new Num(3))))->pretty_print_to_string() == "1 * (2 + 3)");
        CHECK((new Multi(new Num(-8), new Add(new Num(2), new Num(3))))->pretty_print_to_string() == "-8 * (2 + 3)");
        CHECK((new Add(new Multi(new Num(9), new Add(new Num(4), new Num(3))),
                       new Add(new Multi(new Num(2), new Num(4)), new Num(1))))->pretty_print_to_string() ==
              "9 * (4 + 3) + 2 * 4 + 1");
        CHECK((new Multi(new Multi(new Num(10), new Multi(new Multi(new Num(10), new Num(10)), new Num(10))),
                         new Multi(new Num(10), new Num(10))))->pretty_print_to_string() ==
              "(10 * (10 * 10) * 10) * 10 * 10");
        CHECK((new Add(new Num(1), new Add(new Num(2), new Num(5))))->pretty_print_to_string() == "1 + 2 + 5");
        //(2 + 3) * 5
        CHECK((new Multi(new Add(new Num(2), new Num(3)), new Num(5)))->pretty_print_to_string() == "(2 + 3) * 5");
    }

    SECTION("Check _let") {
        CHECK((new _let("x", new Num(5), new Num(5)))->equals(new _let("x", new Num(5), new Num(5))) == true);
        CHECK((new _let("x", new Num(5), new Add(new Variable("x"), new Num(5))))->interp() == 10);
        CHECK((new _let("x", new Num(5), new Add(new Num(10), new Num(5))))->interp() == 15);
        CHECK((new _let("x", new Multi(new Num(7), new Num(3)), new Add(new Variable("x"), new Num(5))))->interp() ==
              26);
        CHECK((new _let("x", new Num(5), new _let("x", new Add(new Variable("x"), new Num(2)),
                                                  new Add(new Variable("x"), new Num(1)))))->interp() == 8);
        CHECK((new _let("x", new Num(5),
                        new _let("x", new Num(6), new Add(new Variable("x"), new Num(1)))))->interp() == 7);
        CHECK((new _let("x", new Num(5),
                        new _let("y", new Num(6), new Add(new Variable("x"), new Num(1)))))->interp() == 6);
        CHECK((
                      new _let("x", new Num(5), new _let("y", new Num(3),
                                                         new Add(new Add(new Variable("y"), new Num(2)),
                                                                 new Variable("x"))))
              )->interp() == 10);

//        (_let x=5 _in ((_let y=3 _in (y + (_let z = 10, _in (z + 5))))+x)) ==23
        CHECK((
                      new _let("x", new Num(5), new _let("y", new Num(3),
                                                         new Add(
                                                                 new Add(
                                                                         new Variable("y"), new _let("z", new Num(10),
                                                                                                     new Add(new Variable(
                                                                                                                     "z"),
                                                                                                             new Num(5)))),
                                                                 new Variable("x"))))
              )->interp() == 23);

        //(_let x=5 _in ((_let y= (_let q = 5 _in q * 10) _in (y + (_let z = 10, _in (z + 5))))+x)) == 70
        CHECK((
                      new _let("x", new Num(5),
                               new _let("y", new _let("q", new Num(5), new Multi(new Num(10), new Variable("q"))),
                                        new Add(
                                                new Add(
                                                        new Variable("y"), new _let("z", new Num(10),
                                                                                    new Add(new Variable(
                                                                                                    "z"),
                                                                                            new Num(5)))),
                                                new Variable("x"))))
              )->interp() == 70);


        //x = 10, y = 10, z = 10. x + y + z = 30
        CHECK((
                      new _let(
                              "x", new Num(10),
                              new _let("y", new Num(10),
                                       new _let("z", new Num(10), new Add(new Add(new Variable("x"), new Variable("y")),
                                                                          new Variable("z"))))
                      )
              )->interp() == 30);

        CHECK((
                      new _let("x", new Num(5), new _let("y", new Num(3),
                                                         new Add(new Add(new Variable("y"), new Num(2)),
                                                                 new Variable("x"))))
              )->to_string() == "(_let x=5 _in (_let y=3 _in ((y+2)+x)))");

        _let let1("x",
                  new Num(5),
                  new Add(
                          new _let("y", new Num(3), new Add(new Variable("y"), new Num(2))),
                          new Variable("x")));
        CHECK(let1.to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
        CHECK((new _let("x", new Num(5), new Add(new Variable("x"), new Num(5))))->to_string() ==
              "(_let x=5 _in (x+5))");

//        let1.pretty_print(std::cout);
        CHECK((let1).pretty_print_to_string() == "_let x = 5\n_in  (_let y = 3\n      _in  y + 2) + x");
        _let *test2 = new _let("x", new Num(5),
                               new Add(new _let("y", new Num(3), new Add(new Variable("y"), new Num(2))),
                                       new Variable("x")));
        _let *test3 = new _let("x", new Num(5), new _let("x", new Num(6), new Add(new Variable("x"), new Num(1))));
        _let *test4 = new _let("x", new Num(5), new _let("y", new Num(6), new Add(new Variable("x"), new Num(1))));
//        _let *test5 = new _let("x", new Num(5), new _let("x", new Add(new Variable("x"), new Num(2)), new Add(new Variable("x"), new Num(1))));
        _let *test5 = new _let("x", new Num(5), new _let("x", new Add(new Variable("x"), new Num(2)),
                                                         new Add(new Variable("x"), new Num(1))));
        _let *test6 = new _let("x", new Num(5), new _let("y", new Num(6), new _let("y", new Num(7),
                                                                                   new Add(new Variable("x"),
                                                                                           new Num(1)))));
        _let *test10 = new _let("x", new Num(5), new Add(new _let("y", new Num(6), new _let("y", new Num(7),
                                                                                            new Add(new Variable("x"),
                                                                                                    new Num(1)))),
                                                         new Num(1)));
        _let *test11 = new _let("x", new Add(new Variable("x"), new Num(2)),
                                new Add(new _let("y", new Num(6), new _let("y", new Num(7),
                                                                           new Add(new Variable("x"),
                                                                                   new Num(1)))),
                                        new Num(1)));
        std::cout << test2->pretty_print_to_string() << std::endl;
        std::cout << test3->pretty_print_to_string() << std::endl;
        std::cout << test4->pretty_print_to_string() << std::endl;
        std::cout << test5->pretty_print_to_string() << std::endl;
        std::cout << test6->pretty_print_to_string() << std::endl;
        std::cout << test10->pretty_print_to_string() << std::endl;
        std::cout << test11->pretty_print_to_string() << std::endl;

        _let letBase1("x", new Num(5), new Add(new Variable("x"), new Num(1)));
        _let letBase2("x", new Num(6), new Add(new Variable("x"), new Num(1)));

        CHECK(letBase1.pretty_print_to_string() == "_let x = 5\n_in  x + 1");
        CHECK(letBase2.pretty_print_to_string() == "_let x = 6\n_in  x + 1");
        _let let2("x", new Num(5), &letBase2);
        CHECK(let2.pretty_print_to_string() == "_let x = 5\n"
                                               "_in  _let x = 6\n"
                                               "     _in  x + 1");

        Multi let11(new Num(1), new Multi(new Num(2), &letBase1));
        std::cout << let11.pretty_print_to_string() << std::endl;

        CHECK ((new _let("x", new Num(2), new _let("z", new Num(4), new Add(new Variable("x"), new Num(10)))))
                       ->interp() == 12);

        CHECK((new _let("x", new Num(1), new Multi(
                new Multi(new Variable("x"), new Multi(new Multi(new Num(10), new Num(10)), new Variable("x"))),
                new Multi(new Num(10), new Num(10)))))
                      ->interp() == 10000);
        CHECK(let11.pretty_print_to_string() == "1 * 2 * _let x = 5\n"
                                                "        _in  x + 1");
        Add let13(&let11, new Num(5));
        CHECK(let13.pretty_print_to_string() == "1 * 2 * (_let x = 5\n"
                                                "         _in  x + 1) + 5");


    }
}

TEST_CASE("Pretty Print examples_Kevin") {           //Created from assignment examples
    std::stringstream out("");
    (new _let("x", new Num(5), new Add(new Variable("x"), new Num(1))))->pretty_print(out);
    CHECK(out.str() == "_let x = 5\n"
                       "_in  x + 1");
    out.str(std::string());
    (new Add(new _let("x", new Num(5), new Variable("x")), new Num(1)))->pretty_print(out);
    CHECK(out.str() == "(_let x = 5\n"
                       " _in  x) + 1");
    out.str(std::string());
    (new Multi(new Num(5), new _let("x", new Num(5), new Add(new Variable("x"), new Num(1)))))->pretty_print(out);
    CHECK(out.str() == "5 * _let x = 5\n"
                       "    _in  x + 1");
    out.str(std::string());
    (new Add(new Multi(new Num(5), new _let("x", new Num(5), new Variable("x"))), new Num(1)))->pretty_print(out);
    CHECK(out.str() == "5 * (_let x = 5\n"
                       "     _in  x) + 1");
    out.str(std::string());
    (new _let("x", new Num(5),
              new Add(new _let("y", new Num(3), new Add(new Variable("y"), new Num(2))), new Variable("x"))))
            ->pretty_print(out);

    CHECK(out.str() == "_let x = 5\n"
                       "_in  (_let y = 3\n"
                       "      _in  y + 2) + x");
    out.str(std::string());
    (new _let("x", new _let("y", new Num(6), new Multi(new Variable("y"), new Num(2))),
              new Add(new Variable("x"), new Num(1))))->pretty_print(out);
    CHECK(out.str() == "_let x = _let y = 6\n"
                       "         _in  y * 2\n"
                       "_in  x + 1");

}

TEST_CASE("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let") {
    _let *tripleNestedLet = new _let("x", new Num(1),
                                     new _let("y", new Num(1),
                                              new Multi(new Add(new Variable("x"), new Variable("y")),
                                                        new Variable("z"))));
    _let *tripleNestedLet2 = new _let("x", new Num(1),
                                      new _let("y", new Num(1),
                                               new _let("z", new Add(new Variable("x"), new Num(1)),
                                                        new Add(new Add(new Variable("x"), new Variable("y")),
                                                                new Variable("z")))));
    _let *tripleNestedLet3 = new _let("x", new Num(1),
                                      new _let("y", new Num(1),
                                               new _let("z", new Add(new Variable("x"), new Num(1)),
                                                        new Multi(new Add(new Variable("x"), new Variable("y")),
                                                                  new Variable("z")))));


    CHECK(tripleNestedLet->pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  (x + y) * z"
    );
    CHECK(tripleNestedLet2->pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  _let z = x + 1\n"
          "          _in  (x + y) + z"
    );
    CHECK(tripleNestedLet3->pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  _let z = x + 1\n"
          "          _in  (x + y) * z"
    );
    _let *tripleNestedLet4 = new _let("x", new Num(5),
                                      new _let("y", new Num(3),
                                               new Add(new Variable("y"), new Num(2))));
    _let *tripleNestedLet5 = new _let("x", new Num(5),
                                      new Add(new _let("y", new Num(3),
                                                       new Add(new Variable("y"), new Num(2))), new Variable("x")));
    std::stringstream out("");
    out.str("");
    tripleNestedLet4->pretty_print(out);
    CHECK(out.str() ==
          "_let x = 5\n"
          "_in  _let y = 3\n"
          "     _in  y + 2"
    );

    CHECK(tripleNestedLet5->pretty_print_to_string() == "_let x = 5\n"
                                                        "_in  (_let y = 3\n"
                                                        "      _in  y + 2) + x");
    SECTION("assignment_examples") {
        CHECK((new Add(new Multi(new Num(5), new _let("x", new Num(5), new Variable("x"))),
                       new Num(1)))->pretty_print_to_string()
              == "5 * (_let x = 5\n"
                 "     _in  x) + 1");
        CHECK((new Multi(new Multi(new Num(2), new _let("x", new Num(5), new Add(new Variable("x"), new Num(1)))),
                         new Num(3)))->pretty_print_to_string()
              == "(2 * _let x = 5\n"
                 "     _in  x + 1) * 3");
    }
    // A _let needs parentheses when it is nested immediately as the right argument of an unparenthesized *
    // where _let would have needed parentheses in the surrounding context
    // (that is, if the _let used in place of the whole * would need parentheses,
    // then it still needs parentheses within the right-hand size of *).
    SECTION("new_edge") {
        CHECK((new Multi(new Num(2),
                         new _let("x", new Num(5), new Add(new Variable("x"), new Num(1)))))->pretty_print_to_string()
              == "2 * _let x = 5\n"
                 "    _in  x + 1");
        CHECK((new Add(new Multi(new Num(5), new _let("x", new Num(5), new Multi(new Variable("x"), new Num(2)))),
                       new Num(1)))->pretty_print_to_string()
              == "5 * (_let x = 5\n"
                 "     _in  x * 2) + 1");
        CHECK((new Multi(
                (new Add(new Multi(new Num(5), new _let("x", new Num(5), new Multi(new Variable("x"), new Num(2)))),
                         new Num(1))), new Num(7)))->pretty_print_to_string()
              == "(5 * (_let x = 5\n"
                 "      _in  x * 2) + 1) * 7");
        CHECK((new _let("x", new Num(10), new Multi(
                new Multi(new Variable("x"), new Multi(new Multi(new Num(10), new Num(10)), new Num(10))),
                new Multi(new Num(10), new Num(10)))))
                      ->pretty_print_to_string() == "_let x = 10\n"
                                                    "_in  (x * (10 * 10) * 10) * 10 * 10");
        CHECK((new _let("x", new Num(1), new Multi(
                new Multi(new Variable("x"), new Multi(new Multi(new Num(10), new Num(10)), new Variable("x"))),
                new Multi(new Num(10), new Num(10)))))
                      ->pretty_print_to_string() == "_let x = 1\n"
                                                    "_in  (x * (10 * 10) * x) * 10 * 10");
        CHECK((new _let("x", new Num(1), new Multi(
                new Multi(new Variable("x"), new Multi(new Multi(new Num(10), new Num(10)), new Variable("x"))),
                new Multi(new Variable("y"), new Num(10)))))
                      ->pretty_print_to_string() == "_let x = 1\n"
                                                    "_in  (x * (10 * 10) * x) * y * 10");
    }
}

TEST_CASE("Let_equals_mine") {
    SECTION("Values_same") {
        REQUIRE((new _let("x", new Num(4), new Add(new Num(2), new Variable("x"))))->equals(
                new _let("x", new Num(4), new Add(new Num(2), new Variable("x")))));
    }
    SECTION("Values_same_different_rhs") {
        REQUIRE(!(new _let("x", new Num(4), new Add(new Num(2), new Variable("x"))))->equals(
                new _let("x", new Num(5), new Add(new Num(2), new Variable("x")))));
    }
    SECTION("Values_same_different_lhs") {
        REQUIRE(!(new _let("x", new Num(4), new Add(new Num(2), new Variable("x"))))->equals(
                new _let("y", new Num(4), new Add(new Num(2), new Variable("x")))));
    }
    SECTION("Values_same_different_body") {
        REQUIRE(!(new _let("x", new Num(4), new Add(new Num(2), new Variable("x"))))->equals(
                new _let("x", new Num(4), new Multi(new Num(3), new Variable("y")))));
    }
    SECTION("different_types") {
        REQUIRE(!(new _let("x", new Num(4), new Add(new Num(2), new Variable("x"))))->equals(
                new Multi(new Num(3), new Variable("y"))));
    }
}

TEST_CASE("Let_has_variable_mine") {
    SECTION("has") {
        REQUIRE((new _let("x", new Num(4), new Add(new Num(2), new Variable("x"))))->hasVariable());
    }
    SECTION("does_not_has") {
        REQUIRE(!(new _let("x", new Num(4), new Add(new Num(2), new Num(4))))->hasVariable());
    }
}

TEST_CASE("Let_print_mine") {
    CHECK((new _let("x", new Num(5), new Add(new _let("y", new Num(3), new Add(new Variable("y"), new Num(2))),
                                             new Variable("x"))))->to_string()
          == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
    CHECK((new _let("x", new Num(1),
                    new _let("y", new Num(1),
                             new _let("z", new Add(new Variable("x"), new Num(1)),
                                      new Multi(new Add(new Variable("x"), new Variable("y")),
                                                new Variable("z"))))))->to_string()
          == "(_let x=1 _in (_let y=1 _in (_let z=(x+1) _in ((x+y)*z))))");
}

TEST_CASE ("Let_interp_mine") {
    SECTION("hw_examples") {
        CHECK((new Add(new Multi(new Num(5), new _let("x", new Num(5), new Variable("x"))), new Num(1)))->interp() ==
              26);
        CHECK((new Multi(new Num(5), new _let("x", new Num(5), new Add(new Variable("x"), new Num(1)))))->interp() ==
              30);
    }
    SECTION("from_pretty_print_edge") {
        CHECK((new _let("x", new Num(1),
                        new _let("y", new Num(1),
                                 new _let("z", new Add(new Variable("x"), new Num(1)),
                                          new Multi(new Add(new Variable("x"), new Variable("y")),
                                                    new Variable("z"))))))->interp() == 4);
        CHECK((new Multi(
                (new Add(new Multi(new Num(5), new _let("x", new Num(5), new Multi(new Variable("x"), new Num(2)))),
                         new Num(1))), new Num(7)))->interp() == 357); // 51 * 7
        CHECK((new _let("x", new Num(10), new Multi(
                new Multi(new Variable("x"), new Multi(new Multi(new Num(10), new Num(10)), new Num(10))),
                new Multi(new Num(10), new Num(10)))))
                      ->interp() == 1000000);
        CHECK((new _let("x", new Num(1), new Multi(
                new Multi(new Variable("x"), new Multi(new Multi(new Num(10), new Num(10)), new Variable("x"))),
                new Multi(new Num(10), new Num(10)))))
                      ->interp() == 10000);
//        CHECK_THROWS_WITH( ((new _let("x", new Num(1), new Multi( new Multi(new Variable("x"), new Multi(new Multi(new Num(10), new Num(10)), new Variable("x"))), new Multi(new Variable("y"), new Num(10)))))
//                                    -> interp() == 10000), "You cannot interpret a variable expression. Substitute instead.");
    }
    SECTION("bypass_middle_let") {
        CHECK ((new _let("x", new Num(2), new _let("z", new Num(4), new Add(new Variable("x"), new Num(10)))))
                       ->interp() == 12);
    }
}
