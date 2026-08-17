# UrbanPulse — Qom Metro Algorithm Project

UrbanPulse is the final project for the **Design of Algorithms** course. The program models a simplified metro network for Qom as a weighted graph and applies several algorithms to routing, infrastructure design, train operations, passenger flow, and network analysis.

## Requirements

- C++17
- CMake 3.16+
- A C++ compiler such as GCC/g++ 13.x, Clang, or MSVC

## Project Structure

```text
UrbanPulse/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── BellmanFord.h
│   ├── Data.h
│   ├── ExpressNetwork.h
│   ├── Infrastructure.h
│   ├── MetroController.h
│   ├── MetroGraph.h
│   ├── MetroOperations.h
│   ├── NetworkAnalysis.h
│   └── Routing.h
└── src/
    ├── BellmanFord.cpp
    ├── Data.cpp
    ├── ExpressNetwork.cpp
    ├── Infrastructure.cpp
    ├── main.cpp
    ├── MetroController.cpp
    ├── MetroGraph.cpp
    ├── MetroOperations.cpp
    ├── NetworkAnalysis.cpp
    └── Routing.cpp
```

### File Responsibilities

- **MetroGraph** — Base undirected weighted graph and adjacency-list representation.
- **Routing** — BFS reachability and Dijkstra shortest path by distance or time.
- **Infrastructure** — Kruskal MST and Disjoint Set / Union-Find.
- **ExpressNetwork** — Directed acyclic express network, Kahn topological sort, and DAG shortest path.
- **BellmanFord** — Shortest path with negative edges and negative-cycle detection.
- **MetroOperations** — Interval scheduling, train dispatch priority queue, traffic analytics, and passenger queue simulation.
- **NetworkAnalysis** — Floyd-Warshall, Edmonds-Karp maximum flow, articulation points / bridges, and Levenshtein station search.
- **Data** — Creates the sample metro graph and test datasets used by the application.
- **MetroController** — Console menu, input handling, and coordination between modules.
- **main.cpp** — Program entry point only.

## Algorithms

| Task | Algorithm / Data Structure | Main Complexity |
|---|---|---|
| Reachability | BFS | `O(V + E)` |
| Weighted shortest path | Dijkstra + min-heap | `O((V + E) log V)` |
| Minimum spanning tree | Kruskal + Union-Find | `O(E log E)` |
| Express route | Kahn topological sort + DAG relaxation | `O(V + E)` |
| Negative-weight shortest path | Bellman-Ford | `O(VE)` |
| Train scheduling | Greedy interval scheduling | `O(n log n)` |
| Train dispatch | Priority queue | `push/pop: O(log n)`, `top: O(1)` |
| k-th busiest station | Min-heap of size `k` | `O(n log k)` |
| Passenger simulation | FIFO queue | Linear in simulated queue operations |
| All-pairs shortest paths | Floyd-Warshall | `O(V^3)` |
| Maximum flow | Edmonds-Karp | `O(VE^2)` |
| Critical stations/routes | DFS low-link | `O(V + E)` |
| Typo-tolerant station search | Levenshtein DP | `O(nm)` per string comparison |

## Build with CMake

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

The executable is named `metro` (`metro.exe` on Windows).

### Windows + MinGW / g++

If CMake does not automatically select your GCC/MinGW toolchain, use:

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

Then run the executable from the generated build directory, for example:

```bash
./build/metro
```

On Windows PowerShell, depending on the generator/layout, the executable may be run as:

```powershell
.\build\metro.exe
```

## Direct g++ Build

CMake is recommended, but the project can also be compiled directly:

```bash
g++ src/main.cpp src/MetroController.cpp src/MetroGraph.cpp src/Routing.cpp src/Infrastructure.cpp src/ExpressNetwork.cpp src/BellmanFord.cpp src/MetroOperations.cpp src/NetworkAnalysis.cpp src/Data.cpp -Iinclude -std=c++17 -o metro
```

## Program Menu

The console application provides the following operations:

1. Show stations
2. BFS reachability
3. Dijkstra shortest path
4. Kruskal MST
5. Express DAG shortest path
6. Bellman-Ford
7. Train interval scheduling
8. Train dispatch priority queue
9. Metro analytics
10. Passenger simulation
11. Floyd-Warshall
12. Maximum flow
13. Critical stations and bridges
14. Typo-tolerant station search
0. Exit

## Design Notes

- The main metro network is an **undirected weighted graph** represented with an adjacency list.
- Express routes are modeled separately as a **directed acyclic graph (DAG)**.
- For the MST task, route distance is used as the relative construction-cost weight because no separate construction-cost dataset is provided.
- Passenger simulation uses a fixed random seed in the supplied test scenario so results are reproducible.
- Sample flow capacities, train data, and traffic statistics are stored separately from the algorithms in `Data.cpp`.
- Bonus sections are not part of this implementation.

## Repository Hygiene

Generated binaries and build files should not be committed. Keep `metro.exe` and the `build/` directory out of the source tree. A typical `.gitignore` can include:

```gitignore
build/
*.exe
*.o
*.obj
```
