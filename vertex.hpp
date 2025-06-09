#pragma once

#include <memory>
#include <vector>

#include "edge.hpp"

namespace algo {

template <typename T, typename Weight = weight<double>>
class Vertex : public std::enable_shared_from_this<Vertex<T>> {
    using GraphEdge = Edge<Vertex<T>, Weight>;
    using SharedEdge = std::shared_ptr<GraphEdge>;

private:
    std::shared_ptr<T> data_;
    std::vector<SharedEdge> in_;
    std::vector<SharedEdge> out_;

public:
    explicit Vertex() = default;
    Vertex(const std::shared_ptr<T>& data) : data_(data), in_(), out_() {}

public:
    Vertex(const Vertex& other) = default;
    Vertex(Vertex&& other) = default;

public:
    Vertex& operator=(const Vertex& other) = default;
    Vertex& operator=(Vertex&& other) = default;

public:
    ~Vertex() = default;

public:
    SharedEdge addEdgeIn(const std::shared_ptr<Vertex>& destination, const std::shared_ptr<Weight>& weight) {
        auto self = this->shared_from_this();
        in_.push_back(std::make_shared<GraphEdge>(self, destination, weight));
        return in_.back();
    }

public:
    SharedEdge addEdgeOut(const std::shared_ptr<Vertex>& beginner, const std::shared_ptr<Weight>& weight) {
        auto self = this->shared_from_this();
        out_.push_back(std::make_shared<GraphEdge>(beginner, self, weight));
        return out_.back();
    }

public:
    void addEdgeIn(const SharedEdge& edge) { in_.push_back(edge); }

    void addEdgeOut(const SharedEdge& edge) { out_.push_back(edge); }

public:
    const std::vector<SharedEdge>& getOutEdges() const { return out_; }

    const std::vector<SharedEdge>& getInEdges() const { return in_; }

public:
    const std::shared_ptr<T>& getData() const { return data_; }
};

}  // namespace algo
