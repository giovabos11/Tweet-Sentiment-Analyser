#include <iostream>

#include "Classifier.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;

int run(const char*, const char*, const char*, const char*);

int main(int argc, char** argv) {
    // Test DSString with CATCH if no extra arguments
    if (argc == 1) {
        return Catch::Session().run();
    }
    // Otherwise, run program
    return run(argv[1], argv[2], argv[3], argv[4]);
}

int run(const char* arg1, const char* arg2, const char* arg3, const char* arg4) {
    // Create a new instance of classifier
    Classifier c;

    /** TRAIN PHASE **/

    cout << "Training..." << endl;

    c.readTrainFile(arg1);

    cout << "Training completed!" << endl;

    /** TEST PHASE **/

    cout << "Testing..." << endl;

    c.readDataFile(arg2);

    cout << "Testing completed!" << endl;

    /** CALCULATE ACCURACY AND REPORT **/

    cout << "Calculating accuracy..." << endl;

    c.accuracy(arg3);

    cout << "Accuracy calculated! ("  << c.getAccuracy() << ")" << endl;

    cout << "Writing results to output file..." << endl;

    c.report(arg4);

    cout << "Output file successfully created!" << endl;

    return 0;
}