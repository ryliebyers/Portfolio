#ifndef ENV_H
#define ENV_H
#include "pointer.h"
#include "val.h"
#include "expr.h"
#include <memory>


class Env {
public:
    virtual PTR(Val) lookup(std::string find_name) = 0;
};

class emptyEnv : public Env {
    PTR(Val) lookup(std::string find_name) {
        throw std::runtime_error("free variable: "
                                 + find_name);
    }
};

class ExtendedEnv : public Env {
public:
    ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) env) {
        this->val = val;
        this->name = name;
        this->env = env;
    }
    std::string name;
    PTR(Val) val;
    PTR(Env) env;
    PTR(Val) lookup(std::string find_name) {
        if (find_name == name)
            return val;
        else
            return env->lookup(find_name);
    }

};



#endif //ENV_H
