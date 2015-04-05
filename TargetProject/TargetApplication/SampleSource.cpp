#include "stdafx.h"
#include "SampleSource.h"

SampleClass::SampleClass() {}
SampleClass::~SampleClass() {}

std::string SampleClass::echo()
{
	return "Hello, World!";
}

double Add(double a, double b){ return a + b; }
double Sub(double a, double b){ return a - b; }
double Multiply(double a, double b){ return a * b; }
double Divide(double a, double b){ return a / b; }
