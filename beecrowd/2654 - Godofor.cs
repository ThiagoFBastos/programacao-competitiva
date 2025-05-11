using System; 

class URI {
	
	struct Hero {
		public string name;
		public int power;
		public int kills;
		public int deaths;
	}

	static int cmp(Hero a, Hero b) {
		if(a.power != b.power) return b.power - a.power;
		else if(a.kills != b.kills) return b.kills - a.kills;
		else if(a.deaths != b.deaths) return a.deaths - b.deaths;
		return string.CompareOrdinal(a.name, b.name);
	}

    static void Main(string[] args) {
		int n = int.Parse(Console.ReadLine());
		
		var heroes = new Hero[n];

		for(int i = 0; i < n; ++i) {
			var l = Console.ReadLine().Split(' ');
			heroes[i].name = l[0];
			heroes[i].power = int.Parse(l[1]);
			heroes[i].kills = int.Parse(l[2]);
			heroes[i].deaths = int.Parse(l[3]);
		}	
	
		Hero godofor = heroes[0];

		for(int i = 0; i < n; ++i) {
			if(cmp(heroes[i], godofor) < 0)
				godofor = heroes[i];
		}

		Console.WriteLine(godofor.name);
    }
}