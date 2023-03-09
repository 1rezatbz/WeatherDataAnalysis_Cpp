//
// Created by Reza Tabriz on 08/03/2023.
//

#include "WeatherDataAnalysis.h"

using namespace std;

void WeatherDataAnalysis::loadData() {
    for (int year = 2012; year <= 2015; year++) {
        std::map<time_t, double> timeToPressure_;
        // ostringstream is used for concatenating strings, numbers,and other data types, just like you would with a regular output stream like cout.
        ostringstream filenameStream;
        filenameStream << FILE_PATH << "Environmental_Data_Deep_Moor_" << year << ".txt";
        string fileName = filenameStream.str();
        cout << "Loading . . . " << fileName << endl;
        //fstream is a class and it is used for reading from and writing to files on a file system.
        fstream dataFileStream;
        dataFileStream.open(fileName);
        string line;
        getline(dataFileStream, line);
        while (getline(dataFileStream, line)) {
            string date, time;
            double Air_Temp, Barometric_Press, Dew_Point, Relative_Humidity, Wind_Dir, Wind_Gust, Wind_Speed;
            //istringstream is a class, and it is used to read input from a string as if it were a stream.
            istringstream buffer(line);
            buffer >> date >> time >> Air_Temp >> Barometric_Press >> Dew_Point >> Relative_Humidity >> Wind_Dir
                   >> Wind_Gust >> Wind_Speed;
            time_t dataTime = convertDateTime(date,time);
            timeToPressure_[dataTime] = Barometric_Press;}
        dataFileStream.close();}
}

time_t WeatherDataAnalysis::getFirstDateTime() {
    return timeToPressure_.begin()->first;
}

time_t WeatherDataAnalysis::getLastDateTime() {
    return timeToPressure_.rbegin()->first;
}

time_t WeatherDataAnalysis::convertDateTime(std::string date, std::string time) {
    int yyyy,mon, dd =0;
    //The sscanf function is a C library function that reads formatted input from a string.
    // c_str() is used to convert the date string to a C-style string, which can be used as the input to sscanf
    if(sscanf(date.c_str(), "%d_%d_%d", &yyyy,&mon, &dd)!=3){
        // If the function returns a value other than 3, it means that the date string was not formatted correctly,
        // and an error message is printed to the console before the function returns -1.
        cerr << "ERROR: Failed to parse date string "<<date<<endl;
        return -1;
    }
    int hh,mm, ss =0;
    if(sscanf(time.c_str(), "%d:%d:%d", &hh,&mm, &ss)!=3){
        cerr << "ERROR: Failed to parse date string "<<date<<endl;
        return -2;
    }
    //struct tm is a C structure defined in the header file <time.h>,
    // which contains the components of a calendar
    // date and time broken down into its individual components.
    struct tm dateTime={};
    dateTime.tm_year = yyyy -1990;
    dateTime.tm_mon = mon -1;
    dateTime.tm_mday = dd;
    dateTime.tm_hour = hh;
    dateTime.tm_min = mm;
    dateTime.tm_sec= ss;
    // return a time_t value representing seconds since 1970
    return mktime(&dateTime);
}

WeatherDataAnalysis::WeatherDataAnalysis() {loadData();}

bool WeatherDataAnalysis::isValidDateTime(std::string date, std::string time) {
    time_t dateTime = convertDateTime(date,time);
    if(dateTime<0){return false;} // failure to parse date/time
    if ((dateTime < getFirstDateTime())||dateTime> getLastDateTime()){
        cerr << "ERROR: "<< date << " " << time<< " " << " is outside available data range"<<endl;
        return false;
    }
    return true;
}

double WeatherDataAnalysis::computeCoeff(std::string startDate, std::string startTime, std::string endDate,
                                         std::string endTime) {
    time_t startDateTime = convertDateTime(startDate,startTime);
    time_t endDateTime = convertDateTime(endDate, endTime);
    if(endDateTime < startDateTime){
        //error messages are often time-sensitive and need to be displayed
        // immediately to inform the user of a problem, using cerr ensures that the
        // error message is displayed right away and not buffered.
        cerr << "ERROR: The start date/time must occur before the end date/time" << endl;
        exit(1);
    }

    // find iterators based on input range
    map<time_t,double>::iterator startTimePressure;
    map<time_t,double>::iterator endTimePressure;
    startTimePressure = timeToPressure_.lower_bound(startDateTime);
    endTimePressure = timeToPressure_.lower_bound(endDateTime);
    double timeDiff = endTimePressure->first - startTimePressure->first;
    double pressureDiff = endTimePressure->second - startTimePressure->second;
    // calculate and return slope
    return (pressureDiff)/(timeDiff);
}
