#pragma once
#ifndef MAIN_HPP
#define MAIN_HPP
#include <iostream>
#include <iomanip>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\objdetect.hpp>
#include <opencv2\ml.hpp>
#include <string>

#define TIPUSDB 3
#define KEPDB 8 //beolvasott képek darabszáma típusonként
#define BLACKandWHITE cv::ImreadModes::IMREAD_GRAYSCALE

enum Tipus {
	MOBIL,
	SOR,
	BURGER,
	NINCS_TALALAT
};

class TreningElem {
private:
	cv::Mat kep;
	std::string fajlnev;
	bool pozvagyneg;
public:
	TreningElem(cv::Mat _kep, std::string _fajlnev, bool _pozvagyneg) :kep(_kep), fajlnev(_fajlnev), pozvagyneg(_pozvagyneg) {  }; //konstruktor
	std::string getFajnev();
	cv::Mat getKep();
	bool getAdatFajta();
};

class TreningElemTarolo {
private:
	std::vector<TreningElem> mobil;
	std::vector<TreningElem> sor;
	std::vector<TreningElem> burger;
public:
	static void listazas(std::vector<TreningElem> tarolo);
	void addToTarolo(TreningElem t, enum Tipus tt);
	std::vector<TreningElem> getTarolo(enum Tipus t);
	void beolvas(std::string utvonal, std::string kiterjesztes, Tipus hova);
	int getPozDB(std::vector<TreningElem> tarolo);
	enum Tipus svmTrening(enum Tipus t, std::string fajlnev);
};

static class Muveletek {
public:
	static cv::Mat kepBeolvas(std::string Fajlnev, int mod);
};

#endif // !MAIN_HPP
