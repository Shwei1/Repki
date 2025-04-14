#include <iostream>
#include <cstdlib>

// C, C++
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Tree
{
public:

    TreeNode *head;

    Tree() : head(NULL) {};

    ~Tree(){
        clear(head);
    }

    void clear(TreeNode* node){
        if (!node) return;
        clear(node->left); 
        clear(node->right);
        delete node;
    }

    void Insert(int val){
        TreeNode* newnode = new TreeNode(val);

        if (!head){
            head = newnode;
            return;
        }

        TreeNode* current = head;
        TreeNode* parent = NULL;

        while (current){
            parent = current;

            if (current->val > val){
                current = current->left;
            }
            else if (current->val <= val)
                current = current->right;
            // else {
            //     delete newnode;
            //     return;
            // }
            
        }

        if (val >= parent->val)
            parent->right = newnode;
        else
            parent->left = newnode;
    }

    static bool AreSameNodes(TreeNode* first, TreeNode* second){
        if (!first && !second){
            return true;
        }
        else if ((!first && second) || (!second && first)){
            return false;
        }

        bool ok = first->val == second->val;

        return ok && AreSameNodes(first->left, second->left) 
                            && AreSameNodes(first->right,
                                             second->right);
    }

    int IsSameTree(Tree *p){
        TreeNode* curr2 = head;
        TreeNode* curr1 = p->head;

        return AreSameNodes(curr1, curr2) ? 1 : 0;
    }
};

auto main(void) -> int {
    int n;
    std::cin >> n;
    
    Tree t1;

    for (int i = 0; i < n; i++){
        int el;
        std::cin >> el;
        t1.Insert(el);
    }

    int m;
    std::cin >> m;
    
    Tree t2;

    for (int i = 0; i < m; i++){
        int el;
        std::cin >> el;
        t2.Insert(el);
    }
    
    std::cout << t1.IsSameTree(&t2) << std::endl;
    return 0;
}
