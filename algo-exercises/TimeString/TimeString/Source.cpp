#include <iostream>
#include <chrono>
#include <ctime> 
//#include <iomanip>
#include <string>

int main()
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	//auto tstruct = std::localtime(&t);
	//std::string timeString{ std::ctime(&tstruct) };
	//std::string timeString = std::put_time(std::localtime(&t), "%Y_%m_%d_%X");
	//std::cout << std::put_time(std::localtime(&t), "%Y_%m_%d_%X") << std::endl;
	//std::cout << timeString << std::endl;

	std::string timeString{};
	{
		char mbstr[100];

		if (std::strftime(mbstr, sizeof(mbstr), "%Y_%m_%d_%X", std::localtime(&t)))
		{
			//timeString = std::string(mbstr);
			timeString = mbstr;
		}
		std::cout << timeString << std::endl;
	}
	return 0;
}