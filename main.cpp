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

	Kategoria tipustumb[TIPUSDB] = { Tipus::MOBIL, Tipus::BURGER, Tipus::STOP };
	std::string utvonaltomb[TIPUSDB] = { "mobil/mobil", "burger/burger", "stop/stop" };
	std::string kiterjesztes[TIPUSDB] = { ".jpg", ".jpg", ".jpg" };
	for (int i = 0; i < TIPUSDB; i++) {
		tarolo.beolvas(utvonaltomb[i], kiterjesztes[i], tipustumb[i]);
		tarolo.listazas(tarolo.getTarolo(tipustumb[i]));
	}

	bool vege = false;
	int tipdbcheck = 0;
	while (tipdbcheck < TIPUSDB && !vege) {
		Tipus eredmeny = tarolo.svmTrening(tipustumb[tipdbcheck], bekeres);
		if (eredmeny == Tipus::MOBIL) {
			std::cout << "\n\tAz objektum egy mobiltelefon!" << std::endl;
			vege = true;
		}
		else if (eredmeny == Tipus::BURGER) {
			std::cout << "\n\tAz objektum egy hamburger!" << std::endl;
			vege = true;
		}
		else if (eredmeny == Tipus::STOP) {
			std::cout << "\n\tAz objektum egy stoptabla!" << std::endl;
			vege = true;
		}
		tipdbcheck++;
	}
	if (!vege) std::cout << "\n\tAz objektum (" << bekeres << ") nem meghatorzhato!" << std::endl;

	cv::waitKey();
	//getchar();

	std::cout << "\n\tSzeretne latni az osszehasonlitas alapjait? (y/n) --> ";
	ok = false;
	do {
		cv::destroyAllWindows();
		std::string elozobekeres = bekeres;
		bekeres.clear();
		std::cin >> bekeres;
		if (!bekeres.compare("y")) {
			cv::Mat kep1 = Muveletek::kepBeolvas(elozobekeres, GRAYSCALE);
			std::string sub = elozobekeres.substr(0, elozobekeres.find("/")); //stop/stop_teszt.png-bõl -> stop
			cv::Mat kep2 = Muveletek::kepBeolvas(sub + "/" + sub + "00.jpg", GRAYSCALE);

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

	return 0;
}