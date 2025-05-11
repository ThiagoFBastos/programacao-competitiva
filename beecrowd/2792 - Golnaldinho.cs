using System; 

class URI {	
	
	class Fenwick {
		private int[] ft;
		private int n;

		public Fenwick(int n) {
			this.n = n;
			ft = new int[n + 1];
		}

		public void upd(int k, int x) {
			for(; k <= n; k += k & -k) ft[k] += x;
		}

		public int query(int k) {
			int ans = 0;
			for(; k > 0; k -= k & -k) ans += ft[k];
			return ans;
		}
	}

	static bool isDigit(int c) {
		return c >= 48 && c <= 57;
	}

	static int nextInt() {
		int n = 0, ch = Console.Read();
		while(!isDigit(ch)) ch = Console.Read();
		while(isDigit(ch)) {
			n = 10 * n + ch - 48;
			ch = Console.Read();
		}
		return n;
	}

    static void Main(string[] args) {
		int n = nextInt();

		Fenwick ft = new Fenwick(n);
		
		for(int i = 1; i <= n; ++i) ft.upd(i, 1);

		for(int i = 0; i < n; ++i) {
			int a = nextInt();
			Console.Write(ft.query(a));
			Console.Write(i == n - 1 ? '\n' : ' ');
			ft.upd(a, -1);
		}
    }
}