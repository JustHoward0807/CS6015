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
            // std::string inMulti = random_expr_multi_string();
            // std::string inLet = random_expr_let_string();
            // std::vector<std::string> randomFunction{in, inMulti, inLet};
            // for (size_t i = 0; i < randomFunction.size(); i++)
            // {
                std::cout << "Trying " << in << "\n";
                ExecResult interp_result = exec_program(2, interp_argv, in);
                ExecResult print_result = exec_program(2, print_argv, in);
                ExecResult pretty_print_result = exec_program(2, pretty_print_argv, in);

                ExecResult interp_again_result = exec_program(2, interp_argv, print_result.out);
                ExecResult interp_again_pretty_result = exec_program(2, interp_argv, pretty_print_result.out);

                if (interp_again_result.out != interp_result.out || interp_again_pretty_result.out != interp_result.out || interp_again_result.out != interp_again_pretty_result.out)
                {
                    std::cout << "interp_result: " << interp_result.out << std::endl;
                    std::cout << "print_result: " << print_result.out << std::endl;
                    std::cout << "pretty_print_result: " << pretty_print_result.out << std::endl;
                    std::cout << "interp again result: " << interp_again_result.out << std::endl;
                    std::cout << "interp again pretty result: " << interp_again_pretty_result.out << std::endl;

                    // throw std::runtime_error("different result for printed");
                }
                else if (interp_again_result.exit_code != interp_result.exit_code || interp_again_pretty_result.exit_code != interp_result.exit_code || interp_again_result.exit_code != 0 || interp_again_pretty_result.exit_code != 0 || interp_result.exit_code != 0)
                {
                    std::cout << "Interp_again_print: " << interp_again_result.exit_code << std::endl;
                    std::cout << "Interp_result_pretty: " << interp_result.exit_code << std::endl;

                    std::cout << "Interp_again_pretty: " << interp_again_pretty_result.exit_code << std::endl;

                    // throw std::runtime_error("different result for exit code");
                }

                // else if (interp_again_result.err != interp_result.err || interp_again_pretty_result.err != interp_result.err)
                // {
                //     std::cout << "Interp_print: " << interp_again_result.exit_code << std::endl;
                //     std::cout << "Interp_pretty: " << interp_again_pretty_result.exit_code << std::endl;
                //     throw std::runtime_error("different result for err");
                // }
            // }
        }
    }

    // 2 arguments
    if (argc == 3)
    {
        const char *const interp_argv[] = {argv[1], "--interp"};
        const char *const interp_argv_Compare[] = {argv[2], "--interp"};
        const char *const print_argv[] = {argv[1], "--print"};
        const char *const print_argv_Compare[] = {argv[2], "--print"};
        const char *const pretty_print_argv[] = {argv[1], "--pretty-print"};
        const char *const pretty_print_argv_Compare[] = {argv[2], "--pretty-print"};

        for (int i = 0; i < 100; i++)
        {
            std::string in = random_expr_string();
            // std::string inMulti = random_expr_multi_string();
            // std::string inLet = random_expr_let_string();
            // std::string inMultiParenth = random_expr_with_parenth_multi_string();
            // std::string inLetParenth = random_expr_with_parenth_let_string();
            // std::string inNegative = random_expr_with_negative();
            // std::vector<std::string> randomFunction{in};
            // for (size_t i = 0; i < randomFunction.size(); i++)
            // {
                std::cout << "Trying " << in << "\n";
                ExecResult interp_result = exec_program(2, interp_argv, in);
                ExecResult interp_result_Compare = exec_program(2, interp_argv_Compare, in);

                ExecResult print_result = exec_program(2, print_argv, in);
                // std::cout << "print" <<print_result.out<< std::endl;

                ExecResult print_result_Compare = exec_program(2, print_argv_Compare, in);

                ExecResult pretty_print_result = exec_program(2, pretty_print_argv, in);

                // std::cout << "print-pretty" <<pretty_print_result.out<< std::endl;

                ExecResult pretty_print_result_Compare = exec_program(2, pretty_print_argv_Compare, in);

                // ExecResult testPrintWithInterpResult = exec_program(2, interp_argv, print_result.out);
                // ExecResult testPrint2WithInterpResult = exec_program(2, interp_argv, print_result_Compare.out);

                // ExecResult testPrintToPrettyPrint = exec_program(2, pretty_print_argv, print_result.out);
                // ExecResult testPrintToPrettyPrint2 = exec_program(2, pretty_print_argv, print_result_Compare.out);
                // std::cout << testPrintToPrettyPrint.out << std::endl;

                if (interp_result.out != interp_result_Compare.out || interp_result.exit_code != 0 || interp_result_Compare.exit_code != 0 || interp_result.exit_code != interp_result_Compare.exit_code)
                {
                    std::cout << "Interp: " << interp_result.out;
                    std::cout << "Interp2: " << interp_result_Compare.out << std::endl;
                    std::cout << "Interp_exit: " << interp_result.exit_code << std::endl;
                    std::cout << "Interp2_exit: " << interp_result_Compare.exit_code << std::endl;
                    std::cout << "Interp_err: " << interp_result.err << std::endl;
                    std::cout << "Interp2_err: " << interp_result_Compare.err << std::endl;
                    std::cout << std::endl;
                    // throw std::runtime_error("different result for interp");
                }

                if (print_result.out != print_result_Compare.out || print_result.exit_code != 0 || print_result_Compare.exit_code != 0 || print_result.exit_code != print_result_Compare.exit_code)
                {
                    std::cout << "Print: " << print_result.out << std::endl;
                    std::cout << "Print2: " << print_result_Compare.out << std::endl;
                    std::cout << "Print_exit: " << print_result.exit_code << std::endl;
                    std::cout << "Print2_exit: " << print_result_Compare.exit_code << std::endl;
                    std::cout << "Print_err: " << print_result.err << std::endl;
                    std::cout << "Print2_err: " << print_result_Compare.err << std::endl;
                    std::cout << std::endl;
                    // throw std::runtime_error("different result for print");
                }

                if (pretty_print_result.out != pretty_print_result_Compare.out || pretty_print_result.exit_code != 0 || pretty_print_result_Compare.exit_code != 0 || pretty_print_result.exit_code != pretty_print_result_Compare.exit_code) 

                {
                    std::cout << "Pretty_print: " << pretty_print_result.out << std::endl;
                    std::cout << "Pretty_print2: " << pretty_print_result_Compare.out << std::endl;
                    std::cout << "Pretty_print_exit: " << pretty_print_result.exit_code << std::endl;
                    std::cout << "Pretty_print2_exit: " << pretty_print_result_Compare.exit_code << std::endl;
                    std::cout << "Pretty_print_err: " << pretty_print_result.err << std::endl;
                    std::cout << "Pretty_print2_err: " << pretty_print_result_Compare.err << std::endl;
                    std::cout << std::endl;
                    // throw std::runtime_error("different result for pretty_print");
                }
            }
        // }
    }

    return 0;
}