#include "main.hpp"

int main() {
	bool ok = false;
	std::string bekeres;
	do {
		std::cout << "Kerem adjon meg egy letezo fajlnevet, pl. mobil/mobil00.jpg" << std::endl << "-->> ";
		std::cin >> bekeres;
		cv::Mat teszt = cv::imread(bekeres, BLACKandWHITE);
		if (!teszt.empty()) ok = true;
		else if (!bekeres.compare("exit")) return 0;
		else std::cout << "Nem letezo fajl!" << std::endl;
	} while (!ok);
	return 0;
}