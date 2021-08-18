#include "Implementation.h"

#define PI 3.14159265358979323846

// Add names of exported functions and variables here...
const std::vector<std::string> functions = {
	"_abs", "_sign", "_floor", "_ceil", "_round", "_fract", "_factorial", "_gcd", "_gamma", "_erf",
	"_log", "_ln", "_log10", "_log2",
	"_sin", "_asin", "_sinh", "_asinh", "_cos", "_acos", "_cosh", "_acosh", "_tan", "_atan", "_tanh", "_atanh", "_atan2", "_degrees", "_radians", "_distance", 
	"_min", "_max", "_clamp",
	"_sum", "_product", "_average",
};
const std::map<std::string, Type*> variables = {
	{"PI", new Float(PI)},
	{"E", new Float(2.71828182845904523536)},
	{"PHI", new Float(1.618033988749894848204)}
};

// Define your functions here...

Type* _abs(Type* other)
{
	return new Int(abs(Interpreter::getNumber(other)));
}

int __sign(double other)
{
	if (other == 0)
		return 0;
	else if (other > 0)
		return 1;
	else
		return -1;
}
Type* _sign(Type* other)
{
	return new Int(__sign(Interpreter::getNumber(other)));
}

Type* _floor(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(std::floor(((Float*)other)->getValue()));
	else
		throw InvalidOperationException("floor can only get 1 float input");
}

Type* _ceil(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(std::ceil(((Float*)other)->getValue()));
	else
		throw InvalidOperationException("ceil can only get 1 float input");
}

Type* _round(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(std::round(((Float*)other)->getValue()));
	else
		throw InvalidOperationException("round can only get 1 float input");
}

Type* _fract(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(std::fmod(((Float*)other)->getValue(), 1));
	else
		throw InvalidOperationException("fract can only get 1 float input");
}

int __factorial(int n)
{
	if (n == 1 || n == 0)
		return 1;
	else
		return n * __factorial(n - 1);
}
Type* _factorial(Type* other)
{
	if (other->getType() == INT)
		return new Int(__factorial(((Int*)other)->getValue()));
	else
		throw InvalidOperationException("factorial can only get 1 int input");
}

int __gcd(int a, int b)
{
	if (b == 0)
		return a;
	return __gcd(b, a % b);
}
Type* _gcd(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other);
	if (args.size() == 2 && args[0]->getType() == INT && args[1]->getType() == INT)
		return new Int(__gcd(((Int*)args[0])->getValue(), ((Int*)args[1])->getValue()));
	else
		throw InvalidOperationException("gcd has exactly 2 int parameters");
}

Type* _gamma(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(tgamma(((Float*)other)->getValue()));
	else
		throw InvalidOperationException("gamma can only get 1 float input");
}

Type* _erf(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(erf(((Float*)other)->getValue()));
	else
		throw InvalidOperationException("erf can only get 1 float input");
}

Type* _log(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other);
	if (args.size() != 2)
		throw InvalidOperationException("log has exactly 2 number parameters");
	double x = Interpreter::getNumber(args[0]);
	double b = Interpreter::getNumber(args[1]);
	return new Float(std::log(x) / std::log(b));
}

Type* _ln(Type* other)
{
	return new Float(std::log(Interpreter::getNumber(other)));
}

Type* _log10(Type* other)
{
	return new Float(std::log10(Interpreter::getNumber(other)));
}

Type* _log2(Type* other)
{
	return new Float(std::log2(Interpreter::getNumber(other)));
}

Type* _sin(Type* other)
{
	return new Float(std::sin(Interpreter::getNumber(other)));
}

Type* _asin(Type* other)
{
	return new Float(std::asin(Interpreter::getNumber(other)));
}

Type* _sinh(Type* other)
{
	return new Float(std::sinh(Interpreter::getNumber(other)));
}

Type* _asinh(Type* other)
{
	return new Float(std::asinh(Interpreter::getNumber(other)));
}

Type* _cos(Type* other)
{
	return new Float(std::cos(Interpreter::getNumber(other)));
}

Type* _acos(Type* other)
{
	return new Float(std::acos(Interpreter::getNumber(other)));
}

Type* _cosh(Type* other)
{
	return new Float(std::cosh(Interpreter::getNumber(other)));
}

Type* _acosh(Type* other)
{
	return new Float(std::acosh(Interpreter::getNumber(other)));
}

Type* _tan(Type* other)
{
	return new Float(std::tan(Interpreter::getNumber(other)));
}

Type* _atan(Type* other)
{
	return new Float(std::atan(Interpreter::getNumber(other)));
}

Type* _tanh(Type* other)
{
	return new Float(std::tanh(Interpreter::getNumber(other)));
}

Type* _atanh(Type* other)
{
	return new Float(std::atanh(Interpreter::getNumber(other)));
}

Type* _atan2(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other);
	if (args.size() != 2)
		throw InvalidOperationException("atan2 has exactly 2 number parameters");
	double y = Interpreter::getNumber(args[0]);
	double x = Interpreter::getNumber(args[1]);
	return new Float(std::atan2(y, x));
}

Type* _degrees(Type* other)
{
	return new Float(Interpreter::getNumber(other) / PI * 180);
}

Type* _radians(Type* other)
{
	return new Float(Interpreter::getNumber(other) * PI / 180);
}

Type* _distance(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other);
	if(args.size() != 2)
		throw InvalidOperationException("distance gets exactly 2 points");
	std::vector<Type*> point0 = Interpreter::getArgs(args[0], true);
	std::vector<Type*> point1 = Interpreter::getArgs(args[1], true);
	if(point0.size() != point1.size())
		throw InvalidOperationException("distance between points with different dimensions");
	// calculate distance
	double squareSum = 0;
	for (int i = 0; i < point0.size(); i++)
	{
		double a = Interpreter::getNumber(point0[i]);
		double b = Interpreter::getNumber(point1[i]);
		squareSum += (a - b) * (a - b);
	}
	return new Float(std::sqrt(squareSum));
}

Type* _min(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other, true);
	double min = DBL_MAX;
	for (Type* t : args)
	{
		double value = Interpreter::getNumber(t);
		if (value < min)
			min = value;
	}
	return new Float(min);
}

Type* _max(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other, true);
	double max = DBL_MIN;
	for (Type* t : args)
	{
		double value = Interpreter::getNumber(t);
		if (value > max)
			max = value;
	}
	return new Float(max);
}

Type* _clamp(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other);
	if (args.size() != 3)
		throw InvalidOperationException("function clamp has 3 parameters");
	double value = Interpreter::getNumber(args[0]),
		min = Interpreter::getNumber(args[1]),
		max = Interpreter::getNumber(args[2]);
	return new Float(std::min(max, std::max(min, value)));
}

Type* _sum(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other, true);
	double s = 0;
	for (Type* t : args)
		s += Interpreter::getNumber(t);
	return new Float(s);
}

Type* _product(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other, true);
	double p = 1;
	for (Type* t : args)
		p *= Interpreter::getNumber(t);
	return new Float(p);
}

Type* _average(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other, true);
	double sum = 0;
	for (Type* t : args)
		sum += Interpreter::getNumber(t);
	return new Float(sum / args.size());
}
