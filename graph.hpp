#pragma once

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "distance.hpp"
#include "edge.hpp"
#include "path.hpp"
#include "vertex.hpp"
#include "weight.hpp"

namespace algo {

template <typename T, typename Weight = weight<double>>
class Graph {
    using GraphVertex = Vertex<T, Weight>;
    using GraphEdge = Edge<GraphVertex, Weight>;
    using Map = std::unordered_map<std::shared_ptr<T>, std::shared_ptr<GraphVertex>>;

private:
    Map vertices_;

public:
    Graph() = default;

public:
    Graph(const Graph& other) = default;
    Graph(Graph&& other) = default;

public:
    Graph& operator=(const Graph& other) = default;
    Graph& operator=(Graph&& other) = default;

public:
    ~Graph() = default;

public:
    void addVertex(const std::shared_ptr<T>& data) {
        if (vertices_.find(data) == vertices_.end()) {
            vertices_[data] = std::make_shared<GraphVertex>(data);
        } else {
            throw std::runtime_error("Vertecies should be unique!");
        }
    }

public:
    void addEdge(const std::shared_ptr<T>& from, const std::shared_ptr<T>& to, const typename Weight::Type weight) {
        auto weight_ptr = std::make_shared<Weight>(weight);
        addEdge(from, to, weight_ptr);
    }

public:
    void addEdge(const std::shared_ptr<T>& from, const std::shared_ptr<T>& to, const std::shared_ptr<Weight>& weight) {
        auto edge = vertices_[from]->addEdgeOut(vertices_[to], weight);
        vertices_[to]->addEdgeIn(edge);
    }

public:
    std::shared_ptr<Path<T>> findShortestPath(const std::shared_ptr<T>& start, const std::shared_ptr<T>& end) {
        std::shared_ptr<GraphVertex> vstart = vertices_[start];
        std::shared_ptr<GraphVertex> vend = vertices_[end];

        return findShortestPath(vstart, vend);
    }

public:
    std::shared_ptr<Path<T>> findShortestPath(const std::shared_ptr<GraphVertex>& vstart,
                                              const std::shared_ptr<GraphVertex>& vend) {
        typedef distance<Weight> distance;
        typedef Path<T, Weight> Path;

        Path path{};
        path[vstart] = distance::SMALL();

        std::set<std::pair<distance, std::shared_ptr<GraphVertex>>> pq;
        pq.emplace(distance::SMALL(), vstart);

        while (!pq.empty()) {
            auto [current_dist, current_vertex] = *pq.begin();
            pq.erase(pq.begin());

            if (current_vertex == vend) break;

            for (const auto& edge : current_vertex->getOutEdges()) {
                distance new_dist = path[current_vertex] + edge->weight_;
                const auto& destination = edge->destination_;

                if (new_dist < path[destination]) {
                    // remove old version
                    pq.erase({path[destination], destination});
                    path[destination] = new_dist;
                    path.append(edge, destination);
                    pq.emplace(new_dist, destination);
                }
            }
        }

        auto path_ptr = std::make_shared<Path>(std::move(path));

        return path_ptr->create(vstart, vend);
    }

public:
    void clear() { vertices_.clear(); }

public:
    const std::unordered_map<std::shared_ptr<T>, std::shared_ptr<GraphVertex>>& getVertices() const { return vertices_; }
};

}  // namespace algo
