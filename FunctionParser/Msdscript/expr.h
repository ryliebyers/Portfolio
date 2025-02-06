/**
* \file expr.h
* \brief brief Defines classes for mathematical expressions.
*
* There is the expr class. Add, mult, and var subclasses. All of the expr calls get overridden by Add, mult, and var subclasses
*/

#ifndef expr_h
#define expr_h


#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <set>
#include "pointer.h"
#pragma once

class Val; // Forward declaration
class Env;// Forward declaration

typedef enum {
    prec_none, //0
    prec_add, //1
    prec_mult //1
} precedence_t;





CLASS(Expr) {
public:
    virtual ~Expr() = default; 
    virtual bool equals(PTR(Expr) e) = 0;
    virtual PTR(Val) interp(PTR(Env) env) = 0;
  //  virtual PTR(Expr) subst(std::string stringInput, PTR(Expr) e)=0;

    std::string to_string() {
        std::stringstream st("");
        this->print(st);
        return st.str();
    }

    std::string to_pretty_print_string(){
        std::stringstream st("");
        this->pretty_print_at(st);
        return st.str();
    }

    virtual void print(std::ostream& stream)=0;
    virtual void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren)=0;
    virtual void pretty_print_at(std::ostream &ot)=0;

};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(PTR(Expr) e) override;
    PTR(Val) interp(PTR(Env) env) override;
 //   PTR(Expr) subst(std::string stringInput, PTR(Expr) e) override;
    void print(std::ostream& stream) override;
    void pretty_print_at(std::ostream &ot) override;
protected:
    void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) override;
};

class Add : public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;

    Add(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e) override;
    PTR(Val) interp(PTR(Env) env) override;
   // PTR(Expr) subst(std::string stringInput, PTR(Expr) e) override;
    void print(std::ostream& stream) override;
    void pretty_print_at(std::ostream &ot) override;

protected:
    void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) override;

};

class Mult : public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;

    Mult(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e) override;
    PTR(Val) interp(PTR(Env) env) override;
   // PTR(Expr) subst(std::string stringInput, PTR(Expr) e) override;
    void print(std::ostream& stream) override;
    void pretty_print_at(std::ostream &ot) override;

protected:
    void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) override;

};

class Var : public Expr {
public:
    std::string var;
    Var(std::string varPassed);
    bool equals(PTR(Expr) e) override;
    PTR(Val) interp(PTR(Env) env) override;
 //   PTR(Expr) subst(std::string stringInput, PTR(Expr) e) override;
    void print(std::ostream& stream) override;
    void pretty_print_at(std::ostream &ot) override;

protected:
    void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) override;

};


class _Let : public Expr {
public:
    std::string varName;
    PTR(Expr) head ;
    PTR(Expr) body;

    bool equals(PTR(Expr) e) override;
    PTR(Val) interp(PTR(Env) env) override;
 //   PTR(Expr) subst(std::string stringInput, PTR(Expr) e) override;
    void print(std::ostream& stream) override;
    void pretty_print_at(std::ostream &ot) override;
    _Let(std::string varName, PTR(Expr) expr1, PTR(Expr) expr2);
    void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) override;
};


class BoolExpr: public Expr{
public:
    bool b;
   // PTR(Expr) subst(std::string stringInput, PTR(Expr) e) override;
    void pretty_print_at(std::ostream &ot) override;
    void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) override;

    BoolExpr(bool value);
    PTR(Val) interp(PTR(Env) env) override;
    void print(std::ostream& stream) override;
    bool equals(PTR(Expr) e) override;
};


class IfExpr: public Expr{
    PTR(Expr) condition;
    PTR(Expr) thenExpr;
    PTR(Expr) elseExpr;

 //   PTR(Expr) subst(std::string stringInput, PTR(Expr) e) override;
    void pretty_print_at(std::ostream &ot) override;
    void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) override;
public:
    IfExpr(PTR(Expr) condition, PTR(Expr) thenExpr, PTR(Expr) elseExpr);
    bool equals(PTR(Expr) e) override;
    PTR(Val) interp(PTR(Env) env) override;
    void print(std::ostream& stream) override;
};

class EqExpr: public Expr{
    PTR(Expr) lhs;
    PTR(Expr) rhs;
 //   PTR(Expr) subst(std::string stringInput, PTR(Expr) e) override;
    void pretty_print_at(std::ostream &ot) override;
    void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) override;
public:
    EqExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    PTR(Val) interp(PTR(Env) env) override;
    bool equals(PTR(Expr) e) override;
    void print(std::ostream& stream) override;
};

class FunExpr: public Expr{
public:
    std::string formalArg;
    PTR(Expr) body;
    FunExpr(std::string passedArg, PTR(Expr) passedBody);
    bool equals(PTR(Expr) e) override;
    PTR(Val) interp(PTR(Env) env) override;
//    PTR(Expr) subst(std::string stringInput, PTR(Expr) e) override;
    void print(std::ostream &stream) override;
    void pretty_print_at(std::ostream &ot) override;
    void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) override;
    
};

class CallExpr : public Expr{
public:
    PTR(Expr) toBeCalled;
    PTR(Expr) actualArg;
    CallExpr(PTR(Expr) toBePassed, PTR(Expr) argPassed);
    bool equals(PTR(Expr) e) override;
    PTR(Val) interp(PTR(Env) env) override;
 //   PTR(Expr) subst(std::string stringInput, PTR(Expr) e) override;
    void print(std::ostream &stream) override;
    void pretty_print_at(std::ostream &ot) override;
    void pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) override;
   
};







#endif /* expr_h */
