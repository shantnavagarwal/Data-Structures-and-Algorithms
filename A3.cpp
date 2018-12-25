// Market Display Publisher
// Constructs AVL Tree in O(n) time
#include <iostream>
using namespace std;
typedef long int num;
typedef struct Tree* tree;
typedef struct Sort sort;
struct Tree{
    num id = 0;
    num val = 0;
    tree left = nullptr;
    tree right = nullptr;
    num key = 0;
};
struct Sort{
    num id = 0;
    num val = 0;
};
num mdp = 0;
void Merge(sort a[], num l, num m, num r, sort arr[])
{
    num p = l;
    num q = m+1;
    num k = 0;
    for(num i = l; i <= r; i++)
    {
        if(q > r)
        {
            arr[k++] = a[p++];
            continue;
        }
        else if(p > m)
        {
            arr[k++] = a[q++];
            continue;
        }
        else if(a[p].id > a[q].id)
        {
            arr[k++] = a[q++];
            continue;
        }
        else
            arr[k++] = a[p++];
    }
    for(num i = 0; i < k; i++)
    {
        a[l++] = arr[i];
    }
}
void MergeSort(sort a[], num l, num r, sort temp[])
{
    if(l < r)
    {
        num m = (l + r)/2;
        MergeSort(a, l, m, temp);
        MergeSort(a, m+1, r, temp);
        Merge(a, l, m, r, temp);
    }
}
num max(num a, num b)
{
    return (a>b ? a : b);
}
num absolute(num a)
{
    return a > 0 ? a : -a;
}
tree onetree()
{
    tree down = (tree)malloc(sizeof(struct Tree));
    down->id = 0;
    down->val = 0;
    down->key = 0;
    down->left = nullptr;
    down->right = nullptr;
    return down;
}
tree CreateTree(sort a[], num l, num r)
{
    num m = (l+r)/2;
    if(l <= r)
    {
        tree node = (tree)malloc(sizeof(struct Tree));
        node->id = a[m].id;
        node->val = a[m].val;
        node->right = CreateTree(a, m + 1, r);
        node->left = CreateTree(a, l, m - 1);
        node->key = max(node->right->key, node->left->key) + 1;
        return node;
    }
    return onetree();
}
void llrot(tree z)
{
    tree y = z->left;
    struct Tree t = *z;
    *z = *y;
    t.left = y->right;
    t.key = max(t.left->key, t.right->key) + 1;
    *y = t;
    z->right = y;
    z->key = max(z->right->key, z->left->key) + 1;
}
void rrrot(tree z)
{
    tree y = z->right;
    struct Tree t = *z;
    *z = *y;
    t.right = y->left;
    t.key = max(t.left->key, t.right->key) + 1;
    *y = t;
    z->left = y;
    z->key = max(z->right->key, z->left->key) + 1;
}
void lrrot(tree z)
{
    tree y = z->left;
    tree x = y->right;
    struct Tree t = *y;
    *y = *x;
    t.right = y->left;
    t.key = max(t.left->key, t.right->key) + 1;
    *x = t;
    y->left = x;
    y->key = max(y->left->key, y->right->key) + 1;
    struct Tree tt = *z;
    *z = *y;
    tt.left = z->right;
    tt.key = max(tt.left->key, tt.right->key) + 1;
    *y = tt;
    z->right = y;
    z->key = max(z->right->key, z->left->key) + 1;
}
void rlrot(tree z)
{
    tree y = z->right;
    tree x = y->left;
    struct Tree t = *y;
    *y = *x;
    t.left = y->right;
    t.key = max(t.left->key, t.right->key) + 1;
    *x = t;
    y->right = x;
    y->key = max(y->left->key, y->right->key) + 1;
    struct Tree tt = *z;
    *z = *y;
    //tt.left = z->right;
    tt.right = z->left;
    tt.key = max(tt.left->key, tt.right->key) + 1;
    *y = tt;
    z->left = y;
    z->key = max(z->right->key, z->left->key) + 1;
}
tree insertTree(tree down, num id, num val)
{
    if(!down)
    {
        down = (tree) malloc(sizeof(struct Tree));
        down->id = id;
        down->val = val;
        down->key = 1;
        down->left = onetree();
        down->right = onetree();
        return down;
    }
    if (down->id == 0)
    {
        down = (tree) malloc(sizeof(struct Tree));
        down->id = id;
        down->val = val;
        down->key = 1;
        down->left = onetree();
        down->right = onetree();
        return down;
    }
    else if (down->id != 0)
    {
        if (id > down->id)
        {
            down->right = insertTree(down->right, id, val);
        }
        else if (id < down->id)
        {
            down->left = insertTree(down->left, id, val);
        }
        if(absolute(down->right->key - down->left->key) <= 1)
        {
            down->key = max(down->right->key, down->left->key) + 1;
            return down;
        }
        else if(down->left->key - down->right->key == 2)
        {
            if(down->left->left->key > down->left->right->key)
            {
                llrot(down);
                return down;
            } else{
                lrrot(down);
                return down;
            }
        }
        else if(down->right->key - down->left->key == 2)
        {
            if(down->right->right->key > down->right->left->key)
            {
                rrrot(down);
                return down;
            } else{
                rlrot(down);
                return down;
            }
        }
    }
    return down;
}
tree successor(tree down)
{
    while(down->left->id != 0)
    {
        down = down->left;
    }
    return down;
}
void rotate(tree down)
{
    if(down->id != 0)
    {
        if(down->left->key - down->right->key == 2)
        {
            if(down->left->left->key >= down->left->right->key)
            {
                llrot(down);
            } else{
                lrrot(down);
            }
        }
        else if(down->right->key - down->left->key == 2)
        {
            if(down->right->right->key >= down->right->left->key)
            {
                rrrot(down);
            } else{
                rlrot(down);
            }
        }
    }
}
tree removeTree(tree down, num id)
{
    if (down->id == 0)
    {
        return down;
    }
    else if(down->id == id)
    {
        if(!down->right->id && !down->left->id)
        {
            down->id = 0;
            down->val = 0;
            down->key = 0;
            free(down->right);
            free(down->left);
            down->right = nullptr;
            down->left = nullptr;
            return down;
        }
        else if(!down->left->id)
        {
            tree t = down->right;
            free(down);
            return t;
        }
        else if(!down->right->id)
        {
            tree t = down->left;
            free(down);
            return t;
        } else{
            tree temp = successor(down->right);
            down->id = temp->id;
            down->val = temp->val;
            down->right = removeTree(down->right, temp->id);
            down->key = max(down->left->key, down->right->key) + 1;
            return down;
        }
    }
    else if(down->id > id)
    {
        down->left = removeTree(down->left, id);
        rotate(down);
        down->key = max(down->left->key, down->right->key)+1;
        return down;
    }
    else if(down->id < id)
    {
        down->right = removeTree(down->right, id);
        rotate(down);
        down->key = max(down->left->key, down->right->key)+1;
        return down;
    }
    return down;
}
void updatePrice(tree down, num id, num val)
{
    if(down->id == 0)
        return;
    else if(down->id == id)
    {
        if(absolute(val - down->val) > mdp)
        {
            down->val = val;
            cout << down->id<< ' ' << down->val << endl;
        }
        return;
    }
    else if(down->id > id)
    {
        down = down->left;
        updatePrice(down, id, val);
        return;
    }
    else if (down->id < id)
    {
        down = down->right;
        updatePrice(down, id, val);
        return;
    }
}
void updateStock(tree down, num id, num x, num y)
{
    if(down->id == 0)
        return;
    else if(down->id == id)
    {
        down->val = (down->val*y)/x;
        cout << down->id << ' ' << down->val << endl;
    }
    else if(down->id > id)
    {
        down = down->left;
        updateStock(down, id, x, y);
        return;
    }
    else if (down->id < id)
    {
        down = down->right;
        updateStock(down, id, x, y);
        return;
    }
}
int main() {
    num n, N;
    cin >> n;
    sort a[n];
    sort temp[n];
    for(num i = 0; i < n; i++)
    {
        cin >> a[i].id;
        cin >> a[i].val;
    }
    MergeSort(a, 0, n-1, temp);
    tree super = nullptr;
    super = CreateTree(a, 0, n-1);
    cin >> N >> mdp;
    num oper;
    num inone, intwo, y;
    char colan;
    for(num i = 0; i < N; i++)
    {
        cin >> oper;
        if(oper == 1)
        {
            cin >> inone >> intwo;
            super = insertTree(super, inone, intwo);
            cout << inone << ' ' << intwo << endl;
        }
        else if(oper == 2)
        {
            cin >> inone;
            super = removeTree(super, inone);
            if(super->left == nullptr)
                super->left = onetree();
            if(super->right == nullptr)
                super->right = onetree();
        }
        else if(oper == 3)
        {
            cin >> inone >> intwo;
            updatePrice(super, inone, intwo);
        }
        else if(oper == 4)
        {
            cin >> inone >> intwo >> colan >> y;
            updateStock(super, inone, intwo, y);
        }
    }
}
