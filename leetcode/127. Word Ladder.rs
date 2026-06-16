use std::collections::{HashMap, VecDeque};

impl Solution {
    pub fn ladder_length(begin_word: String, end_word: String, word_list: Vec<String>) -> i32 {
        let mut index = HashMap::new();
        let mut dist = HashMap::new();

        for (idx, s) in word_list.iter().enumerate() {
            index.insert(s.clone(), idx);
        }

        let mut queue = VecDeque::new();

        dist.insert(begin_word.clone(), 1);
        queue.push_back(begin_word);

        while let Some(word) = queue.pop_front() {
            if word == end_word {
                break;
            }

            let d = *dist.get(&word).unwrap();
            let mut characters = word.chars().collect::<Vec<_>>();
            let n = characters.len();

            for idx in 0..n {
                let original = characters[idx];

                for ch in 'a'..='z' {
                    characters[idx] = ch;

                    let updated = characters.iter().map(|c| *c).collect::<String>();

                    if index.contains_key(&updated) && !dist.contains_key(&updated) {
                        dist.insert(updated.clone(), d + 1);
                        queue.push_back(updated);
                    }
                }

                characters[idx] = original;
            }
        }

        if let Some(distance) = dist.get(&end_word) {
            return *distance;
        }

        0
    }
}