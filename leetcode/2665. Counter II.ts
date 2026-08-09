type Counter = {
    increment: () => number,
    decrement: () => number,
    reset: () => number,
}

function createCounter(init: number): Counter {
    const firstInit: number = init;
    return {
        increment: (): number => {return ++init;},
        decrement: (): number => {return --init;},
        reset: (): number => {
            init = firstInit;
            return init;
        }
    };
};

/**
 * const counter = createCounter(5)
 * counter.increment(); // 6
 * counter.reset(); // 5
 * counter.decrement(); // 4
 */