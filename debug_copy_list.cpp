#include <bits/stdc++.h>
using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

// YOUR CODE (with issues):
class Solution_Wrong {
public:
    Node* copyRandomList(Node* head) {
        Node *p, *q;
        p = head;
        while(p) {
            Node *t = new Node(p -> val);
            t -> next = p -> next;
            p -> next = t;
            p = p -> next -> next;
        }
        p = head;
        while(p) {
            Node *t = p -> next;
            if(p -> random) t -> random = p -> random -> next;
            else t -> random = nullptr;
            p = p -> next -> next;
        }

        Node *dummy = new Node(-1);
        p = head;
        dummy -> next = p -> next;  // ISSUE 1: This sets dummy to first copy, but doesn't build the list properly
        while(p) {
            Node *t = p -> next;
            if(p -> next) t -> next = p -> next -> next;  // ISSUE 2: This does nothing useful
            else t -> next = nullptr;
            p = p -> next -> next;
        }

        return dummy -> next;
    }
};

// CORRECTED VERSION:
class Solution_Correct {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;  // ISSUE 3: Missing null check
        
        // Step 1: Create copy nodes and interleave them
        Node* p = head;
        while (p) {
            Node* copy = new Node(p->val);
            copy->next = p->next;
            p->next = copy;
            p = copy->next;
        }
        
        // Step 2: Set random pointers for copy nodes
        p = head;
        while (p) {
            if (p->random) {
                p->next->random = p->random->next;
            }
            p = p->next->next;
        }
        
        // Step 3: Separate original and copy lists properly
        Node* dummy = new Node(-1);
        Node* copyHead = dummy;
        p = head;
        
        while (p) {
            Node* copy = p->next;
            Node* next = copy->next;
            
            // Extract copy node and add to copy list
            copyHead->next = copy;
            copyHead = copy;
            
            // Restore original list
            p->next = next;
            p = next;
        }
        
        Node* result = dummy->next;
        delete dummy;
        return result;
    }
};

int main() {
    // Test the corrected version
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    
    // Set random pointers
    head->random = head->next->next;  // 1->3
    head->next->random = head;        // 2->1
    head->next->next->random = head->next; // 3->2
    
    Solution_Correct solution;
    Node* copy = solution.copyRandomList(head);
    
    // Print original list
    cout << "Original: ";
    Node* p = head;
    while (p) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
    
    // Print copy list
    cout << "Copy: ";
    p = copy;
    while (p) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
    
    return 0;
} 