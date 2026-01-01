#include "cuhftlib.h"

#include <iostream>
#include <random>
#include <chrono>
#include <functional>


template<typename Func, typename... Args>
auto timeit(Func&& func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // Execute the function
    if constexpr (std::is_same_v<void, std::invoke_result_t<Func, Args...>>) {
        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "Execution time: " << duration.count() << " us" << std::endl;
        return duration;
    } else {
        auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "Execution time: " << duration.count() << " us" << std::endl;
        return std::make_pair(result, duration);
    }
}

int main(int argc, char** argv)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> double_dist(0., 200.);

    cuhft::RollingStatistics rs(20);
    double stddev, mean, zscore;

    timeit([&]() {
        for(int i = 0; i < 100000 ; ++ i)
        {
            double x = double_dist(rng);
            rs.update(x);
        }
    });

    timeit([&]() {stddev = rs.stddev();});
    timeit([&]() {mean = rs.mean();});
    timeit([&]() {zscore = rs.zscore(1.);});

    std::cout << "  sigma = " << rs.stddev() << "\n"
              << "     mu = " << rs.mean() << "\n"
              << " zscore = " << rs.zscore(1.) << "\n";

    return 0;
}
