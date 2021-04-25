#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int T;
    string s;

    cin >> T;

    while (T--)
    {
        cin >> s;
        if (s[0] == s[s.length() - 1]) // E.g. aihfga or anjra
        {
            if (s.length() % 2 == 0)
            {
                cout << "Chikapu" << endl;
            }
            else
            {
                cout << "Bash" << endl;
            }
        }
        else
        {
            if (s.length() % 2 == 0)
            {
                cout << "Bash" << endl;
            }
            else
            {
                cout << "Chikapu" << endl;
            }
        }
    }

    return 0;
}