#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

// Define the structure
struct MyStruct {
    int variable1;
    float variable2;
    char variable3;
};

int main() {
    MyStruct data; // Create an instance of the structure

    while (true) {
        // Populate the structure with some example data
        data.variable1 = 42;
        data.variable2 = 3.14;
        data.variable3 = 'A';

        // Get the current time
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char filename[100];
        sprintf(filename, "./output/output_%04d-%02d-%02d_%02d-%02d-%02d.txt", 
                1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, 
                ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

        // Open the file for writing
        ofstream outputFile(filename);

        // Check if the file opened successfully
        if (!outputFile) {
            cerr << "Error opening file: " << filename << endl;
            return 1;
        }

        // Write the structure data to the file
        outputFile << "Variable 1: " << data.variable1 << endl;
        outputFile << "Variable 2: " << data.variable2 << endl;
        outputFile << "Variable 3: " << data.variable3 << endl;

        // Close the file
        outputFile.close();

        // Sleep for ten seconds, better stead of sleep(10)
        this_thread::sleep_for(chrono::seconds(10));
    }

    return 0;
}
