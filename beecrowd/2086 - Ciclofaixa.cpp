#include <cstdio>
#include <climits>

using namespace std;

struct LinkedList {

	short value, cost;
	LinkedList* next;
	
	LinkedList(short V, short C) {

		value = V;
		cost = C;
		next = nullptr;
	}
};

struct List {

	LinkedList* first, *last;

	List() {

		first = nullptr;
	}

	~List() {

		while(first) {

			last = first->next;
			delete first;
			first = last;
		}
	}

	void insert(short value, short cost) {

		LinkedList* q = new LinkedList(value, cost);

		if(first) last->next = q;
		else first = q;

		last = q;
	}
};

List* ruas {nullptr};
short *alturas {nullptr};
bool *acesso {nullptr};

int minCusto(short a, short b, int n) {

	for(int i = 0; i < n; ++i) {

		alturas[i] = SHRT_MAX;
		acesso[i] = true;
	}

	alturas[a] = 0;
	acesso[a] = 0;

	for(LinkedList* q = ruas[a].first; q; q = q->next)
		alturas[q->value] = q->cost;

	while(true) {

		short w, custo = SHRT_MAX;

		for(int i = 0; i < n; ++i) {

			if(acesso[i] && custo > alturas[i])
				w = i, custo = alturas[i];
		}

		if(custo == SHRT_MAX || w == b)
			break;

		acesso[w] = false;

		for(LinkedList* q = ruas[w].first; q; q = q->next) {

			int z = q->value;

			if(acesso[z]) {

				if(custo < alturas[z] && q->cost < alturas[z]) {

					alturas[z] = custo;

					if(q->cost > alturas[z])
						alturas[z] = q->cost;
				}

			}
		}
	}

	return alturas[b];
}

int main() {

	int n, m, j = 0;

	while(true) {

		scanf("%d%d", &n, &m);

		if(!(n || m)) break;

		ruas = new List[n];
		alturas = new short[n];
		acesso = new bool[n];

		for(int k = 0; k < m; ++k) {

			short w, v, custo;

			scanf("%hd%hd%hd", &w, &v, &custo);

			--w, --v;

			ruas[w].insert(v, custo);
			ruas[v].insert(w, custo);
		}

		scanf("%d", &m);

		for(int k = 0; k < m; ++k) {

			short w, v;

			scanf("%hd%hd", &w, &v);
			printf("%d\n", minCusto(w - 1, v - 1, n));
		}

		delete[] ruas;
		ruas = nullptr;

		delete[] alturas;
		alturas = nullptr;

		delete[] acesso;
		acesso = nullptr;
	}

	return 0;
}