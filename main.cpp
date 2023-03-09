#include <iostream>
#include <string>
# include "WeatherDataAnalysis.h"

using namespace std;
int main() {
    WeatherDataAnalysis stats;
    // request start date/time from user#
    string startDate, startTime;
    cout << endl << "Enter START DATE as yyyy_mm_dd: ";
    cin >> startDate;
    cout << "Enter START TIME as hh:mm:ss (24-hour): ";
    cin >> startTime;
    if (!stats.isValidDateTime(startDate,startTime)){return 1;}
    // request end date/time from user
    string endDate, endTime;
    cout << "Enter END DATE as yyyy_mm_dd: ";
    cin >> endDate;
    cout << "Enter END TIME as hh:mm:ss (24-hour): ";
    cin >> endTime;
    if (!stats.isValidDateTime(endDate, endTime)){return 1;}
    double coefficient = stats.computeCoeff(startDate,startTime,endDate,endTime);
    cout << endl << "Coefficient: " << coefficient * 24 * 60 * 60 << " inHg/day" << endl;
    return 0;
}
