#pragma once

#include <functional>
#include <initializer_list>
#include <list>
#include <memory>

namespace algo {

template <typename U>
class weight {
public:
    using Type = U;

public:
    static constexpr U INF = static_cast<U>(10000000.0);
    static constexpr double SMALL = static_cast<U>(0.0);

private:
    U measure_;

public:
    explicit weight(const U& m) : measure_(m) {}

public:
    ~weight() = default;

public:
    weight operator+(const weight& other) const { return weight(measure_ + other.measure_); }

public:
    bool operator<(const weight& other) const { return compare(other, std::less<>()); }

    bool operator>(const weight& other) const { return compare(other, std::greater<>()); }

    bool operator==(const weight& other) const { return compare(other, std::equal_to<>()); }

    bool operator<=(const weight& other) const { return compare(other, std::less_equal<>()); }

    bool operator>=(const weight& other) const { return compare(other, std::greater_equal<>()); }

public:
    const U& getMeasure() { return measure_; }

private:
    template <typename Comparator>
    bool compare(const weight& other, Comparator comp) const {
        return comp(measure_, other.measure_);
    }
};

}  // namespace algo
