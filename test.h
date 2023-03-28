//
// Created by Howard Tung on 3/13/23.
//

#ifndef CS6015_TEST_H
#define CS6015_TEST_H

#include "Expr.hpp"
#include "catch.h"
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
  AddExpr *add = new AddExpr(new NumExpr(2), new NumExpr(3));
  AddExpr *add2 = new AddExpr(new NumExpr(2), new NumExpr(3));
  AddExpr *add3 = new AddExpr(new NumExpr(2), new NumExpr(4));
  MultiExpr *mav = new MultiExpr(
      new NumExpr(6), new AddExpr(new NumExpr(6), new VariableExpr("Hello")));
  MultiExpr *mav2 = new MultiExpr(
      new NumExpr(6), new AddExpr(new NumExpr(6), new VariableExpr("Hello")));
  MultiExpr *mav3 = new MultiExpr(
      new NumExpr(6), new AddExpr(new NumExpr(6), new VariableExpr("World")));
  SECTION("Equals") {
    CHECK((new NumExpr(1))->equals(new NumExpr(1)) == true);
    CHECK((new VariableExpr("x"))->equals(new VariableExpr("y")) == false);
    CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))
              ->equals(new AddExpr(new NumExpr(2), new NumExpr(3))) == true);
    CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))
              ->equals(new AddExpr(new NumExpr(3), new NumExpr(2))) == false);
    CHECK((new MultiExpr(new NumExpr(2), new NumExpr(2)))
              ->equals(new AddExpr(new NumExpr(1), new NumExpr(2))) == false);
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
    CHECK((new MultiExpr(new NumExpr(3), new NumExpr(2)))
              ->interp()
              ->equals(new NumVal(6)));
    // 3 + 2
    CHECK((new AddExpr(new NumExpr(3), new NumExpr(2)))
              ->interp()
              ->equals(new NumVal(5)));

    CHECK((new AddExpr(new MultiExpr(new NumExpr(2), new NumExpr(3)),
                       new NumExpr(4)))
              ->interp()
              ->equals(new NumVal(10)));
    // 2 * (3 * 4)
    CHECK((new MultiExpr(new NumExpr(2),
                         new MultiExpr(new NumExpr(3), new NumExpr(4))))
              ->interp()
              ->equals(new NumVal(24)));

    //(5*5) * 2
    CHECK((new MultiExpr(new MultiExpr(new NumExpr(5), new NumExpr(5)),
                         new NumExpr(2)))
              ->interp()
              ->equals(new NumVal(50)));

    //(2 * 3) * (2 * 3)
    CHECK((new MultiExpr(new MultiExpr(new NumExpr(2), new NumExpr(3)),
                         new MultiExpr(new NumExpr(2), new NumExpr(3))))
              ->interp()
              ->equals(new NumVal(36)));

    //(2 + (3 * 4))
    CHECK((new AddExpr(new NumExpr(2),
                       new MultiExpr(new NumExpr(3), new NumExpr(4))))
              ->interp()
              ->equals(new NumVal(14)));

    //(10+15) + (20 + 20))
    CHECK((new AddExpr(new AddExpr(new NumExpr(10), new NumExpr(15)),
                       new AddExpr(new NumExpr(20), new NumExpr(20))))
              ->interp()
              ->equals(new NumVal(65)));

    //(10*10) * (30+15)
    CHECK((new MultiExpr(new MultiExpr(new NumExpr(10), new NumExpr(10)),
                         new AddExpr(new NumExpr(30), new NumExpr(15))))
              ->interp()
              ->equals(new NumVal(4500)));

    // (10 + 10) + (20+ 20) * (30 + 30) + (40 * 40)
    CHECK((new MultiExpr(
               new AddExpr(new AddExpr(new NumExpr(10), new NumExpr(10)),
                           new AddExpr(new NumExpr(20), new NumExpr(20))),
               new AddExpr(new AddExpr(new NumExpr(30), new NumExpr(30)),
                           new MultiExpr(new NumExpr(40), new NumExpr(40)))))
              ->interp()
              ->equals(new NumVal(99600)));
  }
  //    SECTION("HasVariable check")
  //    {
  //        CHECK((new MultiExpr(new VariableExpr("x"), new
  //        NumExpr(2)))->hasVariable() == true); CHECK((new
  //        VariableExpr("q"))->hasVariable() == true); CHECK((new
  //        NumExpr(6))->hasVariable() == false); CHECK((new AddExpr(new
  //        VariableExpr("d"), new NumExpr(4)))->hasVariable() == true);
  //    }

  SECTION("Subst check") {
    CHECK((new AddExpr(new VariableExpr("x"), new NumExpr(7)))
              ->subst("x", new VariableExpr("y"))
              ->equals(new AddExpr(new VariableExpr("y"), new NumExpr(7))));

    CHECK((new AddExpr(new NumExpr(7), new VariableExpr("x")))
              ->subst("x", new VariableExpr("y"))
              ->equals(new AddExpr(new NumExpr(7), new VariableExpr("y"))));

    CHECK((new AddExpr(new VariableExpr("x"), new VariableExpr("x")))
              ->subst("x", new VariableExpr("y"))
              ->equals(
                  new AddExpr(new VariableExpr("y"), new VariableExpr("y"))));

    CHECK((new MultiExpr(new VariableExpr("x"), new NumExpr(7)))
              ->subst("x", new VariableExpr("y"))
              ->equals(new MultiExpr(new VariableExpr("y"), new NumExpr(7))));

    CHECK((new MultiExpr(new NumExpr(7), new VariableExpr("x")))
              ->subst("x", new VariableExpr("y"))
              ->equals(new MultiExpr(new NumExpr(7), new VariableExpr("y"))));

    CHECK((new MultiExpr(new VariableExpr("x"), new VariableExpr("x")))
              ->subst("x", new VariableExpr("y"))
              ->equals(
                  new MultiExpr(new VariableExpr("y"), new VariableExpr("y"))));

    CHECK(
        (new NumExpr(2))->subst("x", new NumExpr(3))->equals(new NumExpr(3)) ==
        false);

    CHECK((new VariableExpr("x"))
              ->subst("x", new AddExpr(new VariableExpr("y"), new NumExpr(7)))
              ->equals(new AddExpr(new VariableExpr("y"), new NumExpr(7))));

    CHECK((new AddExpr((new MultiExpr(new NumExpr(10), new VariableExpr("x"))),
                       new NumExpr(7)))
              ->subst("x", new VariableExpr("y"))
              ->equals((new AddExpr(
                  (new MultiExpr(new NumExpr(10), new VariableExpr("y"))),
                  new NumExpr(7)))));
  }

  SECTION("Check Print") {
    CHECK((new AddExpr(new NumExpr(1),
                       new AddExpr(new NumExpr(2), new NumExpr(3))))
              ->to_string() == "(1+(2+3))");
    CHECK((new AddExpr(new AddExpr(new NumExpr(1), new NumExpr(2)),
                       new NumExpr(3)))
              ->to_string() == "((1+2)+3)");
    CHECK((new NumExpr(10))->to_string() == "10");
    CHECK((new VariableExpr("x"))->to_string() == "x");
    CHECK((new AddExpr(new NumExpr(5), new NumExpr(5)))->to_string() ==
          "(5+5)");
    CHECK((new MultiExpr(new NumExpr(10), new NumExpr(10)))->to_string() ==
          "(10*10)");
    CHECK((new AddExpr(new NumExpr(5),
                       new MultiExpr(new NumExpr(5), new NumExpr(5))))
              ->to_string() == "(5+(5*5))");

    CHECK((new MultiExpr(new MultiExpr(new NumExpr(2), new NumExpr(3)),
                         new NumExpr(4)))
              ->pretty_print_to_string() == "(2 * 3) * 4");
    CHECK((new AddExpr(new NumExpr(1),
                       new MultiExpr(new NumExpr(2), new NumExpr(3))))
              ->pretty_print_to_string() == "1 + 2 * 3");
    CHECK((new AddExpr(new NumExpr(1),
                       new AddExpr(new NumExpr(2), new NumExpr(3))))
              ->pretty_print_to_string() == "1 + 2 + 3");
    CHECK((new MultiExpr(new NumExpr(2),
                         new MultiExpr(new NumExpr(3), new NumExpr(4))))
              ->pretty_print_to_string() == "2 * 3 * 4");
    CHECK((new MultiExpr(new NumExpr(1),
                         new AddExpr(new NumExpr(2), new NumExpr(3))))
              ->pretty_print_to_string() == "1 * (2 + 3)");
    CHECK((new MultiExpr(new NumExpr(-8),
                         new AddExpr(new NumExpr(2), new NumExpr(3))))
              ->pretty_print_to_string() == "-8 * (2 + 3)");
    CHECK(
        (new AddExpr(new MultiExpr(new NumExpr(9),
                                   new AddExpr(new NumExpr(4), new NumExpr(3))),
                     new AddExpr(new MultiExpr(new NumExpr(2), new NumExpr(4)),
                                 new NumExpr(1))))
            ->pretty_print_to_string() == "9 * (4 + 3) + 2 * 4 + 1");
    CHECK((new MultiExpr(
               new MultiExpr(new NumExpr(10),
                             new MultiExpr(new MultiExpr(new NumExpr(10),
                                                         new NumExpr(10)),
                                           new NumExpr(10))),
               new MultiExpr(new NumExpr(10), new NumExpr(10))))
              ->pretty_print_to_string() == "(10 * (10 * 10) * 10) * 10 * 10");
    CHECK((new AddExpr(new NumExpr(1),
                       new AddExpr(new NumExpr(2), new NumExpr(5))))
              ->pretty_print_to_string() == "1 + 2 + 5");
    //(2 + 3) * 5
    CHECK((new MultiExpr(new AddExpr(new NumExpr(2), new NumExpr(3)),
                         new NumExpr(5)))
              ->pretty_print_to_string() == "(2 + 3) * 5");
  }

  SECTION("Check LetExpr") {
    CHECK((new LetExpr("x", new NumExpr(5), new NumExpr(5)))
              ->equals(new LetExpr("x", new NumExpr(5), new NumExpr(5))) ==
          true);
    CHECK((new LetExpr("x", new NumExpr(5),
                       new AddExpr(new VariableExpr("x"), new NumExpr(5))))
              ->interp()
              ->equals(new NumVal(10)));
    CHECK((new LetExpr("x", new NumExpr(5),
                       new AddExpr(new NumExpr(10), new NumExpr(5))))
              ->interp()
              ->equals(new NumVal(15)));
    CHECK((new LetExpr("x", new MultiExpr(new NumExpr(7), new NumExpr(3)),
                       new AddExpr(new VariableExpr("x"), new NumExpr(5))))
              ->interp()
              ->equals(new NumVal(26)));
    CHECK((new LetExpr(
               "x", new NumExpr(5),
               new LetExpr("x",
                           new AddExpr(new VariableExpr("x"), new NumExpr(2)),
                           new AddExpr(new VariableExpr("x"), new NumExpr(1)))))
              ->interp()
              ->equals(new NumVal(8)));
    CHECK((new LetExpr(
               "x", new NumExpr(5),
               new LetExpr("x", new NumExpr(6),
                           new AddExpr(new VariableExpr("x"), new NumExpr(1)))))
              ->interp()
              ->equals(new NumVal(7)));
    CHECK((new LetExpr(
               "x", new NumExpr(5),
               new LetExpr("y", new NumExpr(6),
                           new AddExpr(new VariableExpr("x"), new NumExpr(1)))))
              ->interp()
              ->equals(new NumVal(6)));
    CHECK(
        (new LetExpr("x", new NumExpr(5),
                     new LetExpr("y", new NumExpr(3),
                                 new AddExpr(new AddExpr(new VariableExpr("y"),
                                                         new NumExpr(2)),
                                             new VariableExpr("x")))))
            ->interp()
            ->equals(new NumVal(10)));

    //        (LetExpr x=5 _in ((LetExpr y=3 _in (y + (LetExpr z = 10, _in (z +
    //        5))))+x)) ==23
    CHECK(
        (new LetExpr(
             "x", new NumExpr(5),
             new LetExpr(
                 "y", new NumExpr(3),
                 new AddExpr(
                     new AddExpr(new VariableExpr("y"),
                                 new LetExpr("z", new NumExpr(10),
                                             new AddExpr(new VariableExpr("z"),
                                                         new NumExpr(5)))),
                     new VariableExpr("x")))))
            ->interp()
            ->equals(new NumVal(23)));

    //(LetExpr x=5 _in ((LetExpr y= (LetExpr q = 5 _in q * 10) _in (y + (LetExpr
    // z = 10, _in (z + 5))))+x)) == 70
    CHECK(
        (new LetExpr(
             "x", new NumExpr(5),
             new LetExpr(
                 "y",
                 new LetExpr(
                     "q", new NumExpr(5),
                     new MultiExpr(new NumExpr(10), new VariableExpr("q"))),
                 new AddExpr(
                     new AddExpr(new VariableExpr("y"),
                                 new LetExpr("z", new NumExpr(10),
                                             new AddExpr(new VariableExpr("z"),
                                                         new NumExpr(5)))),
                     new VariableExpr("x")))))
            ->interp()
            ->equals(new NumVal(70)));

    // x = 10, y = 10, z = 10. x + y + z = 30
    CHECK((new LetExpr(
               "x", new NumExpr(10),
               new LetExpr(
                   "y", new NumExpr(10),
                   new LetExpr("z", new NumExpr(10),
                               new AddExpr(new AddExpr(new VariableExpr("x"),
                                                       new VariableExpr("y")),
                                           new VariableExpr("z"))))))
              ->interp()
              ->equals(new NumVal(30)));

    CHECK(
        (new LetExpr("x", new NumExpr(5),
                     new LetExpr("y", new NumExpr(3),
                                 new AddExpr(new AddExpr(new VariableExpr("y"),
                                                         new NumExpr(2)),
                                             new VariableExpr("x")))))
            ->to_string() == "(_let x=5 _in (_let y=3 _in ((y+2)+x)))");

    LetExpr let1("x", new NumExpr(5),
                 new AddExpr(new LetExpr("y", new NumExpr(3),
                                         new AddExpr(new VariableExpr("y"),
                                                     new NumExpr(2))),
                             new VariableExpr("x")));
    CHECK(let1.to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
    CHECK((new LetExpr("x", new NumExpr(5),
                       new AddExpr(new VariableExpr("x"), new NumExpr(5))))
              ->to_string() == "(_let x=5 _in (x+5))");

    //        let1.pretty_print(std::cout);
    CHECK((let1).pretty_print_to_string() ==
          "_let x = 5\n_in  (_let y = 3\n      _in  y + 2) + x");
    LetExpr *test2 =
        new LetExpr("x", new NumExpr(5),
                    new AddExpr(new LetExpr("y", new NumExpr(3),
                                            new AddExpr(new VariableExpr("y"),
                                                        new NumExpr(2))),
                                new VariableExpr("x")));
    LetExpr *test3 = new LetExpr(
        "x", new NumExpr(5),
        new LetExpr("x", new NumExpr(6),
                    new AddExpr(new VariableExpr("x"), new NumExpr(1))));
    LetExpr *test4 = new LetExpr(
        "x", new NumExpr(5),
        new LetExpr("y", new NumExpr(6),
                    new AddExpr(new VariableExpr("x"), new NumExpr(1))));
    //        LetExpr *test5 = new LetExpr("x", new NumExpr(5), new LetExpr("x",
    //        new AddExpr(new VariableExpr("x"), new NumExpr(2)), new
    //        AddExpr(new VariableExpr("x"), new NumExpr(1))));
    LetExpr *test5 = new LetExpr(
        "x", new NumExpr(5),
        new LetExpr("x", new AddExpr(new VariableExpr("x"), new NumExpr(2)),
                    new AddExpr(new VariableExpr("x"), new NumExpr(1))));
    LetExpr *test6 =
        new LetExpr("x", new NumExpr(5),
                    new LetExpr("y", new NumExpr(6),
                                new LetExpr("y", new NumExpr(7),
                                            new AddExpr(new VariableExpr("x"),
                                                        new NumExpr(1)))));
    LetExpr *test10 = new LetExpr(
        "x", new NumExpr(5),
        new AddExpr(new LetExpr("y", new NumExpr(6),
                                new LetExpr("y", new NumExpr(7),
                                            new AddExpr(new VariableExpr("x"),
                                                        new NumExpr(1)))),
                    new NumExpr(1)));
    LetExpr *test11 = new LetExpr(
        "x", new AddExpr(new VariableExpr("x"), new NumExpr(2)),
        new AddExpr(new LetExpr("y", new NumExpr(6),
                                new LetExpr("y", new NumExpr(7),
                                            new AddExpr(new VariableExpr("x"),
                                                        new NumExpr(1)))),
                    new NumExpr(1)));

    LetExpr letBase1("x", new NumExpr(5),
                     new AddExpr(new VariableExpr("x"), new NumExpr(1)));
    LetExpr letBase2("x", new NumExpr(6),
                     new AddExpr(new VariableExpr("x"), new NumExpr(1)));

    CHECK(letBase1.pretty_print_to_string() == "_let x = 5\n_in  x + 1");
    CHECK(letBase2.pretty_print_to_string() == "_let x = 6\n_in  x + 1");
    LetExpr let2("x", new NumExpr(5), &letBase2);
    CHECK(let2.pretty_print_to_string() == "_let x = 5\n"
                                           "_in  _let x = 6\n"
                                           "     _in  x + 1");

    MultiExpr let11(new NumExpr(1), new MultiExpr(new NumExpr(2), &letBase1));

    CHECK((new LetExpr("x", new NumExpr(2),
                       new LetExpr("z", new NumExpr(4),
                                   new AddExpr(new VariableExpr("x"),
                                               new NumExpr(10)))))
              ->interp()
              ->equals(new NumVal(12)));

    CHECK((new LetExpr(
               "x", new NumExpr(1),
               new MultiExpr(
                   new MultiExpr(new VariableExpr("x"),
                                 new MultiExpr(new MultiExpr(new NumExpr(10),
                                                             new NumExpr(10)),
                                               new VariableExpr("x"))),
                   new MultiExpr(new NumExpr(10), new NumExpr(10)))))
              ->interp()
              ->equals(new NumVal(10000)));
    CHECK(let11.pretty_print_to_string() == "1 * 2 * _let x = 5\n"
                                            "        _in  x + 1");
    AddExpr let13(&let11, new NumExpr(5));
    CHECK(let13.pretty_print_to_string() == "1 * 2 * (_let x = 5\n"
                                            "         _in  x + 1) + 5");
  }
}

//

// TEST_CASE("Pretty Print examples_Kevin")
//{ // Created from assignment examples
//     std::stringstream out("");
//     (new LetExpr("x", new NumExpr(5), new AddExpr(new VariableExpr("x"), new
//     NumExpr(1))))->pretty_print(out); CHECK(out.str() == "LetExpr x = 5\n"
//                        "_in  x + 1");
//     out.str(std::string());
//     (new AddExpr(new LetExpr("x", new NumExpr(5), new VariableExpr("x")), new
//     NumExpr(1)))->pretty_print(out); CHECK(out.str() == "(LetExpr x = 5\n"
//                        " _in  x) + 1");
//     out.str(std::string());
//     (new MultiExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new
//     AddExpr(new VariableExpr("x"), new NumExpr(1)))))->pretty_print(out);
//     CHECK(out.str() == "5 * LetExpr x = 5\n"
//                        "    _in  x + 1");
//     out.str(std::string());
//     (new AddExpr(new MultiExpr(new NumExpr(5), new LetExpr("x", new
//     NumExpr(5), new VariableExpr("x"))), new NumExpr(1)))->pretty_print(out);
//     CHECK(out.str() == "5 * (LetExpr x = 5\n"
//                        "     _in  x) + 1");
//     out.str(std::string());
//     (new LetExpr("x", new NumExpr(5),
//               new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new
//               VariableExpr("y"), new NumExpr(2))), new VariableExpr("x"))))
//         ->pretty_print(out);
//
//     CHECK(out.str() == "LetExpr x = 5\n"
//                        "_in  (LetExpr y = 3\n"
//                        "      _in  y + 2) + x");
//     out.str(std::string());
//     (new LetExpr("x", new LetExpr("y", new NumExpr(6), new MultiExpr(new
//     VariableExpr("y"), new NumExpr(2))),
//               new AddExpr(new VariableExpr("x"), new NumExpr(1))))
//         ->pretty_print(out);
//     CHECK(out.str() == "LetExpr x = LetExpr y = 6\n"
//                        "         _in  y * 2\n"
//                        "_in  x + 1");
// }
//
// TEST_CASE("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let")
//{
//     LetExpr *tripleNestedLet = new LetExpr("x", new NumExpr(1),
//                                      new LetExpr("y", new NumExpr(1),
//                                               new MultiExpr(new AddExpr(new
//                                               VariableExpr("x"), new
//                                               VariableExpr("y")),
//                                                         new
//                                                         VariableExpr("z"))));
//     LetExpr *tripleNestedLet2 = new LetExpr("x", new NumExpr(1),
//                                       new LetExpr("y", new NumExpr(1),
//                                                new LetExpr("z", new
//                                                AddExpr(new VariableExpr("x"),
//                                                new NumExpr(1)),
//                                                         new AddExpr(new
//                                                         AddExpr(new
//                                                         VariableExpr("x"),
//                                                         new
//                                                         VariableExpr("y")),
//                                                                 new
//                                                                 VariableExpr("z")))));
//     LetExpr *tripleNestedLet3 = new LetExpr("x", new NumExpr(1),
//                                       new LetExpr("y", new NumExpr(1),
//                                                new LetExpr("z", new
//                                                AddExpr(new VariableExpr("x"),
//                                                new NumExpr(1)),
//                                                         new MultiExpr(new
//                                                         AddExpr(new
//                                                         VariableExpr("x"),
//                                                         new
//                                                         VariableExpr("y")),
//                                                                   new
//                                                                   VariableExpr("z")))));
//
//     CHECK(tripleNestedLet->pretty_print_to_string() ==
//           "LetExpr x = 1\n"
//           "_in  LetExpr y = 1\n"
//           "     _in  (x + y) * z");
//     CHECK(tripleNestedLet2->pretty_print_to_string() ==
//           "LetExpr x = 1\n"
//           "_in  LetExpr y = 1\n"
//           "     _in  LetExpr z = x + 1\n"
//           "          _in  (x + y) + z");
//     CHECK(tripleNestedLet3->pretty_print_to_string() ==
//           "LetExpr x = 1\n"
//           "_in  LetExpr y = 1\n"
//           "     _in  LetExpr z = x + 1\n"
//           "          _in  (x + y) * z");
//     LetExpr *tripleNestedLet4 = new LetExpr("x", new NumExpr(5),
//                                       new LetExpr("y", new NumExpr(3),
//                                                new AddExpr(new
//                                                VariableExpr("y"), new
//                                                NumExpr(2))));
//     LetExpr *tripleNestedLet5 = new LetExpr("x", new NumExpr(5),
//                                       new AddExpr(new LetExpr("y", new
//                                       NumExpr(3),
//                                                        new AddExpr(new
//                                                        VariableExpr("y"), new
//                                                        NumExpr(2))),
//                                               new VariableExpr("x")));
//     std::stringstream out("");
//     out.str("");
//     tripleNestedLet4->pretty_print(out);
//     CHECK(out.str() ==
//           "LetExpr x = 5\n"
//           "_in  LetExpr y = 3\n"
//           "     _in  y + 2");
//
//     CHECK(tripleNestedLet5->pretty_print_to_string() == "LetExpr x = 5\n"
//                                                         "_in  (LetExpr y =
//                                                         3\n" "      _in  y +
//                                                         2) + x");
//     SECTION("assignment_examples")
//     {
//         CHECK((new AddExpr(new MultiExpr(new NumExpr(5), new LetExpr("x", new
//         NumExpr(5), new VariableExpr("x"))),
//                        new NumExpr(1)))
//                   ->pretty_print_to_string() == "5 * (LetExpr x = 5\n"
//                                                 "     _in  x) + 1");
//         CHECK((new MultiExpr(new MultiExpr(new NumExpr(2), new LetExpr("x",
//         new NumExpr(5), new AddExpr(new VariableExpr("x"), new NumExpr(1)))),
//                          new NumExpr(3)))
//                   ->pretty_print_to_string() == "(2 * LetExpr x = 5\n"
//                                                 "     _in  x + 1) * 3");
//     }
//     // A LetExpr needs parentheses when it is nested immediately as the right
//     argument of an unparenthesized *
//     // where LetExpr would have needed parentheses in the surrounding context
//     // (that is, if the LetExpr used in place of the whole * would need
//     parentheses,
//     // then it still needs parentheses within the right-hand size of *).
//     SECTION("new_edge")
//     {
//         CHECK((new MultiExpr(new NumExpr(2),
//                          new LetExpr("x", new NumExpr(5), new AddExpr(new
//                          VariableExpr("x"), new NumExpr(1)))))
//                   ->pretty_print_to_string() == "2 * LetExpr x = 5\n"
//                                                 "    _in  x + 1");
//         CHECK((new AddExpr(new MultiExpr(new NumExpr(5), new LetExpr("x", new
//         NumExpr(5), new MultiExpr(new VariableExpr("x"), new NumExpr(2)))),
//                        new NumExpr(1)))
//                   ->pretty_print_to_string() == "5 * (LetExpr x = 5\n"
//                                                 "     _in  x * 2) + 1");
//         CHECK((new MultiExpr(
//                    (new AddExpr(new MultiExpr(new NumExpr(5), new
//                    LetExpr("x", new NumExpr(5), new MultiExpr(new
//                    VariableExpr("x"), new NumExpr(2)))),
//                             new NumExpr(1))),
//                    new NumExpr(7)))
//                   ->pretty_print_to_string() == "(5 * (LetExpr x = 5\n"
//                                                 "      _in  x * 2) + 1) *
//                                                 7");
//         CHECK((new LetExpr("x", new NumExpr(10), new MultiExpr(new
//         MultiExpr(new VariableExpr("x"), new MultiExpr(new MultiExpr(new
//         NumExpr(10), new NumExpr(10)), new NumExpr(10))), new MultiExpr(new
//         NumExpr(10), new NumExpr(10)))))
//                   ->pretty_print_to_string() == "LetExpr x = 10\n"
//                                                 "_in  (x * (10 * 10) * 10) *
//                                                 10 * 10");
//         CHECK((new LetExpr("x", new NumExpr(1), new MultiExpr(new
//         MultiExpr(new VariableExpr("x"), new MultiExpr(new MultiExpr(new
//         NumExpr(10), new NumExpr(10)), new VariableExpr("x"))), new
//         MultiExpr(new NumExpr(10), new NumExpr(10)))))
//                   ->pretty_print_to_string() == "LetExpr x = 1\n"
//                                                 "_in  (x * (10 * 10) * x) *
//                                                 10 * 10");
//         CHECK((new LetExpr("x", new NumExpr(1), new MultiExpr(new
//         MultiExpr(new VariableExpr("x"), new MultiExpr(new MultiExpr(new
//         NumExpr(10), new NumExpr(10)), new VariableExpr("x"))), new
//         MultiExpr(new VariableExpr("y"), new NumExpr(10)))))
//                   ->pretty_print_to_string() == "LetExpr x = 1\n"
//                                                 "_in  (x * (10 * 10) * x) * y
//                                                 * 10");
//     }
// }
//
// TEST_CASE("Let_equals_mine")
//{
//     SECTION("Values_same")
//     {
//         REQUIRE((new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2),
//         new VariableExpr("x"))))->equals(new LetExpr("x", new NumExpr(4), new
//         AddExpr(new NumExpr(2), new VariableExpr("x")))));
//     }
//     SECTION("Values_same_different_rhs")
//     {
//         REQUIRE(!(new LetExpr("x", new NumExpr(4), new AddExpr(new
//         NumExpr(2), new VariableExpr("x"))))->equals(new LetExpr("x", new
//         NumExpr(5), new AddExpr(new NumExpr(2), new VariableExpr("x")))));
//     }
//     SECTION("Values_same_different_lhs")
//     {
//         REQUIRE(!(new LetExpr("x", new NumExpr(4), new AddExpr(new
//         NumExpr(2), new VariableExpr("x"))))->equals(new LetExpr("y", new
//         NumExpr(4), new AddExpr(new NumExpr(2), new VariableExpr("x")))));
//     }
//     SECTION("Values_same_different_body")
//     {
//         REQUIRE(!(new LetExpr("x", new NumExpr(4), new AddExpr(new
//         NumExpr(2), new VariableExpr("x"))))->equals(new LetExpr("x", new
//         NumExpr(4), new MultiExpr(new NumExpr(3), new VariableExpr("y")))));
//     }
//     SECTION("different_types")
//     {
//         REQUIRE(!(new LetExpr("x", new NumExpr(4), new AddExpr(new
//         NumExpr(2), new VariableExpr("x"))))->equals(new MultiExpr(new
//         NumExpr(3), new VariableExpr("y"))));
//     }
// }
//
// TEST_CASE("Let_has_variable_mine")
//{
//     SECTION("has")
//     {
//         REQUIRE((new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2),
//         new VariableExpr("x"))))->hasVariable());
//     }
//     SECTION("does_not_has")
//     {
//         REQUIRE(!(new LetExpr("x", new NumExpr(4), new AddExpr(new
//         NumExpr(2), new NumExpr(4))))->hasVariable());
//     }
// }
//
// TEST_CASE("Let_print_mine")
//{
//     CHECK((new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new
//     NumExpr(3), new AddExpr(new VariableExpr("y"), new NumExpr(2))), new
//     VariableExpr("x"))))->to_string() == "(LetExpr x=5 _in ((LetExpr y=3 _in
//     (y+2))+x))"); CHECK((new LetExpr("x", new NumExpr(1),
//                     new LetExpr("y", new NumExpr(1),
//                              new LetExpr("z", new AddExpr(new
//                              VariableExpr("x"), new NumExpr(1)),
//                                       new MultiExpr(new AddExpr(new
//                                       VariableExpr("x"), new
//                                       VariableExpr("y")),
//                                                 new VariableExpr("z"))))))
//               ->to_string() == "(LetExpr x=1 _in (LetExpr y=1 _in (LetExpr
//               z=(x+1) _in ((x+y)*z))))");
// }
//
// TEST_CASE("Let_interp_mine")
//{
//
//     SECTION("hw_examples")
//     {
//         CHECK((new AddExpr(new MultiExpr(new NumExpr(5), new LetExpr("x", new
//         NumExpr(5), new VariableExpr("x"))), new NumExpr(1)))->interp() ==
//               26);
//         CHECK((new MultiExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5),
//         new AddExpr(new VariableExpr("x"), new NumExpr(1)))))->interp() ==
//               30);
//     }
//     SECTION("from_pretty_print_edge")
//     {
//         CHECK((new LetExpr("x", new NumExpr(1),
//                         new LetExpr("y", new NumExpr(1),
//                                  new LetExpr("z", new AddExpr(new
//                                  VariableExpr("x"), new NumExpr(1)),
//                                           new MultiExpr(new AddExpr(new
//                                           VariableExpr("x"), new
//                                           VariableExpr("y")),
//                                                     new
//                                                     VariableExpr("z"))))))
//                   ->interp() == 4);
//         CHECK((new MultiExpr(
//                    (new AddExpr(new MultiExpr(new NumExpr(5), new
//                    LetExpr("x", new NumExpr(5), new MultiExpr(new
//                    VariableExpr("x"), new NumExpr(2)))),
//                             new NumExpr(1))),
//                    new NumExpr(7)))
//                   ->interp() == 357); // 51 * 7
//         CHECK((new LetExpr("x", new NumExpr(10), new MultiExpr(new
//         MultiExpr(new VariableExpr("x"), new MultiExpr(new MultiExpr(new
//         NumExpr(10), new NumExpr(10)), new NumExpr(10))), new MultiExpr(new
//         NumExpr(10), new NumExpr(10)))))
//                   ->interp() == 1000000);
//         CHECK((new LetExpr("x", new NumExpr(1), new MultiExpr(new
//         MultiExpr(new VariableExpr("x"), new MultiExpr(new MultiExpr(new
//         NumExpr(10), new NumExpr(10)), new VariableExpr("x"))), new
//         MultiExpr(new NumExpr(10), new NumExpr(10)))))
//                   ->interp() == 10000);
//     }
//     SECTION("bypass_middle_let")
//     {
//         CHECK((new LetExpr("x", new NumExpr(2), new LetExpr("z", new
//         NumExpr(4), new AddExpr(new VariableExpr("x"), new NumExpr(10)))))
//                   ->interp() == 12);
//     }
// }

TEST_CASE("Parsing string") {
  SECTION("Parsing_Str") {
    CHECK_THROWS_WITH(parse_Str("()"), "Invalid input");
    CHECK(parse_Str("(1)")->equals(new NumExpr(1)));
    CHECK(parse_Str("(((1)))")->equals(new NumExpr(1)));

    CHECK_THROWS_WITH(parse_Str("(1"), "Missing close parenthesis");
    CHECK(parse_Str("1")->equals(new NumExpr(1)));
    CHECK(parse_Str("10")->equals(new NumExpr(10)));
    CHECK(parse_Str("-3")->equals(new NumExpr(-3)));
    CHECK(parse_Str("  \n 5  ")->equals(new NumExpr(5)));
    CHECK_THROWS_WITH(parse_Str("-"), "Invalid input");
    CHECK_THROWS_WITH(parse_Str(" -  5 "), "unexpected input after expression");
    CHECK(parse_Str("x")->equals(new VariableExpr("x")));
    CHECK(parse_Str("xyz")->equals(new VariableExpr("xyz")));
    CHECK(parse_Str("xYz")->equals(new VariableExpr("xYz")));
    CHECK_THROWS_WITH(parse_Str("x_z"), "Invalid input");

    CHECK(parse_Str("x + y")->equals(
        new AddExpr(new VariableExpr("x"), new VariableExpr("y"))));
    CHECK(parse_Str("x * y")->equals(
        new MultiExpr(new VariableExpr("x"), new VariableExpr("y"))));
    CHECK(parse_Str("z * x + y")
              ->equals(new AddExpr(
                  new MultiExpr(new VariableExpr("z"), new VariableExpr("x")),
                  new VariableExpr("y"))));

    CHECK(parse_Str("z * (x + y)")
              ->equals(new MultiExpr(
                  new VariableExpr("z"),
                  new AddExpr(new VariableExpr("x"), new VariableExpr("y")))));
  }
}

TEST_CASE("NumVal::equals") {
  SECTION("EQUALS") {
    IfExpr *b =
        new IfExpr(new BoolExpr(false), new NumExpr(9), new NumExpr(88));
    IfExpr *c = new IfExpr(new EqExpr(new NumExpr(1), new NumExpr(5)),
                           new NumExpr(1), new NumExpr(77));
    IfExpr *d = new IfExpr(
        new AddExpr(new EqExpr(new NumExpr(1), new NumExpr(2)), new NumExpr(5)),
        new NumExpr(1), new NumExpr(77));
    IfExpr *f = new IfExpr(new AddExpr(new NumExpr(1), new NumExpr(2)),
                           new NumExpr(1), new NumExpr(77));
    Expr *g =
        new EqExpr(new NumExpr(6), new AddExpr(new NumExpr(5), new NumExpr(6)));
    EqExpr *h = new EqExpr(new NumExpr(6), new NumExpr(7));
    CHECK_THROWS_WITH(f->interp(), "It's not equal expression doable");
    //    h->pretty_print(std::cout);

    CHECK((new NumVal(1))->equals(nullptr) == false);
  }

  SECTION("from quiz") {

    CHECK((parse_Str("_if 1 == 2 _then 5 _else 6"))
              ->equals(new IfExpr(new EqExpr(new NumExpr(1), new NumExpr(2)),
                                  new NumExpr(5), new NumExpr(6))));

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
    CallExpr *t = new CallExpr(
        new FunExpr("x", new AddExpr(new VariableExpr("x"), new NumExpr(1))),
        new NumExpr(10));

    CHECK((t->interp())->equals(new NumVal(11)));
    FunExpr *t2 =
        new FunExpr("x", new AddExpr(new VariableExpr("x"), new NumExpr(5)));

    FunVal *e = new FunVal("x", new NumExpr(6));

    //    "_let f = _fun (x) x + 1 \n"
    //    "_in _let g = _fun (x)\n"
    //    "              f(2) + x\n"
    //    "_in g(5) "
    LetExpr *l = new LetExpr(
        "f",
        new FunExpr("x", new AddExpr(new VariableExpr("x"), new NumExpr(1))),
        new LetExpr(
            "g",
            new FunExpr("x", new AddExpr(new CallExpr(new VariableExpr("f"),
                                                      new NumExpr(2)),
                                         new VariableExpr("x"))),
            new CallExpr(new VariableExpr("g"), new NumExpr(5))));

    LetExpr *l2 = new LetExpr(
        "f",
        new FunExpr("x", new AddExpr(new VariableExpr("x"), new NumExpr(1))),
        new CallExpr(new VariableExpr("f"), new NumExpr(2)));
    //    l->print(std::cout);
    //    l->interp()->print(std::cout);

    //    l->print(std::cout);
    //    l->interp()->print(std::cout);
  }

  SECTION("From quiz") {
    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in f(5) ")
                ->interp()
                ->equals(new NumVal(6)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           7\n"
                      "_in f(5)")
                ->interp()
                ->equals(new NumVal(7)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           _true\n"
                      "_in f(5) ")
                ->interp()
                ->equals(new BoolVal(true)));

    REQUIRE_THROWS_WITH(parse_Str("_let f = _fun (x)\n"
                                  "           x + _true\n"
                                  "_in f(5) ")
                            ->interp(),
                        "AddExpr of non-number");

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           x + _true\n"
                      "_in 5 + 1 ")
                ->interp()
                ->equals(new NumVal(6)));

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
                ->equals(new NumVal(7)));

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in _let g = _fun (y) y+ 2 \n"
                      "_in _if _true\n"
                      "    _then f(5)\n"
                      "    _else g(5)")
                ->interp()
                ->equals(new NumVal(6)));

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in _let g = _fun (y) y+ 2 \n"
                      "_in f(g(5)) ")
                ->interp()
                ->equals(new NumVal(8)));

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in _let g = _fun (y)\n"
                      "              f(y + 2)\n"
                      "_in g(5) ")
                ->interp()
                ->equals(new NumVal(8)));

    REQUIRE(parse_Str("_let f = _fun (x) x + 1 \n"
                      "_in _let g = _fun (x)\n"
                      "              f(2) + x\n"
                      "_in g(5) ")
                ->interp()
                ->equals(new NumVal(8)));

    REQUIRE_THROWS_WITH(parse_Str("_let f = _fun (x) x+ 1 \n"
                                  "_in f 5 ")
                            ->interp(),
                        "[ERROR] : Invalid input");

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in (f)(5) ")
                ->interp()
                ->equals(new NumVal(6)));

    auto *add_x_1 = new AddExpr(new VariableExpr("x"), new NumExpr(1));
    auto *fun_val_x_add_x_1 = new FunVal("x", add_x_1);
    REQUIRE(parse_Str("_fun (x) x+ 1")->interp()->equals(fun_val_x_add_x_1));

    REQUIRE(parse_Str("_let f = _fun (x) x+ 1 \n"
                      "_in f ")
                ->interp()
                ->equals(fun_val_x_add_x_1));

    REQUIRE(parse_Str("(_fun (x)\n"
                      "   x + 1)(5)")
                ->interp()
                ->equals(new NumVal(6)));

    REQUIRE(parse_Str("_let f = _if _false\n"
                      "            _then _fun (x)  \n"
                      "                        x+ 1 \n"
                      "           _else _fun (x)\n"
                      "                       x+ 2\n"
                      "_in f(5)")
                ->interp()
                ->equals(new NumVal(7)));

    REQUIRE(parse_Str("(_if _false \n"
                      "  _then _fun (x)\n"
                      "            x+ 1\n"
                      "   _else _fun (x)\n"
                      "                x + 2)(5)")
                ->interp()
                ->equals(new NumVal(7)));

    REQUIRE(parse_Str("_let f = _fun (g)\n"
                      "           g(5)\n"
                      "_in _let g = _fun (y)  \n"
                      "             y + 2\n"
                      "_in f(g) ")
                ->interp()
                ->equals(new NumVal(7)));

    REQUIRE(parse_Str("_let f = _fun (g)\n"
                      "           g(5)\n"
                      "_in f(_fun (y)\n"
                      "        y + 2)")
                ->interp()
                ->equals(new NumVal(7)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           _fun (y)\n"
                      "x+ y _in (f(5))(1) ")
                ->interp()
                ->equals(new NumVal(6)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           _fun (y)\n"
                      "x+ y _in f(5)(1) ")
                ->interp()
                ->equals(new NumVal(6)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           _fun (g)\n"
                      "             g(x + 1)\n"
                      "_in _let g = _fun (y)\n"
                      "              y+ 2 \n"
                      "_in (f(5))(g) ")
                ->interp()
                ->equals(new NumVal(8)));

    REQUIRE(parse_Str("_let f = _fun (x)\n"
                      "           _fun (g)\n"
                      "             g(x + 1)\n"
                      "_in _let g = _fun (y)\n"
                      "y+ 2 _in f(5)(g)")
                ->interp()
                ->equals(new NumVal(8)));

    CHECK((parse_Str("_let factrl = _fun (factrl)\n"
                     "                _fun (x)\n"
                     "                  _if x == 1\n"
                     "                  _then 1\n"
                     "                  _else x * factrl(factrl)(x + -1)\n"
                     "_in  factrl(factrl)(10)"))
              ->interp()
              ->equals(new NumVal(3628800)));

    REQUIRE(parse_Str("_let f = _fun (f)\n"
                      "           _fun (x)\n"
                      "             _if x == 0\n"
                      "             _then 0\n"
                      "             _else x + f(f)(x + -1)\n"
                      "_in f(f)(3)")
                ->interp()
                ->equals(new NumVal(6)));
  }
}

#endif // CS6015_TEST_H
