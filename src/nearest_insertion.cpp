#include "nearest_insertion.h"
#include "data_loader.h"
#include "plot_tour.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <climits>

using namespace std;

pair<vector<int>, int> heuristic_nearest_insertion(
    const vector<vector<int>>& distance_matrix
) {
    int n = distance_matrix.size();
    vector<int> tour;
    vector<bool> visitado(n, false);

    int actual = 0;
    tour.push_back(actual);
    visitado[actual] = true;

    int nodo_mas_cercano = -1;
    int min_dist = INT_MAX;
    for (int i=1; i<n; ++i){
        if (distance_matrix[0][i] < min_dist){
            min_dist = distance_matrix[0][i];
            nodo_mas_cercano = i;
        }
    }
    tour.push_back(nodo_mas_cercano);
    visitado[nodo_mas_cercano] = true;

    while (tour.size() < n){
        int nodo_a_insertar;
        int min_dist2 = INT_MAX;
        for (int i=0; i<n; ++i){
            if (!visitado[i]){
                for(int j = 0; j<tour.size(); j++){
                    int tour_n = tour[j];
                    if (distance_matrix[i][tour_n] < min_dist2){
                        min_dist2 = distance_matrix[i][tour_n];
                        nodo_a_insertar = i;
                    }
                }
            }
        }
        int mejor_pos = -1;
        int menor_coste_inser = INT_MAX;

        for (int i=0; i< tour.size(); i++){
            int nodo_actual = tour[i];
            int nodo_sig = tour[(i+1) % tour.size()];

            int coste = distance_matrix[nodo_actual][nodo_a_insertar] + distance_matrix[nodo_a_insertar][nodo_sig] - distance_matrix[nodo_actual][nodo_sig];
            if (coste < menor_coste_inser){
                menor_coste_inser = coste;
                mejor_pos = i + 1;
            }
        }
        tour.insert(tour.begin() + mejor_pos, nodo_a_insertar);
        visitado[nodo_a_insertar] = true;
    }

    int total_cost = 0;
    for (int i=0; i<tour.size(); i++){
        total_cost += distance_matrix[tour[i]][tour[(i+1) % tour.size()]];
    }

    return {tour, total_cost};
}

int main(int argc, char* argv[]) {
    // g++ nearest_insertion.cpp data_loader.cpp plot_tour.cpp -o nearest_insertion.bin -O3 && ./nearest_insertion.bin ./data/berlin52.tsp
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <path_to_tsp_file>" << endl;
        return 1;
    }

    string file_path = argv[1];
    pair<vector<Node>, vector<int>> parsed_data = parse_tsplib_file(file_path);
    vector<Node> nodes = parsed_data.first;
    vector<int> optimal_tour = parsed_data.second;

    if (nodes.empty()) {
        cout << "No nodes loaded. Please check the file path and format." << endl;
        return 1;
    }

    vector<vector<int>> dist_matrix = build_distance_matrix(nodes);
    cout << "Successfully loaded " << dist_matrix.size() << " nodes." << endl;
    string instance_name = get_instance_name(file_path);

    if (!optimal_tour.empty()) {
        int optimal_cost = compute_tour_cost(optimal_tour, dist_matrix);
        cout << "Optimal Tour Cost from file: " << optimal_cost << endl;

        string optimal_png_path = instance_name + "_optimal_tour.png";
        if (export_tour_to_png(nodes, optimal_tour, optimal_png_path, "Optimal Tour", "#1f77b4")) {
            cout << "Saved optimal tour visualization to " << optimal_png_path << endl;
        } else {
            cout << "Could not write optimal tour PNG (requires gnuplot)." << endl;
        }
    } else {
        cout << "No optimal tour found in input file." << endl;
    }

    pair<vector<int>, int> insertion_result = heuristic_nearest_insertion(dist_matrix);
    cout << "Nearest Insertion Cost: " << insertion_result.second << endl;

    if (!insertion_result.first.empty()) {
        string computed_png_path = instance_name + "_nearest_insertion_tour.png";
        if (export_tour_to_png(nodes, insertion_result.first, computed_png_path, "Nearest Insertion Tour", "#d62728")) {
            cout << "Saved nearest-insertion tour visualization to " << computed_png_path << endl;
        } else {
            cout << "Could not write nearest-insertion tour PNG (requires gnuplot)." << endl;
        }
    } else {
        cout << "No computed nearest-insertion tour to visualize." << endl;
    }

    return 0;
}
