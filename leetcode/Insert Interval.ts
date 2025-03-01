function compareIntervals(a: number[], b: number[]): boolean {
    return a[1] < b[0];
}

function overlaps(a: number[], b: number[]): boolean {
    return Math.max(a[0], b[0]) <= Math.min(a[1], b[1]);
}

function insert(intervals: number[][], newInterval: number[]): number[][] {
    const joinedIntervals: number[][] = [];
    let i = 0;
    
    for(; i < intervals.length && compareIntervals(intervals[i], newInterval); ++i)
        joinedIntervals.push(intervals[i]);

    joinedIntervals.push(newInterval);

    for(; i < intervals.length; ++i) {
        const lastInterval = joinedIntervals[joinedIntervals.length - 1];

        if(overlaps(intervals[i], lastInterval)) {
            let l = Math.min(intervals[i][0], lastInterval[0]);
            let r = Math.max(intervals[i][1], lastInterval[1]);
            joinedIntervals[joinedIntervals.length - 1] = [l, r];
        }
        else
            joinedIntervals.push(intervals[i]);
    }

    return joinedIntervals;
};