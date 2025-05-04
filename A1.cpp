/*Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s telephone number. Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone number.*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 10;
/*Make use of any Two collision Handling technique*/
const int Chsize = 5;
void linearprobing(ll numbers[MAX], ll freq[MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        int key = numbers[i] % MAX;
        while (freq[key] != (ll)-1)
        {
            key = (key + 1) % MAX;
        }
        freq[key] = numbers[i];
    }
    cout << "Linear Probing Hash Table:\n";
    for (int i = 0; i < MAX; i++)
    {
        if (freq[i] == -1)
            cout << i << ": " << "Empty" << '\n';
        else
            cout << i << ": " << freq[i] << '\n';
    }
}
int main()
{
    ll numbers[MAX] = {23, 44, 12, 92, 5};
    ll freq[MAX];
    int n = 5;

    for (int i = 0; i < MAX; i++)
        freq[i] = -1;

    linearprobing(numbers, freq, n);

    return 0;
}
