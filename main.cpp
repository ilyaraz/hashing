#include "minimalistic_timer.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#include <iostream>
#include <vector>

#include <ctime>

typedef unsigned int uint;
typedef std::vector<uint> vuint;

struct Bitset {

    vuint bitset;

    void init(const vuint &data) {
        int size = 1 << 27; 
        bitset.clear();
        bitset.resize(size, 0);
        for (size_t i = 0; i < data.size(); ++i) {
            uint x = data[i];
            bitset[x >> 5] |= 1ul << (x & 31);
        }
    }

    int process(const vuint &queries) {
        int result = 0;
        for (size_t i = 0; i < queries.size(); ++i) {
            uint x = queries[i];
            if ((bitset[x >> 5] >> (x & 31)) & 1) {
                ++result;
            }
        }
        return result;
    }
};

template<typename T> void testDictionary(const vuint &data, const vuint &queries, T dictionary) {
    utils::MinimalisticTimer timer;
    timer.start();
    dictionary.init(data);
    timer.stop();
    std::cerr << "preprocessing time: " << timer.getTime() << std::endl;
    timer.reset();
    timer.start();
    int result = dictionary.process(queries);
    timer.stop();
    std::cerr << "query time: " << timer.getTime() << std::endl;
    std::cerr << "result: " << result << std::endl;
}

uint getSeed() {
    return std::time(0);
}

void generateDataQueries(int dataSize, int queriesNumber, double positiveProbability, vuint &data, vuint &queries) {
    namespace rnd = boost::random;
    rnd::mt19937 generator(getSeed());
    rnd::uniform_01<rnd::mt19937> rndDouble(generator);
    boost::uniform_int<> rndIndex(0, dataSize - 1);
    data.resize(dataSize);
    for (int i = 0; i < dataSize; ++i) {
        data[i] = generator();
    }
    queries.resize(queriesNumber);
    for (int i = 0; i < queriesNumber; ++i) {
        if (rndDouble() < positiveProbability) {
            queries[i] = data[rndIndex(generator)];
        }
        else {
            queries[i] = generator();
        }
    }
}

int main() {
    vuint data;
    vuint queries;
    const int DATA_SIZE = 100000;
    const int QUERIES_NUMBER = 100000000;
    const double POSITIVE_PROBABILITY = 0.3;
    generateDataQueries(DATA_SIZE, QUERIES_NUMBER, POSITIVE_PROBABILITY, data, queries);
    testDictionary(data, queries, Bitset());
    return 0;
}
