
#ifndef PARSE_HPP
#define PARSE_HPP

#include <iostream>
#include <cctype>
#include <sstream>
#include "expr.h"
#include "catch.h"
#include "pointer.h"
#include "cmdline.hpp"
#include "val.h"
#pragma once


void consume(std::istream &in, int expect);
void consume(std::istream &in, const std::string &str);
void skip_whitespace(std::istream &in);
std::string peek_keyword(std::istream &in);
PTR(Expr) parse_num(std::istream &in);
PTR(Expr) parse_multicand(std::istream& in);
PTR(Expr) parse_expr(std::istream &in);
PTR(Expr) parse_expr(const std::string &in);
PTR(Expr) parse_addend(std::istream &in);
PTR(Expr) parse_bool( std::istream & stream );
PTR(Expr) parse_if ( std::istream & stream );
PTR(Expr) parse_eqs ( std::istream & stream );
PTR(Expr) parse_comparg( std::istream & stream );
PTR(Expr) parse(std::istream &in);
PTR(Expr) parse_str(const std::string& s);
PTR(Expr) parse_var(std::istream &in);
PTR(Expr) parse_let(std::istream &in);
PTR(Expr) parseInput();
PTR(Expr) parse_fun(std::istream &in);
PTR(Expr) parse_inner(std::istream &in);
void consume_word(std::istream &in, std::string str);
std::string parse_term(std::istream &in);


#endif // PARSE_HPP
