


#ifndef val_h
#define val_h

#include <string>
#include <iostream>
#include <sstream>
#include "pointer.h"
#pragma once
using namespace std;

class Expr; // Forward declaration
class Env;
CLASS (Val) {
public:
    virtual ~Val() {}
    virtual bool equals (PTR(Val) v)= 0;
    virtual PTR(Expr) to_expr()= 0;
    virtual PTR(Val) add_to(PTR(Val) other_val) = 0;
    virtual PTR(Val) mult_with(PTR(Val) other_val) = 0;
    virtual void print(ostream &ostream) = 0;
    virtual bool is_true()=0;
    virtual PTR(Val) call(PTR(Val) actual_arg)=0;
    virtual std::string to_string() = 0;

};

class NumVal : public Val{
public:
    int val;
    NumVal(int i);
    bool is_true() override;
    PTR(Expr) to_expr() override;
    bool equals (PTR(Val) v) override;
    PTR(Val) add_to(PTR(Val) other_val) override;
    PTR(Val) mult_with(PTR(Val) other_val) override;
    void print (ostream &ostream) override;
    PTR(Val) call(PTR(Val) actual_arg) override;
    std::string to_string() override;

};

class BoolVal : public Val{
public:
    bool value;
    std::string b = "";

    bool is_true() override;
    BoolVal(bool passedBool);
    PTR(Expr) to_expr() override;
    bool equals (PTR(Val) v) override;
    PTR(Val) add_to(PTR(Val) other_val) override;
    PTR(Val) mult_with(PTR(Val) other_val) override;
    void print (ostream &ostream) override;
    PTR(Val) call(PTR(Val) actual_arg) override;
    std::string to_string() override;


};

class FunVal : public Val {
public:
    string formalArg;
    PTR(Expr) body;
    PTR(Env) env;
//    FunVal(string formalArgPassed, PTR(Expr) bodyPassed);
    FunVal(std::string formalArg, PTR(Expr)body, PTR(Env) env);
    std::string to_string() override;
    PTR(Expr) to_expr() override;
    bool equals (PTR(Val) v) override;
    PTR(Val) add_to(PTR(Val) other_val) override;
    PTR(Val) mult_with(PTR(Val) other_val) override;
    void print(std::ostream &ostream) override;
    PTR(Val) call(PTR(Val) actual_arg) override;
    bool is_true() override;
};

#endif /* val_h */
