#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <tuple>
#include <cassert>

constexpr int N = 5e2 + 10;
constexpr int INF = 1e9;

int tempo[N][N];

namespace SCC {

    std::vector<int> sccID, tIn, low;
    int numberSCC, tempo;
    std::stack<int> st;

    void dfs(std::vector<std::vector<int>>& grafo, int v) {
        tIn[v] = low[v] = tempo++;

        st.push(v);
        
        for(int u : grafo[v]) {
            if(tIn[u] == -1) {
                dfs(grafo, u);
                low[v] = std::min(low[v], low[u]);
            } else if(sccID[u] == -1)
                low[v] = std::min(low[v], tIn[u]);
        }

        if(low[v] == tIn[v]) {
            int u;
            do
            {
                u = st.top();
                st.pop();
                sccID[u] = numberSCC;
            } while (u != v);
            numberSCC++;
        }
    }

    std::vector<int> computeSCCs(std::vector<std::vector<int>> grafo) {
        int n = grafo.size();

        sccID.assign(n, -1);
        tIn.assign(n, -1);
        low.assign(n, -1);
        numberSCC = tempo = 0;

        for(int v = 0; v < n; ++v) {
            if(tIn[v] != -1)
                continue;
            dfs(grafo, v);
        }

        return sccID;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, e;

    while(std::cin >> n >> e) {
        if(n == 0 && e == 0)
            break;

        std::vector<std::vector<int>> grafo(n);
        std::vector<std::tuple<int, int, int>> lista(e);

        for(auto& [x, y, h] : lista) {
            std::cin >> x >> y >> h;
            --x, --y;
           grafo[x].push_back(y);
        }

        auto sccID = SCC::computeSCCs(grafo);

        int m = *max_element(sccID.begin(), sccID.end()) + 1;

        for(int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j)
            tempo[i][j] = i == j ? 0 : INF;

        for(auto [x, y, h] : lista) {
            x = sccID[x];
            y = sccID[y];
            tempo[x][y] = std::min(tempo[x][y], h);
        }

        for(int k = 0; k < m; ++k)
        for(int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j)
            tempo[i][j] = std::min(tempo[i][j], tempo[i][k] + tempo[k][j]);
            
        int q;

        std::cin >> q;

        for(int i = 0; i < q; ++i) {
            int x, y;

            std::cin >> x >> y;

            x = sccID[x - 1];
            y = sccID[y - 1];

            if(tempo[x][y] != INF)
                std::cout << tempo[x][y] << '\n';
            else
                std::cout << "Nao e possivel entregar a carta\n";
        }

        std::cout << "\n";
    }

    return 0;
}