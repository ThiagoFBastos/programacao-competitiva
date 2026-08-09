type JSONValue = null | boolean | number | string | JSONValue[] | { [key: string]: JSONValue };
type Obj = Record<string, JSONValue> | JSONValue[]

function isEmpty(obj: Obj): boolean {
    const stringify = JSON.stringify(obj);
    return stringify == '{}' || stringify == '[]';
};