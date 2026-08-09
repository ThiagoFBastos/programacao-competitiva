type JSONValue = null | boolean | number | string | JSONValue[] | { [key: string]: JSONValue };
type Obj = Record<string, JSONValue> | Array<JSONValue>;

function chunk(arr: Obj[], size: number): Obj[][] {
    let chunked = [];
    for(let i = 0; i < arr.length; ++i) {
        if(i % size == 0)
            chunked.push([]);
        chunked[i / size | 0].push(arr[i]);
    }
    return chunked;
};