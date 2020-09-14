#include "pch.h"

#include <cstdlib>

#include <exception>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d) : data(d), left(nullptr), right(nullptr) { }
};

//Sample tree
//     1
//  2     3
// 4 5  6

void longestPath(const Node* root);

int main(int argc, char* argv[]) {
    Node* root = nullptr;
    //Create tree for testing
    root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);

    try {
        longestPath(root);
    } catch (string& e) {
        cerr << e << endl;
        return EXIT_FAILURE;
    }
       
    return EXIT_SUCCESS;
}

void longestPath(const Node* root) {
    if (!root) {
        throw string("no root provided");
    }

    //Auxiliary struct to keep track of the current path
    struct Path {
        const Node* current;
        int cost;
        vector<int> nodes;
        Path(const Node* c) : current(c), cost(0) {}
        Path augmentPath(const Node* newNode) {
            Path augmented = Path(newNode);
            //Add the new cost
            augmented.cost = this->cost + newNode->data;
            // Add the new node
            augmented.nodes = this->nodes;
            augmented.nodes.push_back(newNode->data);
            return augmented;
        }
    };

    // Start a new path from the root
    Path start = Path(root);
    start.cost = root->data;
    start.nodes.push_back(root->data);
    
    //Our best path (so far) is the root
    Path bestPath = start;

    // Store it in the queue
    queue<Path> q;
    q.push(start);

    //Start transversing the whole tree, since it's a queue we are 
    //transversing it wide first
    while (!q.empty()) {
        Path currentPath = q.front(); // We need to explicitlly took it from queue
        q.pop(); //Since pop does not return anything
        // If we have a left child, add it to queue
        if (currentPath.current->left != nullptr) {
            // Create an augmenting path
            Path leftPath = currentPath.augmentPath(currentPath.current->left);
            // Put the augmented path in the queue
            q.push(leftPath);
        }
        // If we have a right child, add it to queue
        if (currentPath.current->right != nullptr) {
            // Create an augmenting path
            Path rightPath = currentPath.augmentPath(currentPath.current->right);
            // Put the augmented path in the queue
            q.push(rightPath);
        }       
        //Check if we are a leaf
        if (currentPath.current->left == nullptr && 
            currentPath.current->right == nullptr) {
            //Check if we improve our best (higher) cost
            if (currentPath.cost > bestPath.cost) {
                bestPath = currentPath;
            }
        }
    }
    //If we reach here we have the best path, print the result
    for (size_t i = 0; i < bestPath.nodes.size(); ++i) {
        cout << bestPath.nodes[i] << " ";
    }
    cout << ": " << bestPath.cost << endl;
}
