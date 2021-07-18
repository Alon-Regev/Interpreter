#pragma once
#include <map>
#include <iostream>

#include "StaticFunction.h"
#include "Tuple.h"
#include "Void.h"

void initVariables(std::map<std::string, Type*>&);
void setVariable(const std::string& name, Type* type, std::map<std::string, Type*>& variables);

Type* print(Type*);
Type* deleteVariable(Type*);