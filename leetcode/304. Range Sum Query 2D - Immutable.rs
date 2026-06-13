struct NumMatrix {
    sum: Vec<Vec<i32>>
}


/** 
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl NumMatrix {

    fn new(matrix: Vec<Vec<i32>>) -> Self {
        let n = matrix.len();
        let m = matrix[0].len();

        let mut sum = vec![vec![0; m + 1]; n + 1];

        for i in 1..=n {
            for j in 1..=m {
                sum[i][j] = sum[i - 1][j] + - sum[i - 1][j - 1] + sum[i][j - 1] + matrix[i - 1][j - 1];
            }
        }

        Self {
            sum
        }
    }
    
    fn sum_region(&self, row1: i32, col1: i32, row2: i32, col2: i32) -> i32 {
        let (x0, y0) = (row1 as usize + 1, col1 as usize + 1);
        let (x1, y1) = (row2 as usize + 1, col2 as usize + 1);

        self.sum[x1][y1] - self.sum[x1][y0 - 1] - self.sum[x0 - 1][y1] + self.sum[x0 - 1][y0 - 1]
    }
}

/**
 * Your NumMatrix object will be instantiated and called as such:
 * let obj = NumMatrix::new(matrix);
 * let ret_1: i32 = obj.sum_region(row1, col1, row2, col2);
 */