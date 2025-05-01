using System; 
using System.Collections.Generic;

class URI {

	static int cmp(string a, string b) {
		return string.CompareOrdinal(a, b);
	}

	static int lcp(string a, string b) {
		int i = 0, n = Math.Min(a.Length, b.Length);
		while(i < n && a[i] == b[i]) ++i;
		return i;
	}

    static void Main(string[] args) {
		while(true) {
			string l = Console.ReadLine();

			if(l == null) break;

			int n = int.Parse(l), ans = 0;

			string[] s = new string[n];

			for(int i = 0; i < n; ++i)
				s[i] = Console.ReadLine();

			Array.Sort(s, cmp);

			for(int i = 1; i < n; ++i) ans += lcp(s[i - 1], s[i]);

			Console.WriteLine(ans);		
		}			
    }	
}