#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<stack>
#include<queue>
#include<deque>

using namespace std;
class binarytree
{
    int data;
    binarytree* left = {};
    binarytree* right = {};
    void clear()
    {
        delete left;
        left = 0;
        delete right;
        right = 0;

    }
public:
    binarytree(int data) :data(data) {}

    void inorder_stack()
    {
        stack<pair<binarytree*, bool>>s;
        s.push({ this,0 });
        while (!s.empty())
        {
            binarytree* curr = s.top().first;
            bool is_expanded = s.top().second;
            s.pop();
            if (is_expanded)
                cout << curr->data;
            else
            {
                if (curr->right)
                    s.push({ curr->right,0 });
                s.push({ curr,1 });
                if (curr->left)
                    s.push({ curr->left,0 });
            }
        }
    }
    void print_preorder_stack()
    {
        stack<binarytree*>s;
        s.push(this);
        while (!s.empty())
        {
            binarytree* curr = s.top();
            s.pop();
            cout << curr->data;
            if (curr->right)
                s.push(curr->right);
            if (curr->left)
                s.push(curr->left);
        }
    }
    int max()
    {
        int l = INT_MIN, r = INT_MIN;
        if (left)
            l = left->max();
        if (right)
            r = right->max();
        return std::max(std::max(l, r), data);


    }
    void print_postorder_stack()
    {
        stack<pair<binarytree*, bool>>s;
        s.push({ this,0 });
        while (!s.empty())
        {
            binarytree* curr = s.top().first;
            bool is_expanded = s.top().second;
            s.pop();
            if (is_expanded)
                cout << curr->data;
            else
            {
                s.push({ curr,1 });
                if (curr->right)
                    s.push({ curr->right,0 });

                if (curr->left)
                    s.push({ curr->left,0 });
            }
        }
    }
    int get_height()
    {
        int l = 0, r = 0;
        if (left)
            l = left->get_height() + 1;
        if (right)
            r = right->get_height() + 1;
        return std::max(l, r);
    }
    int count_nodes()
    {
        int l = 0, r = 0;
        if (left)
            l = left->count_nodes();
        if (right)
            r = right->count_nodes();
        return 1 + l + r;
    }
    int count_leaf()
    {
        int l = 0, r = 0;
        if (left)
            l = left->count_leaf();
        if (right)
            r = right->count_leaf();
        if (!left && !right)
            return 1;
        else
            return l + r;
    }
    bool is_exsist(int val)
    {

        if (data == val)
            return true;
        else
        {
            bool l = 0, r = 0;
            if (left)
                l = left->is_exsist(val);
            if (right)
                r = right->is_exsist(val);
            return l || r;
        }

    }
    bool is_perfect(int h)
    {
        if (left && !right || right && !left)
            return false;
        else
        if (!left && !right)
            return h == 0;
        else
        if (left && right)
            return left->is_perfect(h - 1) && right->is_perfect(h - 1);

    }
    void add(vector<int>values, string directions)
    {
        binarytree* curr = this;
        for (int i = 0; i <= values.size() - 1; i++)
            if (directions[i] == 'L')
            {
                if (!curr->left)
                    curr->left = new binarytree(values[i]);
                curr = curr->left;
            }
            else
            {
                if (!curr->right)
                    curr->right = new binarytree(values[i]);
                curr = curr->right;
            }


    }
    int diameter()
    {
        int res = 0;
        if (left)
            res += left->get_height() + 1;
        if (right)
            res += right->get_height() + 1;
        int dleft = 0, dright = 0;
        if (left)
            dleft = left->diameter();
        if (right)
            dright = right->diameter();
        return std::max(res, std::max(dleft, dright));

    }
    void BFS_khalaf()
    {
        queue<pair<binarytree*, int>>q;
        q.push({ this,0 });
        while (!q.empty())
        {
            binarytree* curr = q.front().first;
            int level = q.front().second;
            q.pop();
            cout << "level" << " " << level << " " << curr->data << endl;
            if (curr->left)
                q.push({ curr->left,level + 1 });
            if (curr->right)
                q.push({ curr->right,level + 1 });
        }
    }

    ~binarytree()
    {
        clear();
    }
    void BFS()
    {
        int level = 0;
        queue<binarytree*>q;

        q.push(this);
        while (!q.empty())
        {

            int size = q.size();
            while (size--)
            {


                binarytree* curr = q.front();
                q.pop();
                cout << curr->data << " ";
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);


            }
            cout << endl;
        }
    }
    bool is_complete()
    {
        if (left && right)
            return left->is_complete() && right->is_complete();
        if (!left && !right)
            return true;
        if (!left && right || left && !right)
            return false;

    }
    void print_sprial()
    {
        deque < binarytree*>d;
        d.push_back(this);
        int level = 0;
        while (!d.empty())
        {
            int size = d.size();
            while (size--)
            {
                if (level % 2 == 0)
                {
                    binarytree* curr = d.front();
                    d.pop_front();
                    cout << curr->data << " ";
                    if (curr->left)
                        d.push_back(curr->left);
                    if (curr->right)
                        d.push_back(curr->right);
                }
                else
                {
                    binarytree* curr = d.back();
                    d.pop_back();
                    cout << curr->data << " ";
                    if (curr->right)
                        d.push_front(curr->right);
                    if (curr->left)
                        d.push_front(curr->left);

                }
            }
            level++;
            cout << endl;
        }
    }


};
int main()
{
    binarytree tree(2);
    tree.add({ 4,8 }, "LL");
    tree.add({ 3,5 }, "RR");
    tree.add({ 3,6 }, "RL");
    tree.print_sprial();


}
