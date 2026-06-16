// Definition for a binary tree node.
// #[derive(Debug, PartialEq, Eq)]
// pub struct TreeNode {
//   pub val: i32,
//   pub left: Option<Rc<RefCell<TreeNode>>>,
//   pub right: Option<Rc<RefCell<TreeNode>>>,
// }
// 
// impl TreeNode {
//   #[inline]
//   pub fn new(val: i32) -> Self {
//     TreeNode {
//       val,
//       left: None,
//       right: None
//     }
//   }
// }
use std::rc::Rc;
use std::cell::RefCell;
impl Solution {
    pub fn min_depth(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {

        if let Some(node) = root {
            let left = node.borrow().left.clone();
            let right = node.borrow().right.clone();

            if left.is_none() && right.is_none() {
                return 1;
            }

            let mut depth = i32::MAX;
            
            if left.is_some() {
                depth = 1 + Self::min_depth(left);
            }

            if right.is_some() {
                depth = std::cmp::min(depth, Self::min_depth(right) + 1);
            }

            return depth;
        }

        0
    }
}