/*
* mainpage MSDScript
* author Rylie Byers
* date 01-24-2024
*/

#include "expr.h"
#include "catch.h"
#include "cmdline.hpp"
#include "parse.hpp"
#include "pointer.h"
#include "Env.h"


int main(int argc, char* argv[]) 


{
 
    PTR(Env) empty = NEW(emptyEnv)();

    
    try {
    run_mode_t mode = use_arguments(argc, argv);
    if (mode != do_nothing) {
        PTR(Expr)e = parse_expr(std::cin);
        switch (mode) {
            case do_nothing:
                break;
            case do_interp:
                std::cout << e->interp(empty) << "\n";
                break;
            case do_print:
                e->print(std::cout);
                std::cout << "\n";
                break;
            case do_pretty_print:
                std::cout << e->to_pretty_print_string() << "\n";
                break;
        }
    }
    return 0;
    } catch (std::runtime_error exn) {
        std::cerr << exn.what() << "\n";
        return 1;
      }
}



