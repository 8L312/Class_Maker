#include <iostream>
#include <string>
#include <fstream>
# include <stdlib.h>

int main(int ac, char** av)
{
	/* This programm take only one argument which is the name of the class you want to create*/

	if (ac != 2)
	{
		std::cout << "Usage : [./Class_Maker] [NameOfClass]" << std::endl;
		exit (1);
	}

	/* Because in 42 we need to write our classes to the UpperCamelCase format */
	av[1][0] = toupper(av[1][0]);

	/* Little setup to have the name ".hpp" and ".cpp" */

	std::string		name_hpp;
	std::string		name_cpp;

	name_hpp.insert(0, ".hpp");
	name_hpp.insert(0, av[1]);
	name_cpp.insert(0, ".cpp");
	name_cpp.insert(0, av[1]);


	/* First we check that the class does not already exists */
	
	std::ifstream	check_hpp;
	std::ifstream	check_cpp;

	check_hpp.open(name_hpp.c_str(), std::ios::in);
	check_cpp.open(name_cpp.c_str(), std::ios::in);

	if (check_hpp.is_open() || check_cpp.is_open())
	{
		if (check_hpp.is_open())
			std::cout << "Your Class.hpp already exists" << std::endl;
		if (check_cpp.is_open())
			std::cout << "Your Class.cpp already exists" << std::endl;
		exit (1);
	}


	/***************************************************************/
	/* Let's now create the Class.hpp following the canonical form */
	/***************************************************************/

	std::ofstream	class_hpp;
	class_hpp.open(name_hpp.c_str());

	/* include guards */

	class_hpp << "#ifndef ";
	for (size_t i = 0; i < strlen(name_hpp.c_str()); i++)
	{
		if (name_hpp.c_str()[i] == '.')
			class_hpp << '_';
		else
		class_hpp << (char)toupper(name_hpp.c_str()[i]);
	}
	class_hpp << "\n# define ";
	for (size_t x = 0; x < strlen(name_hpp.c_str()); x++)
	{
		if (name_hpp.c_str()[x] == '.')
			class_hpp << '_';
		else
			class_hpp << (char)toupper(name_hpp.c_str()[x]);
	}
	class_hpp << "\n\n";

	/* Common includes */

	class_hpp << "# include <iostream>\n# include <string>\n# include <stdlib.h>\n\n";

	/* Class definition */

	class_hpp << "class " << av[1] << "\n{\n\n";
	class_hpp << "public:\n";
	class_hpp << "	" << av[1] << "(void);\n";										// Default constructor
	class_hpp << "	" << av[1] << "(int const n);\n";								// Parametric constructor (optional)
	class_hpp << "	" << av[1] << "(" << av[1] << " const &src);\n";				// Copy constructor
	class_hpp << "	~" << av[1] << "(void);\n\n"; 									// Destructor
	class_hpp << "	int		getExample(void) const;\n";								// Getter (optional)
	class_hpp << "	void	setExample(int n);\n\n";								// Setter (optional)
	class_hpp << "	" << av[1] << "	&operator=(" << av[1] << " const &rhs);\n\n";	// Assignation operator
	class_hpp << "private:\n";
	class_hpp << "	int	_Example;\n\n";
	class_hpp << "};\n\n";
	class_hpp << "#endif";

	class_hpp.close();


	/****************************************************************/
	/* Now we finish by the class implementation with the class.cpp */
	/****************************************************************/

	std::ofstream	class_cpp;
	class_cpp.open(name_cpp.c_str());

	/* Include of Class.hpp */

	class_cpp << "#include \"" << name_hpp << "\"\n\n";

	/* Default constructor definition */

	class_cpp << av[1] << "::" <<av[1] << "(void): _exemple(0)\n{\n";
	class_cpp << "	//std::cout << \"Default constructor called\\n\"\n";
	class_cpp << "	return ;\n}\n\n";

	/* Parametric constructor definition (not canonical but quite useful) */

	class_cpp << av[1] << "::" <<av[1] << "(int const n): _exemple(n)\n{\n";
	class_cpp << "	//std::cout << \"Default constructor called\\n\"\n";
	class_cpp << "	return ;\n}\n\n";

	/* Copy constructor definition */

	class_cpp << av[1] << "::" << av[1] << "(" << av[1] << " const &src)\n{\n";
	class_cpp << "	//std::cout << \"Copy constructor called\\n\"\n";
	class_cpp << "	*this = src;\n";
	class_cpp << "	return ;\n}\n\n";

	/* Destructor definition */

	class_cpp << av[1] << "::~" << av[1] << "(void)\n{\n";
	class_cpp << "	//std::cout << \"Destructor called\\n\"\n";
	class_cpp << "	return ;\n}\n\n";

	/* Getter of _Exemple (also non canonical) */

	class_cpp << "int	" << av[1] << "::getExample(void) const\n{\n";
	class_cpp << "	return (this->_Example);\n}\n\n";

	/* Setter of _Example (non canonical) */

	class_cpp << "void	" << av[1] << "::setExample(int n)\n{\n";
	class_cpp << "	this->_Example = n;\n";
	class_cpp << "	return ;\n}\n\n";

	/* Assignation operator definiton */

	class_cpp << av[1] << "	&" << av[1] << "::operator=(" << av[1] << " const &rhs)\n{\n";
	class_cpp << "	//std::cout << \"Assignation operator called\\n\"\n";
	class_cpp << "	//copy here the eventual values like :\n	this->_Example = rhs.getExample();\n\n";
	class_cpp << "	return (*this);\n}\n";

	class_cpp.close();


	return (0);
}
