//
//  cmdline.cpp
//  cmdline
//
//  Created by Howard Tung on 1/12/23.
//
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "catch.h"

void use_arguments(int argc, char **argv) {
    bool hasSeen = false;

    for (int i = 1; i < argc; i++) {
        std::string s = argv[i];
        if (s == "--help") {
            std::cout << "This is a --help\n";
            exit(0);
        } else if (s == "--test" && !hasSeen) {
            if (Catch::Session().run(1, argv) != 0) {
                std::cout << "Found catch isn't 0" << std::endl;

                exit(1);
            }
            std::cout << "Test passed\n";
            hasSeen = true;

        } else if (s == "--test" && hasSeen) {
            std::cout << "U have seen test before, exit proceed\n";
            exit(1);
        } else {
            std::cerr << "Error\n";
            exit(1);
        }
    }
}
