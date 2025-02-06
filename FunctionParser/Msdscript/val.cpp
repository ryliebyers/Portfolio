#include "val.h"
#include "expr.h"
#include "Env.h"

//===================NumVal subclass=========

NumVal::NumVal(int i) {
    val = i;
}

PTR(Expr) NumVal::to_expr() {
    return NEW(Num)(this->val);
}

bool NumVal::equals(PTR(Val) v) {
    PTR(NumVal) numPointer = CAST(NumVal)(v);
    if (numPointer == nullptr){
        return false;
    }
    return this->val == numPointer ->val;
}

PTR(Val) NumVal::add_to(PTR(Val) other_val) {
    PTR(NumVal) other_num = CAST(NumVal)(other_val);
    if (other_num == nullptr) throw runtime_error("You can't add a non-number!");
    return NEW(NumVal)( (unsigned) other_num->val + (unsigned) this->val);
}

PTR(Val) NumVal::mult_with(PTR(Val) other_val) {
    PTR(NumVal) other_num = CAST(NumVal)(other_val);
    if(other_num == nullptr) throw runtime_error("You can't mult a non-number!");
    return NEW(NumVal)((unsigned)this->val * (unsigned)other_num->val);
}

void NumVal::print(std::ostream &ostream) {
    ostream << val;
}

bool NumVal::is_true() {
    throw std::runtime_error("cannot use is_true on NumVal");
}

PTR(Val) NumVal::call(PTR(Val) actualArg){
    throw runtime_error("Cannot call NumVal!");
}

std::string NumVal::to_string() {
    std::string string = std::to_string(this->val);
    return string;
}

//===================BoolVal subclass=========

BoolVal::BoolVal(bool passedBool){
    value = passedBool;
}

bool BoolVal::equals(PTR(Val) v) {
    PTR(BoolVal) bv = CAST(BoolVal)(v);
    return bv != nullptr && value == bv->value;
}

PTR(Expr) BoolVal::to_expr() {
    return NEW(BoolExpr)(this->value);
}

PTR(Val) BoolVal::add_to(PTR(Val) other_val) {
    throw std::runtime_error("Cannot add boolean values");
}

PTR(Val) BoolVal::mult_with(PTR(Val) other_val) {
    throw std::runtime_error("Cannot multiply boolean values");
}

void BoolVal::print(std::ostream &ostream) {
    ostream <<:: to_string(value);
}

bool BoolVal::is_true() {
    return value;
}

PTR(Val) BoolVal::call(PTR(Val) actualArg){
    throw runtime_error("Cannot call BoolVal");
}
std::string BoolVal::to_string() {
    return b;
}
//===================FunVal subclass=========

//FunVal::FunVal(std::string formalArgPassed, PTR(Expr) bodyPassed) {
//    this->formalArg = formalArgPassed;
//    this->body = bodyPassed;
//}
FunVal::FunVal(std::string formalArgInput, PTR(Expr)body, PTR(Env) env) {
    this->formalArg = formalArgInput;
    this->body = body;
    this->env = env;
}

PTR(Expr) FunVal::to_expr() {
    return NEW(FunExpr)(this->formalArg, this->body);
}

bool FunVal::equals(PTR(Val) v) {
    PTR(FunVal) funPtr = CAST(FunVal)(v);
    if (funPtr == nullptr){
        return false;
    }
    return this->formalArg == funPtr->formalArg && this->body->equals(funPtr->body);
}

PTR(Val) FunVal::add_to(PTR(Val) other_val) {
    throw runtime_error("can't add");
}

PTR(Val) FunVal::mult_with(PTR(Val) other_val) {
    throw runtime_error("can't multiply");
}

void FunVal::print(std::ostream &ostream) {
}

bool FunVal::is_true() {
    return false;
}

PTR(Val)FunVal::call(PTR(Val)actualArg) {
    return body->interp(NEW(ExtendedEnv)(formalArg, actualArg, env));
}


std::string FunVal::to_string() {
    
    std::string string = "_fun (";
    string += formalArg;
    string += ") ";
    string += body->to_string();
    return string;
}
