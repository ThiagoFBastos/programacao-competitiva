class ArrayWrapper {
    #data;

    constructor(nums: number[]) {
        this.#data = nums.slice();
    }
    
    valueOf(): number {
        return this.#data.reduce((a, b) => a + b, 0);
    }
    
    toString(): string {
        return `[${this.#data.toString()}]`;
    }
};

/**
 * const obj1 = new ArrayWrapper([1,2]);
 * const obj2 = new ArrayWrapper([3,4]);
 * obj1 + obj2; // 10
 * String(obj1); // "[1,2]"
 * String(obj2); // "[3,4]"
 */