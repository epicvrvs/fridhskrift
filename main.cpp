#include <iostream>
#include <string>
#include <vector>
#include <fridh/lexer.hpp>
#include <ail/file.hpp>
#include <fridh/interpreter.hpp>

int main(int argc, char ** argv)
{
	if(argc != 3)
	{
		std::cout << argv[0] << " <input> <output>" << std::endl;
		return 1;
	}

	std::string code;
	if(!ail::read_file(argv[1], code))
	{
		std::cout << "Unable to read input" << std::endl;
		return 1;
	}

	std::vector<fridh::line_of_code> lines;
	std::string error;
	fridh::lexer lexer(code, lines, error);
	if(!lexer.parse(lines))
	{
		std::cout << "Error: " << error << std::endl;
		std::cin.get();
		return 1;
	}

	ail::write_file(argv[2], fridh::visualise_lexemes(lines));

	return 0;
}
