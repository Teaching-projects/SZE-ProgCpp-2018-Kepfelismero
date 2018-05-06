#include "main.hpp"



int main() {
	bool ok = false;
	std::string bekeres;
	do {
		std::cout << "Kerem adjon meg egy letezo fajlnevet, pl. mobil/mobil00.jpg" << std::endl << "-->> ";
		std::cin >> bekeres;
		cv::Mat teszt = cv::imread(bekeres, BLACKandWHITE);
		if (!teszt.empty()) ok = true;
		else std::cout << "Nem letezo fajl!" << std::endl;
	} while (!ok);


	TreningElemTarolo tarolo;



	//beolvasáshoz hely + kiterjesztés

	std::vector<std::string> fajlnevekVector;
	std::string prefix = "mobil/mobil";
	std::string kiterj = ".jpg";

	// loading 8 positive samples

	for (int i = 0; i < 8; i++) {
		std::string fajlnev = prefix;
		std::ostringstream ss;
		ss << std::setfill('0') << std::setw(2) << i;
		fajlnev += ss.str();
		fajlnev += kiterj;
		fajlnevekVector.push_back(fajlnev);
	}
	tarolo.beolvas(fajlnevekVector, Tipus::MOBIL);
	// the first 8 positive samples
	cv::Mat pozitivak(2 * tarolo.getTarolo(Tipus::MOBIL)[0].getKep().rows, 4 * tarolo.getTarolo(Tipus::MOBIL)[0].getKep().cols, CV_8U);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++) {
			tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j].getKep().copyTo(pozitivak(
				cv::Rect(j*tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j].getKep().cols,
					i*tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j].getKep().rows,
					tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j].getKep().cols,
					tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j].getKep().rows)));
		}

	cv::imshow("Pozitiv mintak beolvasva", pozitivak);


	// loading 8 negative samples
	std::string nprefix = "mobil/neg";

	fajlnevekVector.clear();
	for (int i = 0; i < 8; i++) {
		std::string fajlnev(nprefix);
		std::ostringstream ss; ss << std::setfill('0') << std::setw(2) << i;
		fajlnev += ss.str();
		fajlnev += ".png";
		fajlnevekVector.push_back(fajlnev);
		cv::Mat beolvasottkep = Muveletek::kepBeolvas(fajlnev, BLACKandWHITE);
		TreningElem t{ beolvasottkep, fajlnev, false };
		tarolo.addToTarolo(t, Tipus::MOBIL);
	}
	int pozdb = tarolo.getPozDB(tarolo.getTarolo(Tipus::MOBIL)); //pozitív minták számának lekérése
	std::cout << pozdb << " darab pozitiv minta volt!" << std::endl;
	//negativ minták
	cv::Mat negativak(2 * tarolo.getTarolo(Tipus::MOBIL)[7].getKep().rows, 4 * tarolo.getTarolo(Tipus::MOBIL)[7].getKep().cols, CV_8U);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++) {
			tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j + pozdb].getKep().copyTo(negativak(cv::Rect(j*tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j + 7].getKep().cols,
				i*tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j + pozdb].getKep().rows,
				tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j + pozdb].getKep().cols,
				tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j + pozdb].getKep().rows)));
		}

	cv::imshow("Negativ mintak beolvasva", negativak);


	cv::waitKey();
	return 0;
}