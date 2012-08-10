#pragma once

#include <boost/optional.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace utils {

namespace pt = boost::posix_time;

class MinimalisticTimer {
    public:
        MinimalisticTimer(): totalTime(0.0) {}

        void start() {
            startTime = pt::microsec_clock::local_time();
        }

        void stop() {
            totalTime += ((pt::microsec_clock::local_time() - *startTime).total_milliseconds() + 0.0) / 1000.0;
            startTime.reset();
        }

        void reset() {
            totalTime = 0.0;
            startTime.reset();
        }

        double getTime() const {
            return totalTime;
        }
    private:
        boost::optional<pt::ptime> startTime;
        double totalTime;
};

}
