#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <queue>

using namespace std;

// Structure for Tree Node (Binary Tree)
struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to define precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to check if character is an operand (digit)
bool isOperand(char c) {
    return isdigit(c);
}


/*
This function is used to clear the tree after use to save memory
*/
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;

    // Recursively delete left and right subtrees
    deleteTree(root->left);
    deleteTree(root->right);

    // Delete current node
    delete root;
}

// Function to convert Infix to Postfix
string infixToPostfix(const string& expression) {
    stack<char> operators;
    string postfix = "";

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        // Skip spaces
        if (isspace(c)) continue;

        // If character is an operand (digit), add it to the postfix result
        if (isOperand(c)) {
            postfix += c;
        } 
        // If character is an opening parenthesis, push it to the operator stack
        else if (c == '(') {
            operators.push(c);
        } 
        // If character is a closing parenthesis, pop until opening parenthesis is found
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Pop the opening '('
        } 
        // If character is an operator
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    // Pop any remaining operators in the stack
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Function to evaluate a Postfix expression
int evaluatePostfix(const string& postfix) {
    stack<int> s;

    for (char c : postfix) {
        if (isspace(c)) continue;

        if (isOperand(c)) {
            s.push(c - '0'); // Convert char to integer and push onto the stack
        } else {
            int right = s.top(); s.pop(); // Pop second operand
            int left = s.top(); s.pop(); // Pop first operand

            switch (c) {
                case '+': s.push(left + right); break;
                case '-': s.push(left - right); break;
                case '*': s.push(left * right); break;
                case '/': s.push(left / right); break;
            }
        }
    }

    return s.top(); // The final result is the only value left in the stack
}

// Function to create an expression tree from infix expression
TreeNode* infixToExpressionTree(const string& expression) {
    stack<TreeNode*> values;
    stack<char> operators;

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        // If current character is a space, skip it
        if (isspace(c)) continue;

        // If character is an operand (digit), create a tree node and push it
        if (isOperand(c)) {
            stringstream ss;
            ss << c; // Current digit
            TreeNode* node = new TreeNode(ss.str());
            values.push(node);
        } 
        // If character is an opening parenthesis, push it to the operator stack
        else if (c == '(') {
            operators.push(c);
        } 
        // If character is a closing parenthesis, resolve the sub-expression
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                TreeNode* right = values.top(); values.pop();
                TreeNode* left = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                TreeNode* opNode = new TreeNode(string(1, op));
                opNode->left = left;
                opNode->right = right;
                values.push(opNode);
            }
            operators.pop(); // Pop the opening '('
        } 
        // If character is an operator
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                TreeNode* right = values.top(); values.pop();
                TreeNode* left = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                TreeNode* opNode = new TreeNode(string(1, op));
                opNode->left = left;
                opNode->right = right;
                values.push(opNode);
            }
            operators.push(c);
        }
    }

    // Process remaining operators
    while (!operators.empty()) {
        TreeNode* right = values.top(); values.pop();
        TreeNode* left = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        TreeNode* opNode = new TreeNode(string(1, op));
        opNode->left = left;
        opNode->right = right;
        values.push(opNode);
    }

    return values.top(); // Root of the expression tree
}

// Function to print the tree by levels (Level-order traversal)
void printTreeByLevels(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int nodeCount = q.size();
        cout << "Level " << level << ": ";
        
        while (nodeCount > 0) {
            TreeNode* node = q.front();
            cout << node->value << " ";
            q.pop();
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);

            nodeCount--;
        }
        cout << endl;
        level++;
    }
}

int main() {
    string expression;
    
    // Get the expression from user input
    cout << "Enter an infix expression (e.g., '(1 + 2) * 3 + (4 * 5) - 6'): ";
    getline(cin, expression);

    // Convert infix to postfix
    string postfix = infixToPostfix(expression);
    cout << "Postfix Expression: " << postfix << endl;

    // Evaluate the postfix expression
    int result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;

    // Build the expression tree
    TreeNode* root = infixToExpressionTree(expression);

    // Print the expression tree by levels
    printTreeByLevels(root);

    // Clean tree to save memory
    deleteTree(root);

    return 0;
}
