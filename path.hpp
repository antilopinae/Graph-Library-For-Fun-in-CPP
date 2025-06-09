#pragma once

#include <algorithm>
#include <memory>
#include <set>
#include <unordered_map>

#include "distance.hpp"
#include "edge.hpp"
#include "vertex.hpp"
#include "weight.hpp"

namespace algo {

template <typename T, typename Weight = weight<double>>
class Path : public std::enable_shared_from_this<Path<T>> {
    using GraphVertex = Vertex<T>;
    using GraphEdge = Edge<GraphVertex, Weight>;
    using Distance = distance<Weight>;
    using MapOfDistance = std::unordered_map<std::shared_ptr<GraphVertex>, Distance>;

private:
    MapOfDistance distances_;
    std::unordered_map<std::shared_ptr<GraphVertex>, std::shared_ptr<GraphEdge>> map_path_;

private:
    std::vector<std::shared_ptr<GraphEdge>> path_edges_;
    std::vector<std::shared_ptr<GraphVertex>> path_vertices_;

public:
    Path() = default;

public:
    Path(const Path& other) = default;
    Path(Path&& other) = default;

public:
    Path& operator=(const Path& other) = default;
    Path& operator=(Path&& other) = default;

public:
    ~Path() = default;

public:
    std::shared_ptr<Path> getSubPath(const std::shared_ptr<GraphVertex>& start, const std::shared_ptr<GraphVertex>& end) = delete;

public:
    Distance& operator[](const std::shared_ptr<GraphVertex>& vertex) {
        if (distances_.find(vertex) == distances_.end()) {
            distances_[vertex] = Distance::INF();
        }
        return distances_[vertex];
    }

public:
    void append(const std::shared_ptr<GraphEdge>& edge, const std::shared_ptr<GraphVertex>& destination) {
        map_path_[destination] = edge;
    }

public:
    const std::vector<std::shared_ptr<GraphEdge>>& getPathEdges() const { return path_edges_; }

public:
    const std::vector<std::shared_ptr<GraphVertex>>& getPathVertices() const { return path_vertices_; }

public:
    std::shared_ptr<Path> create(const std::shared_ptr<GraphVertex>& start, const std::shared_ptr<GraphVertex>& end) {
        if (distances_[end] == Distance::INF()) map_path_.clear();

        auto edge = map_path_[end];

        for (auto at = end; edge != nullptr; edge = map_path_[at]) {
            path_edges_.push_back(edge);
            path_vertices_.push_back(edge->destination_);
            path_vertices_.push_back(edge->beginning_);
            at = edge->beginning_;
        }

        map_path_.clear();

        std::reverse(path_edges_.begin(), path_edges_.end());
        std::reverse(path_vertices_.begin(), path_vertices_.end());

        return this->shared_from_this();
    }
};

}  // namespace algo
