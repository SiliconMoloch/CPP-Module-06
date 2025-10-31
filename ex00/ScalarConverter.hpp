#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>

class ScalarConverter

{
	private:
		ScalarConverter(void);
		ScalarConverter(ScalarConverter const &copy);
		ScalarConverter&	operator=(ScalarConverter const &to_assign);
		~ScalarConverter(void);

		enum	Type {CHAR, INT, FLOAT, DOUBLE, INVALID};
		static	Type detectType(const std::string& literal);
		
		static void			convertChar(char c);
		static void			convertInt(int i);
		static void			convertFloat(float f);
		static void			convertDouble(double d);
		static void			handleSpecialValues(const std::string& literal);
	public:
		static void			convert(std::string to_convert);
};

#endif
