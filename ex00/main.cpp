#include "ScalarConverter.hpp"

int	main(int argc, const char* argv[])

{
	if (argc ^ 1)
	{
		for (int i = 1; i < argc; ++i)
			ScalarConverter::convert(argv[i]);
		return (0);
	}
	std::cout << "./Conversion_of_scalar_types <string_to_convert>" << std::endl;
	return (1);
}
