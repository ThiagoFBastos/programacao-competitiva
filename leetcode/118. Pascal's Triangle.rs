impl Solution {
    pub fn generate(num_rows: i32) -> Vec<Vec<i32>> {
        let n = num_rows as usize;
        let mut pascal = Vec::new();

        pascal.push(vec![1]);

        for i in 1..n {
            let mut pascal_row = Vec::new();

            for j in 0..=i {
                let mut val = 0;

                if j < i {
                    val += pascal[i - 1][j];
                }
                
                if j > 0 {
                    val += pascal[i - 1][j - 1];
                }

                pascal_row.push(val);
            }

            pascal.push(pascal_row);
        }

        pascal
    }
}