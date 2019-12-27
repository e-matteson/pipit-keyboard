use std::fmt::Debug;
use std::iter;
use std::string::ToString;

use bit_vec::BitVec;

use error::Error;

#[derive(Debug, Clone)]
pub struct Permutation {
    order: Vec<usize>,
    new_length: usize,
}

impl Permutation {
    /// Create a Permutation that can permute sequences from the order of the
    /// old one to the order of the new one. All elements in `old_template`
    /// must be present in `new_template`. However, there can be extra elements
    /// in `new_template`.
    pub fn from_to<T>(
        old_template: &[T],
        new_template: &[T],
    ) -> Result<Self, Error>
    where
        T: Clone + Eq + ToString + Debug,
    {
        let mut order = Vec::new();
        for old_item in old_template {
            let pos_in_new = new_template
                .iter()
                .position(|item| item == old_item)
                .ok_or(Error::PermuteWouldDrop)?;
            order.push(pos_in_new)
        }

        Ok(Self {
            order,
            new_length: new_template.len(),
        })
    }

    /// Permute the given sequence to the new order. If the new sequence
    /// template contained extra elements not in the old sequence template,
    /// those elements in the returned sequence will be set to their
    /// default value.
    pub fn permute(&self, old: &BitVec<u8>) -> Result<BitVec<u8>, Error> {
        if old.len() != self.order.len() {
            return Err(Error::PermuteLength);
        }

        let mut new: BitVec<_> =
            iter::repeat(false).take(self.new_length).collect();

        for (old_index, &new_index) in self.order.iter().enumerate() {
            new.set(new_index, old.get(old_index).expect("permutation failed"));
        }
        Ok(new)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn bits(b: &[u8]) -> BitVec<u8> {
        b.into_iter().map(|&bit| bit != 0).collect()
    }

    #[test]
    fn test_permute_reverse() {
        let p = Permutation::from_to(
            &[1, 2, 3, 4, 5, 6, 7],
            &[7, 6, 5, 4, 3, 2, 1],
        )
        .unwrap();
        assert_eq!(
            bits(&[0, 1, 0, 0, 1, 0, 1]),
            p.permute(&bits(&[1, 0, 1, 0, 0, 1, 0])).unwrap()
        )
    }

    #[test]
    fn test_permute_identity() {
        let p = Permutation::from_to(&[1, 2, 3], &[1, 2, 3]).unwrap();
        assert_eq!(bits(&[0, 1, 1]), p.permute(&bits(&[0, 1, 1])).unwrap())
    }

    #[test]
    fn test_permute_lengthen() {
        let p = Permutation::from_to(&[1, 2, 3], &[5, 4, 3, 2, 1]).unwrap();
        assert_eq!(
            bits(&[0, 0, 1, 1, 0]),
            p.permute(&bits(&[0, 1, 1])).unwrap()
        )
    }

    #[test]
    fn test_permute_err_shorten() {
        if Permutation::from_to(&[1, 2, 3, 4, 5], &[5, 4, 3]).is_ok() {
            panic!("should be permute error, but was ok");
        }
    }

    #[test]
    fn test_permute_err_long() {
        let p = Permutation::from_to(&[1, 2, 3], &[1, 2, 3]).unwrap();
        if p.permute(&bits(&[1, 1, 1, 1])).is_ok() {
            panic!("should be permute error, but was ok");
        }
    }

    #[test]
    fn test_permute_err_short() {
        let p = Permutation::from_to(&[1, 2, 3], &[1, 2, 3]).unwrap();
        if p.permute(&bits(&[1, 1])).is_ok() {
            panic!("should be permute error, but was ok");
        }
    }
}
