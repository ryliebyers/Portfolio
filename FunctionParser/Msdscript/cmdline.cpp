/**
* \file cmdline.cpp
* \Checks user inputs
*
*
* If user inserts --test all tests run, If they enter --help lists all calls. And returns error if the correct call isnt entered.
* \author Rylie Byers
*/

#include "cmdline.hpp"

/** //update this
* \brief Parses command-line arguments to determine if tests should be run.
* \param argc The number of command-line arguments
* \param argv The array of command-line arguments.
* \return  bool True if the "--test" flag is present, indicating that tests should be run; false otherwise
*/


run_mode_t use_arguments(int argc, char* argv[]) {
    bool saw_tests = false;
    run_mode_t mode = do_nothing;

    for (int i = 1; i < argc; i++) {
        if ((std::string)argv[i] == "--help") {
            std::cout << "Available flags: \n";
            std::cout << "--test : run tests\n";
            std::cout << "--help : this help\n";
            std::cout << "--interp : ";
            std::cout << "--print : ";
            std::cout << "--pretty_print : ";
            exit(0);
        } else if ((std::string)argv[i] == "--test") {
            if (saw_tests) {
                std::cerr << "duplicate --test flag\n";
                exit(1);
            }
            saw_tests = true;
            Catch::Session().run();
            exit(1);
        } else if ((std::string)argv[i] == "--interp") {
            check_mode_already(mode, argv[i]);
            mode = do_interp;
        } else if ((std::string)argv[i] == "--print") {
            check_mode_already(mode, argv[i]);
            mode = do_print;
        } else if ((std::string)argv[i] == "--pretty_print") {
            check_mode_already(mode, argv[i]);
            mode = do_pretty_print;
        } else {
            std::cerr << "bad flag: " << argv[i] << "\n";
            exit(1);
        }
    }

    return mode;
}

static void check_mode_already(run_mode_t mode, std::string flag) {
    if (mode != do_nothing) {
        std::cerr << "extra flag: " << flag << "\n";
        exit(1);
    }
}
