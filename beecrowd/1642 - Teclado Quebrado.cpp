#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while(true) {
        int m;
        string text;
        unordered_map<char, int> frequency;

        cin >> m;

        if(cin.eof() || !m)
            break;

        while(cin.peek() == '\r' || cin.peek() == '\n')
            cin.ignore();

        getline(cin, text);

        while(text.back() == '\r' || text.back() == '\n')
            text.pop_back();

        int lo {}, max_len {};

        for(int i = 0; i < (int)text.size(); ++i) {
            ++frequency[text[i]];

            while(lo < i && (int)frequency.size() > m) {
                char ch = text[lo++];

                if(--frequency[ch] == 0)
                    frequency.erase(ch);
            }

            max_len = max(max_len, i - lo + 1);
        }

        cout << max_len << '\n';
    }

    return 0;
}