#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct Control {
    int id;
    string name;

    // Overload the < operator for sorting
    bool operator<(const Control& other) const {
        return id < other.id;
    }
};

// Function to print the controls
void printControls(const vector<Control>& controls) {
    for (const auto& control : controls) {
        cout << "ID: " << control.id << ", Name: " << control.name << endl;
    }
}

int main() {
    // Sample lists of controls
    vector<Control> controls1 = { {3, "Button1"}, {1, "Button2"}, {2, "Button3"}, {2, "Button4"} };
    vector<Control> controls2 = { {5, "Button5"}, {4, "Button6"}, {6, "Button7"}, {1, "Button8"} };

    // Step 1: Sort controls by ID using std::stable_sort
    stable_sort(controls1.begin(), controls1.end());
    stable_sort(controls2.begin(), controls2.end());

    cout << "Sorted Controls 1--> using std::stable_sort:" << endl;
    printControls(controls1);
    cout << endl;

    cout << "Sorted Controls 2--> using std::stable_sort:" << endl;
    printControls(controls2);
    cout << endl;

    // Step 2: Binary Search for a control by ID
    int searchId = 2;
    auto lower = lower_bound(controls1.begin(), controls1.end(), Control{ searchId, "" });
    auto upper = upper_bound(controls1.begin(), controls1.end(), Control{ searchId, "" });

    cout << "Searching for ID: " << searchId << endl;
    if (lower != upper) {
        cout << "Found Controls with ID " << searchId << ":" << endl;
        for (auto it = lower; it != upper; ++it) {
            cout << "ID: " << it->id << ", Name: " << it->name << endl;
        }
    }
    else {
        cout << "No Controls found with ID " << searchId << endl;
    }

    // Step 3: Merging two sorted lists of controls
    vector<Control> mergedControls(controls1.size() + controls2.size());
    merge(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(), mergedControls.begin());

    cout << endl;

    cout << "Merged Controls:" << endl;
    printControls(mergedControls);
    cout << endl;

    // Step 4: In-place merge (assuming we have two segments in the same vector)
    vector<Control> controls3 = { {1, "ButtonA"}, {3, "ButtonB"}, {2, "ButtonC"}, {4, "ButtonD"} };
    stable_sort(controls3.begin(), controls3.begin() + 2); // Sort first half
    stable_sort(controls3.begin() + 2, controls3.end()); // Sort second half

    cout << "Controls before in-place merge:" << endl;
    printControls(controls3);
    inplace_merge(controls3.begin(), controls3.begin() + 2, controls3.end());
    cout << endl;

    cout << "Controls after in-place merge:" << endl;
    printControls(controls3);
    cout << endl;

    // Step 5: Set operations (union and intersection)
    vector<Control> uniqueControls;
    vector<Control> intersectionControls;

    set_union(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(),
        back_inserter(uniqueControls));
    cout << "Unique Controls (Union):" << endl;
    printControls(uniqueControls);
    cout << endl;

    set_intersection(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(),
        back_inserter(intersectionControls));
    cout << "Common Controls (Intersection):" << endl;
    printControls(intersectionControls);

    return 0;
}