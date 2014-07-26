#pragma once

P list_to_tree_(P list, int size) {
	P ret;
	P left;
	P right;
	if (size == 1) {
		ret = list;
	} else {
		left = list_to_tree_(list, size / 2);
		right = list_to_tree_(snd(left), size - size / 2);
		ret = P(P(fst(left), fst(right)), snd(right));
	}
	return ret;
}

P list_to_tree(P list) {
	int size;
	size = length_list(list);
	return P(fst(list_to_tree_(list, size)), size);
}

P read_tree_(P tree, int size, int i) {
	P ret;
	if (size == 1) {
		ret = tree;
	} else {
		if (i < size / 2) {
			ret = read_tree_(fst(tree), size / 2, i);
		} else {
			ret = read_tree_(snd(tree), size - size / 2, i - size / 2);
		}
	}
	return ret;
}

P read_tree(P tree, int i) {
	return read_tree_(fst(tree), toi(snd(tree)), i);
}

P write_tree_(P tree, int size, int i, P v) {
	P ret;
	if (size == 1) {
		ret = v;
	} else {
		if (i < size / 2) {
			ret = P(write_tree_(fst(tree), size / 2, i, v), snd(tree));
		} else {
			ret = P(fst(tree), write_tree_(snd(tree), size - size / 2, i - size / 2, v));
		}
	}
	return ret;
}

P write_tree(P tree, int i, P v) {
	return P(write_tree_(fst(tree), toi(snd(tree)), i, v), snd(tree));
}

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
