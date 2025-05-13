#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <fstream> 

using namespace std;

class Graph_M {
private:
    unordered_map<string, vector<pair<string, int>>> adjList;

public:
    void addVertex(const string& station) {
        adjList[station]; // Create an empty vector for the station if it doesn't exist
    }

    void addEdge(const string& from, const string& to, int distance) {
        adjList[from].emplace_back(to, distance);
        adjList[to].emplace_back(from, distance); // Assuming the graph is undirected
    }

    void removeVertex(const string& station) {
        for (auto& pair : adjList) {
            pair.second.erase(
                remove_if(pair.second.begin(), pair.second.end(),
                    [&station](const std::pair<string, int>& edge) {
                        return edge.first == station;
                    }),
                pair.second.end()
            );
        }
        adjList.erase(station);
    }

    void removeEdge(const string& src, const string& dest) {
        if (adjList.find(src) != adjList.end()) {
            adjList[src].erase(
                remove_if(adjList[src].begin(), adjList[src].end(),
                    [&dest](const std::pair<string, int>& edge) {
                        return edge.first == dest;
                    }),
                adjList[src].end()
            );
        }
        if (adjList.find(dest) != adjList.end()) {
            adjList[dest].erase(
                remove_if(adjList[dest].begin(), adjList[dest].end(),
                    [&src](const std::pair<string, int>& edge) {
                        return edge.first == src;
                    }),
                adjList[dest].end()
            );
        }
    }

    void display_Stations() const {
        cout << "Stations in the Metro Map:\n";
        for (const auto& station : adjList) {
            cout << station.first << endl;
        }
    }

    void display_Map() const {
        cout << "Metro Map Connections:\n";
        for (const auto& station : adjList) {
            cout << station.first << " connects to: ";
            for (const auto& neighbor : station.second) {
                cout << neighbor.first << " (" << neighbor.second << " km), ";
            }
            cout << endl;
        }
    }

    const vector<pair<string, int>>& getConnectedStations(const string& station) const {
        return adjList.at(station);
    }

    bool containsVertex(const string& station) const {
        return adjList.find(station) != adjList.end();
    }

    bool hasPath(const string& from, const string& to, unordered_map<string, bool>& processed) {
        if (!containsVertex(from) || !containsVertex(to)) return false;
        if (from == to) return true;

        processed[from] = true;
        for (const auto& neighbor : adjList.at(from)) {
            if (!processed[neighbor.first] && hasPath(neighbor.first, to, processed)) {
                return true;
            }
        }
        return false;
    }

    int dijkstra(const string& source, const string& destination, bool isTime, vector<string>& path) {
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        unordered_map<string, int> distances;
        unordered_map<string, string> previous;

        for (const auto& station : adjList) {
            distances[station.first] = numeric_limits<int>::max();
        }
        distances[source] = 0;
        pq.emplace(0, source);

        while (!pq.empty()) {
            auto [currentDistance, currentStation] = pq.top();
            pq.pop();

            if (currentStation == destination) {
                for (string at = destination; at != ""; at = previous[at]) {
                    path.push_back(at);
                }
                reverse(path.begin(), path.end());
                return currentDistance;
            }

            for (const auto& neighbor : adjList[currentStation]) {
                int weight = isTime ? 1 : neighbor.second;
                int newDistance = currentDistance + weight;

                if (newDistance < distances[neighbor.first]) {
                    distances[neighbor.first] = newDistance;
                    pq.emplace(newDistance, neighbor.first);
                    previous[neighbor.first] = currentStation;
                }
            }
        }
        return numeric_limits<int>::max();
    }

    vector<string> get_Interchanges(int distance) {
        vector<string> interchanges;
        interchanges.push_back("Interchange Logic Placeholder");
        interchanges.push_back(to_string(distance));
        return interchanges;
    }

    void saveMap(const string& filename) {
        ofstream file(filename);
        for (const auto& station : adjList) {
            for (const auto& edge : station.second) {
                file << station.first << " " << edge.first << " " << edge.second << endl;
            }
        }
        file.close();
    }

    void loadMap(const string& filename) {
        ifstream file(filename);
        string station1, station2;
        int distance;
        while (file >> station1 >> station2 >> distance) {
            addVertex(station1);
            addVertex(station2);
            addEdge(station1, station2, distance);
        }
        file.close();
    }
};

void Create_Metro_Map(Graph_M& g) {
    g.addVertex("Noida Sector 62~B");
    g.addVertex("Botanical Garden~B");
    g.addVertex("Yamuna Bank~B");
    g.addVertex("Rajiv Chowk~BY");
    g.addVertex("Vaishali~B");
    g.addVertex("Moti Nagar~B");
    g.addVertex("Janak Puri West~BO");
    g.addVertex("Dwarka Sector 21~B");
    g.addVertex("Huda City Center~Y");
    g.addVertex("Saket~Y");
    g.addVertex("Vishwavidyalaya~Y");
    g.addVertex("Chandni Chowk~Y");
    g.addVertex("New Delhi~YO");
    g.addVertex("AIIMS~Y");
    g.addVertex("Shivaji Stadium~O");
    g.addVertex("DDS Campus~O");
    g.addVertex("IGI Airport~O");
    g.addVertex("Rajouri Garden~BP");
    g.addVertex("Netaji Subhash Place~PR");
    g.addVertex("Punjabi Bagh West~P");

    g.addEdge("Noida Sector 62~B", "Botanical Garden~B", 8);
    g.addEdge("Botanical Garden~B", "Yamuna Bank~B", 10);
    g.addEdge("Yamuna Bank~B", "Vaishali~B", 8);
    g.addEdge("Yamuna Bank~B", "Rajiv Chowk~BY", 6);
    g.addEdge("Rajiv Chowk~BY", "Moti Nagar~B", 9);
    g.addEdge("Moti Nagar~B", "Janak Puri West~BO", 7);
    g.addEdge("Janak Puri West~BO", "Dwarka Sector 21~B", 6);
    g.addEdge("Huda City Center~Y", "Saket~Y", 15);
    g.addEdge("Saket~Y", "AIIMS~Y", 6);
    g.addEdge("AIIMS~Y", "Rajiv Chowk~BY", 7);
    g.addEdge("Rajiv Chowk~BY", "New Delhi~YO", 1);
    g.addEdge("New Delhi~YO", "Chandni Chowk~Y", 2);
    g.addEdge("Chandni Chowk~Y", "Vishwavidyalaya~Y", 5);
    g.addEdge("New Delhi~YO", "Shivaji Stadium~O", 2);
    g.addEdge("Shivaji Stadium~O", "DDS Campus~O", 7);
    g.addEdge("DDS Campus~O", "IGI Airport~O", 8);
    g.addEdge("Moti Nagar~B", "Rajouri Garden~BP", 2);
    g.addEdge("Punjabi Bagh West~P", "Rajouri Garden~BP", 2);
    g.addEdge("Punjabi Bagh West~P", "Netaji Subhash Place~PR", 3);
}

void displayHelpMenu() {
    cout << "****WELCOME TO THE METRO APP*****\n";
    cout << "\n\t\t~~LIST OF ACTIONS~~\n";
    cout << "Help Menu:\n";
    cout << "1. LIST ALL THE STATIONS IN THE MAP - Shows all the stations in the metro map.\n";
    cout << "2. SHOW THE METRO MAP - Displays the connections between stations.\n";
    cout << "3. GET SHORTEST DISTANCE - Shows the shortest distance between two stations.\n";
    cout << "4. GET SHORTEST TIME - Shows the shortest time between two stations.\n";
    cout << "5. GET SHORTEST PATH (DISTANCE WISE) - Shows the shortest path by distance between two stations.\n";
    cout << "6. GET SHORTEST PATH (TIME WISE) - Shows the shortest path by time between two stations.\n";
    cout << "7. REMOVE A STATION - Remove a specified station from the metro map.\n";
    cout << "8. REMOVE A CONNECTION - Remove a specified connection between two stations.\n";
    cout << "9. SAVE MAP TO FILE - Saves the current metro map to a file.\n";
    cout << "10. LOAD MAP FROM FILE - Loads a metro map from a specified file.\n";
    cout << "11. EXIT - Exits the application.\n";
}

void performUserAction(int choice, Graph_M& g) {
    string src, dest;
    int distance;
    vector<string> path;

    switch (choice) {
    case 1:
        g.display_Stations();
        break;
    case 2:
        g.display_Map();
        break;
    case 3:
        cout << "Enter source station: ";
        cin >> ws;
        getline(cin, src);
        cout << "Enter destination station: ";
        getline(cin, dest);
        distance = g.dijkstra(src, dest, false, path);
        cout << "The shortest distance is: " << distance << " km\n";
        break;
    case 4:
        cout << "Enter source station: ";
        cin >> ws;
        getline(cin, src);
        cout << "Enter destination station: ";
        getline(cin, dest);
        distance = g.dijkstra(src, dest, true, path);
        cout << "The shortest time is: " << distance << " units\n";
        break;
    case 5:
        cout << "Enter source station: ";
        cin >> ws;
        getline(cin, src);
        cout << "Enter destination station: ";
        getline(cin, dest);
        distance = g.dijkstra(src, dest, false, path);
        cout << "***********************************************************\n";
        cout << "SOURCE STATION: " << src << "\n";
        cout << "DESTINATION STATION: " << dest << "\n";
        cout << "DISTANCE: " << distance << " KM\n";
        cout << "NUMBER OF INTERCHANGES: " << g.get_Interchanges(distance).size() << "\n";
        cout << "~~~~~~~~~~~~~\n";
        cout << "START ==> " << src << endl;
        for (const auto& station : path) {
            cout << station << endl;
        }
        cout << dest << " ==> END\n";
        cout << "~~~~~~~~~~~~~\n";
        break;
    case 6:
        cout << "Enter source station: ";
        cin >> ws;
        getline(cin, src);
        cout << "Enter destination station: ";
        getline(cin, dest);
        distance = g.dijkstra(src, dest, true, path);
        cout << "***********************************************************\n";
        cout << "SOURCE STATION: " << src << "\n";
        cout << "DESTINATION STATION: " << dest << "\n";
        cout << "TIME: " << distance << " units\n";
        cout << "NUMBER OF INTERCHANGES: " << g.get_Interchanges(distance).size() << "\n";
        cout << "~~~~~~~~~~~~~\n";
        cout << "START ==> " << src << endl;
        for (const auto& station : path) {
            cout << station << endl;
        }
        cout << dest << " ==> END\n";
        cout << "~~~~~~~~~~~~~\n";
        break;
    case 7:
        cout << "Enter the name of the station to remove: ";
        cin >> ws;
        getline(cin, src);
        g.removeVertex(src);
        cout << "Station removed.\n";
        break;
    case 8:
        cout << "Enter the source station: ";
        cin >> ws;
        getline(cin, src);
        cout << "Enter the destination station: ";
        getline(cin, dest);
        g.removeEdge(src, dest);
        cout << "Connection removed.\n";
        break;
    case 9:
        cout << "Enter filename to save the map: ";
        cin >> ws;
        getline(cin, src);
        g.saveMap(src);
        cout << "Map saved to " << src << "\n";
        break;
    case 10:
        cout << "Enter filename to load the map from: ";
        cin >> ws;
        getline(cin, src);
        g.loadMap(src);
        cout << "Map loaded from " << src << "\n";
        break;
    case 11:
        cout << "Exiting the application.\n";
        exit(0);
    default:
        cout << "Invalid choice, please try again.\n";
        break;
    }
}

int main() {
    Graph_M metroGraph;
    Create_Metro_Map(metroGraph);
    int choice;

    do {
        displayHelpMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        performUserAction(choice, metroGraph);
    } while (choice != 11);

    return 0;
}
