#include "../include/Computor_v2.hpp"


void _signal_handler(int signal)
{
	std::string msg;

	msg = "\rSTOP SIGNAL";
	switch (signal)
	{
		case -1:
			msg += " Ctrl + D ";
			break;
		case 2:
			msg += " Ctrl + C ";
			break;
		case 3:
			msg += " Ctrl + / ";
			break;
		case 20:
			msg += " Ctrl + Z ";
			break;
	}
	msg += "from user";

	std::cout << "\033[93m";
	std::cout << msg << std::endl;
	std::cout << "\033[0m";
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

	Computor_v2	comp;
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
