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

	//poz. minták

	for (int i = 0; i < 8; i++) {
		std::string fajlnev = prefix;
		std::ostringstream ss;
		ss << std::setfill('0') << std::setw(2) << i;
		fajlnev += ss.str();
		fajlnev += kiterj;
		cv::Mat beolvasottkep = Muveletek::kepBeolvas(fajlnev, BLACKandWHITE);
		TreningElem t{ beolvasottkep, fajlnev, true };
		tarolo.addToTarolo(t, Tipus::MOBIL);
	}
	

	cv::Mat pozitivak(2 * tarolo.getTarolo(Tipus::MOBIL)[0].getKep().rows, 4 * tarolo.getTarolo(Tipus::MOBIL)[0].getKep().cols, CV_8U);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++) {
			tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j].getKep().copyTo(pozitivak(
				cv::Rect(j*tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j].getKep().cols,
					i*tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j].getKep().rows,
					tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j].getKep().cols,
					tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j].getKep().rows)));
		}

	cv::imshow("MOBIL Pozitiv mintak beolvasva", pozitivak);


	//neg. minták
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
	

	cv::Mat negativak(2 * tarolo.getTarolo(Tipus::MOBIL)[7].getKep().rows, 4 * tarolo.getTarolo(Tipus::MOBIL)[7].getKep().cols, CV_8U);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++) {
			tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j + pozdb].getKep().copyTo(negativak(cv::Rect(j*tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j + 7].getKep().cols,
				i*tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j + pozdb].getKep().rows,
				tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j + pozdb].getKep().cols,
				tarolo.getTarolo(Tipus::MOBIL)[i * 4 + j + pozdb].getKep().rows)));
		}
	tarolo.listazas(tarolo.getTarolo(Tipus::MOBIL));
	cv::imshow("MOBIL Negativ mintak beolvasva", negativak);

	////////////
	//másik típus

	std::vector<std::string> fajlnevek2;
	for (int i = 0; i < 8; i++) {
		std::string fajlnev = "sor/sor";
		std::ostringstream ss;
		ss << std::setfill('0') << std::setw(2) << i;
		fajlnev += ss.str();
		fajlnev += ".jpg";
		cv::Mat beolvasottkep = Muveletek::kepBeolvas(fajlnev, BLACKandWHITE);
		TreningElem t{ beolvasottkep, fajlnev, true };
		tarolo.addToTarolo(t, Tipus::SOR);
	}
	tarolo.listazas(tarolo.getTarolo(Tipus::SOR));
	

	cv::Mat sor_pozitivak(2 * tarolo.getTarolo(Tipus::SOR)[0].getKep().rows, 4 * tarolo.getTarolo(Tipus::SOR)[0].getKep().cols, CV_8U);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++) {
			tarolo.getTarolo(Tipus::SOR)[i * 4 + j].getKep().copyTo(sor_pozitivak(
				cv::Rect(j*tarolo.getTarolo(Tipus::SOR)[i * 4 + j].getKep().cols,
					i*tarolo.getTarolo(Tipus::SOR)[i * 4 + j].getKep().rows,
					tarolo.getTarolo(Tipus::SOR)[i * 4 + j].getKep().cols,
					tarolo.getTarolo(Tipus::SOR)[i * 4 + j].getKep().rows)));
		}

	cv::imshow("SOR Pozitiv mintak beolvasva", sor_pozitivak);

	fajlnevekVector.clear();
	for (int i = 0; i < 8; i++) {
		std::string fajlnev(nprefix);
		std::ostringstream ss; ss << std::setfill('0') << std::setw(2) << i;
		fajlnev += ss.str();
		fajlnev += ".png";
		fajlnevekVector.push_back(fajlnev);
		cv::Mat beolvasottkep = Muveletek::kepBeolvas(fajlnev, BLACKandWHITE);
		TreningElem t{ beolvasottkep, fajlnev, false };
		tarolo.addToTarolo(t, Tipus::SOR);
	}

	
	cv::Mat sor_negativak(2 * tarolo.getTarolo(Tipus::SOR)[7].getKep().rows, 4 * tarolo.getTarolo(Tipus::SOR)[7].getKep().cols, CV_8U);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++) {
			tarolo.getTarolo(Tipus::SOR)[i * 4 + j + pozdb].getKep().copyTo(sor_negativak(cv::Rect(j*tarolo.getTarolo(Tipus::SOR)[i * 4 + j + 7].getKep().cols,
				i*tarolo.getTarolo(Tipus::SOR)[i * 4 + j + pozdb].getKep().rows,
				tarolo.getTarolo(Tipus::SOR)[i * 4 + j + pozdb].getKep().cols,
				tarolo.getTarolo(Tipus::SOR)[i * 4 + j + pozdb].getKep().rows)));
		}

	cv::imshow("SOR Negativ mintak beolvasva", sor_negativak);
	//////////////

	Tipus eredmeny = tarolo.svmTrening(Tipus::SOR, bekeres);
	if (eredmeny == Tipus::NINCS_TALALAT) {
		std::cout << "Az objektum (" << bekeres << ") nem meghatorzhato!" << std::endl;
	}
	else if (eredmeny == Tipus::MOBIL) {
		std::cout << "Az objektum egy mobiltelefon!" << std::endl;
	}
	else if (eredmeny == Tipus::SOR) {
		std::cout << "Az objektum egy sorosuveg!" << std::endl;
	}

	cv::waitKey();
	return 0;
}