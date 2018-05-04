#include "main.hpp"

cv::Mat Muveletek::kepBeolvas(std::string Fajlnev, int mod) {
	cv::Mat beolvasottkep;
	beolvasottkep = cv::imread(Fajlnev, mod);
	if (beolvasottkep.empty()) {
		std::cout << "A kepet nem sikerult beolvasni: " << Fajlnev << std::endl;
	}
	return beolvasottkep;
}

bool TreningElem::getAdatFajta() { return this->pozvagyneg; }

std::string TreningElem::getFajnev() { return this->fajlnev; }

cv::Mat TreningElem::getKep() { return this->kep; }

void TreningElemTarolo::beolvas(std::vector<std::string> fajlnevek, enum Tipus t) {
	for (int i = 0; i < fajlnevek.size(); i++) {
		cv::Mat beolvasottkep = Muveletek::kepBeolvas(fajlnevek[i], BLACKandWHITE);
		TreningElem t{ beolvasottkep, fajlnevek[i], true };
		this->addToTarolo(t, Tipus::MOBIL);
	}

}

void TreningElemTarolo::addToTarolo(TreningElem t, enum Tipus tt) {
	if (tt == Tipus::MOBIL) {
		this->mobil.push_back(t);
	}
}