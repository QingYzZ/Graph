#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

using namespace std;

template <typename V>
class Graph {
	unordered_map<V, list< pair<V, int> > > adjList;

	/* Method to add a new vertex */
    bool newGraphVertex(V vertex) {
        /* Check if the vertex already exists */
        if (ifContainVertex(vertex)) {
            return false; // Vertex already exists
        }

        /* Add the vertex with an empty adjacency list */ 
        adjList[vertex] = std::list< pair<V, int> >();
        return true; /* Vertex added successfully */
    }

	/* check if vertex is already in the map */
	bool ifContainVertex(V vertex) {
		return adjList.find(vertex) != adjList.end();
	}

	bool newGraphEdge(V goesFrom, V goesTo, int weight) {
		if (weight < 0) {
			return false;
		}

		if (goesFrom == goesTo && weight != 0) {
            return false;
        }

		if (!ifContainVertex(goesFrom)) {
			newGraphVertex(goesFrom);
		} 

		if (!ifContainVertex(goesTo)) {
			newGraphVertex(goesTo);
		}

		/* Check if an edge from goesFrom to goesTo already exists */
        for (const auto& edge : adjList[goesFrom]) {
            if (edge.first == goesTo) {
                return false; /* Edge already exists */
            }
        }

		adjList[goesFrom].emplace_back(goesTo, weight);
		return true;
	}

	int getGraphEdgeWeight(V goesFrom, V goesTo) {
		/* Check if both vertices exist in the graph */ 
		if (ifContainVertex(goesFrom) && ifContainVertex(goesTo)) {
			/* Edge exists, return the weight */
			return adjList[goesFrom][goesTo];
		}
		/* If either vertex is missing or no edge exists, return -1 */
		return -1;
	}

    bool removeGraphEdge(V goesFrom, V goesTo) {
        /* Check if the source vertex exists */
        if (ifContainVertex(goesFrom) && ifContainVertex(goesTo)) {
			adjList[goesFrom].erase(goesTo);
			return true;
        }
        /* If the edge or vertices don't exist, return false */
        return false;
    }

    /* Method to display the graph */
    void printGraph() {
        for (auto &pair : adjList) {
            cout << "Vertex " << pair.first << ":";
            for (auto &adjVertex : pair.second) {
                cout << " -> " << adjVertex;
            }
            cout << std::endl;
        }
    }

};