#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <list>
#include <string>

//#include <bits/stdc++.h>

using namespace std;

/// DONE : now node1 < node2 ALWAYS, fuck with this however you want, your problem now...

/// use notation starting from '0'. And it'll solve thousands of problems and save ~50 lines of code

/// change the size in fucntions close_nodes and close_adj node or sth, cuz rn I have to manually write 'size1-1'
/// after using this functions

/// maybe when closing nodes for adj list -> it does not create a loop if 'node1' and 'node2'
/// (which are being closed) has connections
/// FIXED

/// !!!!also add a check for 'out of boundaries' and 'same numbers',  all zeros and such...

/// use this:
///    int size = (*size_old - 1);
///    *size_old += 1;
/// and this:       nodes->push_back(*size_old+1);

//  initiates a Graph of specified size in a matrix form, fills it with random numbers.
//  no looping nodes
vector<vector<int>> create_Graph(int size, vector<int>* nodes) {

    for (int i = 0; i < size; i++) nodes->push_back(i + 1);

    vector<vector<int>>  matrix(size, vector<int>(size));

    for (int i = 0; i != size; i++) {
        for (int j = i; j != size; j++) {
            if (j == i) {
                matrix[i][j] = 0;
                continue;
            }

            matrix[i][j] = rand() % 2;
            matrix[j][i] = matrix[i][j];
        }
    }

    return matrix;
}

//  displays it. Uses a vector with all of the node 'numbers' to properly display it
void display_Graph(vector<vector<int>> matrix, int size, string name, vector<int> nodes) {

    cout << "Adjacency matrix for graph " << name << ":" << endl;
    for (int i = 0; i < size; i++) {
        cout << nodes[i] << " | ";
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "    ";
    for (int k = 0; k < size; k++) cout << "_" << " ";
    cout << endl << "    ";
    for (int k = 0; k < size; k++) cout << nodes[k] << " ";
    cout << endl << endl;
}

list<list<int>> convert_to_adj_list(vector<vector<int>> matrix, int size) {

    list<list<int>> graph;
    list<int> temp_list;

    for (int i = 0; i != size; i++) {
        for (int j = 0; j != size; j++) {

            if (matrix[i][j] == 1) {
                temp_list.push_back(j);
            }
        }

        graph.push_back(temp_list);
        temp_list.clear();
    }

    return graph;
}

void display_adj_list(list<list<int>> adj_list, int size, string name, vector<int> nodes) {
    int counter = 0;

    cout << "Adjacency list for graph " << name << ":" << endl;

    for (auto iterator = adj_list.begin(); iterator != adj_list.end(); ++iterator) {
        cout << nodes[counter];
        counter++;

        list<int>::iterator sub_iterator;
        list<int>& sub_pointer = *iterator;
        for (sub_iterator = sub_pointer.begin(); sub_iterator != sub_pointer.end(); sub_iterator++) {
            cout << "-> " << (*sub_iterator) + 1;
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> close_nodes(vector<vector<int>> matrix, int* size_old, int node1, int node2, vector<int>* nodes) {
    node1--;
    node2--;

    int size = (*size_old - 1);
    *size_old -= 1;

    vector<int> new_node(size);

    //creating new node by 'closing' two specified
    // because we used new_node[i] it was messing up position for new closed node
    // I can add another counter - which is easy, or try to insert thenew nums i

    // can't I just omit using 'j' and also the first if, and just check the second if and do a .push_back intead of 'new_node[j] = 1' ???
    int j = 0;
    for (int i = 0; i <= size; i++) {
        if (i == node1 || i == node2) continue;

        if (matrix[node1][i] || matrix[node2][i]) new_node[j] = 1;
        j++;
        /*
                if (!matrix[node1][i] && !matrix[node2][i]) {
                    //new_node[j] = 0;
                    j++;
                }
                else {
                    new_node[j] = 1;
                    j++;
                }
                */
    }

    // should there be 'size-1' ???
    if (matrix[node1][node2]) new_node[size - 1] = 1; //adding loop if it exists

    matrix.erase(matrix.begin() + node2);
    matrix.erase(matrix.begin() + node1);

    for (j = 0; j != size - 1; j++) {
        matrix[j].erase(matrix[j].begin() + node2);
        matrix[j].erase(matrix[j].begin() + node1);

        matrix[j].push_back(new_node[j]);
    }

    matrix.push_back(new_node);

    //there we delete the nodes
    //int temp = max(node1, node2);
    //int mini = min(node1, node2); 
    nodes->erase(nodes->begin() + node2);
    nodes->erase(nodes->begin() + node1);
    nodes->push_back(size + 2);

    return matrix;
}

// rename it, cuz it is used for borh vectors and lists
// shouldve used: 
//      nodes.erase(nodes.begin() + node2);
// instead of all this iterator nonesense

//maybe there needs to be size-1 or sth...
list<list<int>> close_nodes_adj(list<list<int>> graph, int* size_old, int node1, int node2, vector<int>* nodes) {

    node1--;
    node2--;

    int size = *size_old;
    *size_old -= 1;

    nodes->erase(nodes->begin() + node2);
    nodes->erase(nodes->begin() + node1);
    nodes->push_back(size + 1);

    list<int> new_sub_list;

    list<list<int>>::iterator it = graph.begin();
    advance(it, node1);

    list<int>& sub_pointer = *it;
    list<int>::iterator sub_iterator;

    int check = 0;
    for (sub_iterator = sub_pointer.begin(); sub_iterator != sub_pointer.end(); sub_iterator++) {
        new_sub_list.push_back(*sub_iterator);
        if (*sub_iterator == node2) check = 1;
    }

    it = graph.begin();
    advance(it, node2);
    sub_pointer = *it;

    new_sub_list.merge(sub_pointer); // by mergin we are also deleting the list number 'node2'
    new_sub_list.unique();

    new_sub_list.remove(node1);
    new_sub_list.remove(node2);

    if (check == 1) new_sub_list.push_back(size);

    //here we are proly traversing throught the whole list of lists, but technically
    // we can only search for lists with indexes from 'new_sub_list' and do not even look in the rest of them

    // i did the 'new sub list' traversing but exactly zero line of this code is working properly
    for (auto iterator = new_sub_list.begin(); (iterator != new_sub_list.end()) && *iterator != size; ++iterator) {

        it = graph.begin();
        advance(it, *iterator);

        //looks like we pass teh link but not the actual memory pointer or something.
        // So it changes everything only in sub pointer
        sub_pointer = *it;

        sub_pointer.push_back(size);
        sub_pointer.remove(node1);
        sub_pointer.remove(node2);

        *it = sub_pointer;
        //        for (sub_iterator = sub_pointer.begin(); sub_iterator != sub_pointer.end(); sub_iterator++) {
        //            cout<< (*sub_iterator) << " is erased" << endl;
        //            if (*sub_iterator == node1 || *sub_iterator == node2) sub_pointer.erase(sub_iterator);
        //            //cout<< (*sub_iterator) << "_" << endl;
        //        }
    }

    it = graph.begin();
    advance(it, node2);
    graph.erase(it);

    it = graph.begin();
    advance(it, node1);
    graph.erase(it);

    graph.push_back(new_sub_list);

    //РІРµР·РґРµ РіРґРµ РІСЃС‚СЂРµС‡Р°РµС‚СЃСЏ node1 or node2 РјС‹:
    //СѓРґР°Р»СЏРµРј РёС…, РѕСЃС‚Р°Р»СЊРЅРѕРµ РІСЃРµ СЃРґРІРёРіР°РµС‚СЃСЏ Рё РІ РєРѕРЅС†Рµ РґРѕР±Р°РІР»СЏРµРј РЅРѕРІСѓСЋ РЅР°РґРѕ Рє СЃРїРёСЃРєСѓ
    //СЃР°Рј СЃРїРёСЃРєРё СЃ РёРЅРґРµРєСЃР°РјРё node1, node2 С‚РѕР¶Рµ СѓРґР°Р»СЏРµРј || list.remove()!

    //РёР»Рё РµС‰Рµ - new_sub_list СЃРѕРґРµСЂР¶РёС‚ СЃРїРёСЃРѕРє РІСЃРµС… РЅРѕРґ РєРѕС‚РѕСЂС‹Рµ РЅР°РґРѕ РёР·РјРµРЅРёС‚СЊ,
    // РѕСЃС‚Р°Р»СЊРЅС‹Рµ - РїРѕС„РёРі

    return graph;
}

vector<vector<int>> contract_nodes(vector<vector<int>> graph, int* size_old, int node1, int node2, vector<int>* nodes) {
    node1--;
    node2--;
    if (graph[node1][node2] == 0) {
        cout << "Nodes are not connected to each other. Operation can't be done." << endl;
        return graph;
    }

    int size = *size_old;
    *size_old -= 1;

    nodes->erase(nodes->begin() + node2);

    for (auto i = 0; i < size + 1; i++) {
        // if we ecnounter ref to 'node2' we make it a ref to 'node1'
        if (graph[i][node2] == 1) {
            graph[i][node1] = 1;
        }
        graph[i].erase(graph[i].begin() + node2); // erase ref to 'node2' completely

        if (graph[node1][i] == 1) continue;
        if (graph[node2][i] == 1) {
            graph[node1][i] = 1;
            continue;
        }
    }

    graph[node1][node1] = 0;

    graph.erase(graph.begin() + node2);

    return graph;
}

list<list<int>> contract_nodes_adj(list<list<int>> graph, int* size_old, int node1, int node2, vector<int>* nodes) {
    node1--;
    node2--;

    *size_old -= 1;

    int temp_check = 0;

    // get the list for node1
    list<list<int>>::iterator it = graph.begin();
    advance(it, node1);
    list<int>& sub_pointer = *it;

    int gggg = 0;
    for (auto iterator1 = sub_pointer.begin(); iterator1 != sub_pointer.end(); ++iterator1) {
        if (*iterator1 == node2) gggg++;
        if(gggg == 0 ) {
            cout << "Nodes are not connected to each other. Operation can't be done." << endl;
            return graph;
        }
    }

    // get the list for node2
    it = graph.begin();
    advance(it, node2);
    list<int>& sub_pointer2 = *it;

    sub_pointer.merge(sub_pointer2);
    sub_pointer.unique();
    sub_pointer.remove(node2);
    sub_pointer.remove(node1);

    /// some problem with 'sub_pointer2' it's a &list, should be just a list
    ///
    list<int> contracted_sub_list = sub_pointer;
    for (auto iterator1 = contracted_sub_list.begin(); iterator1 != contracted_sub_list.end(); ++iterator1) {

        it = graph.begin();
        //ther was *iterator1
        advance(it, *iterator1);

        sub_pointer2 = *it;

        //proly can add an if() to test if node is even present. If it's not in the line, 
        //then we don't have to do anything with the list at all and just continue; and move on.

        list<int> temp_list = sub_pointer2;

        for (list<int>::iterator iter = sub_pointer2.begin(); iter != sub_pointer2.end(); ++iter) {

            /// THERE IS AN INFINTE CYCLE IN CASE OF [3, 4] IT DELETES THE 4 (NODE2) AND THE SIZE OF LIST CHANGES AND ITER MESSES UP
            /// I HAVE NO IDEA FOR NOW HOW TO FIX THIS
            if (*iter == node1) temp_check = 1;
            if (*iter == node2) {
                if (temp_check == 1) {
                    temp_list.remove(node2);
                }
                else {
                    temp_list.remove(node2);
                    temp_list.push_back(node1);
                    temp_list.sort();
                }
            }
            //*it = sub_pointer2;
        }
        sub_pointer2 = temp_list;
        *it = sub_pointer2;

        temp_check = 0;

    }

    it = graph.begin();
    advance(it, node2);
    graph.erase(it);

    nodes->erase(nodes->begin() + node2);

    return graph;
}

vector<vector<int>> split_nodes(vector<vector<int>> graph, int* size_old, int node1, vector<int>* nodes) {

    nodes->push_back(*size_old + 1);


    int size = (*size_old - 1); // cuz notation starts from zero
    *size_old += 1;

    node1--;

    vector<int> new_node = graph[node1];
    new_node[node1] = 1;    // add a connection to splitted node
    new_node.push_back(0); //new node is not looping


    for (auto i = 0; i <= size; i++) {
        if (new_node[i] == 1) {
            graph[i].push_back(1);
        }
        else {
            graph[i].push_back(0);
        }
    }

    graph.push_back(new_node);

    return graph;
}

list<list<int>> split_nodes_adj(list<list<int>> graph, int* size_old, int node1, vector<int>* nodes) {
    nodes->push_back(*size_old + 1); //because we use pointer we also use '->'

    int size = (*size_old - 1); // cuz notation starts from zero
    *size_old += 1;

    node1--;

    list<list<int>>::iterator it = graph.begin();
    advance(it, node1);
    list<int> new_node = *it;

    new_node.push_back(node1);
    new_node.sort();

    list<int>& sub_pointer = *it;
    for (auto iter = new_node.begin(); iter != new_node.end(); ++iter) {
        it = graph.begin();
        advance(it, *iter);

        (*it).push_back(size + 1);
    }

    graph.push_back(new_node);

    return graph;
}

vector<vector<int>> merge_graphs(vector<vector<int>> graph1, vector<vector<int>> graph2, int size1, int size2, vector<int>* nodes, int* new_size) {
    int j = 0, i = 0;

    int size = max(size1, size2);
    vector<vector<int>> new_graph(size, vector<int>(size));

    for (int i = 0; i < size; i++) nodes->push_back(i + 1);
    *new_size = size;

    /// РµРїС‚Р° РіСЂР°С„ Р¶Рµ РЅРµ РЅР°РїСЂР°РІР»РµРЅРЅС‹Р№ Рё РЅРµРІР·РІРµС€РµРЅРЅС‹Р№ С‚СѓС‚ РјРѕР¶РЅРѕ РІ РІС‚РѕСЂРѕРј С†РёРєР»Рµ СЃРґРµР»Р°С‚СЊ i = j РёР»Рё С‡РµС‚ С‚РёРїР° С‚РѕРіРѕ РІСЂРѕРґРµ
    int mini = min(size1, size2);
    for (i = 0; i != mini; i++) {
        for (j = 0; j != mini; j++) {
            new_graph[i][j] = (graph1[i][j] | graph2[i][j]);
        }
    }

    //if we have two different matrix we then just copy everything what's left to new graph
    if (size1 != size2) {
        for (i = 0; i != size; i++) {
            for (j = mini; j != size; j++) {
                // add a check to determin which graph is bigger..
                if (size == size1) {
                    new_graph[i][j] = graph1[i][j];
                    new_graph[j][i] = new_graph[i][j];
                }
                else {
                    new_graph[i][j] = graph2[i][j];
                    new_graph[j][i] = new_graph[i][j];
                }
            }
        }
    }

    return new_graph;
}

vector<vector<int>> intersection(vector<vector<int>> graph1, vector<vector<int>> graph2, int size1, int size2, vector<int>* nodes, int* new_size) {

    int size = min(size1, size2);
    vector<vector<int>> new_graph(size, vector<int>(size));

    for (int i = 0; i < size; i++) nodes->push_back(i + 1);
    *new_size = size;

    for (int i = 0; i != size; i++) {
        for (int j = i; j != size; j++) {
            new_graph[i][j] = (graph1[i][j] & graph2[i][j]);
            new_graph[j][i] = new_graph[i][j];
        }
    }

    return new_graph;
}

vector<vector<int>> ring_sum(vector<vector<int>> graph1, vector<vector<int>> graph2, int size1, int size2, vector<int>* nodes, int* new_size) {

    int size = max(size1, size2);
    vector<vector<int>> new_graph(size, vector<int>(size));

    int mini = min(size1, size2);
    for (int i = 0; i != mini; i++) {
        for (int j = i; j != mini; j++) {
            new_graph[i][j] = (graph1[i][j] ^ graph2[i][j]); // this is a XOR (РѕС‚СЂРёС†Р°РЅРёРµ РР›Р)
            new_graph[j][i] = new_graph[i][j];
        }
    }

    // if graphs are not the same size, this code executes:
    // it just fills evertyhting with leftovers of the bigger graph
    if (size1 != size2) {
        for (int i = 0; i != size; i++) {
            for (int j = mini; j != size; j++) {
                if (size == size1) {
                    new_graph[i][j] = graph1[i][j];
                    new_graph[j][i] = new_graph[i][j];
                }
                else {
                    new_graph[i][j] = graph2[i][j];
                    new_graph[j][i] = new_graph[i][j];
                }
            }
        }
    }

    int temp_size = size;

    for (int i = 0; i < size; i++) nodes->push_back(i + 1);

    // I think we delete the leftover nodes and such here...
    for (int i = 0; i != temp_size; i++) {
        // if node's connections are all zero, like, it is separeted from the graph..
        if ((equal(new_graph[i].begin() + 1, new_graph[i].end(), new_graph[i].begin())) && (new_graph[i][0]) == 0) {
            //we erase all traces of this node
            for (int j = 0; j != temp_size; j++) new_graph[j].erase(new_graph[j].begin() + i);
            new_graph.erase(new_graph.begin() + i);

            nodes->erase(nodes->begin() + i);

            // now that we have a new graph, we reset the counter and check everything once again
            // it might be actually useless, but idk...
            temp_size--;
            i = 0;
        }
    }

    *new_size = new_graph.size();

    return new_graph;
}

vector<vector<int>> Cartesian_product(vector<vector<int>> graph1, vector<vector<int>> graph2, int size1, int size2, vector<int>* nodes, int* new_size) {

    int x = 0, y = 0;
    int temp = size1 * size2;
    vector<vector<int>> new_graph(temp, vector<int>(temp));

    for (int a = 0; a != size1; a++) {
        for (int b = 0; b != size2; b++) {
            for (int c = 0; c != size1; c++) {
                for (int d = 0; d != size2; d++) {
                    if (((a == c) && (graph2[b][d] == 1)) || ((b == d) && (graph1[a][c] == 1))) {
                        new_graph[x][y] = 1;
                    }
                    else {
                        new_graph[x][y] = 0;
                    }

                    //new_graph[x][y] = graph1[a][b] * graph2[c][d];
                    y++;
                }
            }
            x++;
            y = 0;
        }
    }

    *new_size = new_graph.size();
    for (int i = 0; i < *new_size; i++) nodes->push_back(i + 1);

    return new_graph;
}

void save_changes(vector<vector<int>> graph, int size, vector<int> nodes, vector<vector<int>>* g, int* s, vector<int>* n) {
    *g = graph;
    *s = size;
    *n = nodes;
}

void save_changes(list<list<int>> graph, int size, vector<int> nodes, list<list<int>>* g, int* s, vector<int>* n) {
    *g = graph;
    *s = size;
    *n = nodes;
}

int main() {
    ///DEBUG
    /*
        vector<vector<int>> debug_matrix ={{0,1,0,1,1},//1
                                           {1,0,1,0,0},//2
                                           {0,1,0,0,1},//3
                                           {1,0,0,0,1},//4
                                           {1,0,1,1,0},//5
                                           };
        list<list<int>> debug_list = convert_to_adj_list(debug_matrix, 5);
    */
    ///DEBUG
    srand(time(0)); //for random, always has to be set at zero, uses system time

    int size1, size2, choice, node1, node2; //choice; //input;
    char input;
    vector<int> nodesG1, nodesG2;

    // this might go in a function actually
    cout << "Enter the amount of first Graph's nodes" << endl;
    cin >> size1;
    vector<vector<int>> graph1 = create_Graph(size1, &nodesG1);

    cout << "Enter the amount of second Graph's nodes" << endl;
    cin >> size2;
    vector<vector<int>> graph2 = create_Graph(size2, &nodesG2);

    display_Graph(graph1, size1, "no.1", nodesG1);
    display_Graph(graph2, size2, "no.2", nodesG2);


    list<list<int>> adj_list1 = convert_to_adj_list(graph1, size1);
    list<list<int>> adj_list2 = convert_to_adj_list(graph2, size2);

    display_adj_list(adj_list1, size1, "no.1", nodesG1);
    display_adj_list(adj_list2, size2, "no.2", nodesG2);

    // I am not sure, but I'll just copy the values, and if the user chooses to save teh changes, then it'll overwrite them..

    while (1) {
        int t_size1 = size1;
        int t_size2 = size2;
        vector<vector<int>> t_graph1 = graph1;
        vector<vector<int>> t_graph2 = graph2;
        vector<int> t_nodesG1 = nodesG1;
        vector<int> t_nodesG2 = nodesG2;
        list<list<int>> t_list1 = adj_list1;
        list<list<int>> t_list2 = adj_list2;

        //template for new graph
        int G3_size;
        vector<int> G3_nodes;
        vector<vector<int>> G3;

        cout << "Choose, which operation you would like to perform:" << endl;
        cout << "1 - closing nodes (matrix form)" << endl << "2 - closing nodes (adj. list form)" << endl;
        cout << "3 - contracting nodes (matrix form)" << endl << "4 - contracting nodes (adj. list form)" << endl;
        cout << "5 - splitting node (matrix form)" << endl << "6 - splitting node (adj. list form)" << endl << "----" << endl;
        cout << "7 - merge graphs" << endl << "8 - intersect graphs" << endl << "9 - ring sum for graphs" << endl << "----" << endl;
        cout << "c - cartesian product of graphs" << endl << "----" << endl;
        //cout << "r - generate new graphs" << endl << endl;
        cout << "q - quit the program" << endl << endl;

        cin >> input;

        switch (input) {
            //1
        case '1':
            cout << "Choose the graph for the operation (1 or 2):" << endl;
            cin >> choice;

            cout << "Which nodes should be closed?" << endl;
            cin >> node1;
            cin >> node2;
            if (node1 > node2) swap(node1, node2); //we ensure that node1 < node2. It's just so we don't do this later

            if (choice == 1) {
                t_graph1 = close_nodes(t_graph1, &t_size1, node1, node2, &t_nodesG1);
                display_Graph(t_graph1, t_size1, "no.1, after operation 'closing' ", t_nodesG1);
            }

            else {
                t_graph2 = close_nodes(t_graph2, &t_size2, node1, node2, &t_nodesG2);
                display_Graph(t_graph2, t_size2, "no.2, after operation 'closing' ", t_nodesG2);
            };

            cout << "Would you like to save the changes? (Y / N)" << endl;
            cin >> input;
            switch (input) {
            case 'y':
                if (choice == 1) save_changes(t_graph1, t_size1, t_nodesG1, &graph1, &size1, &nodesG1);
                else save_changes(t_graph2, t_size2, t_nodesG2, &graph2, &size2, &nodesG2);
            case 'n':
                break;
            }

            break;
            //2
        case '2':
            cout << "Choose the graph for the operation (1 or 2):" << endl;
            cin >> choice;

            cout << "Which nodes should be closed?" << endl;
            cin >> node1;
            cin >> node2;
            if (node1 > node2) swap(node1, node2); //we ensure that node1 < node2. It's just so we don't do this later

            if (choice == 1) {
                t_list1 = close_nodes_adj(t_list1, &t_size1, node1, node2, &t_nodesG1);
                display_adj_list(t_list1, t_size1, "no.1, after operation 'closing' ", t_nodesG1);
            }

            else {
                t_list2 = close_nodes_adj(t_list2, &t_size2, node1, node2, &t_nodesG2);
                display_adj_list(t_list2, t_size2, "no.2, after operation 'closing' ", t_nodesG2);
            };

            cout << "Would you like to save the changes? (Y / N)" << endl;
            cin >> input;
            switch (input) {
            case 'y':
                if (choice == 1) save_changes(t_list1, t_size1, t_nodesG1, &adj_list1, &size1, &nodesG1);
                else save_changes(t_list2, t_size2, t_nodesG2, &adj_list2, &size2, &nodesG2);
            case 'n':
                break;
            }

            break;
            //3
        case '3':
            cout << "Choose the graph for the operation (1 or 2):" << endl;
            cin >> choice;

            cout << "Which nodes should be closed?" << endl;
            cin >> node1;
            cin >> node2;
            if (node1 > node2) swap(node1, node2); //we ensure that node1 < node2. It's just so we don't do this later

            if (choice == 1) {
                t_graph1 = contract_nodes(t_graph1, &t_size1, node1, node2, &t_nodesG1);
                display_Graph(t_graph1, t_size1, "no.1, after operation 'contraction' ", t_nodesG1);
            }

            else {
                t_graph2 = contract_nodes(t_graph2, &t_size2, node1, node2, &t_nodesG2);
                display_Graph(t_graph2, t_size2, "no.2, after operation 'contraction' ", t_nodesG2);
            };

            cout << "Would you like to save the changes? (Y / N)" << endl;
            cin >> input;
            switch (input) {
            case 'y':
                if (choice == 1) save_changes(t_graph1, t_size1, t_nodesG1, &graph1, &size1, &nodesG1);
                else save_changes(t_graph2, t_size2, t_nodesG2, &graph2, &size2, &nodesG2);
            case 'n':
                break;
            }

            break;
            //4
        case '4':
            cout << "Choose the graph for the operation (1 or 2):" << endl;
            cin >> choice;

            cout << "Which nodes should be contracted?" << endl;
            cin >> node1;
            cin >> node2;
            if (node1 > node2) swap(node1, node2); //we ensure that node1 < node2. It's just so we don't do this later

            if (choice == 1) {
                t_list1 = contract_nodes_adj(t_list1, &t_size1, node1, node2, &t_nodesG1);
                display_adj_list(t_list1, t_size1, "no.1, after operation 'contraction' ", t_nodesG1);
            }

            else {
                t_list2 = close_nodes_adj(t_list2, &t_size2, node1, node2, &t_nodesG2);
                display_adj_list(t_list2, t_size2, "no.2, after operation 'contraction' ", t_nodesG2);
            };

            cout << "Would you like to save the changes? (Y / N)" << endl;
            cin >> input;
            switch (input) {
            case 'y':
                if (choice == 1) save_changes(t_list1, t_size1, t_nodesG1, &adj_list1, &size1, &nodesG1);
                else save_changes(t_list2, t_size2, t_nodesG2, &adj_list2, &size2, &nodesG2);
            case 'n':
                break;
            }

            break;
            //5
        case '5':
            cout << "Choose the graph for the operation (1 or 2):" << endl;
            cin >> choice;

            cout << "Which node should be splitted?" << endl;
            cin >> node1;

            if (choice == 1) {
                t_graph1 = split_nodes(t_graph1, &t_size1, node1, &t_nodesG1);
                display_Graph(t_graph1, t_size1, "no.1, after operation 'splitting' ", t_nodesG1);
            }

            else {
                t_graph2 = split_nodes(t_graph2, &t_size2, node1, &t_nodesG2);
                display_Graph(t_graph2, t_size2, "no.2, after operation 'splitting' ", t_nodesG2);
            };

            cout << "Would you like to save the changes? (Y / N)" << endl;
            cin >> input;
            switch (input) {
            case 'y':
                if (choice == 1) save_changes(t_graph1, t_size1, t_nodesG1, &graph1, &size1, &nodesG1);
                else save_changes(t_graph2, t_size2, t_nodesG2, &graph2, &size2, &nodesG2);
            case 'n':
                break;
            }

            break;
            //6
        case '6':
            cout << "Choose the graph for the operation (1 or 2):" << endl;
            cin >> choice;

            cout << "Which node should be splitted?" << endl;
            cin >> node1;

            if (choice == 1) {
                t_list1 = split_nodes_adj(t_list1, &t_size1, node1, &t_nodesG1);
                display_adj_list(t_list1, t_size1, "no.1, after operation 'splitting' ", t_nodesG1);
            }

            else {
                t_list2 = split_nodes_adj(t_list2, &t_size2, node1, &t_nodesG2);
                display_adj_list(t_list2, t_size2, "no.2, after operation 'splitting' ", t_nodesG2);
            };

            cout << "Would you like to save the changes? (Y / N)" << endl;
            cin >> input;
            switch (input) {
            case 'y':
                if (choice == 1) save_changes(t_list1, t_size1, t_nodesG1, &adj_list1, &size1, &nodesG1);
                else save_changes(t_list2, t_size2, t_nodesG2, &adj_list2, &size2, &nodesG2);
            case 'n':
                break;
            }

            break;
            //7
        case '7':
            G3 = merge_graphs(t_graph1, t_graph2, t_size1, t_size2, &G3_nodes, &G3_size);
            display_Graph(G3, G3_size, "no.3, after merging two other graphs", G3_nodes);
            cout << endl;
            break;
            //8
        case '8':
            G3 = intersection(t_graph1, t_graph2, t_size1, t_size2, &G3_nodes, &G3_size);
            display_Graph(G3, G3_size, "no.3, after intersecting two other graphs", G3_nodes);
            cout << endl;
            break;
            //9
        case '9':
            G3 = ring_sum(t_graph1, t_graph2, t_size1, t_size2, &G3_nodes, &G3_size);
            display_Graph(G3, G3_size, "no.3, which is a ring sum of two other graphs", G3_nodes);
            cout << endl;
            break;
            //10
        case 'c':
            G3 = Cartesian_product(t_graph1, t_graph2, t_size1, t_size2, &G3_nodes, &G3_size);
            display_Graph(G3, G3_size, "no.3, which is a Cartesian product of two other graphs", G3_nodes);
            cout << endl;
            break;
        case 'q':
            cout << "Terminating the process...";
            return 0;

            //case 'r':
        default:
            cout << "Incorrect input, try again" << endl << endl;
            fflush(stdin);
            //cin >> ws;
            //cin.clear();
            //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    /// DEBUG ///
    /*
        vector<vector<int>> debug_graph = {{0,0,1,0,0,0,0},//1
                                           {0,0,0,1,1,0,0},//2
                                           {1,0,0,1,0,0,1},//3
                                           {0,1,1,0,1,1,0},//4
                                           {0,1,0,1,0,0,1},//5
                                           {0,0,0,1,0,0,0},//6
                                           {0,0,1,0,1,0,0},//7
                                           };

        vector<vector<int>> debug_jopa =  {{0,1,1,1,0,1,1},//1
                                           {1,0,0,0,0,1,1},//2
                                           {1,0,0,0,1,1,0},//3
                                           {1,0,0,0,1,0,0},//4
                                           {0,0,1,1,0,0,0},//5
                                           {1,1,1,0,0,0,1},//6
                                           {1,1,0,0,0,1,0},//7
                                           };
        vector<vector<int>> debug_jopa =  {{0,1,1,1,0,1},//1
                                           {1,0,0,0,0,1},//2
                                           {1,0,0,0,1,1},//3
                                           {1,0,0,0,1,0},//4
                                           {0,0,1,1,0,0},//5
                                           {1,1,1,0,0,0},//6
                                           };
        int debug_size = 7, jopa_size = 6;
        vector<int> debug_nodes;
        //for (int i = 0; i < debug_size; i++) debug_nodes.push_back(i+1);

        //display_Graph(debug_graph, debug_size, "TEST", debug_nodes);
        //cout << endl;

            //debug_graph = split_nodes(debug_graph, &debug_size, 3, &debug_nodes);
            //cout << "Razsheplenie check" << endl;

            //debug_graph = contract_nodes(debug_graph, &debug_size, 2, 3, &debug_nodes);
            //cout << "Styagivanie check" << endl;

            vector<vector<int>> mergeee;
            int new_size = 0;

                //vector<vector<int>> wood = create_Graph(4);
                //vector<vector<int>> stone = create_Graph(4);

                vector<vector<int>> wood ={{0,0,1},//1
                                           {0,0,1},//2
                                           {1,1,0},//3
                                           };
                vector<vector<int>> stone={{0,0,0},//1
                                           {0,0,1},//2
                                           {0,1,0},//3
                                           };

                mergeee = Cartesian_product(wood, stone, 3, 3, &debug_nodes, &new_size);
                display_Graph(mergeee, new_size, "ETO SHTOOO VSEEEEE 6 LABA GOTOVAAAA???????", debug_nodes);
                cout << "Dekartovo prouzvedenie check" << endl;

            //mergeee = ring_sum(wood, stone, 4, 4, &debug_nodes, &new_size);
            //display_Graph(mergeee, new_size, "Ring Sum", debug_nodes);
            //cout << "Kolcevaya summa check" << endl;

            //mergeee = merge_graphs(debug_graph, debug_jopa, debug_size, jopa_size, &debug_nodes, &new_size);
            //display_Graph(mergeee, new_size, "Eddie", debug_nodes);
            //cout << "Ob'edinenie check" << endl;

            //mergeee = intersection(debug_graph, debug_jopa, debug_size, jopa_size, &debug_nodes, &new_size);
            //display_Graph(mergeee, new_size, "Eddie", debug_nodes);
            //cout << "Peresechenie check" << endl;

        //list<list<int>> debug_list = convert_to_adj_list(debug_graph, debug_size);
        display_adj_list(debug_list, debug_size, "TEST_list", debug_nodes);

            //debug_list = split_nodes_adj(debug_list, &debug_size, 3, &debug_nodes);
            //cout << "Razsheplenie check" << endl;

            //debug_list = contract_nodes_adj(debug_list, 3, 4, &debug_nodes);
            //cout << "Styagivanie check" << endl;

        ///debug_list = close_nodes_adj(debug_list, 5, 7, debug_size);
        */

    return 0;
}