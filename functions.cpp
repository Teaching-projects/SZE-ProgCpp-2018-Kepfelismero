#include "main.hpp"

cv::Mat Muveletek::kepBeolvas(std::string Fajlnev, int mod) {
	cv::Mat beolvasottkep;
	beolvasottkep = cv::imread(Fajlnev, mod);
	if (beolvasottkep.empty()) {
		std::cout << "A kepet nem sikerult beolvasni: " << Fajlnev << std::endl;
	}
	return beolvasottkep;
}