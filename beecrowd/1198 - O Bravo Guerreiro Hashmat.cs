using System; 
using System.Collections.Generic;

class URI {

    static void Main(string[] args) {
		while(true) {
            string row = Console.ReadLine();

            if(row == null) break;

            string[] parts = row.Split(' ');

            long a = long.Parse(parts[0]);
            long b = long.Parse(parts[1]);

            Console.WriteLine(Math.Abs(a - b));
        }
    }
}