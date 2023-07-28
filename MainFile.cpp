#include "ReedSolomon.h"
#include "Windows.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool finish{ false };
	while (!finish)
	{
		std::cout << "Выберите действие (Decode/Encode/quit): ";
		std::string action;
		std::cin >> action;
		if (action == "Decode")
		{
			std::cout << "Введите декодируемое сообщение : ";
			std::string msg;
			std::cin >> msg;
			std::cout << "Введите количество избыточных символов: ";
			int NumOfRedChar;
			std::cin >> NumOfRedChar;
			std::cout << "Поочерёдно введите позиции ошибок (0 - позиция первого символа). Для выхода введите '-1'\n";
			std::vector<int> ErrorPos{};
			for (int counter{}; counter != NumOfRedChar; counter++)
			{
				int num;
				std::cin >> num;
				if (num == -1) { break; }
				ErrorPos.push_back(num);
			}
			std::cout << "Исходное сообщение - " << ToStr(RSDecoder(ToIntVector(msg), NumOfRedChar, ErrorPos)) << std::endl;
		}
		else if (action == "Encode")
		{
			std::cout << "Введите кодируемое сообщение: ";
			std::string msg;
			std::cin >> msg;
			std::cout << "Введите количество избыточных символов: ";
			int NumOfRedChar;
			std::cin >> NumOfRedChar;
			std::vector<int> EnMsg{RSEncoder(ToIntVector(msg), NumOfRedChar)};
			std::cout << "Закодированное сообщение - " << ToStr(EnMsg) << std::endl;
		}
		else if (action == "quit") { finish = true; }
		else { std::cout << "Команда отсутствует!" << std::endl; }
	}
	return 0;
}