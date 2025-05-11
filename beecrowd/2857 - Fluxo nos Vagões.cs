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
			for(; k <= n; k += k & -k)
				ft[k] += x;
		}

		private int query(int k) {
			int ans = 0;
			for(; k > 0; k -= k & -k)
				ans += ft[k];
			return ans;
		}

		public int query(int l, int r) {
			return query(r) - query(l - 1);
		}
	}
	
	static bool isDigit(int ch) {
		return ch >= 48 && ch <= 57;
	}

	static int nextInt() {
		int n = 0, ch;
		ch = Console.Read();
		while(!isDigit(ch)) ch = Console.Read();
		while(isDigit(ch)) {
			n = 10 * n + ch - '0';
			ch = Console.Read();
		}		
		return n;
	}

    static void Main(string[] args) { 

		int n = nextInt();
		int m = nextInt();

		Fenwick ft = new Fenwick(n);

		for(int i = 0; i < m; ++i) {
			int type = nextInt();

			if(type == 1) {
				int x = nextInt();
				int y = nextInt();
				ft.upd(x, y);
			} else {
				int a = nextInt();
				int b = nextInt();
				int c = nextInt();
				int d = nextInt();

				if(Math.Min(b, d) < Math.Max(a, c)) 
					Console.WriteLine(ft.query(a, b) + ft.query(c, d));
				else
					Console.WriteLine(ft.query(Math.Min(a, c), Math.Max(b, d)));
			}
		}
    }
}