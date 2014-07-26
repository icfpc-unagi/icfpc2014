// vi:filetype=cpp:

// P read_tree(P tree, int n)
// P write_tree(P tree, int n, P value)
// P list_to_tree(P list)
#include "translator/lib.h"

// readTree :: Integer -> Tree a -> Maybe a
// readTree n tr = readTree1 n 1 tr
// readTree1 _ _ Nil = Nothing
// readTree1 n k (Node l r) =
//   if n < k
//      then readTree2 n k l
//      else readTree1 (n - k) (k * 2) r
// readTree2 _ _ Nil = Nothing
// readTree2 n 1 (Value x) = Just x
// readTree2 n 1 _ = error "hoge"
// readTree2 n k (Node l r) = let
//   k2 = k `div` 2
//   in if n < k2
//         then readTree2 n k2 l
//         else readTree2 (n - k2) k2 r
P read_tree2(int n, int k, P tr) {
  P res;
  int k2;
  if (k == 1) {
    res = tr;
  } else {
    k2 = k / 2;
    if (n < k2) {
      res = read_tree2(n, k2, fst(tr));
    } else {
      res = read_tree2(n-k2, k2, snd(tr));
    }
  }
  return res;
}
P read_tree1(int n, int k, P tr) {
  P res;
  // tr must be P(-,-).
  if (n < k) {
    res = read_tree2(n, k, fst(tr));
  } else {
    res = read_tree1(n-k, k*2, snd(tr));
  }
  return res;
}
P read_tree(P tr, int n) {
  return read_tree1(n, 1, tr);
}


// writeTree :: Integer -> a -> Tree a -> Tree a
// writeTree n v tr = writeTree1 n 1 v tr
// writeTree1 n k v Nil = writeTree1 n k v (Node Nil Nil)
// writeTree1 n k v (Node l r) =
//   if n < k
//      then Node (writeTree2 n k v l) r
//      else Node l (writeTree1 (n - k) (k * 2) v r)
// writeTree2 n k v Nil = writeTree2 n k v (Node Nil Nil)
// writeTree2 n 1 v _ = Value v
// writeTree2 n k v (Node l r) = let
//   k2 = k `div` 2
//   in if n < k2
//         then Node (writeTree2 n k2 v l) r
//         else Node l (writeTree2 (n - k2) k2 v r)
P write_tree2(int n, int k, P v, P tr) {
  P res;
  int k2;
  if (atom(tr)) {
    tr = P(top(0), top(0));
  } else { }

  if (k == 1){
    res = v;
  } else {
    k2 = k/2;
    if (n < k2) {
      res = P(write_tree2(n, k2, v, fst(tr)), snd(tr));
    } else {
      res = P(fst(tr), write_tree2(n-k2, k2, v, snd(tr)));
    }
  }
  return res;
}
P write_tree1(int n, int k, P v, P tr) {
  P res;
  if (atom(tr)) {
    tr = P(top(0), top(0));
  } else { }

  if (n < k) {
    res = P(write_tree2(n, k, v, fst(tr)), snd(tr));
  } else {
    res = P(fst(tr), write_tree1(n-k, k*2, v, snd(tr)));
  }
  return res;
}
P write_tree(P tr, int n, P v) {
  return write_tree1(n, 1, v, tr);
}

// listToTree :: [a] -> Tree a
// listToTree xs = listToTree1 xs 0
// listToTree1 [] _ = emptyTree
// listToTree1 (x:xs) n = writeTree n x (listToTree1 xs (n + 1))
P list_to_tree1(P ys, int n) {
  P res;
  if (atom(ys)) {  // []
    res = top(0);
  } else {
    res = write_tree(list_to_tree1(snd(ys), n+1), n, fst(ys));
  }
  return res;
}
P list_to_tree(P xs) {
  return list_to_tree1(xs, 0);
}
