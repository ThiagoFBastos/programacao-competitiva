using System; 
using System.Collections.Generic;

class URI {

    static void Main(string[] args) {
		while(true) {
            string row = Console.ReadLine();

            if(row == null) break;

            string[] parts = row.Split(' ');

            int v0 = int.Parse(parts[0]);
            int t = int.Parse(parts[1]);

            Console.WriteLine(2 * v0 * t);
        }
    }
}