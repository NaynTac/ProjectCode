#include "GF_func.h"

std::string Bin(int num)
{
	std::string result{};
	while (num > 0)
	{
		result += std::to_string(num % 2);
		num /= 2;
	}
	std::reverse(result.begin(), result.end());
	return result;
}

unsigned int SumGF(unsigned int frst_num, unsigned int scnd_num)
{
	return frst_num ^ scnd_num;
}

unsigned int MulGF(unsigned int frst_num, unsigned int scnd_num)
{
	unsigned int result{};
	std::string frst_bin{ Bin(frst_num) };
	std::reverse(frst_bin.begin(), frst_bin.end());
	for (size_t rol_num{}; rol_num != frst_bin.size(); ++rol_num)
	{
		if (frst_bin[rol_num] == '1') { result ^= scnd_num << rol_num; }
	}
	while (Bin(result).size() > 8)
	{
		int pol{ 285 };
		while (Bin(pol).size() != Bin(result).size()) { pol <<= 1; }
		result ^= pol;
	}
	return result;
}

unsigned int DivGF(unsigned int frst_num, unsigned int scnd_num)
{
	for (int num{ 1 }; num != 256; ++num)
	{
		if (MulGF(scnd_num, num) == frst_num) { return num; }
	}
}

unsigned int ExpGF(unsigned int frst_num, unsigned int scnd_num)
{
	unsigned int result{ 1 };
	for (unsigned int deg{ 1 }; deg <= scnd_num; ++deg) { result = MulGF(result, frst_num); }
	return result;
}

std::vector<int> PolynomialMulGF(std::vector<int> frst_polynomial, std::vector<int> scnd_polynomial)
{
	std::vector<int> result(frst_polynomial.size() + scnd_polynomial.size() - 1);
	for (int index{ 0 }; index != scnd_polynomial.size(); ++index)
	{
		for (std::vector<int>::iterator frst_iter{frst_polynomial.begin()}, scnd_iter{ result.begin() }; frst_iter != frst_polynomial.end(); ++frst_iter, ++scnd_iter)
		{
			*scnd_iter = SumGF(*scnd_iter, MulGF(*frst_iter, scnd_polynomial[index]));
		}
		frst_polynomial.insert(frst_polynomial.begin(), 0);
	}
	return result;
}