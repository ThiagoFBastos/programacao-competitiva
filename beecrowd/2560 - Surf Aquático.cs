using System; 

class URI {

	static bool isDigit(int ch) {
		return ch >= 48 && ch <= 57;
	}

	static int nextInt() {
		int n = 0, ch;

		ch = Console.Read();

		while(ch >= 0 && !isDigit(ch)) ch = Console.Read();

		if(ch < 0) return -1;

		while(isDigit(ch)) {
			n = 10 * n + ch - '0';
			ch = Console.Read();
		}

		return n;
	}

    static void Main(string[] args) {
		const int N = (int)(2e5 + 10);

		var delta = new int[2] {1, -1};
		var a = new int[N];
		var maxNext = new int[N];
		var maxPrev = new int[N];

		while(true) {
			int n = nextInt();

			if(n < 0) break;

			int b = nextInt();

			long soma = 0, ans = 0;

			for(int i = 0, lo = 0; i < n; ++i) {
				a[i] = nextInt();	
				soma += a[i];
				if(i - lo == b) soma -= a[lo++];
				if(i >= b - 1) ans += soma;
			}
	
			for(int i = 0; i < 2; ++i) {
				for(int j = n - 1; j >= 0; --j) {
					int r = Math.Min(n - 1, j + (b - j % b) % b);
					maxNext[j] = r == j ? delta[i]*a[j] : Math.Max(delta[i]*a[j], maxNext[j + 1]);
				}
				for(int j = 0; j < n; ++j) {
					int l = j - j % b;
					maxPrev[j] = l == j ? delta[i]*a[j] : Math.Max(delta[i]*a[j], maxPrev[j - 1]);
				}
				for(int j = 0; j <= n - b; ++j)
					ans -= Math.Abs(Math.Max(maxNext[j], maxPrev[j + b - 1]));
			}

			Console.WriteLine(ans);
		}
    }
}