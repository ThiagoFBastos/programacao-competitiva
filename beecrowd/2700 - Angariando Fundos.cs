using System; 
using System.Collections.Generic;

class URI {

	struct P {
		public int B;
		public int F;
		public int D;
	}

	static int cmp(P a, P b) {
		if(a.B != b.B) return a.B - b.B;
		return a.F - b.F;
	}

	class BIT {
		private long[] bit;
		private int n;

		public BIT(int n) {
			this.n = n;
			bit = new long[n + 1];
		}

		public void upd(int k, long x) {
			if(k < 0) return;
			for(++k; k <= n; k += k & -k)
				bit[k] = Math.Max(bit[k], x);
		}

		public long query(int k) {
			long ans = 0;
			for(++k; k > 0; k -= k & -k)
				ans = Math.Max(ans, bit[k]);
			return ans;
		}
	}

    static void Main(string[] args) {
		int n = int.Parse(Console.ReadLine());

		P[] a = new P[n];
		int[] values = new int[n];
		long[] cost = new long[n];
		BIT bit = new BIT(n);

		for(int i = 0; i < n; ++i) {
			var l = Console.ReadLine().Split(' ');
			a[i].B = int.Parse(l[0]);
			a[i].F = int.Parse(l[1]);
			a[i].D = int.Parse(l[2]);
			values[i] = a[i].F;
		}

		Array.Sort(values);
		Array.Sort(a, cmp);

		for(int i = 0; i < n; ++i)
			a[i].F = Array.BinarySearch(values, a[i].F);

		for(int i = 0; i < n; ) {
			int k;
			for(k = i; k < n && a[k].B == a[i].B; ) {			
				long D = 0;
				int j;
				for(j = k; j < n && a[j].B == a[k].B && a[j].F == a[k].F; ++j) D += a[j].D;
				cost[k] = bit.query(a[k].F - 1) + D;
				k = j;
			}
			for(; i < k; ++i) bit.upd(a[i].F, cost[i]);
		}

		Console.WriteLine(bit.query(n - 1));
    }
}