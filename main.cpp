#include <iostream>

#include "graph.hpp"

struct Data {
    int data;
};

int main() {
    algo::Graph<Data> graph;

    auto d1 = std::shared_ptr<Data>(new Data{1});
    auto d2 = std::shared_ptr<Data>(new Data{2});
    auto d3 = std::shared_ptr<Data>(new Data{3});

    graph.addVertex(d1);
    graph.addVertex(d2);
    graph.addVertex(d3);

    auto w1 = std::make_shared<algo::weight<double>>(4.0);
    auto w2 = std::make_shared<algo::weight<double>>(5.0);

    graph.addEdge(d1, d3, 3.0);
    graph.addEdge(d1, d2, w1);
    graph.addEdge(d2, d3, w2);

    auto path = graph.findShortestPath(d1, d3);

    for (const auto& edge : path->getPathEdges()) {
        std::cout << edge->weight_->getMeasure() << std::endl;
    }
}
