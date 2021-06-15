#pragma once
#include <map>
#include <iostream>

#include "StaticFunction.h"
#include "Tuple.h"
#include "Void.h"

void initVariables(std::map<std::string, Type*>&);

Type* print(Type*);