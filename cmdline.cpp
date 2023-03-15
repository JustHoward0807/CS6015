//
//  cmdline.cpp
//  cmdline
//
//  Created by Howard Tung on 1/12/23.
//

/**
 * \file cmdline.cpp
 * \brief Getting the input argument and deal with it
 * \author Howard Tung
 */

#define CATCH_CONFIG_RUNNER

#include <iostream>
#include "catch.h"
#include "cmdline.h"
#include "test.h"

/**
 * \brief Check input arguments if its --test or --help then doing different stuff accordingly
 * \param argc - how many arguments
 * \param argv - array of the argument
 * \return void - no return value
 */

run_mode_t use_arguments(int argc, char **argv)
{
    bool hasSeen = false;
    for (int i = 1; i < argc; i++)
    {
        std::string s = argv[i];
        if (s == "--help")
        {
            std::cout << "--test for testing cases\n";
            exit(0);
            // return do_nothing;
        }
        else if (s == "--test" && !hasSeen)
        {
            hasSeen = true;
            if (Catch::Session().run(1, argv) != 0)
            {
                std::cout << "Found catch isn't 0" << std::endl;
                exit(1);
            }
            else
            {
                exit(0);
            }
        }
        else if (s == "--test" && hasSeen)
        {
            std::cout << "U have seen test before, exit proceed\n";
            exit(1);
        }
        else if (s == "--interp")
        {
            return do_interp;
        }
        else if (s == "--print")
        {

            return do_print;
        }
        else if (s == "--pretty-print")
        {

            return do_pretty_print;
        }
        else
        {
            std::cerr << "Error, Unknown argument.\nTry --help to see more info.\n";
            exit(1);
        }
    }
    return do_nothing;
}
