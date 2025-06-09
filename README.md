# Graph Library For Fun in CPP (C++)

**Graph-Library-For-Fan-in-CPP** is a compact C++ library for working with directed, weighted graphs.  
It provides fundamental structures for vertices, edges, and weights, and includes Dijkstra's algorithm for finding the shortest path between two vertices.  

## Key Features

*   **Modern C++**: Leverages smart pointers (`std::shared_ptr`), templates, and `std::enable_shared_from_this`.
*   **Generic Design**: Classes are parameterized by vertex data type (`T`) and weight type (`Weight::Type`) for flexibility.
*   **Automatic Memory Management**: Utilizes `std::shared_ptr` for managing the lifecycle of graph components.
*   **Dijkstra's Algorithm**: Implementation for finding the shortest path in graphs with non-negative edge weights.

## Requirements
C++17 (or higher) compliant compiler.

## License
[MIT License](LICENSE)
