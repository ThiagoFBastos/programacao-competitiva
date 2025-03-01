function canFinish(numCourses: number, prerequisites: number[][]): boolean {
    const adj: number[][] = [];
    const foundTime: number[] = new Array<number>(numCourses).fill(-1);
    const inPath: boolean[] = new Array<boolean>(numCourses).fill(false);
    let time: number = 0;
    
    for(let i = 0; i < numCourses; ++i)
        adj.push([]);

    prerequisites.forEach(arr => adj[arr[1]].push(arr[0]));

    function hasCycle(u: number) {
        foundTime[u] = time;
        inPath[u] = true;
        for(let v of adj[u]) {
            if(foundTime[v] == -1) {
                if(hasCycle(v))
                    return true;
            } else if(foundTime[u] == foundTime[v] && inPath[v])
                return true;
        }
        inPath[u] = false;
        return false;
    }

    for(let i = 0; i < numCourses; ++i) {
        if(foundTime[i] == -1 && hasCycle(i))
            return false;
        ++time;
    }

    return true;
};