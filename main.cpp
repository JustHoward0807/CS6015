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
int main(int argc, char **argv) {
	auto type = use_arguments(argc, argv);
	Expr* parseExpr;
	switch (type)
	{
	case do_interp:
		parseExpr = parse_Expr(std::cin);
        std::cout << "Value: " << parseExpr->interp() << std::endl;
		break;
	
	case do_print:
		parseExpr = parse_Expr(std::cin);
		std::cout << "Print: " << std::endl;
		parseExpr->print(std::cout);
		break;

	case do_pretty_print:
		parseExpr = parse_Expr(std::cin);
        std::cout << "Pretty-print: " << std::endl;
        parseExpr->pretty_print(std::cout);
		break;

	default:
		break;
	}

	return 0;
}
