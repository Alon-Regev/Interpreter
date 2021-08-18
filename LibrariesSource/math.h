#pragma once
#include <vector>
#include <map>
#include <string>
// Include needed Interpreter dependencies Here...
#include "../Interpreter/Interpreter.h"
#include "../Interpreter/Type.h"
#include "../Interpreter/Int.h"
#include "../Interpreter/Float.h"

#define DLLEXPORT __declspec(dllexport)
extern "C" DLLEXPORT const std::vector<std::string> functions;
extern "C" DLLEXPORT const std::map<std::string, Type*> variables;

// Declare your functions here...
extern "C" DLLEXPORT Type* _abs(Type* other);
extern "C" DLLEXPORT Type* _sign(Type* other);
extern "C" DLLEXPORT Type* _floor(Type* other);
extern "C" DLLEXPORT Type* _ceil(Type* other);
extern "C" DLLEXPORT Type* _round(Type* other);
extern "C" DLLEXPORT Type* _fract(Type* other);
extern "C" DLLEXPORT Type* _factorial(Type* other);
extern "C" DLLEXPORT Type* _gcd(Type* other);
extern "C" DLLEXPORT Type* _gamma(Type* other);
extern "C" DLLEXPORT Type* _erf(Type* other);

extern "C" DLLEXPORT Type* _log(Type* other);
extern "C" DLLEXPORT Type* _ln(Type* other);
extern "C" DLLEXPORT Type* _log10(Type* other);
extern "C" DLLEXPORT Type* _log2(Type* other);

extern "C" DLLEXPORT Type* _sin(Type* other);
extern "C" DLLEXPORT Type* _asin(Type* other);
extern "C" DLLEXPORT Type* _sinh(Type* other);
extern "C" DLLEXPORT Type* _asinh(Type* other);
extern "C" DLLEXPORT Type* _cos(Type* other);
extern "C" DLLEXPORT Type* _acos(Type* other);
extern "C" DLLEXPORT Type* _cosh(Type* other);
extern "C" DLLEXPORT Type* _acosh(Type* other);
extern "C" DLLEXPORT Type* _tan(Type* other);
extern "C" DLLEXPORT Type* _atan(Type* other);
extern "C" DLLEXPORT Type* _tanh(Type* other);
extern "C" DLLEXPORT Type* _atanh(Type* other);
extern "C" DLLEXPORT Type* _atan2(Type* other);
extern "C" DLLEXPORT Type* _degrees(Type* other);
extern "C" DLLEXPORT Type* _radians(Type* other);
extern "C" DLLEXPORT Type* _distance(Type* other);

extern "C" DLLEXPORT Type* _min(Type* other);
extern "C" DLLEXPORT Type* _max(Type* other);
extern "C" DLLEXPORT Type* _clamp(Type* other);

extern "C" DLLEXPORT Type* _sum(Type* other);
extern "C" DLLEXPORT Type* _product(Type* other);
extern "C" DLLEXPORT Type* _average(Type* other);
