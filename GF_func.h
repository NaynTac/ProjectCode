#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

std::string Bin(int);
unsigned int SumGF(unsigned int, unsigned int);
unsigned int MulGF(unsigned int, unsigned int);
unsigned int DivGF(unsigned int, unsigned int);
unsigned int ExpGF(unsigned int, unsigned int);
std::vector<int> PolynomialMulGF(std::vector<int>, std::vector<int>);