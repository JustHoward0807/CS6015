//
//  cmdline.cpp
//  cmdline
//
//  Created by Howard Tung on 1/12/23.
//

#include <stdio.h>
#include <iostream>
#include <string>

void use_arguments(int argc, char** argv) {
    bool hasSeen = false;
    
    for(int i = 1; i < argc; i++) {
        std::string s = argv[i];
        if (s == "--help") {
            std::cout << "This is a --help\n";
            exit(0);
        } else if (s == "--test" && !hasSeen) {
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
