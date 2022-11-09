#include "../include/main_library.hpp"
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./computor_v2
// график
// вектор
// проверить историю
// расширить тесты

static Computor_v2	comp;
bool is_radian = false;

void _signal_handler(int signal)
{
	{
		std::string msg = "\rSTOP SIGNAL";
		if (signal == -1)
			msg.append(" Ctrl + D ");
		else if (signal == 2)
			msg.append(" Ctrl + C ");
		else if (signal == 3)
			msg.append(" Ctrl + / ");
		else if (signal == 20)
			msg.append(" Ctrl + Z ");
		else
			msg.append(" Unknown signal ");

		msg.append("from user");

		std::cout << "\033[93m";
		std::cout << msg << std::endl;
		std::cout << "\033[0m";
	}
	exit(signal);
}


int main()
{
	std::cout << "\033[95m";
	std::cout << "The computor_v2 START!!!" << std::endl;
	std::cout << "\033[0m";

	signal(SIGINT, _signal_handler);	//Ctrl + 'C'
	signal(SIGQUIT, _signal_handler);	//Ctrl + '\'
	signal(SIGTSTP, _signal_handler);	//Ctrl + 'Z'

	bool is_radian = false;
	while (true)
	{
		std::string	input;
		std::cout << " > ";
		getline(std::cin, input);

		if (std::cin.eof())				//Ctrl + 'D'
			_signal_handler(-1);

		transform(input.begin(), input.end(), input.begin(), ::tolower);

		if (input == "quit")
			break;

		comp.analysis(input);
	}

	std::cout << "\033[95m";
	std::cout << "The END!!!" << std::endl;
	std::cout << "\033[0m";	
	return 0;
}
