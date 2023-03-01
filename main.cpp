#include "cmdline.h"
#include "Expr.hpp"
/**
 * \mainpage MSDScript-main.cpp
 * \author Howard Tung
 * \date 02-07-2023
 */

/**
 * \brief Call use_arguments function
 * \param argc - how many arguments are there
 * \param argv - array of arguments
 * \return return integer
 */
int main(int argc, char **argv)
{
	try
	{
		run_mode_t type = use_arguments(argc, argv);
		Expr *parseExpr;
		switch (type)
		{
		case do_interp:
			parseExpr = parse_Expr(std::cin);
			std::cout << parseExpr->interp() << std::endl;
			// std::cout << "Value: " << parseExpr->interp() << std::endl;
			exit(0);
			break;

		case do_print:
			parseExpr = parse_Expr(std::cin);
			// std::cout << "Print: " << std::endl;
			parseExpr->print(std::cout);
			std::cout << std::endl;
			exit(0);
			break;

		case do_pretty_print:
			parseExpr = parse_Expr(std::cin);
			// std::cout << "Pretty-print: " << std::endl;
			parseExpr->pretty_print(std::cout);
			std::cout << std::endl;
			exit(0);
			break;

		default:
			exit(0);
			break;
		}
		return 0;
	}
	catch (std::runtime_error exn)
	{
		std::cerr << exn.what() << "\n";
		
		return 1;
		exit(1);
	}
}
