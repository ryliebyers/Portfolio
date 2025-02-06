/**
* \file cmdline.hpp
* \brief expression class
*
* Checks users input
*/


#ifndef cmdline_hpp
#define cmdline_hpp

#define CATCH_CONFIG_RUNNER
#include <stdio.h>
#include "expr.h"
#include "catch.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include "pointer.h"

#pragma once


enum run_mode_t {
    do_nothing,
    do_interp,
    do_print,
    do_pretty_print
};

run_mode_t use_arguments(int argc, char* argv[]);
static void check_mode_already(run_mode_t mode, std::string flag);

#endif /* cmdline_hpp */
