#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class HMIScreen
{
    vector<string> dynamicWidges;
    set<string> staticWidges;
    vector<string> combinedWidges;
public:
    HMIScreen() {
        dynamicWidges.push_back("Speedometer");
        dynamicWidges.push_back("Tacometer");
        dynamicWidges.push_back("Odometer");
        dynamicWidges.push_back("FuelGuage");
        dynamicWidges.push_back("EngineTempGauge");
        staticWidges.insert("Logo");
        staticWidges.insert("WarningLights");
        staticWidges.insert("SeatBeltWarning");
        staticWidges.insert("DrivingModeIndicator");
        staticWidges.insert("TurnSignalIndicator");
    }

    void printAllDynamicWidges()
    {
        auto it = dynamicWidges.begin();
        cout << "All the dynamic widgets are :" << endl;
        while (it != dynamicWidges.end()) {
            cout << *it << endl;
            it++;
        }
        cout << endl;
    }

    void findStaticWidge(string widge)
    {
        auto desiredWidge = staticWidges.find(widge);
        if (desiredWidge != staticWidges.end()) {
            cout << widge << " found in widgets" << endl;
        }
        else {
            cout << widge << " not found in widgets " << endl;
        }
    }

    void findInCombinedWidges(string widge)
    {
        combinedWidges.clear(); // Clear the combined widgets before adding new data
        copy(dynamicWidges.begin(), dynamicWidges.end(), back_inserter(combinedWidges));
        copy(staticWidges.begin(), staticWidges.end(), back_inserter(combinedWidges));

        auto desiredWidge = find(combinedWidges.begin(), combinedWidges.end(), widge);
        if (desiredWidge != combinedWidges.end()) {
            cout << widge << " Widget found at location " << desiredWidge - combinedWidges.begin() << endl;
        }
        else {
            cout << widge << " Widget not found" << endl;
        }
    }
};

int main()
{
    HMIScreen hmiScreen;
    hmiScreen.printAllDynamicWidges(); // Prints all dynamic widgets
    hmiScreen.findStaticWidge("SeatBeltWarning"); // Find if desired widget is present or not
    hmiScreen.findInCombinedWidges("TurnSignalIndicator"); // Find location of a widget in combined widgets

    return 0;
}
