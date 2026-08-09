type JSONValue = null | boolean | number | string | JSONValue[] | { [key: string]: JSONValue };
type ArrayType = { "id": number } & Record<string, JSONValue>;

function merge(obj1: ArrayType, obj2: ArrayType): ArrayType {
    let obj3: ArrayType = {id: -1};
    for(const key in obj1) obj3[key] = obj1[key];
    for(const key in obj2) obj3[key] = obj2[key];
    return obj3;
}

function join(arr1: ArrayType[], arr2: ArrayType[]): ArrayType[] {
    let arr3: ArrayType[] = [];
    let i = 0, j = 0;

    arr1.sort((a, b) => a.id - b.id);
    arr2.sort((a, b) => a.id - b.id);

    while(i < arr1.length && j < arr2.length) {
        if(arr1[i].id < arr2[j].id)
            arr3.push(arr1[i++]);
        else if(arr1[i].id > arr2[j].id)
            arr3.push(arr2[j++]);
        else
            arr3.push(merge(arr1[i++], arr2[j++]));
    }

    for(; i < arr1.length; ++i) arr3.push(arr1[i]);
    for(; j < arr2.length; ++j) arr3.push(arr2[j]);
    
    return arr3;
};