#pragma once
#include "GF_func.h"

int ValSubGF(std::vector<int>, int);
std::vector<int> CreatePolynomialGen(int);
std::vector<int> RSEncoder(std::vector<int>, int);
std::vector<int> MakeSyndPol(std::vector<int>, int);
std::vector<int> FormalDer(std::vector<int>);
std::vector<int> CreatePolynomialLoc(std::vector<int>);
std::vector<int> ForneyAlg(std::vector<int>, std::vector<int>, int);
std::vector<int> RSDecoder(std::vector<int>, int, std::vector<int>);
std::vector<int> ToIntVector(std::string);
std::string ToStr(std::vector<int>);