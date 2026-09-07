#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class K, class V>
using ht = gp_hash_table
<K, V, std :: hash<K>, std :: equal_to<K>,
direct_mask_range_hashing<>,
linear_probe_fn<>,
hash_standard_resize_policy<
hash_exponential_size_policy<>,
hash_load_check_resize_trigger
<>, true>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
long long uniform(long long l, long long r) {
	uniform_int_distribution<long long> uid(l, r);
	return uid(rng);
}

template<class T, int k>
struct MersenneHash {
	static long long P;
	static constexpr long long mod = (1ll << k) - 1;
	vector<long long> p, h;

	MersenneHash() = default;

	MersenneHash(const T& s) : p(s.size() + 2), h(s.size() + 1) {
		const int n = static_cast<int>(s.size());

		p[0] = 1, h[0] = 0;

		for(int i = 1; i <= n; ++i) {
			p[i] = mulmod(p[i - 1], P);
			h[i] = addmod(h[i - 1], mulmod(p[i], s[i - 1]));
		}

		p.back() = mulmod(p[n], P);
	}

	inline long long addmod(long long a, long long b) const {
		a += b;
		return a >= mod ? a - mod : a;
	}

	inline long long mulmodSQRT(long long a, long long b) const {
		return addmod((a*b) & mod, (a*b) >> k);
	}
	
	inline long long mulmod(long long a, long long b) const {
		int m1 = (k + 1) >> 1, m2 = k >> 1;
		long long a1 = a >> m1, a2 = a & ((1ll << m1) - 1), b1 = b >> m2, b2 = b & ((1ll << m2) - 1);
		long long s = mulmodSQRT(a1, b1), t = mulmodSQRT(a1, b2);
		long long u = mulmodSQRT(b1, a2), v = mulmodSQRT(a2, b2);
		t = addmod((t & ((1ll<<m2)-1)) << m1, t >> (k - m1));
		u = addmod((u & ((1ll<<m1)-1)) << m2, u >> (k - m2));
		return addmod(addmod(s, t), addmod(u, v));
	}

	long long operator()(int l, int r) const {
		int n = static_cast<int>(p.size()) - 1;
		return mulmod(addmod(h[r + 1] - h[l], mod), p[n - l - 1]);
	}
};

template<class T, int k>
long long MersenneHash<T, k> :: P = uniform(256, (1ll << k) - 2);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string str;

	cin >> str;

	MersenneHash<string, 61> mh(str);

	auto check = [&](int L) {
		const int n = static_cast<int>(str.size());

		ht<long long, null_type> us;

		us.resize(n - L + 1);

		for(int i = 0; i <= n - L; ++i)
			us.insert(mh(i, i + L - 1));

		for(int i = 0; i <= n - L + 1; ++i) {

			long long h = L >= 2 ? mh.addmod(mh.h[i + L - 1] - mh.h[i], mh.mod) : 0ll;

			for(char ch : {'0', '1'}) {
				auto new_hash = mh.mulmod(mh.addmod(h, mh.mulmod((int)ch, mh.p[i + L])), mh.p[n - i]);

				if(auto it = us.find(new_hash); it == us.end())
					return true;
			}
		}

		return false;
	};

	int low = 1, high = str.size();

	while(low < high) {
		int mid = (low + high) / 2;

		if(check(mid))
			high = mid;
		else
			low = mid + 1;
	}

	cout << high << '\n';

	return 0;
}