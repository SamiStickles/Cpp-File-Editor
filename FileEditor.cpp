#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// creates a new file with specified name and number of lines
void createFile(string file_name, int num_lines)
{
    ofstream myfile(file_name);

    if (myfile.is_open())
    {
        // prints "blank line 1" with line number on all lines in file
        for (int i = 1; i <= num_lines; i++)
        {
            myfile << "blank line " << i << '\n';
        }
        myfile.close();
    }
}

// reads and prints whole file line by line using getline
void readFile(string file_name)
{
    string eachline;
    ifstream myfile(file_name);

    if (myfile.is_open())
    {
        // getline is used as while loop parameter, so the action is performed on each line in myfile
        while (getline(myfile, eachline))
        {
            cout << eachline << '\n';
        }
    }
    else
        cout << "error: file is not open\n";
    myfile.close();
}

// goes through all lines of a specified file and can edit any in order of appearance
void editFile(string file_name)
{
    ifstream myfile(file_name);
    ofstream myfile_edit("editfile.txt");
    
    // response changes to y/n on user input and back to a between loops
    char response = 'a';
    string newline;
    string eachline;

    if (myfile.is_open())
    {
        // read each line and decide whether to edit or not
        // after editing or not, write the line to the new file
        // delete the old file and rename the new file to the old one's name
        while (getline(myfile, eachline))
        {
            cout << eachline << '\n';
            // newline is changed each iteration to the current line, then edited below if chosen
            newline = eachline;

            while (response != 'y' && response != 'n')
            {
                cout << "Do you want to edit this line? (y/n) ";
                cin >> response;
            }
            if (response == 'y')
            {
                cout << "Enter the new line: ";
                cin.ignore();
                // getline here allows the user to enter multiple words into the input stream as one input
                getline(cin, newline);
            }
            // set response back to a to allow new response in loop
            response = 'a';
            // add the line to the new file
            myfile_edit << newline << '\n';
        }
        // close both files, delete old and rename new
        myfile.close();
        myfile_edit.close();
        remove(file_name.c_str());
        rename("editfile.txt", file_name.c_str());
    }
    else
        cout << "error: file is not open\n";
}

// tries to delete the specified file
void deleteFile(string file_name)
{
    // remove method equals 0 if successful, so we check that here
    if (remove(file_name.c_str()) == 0)
        cout << "File has been deleted.\n";
    else
        cout << "Deletion failed. File has not been deleted.\n";
}

int main()
{
    string file_input;
    int lines_input;
    // response changes to an action depending on input, then back to none between inputs
    string response = "none";

    // while loops stays open until user types exit in the menu
    while (true)
    {
        cout << "What do you want to do? (create, read, edit, del, exit) ";
        cin >> response;
        // use clear and ignore to clear the stream of any stray new lines or other characters
        cin.clear();
        cin.ignore();

        // performs the chosen action, if user enters an input that is not an option, loop restarts and asks again
        if (response == "create") {
            cout << "Name of file that you want to create: ";
            cin >> file_input;
            cout << "Number of lines to make the file: ";
            cin >> lines_input;
            createFile(file_input, lines_input);
        }
        else if (response == "read") {
            cout << "Name of file that you want to read: ";
            cin >> file_input;
            readFile(file_input);
        }
        else if (response == "edit") {
            cout << "Name of file that you want to edit: ";
            cin >> file_input;
            editFile(file_input);
        }
        else if (response == "del") {
            cout << "Name of file that you want to delete: ";
            cin >> (file_input);
            deleteFile(file_input);
        }
        else if (response == "exit") {
            cout << "Ok. Exiting program.";
            return 1;
        }
        else {
            cout << "You did not pick a valid option.\n";
        }
        // set response to none to allow loop to repeat input
        response = "none";
    }
}