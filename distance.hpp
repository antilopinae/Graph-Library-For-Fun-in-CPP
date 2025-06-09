#pragma once

#include <functional>
#include <initializer_list>
#include <list>
#include <memory>
#include <numeric>

#include "edge.hpp"
#include "weight.hpp"

namespace algo {

template <typename Weight = weight<double>>
class distance {
private:
    std::vector<std::shared_ptr<Weight>> edges_;

public:
    static const distance& INF() {
        static distance inf_instance(std::make_shared<Weight>(Weight::INF));
        return inf_instance;
    }

    static const distance& SMALL() {
        static distance small_instance(std::make_shared<Weight>(Weight::SMALL));
        return small_instance;
    }

public:
    explicit distance(std::initializer_list<std::shared_ptr<Weight>> list) : edges_(list) {}
    explicit distance(std::shared_ptr<Weight> weight) : edges_({weight}) {}
    explicit distance() = default;

public:
    ~distance() = default;

public:
    const distance operator+(const distance& other) const {
        auto result = *this;
        result.edges_.insert(result.edges_.end(), other.edges_.begin(), other.edges_.end());
        return result;
    }

public:
    const distance operator+(const std::shared_ptr<Weight>& other) const {
        auto result = *this;
        result.edges_.push_back(other);
        return result;
    }

public:
    bool operator<(const distance& other) const { return compare(other, std::less<>()); }

    bool operator>(const distance& other) const { return compare(other, std::greater<>()); }

    bool operator==(const distance& other) const { return compare(other, std::equal_to<>()); }

    bool operator<=(const distance& other) const { return compare(other, std::less_equal<>()); }

    bool operator>=(const distance& other) const { return compare(other, std::greater_equal<>()); }

private:
    template <typename Comparator>
    bool compare(const distance& other, Comparator comp) const {
        auto our_sum = std::accumulate(
            edges_.begin(), edges_.end(), Weight(0), [](Weight acc, const std::shared_ptr<Weight>& edge) { return acc + *edge; });

        auto other_sum = std::accumulate(
            other.edges_.begin(), other.edges_.end(), Weight(0), [](Weight acc, const std::shared_ptr<Weight>& edge) {
                return acc + *edge;
            });

        return comp(our_sum, other_sum);
    }
};

}  // namespace algo
