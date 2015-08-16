#pragma once

#include <vector>

class TimeIndexManager {
public:
    TimeIndexManager(
        const std::vector<double>& timeGrid, 
        const std::vector<std::size_t>& timeIndice);
    ~TimeIndexManager();

    double operator[](const std::size_t index) const;
    std::size_t size() const;
    std::size_t getTimeIndex(const std::size_t index) const;
    std::size_t searchIndex(const double time) const;
    std::vector<double> getTimeGrid() const;

private:
    const std::vector<double> _timeGrid;
    const std::vector<std::size_t> _timeIndice;

};

