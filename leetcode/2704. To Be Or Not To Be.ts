type ToBeOrNotToBe = {
    toBe: (val: any) => boolean;
    notToBe: (val: any) => boolean;
};

function expect(val: any): ToBeOrNotToBe {
    const other = val;
    return {
        toBe: (val: any): boolean => {
            if(other === val)
                return true;
            throw new Error("Not Equal");
            return false;
        },
        notToBe: (val: any): boolean => {
            if(other !== val)
                return true;
            throw new Error("Equal");
            return false;
        }
    };
};

/**
 * expect(5).toBe(5); // true
 * expect(5).notToBe(5); // throws "Equal"
 */