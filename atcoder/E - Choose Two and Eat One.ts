import * as fs from 'fs';

const input: string = fs.readFileSync('/dev/stdin', 'utf8');
const lines: string[] = input.split('\n');

class Reader {
    static low: number = 0;

    static readLine(): string {
        return lines[this.low++];
    }

    static readInt(): number {
        return parseInt(Reader.readLine());
    }

    static readFloat(): number {
        return parseFloat(Reader.readLine());
    }

    static readIntArray(): number[] {
        return Reader.readLine().split(' ').map((x: string) => parseInt(x));
    }

    static readStringArray(): string[] {
        return Reader.readLine().split(' ');
    }
}

interface IUnionFind {
    findSet(u: number): number;
    join(u: number, v: number): void;
    same(u: number, v: number): boolean;
}

class UnionFind implements IUnionFind {
    private parent: number[];
    private rank: number[];

    constructor(n: number) {
        this.parent = new Array<number>(n);
        this.rank = new Array<number>(n);

        for(let i = 0; i < n; ++i) {
            this.parent[i] = i;
            this.rank[i] = 0;
        }
    }

    findSet(u: number): number {
        if(u == this.parent[u]) return u;
        let par: number = this.findSet(this.parent[u]);
        this.parent[u] = par;
        return par;
    }

    join(u: number, v: number): void {
        u = this.findSet(u);
        v = this.findSet(v);

        if(u != v) {
            if(this.rank[u] > this.rank[v]) {
                let tmp = u;
                u = v;
                v = tmp;
            }

            this.parent[u] = v;

            if(this.rank[u] == this.rank[v]) 
                ++this.rank[v];
        }
    }

    same(u: number, v: number): boolean {
        return this.findSet(u) == this.findSet(v);
    }
}

function binExp(a: number, p: number, m: number): number {
    let mod: bigint = BigInt(1), A: bigint = BigInt(a), M: bigint = BigInt(m);
    for(; p; p >>= 1) {
        if(p % 2) mod = mod * A % M;
        A = A * A % M;
    }
    return Number(mod);
}

function mst(nums: number[], m: number): number {
    type Edge = {u: number, v: number, w: number};
    let edges: Edge[] = [];
    let n: number = nums.length, weight: number = 0;
    let uf: UnionFind = new UnionFind(n);

    for(let i = 0; i < n; ++i) {
        for(let j = i + 1; j < n; ++j) {
            let score: number = (binExp(nums[i], nums[j], m) + binExp(nums[j], nums[i], m)) % m;
            edges.push({u: i, v: j, w: score});
        }
    }

    edges.sort((a: Edge, b: Edge) => b.w - a.w);

    for(const {u, v, w} of edges) {
        if(!uf.same(u, v)) {
            weight += w;
            uf.join(u, v);
        }
    }

    return weight;
}

const [n, m] = Reader.readIntArray();

const a = Reader.readIntArray();

let weight: number = mst(a, m);

console.log(weight);