#include "exec.h"
#include <vector>
#include <functional>

int main(int argc, char **argv)
{
    // 1 argument
    if (argc == 2)
    {
        const char *const interp_argv[] = {argv[1], "--interp"};
        const char *const print_argv[] = {argv[1], "--print"};
        const char *const pretty_print_argv[] = {argv[1], "--pretty-print"};
        for (int i = 0; i < 100; i++)
        {
            std::string in = random_expr_string();
            std::string inMulti = random_expr_multi_string();
            std::string inLet = random_expr_let_string();
            std::vector<std::string> randomFunction{in, inMulti, inLet};
            for (size_t i = 0; i < randomFunction.size(); i++)
            {
                std::cout << "Trying " << randomFunction[i] << "\n";
                ExecResult interp_result = exec_program(2, interp_argv, randomFunction[i]);
                ExecResult print_result = exec_program(2, print_argv, randomFunction[i]);
                ExecResult pretty_print_result = exec_program(2, pretty_print_argv, randomFunction[i]);

                ExecResult interp_again_result = exec_program(2, interp_argv, print_result.out);

                ExecResult interp_again_pretty_result = exec_program(2, interp_argv, pretty_print_result.out);

                if (interp_again_result.out != interp_result.out || interp_again_pretty_result.out != interp_result.out)
                    throw std::runtime_error("different result for printed");
            }
        }
    }

    // 2 arguments
    if (argc == 3)
    {
        const char *const interp_argv[] = {argv[1], "--interp"};
        const char *const interp_argv2[] = {argv[2], "--interp"};
        const char *const print_argv[] = {argv[1], "--print"};
        const char *const print_argv2[] = {argv[2], "--print"};
        const char *const pretty_print_argv[] = {argv[1], "--pretty-print"};
        const char *const pretty_print_argv2[] = {argv[2], "--pretty-print"};

        for (int i = 0; i < 100; i++)
        {
            std::string in = random_expr_string();
            std::string inMulti = random_expr_multi_string();
            std::vector<std::string> randomFunction{in, inMulti};
            for (size_t i = 0; i < randomFunction.size(); i++)
            {
                std::cout << "Trying " << randomFunction[i] << "\n";
                ExecResult interp_result = exec_program(2, interp_argv, randomFunction[i]);
                ExecResult interp_result2 = exec_program(2, interp_argv2, randomFunction[i]);
                ExecResult print_result = exec_program(2, print_argv, randomFunction[i]);
                ExecResult print_result2 = exec_program(2, print_argv, randomFunction[i]);
                ExecResult pretty_print_result = exec_program(2, pretty_print_argv, randomFunction[i]);
                ExecResult pretty_print_result2 = exec_program(2, pretty_print_argv, randomFunction[i]);

                // if (interp_result.out != interp_result2.out || print_result.out != print_result2.out || pretty_print_result.out != pretty_print_result2.out)
                //     throw std::runtime_error("different result for printed");

                if (interp_result.out != interp_result2.out || interp_result.exit_code != interp_result2.exit_code) {
                    std::cout << "Interp: "<<interp_result.out;
                    std::cout << "Interp2: "<<interp_result2.out;
                    std::cout << "Interp: "<<interp_result.exit_code << std::endl;
                    std::cout << "Interp2: "<<interp_result2.exit_code << std::endl;
                    throw std::runtime_error("different result for interp");
                }
                else if (print_result.out != print_result2.out || print_result.exit_code != print_result2.exit_code) {
                    std::cout << "Print: "<<print_result.out;
                    std::cout << "Print2: "<<print_result2.out;
                     std::cout << "Print: "<<print_result.exit_code<< std::endl;
                    std::cout << "Print2: "<<print_result2.exit_code << std::endl;
                    throw std::runtime_error("different result for print");
                }
                else if (pretty_print_result.out != pretty_print_result2.out || pretty_print_result.exit_code != pretty_print_result2.exit_code) {
                    std::cout << "Print_print: "<<pretty_print_result.out;
                    std::cout << "Print_print2: "<<pretty_print_result2.out;
                    std::cout << "Print_print: "<<pretty_print_result.exit_code << std::endl;
                    std::cout << "Print_print2: "<<pretty_print_result2.exit_code << std::endl;
                    throw std::runtime_error("different result for pretty_print");
                }
            }
            // std::string in = random_expr_string();
            // std::cout << "Trying " << in << "\n";
            // ExecResult interp_result = exec_program(2, interp_argv, in);
            // ExecResult print_result = exec_program(2, print_argv, in);

            // ExecResult interp_again_result = exec_program(2, interp_argv, print_result.out);

            // if (interp_again_result.out != interp_result.out)
            //     throw std::runtime_error("different result for printed");
        }
    }

    return 0;
}