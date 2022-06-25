#include "EmployeeTree.hpp"

EmployeeTree::EmployeeTree() {
    root = NULL;
}

void deleteNode(EmployeeNode *node) {
    if (node == NULL) {
        return;
    }
    
    deleteNode(node->left);                  
    delete node;
    deleteNode(node->right);            
}

EmployeeTree::~EmployeeTree() {
    deleteNode(root);
}



void _printEmployeeDirectory(EmployeeNode *node) {
    if (node == NULL) {
        return;
    }
    
    _printEmployeeDirectory(node->left);                  // Most left Value
    cout << node->empId << ", " << node->empName << endl; // Start printing
    _printEmployeeDirectory(node->right);                 // Continue right
}

void EmployeeTree::printEmployeeDirectory() {
    if (root == NULL) {
        cout << "Tree is Empty. Cannot print." << endl;
    } else {
        _printEmployeeDirectory(root);
    }
}


void EmployeeTree::addEmployee(int empId, string empName, int empLevel, string empPhone, int empJoiningYear) {
    EmployeeNode *newNode = new EmployeeNode;
    newNode->empId = empId;
    newNode->empName = empName;
    newNode->empLevel = empLevel;
    newNode->empPhone = empPhone;
    newNode->empJoiningYear = empJoiningYear;

    if (root == NULL) {
        root = newNode;
        return;
    }

    EmployeeNode *node = root;
    while (node != NULL) {
        if (empId < node->empId) {
            if (node->left != NULL) {
                node = node->left;
            } else {
                node->left = newNode;
                return;
            }
        } else if (empId > node->empId) {
            if (node->right != NULL) {
                node = node->right;
            } else {
                node->right = newNode;
                return;
            }
        }
    }
}

void EmployeeTree::findEmployee(int empId) {
    EmployeeNode *node = root;
    while (node != NULL) {
        if (empId < node->empId) {
            node = node->left;
        } else if (empId > node->empId) {
            node = node->right;
        } else { // Found Node
            cout << "Employee Information" << endl;
            cout << "====================" << endl;
            cout << "ID     : " << node->empId << endl;
            cout << "Name   : " << node->empName << endl;
            cout << "Level  : " << node->empLevel << endl;
            cout << "Phone  : " << node->empPhone << endl;
            cout << "Joined : " << node->empJoiningYear << endl;
            return; // Function completed
        }
    }
    cout << "Employee not found." << endl; // No Employee Found
}

void _queryEmployees(EmployeeNode *node, int level, int year) {
    if (node == NULL) {
        return;
    }
    if (node->empLevel >= level && node->empJoiningYear > year) {
        cout << "====================" << endl;
        cout << "ID     : " << node->empId << endl;
        cout << "Level  : " << node->empLevel << endl;
        cout << "Joined : " << node->empJoiningYear << endl;             
    }
    _queryEmployees(node->left, level, year);            
    _queryEmployees(node->right, level, year);  
}

void EmployeeTree::queryEmployees(int level, int year)
{
    if (root == NULL) {
        cout << "Tree is Empty. Cannot query employees directory" << endl;
    } else {
        cout << "Employees who joined after " << year << " and are at least at level " << level << ":" << endl;
        _queryEmployees(root, level, year);
    }
}

void _printLevelNodes(EmployeeNode *node, int node_level, int current_level) {
    if (node == NULL) {return;}
    if(current_level == node_level) {
        cout << node->empId << ", " << node->empName << endl;
    }
    _printLevelNodes(node->left, node_level, current_level+1);                  
    _printLevelNodes(node->right, node_level, current_level+1);                
}

void EmployeeTree::printLevelNodes(int node_level) {
    if (root == NULL) {
        cout << "Tree is Empty. Cannot print." << endl;
    } else {
        _printLevelNodes(root, node_level, 0);
    }
}

int _getKthLowestEmployeeID(EmployeeNode *root, int k, int *count) {
    if (root == NULL) {
        return 0;
    }
    int l = _getKthLowestEmployeeID(root->left, k, count);
    if (l != 0){
        return l;
    }
    if (++*count == k) {
        return root->empId;
    }
    return _getKthLowestEmployeeID(root->right, k, count);  
}

int EmployeeTree::getKthLowestEmployeeID(int k) {
    if (root == NULL) {
        cout << "Tree is Empty. Cannot find Employee." << endl;
        return 0;
    } else {
        //EmployeeNode *node = root;
        int count = 0;
        return _getKthLowestEmployeeID(root, k, &count);
    }
}