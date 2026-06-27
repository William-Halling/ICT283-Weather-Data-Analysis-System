# Weather Data Analyzer: Blizzard Project

## Executive Summary
This project is a high-performance C++17 diagnostic and analytical tool designed to meet rigorous data processing standards. It provides a robust, memory-safe solution for ingesting meteorological data, storing it in a custom-engineered `BinarySearchTree` (BST), and performing high-speed statistical analyses. The system is architected for efficiency, ensuring rapid retrieval and low memory overhead for time-sensitive environmental reporting.

## 1. Core Technical Features
* **Custom Template-Based BST:** A fully templated data structure designed for generic storage, ensuring strict type safety and code reusability across meteorological datasets.
* **Memory Safety Architecture:** Utilizes `std::unique_ptr` and adheres to the "Rule of 5," effectively preventing memory leaks and dangling pointer vulnerabilities.
* **Algorithmic Efficiency:**
    * **Insertion:** Average-case time complexity of $O(\log n)$.
    * **Data Retrieval:** Highly optimized traversal algorithms:
        * *In-order:* Enables chronological data processing for standard reports.
        * *Pre-order:* Supports structural duplication and cloning.
        * *Post-order:* Facilitates safe, bottom-up node aggregation and recursive deletion.

## 2. Design Philosophy
The core of the application leverages a decoupled architecture where the `BinarySearchTree` acts as the primary data container, and external `collectors` perform domain-specific statistical operations.


The BST is optimized to maintain sorted states during insertion, allowing analytical collectors to perform range-based filtering with minimal computational overhead. 

## 3. System Architecture
* `container/`: Contains the core `BinarySearchTree.h` and the underlying node management logic.
* `weather/`: Defines the `WeatherRecord` domain model, providing the data structure interface for the BST.
* `io/`: Manages file I/O operations, featuring `TextFile` for configuration and `CsvFile` for fault-tolerant data parsing.
* `ui/`: Handles the interactive console interface, user input validation, and menu-driven command execution.
* `collectors/`: Houses the functional modules for aggregating meteorological data points into analytical containers.

## 4. Development & Deployment
### Prerequisites
* **Compiler:** C++17 compatible (GCC 9+, Clang 10+, MSVC 2019+).
* **Build System:** CMake 3.10+.

### Compilation Steps
```bash
# Clone the repository and navigate to the directory
mkdir build && cd build
cmake ..
make
