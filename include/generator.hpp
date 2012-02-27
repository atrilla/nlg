/*
     ____  _____    _____         ______
    |_   \|_   _|  |_   _|      .' ___  |
      |   \ | |      | |       / .'   \_|
      | |\ \| |      | |   _   | |    ____
     _| |_\   |_    _| |__/ |  \ `.___]  _|
 ___|     |\_   |__|        |___'.      |_______________________________
|                                                                      |\
|                                                                      |_\
|   File    : generator.hpp                                               |
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

#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "ngram.hpp"
#include <string>
#include <map>

/**
 * @brief Indicates the beginning of a textual instance.
 */
const string RESERVED_TAG_START = "AAAA";
/**
 * @brief Indicates the ending of a textual instance.
 */
const string RESERVED_TAG_END = "zzzz";
/**
 * @brief Supplies some random numbers drawn from a uniform distribution
 *     from 0 to the maximum integer value in order not to mess with the
 *     platform-wise idiosyncrasies with random number generation.
 */
const int randy[50] = {24007, 17237, 12547, 24406, 21938, 18538, 10334,
    31370, 15283, 7463, 2714, 24380, 3774, 6057, 29072, 21206, 1851, 
    9831, 24220, 11472, 8849, 7888, 4993, 19550, 21141, 26953, 27759, 
    5661, 32236, 7830, 30515, 20316, 26174, 18856, 8649, 24022, 7273, 
    25320, 29441, 1509, 20651, 12697, 16980, 20068, 11642, 5454, 27040, 
    15743, 20593, 13896};

using namespace std;

/**
 * @class generator
 * @brief Keeps a record of the n-grams observed in the training data along
 *     with their frequency counts, and given a history of tokens, it 
 *     predicts the next token according to a uniform distribution over 
 *     the possible outcomes.
 *
 * From a frequentist point of view, the prediction task equation is
 * determined by the following ratio of n-gram counts:
 *
 * @image html mleeqngram.png "Probability estimate (MLE) of the prediction task as is described in Manning and Schutze (1999)."
 *
 * In general, though, Maximum Likelihood Estimation (MLE) is unsuitable
 * for statistical Natural Language Processing because of the sparseness
 * of the data. MLE assigns a zero probability to unseen events, and since
 * the probability of a whole text is generally computed by multiplying
 * the probabilities of subparts, these zeroes will propagate and give bad
 * estimates for the probability of long sentences. In case of having to
 * deal with an unseen event, NLG dodges this inconvenience by using a 
 * unigram Language Model (LM), aka Bag-Of-Words model, instead of 
 * smoothing all the probabilities.
 *
 * --<br>
 * [Manning and Schutze, 1999] Manning, C. D. and Schutze, H.,
 * "Foundations of Statistical Natural Language Processing", Cambridge, 
 * MA, USA: The MIT Press, 1999.
 *
 * @author Alexandre Trilla (atrilla)
 */
class generator {
    public:
        /**
         * @brief Plain empty constructor.
         */
        generator();
        /**
         * @brief Constructor indicating the order of the LM.
         * @param ord The order of the LM.
         */
        generator(int ord);
        /**
         * @brief Sets the order of the LM.
         * @param ord The given order.
         */
        void setOrder(int ord);
        /**
         * @brief Retrieves the order of the LM.
         * @return The order of the LM.
         */
        int getOrder() const;
        /**
         * @brief Inputs an instance of training data.
         * @param food The instance of training data.
         */
        void feed(const string &food);
        /**
         * @brief Outputs a language instance.
         * @return A language instance.
         */
        string produce();
    private:
        /**
         * @brief Container to keep record of the set of observed n-grams
         *     along with their frequencies.
         */
        map<ngram, int> freq;
        /**
         * @brief Order of the n-gram-based LM.
         */
        int order;
        /**
         * @brief Random number counter.
         */
        int rc;
        /**
         * @brief Lower bound function.
         * @param ng The test n-gram.
         * @return Iterator pointing to the lower bound.
         */
        map<ngram, int>::const_iterator lower (const ngram& ng) const;
        /**
         * @brief Upper bound function.
         * @param ng The test n-gram.
         * @return Iterator pointing to the upper bound.
         */
        map<ngram, int>::const_iterator upper (const ngram& ng) const;
        /**
         * @brief Generates a pseudo random number.
         * @return A pseudo random number.
         */
        int randNum();
        /**
         * @brief Makes a prediction according to the given history.
         * @param hist The given history.
         * @return The predicted token.
         */
        string predict(const ngram &hist);
};

#endif

