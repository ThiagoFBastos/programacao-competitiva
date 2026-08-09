interface Array<T> {
    groupBy(fn: (item: T) => string): Record<string, T[]>
}


Array.prototype.groupBy = function(fn) {
    let obj = {};
    for(const item of this) {
        const id = fn(item);
        if(obj[id] == undefined)
            obj[id] = [];
        obj[id].push(item);
    }
    return obj;
}

/**
 * [1,2,3].groupBy(String) // {"1":[1],"2":[2],"3":[3]}
 */