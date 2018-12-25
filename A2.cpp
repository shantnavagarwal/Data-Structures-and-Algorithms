//Implements Sparse Matrix with Circular Multi Linked List
#include <cmath>
#include <iostream>

using namespace std;

struct node{
    int long r = 0;
    int long c = 0;
    bool flag = false;
    union{
        int long val = 0;
        struct node* next;
    };
    struct node* row = NULL; //traverse down btw rows
    struct node* col = NULL; //traverse right btw columns
};
struct node* sptr = (struct node *)malloc(sizeof(struct node));               //Super point longer
//Defining all functions that have to be carried of by this program.

void AddLink(int long i, int long j)
{
    bool a = true, b = true;
    if(i == j)
        b = false;
    struct node* traverse = sptr;
    struct node* trav;
    struct node* travs;
    while (a || b)
    {
        if(traverse->next->r > i && a)
        {
            auto *temp = (struct node *) malloc(sizeof(struct node));
            temp->next = traverse->next;
            temp->r = i;
            temp->c = i;
            temp->flag = true;
            temp->col = temp;
            temp->row = temp;
            traverse->next = temp;
            trav = temp;
            a = false;
        }
        else if(traverse->next->r > j && b)
        {
            auto *temp = (struct node *) malloc(sizeof(struct node));
            temp->next = traverse->next;
            temp->r = j;
            temp->c = j;
            temp->flag = true;
            temp->col = temp;
            temp->row = temp;
            traverse->next = temp;
            travs = temp;
            b = false;
        }
        else if(traverse->next->r == i && a)
        {
            trav = traverse->next;
            a = false;
        }
        else if(traverse->next->r == j && b)
        {
            travs = traverse->next;
            b = false;
        }
        traverse = traverse->next;
    }
    if(i == j)
        travs = trav;
    traverse = trav;
    while(true)
    {
        //cout << 74 << endl;
        if(traverse->col->c < j && !traverse->col->flag)
        {
            traverse = traverse->col;
            continue;
        }
        else if(traverse->col->c == j && !traverse->col->flag)
        {
            traverse->col->val++;
            break;
        }
        else if(traverse->col->flag || traverse->col->c > j)
        {
            auto *temp = (struct node *)malloc(sizeof(struct node));
            temp->col = traverse->col;
            traverse->col = temp;
            traverse->col->r = i;
            traverse->col->c = j;
            traverse->col->val = 1;
            traverse->col->flag = false;
            //Starting Vertical linking
            traverse = travs;
            while(true)
            {
                //cerr << 99 << endl;
                if(traverse->row->r > i)
                {
                    temp->row = traverse->row;
                    traverse->row = temp;
                    break;
                }
                else if(traverse->row->flag)
                {
                    temp->row = traverse->row;
                    traverse->row = temp;
                    break;
                }
                traverse = traverse->row;
            }
            break;
        }
    }
}
void DeleteLink(int long i, int long j)
{
    struct node *traverse = sptr->next;
    while(traverse->r != i)
    {
        traverse = traverse->next;
        if(traverse == sptr)
            return;
    }
    while(traverse->col->c != j)
    {
        traverse = traverse->col;
        if(traverse->col->flag)
            return;
    }
    traverse->col->val--;
    if (traverse->col->val == 0)
    {
        struct node* travs;
        struct node* temp = traverse->col->col;
        travs = traverse->col;
        traverse->col = temp;
        while(true)
        {
            if(travs->row->val == 0 && !travs->row->flag)
            {
                temp = travs->row->row;
                free(travs->row);
                travs->row = temp;
                break;
            }
            travs = travs->row;
        }
        return;
    }
}
int long RetrieveValue(int long i, int long j)
{
    struct node *traverse = sptr->next;
    while(traverse->r != i)
    {
        traverse = traverse->next;
        if(traverse == sptr)
            return 0;
    }
    while(traverse->col->c != j)
    {
        traverse = traverse->col;
        if(traverse->col->flag)
            return 0;
    }
    if (traverse->col->flag)
        return 0;
    else
        return (traverse->col->val);
}
int long RetrieveRowSum(int long i, int long k)
{
    struct node* traverse = sptr->next;
    while(traverse->r != i)
    {
        if(traverse == sptr)
            return 0;
        traverse = traverse->next;
    }
    int long sum = 0;
    traverse = traverse->row;
    while(traverse->r < k && !traverse->flag)
    {
        sum = sum + traverse->val;
        traverse = traverse->row;
    }
    return sum;
}
int long RetrieveColumnSum(int long j, int long k)
{
    struct node *traverse = sptr->next;
    while(traverse->c != j)
    {
        traverse = traverse->next;
        if (traverse == sptr)
            return 0;
    }
    int long sum = 0;
    traverse = traverse->col;
    while (traverse->c < k && !traverse->flag)
    {
        sum = sum + traverse->val;
        traverse = traverse->col;
    }
    return sum;
}
void MultiplyVector()
{
    long int n;
    cin >> n;
    if(n <= 0)
    {
        cout << 0 << endl;
        return;
    }
    long int arr[n];
    
    for(int long t = 0; t < n; t++)
    {
        cin >> arr[t];
    }
    int long sarr[n] = {0};
    struct node* traverse = sptr->next;
    struct node* travs = sptr->next;
    while(traverse->c < n && traverse != sptr)
    {
        if(traverse->row->flag != true )
        {
            travs = traverse->row;
            while(travs->r<n && travs->flag != true)
            {
                sarr[travs->c] = sarr[travs->c] + travs->val*arr[travs->r];
                travs = travs->row;
            }
        }
       traverse= traverse->next;
    }
    for(int r = 0; r < n - 1; r++)
    {
        cout << sarr[r] << " ";
    }
    cout << sarr[n-1] << endl;
}
int main() {
    int long q = 0, x = 0, i = 0, j = 0, k = 0, n = 0;        //x for query number, i,j are row and column.
    cin >> q;                       //storing number of queries
    sptr->r = 1000000000;
    sptr->c = 1000000000;
    sptr->flag = true;
    sptr->next = sptr;
    sptr->row = nullptr;
    sptr->col = nullptr;
    for (int long a = 0; a < q; a++)
    {
        cin >> x;
        if(x == 1)
        {
            cin >> i >> j;
            AddLink(i, j);
            //continue;
        }
        else if(x == 2)
        {
            cin >> i >> j;
            DeleteLink(i, j);
            //continue;
        }
        else if(x == 3)
        {
            cin >> i >> j;
            cout << RetrieveValue(i, j) << endl;
            //continue;
        }
        else if(x == 4)
        {
            cin >> i >> k;
            cout << RetrieveRowSum(i, k) << endl;
            //continue;
        }
        else if(x == 5)
        {
            cin >> j >> k;
            cout << RetrieveColumnSum(j, k) << endl;
            //continue;
        }
        else if(x == 6)
        {
            
            MultiplyVector();
            continue;
        }
    }
}
