//use rand::prelude::*;

// Merge vector as in merge sort algorithm
fn merge(a: Vec<i64>, b: Vec<i64>) -> Vec<i64> {
    if a.len() == 0 {
        return b;
    }
    if b.len() == 0 {
        return a;
    }

    return if a[0] <= b[0] {
        let mut v = vec![a[0]];
        v.extend(merge(a[1..].to_vec(), b));
        v
    } else {
        let mut v = vec![b[0]];
        v.extend(merge(a, b[1..].to_vec()));
        v
    }
}

// Sort a vector using merge sort algorithm
fn sort(v: Vec<i64>) -> Vec<i64> {
    if v.len() <= 1 {
        return v
    }

    merge(
        sort(v[..v.len()/2].to_vec()),
        sort(v[v.len()/2..].to_vec()),
    )
}

fn is_sorted(v: &Vec<i64>) -> bool {
    for i in 1..v.len() {
        if v[i-1] > v[i] {
            return false;
        }
    }
    true
}

fn generate_random_numbers() -> Vec<i64> {
    let mut v: Vec<i64> = Vec::new();

    for i in 0..1000 {
        v.push(i); //rng.gen_range(0..10000);
    }

    v
}

fn main() {
    // Sort empty vector
    let v = vec![];
    let s = sort(v);
    assert!(is_sorted(&s));
    // Sort one element vector
    let v = vec![4];
    let s = sort(v);
    assert!(is_sorted(&s));
    // Sort odd number of elements
    let v = vec![3, 8, 2, 5, 6];
    let s = sort(v);
    assert!(is_sorted(&s));
    // Sort even number of elements
    let v = vec![3, 1, 5, 7, 0, 2];
    let s = sort(v);
    assert!(is_sorted(&s));


    // Generate vector of 1000 random elements
    let v = generate_random_numbers();


    println!("{:?}", sort(v));
}
