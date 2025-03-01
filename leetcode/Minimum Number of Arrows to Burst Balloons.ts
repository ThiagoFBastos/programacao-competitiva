function findMinArrowShots(points: number[][]): number {
    let shots: number = 0;
    let lastX: number = Number.MIN_SAFE_INTEGER;

    points.sort((a, b) => a[1] - b[1]);

    for(const [l, r] of points) {
        if(lastX < l) {
            ++shots;
            lastX = r;
        }
    }

    return shots;
};