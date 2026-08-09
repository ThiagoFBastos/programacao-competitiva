type Fn = (...params: number[]) => number

function memoize(fn: Fn): Fn {
    let mp = new Map<string, number>();

    function index(args: number[]): string {
        if(args.length < 2) 
            return `${args[0]}`;
        return `${args[0]},${args[1]}`;
    }

    return function(...args) {
        let id = index(args);
        if(mp.has(id))
            return mp.get(id);
        let val = fn(...args);
        mp.set(id, val);
        return val;
    }
}


/** 
 * let callCount = 0;
 * const memoizedFn = memoize(function (a, b) {
 *	 callCount += 1;
 *   return a + b;
 * })
 * memoizedFn(2, 3) // 5
 * memoizedFn(2, 3) // 5
 * console.log(callCount) // 1 
 */