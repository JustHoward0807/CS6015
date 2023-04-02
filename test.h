//
// Created by Howard Tung on 3/13/23.
//

#ifndef CS6015_TEST_H
#define CS6015_TEST_H

#include "Expr.hpp"
#include "catch.h"
#include "pointer.h"
#include "val.h"
/*
   888888888888888                   888    d8b
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
  PTR(AddExpr) add = NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3));
  PTR(AddExpr) add2 = NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3));
  PTR(AddExpr) add3 = NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(4));
  PTR(MultiExpr)
  mav =
      NEW(MultiExpr)(NEW(NumExpr)(6),
                     NEW(AddExpr)(NEW(NumExpr)(6), NEW(VariableExpr)("Hello")));
  PTR(MultiExpr)
  mav2 =
      NEW(MultiExpr)(NEW(NumExpr)(6),
                     NEW(AddExpr)(NEW(NumExpr)(6), NEW(VariableExpr)("Hello")));
  PTR(MultiExpr)
  mav3 =
      NEW(MultiExpr)(NEW(NumExpr)(6),
                     NEW(AddExpr)(NEW(NumExpr)(6), NEW(VariableExpr)("World")));
  SECTION("Equals") {
    CHECK((NEW(NumExpr)(1))->equals(NEW(NumExpr)(1)) == true);
    CHECK((NEW(VariableExpr)("x"))->equals(NEW(VariableExpr)("y")) == false);
    CHECK((NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)))
              ->equals(NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))) == true);
    CHECK((NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)))
              ->equals(NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(2))) ==
          false);
    CHECK((NEW(MultiExpr)(NEW(NumExpr)(2), NEW(NumExpr)(2)))
              ->equals(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) ==
          false);
  }
  SECTION("AddExpr Test") {
    REQUIRE(add->equals(add2));
    REQUIRE(add->equals(add3) == 0);
  }

  SECTION("MultiExpr AddExpr VariableExpr Test") {
    REQUIRE(mav->equals(mav2));
    REQUIRE(mav->equals(mav3) == 0);
  }

  SECTION("Interpret check") {
    // 3 * 2
    CHECK((NEW(MultiExpr)(NEW(NumExpr)(3), NEW(NumExpr)(2)))
              ->interp()
              ->equals(NEW(NumVal)(6)));
    // 3 + 2
    CHECK((NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(2)))
              ->interp()
              ->equals(NEW(NumVal)(5)));

    CHECK((NEW(AddExpr)(NEW(MultiExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)),
                        NEW(NumExpr)(4)))
              ->interp()
              ->equals(NEW(NumVal)(10)));
    // 2 * (3 * 4)
    CHECK((NEW(MultiExpr)(NEW(NumExpr)(2),
                          NEW(MultiExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4))))
              ->interp()
              ->equals(NEW(NumVal)(24)));

    //(5*5) * 2
    CHECK((NEW(MultiExpr)(NEW(MultiExpr)(NEW(NumExpr)(5), NEW(NumExpr)(5)),
                          NEW(NumExpr)(2)))
              ->interp()
              ->equals(NEW(NumVal)(50)));

    //(2 * 3) * (2 * 3)
    CHECK((NEW(MultiExpr)(NEW(MultiExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)),
                          NEW(MultiExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))
              ->interp()
              ->equals(NEW(NumVal)(36)));

    //(2 + (3 * 4))
    CHECK((NEW(AddExpr)(NEW(NumExpr)(2),
                        NEW(MultiExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4))))
              ->interp()
              ->equals(NEW(NumVal)(14)));

    //(10+15) + (20 + 20))
    CHECK((NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(15)),
                        NEW(AddExpr)(NEW(NumExpr)(20), NEW(NumExpr)(20))))
              ->interp()
              ->equals(NEW(NumVal)(65)));

    //(10*10) * (30+15)
    CHECK((NEW(MultiExpr)(NEW(MultiExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)),
                          NEW(AddExpr)(NEW(NumExpr)(30), NEW(NumExpr)(15))))
              ->interp()
              ->equals(NEW(NumVal)(4500)));

    // (10 + 10) + (20+ 20) * (30 + 30) + (40 * 40)
    CHECK(
        (NEW(MultiExpr)(
             NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)),
                          NEW(AddExpr)(NEW(NumExpr)(20), NEW(NumExpr)(20))),
             NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(30), NEW(NumExpr)(30)),
                          NEW(MultiExpr)(NEW(NumExpr)(40), NEW(NumExpr)(40)))))
            ->interp()
            ->equals(NEW(NumVal)(99600)));
  }
  //    SECTION("HasVariable check")
  //    {
  //        CHECK((NEW(MultiExpr)(NEW(VariableExpr)("x"), new
  //        NumExpr(2)))->hasVariable() == true); CHECK((new
  //        VariableExpr("q"))->hasVariable() == true); CHECK((new
  //        NumExpr(6))->hasVariable() == false); CHECK((NEW(AddExpr)(new
  //        VariableExpr("d"), NEW(NumExpr)(4)))->hasVariable() == true);
  //    }

  SECTION("Subst check") {
    CHECK((NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(7)))
              ->subst("x", NEW(VariableExpr)("y"))
              ->equals(NEW(AddExpr)(NEW(VariableExpr)("y"), NEW(NumExpr)(7))));

    CHECK((NEW(AddExpr)(NEW(NumExpr)(7), NEW(VariableExpr)("x")))
              ->subst("x", NEW(VariableExpr)("y"))
              ->equals(NEW(AddExpr)(NEW(NumExpr)(7), NEW(VariableExpr)("y"))));

    CHECK((NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(VariableExpr)("x")))
              ->subst("x", NEW(VariableExpr)("y"))
              ->equals(NEW(AddExpr)(NEW(VariableExpr)("y"),
                                    NEW(VariableExpr)("y"))));

    CHECK(
        (NEW(MultiExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(7)))
            ->subst("x", NEW(VariableExpr)("y"))
            ->equals(NEW(MultiExpr)(NEW(VariableExpr)("y"), NEW(NumExpr)(7))));

    CHECK(
        (NEW(MultiExpr)(NEW(NumExpr)(7), NEW(VariableExpr)("x")))
            ->subst("x", NEW(VariableExpr)("y"))
            ->equals(NEW(MultiExpr)(NEW(NumExpr)(7), NEW(VariableExpr)("y"))));

    CHECK((NEW(MultiExpr)(NEW(VariableExpr)("x"), NEW(VariableExpr)("x")))
              ->subst("x", NEW(VariableExpr)("y"))
              ->equals(NEW(MultiExpr)(NEW(VariableExpr)("y"),
                                      NEW(VariableExpr)("y"))));

    CHECK((NEW(NumExpr)(2))
              ->subst("x", NEW(NumExpr)(3))
              ->equals(NEW(NumExpr)(3)) == false);

    CHECK(
        (NEW(VariableExpr)("x"))
            ->subst("x", NEW(AddExpr)(NEW(VariableExpr)("y"), NEW(NumExpr)(7)))
            ->equals(NEW(AddExpr)(NEW(VariableExpr)("y"), NEW(NumExpr)(7))));

    CHECK((NEW(AddExpr)(
               (NEW(MultiExpr)(NEW(NumExpr)(10), NEW(VariableExpr)("x"))),
               NEW(NumExpr)(7)))
              ->subst("x", NEW(VariableExpr)("y"))
              ->equals((NEW(AddExpr)(
                  (NEW(MultiExpr)(NEW(NumExpr)(10), NEW(VariableExpr)("y"))),
                  NEW(NumExpr)(7)))));
  }

  SECTION("Check Print") {
    CHECK((NEW(AddExpr)(NEW(NumExpr)(1),
                        NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))
              ->to_string() == "(1+(2+3))");
    CHECK((NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
                        NEW(NumExpr)(3)))
              ->to_string() == "((1+2)+3)");
    CHECK((NEW(NumExpr)(10))->to_string() == "10");
    CHECK((NEW(VariableExpr)("x"))->to_string() == "x");
    CHECK((NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(5)))->to_string() ==
          "(5+5)");
    CHECK((NEW(MultiExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))->to_string() ==
          "(10*10)");
    CHECK((NEW(AddExpr)(NEW(NumExpr)(5),
                        NEW(MultiExpr)(NEW(NumExpr)(5), NEW(NumExpr)(5))))
              ->to_string() == "(5+(5*5))");

    CHECK((NEW(MultiExpr)(NEW(MultiExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)),
                          NEW(NumExpr)(4)))
              ->pretty_print_to_string() == "(2 * 3) * 4");
    CHECK((NEW(AddExpr)(NEW(NumExpr)(1),
                        NEW(MultiExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))
              ->pretty_print_to_string() == "1 + 2 * 3");
    CHECK((NEW(AddExpr)(NEW(NumExpr)(1),
                        NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))
              ->pretty_print_to_string() == "1 + 2 + 3");
    CHECK((NEW(MultiExpr)(NEW(NumExpr)(2),
                          NEW(MultiExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4))))
              ->pretty_print_to_string() == "2 * 3 * 4");
    CHECK((NEW(MultiExpr)(NEW(NumExpr)(1),
                          NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))
              ->pretty_print_to_string() == "1 * (2 + 3)");
    CHECK((NEW(MultiExpr)(NEW(NumExpr)(-8),
                          NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))
              ->pretty_print_to_string() == "-8 * (2 + 3)");
    CHECK((NEW(AddExpr)(
               NEW(MultiExpr)(NEW(NumExpr)(9),
                              NEW(AddExpr)(NEW(NumExpr)(4), NEW(NumExpr)(3))),
               NEW(AddExpr)(NEW(MultiExpr)(NEW(NumExpr)(2), NEW(NumExpr)(4)),
                            NEW(NumExpr)(1))))
              ->pretty_print_to_string() == "9 * (4 + 3) + 2 * 4 + 1");
    CHECK((NEW(MultiExpr)(
               NEW(MultiExpr)(NEW(NumExpr)(10),
                              NEW(MultiExpr)(NEW(MultiExpr)(NEW(NumExpr)(10),
                                                            NEW(NumExpr)(10)),
                                             NEW(NumExpr)(10))),
               NEW(MultiExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10))))
              ->pretty_print_to_string() == "(10 * (10 * 10) * 10) * 10 * 10");
    CHECK((NEW(AddExpr)(NEW(NumExpr)(1),
                        NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(5))))
              ->pretty_print_to_string() == "1 + 2 + 5");
    //(2 + 3) * 5
    CHECK((NEW(MultiExpr)(NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)),
                          NEW(NumExpr)(5)))
              ->pretty_print_to_string() == "(2 + 3) * 5");
  }

  SECTION("Check LetExpr") {
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(NumExpr)(5)))
              ->equals(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(NumExpr)(5))) ==
          true);
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
                        NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(5))))
              ->interp()
              ->equals(NEW(NumVal)(10)));
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
                        NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(5))))
              ->interp()
              ->equals(NEW(NumVal)(15)));
    CHECK((NEW(LetExpr)("x", NEW(MultiExpr)(NEW(NumExpr)(7), NEW(NumExpr)(3)),
                        NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(5))))
              ->interp()
              ->equals(NEW(NumVal)(26)));
    CHECK((NEW(LetExpr)(
               "x", NEW(NumExpr)(5),
               NEW(LetExpr)(
                   "x", NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(2)),
                   NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(1)))))
              ->interp()
              ->equals(NEW(NumVal)(8)));
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
                        NEW(LetExpr)("x", NEW(NumExpr)(6),
                                     NEW(AddExpr)(NEW(VariableExpr)("x"),
                                                  NEW(NumExpr)(1)))))
              ->interp()
              ->equals(NEW(NumVal)(7)));
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
                        NEW(LetExpr)("y", NEW(NumExpr)(6),
                                     NEW(AddExpr)(NEW(VariableExpr)("x"),
                                                  NEW(NumExpr)(1)))))
              ->interp()
              ->equals(NEW(NumVal)(6)));
    CHECK((NEW(LetExpr)(
               "x", NEW(NumExpr)(5),
               NEW(LetExpr)("y", NEW(NumExpr)(3),
                            NEW(AddExpr)(NEW(AddExpr)(NEW(VariableExpr)("y"),
                                                      NEW(NumExpr)(2)),
                                         NEW(VariableExpr)("x")))))
              ->interp()
              ->equals(NEW(NumVal)(10)));

    //        (PTR(LetExpr) x=5 _in ((PTR(LetExpr) y=3 _in (y + (PTR(LetExpr) z
    //        = 10, _in (z + 5))))+x)) ==23
    CHECK((NEW(LetExpr)(
               "x", NEW(NumExpr)(5),
               NEW(LetExpr)(
                   "y", NEW(NumExpr)(3),
                   NEW(AddExpr)(
                       NEW(AddExpr)(
                           NEW(VariableExpr)("y"),
                           NEW(LetExpr)("z", NEW(NumExpr)(10),
                                        NEW(AddExpr)(NEW(VariableExpr)("z"),
                                                     NEW(NumExpr)(5)))),
                       NEW(VariableExpr)("x")))))
              ->interp()
              ->equals(NEW(NumVal)(23)));

    //(PTR(LetExpr) x=5 _in ((PTR(LetExpr) y= (PTR(LetExpr) q = 5 _in q * 10)
    //_in (y + (LetExpr
    // z = 10, _in (z + 5))))+x)) == 70
    CHECK((NEW(LetExpr)(
               "x", NEW(NumExpr)(5),
               NEW(LetExpr)(
                   "y",
                   NEW(LetExpr)("q", NEW(NumExpr)(5),
                                NEW(MultiExpr)(NEW(NumExpr)(10),
                                               NEW(VariableExpr)("q"))),
                   NEW(AddExpr)(
                       NEW(AddExpr)(
                           NEW(VariableExpr)("y"),
                           NEW(LetExpr)("z", NEW(NumExpr)(10),
                                        NEW(AddExpr)(NEW(VariableExpr)("z"),
                                                     NEW(NumExpr)(5)))),
                       NEW(VariableExpr)("x")))))
              ->interp()
              ->equals(NEW(NumVal)(70)));

    // x = 10, y = 10, z = 10. x + y + z = 30
    CHECK(
        (NEW(LetExpr)(
             "x", NEW(NumExpr)(10),
             NEW(LetExpr)(
                 "y", NEW(NumExpr)(10),
                 NEW(LetExpr)("z", NEW(NumExpr)(10),
                              NEW(AddExpr)(NEW(AddExpr)(NEW(VariableExpr)("x"),
                                                        NEW(VariableExpr)("y")),
                                           NEW(VariableExpr)("z"))))))
            ->interp()
            ->equals(NEW(NumVal)(30)));

    CHECK((NEW(LetExpr)(
               "x", NEW(NumExpr)(5),
               NEW(LetExpr)("y", NEW(NumExpr)(3),
                            NEW(AddExpr)(NEW(AddExpr)(NEW(VariableExpr)("y"),
                                                      NEW(NumExpr)(2)),
                                         NEW(VariableExpr)("x")))))
              ->to_string() == "(_let x=5 _in (_let y=3 _in ((y+2)+x)))");

    LetExpr let1 =
        LetExpr("x", NEW(NumExpr)(5),
                NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
                                          NEW(AddExpr)(NEW(VariableExpr)("y"),
                                                       NEW(NumExpr)(2))),
                             NEW(VariableExpr)("x")));
    CHECK(let1.to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
                        NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(5))))
              ->to_string() == "(_let x=5 _in (x+5))");

    //        let1.pretty_print(std::cout);
    CHECK((let1).pretty_print_to_string() ==
          "_let x = 5\n_in  (_let y = 3\n      _in  y + 2) + x");
    PTR(LetExpr)
    test2 = NEW(LetExpr)(
        "x", NEW(NumExpr)(5),
        NEW(AddExpr)(
            NEW(LetExpr)("y", NEW(NumExpr)(3),
                         NEW(AddExpr)(NEW(VariableExpr)("y"), NEW(NumExpr)(2))),
            NEW(VariableExpr)("x")));
    PTR(LetExpr)
    test3 = NEW(LetExpr)(
        "x", NEW(NumExpr)(5),
        NEW(LetExpr)("x", NEW(NumExpr)(6),
                     NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(1))));
    PTR(LetExpr)
    test4 = NEW(LetExpr)(
        "x", NEW(NumExpr)(5),
        NEW(LetExpr)("y", NEW(NumExpr)(6),
                     NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(1))));
    //        PTR(LetExpr)test5 = NEW(LetExpr)("x", NEW(NumExpr)(5),
    //        NEW(LetExpr)("x", NEW(AddExpr)(NEW(VariableExpr)("x"),
    //        NEW(NumExpr)(2)), new AddExpr(NEW(VariableExpr)("x"),
    //        NEW(NumExpr)(1))));
    PTR(LetExpr)
    test5 = NEW(LetExpr)(
        "x", NEW(NumExpr)(5),
        NEW(LetExpr)("x", NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(2)),
                     NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(1))));
    PTR(LetExpr)
    test6 = NEW(LetExpr)(
        "x", NEW(NumExpr)(5),
        NEW(LetExpr)("y", NEW(NumExpr)(6),
                     NEW(LetExpr)("y", NEW(NumExpr)(7),
                                  NEW(AddExpr)(NEW(VariableExpr)("x"),
                                               NEW(NumExpr)(1)))));
    PTR(LetExpr)
    test10 = NEW(LetExpr)(
        "x", NEW(NumExpr)(5),
        NEW(AddExpr)(
            NEW(LetExpr)("y", NEW(NumExpr)(6),
                         NEW(LetExpr)("y", NEW(NumExpr)(7),
                                      NEW(AddExpr)(NEW(VariableExpr)("x"),
                                                   NEW(NumExpr)(1)))),
            NEW(NumExpr)(1)));
    PTR(LetExpr)
    test11 = NEW(LetExpr)(
        "x", NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(2)),
        NEW(AddExpr)(
            NEW(LetExpr)("y", NEW(NumExpr)(6),
                         NEW(LetExpr)("y", NEW(NumExpr)(7),
                                      NEW(AddExpr)(NEW(VariableExpr)("x"),
                                                   NEW(NumExpr)(1)))),
            NEW(NumExpr)(1)));

    PTR(LetExpr)
    letBase1 =
        NEW(LetExpr)("x", NEW(NumExpr)(5),
                     NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(1)));
    PTR(LetExpr)
    letBase2 =
        NEW(LetExpr)("x", NEW(NumExpr)(6),
                     NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(1)));

    CHECK(letBase1->pretty_print_to_string() == "_let x = 5\n_in  x + 1");
    CHECK(letBase2->pretty_print_to_string() == "_let x = 6\n_in  x + 1");
    PTR(LetExpr) let2 = NEW(LetExpr)("x", NEW(NumExpr)(5), letBase2);
    CHECK(let2->pretty_print_to_string() == "_let x = 5\n"
                                            "_in  _let x = 6\n"
                                            "     _in  x + 1");

    PTR(MultiExpr)
    let11 = NEW(MultiExpr)(NEW(NumExpr)(1),
                           NEW(MultiExpr)(NEW(NumExpr)(2), letBase1));

    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
                        NEW(LetExpr)("z", NEW(NumExpr)(4),
                                     NEW(AddExpr)(NEW(VariableExpr)("x"),
                                                  NEW(NumExpr)(10)))))
              ->interp()
              ->equals(NEW(NumVal)(12)));

    CHECK(
        (NEW(LetExpr)(
             "x", NEW(NumExpr)(1),
             NEW(MultiExpr)(
                 NEW(MultiExpr)(NEW(VariableExpr)("x"),
                                NEW(MultiExpr)(NEW(MultiExpr)(NEW(NumExpr)(10),
                                                              NEW(NumExpr)(10)),
                                               NEW(VariableExpr)("x"))),
                 NEW(MultiExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
            ->interp()
            ->equals(NEW(NumVal)(10000)));
    CHECK(let11->pretty_print_to_string() == "1 * 2 * _let x = 5\n"
                                             "        _in  x + 1");
    PTR(AddExpr) let13 = NEW(AddExpr)(let11, NEW(NumExpr)(5));
    CHECK(let13->pretty_print_to_string() == "1 * 2 * (_let x = 5\n"
                                             "         _in  x + 1) + 5");
  }
}

//

// TEST_CASE("Pretty Print examples_Kevin")
//{ // Created from assignment examples
//     std::stringstream out("");
//     (NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VariableExpr)("x"),
//     new NumExpr(1))))->pretty_print(out); CHECK(out.str() == "PTR(LetExpr) x
//     = 5\n"
//                        "_in  x + 1");
//     out.str(std::string());
//     (NEW(AddExpr)(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VariableExpr)("x")),
//     new NumExpr(1)))->pretty_print(out); CHECK(out.str() == "(PTR(LetExpr) x
//     = 5\n"
//                        " _in  x) + 1");
//     out.str(std::string());
//     (NEW(MultiExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5), new
//     AddExpr(NEW(VariableExpr)("x"), NEW(NumExpr)(1)))))->pretty_print(out);
//     CHECK(out.str() == "5 * PTR(LetExpr) x = 5\n"
//                        "    _in  x + 1");
//     out.str(std::string());
//     (NEW(AddExpr)(NEW(MultiExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", new
//     NumExpr(5), NEW(VariableExpr)("x"))),
//     NEW(NumExpr)(1)))->pretty_print(out); CHECK(out.str() == "5 *
//     (PTR(LetExpr) x = 5\n"
//                        "     _in  x) + 1");
//     out.str(std::string());
//     (NEW(LetExpr)("x", NEW(NumExpr)(5),
//               NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
//               NEW(AddExpr)(new VariableExpr("y"), NEW(NumExpr)(2))),
//               NEW(VariableExpr)("x"))))
//         ->pretty_print(out);
//
//     CHECK(out.str() == "PTR(LetExpr) x = 5\n"
//                        "_in  (PTR(LetExpr) y = 3\n"
//                        "      _in  y + 2) + x");
//     out.str(std::string());
//     (NEW(LetExpr)("x", NEW(LetExpr)("y", NEW(NumExpr)(6), NEW(MultiExpr)(new
//     VariableExpr("y"), NEW(NumExpr)(2))),
//               NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(1))))
//         ->pretty_print(out);
//     CHECK(out.str() == "PTR(LetExpr) x = PTR(LetExpr) y = 6\n"
//                        "         _in  y * 2\n"
//                        "_in  x + 1");
// }
//
// TEST_CASE("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let")
//{
//     PTR(LetExpr)tripleNestedLet = NEW(LetExpr)("x", NEW(NumExpr)(1),
//                                      NEW(LetExpr)("y", NEW(NumExpr)(1),
//                                               NEW(MultiExpr)(NEW(AddExpr)(new
//                                               VariableExpr("x"), new
//                                               VariableExpr("y")),
//                                                         new
//                                                         VariableExpr("z"))));
//     PTR(LetExpr)tripleNestedLet2 = NEW(LetExpr)("x", NEW(NumExpr)(1),
//                                       NEW(LetExpr)("y", NEW(NumExpr)(1),
//                                                NEW(LetExpr)("z", new
//                                                AddExpr(NEW(VariableExpr)("x"),
//                                                NEW(NumExpr)(1)),
//                                                         NEW(AddExpr)(new
//                                                         AddExpr(new
//                                                         VariableExpr("x"),
//                                                         new
//                                                         VariableExpr("y")),
//                                                                 new
//                                                                 VariableExpr("z")))));
//     PTR(LetExpr)tripleNestedLet3 = NEW(LetExpr)("x", NEW(NumExpr)(1),
//                                       NEW(LetExpr)("y", NEW(NumExpr)(1),
//                                                NEW(LetExpr)("z", new
//                                                AddExpr(NEW(VariableExpr)("x"),
//                                                NEW(NumExpr)(1)),
//                                                         NEW(MultiExpr)(new
//                                                         AddExpr(new
//                                                         VariableExpr("x"),
//                                                         new
//                                                         VariableExpr("y")),
//                                                                   new
//                                                                   VariableExpr("z")))));
//
//     CHECK(tripleNestedLet->pretty_print_to_string() ==
//           "PTR(LetExpr) x = 1\n"
//           "_in  PTR(LetExpr) y = 1\n"
//           "     _in  (x + y) * z");
//     CHECK(tripleNestedLet2->pretty_print_to_string() ==
//           "PTR(LetExpr) x = 1\n"
//           "_in  PTR(LetExpr) y = 1\n"
//           "     _in  PTR(LetExpr) z = x + 1\n"
//           "          _in  (x + y) + z");
//     CHECK(tripleNestedLet3->pretty_print_to_string() ==
//           "PTR(LetExpr) x = 1\n"
//           "_in  PTR(LetExpr) y = 1\n"
//           "     _in  PTR(LetExpr) z = x + 1\n"
//           "          _in  (x + y) * z");
//     PTR(LetExpr)tripleNestedLet4 = NEW(LetExpr)("x", NEW(NumExpr)(5),
//                                       NEW(LetExpr)("y", NEW(NumExpr)(3),
//                                                NEW(AddExpr)(new
//                                                VariableExpr("y"), new
//                                                NumExpr(2))));
//     PTR(LetExpr)tripleNestedLet5 = NEW(LetExpr)("x", NEW(NumExpr)(5),
//                                       NEW(AddExpr)(NEW(LetExpr)("y", new
//                                       NumExpr(3),
//                                                        NEW(AddExpr)(new
//                                                        VariableExpr("y"), new
//                                                        NumExpr(2))),
//                                               NEW(VariableExpr)("x")));
//     std::stringstream out("");
//     out.str("");
//     tripleNestedLet4->pretty_print(out);
//     CHECK(out.str() ==
//           "PTR(LetExpr) x = 5\n"
//           "_in  PTR(LetExpr) y = 3\n"
//           "     _in  y + 2");
//
//     CHECK(tripleNestedLet5->pretty_print_to_string() == "PTR(LetExpr) x =
//     5\n"
//                                                         "_in  (PTR(LetExpr) y
//                                                         = 3\n" "      _in  y
//                                                         + 2) + x");
//     SECTION("assignment_examples")
//     {
//         CHECK((NEW(AddExpr)(NEW(MultiExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x",
//         new NumExpr(5), NEW(VariableExpr)("x"))),
//                        NEW(NumExpr)(1)))
//                   ->pretty_print_to_string() == "5 * (PTR(LetExpr) x = 5\n"
//                                                 "     _in  x) + 1");
//         CHECK((NEW(MultiExpr)(NEW(MultiExpr)(NEW(NumExpr)(2),
//         NEW(LetExpr)("x", NEW(NumExpr)(5),
//         NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(1)))),
//                          NEW(NumExpr)(3)))
//                   ->pretty_print_to_string() == "(2 * PTR(LetExpr) x = 5\n"
//                                                 "     _in  x + 1) * 3");
//     }
//     // A PTR(LetExpr) needs parentheses when it is nested immediately as the
//     right argument of an unparenthesized *
//     // where PTR(LetExpr) would have needed parentheses in the surrounding
//     context
//     // (that is, if the PTR(LetExpr) used in place of the whole * would need
//     parentheses,
//     // then it still needs parentheses within the right-hand size of *).
//     SECTION("new_edge")
//     {
//         CHECK((NEW(MultiExpr)(NEW(NumExpr)(2),
//                          NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(new
//                          VariableExpr("x"), NEW(NumExpr)(1)))))
//                   ->pretty_print_to_string() == "2 * PTR(LetExpr) x = 5\n"
//                                                 "    _in  x + 1");
//         CHECK((NEW(AddExpr)(NEW(MultiExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x",
//         new NumExpr(5), NEW(MultiExpr)(NEW(VariableExpr)("x"),
//         NEW(NumExpr)(2)))),
//                        NEW(NumExpr)(1)))
//                   ->pretty_print_to_string() == "5 * (PTR(LetExpr) x = 5\n"
//                                                 "     _in  x * 2) + 1");
//         CHECK((NEW(MultiExpr)(
//                    (NEW(AddExpr)(NEW(MultiExpr)(NEW(NumExpr)(5), new
//                    LetExpr("x", NEW(NumExpr)(5), NEW(MultiExpr)(new
//                    VariableExpr("x"), NEW(NumExpr)(2)))),
//                             NEW(NumExpr)(1))),
//                    NEW(NumExpr)(7)))
//                   ->pretty_print_to_string() == "(5 * (PTR(LetExpr) x = 5\n"
//                                                 "      _in  x * 2) + 1) *
//                                                 7");
//         CHECK((NEW(LetExpr)("x", NEW(NumExpr)(10), NEW(MultiExpr)(new
//         MultiExpr(NEW(VariableExpr)("x"), NEW(MultiExpr)(NEW(MultiExpr)(new
//         NumExpr(10), NEW(NumExpr)(10)), NEW(NumExpr)(10))),
//         NEW(MultiExpr)(new NumExpr(10), NEW(NumExpr)(10)))))
//                   ->pretty_print_to_string() == "PTR(LetExpr) x = 10\n"
//                                                 "_in  (x * (10 * 10) * 10) *
//                                                 10 * 10");
//         CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(MultiExpr)(new
//         MultiExpr(NEW(VariableExpr)("x"), NEW(MultiExpr)(NEW(MultiExpr)(new
//         NumExpr(10), NEW(NumExpr)(10)), NEW(VariableExpr)("x"))), new
//         MultiExpr(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
//                   ->pretty_print_to_string() == "PTR(LetExpr) x = 1\n"
//                                                 "_in  (x * (10 * 10) * x) *
//                                                 10 * 10");
//         CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(MultiExpr)(new
//         MultiExpr(NEW(VariableExpr)("x"), NEW(MultiExpr)(NEW(MultiExpr)(new
//         NumExpr(10), NEW(NumExpr)(10)), NEW(VariableExpr)("x"))), new
//         MultiExpr(NEW(VariableExpr)("y"), NEW(NumExpr)(10)))))
//                   ->pretty_print_to_string() == "PTR(LetExpr) x = 1\n"
//                                                 "_in  (x * (10 * 10) * x) * y
//                                                 * 10");
//     }
// }
//
// TEST_CASE("Let_equals_mine")
//{
//     SECTION("Values_same")
//     {
//         REQUIRE((NEW(LetExpr)("x", NEW(NumExpr)(4),
//         NEW(AddExpr)(NEW(NumExpr)(2),
//         NEW(VariableExpr)("x"))))->equals(NEW(LetExpr)("x", NEW(NumExpr)(4),
//         new AddExpr(NEW(NumExpr)(2), NEW(VariableExpr)("x")))));
//     }
//     SECTION("Values_same_different_rhs")
//     {
//         REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(new
//         NumExpr(2), NEW(VariableExpr)("x"))))->equals(NEW(LetExpr)("x", new
//         NumExpr(5), NEW(AddExpr)(NEW(NumExpr)(2), NEW(VariableExpr)("x")))));
//     }
//     SECTION("Values_same_different_lhs")
//     {
//         REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(new
//         NumExpr(2), NEW(VariableExpr)("x"))))->equals(NEW(LetExpr)("y", new
//         NumExpr(4), NEW(AddExpr)(NEW(NumExpr)(2), NEW(VariableExpr)("x")))));
//     }
//     SECTION("Values_same_different_body")
//     {
//         REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(new
//         NumExpr(2), NEW(VariableExpr)("x"))))->equals(NEW(LetExpr)("x", new
//         NumExpr(4), NEW(MultiExpr)(NEW(NumExpr)(3),
//         NEW(VariableExpr)("y")))));
//     }
//     SECTION("different_types")
//     {
//         REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(new
//         NumExpr(2), NEW(VariableExpr)("x"))))->equals(NEW(MultiExpr)(new
//         NumExpr(3), NEW(VariableExpr)("y"))));
//     }
// }
//
// TEST_CASE("Let_has_variable_mine")
//{
//     SECTION("has")
//     {
//         REQUIRE((NEW(LetExpr)("x", NEW(NumExpr)(4),
//         NEW(AddExpr)(NEW(NumExpr)(2),
//         NEW(VariableExpr)("x"))))->hasVariable());
//     }
//     SECTION("does_not_has")
//     {
//         REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(new
//         NumExpr(2), NEW(NumExpr)(4))))->hasVariable());
//     }
// }
//
// TEST_CASE("Let_print_mine")
//{
//     CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(LetExpr)("y",
//     new NumExpr(3), NEW(AddExpr)(NEW(VariableExpr)("y"), NEW(NumExpr)(2))),
//     new VariableExpr("x"))))->to_string() == "(PTR(LetExpr) x=5 _in
//     ((PTR(LetExpr) y=3 _in (y+2))+x))"); CHECK((NEW(LetExpr)("x",
//     NEW(NumExpr)(1),
//                     NEW(LetExpr)("y", NEW(NumExpr)(1),
//                              NEW(LetExpr)("z", NEW(AddExpr)(new
//                              VariableExpr("x"), NEW(NumExpr)(1)),
//                                       NEW(MultiExpr)(NEW(AddExpr)(new
//                                       VariableExpr("x"), new
//                                       VariableExpr("y")),
//                                                 NEW(VariableExpr)("z"))))))
//               ->to_string() == "(PTR(LetExpr) x=1 _in (PTR(LetExpr) y=1 _in
//               (LetExpr z=(x+1) _in ((x+y)*z))))");
// }
//
// TEST_CASE("Let_interp_mine")
//{
//
//     SECTION("hw_examples")
//     {
//         CHECK((NEW(AddExpr)(NEW(MultiExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x",
//         new NumExpr(5), NEW(VariableExpr)("x"))), NEW(NumExpr)(1)))->interp()
//         ==
//               26);
//         CHECK((NEW(MultiExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x",
//         NEW(NumExpr)(5), NEW(AddExpr)(NEW(VariableExpr)("x"),
//         NEW(NumExpr)(1)))))->interp() ==
//               30);
//     }
//     SECTION("from_pretty_print_edge")
//     {
//         CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1),
//                         NEW(LetExpr)("y", NEW(NumExpr)(1),
//                                  NEW(LetExpr)("z", NEW(AddExpr)(new
//                                  VariableExpr("x"), NEW(NumExpr)(1)),
//                                           NEW(MultiExpr)(NEW(AddExpr)(new
//                                           VariableExpr("x"), new
//                                           VariableExpr("y")),
//                                                     new
//                                                     VariableExpr("z"))))))
//                   ->interp() == 4);
//         CHECK((NEW(MultiExpr)(
//                    (NEW(AddExpr)(NEW(MultiExpr)(NEW(NumExpr)(5), new
//                    LetExpr("x", NEW(NumExpr)(5), NEW(MultiExpr)(new
//                    VariableExpr("x"), NEW(NumExpr)(2)))),
//                             NEW(NumExpr)(1))),
//                    NEW(NumExpr)(7)))
//                   ->interp() == 357); // 51 * 7
//         CHECK((NEW(LetExpr)("x", NEW(NumExpr)(10), NEW(MultiExpr)(new
//         MultiExpr(NEW(VariableExpr)("x"), NEW(MultiExpr)(NEW(MultiExpr)(new
//         NumExpr(10), NEW(NumExpr)(10)), NEW(NumExpr)(10))),
//         NEW(MultiExpr)(new NumExpr(10), NEW(NumExpr)(10)))))
//                   ->interp() == 1000000);
//         CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(MultiExpr)(new
//         MultiExpr(NEW(VariableExpr)("x"), NEW(MultiExpr)(NEW(MultiExpr)(new
//         NumExpr(10), NEW(NumExpr)(10)), NEW(VariableExpr)("x"))), new
//         MultiExpr(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
//                   ->interp() == 10000);
//     }
//     SECTION("bypass_middle_let")
//     {
//         CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2), NEW(LetExpr)("z", new
//         NumExpr(4), NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(10)))))
//                   ->interp() == 12);
//     }
// }

TEST_CASE("Parsing string") {
  SECTION("Parsing_Str") {
    CHECK_THROWS_WITH(parse_Str("()"), "Invalid input");
    CHECK(parse_Str("(1)")->equals(NEW(NumExpr)(1)));
    CHECK(parse_Str("(((1)))")->equals(NEW(NumExpr)(1)));

    CHECK_THROWS_WITH(parse_Str("(1"), "Missing close parenthesis");
    CHECK(parse_Str("1")->equals(NEW(NumExpr)(1)));
    CHECK(parse_Str("10")->equals(NEW(NumExpr)(10)));
    CHECK(parse_Str("-3")->equals(NEW(NumExpr)(-3)));
    CHECK(parse_Str("  \n 5  ")->equals(NEW(NumExpr)(5)));
    CHECK_THROWS_WITH(parse_Str("-"), "Invalid input");
    CHECK_THROWS_WITH(parse_Str(" -  5 "), "unexpected input after expression");
    CHECK(parse_Str("x")->equals(NEW(VariableExpr)("x")));
    CHECK(parse_Str("xyz")->equals(NEW(VariableExpr)("xyz")));
    CHECK(parse_Str("xYz")->equals(NEW(VariableExpr)("xYz")));
    CHECK_THROWS_WITH(parse_Str("x_z"), "Invalid input");

    CHECK(parse_Str("x + y")->equals(
        NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(VariableExpr)("y"))));
    CHECK(parse_Str("x * y")->equals(
        NEW(MultiExpr)(NEW(VariableExpr)("x"), NEW(VariableExpr)("y"))));
    CHECK(parse_Str("z * x + y")
              ->equals(NEW(AddExpr)(NEW(MultiExpr)(NEW(VariableExpr)("z"),
                                                   NEW(VariableExpr)("x")),
                                    NEW(VariableExpr)("y"))));

    CHECK(parse_Str("z * (x + y)")
              ->equals(NEW(MultiExpr)(NEW(VariableExpr)("z"),
                                      NEW(AddExpr)(NEW(VariableExpr)("x"),
                                                   NEW(VariableExpr)("y")))));
  }
}

TEST_CASE("NumVal::equals") {
  SECTION("EQUALS") {
    PTR(IfExpr)
    b = NEW(IfExpr)(NEW(BoolExpr)(false), NEW(NumExpr)(9), NEW(NumExpr)(88));
    PTR(IfExpr)
    c = NEW(IfExpr)(NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(5)),
                    NEW(NumExpr)(1), NEW(NumExpr)(77));
    PTR(IfExpr)
    d = NEW(IfExpr)(NEW(AddExpr)(NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
                                 NEW(NumExpr)(5)),
                    NEW(NumExpr)(1), NEW(NumExpr)(77));
    PTR(IfExpr)
    f = NEW(IfExpr)(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
                    NEW(NumExpr)(1), NEW(NumExpr)(77));
    PTR(Expr)
    g = NEW(EqExpr)(NEW(NumExpr)(6),
                    NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(6)));
    PTR(EqExpr) h = NEW(EqExpr)(NEW(NumExpr)(6), NEW(NumExpr)(7));
    CHECK_THROWS_WITH(f->interp(), "It's not equal expression doable");
    //    h->pretty_print(std::cout);

    CHECK((NEW(NumVal)(1))->equals(nullptr) == false);
  }

  SECTION("from quiz") {

    CHECK(
        (parse_Str("_if 1 == 2 _then 5 _else 6"))
            ->equals(NEW(IfExpr)(NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
                                 NEW(NumExpr)(5), NEW(NumExpr)(6))));

    CHECK(
        (((parse_Str("_if 1 == 2 _then 5 _else 6"))->interp())->to_string()) ==
        "6");
    CHECK((((parse_Str("1 == 2"))->interp())->to_string()) == "_false");
    CHECK((((parse_Str("(1 + 2) == (3 + 0)"))->interp())->to_string()) ==
          "_true");
    CHECK((((parse_Str("1 + 2 == 3 + 0"))->interp())->to_string()) == "_true");
    CHECK_THROWS_WITH(
        ((((parse_Str("(1 == 2) + 3 "))->interp())->to_string()) == "_true"),
        "add of non-number");
    CHECK((((parse_Str("1==2+3"))->interp())->to_string()) == "_false");
    CHECK((((parse_Str("_if _false\n"
                       "_then 5\n"
                       "_else 6"))
                ->interp())
               ->to_string()) == "6");
    CHECK((((parse_Str("_if _false\n"
                       "_then _false\n"
                       "_else _true"))
                ->interp())
               ->to_string()) == "_true");
    CHECK((((parse_Str("_if _false\n"
                       "_then 5\n"
                       "_else _false"))
                ->interp())
               ->to_string()) == "_false");
    CHECK_THROWS_WITH(
        ((((parse_Str("_true + _false"))->interp())->to_string()) == "_false"),
        "add of non-number");
    CHECK_THROWS_WITH(
        ((((parse_Str("_true + 1"))->interp())->to_string()) == "_false"),
        "add of non-number");
    CHECK((((parse_Str("_true == _true"))->interp())->to_string()) == "_true");
    CHECK((((parse_Str("1 == _true"))->interp())->to_string()) == "_false");
    CHECK_THROWS_WITH(((((parse_Str("_if 1 + 2\n"
                                    "_then _false\n"
                                    "_else _true"))
                             ->interp())
                            ->to_string()) == "_false"),
                      "It's not equal expression doable");
    CHECK((((parse_Str("_if _true\n"
                       "_then 5\n"
                       "_else _true + 1"))
                ->interp())
               ->to_string()) == "5");
    CHECK_THROWS_WITH(((((parse_Str("_if _false\n"
                                    "_then 5\n"
                                    "_else _true + 1"))
                             ->interp())
                            ->to_string()) == "_false"),
                      "add of non-number");
    CHECK_THROWS_WITH(((((parse_Str("_let x = _true + 1\n"
                                    "_in  _if _true\n"
                                    "     _then 5\n"
                                    "     _else x"))
                             ->interp())
                            ->to_string()) == "_false"),
                      "add of non-number");
    CHECK_THROWS_WITH(((((parse_Str("_let x = _true + 1\n"
                                    "_in  _if _true\n"
                                    "     _then 5\n"
                                    "     _else x"))
                             ->interp())
                            ->to_string()) == "_false"),
                      "add of non-number");
    CHECK((((parse_Str("(_if _true\n"
                       " _then 5\n"
                       " _else _true) + 1"))
                ->interp())
               ->to_string()) == "6");
    CHECK((((parse_Str("_if (_if 1 == 2\n"
                       "     _then _false\n"
                       "     _else _true)\n"
                       "_then 5\n"
                       "_else 6"))
                ->interp())
               ->to_string()) == "5");
    CHECK((((parse_Str("_if (_if 1 == 2\n"
                       "     _then _true\n"
                       "      _else _false)\n"
                       "_then 5\n"
                       "_else 6"))
                ->interp())
               ->to_string()) == "6");
  }
}

TEST_CASE("Functions") {
  SECTION("My test") {
    PTR(CallExpr)
    t = NEW(CallExpr)(NEW(FunExpr)("x", NEW(AddExpr)(NEW(VariableExpr)("x"),
                                                     NEW(NumExpr)(1))),
                      NEW(NumExpr)(10));

    CHECK((t->interp())->equals(NEW(NumVal)(11)));
    PTR(FunExpr)
    t2 = NEW(FunExpr)("x",
                      NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(5)));

    PTR(FunVal) e = NEW(FunVal)("x", NEW(NumExpr)(6));

    //    "_let f = _fun (x) x + 1 \n"
    //    "_in _let g = _fun (x)\n"
    //    "              f(2) + x\n"
    //    "_in g(5) "
    PTR(LetExpr)
    l = NEW(LetExpr)(
        "f",
        NEW(FunExpr)("x",
                     NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(1))),
        NEW(LetExpr)(
            "g",
            NEW(FunExpr)("x", NEW(AddExpr)(NEW(CallExpr)(NEW(VariableExpr)("f"),
                                                         NEW(NumExpr)(2)),
                                           NEW(VariableExpr)("x"))),
            NEW(CallExpr)(NEW(VariableExpr)("g"), NEW(NumExpr)(5))));

    PTR(LetExpr)
    l2 = NEW(LetExpr)("f",
                      NEW(FunExpr)("x", NEW(AddExpr)(NEW(VariableExpr)("x"),
                                                     NEW(NumExpr)(1))),
                      NEW(CallExpr)(NEW(VariableExpr)("f"), NEW(NumExpr)(2)));
    //    l->print(std::cout);
    //    l->interp()->print(std::cout);

    //    l->print(std::cout);
    //    l->interp()->print(std::cout);
  }

  SECTION("From quiz") {
    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in f(5) ")
                ->interp()
                ->equals(NEW(NumVal)(6)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           7\n"
                      "_in f(5)")
                ->interp()
                ->equals(NEW(NumVal)(7)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           _true\n"
                      "_in f(5) ")
                ->interp()
                ->equals(NEW(BoolVal)(true)));

    REQUIRE_THROWS_WITH(parse_Str("_let f = _fun (x)\n"
                                  "           x + _true\n"
                                  "_in f(5) ")
                            ->interp(),
                        "AddExpr of non-number");

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           x + _true\n"
                      "_in 5 + 1 ")
                ->interp()
                ->equals(NEW(NumVal)(6)));

    REQUIRE_THROWS_WITH(parse_Str("_let f = _fun (x)\n"
                                  "           7\n"
                                  "_in  f(5 + _true)")
                            ->interp(),
                        "AddExpr of non-number");
    REQUIRE_THROWS_WITH(parse_Str("_let f = _fun (x) x+ 1\n"
                                  "_in f + 5")
                            ->interp(),
                        "[ERROR] Cannot not add_to");

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in _if _false\n"
                      "    _then f(5)\n"
                      "    _else f(6)")
                ->interp()
                ->equals(NEW(NumVal)(7)));

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in _let g = _fun (y) y+ 2 \n"
                      "_in _if _true\n"
                      "    _then f(5)\n"
                      "    _else g(5)")
                ->interp()
                ->equals(NEW(NumVal)(6)));

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in _let g = _fun (y) y+ 2 \n"
                      "_in f(g(5)) ")
                ->interp()
                ->equals(NEW(NumVal)(8)));

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in _let g = _fun (y)\n"
                      "              f(y + 2)\n"
                      "_in g(5) ")
                ->interp()
                ->equals(NEW(NumVal)(8)));

    REQUIRE(parse_Str("_let f = _fun (x) x + 1 \n"
                      "_in _let g = _fun (x)\n"
                      "              f(2) + x\n"
                      "_in g(5) ")
                ->interp()
                ->equals(NEW(NumVal)(8)));

    REQUIRE_THROWS_WITH(parse_Str("_let f = _fun (x) x+ 1 \n"
                                  "_in f 5 ")
                            ->interp(),
                        "[ERROR] : Invalid input");

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in (f)(5) ")
                ->interp()
                ->equals(NEW(NumVal)(6)));

    auto add_x_1 = NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumExpr)(1));
    auto fun_val_x_add_x_1 = NEW(FunVal)("x", add_x_1);
    //    REQUIRE(parse_Str("_fun (x) x+
    //    1")->interp()->equals(fun_val_x_add_x_1));

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in f ")
                ->interp()
                ->equals(fun_val_x_add_x_1));

    REQUIRE(parse_Str("(_fun (x)\n"
                      "   x + 1)(5)")
                ->interp()
                ->equals(NEW(NumVal)(6)));

    REQUIRE(parse_Str("_let f = _if _false\n"
                      "            _then _fun (x)  \n"
                      "                        x+ 1 \n"
                      "           _else _fun (x)\n"
                      "                       x+ 2\n"
                      "_in f(5)")
                ->interp()
                ->equals(NEW(NumVal)(7)));

    REQUIRE(parse_Str("(_if _false \n"
                      "  _then _fun (x)\n"
                      "            x+ 1\n"
                      "   _else _fun (x)\n"
                      "                x + 2)(5)")
                ->interp()
                ->equals(NEW(NumVal)(7)));

    REQUIRE(parse_Str("_let f = _fun (g)\n"
                      "           g(5)\n"
                      "_in _let g = _fun (y)  \n"
                      "             y + 2\n"
                      "_in f(g) ")
                ->interp()
                ->equals(NEW(NumVal)(7)));

    REQUIRE(parse_Str("_let f = _fun (g)\n"
                      "           g(5)\n"
                      "_in f(_fun (y)\n"
                      "        y + 2)")
                ->interp()
                ->equals(NEW(NumVal)(7)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           _fun (y)\n"
                      "x+ y _in (f(5))(1) ")
                ->interp()
                ->equals(NEW(NumVal)(6)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           _fun (y)\n"
                      "x+ y _in f(5)(1) ")
                ->interp()
                ->equals(NEW(NumVal)(6)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           _fun (g)\n"
                      "             g(x + 1)\n"
                      "_in _let g = _fun (y)\n"
                      "              y+ 2 \n"
                      "_in (f(5))(g) ")
                ->interp()
                ->equals(NEW(NumVal)(8)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           _fun (g)\n"
                      "             g(x + 1)\n"
                      "_in _let g = _fun (y)\n"
                      "y+ 2 _in f(5)(g)")
                ->interp()
                ->equals(NEW(NumVal)(8)));

    CHECK((parse_Str("_let factrl = _fun (factrl)\n"
                     "                _fun (x)\n"
                     "                  _if x == 1\n"
                     "                  _then 1\n"
                     "                  _else x * factrl(factrl)(x + -1)\n"
                     "_in  factrl(factrl)(10)"))
              ->interp()
              ->equals(NEW(NumVal)(3628800)));

    REQUIRE(parse_Str("_let f = _fun (f)\n"
                      "           _fun (x)\n"
                      "             _if x == 0\n"
                      "             _then 0\n"
                      "             _else x + f(f)(x + -1)\n"
                      "_in f(f)(3)")
                ->interp()
                ->equals(NEW(NumVal)(6)));
  }
}

#endif // CS6015_TEST_H
