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

#define TIPUSDB 1
#define BLACKandWHITE cv::ImreadModes::IMREAD_GRAYSCALE

enum Tipus {
	MOBIL = 0
};

static class Muveletek {
public:
	static cv::Mat kepBeolvas(std::string Fajlnev, int mod);
};

#endif // !MAIN_HPP
