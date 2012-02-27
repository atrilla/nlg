/*
     ____  _____    _____         ______
    |_   \|_   _|  |_   _|      .' ___  |
      |   \ | |      | |       / .'   \_|
      | |\ \| |      | |   _   | |    ____
     _| |_\   |_    _| |__/ |  \ `.___]  _|
 ___|     |\_   |__|        |___'.      |_______________________________
|                                                                      |\
|                                                                      |_\
|   File    : ngram.cpp                                                   |
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

#include "ngram.hpp"
#include <string>
#include <vector>

using namespace std;

ngram::ngram() {
}

ngram::ngram(const vector<string> &grams) {
    gram = grams;
}

bool ngram::operator==(const ngram &ng) const {
    return testEqual(ng);
}

bool ngram::operator!=(const ngram &ng) const {
    return !testEqual(ng);
}

bool ngram::operator<(const ngram &ng) const {
    return testLesser(ng);
}

bool ngram::operator<=(const ngram &ng) const {
    return (testLesser(ng) || testEqual(ng));
}

bool ngram::operator>(const ngram &ng) const {
    return ((!testLesser(ng)) && (!testEqual(ng)));
}

bool ngram::operator>=(const ngram &ng) const  {
    return !testLesser(ng);
}

string ngram::getGram(int pos) const {
    return (string)gram[pos];
}

const vector<string>* ngram::getGramList() const {
    return &gram;
}

int ngram::getOrder() const {
    return (int)gram.size();
}

bool ngram::operator() (const ngram& first, const ngram& second) const {
    return first < second;
}

bool ngram::testEqual(const ngram &ng) const  {
    bool equal = true;
    vector<string>::const_iterator it, it_own;
    const vector<string> *testNg = ng.getGramList();
    for (it = testNg->begin(), it_own = gram.begin(); 
            (it != testNg->end()) && (it_own != gram.end());
            it++, it_own++) {
        if (*it_own != *it) {
            equal = false;
            break;
        }
    }
    return equal;
}

bool ngram::testLesser(const ngram &ng) const {
    bool lesser = true;
    vector<string>::const_iterator it, it_own;
    const vector<string> *testNg = ng.getGramList();
    for (it = testNg->begin(), it_own = gram.begin(); 
            (it != testNg->end()) && (it_own != gram.end());
            it++, it_own++) {
        if (*it_own > *it) {
            lesser = false;
            break;
        } else if ((*it_own == *it) && 
                ((it + 1) != testNg->end())) {
            continue;
        } else if ((*it_own == *it) && 
                ((it + 1) == testNg->end())) {
            lesser = false;
            break;
        } else {
            break;
        }
    }
    return lesser;
}

