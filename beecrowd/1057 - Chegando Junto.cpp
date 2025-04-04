#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <utility>
#include <cassert>

#define INDICE(x, y, columns) ((x) * columns + (y))

constexpr int N = 100;

const std::pair<int, int> deltas[] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

int dist[N][N][N];

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int t;

    std::cin >> t;

    for(int c = 1; c <= t; ++c) {
        int n;

        std::cin >> n;

        std::vector<std::string> labirinto(n);
        std::vector<std::pair<int, int>> posicoes;
        std::queue<std::tuple<int, int, int, int, int, int>> queue;

        for(int k = 0; k < n; ++k) {
            std::cin >> labirinto[k];

            for(int j = 0; j < n; ++j) {
                if(labirinto[k][j] >= 'A' && labirinto[k][j] <= 'C')
                    posicoes.emplace_back(k, j);
            }
        }

        for(int i = 0; i < n * n; ++i)
            for(int j = 0; j < n * n; ++j)
                for(int k = 0; k < n * n; ++k)
                    dist[i][j][k] = -1;

        for(int i = 0; i < n * n; ++i) {
            for(int j = 0; j < n * n; ++j) {
                dist[i][i][j] = 0;
                dist[i][j][i] = 0;
                dist[j][i][i] = 0;
                dist[i][i][i] = 0;
            }
        }

        assert(posicoes.size() == 3);

        auto [x0, y0] = posicoes[0];
        auto [x1, y1] = posicoes[1];
        auto [x2, y2] = posicoes[2];

        dist[INDICE(x0, y0, n)][INDICE(x1, y1, n)][INDICE(x2, y2, n)] = 0;

        queue.emplace(x0, y0, x1, y1, x2, y2);

        auto posicaoValida = [&labirinto, n](int x, int y)->bool {
            return !(x < 0 || y < 0 || x >= n || y >= n || labirinto[x][y] == '#');
        };

        auto combinacaoValida = [&labirinto, n, &posicaoValida, &queue](int x0, int y0, int x1, int y1, int x2, int y2, int dx, int dy)->void {
             int distAtual = dist[INDICE(x0, y0, n)][INDICE(x1, y1, n)][INDICE(x2, y2, n)];

            x0 += dx, y0 += dy;
            x1 += dx, y1 += dy;
            x2 += dx, y2 += dy;

            if(!posicaoValida(x0, y0)) x0 -= dx, y0 -= dy;
            if(!posicaoValida(x1, y1)) x1 -= dx, y1 -= dy;
            if(!posicaoValida(x2, y2)) x2 -= dx, y2 -= dy;

            if(x0 == x1 && y0 == y1 || x0 == x2 && y0 == y2) x0 -= dx, y0 -= dy;
            if(x0 == x1 && y0 == y1 || x1 == x2 && y1 == y2) x1 -= dx, y1 -= dy;
            if(x2 == x1 && y2 == y1 || x0 == x2 && y0 == y2) x2 -= dx, y2 -= dy;
            
            int& distNova = dist[INDICE(x0, y0, n)][INDICE(x1, y1, n)][INDICE(x2, y2, n)];

            if(distNova != -1)
                return;

            distNova = 1 + distAtual;
            queue.emplace(x0, y0, x1, y1, x2, y2);
        };

        auto combinacaoDesbloqueada = [&labirinto, n](int x0, int y0, int x1, int y1, int x2, int y2)->bool {
            return labirinto[x0][y0] == 'X' && labirinto[x1][y1] == 'X' && labirinto[x2][y2] == 'X' && !(x0 == x1 && y0 == y1 || x0 == x2 && y0 == y2 && x1 == x2 && y1 == y2);
        };

        std::cout << "Case " << c << ": ";

        bool trapped = true;
        
        while(!queue.empty()) {
            auto [x0, y0, x1, y1, x2, y2] = queue.front();

            queue.pop();

             int distAtual = dist[INDICE(x0, y0, n)][INDICE(x1, y1, n)][INDICE(x2, y2, n)];

            if(combinacaoDesbloqueada(x0, y0, x1, y1, x2, y2)) {
                std::cout << distAtual << '\n';
                trapped = false;
                break;
            }

            for(auto [dx, dy] : deltas)
                combinacaoValida(x0, y0, x1, y1, x2, y2, dx, dy);
        }

        if(trapped)
            std::cout << "trapped\n";
    }

    return 0;
}