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

void TreningElemTarolo::listazas(std::vector<TreningElem> tarolo) {
	std::cout << "A felvett trening mintak:" << std::endl;
	int i = 0;
	for (std::vector<TreningElem>::iterator it = tarolo.begin(); it != tarolo.end(); ++it, ++i) {
		std::cout << i << ". elem: " << it->getFajnev() << "\t\tPozitiv? " << it->getAdatFajta() << std::endl;
	}
}

void TreningElemTarolo::beolvas(std::vector<std::string> fajlnevek, enum Tipus t) {
	for (int i = 0; i < fajlnevek.size(); i++) {
		cv::Mat beolvasottkep = Muveletek::kepBeolvas(fajlnevek[i], BLACKandWHITE);
		TreningElem t1{ beolvasottkep, fajlnevek[i], true };
		if (t == Tipus::MOBIL) {
			this->mobil.push_back(t1);
		}
		else if (t == Tipus::SOR) {
			this->sor.push_back(t1);
		}
	}

}

void TreningElemTarolo::addToTarolo(TreningElem t, enum Tipus tt) {
	if (tt == Tipus::MOBIL) {
		this->mobil.push_back(t);
	}
	else if (tt == Tipus::SOR) {
		this->sor.push_back(t);
	}
}

int TreningElemTarolo::getPozDB(std::vector<TreningElem> tarolo) {
	int i = 0;
	for (std::vector<TreningElem>::iterator it = tarolo.begin(); it != tarolo.end(); ++it) {
		if (it->getAdatFajta()) i++;
	}
	return i;
}

enum Tipus TreningElemTarolo::svmTrening(enum Tipus t, std::string fajlnev) {
	//hogdescriptor konstuktor: k�pm�ret, blokkm�ret, l�p�sk�z, cellam�ret, bindb
	cv::HOGDescriptor HOGLeiro(this->getTarolo(t)[0].getKep().size(),
		cv::Size(8, 8),
		cv::Size(4, 4),
		cv::Size(4, 4),
		9);

	//az els� (pozitiv) leiro sz�m�t�sa
	std::vector<float> leirotarolo;
	HOGLeiro.compute(this->getTarolo(t)[0].getKep(), leirotarolo);

	std::cout << "A leirok szama: " << leirotarolo.size() << std::endl;
	cv::Mat bekert = cv::imread(fajlnev, BLACKandWHITE);
	std::cout << "A felhasznalotol bekert kep merete: " << bekert.size << " pixel" << std::endl;
	std::cout << "A vizsgalt elso kep merete: " << this->getTarolo(t)[0].getKep().size << " pixel" << std::endl;


	int jelldb = leirotarolo.size();
	int mintadb = this->getTarolo(t).size();
	//mintadb(sorok) x jellegzetessegdb(oszlopok) m�ret� m�trix l�trehoz�sa cv::Mat tip.v�ltoz�ba
	cv::Mat mintak_matrix(mintadb, jelldb, CV_32F); //CV_32F: float �rt�keket k�pes fogadni

													//az els� sor felt�lt�se a m�trixban
	for (int i = 0; i < jelldb; i++)
		mintak_matrix.ptr<float>(0)[i] = leirotarolo[i];

	int pozdb = this->getPozDB(this->getTarolo(t)); //pozit�v mint�k sz�m�nak lek�r�se

													//poz. mint�k haszn�lata, i=1-t�l mert a 0. elem m�r megvolt
	for (int i = 1; i < pozdb; i++) {
		HOGLeiro.compute(this->getTarolo(t)[i].getKep(), leirotarolo);
		//sorok felt�lt�se
		for (int j = 0; j < jelldb; j++) {
			mintak_matrix.ptr<float>(i)[j] = leirotarolo[j];
		}
	}

	//neg. mint�k
	int negdb = this->getTarolo(t).size() - pozdb;
	for (int i = 0; i < negdb; i++) {
		HOGLeiro.compute(this->getTarolo(t)[i + pozdb].getKep(), leirotarolo);
		//sorok felt�lt�se
		for (int j = 0; j < jelldb; j++)
			mintak_matrix.ptr<float>(i + pozdb)[j] = leirotarolo[j];
	}

	//c�mk�k
	cv::Mat cimkek(mintadb, 1, CV_32SC1);
	cimkek.rowRange(0, pozdb) = 1.0f;
	cimkek.rowRange(pozdb, mintadb) = -1.0f;

	//SVM folyamat
	cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
	svm->setType(cv::ml::SVM::C_SVC);
	svm->setKernel(cv::ml::SVM::LINEAR);

	//tr�ning adatok
	cv::Ptr<cv::ml::TrainData> adathalmaz =
		cv::ml::TrainData::create(mintak_matrix, cv::ml::SampleTypes::ROW_SAMPLE, cimkek);

	svm->train(adathalmaz);

	std::vector<float> keresesvector;

	//keres�s:
	HOGLeiro.compute(Muveletek::kepBeolvas(fajlnev, BLACKandWHITE), leirotarolo);
	for (int i = 0; i < jelldb; i++) {
		keresesvector.push_back(leirotarolo[i]);
	}

	//predikci�
	std::vector<float> eredmeny;

	svm->predict(keresesvector, eredmeny);
	keresesvector.clear();
	Tipus kimenet;
	if (eredmeny[0] == 1.0) {
		kimenet = t;
		eredmeny.clear();
	}
	else {
		kimenet = Tipus::NINCS_TALALAT;
	}
	return kimenet;
}
