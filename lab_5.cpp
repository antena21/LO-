#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <list>

using namespace std;

int main() {
    int size, graph_size = 0, counter = 0, inc_counter = 0;
    list<int> isolated = { 0 }, inc_isolated = { 0 };
    list<int> end_nodes = { 0 }, inc_end_nodes = { 0 };
    list<int> dominant_nodes = { 0 }, inc_dominant_nodes = { 0 };
    srand(time(0));

    cout << "Enter the amount of Graph's nodes" << endl;
    cin >> size;

    vector<vector<int>>  matrix(size, vector<int>(size));

    for (int i = 0; i != size; i++) {
        for (int j = i; j != size; j++) {
            if (i == j) {
                matrix[i][j] = 0;
                continue;
            }

            matrix[i][j] = rand() % 2;

            if (matrix[i][j] == 1) {
                graph_size++;
            }                                   // counting the amount of nodes AKA Graph size
            matrix[j][i] = matrix[i][j];

        }
    }

    for (int i = 0; i != size; i++) {
        for (int j = 0; j != size; j++) {
            if (matrix[i][j] == 1) counter++;
        }
        if (counter == 0) isolated.push_back(i);
        else if (counter == 1) end_nodes.push_back(i);
        if (counter == size - 1) dominant_nodes.push_back(i); // +added '-1' to compensate for cycling nodes
        counter = 0;
    }

    cout << "Adjacency matrix for graph G:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    printf("This is a TOYOTA, erm a Graph consiting of %d nodes.\nGraph size is %d\n", size, graph_size);
    //std::cout << __cplusplus << std::endl;

    cout << "List of isolated nodes of this Graph:" << endl;
    isolated.erase(isolated.begin());
    for (int numberh : isolated) {
        cout << numberh << " ";
    };
    cout << endl;

    cout << "List of end nodes of this Graph:" << endl;
    end_nodes.erase(end_nodes.begin());
    for (int numberh : end_nodes) {
        cout << numberh << " ";
    };
    cout << endl;

    cout << "List of dominant nodes of this Graph:" << endl;
    dominant_nodes.erase(dominant_nodes.begin());
    for (int numberh : dominant_nodes) {
        cout << numberh << " ";
    };
    cout << endl;

    //the incidence matrix
    vector<vector<int>>  incidence_matrix(size, vector<int>(graph_size, 0));

    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (matrix[i][j] == 1) {
                incidence_matrix[i][inc_counter] = 1;
                incidence_matrix[j][inc_counter] = 1;
                inc_counter++;                  // counts the amount of paths which have been already added
            }
        }
    }

    cout << endl << endl << endl;

    cout << "Incidence matrix for graph G:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < graph_size; j++) {
            cout << incidence_matrix[i][j] << " ";
        }
        cout << endl;
    }

    printf("Mooonday left me broken, Tues- Erm.. This is a Graph consiting of %d nodes.\nGraph size is %d\n", size, inc_counter);

    for (int i = 0; i != size; i++) {
        for (int j = 0; j != inc_counter; j++) {
            if (incidence_matrix[i][j] == 1) counter++;
        }
        if (counter == 0) inc_isolated.push_back(i);
        else if (counter == 1) inc_end_nodes.push_back(i);
        if (counter == graph_size - 1) inc_dominant_nodes.push_back(i); // +added '-1' to compensate for cycling nodes
        counter = 0;
    }

    cout << "List of isolated nodes of this Graph:" << endl;
    inc_isolated.erase(inc_isolated.begin());
    for (int numberh : inc_isolated) {
        cout << numberh << " ";
    };
    cout << endl;

    cout << "List of end nodes of this Graph:" << endl;
    inc_end_nodes.erase(inc_end_nodes.begin());
    for (int numberh : inc_end_nodes) {
        cout << numberh << " ";
    };
    cout << endl;

    cout << "List of dominant nodes of this Graph:" << endl;
    inc_dominant_nodes.erase(inc_dominant_nodes.begin());
    for (int numberh : inc_dominant_nodes) {
        cout << numberh << " ";
    };
    cout << endl;

    return 0;
}