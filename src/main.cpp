/*
     ____  _____    _____         ______
    |_   \|_   _|  |_   _|      .' ___  |
      |   \ | |      | |       / .'   \_|
      | |\ \| |      | |   _   | |    ____
     _| |_\   |_    _| |__/ |  \ `.___]  _|
 ___|     |\_   |__|        |___'.      |_______________________________
|                                                                      |\
|                                                                      |_\
|   File    : main.cpp                                                    |
|   Created : 30-Oct-2011                                                 |
|   By      : atrilla                                                     |
|                                                                         |
|   NLG - Natural Language Generator based on n-gram Language Models      |
|                                                                         |
|   Copyright (c) 2011 Alexandre Trilla                                   |
|                                                                         |
|   -------------------------------------------------------------------   |
|                                                                         |
|   This file is part of NLG.                                             |
|                                                                         |
|   NLG is free software: you can redistribute it and/or modify it under  |
|   the terms of the MIT/X11 License as published by the Massachusetts    |
|   Institute of Technology. See the MIT/X11 License for more details.    |
|                                                                         |
|   You should have received a copy of the MIT/X11 License along with     |
|   this source code distribution of NLG (see the COPYING                 |
|   file in the root directory). If not, see                              |
|   <http://www.opensource.org/licenses/mit-license>.                     |
|________________________________________________________________________*/

#include "generator.hpp"
#include "ngram.hpp"
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

map<string, string> getOptionMap(int argc, const char* argv[]) {
    map<string, string> optMap;
    if (((argc - 1) % 2) == 0) {
        for (int optc = 1; optc < argc; optc += 2) {
            optMap[argv[optc]] = argv[optc + 1];
        }
    }
    return optMap;
}

void printSynopsis() {
    cout << endl;
    cout << "n-gram-based Natural Language Generator" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Usage: nlg PARAMETERS" << endl;
    cout << "\t-n ORDER: the order of the language model." << endl;
    cout << "\t-t FILE: the training file." << endl;
    cout << endl;
    cout << "Then, nlg will yield one output at a time." << endl << endl;
}

int main(int argc, const char* argv[]) {
    if (argc == 5) {
        map<string, string> opts = getOptionMap(argc, argv);
        generator gen(atoi(opts["-n"].c_str()));
        ifstream training(opts["-t"].c_str());
        if (!training.good()) {
            cout << "Bad training file!" << endl;
            return EXIT_FAILURE;
        }
        string line;
        getline(training, line);
        while (!training.eof()) {
            gen.feed(line);
            getline(training, line);
        }
        training.close();
        line = "y";
        while (line != "n") {
            cout << gen.produce() << endl;
            cout << "More (y/n)? ";
            cin >> line;
        }
        cout << "Bye!" << endl;
    } else if ((argc == 2) && !strcmp(argv[1], "-h")) {
        printSynopsis();
    } else {
        cout << "Wrong number of arguments!" << endl;
        printSynopsis();
    }
    return EXIT_SUCCESS;
}

