#include "database.hpp"

int main()
{
	database base("nosiema.txt");
	base.init();
	base.analize();
	/*base.print();*/
	std cout << base.data.at("tabela3").at("r3").at(1);
	return 0;
}