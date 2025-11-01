#include "ScalarConverter.hpp"
#include <cstdlib>
#include <cmath>
#include <limits>
#define INT_MIN -2147483648
#define INT_MAX	2147483647

void	ScalarConverter::convert(std::string literal)

{
	if (literal.empty())
		return ;
	try
	{
		switch (detectType(literal))
		{
			case (CHAR):
				convertChar(literal[0]);
				break ;
			case (INT):
			{
				char		*end;
				long const	l = strtol(literal.c_str(), &end, 10);
				if (*end ^ '\0' || l < INT_MIN || l > INT_MAX)
					throw (std::exception());
				convertInt(static_cast<int>(l));
				break ;
			}
			case (FLOAT):
			{
				std::string const	withoutF = \
				(literal[literal.length()] - 1 ^ 'f') ?
				literal.substr(0, literal.length() - 1) : literal;
				char				*end;
				double const		d = strtod(withoutF.c_str(), &end);
				if (*end ^ '\0')
					throw (std::exception());
				convertFloat(static_cast<float>(d));
				break ;
			}
			case (DOUBLE):
			{
				char			*end;
				double const	d = strtod(literal.c_str(), &end);

				if (*end ^ '\0')
					throw (std::exception());
				convertDouble(d);
				break ;
			}
			case (INVALID):
				std::cout << '\'' + literal + '\'' + " is invalid" << std::endl;
		}
	}
	catch (...)
	{
		std::cout << "conversion failed" << std::endl;
	}
}

ScalarConverter::Type	ScalarConverter::detectType(const std::string& literal)

{
	if (literal.length() == 1 && !isdigit(literal[0]))
		return (CHAR);
	
	bool const	has_dot = (literal.find('.') ^ std::string::npos);
	bool const	ends_with_f = (literal[literal.length() - 1] == 'f');
	char		*end;

	if (ends_with_f)
	{
		std::string const	withoutF = literal.substr(0, literal.length() - 1);
		strtod(withoutF.c_str(), &end);
		if (!*end)
			return (FLOAT);
	}
	if (!has_dot && !ends_with_f)
	{
		long const	l = strtol(literal.c_str(), &end, 10);
		if (!*end && l >= INT_MIN && l <= INT_MAX)
			return (INT);
	}
	strtod(literal.c_str(), &end);
	if (!*end)
		return (DOUBLE);
	return (INVALID);
}

void	ScalarConverter::convertChar(char const c)

{
	std::cout << "char: '" << c << '\'' << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" <<  std::endl;
	std::cout << "float: " << static_cast<double>(c) << ".0" <<  std::endl;
}

void	ScalarConverter::convertInt(int const i)

{
	if (i < 0 || i > 127)
		std::cout << "char: impossible" << std::endl;
	else if (i < 32 || i > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << static_cast<float>(i) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(i) << ".0" << std::endl;
}

void	ScalarConverter::convertFloat(float const f)

{
	bool const	is_nan = (f != f);
	bool const	is_pos_inf = (f == std::numeric_limits<float>::infinity());
	bool const	is_neg_inf = (f == -std::numeric_limits<float>::infinity());

	if (is_nan || is_pos_inf || is_neg_inf)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
	}
	else
	{
		if (f < 0.0f || f > 127.0f)
			std::cout << "char: impossible" << std::endl;
		else if (f < 32.0f || f > 126.0f)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(f) << '\'' << std::endl;

		if (f < static_cast<float>(std::numeric_limits<int>::min()) 
			|| f > static_cast<float>(std::numeric_limits<int>::max()))
			std::cout << "int: impossible" << std::endl;
		else
			std::cout << "int: " << static_cast<int>(f) << std::endl;
	}

	if (is_nan)
		std::cout << "float: nanf" << std::endl;
	else if (is_pos_inf)
		std::cout << "float: +inff" << std::endl;
	else if (is_neg_inf)
		std::cout << "float: -inff" << std::endl;
	else
	{
		float		integer_part;
		float const	fractional_part = modff(f, &integer_part);
		
		std::cout << "float: ";
		if (fractional_part == 0.0f)
			std::cout << integer_part << ".0f" << std::endl;
		else
			std::cout << f << "f" << std::endl;
	}

	double const	d = static_cast<double>(f);
	bool const		d_is_nan = (d != d);
	bool const		d_is_pos_inf = (d == std::numeric_limits<double>::infinity());
	bool const		d_is_neg_inf = (d == -std::numeric_limits<double>::infinity());

	if (d_is_nan)
		std::cout << "double: nan" << std::endl;
	else if (d_is_pos_inf)
		std::cout << "double: +inf" << std::endl;
	else if (d_is_neg_inf)
		std::cout << "double: -inf" << std::endl;
	else
	{
		double			d_integer_part;
		double const	d_fractional_part = modf(f, &d_integer_part);
		
		std::cout << "float: ";
		if (d_fractional_part == 0.0)
			std::cout << d_integer_part << ".0" << std::endl;
		else
			std::cout << d << std::endl;
	}
}

void	ScalarConverter::convertDouble(double const d)

{
	bool const	is_nan = (d != d);
	bool const	is_pos_inf = (d == std::numeric_limits<double>::infinity());
	bool const	is_neg_inf = (d == -std::numeric_limits<double>::infinity());

	if (is_nan || is_pos_inf || is_neg_inf)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
	}
	else
	{
		if (d < 0.0 || d > 127.0)
	 		std::cout << "char: impossible" << std::endl;
		else if (d < 32.0 || d > 126.0)
        	std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;

		if (d < static_cast<double>(std::numeric_limits<int>::min()) || 
		d > static_cast<double>(std::numeric_limits<int>::max()))
			std::cout << "int: impossible" << std::endl;
		else
			std::cout << "int: " << static_cast<int>(d) << std::endl;
	}

	float const	f = static_cast<float>(d);
	bool const	f_is_nan = (f != f);
	bool const	f_is_pos_inf = (f == std::numeric_limits<float>::infinity());
	bool const	f_is_neg_inf = (f == -std::numeric_limits<float>::infinity());

	if (f_is_nan)
		std::cout << "float: nanf" << std::endl;
	else if (f_is_pos_inf)
		std::cout << "float: +inff" << std::endl;
	else if (f_is_neg_inf)
		std::cout << "float: -inff" << std::endl;
	else
	{
		float 		f_integer_part;
		float const	f_fractional_part = modff(f, &f_integer_part);

		std::cout << "float: ";
		if (f_fractional_part == 0.0f)
    		std::cout << f_integer_part << ".0f" << std::endl;
		else
    		std::cout << f << "f" << std::endl;
    }

	if (is_nan)
		std::cout << "double: nan" << std::endl;
	else if (is_pos_inf)
		std::cout << "double: +inf" << std::endl;
	else if (is_neg_inf)
		std::cout << "double: -inf" << std::endl;
	else
	{
		double			integer_part;
		double const	fractional_part = modf(d, &integer_part);
		std::cout << "double: ";
		if (fractional_part == 0.0)
			std::cout << integer_part << ".0" << std::endl;
		else
			std::cout << d << std::endl;
	}
}





























ScalarConverter::ScalarConverter(void)

{

}

ScalarConverter::ScalarConverter(ScalarConverter const& copy)

{
	*this = copy;
}

ScalarConverter&	ScalarConverter::operator=(ScalarConverter const& to_assign)

{
	(void)to_assign;
	return (*this);
}

ScalarConverter::~ScalarConverter(void)

{

}
