#include <bits/stdc++.h>

using namespace std;

constexpr int N = 100000 + 5;

template<int N>
struct SuffixArray {
	int tsa[N], c[N], tc[N], head[N], inv[N], sa[N], lcp[N], length;
	char str[N];

	void bucket(int n, int L) {
		memset(head, 0, sizeof head);

		for(int i = 0; i < n; ++i) ++head[c[i]];

		int maxi = max(300, n), k = 0;

		for(int i = 0; i < maxi; ++i) {
			swap(k, head[i]);
			k += head[i];
		}

		for(int i = 0; i < n; ++i) {
			int j = (sa[i] - L + n) % n;
			tsa[head[c[j]]++] = j;
		}

		memcpy(sa, tsa, n * sizeof(int));
	}

	void suffixarray() {
		int n = length + 1;
		for(int i = 0; i < n; ++i) {
			sa[i] = i;
			c[i] = str[i];
		}
		bucket(n, 0);
		for(int L = 1; L < n; L <<= 1) {
			bucket(n, L);
			for(int i = 0, cc = -1; i < n; ++i)
				tc[sa[i]] = !i || c[sa[i]] != c[sa[i - 1]] || c[(sa[i] + L) % n] != c[(sa[i - 1] + L) % n] ? ++cc : cc;
			memcpy(c, tc, n * sizeof(int));
		}
		for(int i = 0; i < n - 1; ++i) sa[i] = sa[i + 1];
	}

	void computeLCP() {
		int k = 0;
		for(int i = 0; i < length; ++i) inv[sa[i]] = i;
		for(int j = 0; j < length; ++j) {
			int i = inv[j];
			while(i > 0 && str[sa[i] + k] == str[sa[i - 1] + k]) ++k;
			lcp[i] = k;
			k = max(k - 1, 0);
		}
	}

	int lower_bound(const char* target) {
		int n = strlen(target), l = 0, r = length - 1;
		while(l < r) {
			int m = (l + r) / 2, i = sa[m], j = 0;
			while(i < length && j < n && str[i] == target[j]) ++i, ++j;
			if(str[i] >= target[j]) r = m;
			else l = m + 1;
		}
		return r;
	}

	SuffixArray() = default;

	SuffixArray(const char* s) {
		build(s);
	}

	void build(const char* s) {
		length = strlen(s);
		strcpy(str, s);
		suffixarray();
	}
};

template struct SuffixArray<N>;

long long count_substrings(const string& s) {
	const int n = static_cast<int>(s.size());
	auto sa = make_unique<SuffixArray<N>>(s.c_str());
	long long answer {};

	sa->computeLCP();
	
	for(int i = 0; i < n; ++i)
		answer += n - i - sa->lcp[i];

	return answer;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;

	cin >> t;

	while(t-- > 0) {
		string first, second;

		cin >> first >> second;

		if(count_substrings(first) == count_substrings(second))
			cout << "s\n";
		else
			cout << "n\n";
	}

	return 0;
}