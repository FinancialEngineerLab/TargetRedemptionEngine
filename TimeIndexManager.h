#pragma once

#include <vector>

class TimeIndexManager {
public:
    TimeIndexManager(
        const std::vector<double>& observedTimes, 
        const std::vector<std::size_t>& timeIndice);
    ~TimeIndexManager();

    double operator[](const std::size_t index) const;
    std::size_t size() const;
    std::size_t getTimeIndex(const std::size_t index) const;
    int searchIndex(const double time) const;

private:
    const std::vector<double> _observedTimes;
    const std::vector<std::size_t> _timeIndice;

};

