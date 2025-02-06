
/**
 * \file  expr.cpp
 * \brief Implementation file for the Expr class and its subclasses.
 *
 * This file contains the implementation of the Expr class and its subclasses: Num, Add, Mult, and Var.
 * The Expr class represents an arithmetic expression, and its subclasses represent different types of expressions,
 * such as numbers, addition, multiplication, and variables.
 *
 * \author Rylie Byers
 * \date Created on January 22, 2024
 */

#include "expr.h"
#include "val.h"
#include "Env.h"

//===================NumExpr===========================
Num::Num(int val) {
    this->val = val;
}
bool Num::equals(PTR(Expr) e) {
    PTR(Num) numPtr = CAST(Num)(e);
    return numPtr && this->val == numPtr->val;
}
//PTR(Val) Num::interp() {
//    return NEW(NumVal)(val);
//}

PTR(Val)Num::interp(PTR(Env) env) {
    PTR(NumVal) value = NEW(NumVal)(this->val);
    return value;
}
//PTR(Expr) Num::subst(std::string stringInput, PTR(Expr) e) {
//    return NEW(Num)(this->val);
//}
void Num::print(std::ostream &stream) {
    stream << std::to_string(val);
}
void Num::pretty_print(std::ostream &ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) {
    ot << val;
}
void Num::pretty_print_at(std::ostream &ot) {
    std::streampos lastNewLinePos =ot.tellp();
    this-> pretty_print(ot,prec_none,lastNewLinePos, false);
}
//===================VarExpr===========================



Var::Var(std::string varPassed) : var(std::move(varPassed)) {
    
}
bool Var::equals(PTR(Expr) e) {
    PTR(Var) varPtr = CAST(Var)(e);
    return varPtr && this->var == varPtr->var;
}
//PTR(Val) Var::interp() {
//    throw std::runtime_error("no value for variable");
//    return NEW(NumVal)(-1);
//}
PTR(Val)Var::interp(PTR(Env) env) {
    return (env->lookup(this->var));
}
//PTR(Expr) Var::subst(std::string stringInput, PTR(Expr) e) {
//    if (this->var == stringInput) {
//        return e;
//    } else {
//        return NEW(Var)(this->var);
//    }
//}
void Var::print(std::ostream &stream) {
    stream << var;
}
void Var::pretty_print(std::ostream &ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) {
    ot << var;
}
void Var::pretty_print_at(std::ostream &ot) {
    std::streampos lastNewLinePos =ot.tellp();
    this-> pretty_print(ot,prec_none,lastNewLinePos, false);

}

//===================AddExpr===========================
Add::Add(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}
bool Add::equals(PTR(Expr) e) {
    PTR(Add) addPtr = CAST(Add)(e);
    return addPtr && ((this->lhs->equals(addPtr->lhs) && this->rhs->equals(addPtr->rhs)) ||
                      (this->lhs->equals(addPtr->rhs) && this->rhs->equals(addPtr->lhs)));
}
//PTR(Val) Add::interp() {
//    return this->lhs->interp()->add_to(this->rhs->interp());}

PTR(Val)Add::interp(PTR(Env) env) {
    return lhs->interp(env)->add_to(rhs->interp(env));
}

//PTR(Expr) Add::subst(std::string stringInput, PTR(Expr) e) {
//    PTR(Expr) newLHS = this->lhs->subst(stringInput,e);
//    PTR(Expr) newRHS = this->rhs->subst(stringInput,e);
//    return NEW(Add)(newLHS,newRHS);
//}
void Add::print(std::ostream &stream) {
    stream << "(";
    lhs->print(stream);
    stream << "+";
    rhs->print(stream);
    stream << ")";
}
void Add::pretty_print_at(std::ostream &ot) {
    std::streampos lastNewLinePos =ot.tellp();
    this-> pretty_print(ot,prec_add,lastNewLinePos, false);
}
void Add::pretty_print(std::ostream &ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) {
    bool needParens = prec > prec_add;

    //add should always be true??
    if (needParens) ot << "(";
    lhs->pretty_print(ot, static_cast<precedence_t>(prec_add + 1),lastNewLinePos, false);
    ot << " + ";
    rhs->pretty_print(ot, prec_add,lastNewLinePos, needParens);
    if (needParens) ot << ")";
}
//===================MultExpr===========================
Mult::Mult(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}
bool Mult::equals(PTR(Expr) e) {
    PTR(Mult) multPtr = CAST(Mult)(e);
    return multPtr && ((this->lhs->equals(multPtr->lhs) && this->rhs->equals(multPtr->rhs)) ||
                       (this->lhs->equals(multPtr->rhs) && this->rhs->equals(multPtr->lhs)));
}
PTR(Val)Mult::interp(PTR(Env) env) {
    return this->lhs->interp(env)->mult_with(this->rhs->interp(env));
}

//PTR(Val) Mult::interp() {
//    return this->lhs->interp()->mult_with(this->rhs->interp());
//}
//PTR(Expr) Mult::subst(std::string stringInput, PTR(Expr) e) {
//    PTR(Expr) newLHS = this->lhs->subst(stringInput,e);
//    PTR(Expr) newRHS = this->rhs->subst(stringInput,e);
//    return NEW(Mult)(newLHS,newRHS);
//}
void Mult::print(std::ostream &stream) {
    stream << "(";
    lhs->print(stream);
    stream << "*";
    rhs->print(stream);
    stream << ")";
}
void Mult::pretty_print_at(std::ostream &ot) {
    std::streampos lastNewLinePos = ot.tellp();
    this-> pretty_print(ot,prec_mult,lastNewLinePos, false);
}
void Mult::pretty_print(std::ostream &ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) {
    bool needParens = prec > prec_mult;
    if (needParens) ot << "(";
    this->lhs->pretty_print(ot, static_cast<precedence_t>(prec_mult + 1),lastNewLinePos, needParens);
    ot << " * ";
    this->rhs->pretty_print(ot, prec_mult,lastNewLinePos, needParens);
    if (needParens) ot << ")";
}

//===================LetExpr===========================
_Let::_Let(std::string varName, PTR(Expr) expr1, PTR(Expr) expr2){
    this->varName = varName;
    this->head=expr1;
    this->body=expr2;
}
bool _Let::equals(PTR(Expr) e) {
    auto other = CAST(_Let)(e);
    if (other == nullptr) return false;
    return varName == other->varName && head->equals(other->head) && body->equals(other->body);
}

PTR(Val)_Let::interp(PTR(Env) env) {
    PTR(Val) rhs_val = head->interp(env);
    PTR(Env) new_env = NEW(ExtendedEnv)(varName, rhs_val, env);
    return body->interp(new_env);
}
//PTR(Val) _Let::interp() {
//    PTR(Val) rhsValue = head->interp();
//    return body->subst(varName, rhsValue->to_expr())->interp();
//}
//PTR(Expr) _Let::subst(std::string stringInput, PTR(Expr) e) {
//    PTR(Expr) newHead = head->subst(stringInput, e);
//    PTR(Expr) newBody = (stringInput == varName) ? body : body->subst(stringInput, e);
//    return NEW(_Let)(varName, newHead, newBody);
//}
void _Let::print(std::ostream &stream) {
    stream << "(_let " << varName << "=" << head->to_string() << " _in " << body->to_string() << ")";
}
void _Let::pretty_print_at(std::ostream &ot) {
    std::streampos lastNewLinePos =ot.tellp();
    this-> pretty_print(ot,prec_none,lastNewLinePos, false);
}
void _Let::pretty_print(std::ostream &ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren) {
    if (!paren && prec != prec_none) {
        ot << "(";
    }
    std::streampos letPosition = ot.tellp();
    std::streampos depth = letPosition - lastNewLinePos;
    ot << "_let " << this->varName<<" = ";
    this->head->pretty_print(ot,prec_none, depth,paren);
    ot << "\n ";
    std::streampos nextPos = ot.tellp();
    for ( int i = 0; i < letPosition - lastNewLinePos; i++ ) {
        ot << " ";
    }
    ot<< "_in  ";
    this->body->pretty_print(ot, prec_none, nextPos,paren);
    if (!paren && prec != prec_none) {
        ot << ")";
    }

}

//===================EqExpr===========================

EqExpr::EqExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->rhs = rhs;
    this->lhs =lhs;
}

bool EqExpr::equals(PTR(Expr) e) {
    PTR(EqExpr) eq = CAST(EqExpr)(e);
    if (eq == nullptr) return false;
    return lhs->equals(eq->lhs) && rhs->equals(eq->rhs);
}

PTR(Val) EqExpr::interp(PTR(Env) env) {
    if (lhs->interp(env)->equals(rhs->interp(env))) {
        return NEW(BoolVal)(true);
    }
    else {
        return NEW(BoolVal)(false);
    }
}

//PTR(Val) EqExpr::interp() {
//    return NEW(BoolVal)(rhs->interp()->equals(lhs->interp()));
//}


//PTR(Expr) EqExpr::subst(std::string stringInput, PTR(Expr) e) {
//    return NEW(EqExpr)(lhs->subst(stringInput,e), rhs->subst(stringInput, e));
//}

void EqExpr::print(std::ostream &stream) {
    lhs->print(stream);
    stream << " == ";
    rhs->print(stream);
}

void EqExpr::pretty_print_at(std::ostream &ot) {
    std::streampos lastNewLinePos =ot.tellp();
    this-> pretty_print(ot,prec_add,lastNewLinePos, false);
}

void EqExpr::pretty_print(std::ostream &ot, precedence_t prec, std::streampos &lastNewLinePos, bool paren) {
    if (paren) ot << "(";
    lhs->pretty_print(ot, prec_add, lastNewLinePos, false);
    ot << " == ";
    rhs->pretty_print(ot, prec_add, lastNewLinePos, false);
    if (paren) ot << ")";
}


//===================IfExpr===========================

IfExpr::IfExpr(PTR(Expr) condition, PTR(Expr) thenExpr, PTR(Expr) elseExpr) {
    this->condition=condition;
    this->thenExpr=thenExpr;
    this->elseExpr=elseExpr;
}

bool IfExpr::equals(PTR(Expr) e) {
    PTR(IfExpr) other = CAST(IfExpr)(e);
    return other != nullptr
           && condition->equals(other->condition)
           && thenExpr->equals(other->thenExpr)
           && elseExpr->equals(other->elseExpr);
}


PTR(Val)IfExpr::interp(PTR(Env) env) {
    if (this->condition->interp(env)->is_true()) {
        return this->thenExpr->interp(env);
    } else return this->elseExpr->interp(env);
}

//PTR(Val) IfExpr::interp() {
//    PTR(Val) condVal = condition->interp();
//    PTR(BoolVal) boolVal = CAST(BoolVal)(condVal);
//    if (boolVal == nullptr) {
//        throw std::runtime_error("Condition expression did not evaluate to a boolean");
//    }
//    PTR(Val) result = boolVal->is_true() ? thenExpr->interp() : elseExpr->interp();
//    return result;
//}


//PTR(Expr) IfExpr::subst(std::string stringInput, PTR(Expr) e) {
//    return NEW(IfExpr)(this->condition->subst(stringInput, e),this->thenExpr->subst(stringInput, e), this->elseExpr->subst(stringInput, e));
//}


void IfExpr::print(std::ostream &stream) {
    stream << "_if ";
    condition->print(stream);
    stream << " _then ";
    thenExpr->print(stream);
    stream << " _else ";
    elseExpr->print(stream);
}

void IfExpr::pretty_print_at(std::ostream &ot) {
    std::streampos lastNewLinePos =ot.tellp();
    this-> pretty_print(ot,prec_none,lastNewLinePos, false);
}

void IfExpr::pretty_print(std::ostream &ot, precedence_t prec, std::streampos &lastNewLinePos, bool paren) {
    ot << "_if ";
    condition->pretty_print(ot, prec_none, lastNewLinePos, false);
    ot << "\n";
    lastNewLinePos = ot.tellp();
    ot << "_then ";
    thenExpr->pretty_print(ot, prec_none, lastNewLinePos, false);
    ot << "\n";
    ot << "_else ";
    lastNewLinePos = ot.tellp();
    elseExpr->pretty_print(ot, prec_none, lastNewLinePos, false);
    ot << "\n";
}

//===================BoolExpr===========================

BoolExpr::BoolExpr(bool value) {
    if (value) {
        this->b = true;
    } else {
        b = false;
    }
}
bool BoolExpr::equals(PTR(Expr)e) {
    PTR(BoolExpr)n = CAST(BoolExpr) (e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->b == n->b);
    }
}

PTR(Val)BoolExpr::interp(PTR(Env) env){
    return NEW(BoolVal)(b);
}


//PTR(Val) BoolExpr::interp() {
//    return NEW(BoolVal)(value);
//}


//PTR(Expr) BoolExpr::subst(std::string stringInput, PTR(Expr) e) {
//    return NEW(BoolExpr)(value);
//}

void BoolExpr::print(std::ostream &stream) {
    if (b) {
        stream << "_true";
    } else {
        stream << "_false";
    }
}
void BoolExpr::pretty_print(std::ostream &ot, precedence_t prec, std::streampos &lastNewLinePos, bool paren) {
    print(ot);
}

void BoolExpr::pretty_print_at(std::ostream &ot) {
    std::streampos lastNewLinePos =ot.tellp();
    this-> pretty_print(ot,prec_none,lastNewLinePos, false);
}
//===================FunExpr===========================

FunExpr::FunExpr(std::string passedArg, PTR(Expr) passedBody) {
    this->formalArg = passedArg;
    this->body = passedBody;
}


bool FunExpr::equals(PTR(Expr) e) {
    PTR(FunExpr) funPtr = CAST(FunExpr)(e);
    if (funPtr == nullptr){
        return false;
    }
    return this->formalArg == funPtr->formalArg && this->body->equals(funPtr->body);
}

PTR(Val) FunExpr::interp(PTR(Env) env) {
    return NEW(FunVal)(this->formalArg, this->body, env);
}


//PTR(Val) FunExpr::interp() {
//    return NEW(FunVal)(formalArg, body);
//}

//PTR(Expr) FunExpr::subst(string str, PTR(Expr) e){
//    if (formalArg == str) {
//        return THIS;
//    } else
//        return NEW(FunExpr)(formalArg, body->subst(str, e));
//}

void FunExpr::print(ostream& o){
    o << "(_fun (" << this->formalArg << ") " << this->body->to_string() << ")";
}

void FunExpr::pretty_print_at(std::ostream &ot){}

void FunExpr::pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren){}


//===================CallExpr===========================
CallExpr::CallExpr(PTR(Expr) toBeCalled, PTR(Expr) actualArg){
    this->toBeCalled = toBeCalled;
    this->actualArg = actualArg;
};

bool CallExpr::equals(PTR(Expr) e){
    PTR(CallExpr) callPtr = CAST(CallExpr)(e);
    if (callPtr == nullptr){
        return false;
    }
    return this->toBeCalled->equals(callPtr->toBeCalled) && this->actualArg->equals(callPtr->actualArg);
}

PTR(Val) CallExpr::interp(PTR(Env) env) {
    PTR(Val) temp = this->toBeCalled->interp(env);
    PTR(Val) act_arg = actualArg->interp(env);
    PTR(Val) ret = temp->call(act_arg);
    return ret;


}

//PTR(Val) CallExpr::interp(){
//    return this->toBeCalled->interp()->call(actualArg->interp());
//}
//PTR(Expr) CallExpr::subst(string str, PTR(Expr) e){
//    return NEW(CallExpr)(this->toBeCalled->subst(str, e), this->actualArg->subst(str, e));
//}
void CallExpr::print(ostream &ostream){
    ostream << "(" << this->toBeCalled->to_string() << ") (" << this->actualArg->to_string() << ")";
}

void CallExpr::pretty_print_at(std::ostream &ot){}

void CallExpr::pretty_print(std::ostream& ot, precedence_t prec, std::streampos& lastNewLinePos, bool paren){}


