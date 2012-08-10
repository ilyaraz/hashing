#include "minimalistic_timer.h"

#include <boost/random/mersenne_twister.hpp>

#include <iostream>
#include <vector>

typedef unsigned int uint;
typedef std::vector<uint> vuint;
typedef unsigned char uchar;
typedef std::vector<uchar> vuchar;

const int DATA_SIZE = 100000000;
const int QUERIES_NUMBER = 100000000;

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
    return 0;
}

void generateDataQueries(vuint &data, vuint &queries, double positiveProbability) {
    namespace rnd = boost::random;
    rnd::mt19937 generator(getSeed());
    data.resize(DATA_SIZE);
    for (int i = 0; i < DATA_SIZE; ++i) {
        data[i] = generator();
    }
    queries.resize(QUERIES_NUMBER);
    for (int i = 0; i < QUERIES_NUMBER; ++i) {
        queries[i] = generator();
    }
}

int main() {
    vuint data;
    vuint queries;
    generateDataQueries(data, queries, 0.3);
    testDictionary(data, queries, Bitset());
    return 0;
}
