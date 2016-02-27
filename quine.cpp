#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
	std::ifstream file(__FILE__);

	std::stringstream buff;
	buff << file.rdbuf();
	std::cout << buff.str() << std::endl;
}
