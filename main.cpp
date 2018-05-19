#include "main.hpp"

int main() {
	bool ok = false;
	/*std::string bekeres;
	do {
		std::cout << "Kerem adjon meg egy letezo fajlnevet, pl. mobil/mobil00.jpg" << std::endl << "-->> ";
		std::cin >> bekeres;
		cv::Mat teszt = cv::imread(bekeres, GRAYSCALE);
		if (!teszt.empty()) ok = true;
		else if (!bekeres.compare("exit")) return 0;
		else std::cout << "Nem letezo fajl!" << std::endl;
	} while (!ok);*/

	TreningElemTarolo tarolo;

	//beolvasáshoz hely + kiterjesztés

	//beolvas(string utvonal, string kiterjesztes, Tipus hova)..

	Kategoria tipustumb[TIPUSDB] = { Tipus::MOBIL, Tipus::BURGER, Tipus::STOP };
	bool sikeres = tarolo.beolvas("config.txt");
	/*for (int i = 0; i < TIPUSDB; i++) {
		tarolo.beolvas("config.txt", utvonaltomb[i], kiterjesztes[i], tipustumb[i]);
		tarolo.listazas(tarolo.getTarolo(tipustumb[i]));
	}*/

	if (sikeres) {
		ok = false;
		std::string keresesutvonal;
		do {
			std::cout << "\nKerem adjon meg egy letezo utvonalat a kereseshez " << std::endl << "-->> ";
			std::cin >> keresesutvonal;
			if (access(keresesutvonal.c_str(), 0) == 0) {
				struct stat allapot;
				stat(keresesutvonal.c_str(), &allapot);
				if (allapot.st_mode& S_IFDIR) {
					ok = true;
				}
				else {
					std::cout << "Mappa utvonalat adjon meg!" << std::endl;
				}
			}
			else {
				std::cout << "Nem letezo utvonal!" << std::endl;
			}
		} while (!ok);

		int j = 0;
		std::string fajlnev;
		while (j < TESZTKEPDB) {
			bool vege = false;
			int tipdbcheck = 0;
			fajlnev = keresesutvonal + "teszt";
			std::ostringstream ss;
			ss << std::setfill('0') << std::setw(2) << j;
			fajlnev += ss.str();
			fajlnev += ".jpg";
			while (tipdbcheck < TIPUSDB && !vege) {
				Tipus eredmeny = tarolo.svmTrening(tipustumb[tipdbcheck], fajlnev);
				if (eredmeny == Tipus::MOBIL) {
					std::cout << "\n\tAz objektum (" << fajlnev << ") egy mobiltelefon!" << std::endl;
					vege = true;
				}
				else if (eredmeny == Tipus::BURGER) {
					std::cout << "\n\tAz objektum (" << fajlnev << ") egy hamburger!" << std::endl;
					vege = true;
				}
				else if (eredmeny == Tipus::STOP) {
					std::cout << "\n\tAz objektum (" << fajlnev << ") egy stoptabla!" << std::endl;
					vege = true;
				}
				tipdbcheck++;
			}
			if (!vege) std::cout << "\n\tAz objektum (" << fajlnev << ") nem meghatorzhato!" << std::endl;
			j++;
		}
		cv::waitKey();
		getchar();

		std::cout << "\n\tSzeretne latni az osszehasonlitas alapjait? (y/n) --> ";
		ok = false;
		do {
			cv::destroyAllWindows();
			std::string bekeres;
			std::cin >> bekeres;
			if (!bekeres.compare("y")) {
				cv::Mat kep1 = Muveletek::kepBeolvas("teszt/teszt01.jpg", GRAYSCALE);
				cv::Mat kep2 = Muveletek::kepBeolvas("stop/stop00.jpg", GRAYSCALE);

				cv::HOGDescriptor hogLeiro(cv::Size(kep1.cols, kep1.rows),
					cv::Size(8, 8),
					cv::Size(4, 4),
					cv::Size(4, 4),
					9);

				//elsõ képre
				cv::Mat kep1uj = kep1.clone();
				Muveletek::kepreRajzol(kep1, kep1uj, cv::Size(16, 16), 9);
				cv::Mat nagyobbkep1; //közös tároló
				cv::resize(kep1uj, nagyobbkep1, cv::Size(kep1uj.cols * 3, kep1uj.rows * 3), 0, 0, CV_INTER_LINEAR);
				cv::imshow("EKep", nagyobbkep1); //eredeti kép megjelenítése
				cv::moveWindow("EKep", 90, 90);

				//második képre
				cv::Mat kep2uj = kep2.clone();
				Muveletek::kepreRajzol(kep2, kep2uj, cv::Size(16, 16), 9);
				cv::resize(kep2uj, nagyobbkep1, cv::Size(kep2uj.cols * 3, kep2uj.rows * 3), 0, 0, CV_INTER_LINEAR);
				cv::imshow("Mintakep", nagyobbkep1); //minta kép megjelenítése
				cv::moveWindow("Mintakep", 300, 90);
				cv::waitKey();
				getchar();
				ok = true;
			}
			else if (!bekeres.compare("n") || !bekeres.compare("exit")) ok = true;
			else std::cout << "Nem megfelelo input!" << std::endl;
		} while (!ok);
	}
	else {
		std::cout << "A konfig fajl betoltese sikertelen volt!" << std::endl;
		
	}
	cv::waitKey();
	getchar();
	return 0;
}