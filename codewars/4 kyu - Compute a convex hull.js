function subtract(a, b) {
    return [a[0] - b[0], a[1] - b[1]];
}

function cross(a, b) {
    return a[0] * b[1] - a[1] * b[0];
}

function cw(a, b, c) {
    return cross(subtract(a, c), subtract(b, c)) < 0;
}

function ccw(a, b, c) {
    return cross(subtract(a, c), subtract(b, c)) > 0;
}

function hullMethod(points) {
    points.sort((a, b) => {
        if(a[0] != b[0]) return a[0] - b[0];
        return a[1] - b[1];
    });

    let upper = [points[0]], lower = [points[0]];

    for(let i = 1; i < points.length; ++i) {
        while(upper.length >= 2 && !cw(upper[upper.length - 2], upper[upper.length - 1], points[i])) upper.pop();
        while(lower.length >= 2 && !ccw(lower[lower.length - 2], lower[lower.length - 1], points[i])) lower.pop();
        upper.push(points[i]);
        lower.push(points[i]);
    }

    for(let i = lower.length - 2; i > 0; --i) upper.push(lower[i]);

    return upper;
}