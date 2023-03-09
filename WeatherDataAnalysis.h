//
// Created by Reza Tabriz on 08/03/2023.
//

#ifndef UNTITLED_WEATHERDATAANALYSIS_H
#define UNTITLED_WEATHERDATAANALYSIS_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#define FILE_PATH "data/"

class WeatherDataAnalysis {
private:
    std::map<time_t, double> timeToPressure_;

    void loadData();

    time_t getFirstDateTime();

    time_t getLastDateTime();

    time_t convertDateTime(std::string date, std::string time);

public:
    WeatherDataAnalysis();

    bool isValidDateTime(std::string date, std::string time);

    double computeCoeff(std::string startDate, std::string startTime,
                        std::string endDate, std::string endTime);
};


#endif //UNTITLED_WEATHERDATAANALYSIS_H
