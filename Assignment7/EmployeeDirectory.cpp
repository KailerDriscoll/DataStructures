#include "EmployeeDirectory.hpp"

// [HELPER FUNCTIONS]
char EmployeeDirectory::getLastInitial(string name) {
    int found_ix = name.find(' ');

    if (found_ix != string::npos)
        return name[found_ix + 1];

    return '\0';
}

void EmployeeDirectory::printEmployee(LLNode* n) {
    if (n == NULL) {
        cout << "LLNode is NULL." << endl;
    }
    else {
        cout << "Employee Information" << endl;
        cout << "====================" << endl;
        cout << "ID     : " << n->empId << endl;
        cout << "Name   : " << n->empName << endl;
        cout << "Level  : " << n->empLevel << endl;
        cout << "Phone  : " << n->empPhone << endl;
        cout << "Joined : " << n->empJoiningYear << endl;
    }
}


// [TO BE IMPLEMENTED]
// ----------------------------------------------------------------------------

EmployeeDirectory::EmployeeDirectory() {
    root = NULL;
}

// ----------------------------------------------------------------------------

void deleteEmp(TreeNode* node) {
    if (node == NULL) {
        return;
    }

    deleteEmp(node->left);
    deleteEmp(node->right);
    
    LLNode* emp;
    while (node->head != NULL) {
        emp = node->head;
        node->head = emp->next;
        delete emp;
        emp = NULL;
    }
    delete node;
    node = NULL;
}

EmployeeDirectory::~EmployeeDirectory() {
    deleteEmp(root);
}

// ----------------------------------------------------------------------------

TreeNode* _searchCharNode(TreeNode* node, char key) {
    if (node == NULL) {
        return NULL;
    }

    if (key < node->lastInitial) {
        return _searchCharNode(node->left, key);
    } else if (key > node->lastInitial) {
        return _searchCharNode(node->right, key);
    } else {
        return node;
    }
    
    return NULL;
    
}

TreeNode* EmployeeDirectory::searchCharNode(char key) {
    if (root != NULL) {
        TreeNode* res = _searchCharNode(root,key);
        return res;
    }
    return NULL;
}

// ----------------------------------------------------------------------------

void _showEmployeeDirectory(TreeNode* node) {
    if (node == NULL) {
        
        return;
    }
 

    _showEmployeeDirectory(node->left);

    if (node->parent == NULL) {
        cout << "[Employees with lastInitial=" << node->lastInitial << ", parent=" << " " << "]" << endl;
    } else {
        cout << "[Employees with lastInitial=" << node->lastInitial << ", parent=" << node->parent->lastInitial << "]" << endl;
    }

    LLNode* ll = node->head;
    if (ll == NULL) {cout << "No employees found." << endl;}
    while (ll != NULL) {
        cout << "> " << ll->empName << ", " << ll->empPhone << ", " << ll->empId << endl;
        ll = ll->next;
    }
    cout << "---------------------------------------" << endl;

    _showEmployeeDirectory(node->right);
}

void EmployeeDirectory::showEmployeeDirectory() 
{   
    if (root != NULL) {
        _showEmployeeDirectory(root);
    }
}

// ----------------------------------------------------------------------------

LLNode* EmployeeDirectory::searchEmployee(int empId, string empName) {
    char lastInitial = getLastInitial(empName);
    TreeNode* tree = searchCharNode(lastInitial);
    if (tree == NULL) {return NULL;}
    LLNode *ll = tree->head;
    while(ll != NULL) {
        if (empId == ll->empId && !empName.compare(ll->empName)) {
            return ll;
        }
        ll = ll->next;
    }
    return NULL;

}

// ----------------------------------------------------------------------------

void EmployeeDirectory::insertEmployee(int empId, string empName, int empLevel, string empPhone, int empJoiningYear) {
    
    //Locate Tree Node
    char lastInitial = getLastInitial(empName);
    TreeNode* tNode = searchCharNode(lastInitial);

    if (tNode == NULL) { //add new Tree Node
        TreeNode* newNode = new TreeNode(lastInitial);

        if (root == NULL) { // Init Tree
            root = newNode;
        } else {
            tNode = root; // Use tNode as a traversing Node
            while ((tNode->left) || (tNode->right)) {
                if (lastInitial < tNode->lastInitial && tNode->left != NULL) {
                    tNode = tNode->left;
                } else if (lastInitial > tNode->lastInitial && tNode->right != NULL){
                    tNode = tNode->right;
                } else {
                    break;
                }
            }
            if (lastInitial < tNode->lastInitial) {
                tNode->left = newNode;
                newNode->parent = tNode;
            } else {
                tNode->right = newNode;
                newNode->parent = tNode;
            }
            
        }
        tNode = newNode;
    }

    //Move through LL until correct location
    LLNode* llnode = new LLNode(empId,empName,empLevel,empPhone,empJoiningYear);
    LLNode* lltraverse = tNode->head;
    if (lltraverse == NULL) {
        tNode->head = llnode;
    } else {
        if (empId < lltraverse->empId) {
            llnode->next = tNode->head;
            tNode->head = llnode;
        } else {
            while(lltraverse->next != NULL) {
                if (empId < lltraverse->next->empId) {
                    break;
                }
                lltraverse = lltraverse->next;
            }
            //Reorder LL
            LLNode* temp = lltraverse->next;
            lltraverse->next = llnode;
            llnode->next = temp;
        }
        
    }

}

// ----------------------------------------------------------------------------

void EmployeeDirectory::removeEmployee(int empId, string empName) {
    // Find Tree Node
    char lastInitial = getLastInitial(empName);
    TreeNode* tree = searchCharNode(lastInitial);
    if (tree == NULL) {
        cout << "Employee not found."<< endl;
        return;
    }

    // Find LL Node
    LLNode* llnode = tree->head;
    if (empId == llnode->empId) { //Check Head
        if (!empName.compare(llnode->empName)) {
            tree->head = llnode->next;
            delete llnode;
            llnode = NULL;
            return;
        } else {
            cout << "Employee not found."<< endl;
            return;
        }
    }
    else if (llnode->next != NULL) { // Not head
        while (empId != llnode->next->empId && llnode->next != NULL) {
            llnode = llnode->next;
        }
    }

    // Reorder
    if (empName.compare(llnode->next->empName) || empId != llnode->next->empId) {
        cout << "Employee not found."<< endl;
    } else {
        LLNode* temp = llnode->next;
        llnode->next = llnode->next->next;
        delete temp;
        temp = NULL;
    }
}

// ----------------------------------------------------------------------------

void EmployeeDirectory::leftRotate(TreeNode* curr) {
    if (curr->right != NULL) {
        TreeNode* y = curr->right;
        TreeNode* yl = y->left;
        if (curr->parent != NULL) {
            if (curr->parent->left == curr) {
                curr->parent->left = y;
                y->parent = curr->parent;
                curr->parent = y;
                curr->right = yl;
                yl->parent = curr;
                y->left = curr;
            } else {
                curr->parent->right = y;
                y->parent = curr->parent;
                curr->parent = y;
                curr->right = yl;
                yl->parent = curr;
                y->left = curr;
            }
        } else {
                root = y;
                y->parent = NULL;
                curr->parent = y;
                curr->right = yl;
                if (yl != NULL) {
                    yl->parent = curr;
                }
                y->left = curr;
        }
    }
}

// ----------------------------------------------------------------------------
