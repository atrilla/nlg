/*
     ____  _____    _____         ______
    |_   \|_   _|  |_   _|      .' ___  |
      |   \ | |      | |       / .'   \_|
      | |\ \| |      | |   _   | |    ____
     _| |_\   |_    _| |__/ |  \ `.___]  _|
 ___|     |\_   |__|        |___'.      |_______________________________
|                                                                      |\
|                                                                      |_\
|   File    : generator.cpp                                               |
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
#include <map>
#include <boost/tokenizer.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace boost;

generator::generator() {
    order = 0;
    srand(time(0));
    rc = rand() % 50;
}

generator::generator(int ord) {
    order = ord;
    srand(time(0));
    rc = rand() % 50;
}

void generator::setOrder(int ord) {
    order = ord;
}

int generator::getOrder() const {
    return order;
}

void generator::feed(const string &food) {
    string theFood = food;
    vector<string> frame(order, RESERVED_TAG_START);
    theFood += " " + RESERVED_TAG_END;
    tokenizer<> tok(theFood);
    for(tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); beg++) {
        for (int framec = 1; framec < order; framec++) {
            frame[framec - 1] = frame[framec];
        }
        frame[order - 1] = *beg;
        ngram ngframe(frame);
        freq[ngframe]++;
    }
}

string generator::predict(const ngram &hist) {
    map<ngram, int> workingMap;
    if (order > 1) {
        map<ngram, int> submap(lower(hist), upper(hist));
        if (submap.empty()) {
            workingMap = freq;
        } else {
            workingMap = submap;
        }
    } else {
        workingMap = freq;
    }
    string prediction;
    map<ngram, int>::iterator vocabit;
    int totalc = 0;
    for (vocabit = workingMap.begin();
            vocabit != workingMap.end(); vocabit++) {
        totalc += vocabit->second;
        vocabit->second = totalc;
    }
    int choice = (randNum() % totalc) + 1;
    ngram ngChoice;
    for (vocabit = workingMap.begin();
            vocabit != workingMap.end(); vocabit++) {
        if (choice > vocabit->second) {
            continue;
        } else {
            prediction = (vocabit->first).getGram(order - 1);
            break;
        }
    }
    return prediction;
}

string generator::produce() {
    vector<string> frame(order - 1, RESERVED_TAG_START);
    if (order == 1) {
        frame.push_back(RESERVED_TAG_START);
    }
    ngram ngprod(frame);
    string p = predict(ngprod);
    if (p == RESERVED_TAG_END) {
        p = "(blank)";
        return p;
    }
    string production = p;
    for (int epoch = 0; epoch < 100; epoch++) {
        if (order > 1) {
            for (int framec = 1; framec < order - 1; framec++) {
                frame[framec - 1] = frame[framec];
            }
            frame[order - 2] = p;
        }
        ngprod = ngram(frame);
        p = predict(ngprod);
        if (p == RESERVED_TAG_END) {
            break;
        } else {
            production += " " + p;
        }
    }
    return production;
}

map<ngram, int>::const_iterator generator::lower (const ngram& ng) const {
    return freq.lower_bound(ng);
}

// map's upper_bound doesn't work right with these n-grams, rats
map<ngram, int>::const_iterator generator::upper (const ngram& ng) const {
    map<ngram, int>::const_iterator it;
    for (it = freq.begin(); it != freq.end(); it++) {
        if (it->first > ng) {
            break;
        }
    }
    return it;
}

int generator::randNum() {
    rc = (rc + 1) % 50;
    return randy[rc];
}

