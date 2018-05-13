#include "main.hpp"

int main() {
	bool ok = false;
	std::string bekeres;
	do {
		std::cout << "Kerem adjon meg egy letezo fajlnevet, pl. mobil/mobil00.jpg" << std::endl << "-->> ";
		std::cin >> bekeres;
		cv::Mat teszt = cv::imread(bekeres, GRAYSCALE);
		if (!teszt.empty()) ok = true;
		else if (!bekeres.compare("exit")) return 0;
		else std::cout << "Nem letezo fajl!" << std::endl;
	} while (!ok);

	TreningElemTarolo tarolo;

	//beolvasáshoz hely + kiterjesztés

	//beolvas(string utvonal, string kiterjesztes, Tipus hova)..

	enum Tipus tipustumb[TIPUSDB] = { Tipus::MOBIL, Tipus::SOR, Tipus::BURGER };
	std::string utvonaltomb[TIPUSDB] = { "mobil/mobil", "sor/sor", "burger/burger" };
	for (int i = 0; i < TIPUSDB; i++) {
		tarolo.beolvas(utvonaltomb[i], ".jpg", tipustumb[i]);
	}

	bool vege = false;
	int tipdbcheck = 0;
	while (tipdbcheck < TIPUSDB && !vege) {
		Tipus eredmeny = tarolo.svmTrening(tipustumb[tipdbcheck], bekeres);
		if (eredmeny == Tipus::MOBIL) {
			std::cout << "Az objektum egy mobiltelefon!" << std::endl;
			vege = true;
		}
		else if (eredmeny == Tipus::SOR) {
			std::cout << "Az objektum egy sorosuveg!" << std::endl;
			vege = true;
		}
		else if (eredmeny == Tipus::BURGER) {
			std::cout << "Az objektum egy hamburger!" << std::endl;
			vege = true;
		}
		tipdbcheck++;
	}
	if (!vege) std::cout << "Az objektum (" << bekeres << ") nem meghatorzhato!" << std::endl;
	cv::waitKey();
	return 0;
}