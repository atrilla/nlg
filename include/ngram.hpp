/*
     ____  _____    _____         ______
    |_   \|_   _|  |_   _|      .' ___  |
      |   \ | |      | |       / .'   \_|
      | |\ \| |      | |   _   | |    ____
     _| |_\   |_    _| |__/ |  \ `.___]  _|
 ___|     |\_   |__|        |___'.      |_______________________________
|                                                                      |\
|                                                                      |_\
|   File    : ngram.hpp                                                   |
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

#ifndef NGRAM_HPP
#define NGRAM_HPP

#include <string>
#include <vector>

using namespace std;

/**
 * @class ngram
 * @brief Data structure to represent the observation of a sequence of
 *     <i>n</i> consecutive words: w_1, w_2, ..., w_n
 *
 * This class facilitates the integration of this atomic linguistic unit
 * into C/C++ STL containers. Regarding its comparison/relational 
 * operations, in case the lengths of the n-grams involved (i.e., their
 * orders) differ, only the oldest part of the n-gram histories is analysed 
 * (i.e., from w_1 to w_{min(orders)}).
 *
 * @author Alexandre Trilla (atrilla)
 */
class ngram {
    public:
        /**
         * @brief Plain empty constructor.
         */
        ngram();
        /**
         * @brief Parametric constructor that initialises the n-gram.
         * @param grams The sequence of words to initialise the n-gram.
         */
        ngram(const vector<string> &grams);
        /**
         * @brief Equal to operator.
         * @param ng N-gram to compare.
         * @return True if it is equal to the test n-gram.
         */
        bool operator==(const ngram &ng) const;
        /**
         * @brief Not equal to operator.
         * @param ng N-gram to compare.
         * @return True if it is different from the test n-gram.
         */
        bool operator!=(const ngram &ng) const;
        /**
         * @brief Less than operator.
         * @param ng N-gram to compare.
         * @return True if it is less than the test n-gram. If the oldest
         *     part of the history is equal, the decision is left to the
         *     newest part.
         */
        bool operator<(const ngram &ng) const;
        /**
         * @brief Less than or equal to operator.
         * @param ng N-gram to compare.
         * @return True if it is less than or equal to the test n-gram.
         */
        bool operator<=(const ngram &ng) const;
        /**
         * @brief Greater than operator.
         * @param ng N-gram to compare.
         * @return True if it is grater than the test n-gram.
         */
        bool operator>(const ngram &ng) const;
        /**
         * @brief Greater than or equal to operator.
         * @param ng N-gram to compare.
         * @return True if it is greater than or equal to the test n-gram.
         */
        bool operator>=(const ngram &ng) const;
        /**
         * @brief Retrieves a token from the n-gram.
         * @param pos The position of the desired token. Must not be
         *     greater than nor equal to the order of the n-gram.
         * @return The token in the given position.
         */
        string getGram(int pos) const;
        /**
         * @brief Retrieves the sequence of tokens of the n-gram.
         * @return The sequence of tokens.
         */
        const vector<string>* getGramList() const;
        /**
         * @brief Retrieves the order of the n-gram.
         * @return The order.
         */
        int getOrder() const;
        /**
         * @brief Indicates if the first given n-gram must be placed 
         *     before the second given n-gram in a container.
         * @param first The first given n-gram.
         * @param second The second given n-gram.
         * @return True if the first goes before the second.
         */
        bool operator() (const ngram& first, const ngram& second) const;
    private:
        /**
         * @brief The sequence of tokens.
         */
        vector<string> gram;
        /**
         * @brief Evaluates equality.
         * @param ng N-gram to compare.
         * @return True if it is equal to the test n-gram.
         */
        bool testEqual(const ngram &ng) const;
        /**
         * @brief Evaluates the less than relation.
         * @param ng N-gram to compare.
         * @return True if it is less than the test n-gram. If the oldest
         *     part of the history is equal, the decision is left to the
         *     newest part.
         */
        bool testLesser(const ngram &ng) const;
};

#endif

