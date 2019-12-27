pub fn offset(width1: usize, width2: usize) -> usize {
    ((width2 - width1) as f32 / 2.).round() as usize
}
