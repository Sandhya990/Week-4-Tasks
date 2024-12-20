#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Define the Control structure
struct Control {
    int id;             // Unique ID for the control
    string type;        // "button" or "slider"
    string state;       // "visible", "invisible", or "disable"

    // Function to print control details
    void details() {
        cout << "Id->" << id << ", Type->" << type << ", State->" << state << endl;
    }
};

// ControlsSystem class encapsulates all operations related to controls
class ControlsSystem {
    vector<Control> controls; // Container for all controls

public:
    // Builds sample controls
    void buildControls() {
        controls.emplace_back(Control{ 1, "button", "visible" });
        controls.emplace_back(Control{ 2, "slider", "visible" });
        controls.emplace_back(Control{ 3, "button", "disable" });
        controls.emplace_back(Control{ 4, "slider", "visible" });
        controls.emplace_back(Control{ 5, "slider", "invisible" });
        controls.emplace_back(Control{ 6, "button", "visible" });
        controls.emplace_back(Control{ 7, "slider", "invisible" });
        controls.emplace_back(Control{ 8, "button", "disable" });
        controls.emplace_back(Control{ 9, "slider", "disable" });
        controls.emplace_back(Control{ 10, "button", "invisible" });
    }

    // Prints all controls in the system
    void getAllControls() {
        if (controls.empty()) {
            cout << "No controls available in the system.\n";
            return;
        }
        cout << "Controllers are:\n";
        for (Control& control : controls) {
            control.details();
        }
    }

    // Gets details of a control by ID
    void getDetailsForId(int id) {
        auto targetControl = find_if(controls.begin(), controls.end(),
            [id](Control& c) { return c.id == id; });
        if (targetControl != controls.end()) {
            cout << "Id " << id << " control details are: ";
            targetControl->details();
        }
        else {
            cout << "Id " << id << " not found in controls.\n";
        }
    }

    // Finds the first invisible control
    void getFirstInvisibleControl() {
        auto firstInvisibleControl = find_if(controls.begin(), controls.end(),
            [](Control& c) { return c.state == "invisible"; });
        if (firstInvisibleControl != controls.end()) {
            cout << "First invisible control details are: ";
            firstInvisibleControl->details();
        }
        else {
            cout << "No invisible control is present in the system.\n";
        }
    }

    // Finds and prints adjacent controls with the same state
    void findIfAdjacentStateAreEqual() {
        auto adjacentStates = adjacent_find(controls.begin(), controls.end(),
            [](Control& c1, Control& c2) { return c1.state == c2.state; });
        if (adjacentStates != controls.end()) {
            cout << "First adjacent pair with the same state are:\n";
            adjacentStates->details();
            (adjacentStates + 1)->details();
        }
        else {
            cout << "No adjacent controls with the same state found.\n";
        }
    }

    // Counts the number of visible controls
    int countVisibleControls() {
        return count_if(controls.begin(), controls.end(),
            [](Control& c) { return c.state == "visible"; });
    }

    // Counts the number of disabled sliders
    int countDisabledSliders() {
        return count_if(controls.begin(), controls.end(),
            [](Control& c) { return c.type == "slider" && c.state == "disable"; });
    }
};

int main() {
    ControlsSystem c;

    c.buildControls(); // Builds all the controls

    cout << "All Controls:\n";
    c.getAllControls(); // Prints all the controls

    cout << "\nFinding the first invisible control:\n";
    c.getFirstInvisibleControl(); // Finds the first occurrence of an invisible control

    cout << "\nGetting details for ID 7:\n";
    c.getDetailsForId(7); // Gets the details of a control with ID 7

    cout << "\nTrying to get details for a non-existent ID 18:\n";
    c.getDetailsForId(18); // Handles case when ID is not found

    cout << "\nFinding adjacent controls with the same state:\n";
    c.findIfAdjacentStateAreEqual(); // Finds adjacent controls with the same state

    cout << "\nCount of visible controls: " << c.countVisibleControls() << endl;
    cout << "Count of disabled sliders: " << c.countDisabledSliders() << endl;

    return 0;
}
