#pragma once
#include <vector>
#include <deque>
#include <cmath>
#include <numeric>

namespace cuhft {

class RollingStatistics {
private:
    std::deque<double> window_;
    size_t capacity_;
    double sum_ = 0.0;
    double sum_sq_ = 0.0;
    
public:
    RollingStatistics(size_t window_size) : capacity_(window_size) {}
    
    void update(double value) {
        window_.push_back(value);
        sum_ += value;
        sum_sq_ += value * value;
        
        if (window_.size() > capacity_) {
            double old = window_.front();
            window_.pop_front();
            sum_ -= old;
            sum_sq_ -= old * old;
        }
    }
    
    double mean() const {
        if (window_.empty()) return 0.0;
        return sum_ / window_.size();
    }
    
    double stddev() const {
        if (window_.size() < 2) return 0.0;
        double m = mean();
        return std::sqrt((sum_sq_ / window_.size()) - (m * m));
    }
    
    double zscore(double value) const {
        double sd = stddev();
        if (sd == 0.0) return 0.0;
        return (value - mean()) / sd;
    }
};

} // namespace cuhft
