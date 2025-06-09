#pragma once

#include <memory>

#include "distance.hpp"
#include "weight.hpp"

namespace algo {

template <typename T, typename Weight = weight<double>>
class Edge : public std::enable_shared_from_this<Edge<T>> {
public:
    std::shared_ptr<T> destination_;
    std::shared_ptr<T> beginning_;
    std::shared_ptr<Weight> weight_;

public:
    Edge(const std::shared_ptr<T>& destionation, const std::shared_ptr<T>& beginning, const std::shared_ptr<Weight>& weight)
        : destination_(destionation), beginning_(beginning), weight_(weight) {}

public:
    Edge(const Edge& other) = default;
    Edge(Edge&& other) = default;

public:
    Edge& operator=(const Edge& other) = default;
    Edge& operator=(Edge&& other) = default;

public:
    ~Edge() = default;
};

}  // namespace algo
