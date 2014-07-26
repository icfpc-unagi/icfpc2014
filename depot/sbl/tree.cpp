#ifndef SBL_SBL_H_

#include "sbl/tree.h"

#include "translator/lib.h"
#include "sbl/list.h"

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

// // listToTree :: [a] -> Tree a
// // listToTree xs = listToTree1 xs 0
// // listToTree1 [] _ = emptyTree
// // listToTree1 (x:xs) n = writeTree n x (listToTree1 xs (n + 1))
// P list_to_tree1(P ys, int n) {
//   P res;
//   if (atom(ys)) {  // []
//     res = top(0);
//   } else {
//     res = write_tree(list_to_tree1(snd(ys), n+1), n, fst(ys));
//   }
//   return res;
// }
// P list_to_tree(P xs) {
//   return list_to_tree1(xs, 0);
// }

// l2t :: [a] -> Tree a
// l2t xs = l2t1 1 xs
// 
// l2t1 :: Integer -> [a] -> Tree a
// l2t1 _ [] = Nil
// l2t1 k xs = let
//   ys = genericTake k xs
//   zs = genericDrop k xs
//   in Node (head $ l2t2 k (map Value ys)) (l2t1 (k * 2) zs)
// 
// l2t2 :: Integer -> [Tree a] -> [Tree a]
// l2t2 1 xs = xs
// l2t2 k xs = l2t2 (k`div`2) (gp2 xs)
// 
// gp2 :: [Tree a] -> [Tree a]
// gp2 [] = []
// gp2 [x] = [Node x Nil]
// gp2 (x:y:xs) = Node x y : gp2 xs
P gp2(P ts) {
  P res;
  P x;
  P y;
  if (atom(ts)) {
    res = top(0);
  } else {
    x = fst(ts);
    ts = snd(ts);
    if (atom(ts)) {
      res = P( P(x,top(0)) ,  top(0) );
    } else {
      res = P( P(x,fst(ts)) ,  gp2(snd(ts)) );
    }
  }
  return res;
}
P l2t2(int k, P ts) {
  while (k > 1) {
    ts = gp2(ts);
    k = k / 2;
  }
  return ts;
}
P l2t1(int k, P xs) {
  P res;
  if (atom(xs)) {
    res = top(0);
  } else {
    xs = split_list(xs, k);
    res = P(fst(l2t2(k, fst(xs))), l2t1(k*2, snd(xs)));
  }
  return res;
}
P list_to_tree(P xs) {
  return l2t1(1, xs);
}

//// tree2d

// read tree[i][j]
P read_tree2d(P tree, int i, int j) {
  return read_tree(read_tree(tree, i), j);
}

// write tree[i][j]
P write_tree2d(P tree, int i, int j, P val) {
  return write_tree(tree, i, write_tree(read_tree(tree,i), j, val) );
}

// map list_to_tree
P list2d_to_tree2d_sub(P xss) {
  P res;
  if (atom(xss)) {
    res = top(0);
  } else {
    res = P(list_to_tree(fst(xss)), list2d_to_tree2d_sub(snd(xss)));
  }
  return res;
}
P list2d_to_tree2d(P xss) {
  return list_to_tree(list2d_to_tree2d_sub(xss));
}

#endif  // SBL_SBL_H_
