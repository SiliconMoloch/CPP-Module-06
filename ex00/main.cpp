#include "ScalarConverter.hpp"

int	main(int argc, const char* argv[])

{
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			ScalarConverter::convert(argv[i]);
			if (i ^ argc - 1)
				std::cout << std::endl;
		}
		return (0);
	}
	std::cout << "./Conversion_of_scalar_types <literal>" << std::endl;
	return (1);
}
