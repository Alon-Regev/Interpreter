#pragma once
#include <map>
#include <iostream>
#include <thread>
#include <chrono>

#include "StaticFunction.h"
#include "Tuple.h"
#include "Void.h"

#include "ReturnException.h"

void initVariables(std::map<std::string, Type*>&);
void setVariable(const std::string& name, Type* type, std::map<std::string, Type*>& variables);

Type* print(Type*);
Type* input(Type*);
Type* deleteVariable(Type*);
Type* typeof(Type*);
Type* instanceof(Type*);
Type* length(Type*);
Type* random(Type*);
Type* range(Type*);

Type* find(Type*);
Type* sort(Type*);

Type* lower(Type*);
Type* upper(Type*);

Type* ret(Type*);

Type* throwFunc(Type*);

Type* sleep(Type*);
