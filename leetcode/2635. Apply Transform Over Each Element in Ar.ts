function map(arr: number[], fn: (n: number, i: number) => number): number[] {
    let newArr = new Array<number>(arr.length);
    for(let i = 0; i < arr.length; ++i)
        newArr[i] = fn(arr[i], i);
    return newArr;
};