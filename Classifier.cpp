//
// Created by giova on 2/4/2022.
//

#include "Classifier.h"

Classifier::Classifier() {}

void Classifier::readTrainFile(const char* trainFile) {
    // Declare input file buffer
    ifstream inputFile;
    // Declare variable buffers
    char meta[40];
    char sentiment[3];
    char id[15];
    char date[35];
    char query[10];
    char user[40];
    char tweet[300];

    // Open train file
    inputFile.open(trainFile);

    // If input file opened correctly
    if (inputFile) {
        // Ignore first line
        inputFile.getline(meta, 1000);

        // Read until the end of the file
        while (!inputFile.eof()) {
            // Read each chunk of data
            inputFile.getline(sentiment, 3, ',');
            inputFile.getline(id, 15, ',');
            inputFile.getline(date, 35, ',');
            inputFile.getline(query, 10, ',');
            inputFile.getline(user, 40, ',');
            inputFile.getline(tweet, 300, '\n');

            // Train with the tweet data provided
            train(strtol(sentiment, NULL, 10), DSString(tweet));
        }
    }

    // Close input file
    inputFile.close();
}

void Classifier::train(int sentiment, DSString tweet) {
    bool flag = false;
    DSString currentToken;
    Token newToken;
    char* tokenPointer;

    // Clean tweet
    tweet.toLower();
    tweet.clean();

    // Strip first token
    tokenPointer = strtok(tweet.c_str()," ");

    // While there are tokens inside the tweet
    while(tokenPointer != NULL) {
        // Store token read into a DSString
        currentToken = tokenPointer;

        // Check if current token is not empty
        if (currentToken.getLength() > 0 && currentToken.c_str() != nullptr) {
            // Search if repeated
            for (int i = 0; i < tokens.size() && !flag; i++) {
                // If token is repeated
                if (tokens[i].key == currentToken) {
                    // Add one point to corresponding sentiment value
                    if (sentiment == 4) {
                        tokens[i].positiveVal++;
                    } else if (sentiment == 0) {
                        tokens[i].negativeVal++;
                    }
                    flag = true;
                }
            }

            // Add to tokens if new token
            if (!flag) {
                newToken.key = currentToken;
                if (sentiment == 4) {
                    newToken.positiveVal = 1;
                } else if (sentiment == 0) {
                    newToken.negativeVal = 1;
                }
                tokens.push_back(newToken);
            }
        }

        // Read next token
        tokenPointer = strtok (NULL, " ");
    }
}

void Classifier::readDataFile(const char* dataFile) {
    // Declare input file buffer
    ifstream inputFile;
    // Declare variable buffers
    char meta[40];
    char id[15];
    char date[35];
    char query[10];
    char user[40];
    char tweet[300];

    // Open data file
    inputFile.open(dataFile);

    // If input file opened correctly
    if (inputFile) {
        // Ignore first line
        inputFile.getline(meta, 100);

        // Read until the end of the file
        while (!inputFile.eof()) {
            // Read each chunk of data
            inputFile.getline(id, 15, ',');
            inputFile.getline(date, 35, ',');
            inputFile.getline(query, 10, ',');
            inputFile.getline(user, 40, ',');
            inputFile.getline(tweet, 300, '\n');

            // Analyze tweet and store it into tweets
            tweets.push_back(analyze(DSString(tweet), id));
        }
    }

    // Close input file
    inputFile.close();
}

Tweet Classifier::analyze(DSString tweet, const char* id) {
    bool flag = false;
    DSString currentToken;
    char* tokenPointer;
    double negativePoints = 0, positivePoints = 0;
    Tweet temp;

    // Clean tweet
    tweet.toLower();
    tweet.clean();

    // Strip first token
    tokenPointer = strtok(tweet.c_str()," ");

    // While there are tokens inside the tweet
    while(tokenPointer != NULL) {
        // Store token read into a DSString
        currentToken = tokenPointer;

        // Check if current token is not empty
        if (currentToken.getLength() > 0 && currentToken.c_str() != nullptr) {
            // Search for similar tokens
            for (int i = 0; i < tokens.size() && !flag; i++) {
                // If token is found
                if (tokens[i].key == currentToken) {
                    // Add points to negative and positive sentiments
                    // based on the token values
                    positivePoints += tokens[i].positiveVal;
                    negativePoints += tokens[i].negativeVal;

                    flag = true;
                }
            }
        }

        // Read next token
        tokenPointer = strtok (NULL, " ");
    }

    // Store tweet information into a temporal variable
    temp.id = id;
    // If positive points is greater than or equal to
    // negative points, the tweet should be positive
    if (positivePoints >= negativePoints) {
        temp.sentiment = 4;
    }
    // Otherwise, the tweet should be negative
    else {
        temp.sentiment = 0;
    }

    // Return temporary tweet
    return temp;
}

void Classifier::accuracy(const char* compareFile) {
    // Declare input file buffer
    ifstream inputFile;
    bool flag;
    int guessed = 0, total = 0;
    // Declare variable buffers
    char meta[40];
    char sentiment[3];
    char id[15];

    // Open data file
    inputFile.open(compareFile);

    // If input file opened correctly
    if (inputFile) {
        // Ignore first line
        inputFile.getline(meta, 1000);

        // Read until the end of the file
        while (!inputFile.eof()) {
            // Read each chunk of data
            inputFile.getline(sentiment, 3, ',');
            inputFile.getline(id, 15, '\n');

            // Find read tweet id in tweets
            for (int i = 0; i < tweets.size() && !flag; i++) {
                // If id's match
                if (tweets[i].id == id) {
                    // If sentiments match, increment guessed tweets counter
                    if (tweets[i].sentiment == strtol(sentiment, NULL, 10)) {
                        guessed++;
                    }
                    // Otherwise, just add tweet to bad classified tweets
                    else {
                        bad_tweets.push_back(tweets[i]);
                    }
                    flag = true;
                }
            }

            // Increment total count of tweets
            total++;

            flag = false;
        }
    }

    // Store accuracy value
    accuracyVal = guessed/static_cast<double>(total - 1);

    // Close input file
    inputFile.close();
}

void Classifier::report(const char* outputFileName) {
    // Declare output file buffer
    ofstream outputFile;

    // Create or overwrite the output file
    outputFile.open(outputFileName);

    // Write accuracy percentage
    outputFile << setprecision(3) << fixed << accuracyVal << endl;

    // Write each bad classified tweet id
    for (int i = 0; i < bad_tweets.size(); i++) {
        outputFile << bad_tweets[i].id << endl;
    }

    // Close output file
    outputFile.close();
}

double Classifier::getAccuracy() {
    // Return accuracy value
    return accuracyVal;
}