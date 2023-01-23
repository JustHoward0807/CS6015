//
//  main.cpp
//  HW-Expression-Classes
//
//  Created by Howard Tung on 1/12/23.
//

#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "Expr.hpp"
#include "catch.h"

//2 + 3
//4 * 5
//6*(7+8)
//(1+2) * (3+4*6)
int main(int argc, const char * argv[]) {
    std::string arg;
    if (argc > 1) {
        arg = argv[1];
    }

    if (arg == "--test") {
        if (Catch::Session().run(1, argv) != 0) {
            std::cout << "Found catch isn't 0" << std::endl;
            exit(1);
        }
    } else {
        return 0;
    }

//    std::string arg;
//    if (argc > 2) {
//        arg = argv[1];
//    }
    
//    if (arg == "--test") {
//        Add *add = new Add(new Num(2), new Num(3));
//        Add *add2 = new Add(new Num(4), new Num(3));
//        assertNotEquals(add, add2, "Add(new Num(2), new Num(3))", "Add(new Num(2), new Num(3))");
//
//        Multi *mav = new Multi(new Num(6), new Add(new Num(6), new Variable("Hello")));
//        Multi *mav2 = new Multi(new Num(6), new Add(new Num(6), new Variable("Hello")));
//
//        assertEquals(mav, mav2, "Multi(new Num(6), new Add(new Num(6), new Variable('Hello')))", "Multi(new Num(6), new Add(new Num(6), new Variable('Hello')));");
//    }

    
    

    
}
