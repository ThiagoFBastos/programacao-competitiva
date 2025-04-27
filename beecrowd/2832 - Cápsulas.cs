using System; 
using System.Collections.Generic;

class URI {

    static void Main(string[] args) {
		string[] l = Console.ReadLine().Split(' ');

		int n = int.Parse(l[0]);
		int f = int.Parse(l[1]);
		int[] C = new int[n];

		l = Console.ReadLine().Split(' ');

		for(int i = 0; i < n; ++i)
			C[i] = int.Parse(l[i]);
		
		long lo = 1, hi = 1;

		while(true) {
			long cnt = 0;
			for(int i = 0; i < n; ++i) cnt += hi / C[i];
			if(cnt >= f) break;
			lo = hi;
			hi <<= 1;
		}		

		while(lo < hi) {
			long mid = (lo + hi) >> 1, cnt = 0;
			for(int i = 0; i < n; ++i) cnt += mid / C[i];
			if(cnt >= f) hi = mid;
			else lo = mid + 1;
		}

		Console.WriteLine(hi);
    }
}