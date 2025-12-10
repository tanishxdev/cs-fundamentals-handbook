// temperature_converter.cpp
#include <iostream>
#include <iomanip>
using namespace std;

/*
    Function: convertTemperature
    Purpose : Converts temperature from one unit to another
    Params  :
        value    -> input temperature
        fromUnit -> source unit (C / F / K)
        toUnit   -> target unit (C / F / K)
    Return :
        Converted temperature
*/

double convertTemperature(double value, char fromUnit, char toUnit) {
    double tempInCelsius;

    // Step 1: Convert source to Celsius
    if (fromUnit == 'C') {
        tempInCelsius = value;
    }
    else if (fromUnit == 'F') {
        tempInCelsius = (value - 32) * 5.0 / 9.0;
    }
    else if (fromUnit == 'K') {
        tempInCelsius = value - 273.15;
    }
    else {
        cout << "Invalid source unit!" << endl;
        return -1;
    }

    // Step 2: Convert Celsius to target unit
    if (toUnit == 'C') {
        return tempInCelsius;
    }
    else if (toUnit == 'F') {
        return (tempInCelsius * 9.0 / 5.0) + 32;
    }
    else if (toUnit == 'K') {
        return tempInCelsius + 273.15;
    }
    else {
        cout << "Invalid target unit!" << endl;
        return -1;
    }
}

int main() {
    double value;
    char fromUnit, toUnit;

    cout << "===== Temperature Conversion System =====" << endl;

    cout << "Enter temperature value: \n";
    cin >> value;
    cout << "Entered temperature value: " << value << "\n";

    cout << "Enter source unit (C/F/K): \n";
    cin >> fromUnit;
    cout << "Entered source unit (C/F/K): " << fromUnit << " \n";

    cout << "Enter target unit (C/F/K): \n";
    cin >> toUnit;
    cout << "Entered target unit (C/F/K): " << toUnit << "\n";

    double result = convertTemperature(value, fromUnit, toUnit);

    if (result != -1) {
        cout << fixed << setprecision(2);
        cout << "Converted Temperature: " << result << " " << toUnit << endl;
    }

    return 0;
}
