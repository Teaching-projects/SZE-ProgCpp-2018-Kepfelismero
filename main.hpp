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
#define GRAYSCALE cv::ImreadModes::IMREAD_GRAYSCALE
#define PI 3.1415927

enum Tipus {
	MOBIL,
	BURGER,
	STOP,
	NINCS_TALALAT
};

typedef enum Tipus Kategoria;

class TreningElem {
private:
	cv::Mat kep;
	std::string fajlnev;
	bool isPozitiv;
public:
	TreningElem(cv::Mat _kep, std::string _fajlnev, bool _pozvagyneg) :kep(_kep), fajlnev(_fajlnev), isPozitiv(_pozvagyneg) {  }; //konstruktor
	std::string getFajnev() const;
	cv::Mat getKep() const;
	bool getAdatFajta() const;
};

class TreningElemTarolo {
private:
	std::vector<TreningElem> mobil;
	std::vector<TreningElem> burger;
	std::vector<TreningElem> stop;
	int getPozDB(std::vector<TreningElem> tarolo);
	
public:
	void beolvas(std::string utvonal, std::string kiterjesztes, Tipus hova);
	std::vector<TreningElem> getTarolo(Kategoria t);
	static void listazas(std::vector<TreningElem> tarolo);
	void addToTarolo(TreningElem t, Kategoria tt);
	Kategoria svmTrening(Kategoria t, std::string fajlnev);
};

static class Muveletek {
public:
	static cv::Mat kepBeolvas(std::string Fajlnev, int mod);
	static void Muveletek::hogRajzol(std::vector<float>::const_iterator hog, int bindb, cv::Mat kep, float meretezes);
	static void Muveletek::kepreRajzol(cv::Mat kep, cv::Mat hogKep, cv::Size cellameret, int bindb);
};

#endif // !MAIN_HPP
