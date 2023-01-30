//
// Created by giova on 2/4/2022.
//

#ifndef CLASSIFIER_H_INCLUDED
#define CLASSIFIER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "Tweet.h"
#include "Token.h"

using namespace std;

class Classifier {
private:
    vector<Tweet> tweets;
    vector<Tweet> bad_tweets;
    vector<Token> tokens;
    double accuracyVal;

public:
    /**
     * Default constructor.
     * @return None.
     **/
    Classifier();

    /**
     * Reads the train data file and creates a list of tokens
     * based in the sentiment.
     * @return Void.
     **/
    void readTrainFile(const char*);
    /**
     * Assigns positive and negative values to each token in the
     * tweet based on the sentiment provided and stores the token
     * into the tokens list.
     * @return Void.
     **/
    void train(int, DSString);

    /**
     * Reads the data file, analyzes each tweet and stores the
     * analyzed tweets into the tweets list
     * @return Void.
     **/
    void readDataFile(const char*);
    /**
     * Tries to classify a tweet by sentiment based on the list of
     * tokens and its respective positive and negative values.
     * @return Tweet object.
     **/
    Tweet analyze(DSString, const char*);

    /**
     * Calculates the accuracy based on the classified tweets.
     * @return Void.
     **/
    void accuracy(const char*);

    /**
     * Creates an output file which reports the accuracy and the
     * bad classified tweets.
     * @return Void.
     **/
    void report(const char*);

    /**
     * Returns the accuracy value based on the classified tweets.
     * @return Double.
     **/
    double getAccuracy();
};

#endif // CLASSIFIER_H_INCLUDED

