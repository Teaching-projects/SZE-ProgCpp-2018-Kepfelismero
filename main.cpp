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

	TreningElemTarolo tarolo;

	//beolvas�shoz hely + kiterjeszt�s

	std::vector<std::string> fajlnevekVector;
	std::string mappa = "mobil/mobil";
	std::string kiterj = ".jpg";

	//f�jln�v kialak�t�sa

	for (int i = 0; i < 8; i++) {
		std::string fajlnev = mappa;
		std::ostringstream ss;
		ss << std::setfill('0') << std::setw(2) << i;
		fajlnev += ss.str();
		fajlnev += kiterj;
		fajlnevekVector.push_back(fajlnev);
	}
	tarolo.beolvas(fajlnevekVector, Tipus::MOBIL);
	
	//poz. mint�k
	//�sszef�z�s
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
	cv::waitKey();
	getchar();
	return 0;
}