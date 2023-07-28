#include "ReedSolomon.h"

std::vector<int> CreatePolynomialGen(int NumOfRedChar)
{
	std::vector<int> result{1};
	for (int index{ 1 }; index <= NumOfRedChar; ++index)
	{
		result = PolynomialMulGF(result, { (int)ExpGF(2, index), 1 });
	}
	return result;
}

std::vector<int> RSEncoder(std::vector<int> message, int NumOfRedChar)
{
	std::vector<int> RSCode{message};
	std::vector<int> PolynomialGen {CreatePolynomialGen(NumOfRedChar)};
	message.insert(message.cbegin(), NumOfRedChar, 0);
	while (message.size() >= PolynomialGen.size())
	{
		std::vector<int> PolCopy{PolynomialGen};
		int msg_ending{ *(message.end() - 1) };
		for (std::vector<int>::reverse_iterator frst_iter{PolCopy.rbegin()},
			scnd_iter{ message.rbegin() };
			frst_iter != PolCopy.rend(); ++frst_iter, ++scnd_iter)
		{
			*frst_iter = MulGF(*frst_iter, msg_ending);
			*scnd_iter = SumGF(*scnd_iter, *frst_iter);
		}
		message.pop_back();
	}
	std::reverse(message.begin(), message.end());
	for (int num : message) { RSCode.emplace(RSCode.cbegin(), num); }
	return RSCode;
}

int ValSubGF(std::vector<int> polynomial, int value)
{
	int result{};
	int i{};
	for (int num : polynomial)
	{
		result = SumGF(result, MulGF(num, ExpGF(value, i)));
		++i;
	}
	return result;
}

std::vector<int> MakeSyndPol(std::vector<int> message, int NumOfRedChar)
{
	std::vector<int> SyndPol{};
	for (int ex{ 1 }; ex != NumOfRedChar + 1; ++ex)
	{
		unsigned int x{ ExpGF(2, ex) };
		int result{ ValSubGF(message, x) };
		SyndPol.push_back(result);
	}
	return SyndPol;
}

std::vector<int> FormalDer(std::vector<int> polynomial)
{
	std::vector<int> result{};
	for (int index{ 1 }; index != polynomial.size(); ++index)
	{
		index % 2 ? result.push_back(polynomial[index]) : result.push_back(0);
	}
	return result;
}

std::vector<int> CreatePolynomialLoc(std::vector<int> ErrorPos)
{
	std::vector<int> result{1};
	for (int pos : ErrorPos)
	{
		result = PolynomialMulGF(result, { 1, (int)ExpGF(2, pos) });
	}
	return result;
}

std::vector<int> ForneyAlg(std::vector<int> SyndPol, std::vector<int> ErrorPos, int NumOfRedChar)
{
	std::vector<int> locator{CreatePolynomialLoc(ErrorPos)};
	std::vector<int> EvalPol{PolynomialMulGF(SyndPol, locator)};
	EvalPol.resize(ErrorPos.size());
	std::vector<int> LocatorDer{FormalDer(locator)};
	int max_error{ *std::max_element(ErrorPos.begin(), ErrorPos.end()) + 1 };
	std::vector<int> result(max_error);

	for (int index{}; index != ErrorPos.size(); ++index)
	{
		int RecNum{ (int)DivGF(1, ExpGF(2, ErrorPos[index])) };
		int EvalPolVal = ValSubGF(EvalPol, RecNum);
		int LocatorDerVal = ValSubGF(LocatorDer, RecNum);
		int ErrorVal = DivGF(EvalPolVal, LocatorDerVal);
		result[ErrorPos[index]] = ErrorVal;
	}
	return result;
}

std::vector<int> RSDecoder(std::vector<int> message, int NumOfRedChar, std::vector<int> ErrorPos)
{
	std::vector<int> SyndPol{MakeSyndPol(message, NumOfRedChar)};
	std::vector<int> ErrorCor{ForneyAlg(SyndPol, ErrorPos, NumOfRedChar)};
	for (int index{}; index != ErrorCor.size(); ++index)
	{
		message[index] = SumGF(message[index], ErrorCor[index]);
	}
	message.erase(message.begin(), message.begin() + NumOfRedChar);
	return message;

}

std::vector<int> ToIntVector(std::string str)
{
	std::vector<int> result;
	for (unsigned char symb : str)
	{
		result.push_back((int)symb);
	}
	return result;
}

std::string ToStr(std::vector<int> polynomial)
{
	std::string result;
	for (int num : polynomial)
	{
		result.push_back((unsigned char)num);
	}
	return result;
}