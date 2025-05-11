using System; 
using System.Collections.Generic;

class URI {
    static void Main(string[] args) {
		int n = int.Parse(Console.ReadLine());

		var st = new Stack<int>();
		var tmp = new Stack<int>();
		
		while(n-- > 0) {
			var l = Console.ReadLine().Split(' ');

			if(l[0] == "PUSH") {
				int val = int.Parse(l[1]);
				if((st.Count > 0 && st.Peek() > val) || st.Count == 0) {
					st.Push(val);
					tmp.Push(1);
				} else
					tmp.Push(0);
			} else if(l[0] == "POP") {	
				if(tmp.Count == 0) {
					Console.WriteLine("EMPTY");
					continue;
				}
				if(tmp.Pop() == 1) st.Pop();
			} else {
				if(tmp.Count == 0) {
					Console.WriteLine("EMPTY");
					continue;
				}
				Console.WriteLine(st.Peek());
			}
		}		
    }
}