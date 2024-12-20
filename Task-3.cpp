#include <iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
struct Control
{
    int id;
    string type;
    string state;

    void details()
    {
        cout << "Id->" << id << ", Type->" << type << ", State->" << state << endl;
    }
};

class ControlsSystem
{

    vector<Control> controls;
    vector<Control> duplicateControls;

public:
    // builds all the controls
    ControlsSystem()
    {
        Control c1 = { 1,"button","visible" };
        Control c2 = { 2,"slider","visible" };
        Control c3 = { 3,"button","disable" };
        Control c4 = { 4,"slider","visible" };
        Control c5 = { 5,"slider","invisible" };
        Control c6 = { 6,"button","visible" };
        Control c7 = { 7,"slider","invisible" };
        Control c8 = { 8,"button","disable" };
        Control c9 = { 9,"slider","disable" };
        Control c10 = { 10,"button","invisible" };

        controls.push_back(c1);
        controls.push_back(c2);
        controls.push_back(c3);
        controls.push_back(c4);
        controls.push_back(c5);
        controls.push_back(c6);
        controls.push_back(c7);
        controls.push_back(c8);
        controls.push_back(c9);
        controls.push_back(c10);

    }


    void manupulateControls()
    {
        copy(controls.begin(), controls.end(), back_inserter(duplicateControls));
    }


    // prints all the controls in the system
    void getAllControls()
    {
        cout << "Controllers are : " << endl;
        for (Control control : duplicateControls)
        {
            control.details();
        }
    }

    // converted all control states to disable
    void convertAllToDisable() {
        vector<Control> disableControls;

        copy(duplicateControls.begin(), duplicateControls.end(), back_inserter(disableControls));

        cout << "\nconverted all control states to disable" << endl;
        for_each(disableControls.begin(), disableControls.end(), [](Control& c) {return c.state = "disable"; });

        for (auto control : disableControls)
        {
            control.details();
        }
    }


    //transform to change the state of all sliders to "invisible".
    void change_all_sliders_to_invisible()
    {
        cout << "\nchanged all sliders to invisible :" << endl;
        vector<Control> transformedControls;
        transform(duplicateControls.begin(), duplicateControls.end(), back_inserter(transformedControls),
            [](Control& c)
            {
                if (c.type == "slider")
                {
                    c.state = "invisible";
                }
                return c;
            }
        );

        for (auto control : transformedControls)
        {
            if (control.type == "slider") {
                control.details();
            }

        }
    }


    //:replace to replace "disabled" with "enabled" for testing.
    void replace_disable_to_enable()
    {
        vector<Control> enableControls;
        copy(duplicateControls.begin(), duplicateControls.end(), back_inserter(enableControls));
        cout << "\nreplaced all  disabled states with enabled " << endl;
        for_each(enableControls.begin(), enableControls.end(), [](Control& c) {
            if (c.state == "disable") {
                c.state = "enable";
            }
            });

        for (auto control : enableControls)
        {
            control.details();
        }

    }

    //remove_if to filter out invisible controls from the list.
    void remove_invisible_controls()
    {
        cout << "\natfter removing invisible controls " << endl;
        vector<Control> non_invisibleControls;
        copy(duplicateControls.begin(), duplicateControls.end(), back_inserter(non_invisibleControls));
        non_invisibleControls.erase(
            remove_if(non_invisibleControls.begin(), non_invisibleControls.end(),
                [](const Control& c) { return c.state == "invisible"; }),
            non_invisibleControls.end());

        for (auto control : non_invisibleControls)
        {
            control.details();
        }

    }

    // :partition to group visible controls together.
    void partition_visible_controls()
    {
        cout << "\npartition the visible controls " << endl;
        vector<Control> partitionControls;
        copy(duplicateControls.begin(), duplicateControls.end(), back_inserter(partitionControls));

        partition(partitionControls.begin(), partitionControls.end(), [](const Control& c) {return c.state == "visible"; });
        for (auto control : partitionControls) {
            control.details();
        }
    }



};

int main()
{


    ControlsSystem c; // builds all the controls


    c.manupulateControls();// prints all the controls
    c.getAllControls();
    c.replace_disable_to_enable(); //:replace to replace "disabled" with "enabled" for testing.
    c.convertAllToDisable();// converted all control states to disable
    c.change_all_sliders_to_invisible();  //transform to change the state of all sliders to "invisible".
    c.remove_invisible_controls();    //remove_if to filter out invisible controls from the list.
    c.partition_visible_controls();// :partition to group visible controls together.

    return 0;
}