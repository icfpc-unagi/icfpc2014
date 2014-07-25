#include <memory>
#include <cassert>
#include <iostream>
#include <string>

struct Var;

//std::string Var::to_string();

struct P {
  std::shared_ptr<Var> car, cdr;

  P(){
    car = NULL; cdr = NULL;
  }

  P(int a, int d);
  P(int a, P d);
  P(P a, int d);
  P(P a, P d);

  std::string to_string();
};

enum var_type {TYPE_INT, TYPE_P};

struct Var {
  enum var_type type;
  //union {
    int data_int;
    P data_P;
  //};

  Var (const Var& v) {
    type = v.type;
    data_int = v.data_int;
    data_P = v.data_P;
  }

  Var (int n) {
    type = TYPE_INT;
    data_int = n;
  }

  Var (P p) {
    type = TYPE_P;
    data_P = p;
  }

  std::string to_string();
};

P pair_var(Var a, Var d) {
  P ret;
  std::shared_ptr<Var> car(new Var(a));
  std::shared_ptr<Var> cdr(new Var(d));
  ret.car = car;
  ret.cdr = cdr;
  return ret;
}

P::P(int a, int d) {
  *this = pair_var(Var(a), Var(d));
}

P::P(int a, P d) {
  *this = pair_var(Var(a), Var(d));
}

P::P(P a, int d) {
  *this = pair_var(Var(a), Var(d));
}

P::P(P a, P d) {
  *this = pair_var(Var(a), Var(d));
}

//P P(int a, int d) {
//  return pair_var(Var(a), Var(d));
//}

int var2int (Var v) {
  assert(v.type == TYPE_INT);
  return v.data_int;
}

struct P var2P (Var v) {
  assert(v.type == TYPE_P);
  return v.data_P;
}

int firstInt(P p) {
  return var2int(*p.car);
}

P firstP(P p) {
  return var2P(*p.car);
}

int secondInt(P p) {
  return var2int(*p.cdr);
}

P secondP(P p) {
  return var2P(*p.cdr);
}



std::string Var::to_string() {
  if (type == TYPE_INT) {
    return std::to_string(data_int);
  } else if (type == TYPE_P) {
    return data_P.to_string();
  } else {
    assert(false);
  }
}

std::string P::to_string() {
  std::string ret;
  ret += "<";
  ret += car->to_string();
  ret += ",";
  ret += cdr->to_string();
  ret += ">";
  return ret;
}


P init(P, P);
P step(P, P);

int main() {
  P game, nazo;
  P state = init(game, nazo);
  while(true){
    std::cout << "state: " << state.to_string() << std::endl;
    P ret = step(state, game);
    state = firstP(ret);
    std::cout << "move: " << secondInt(ret) << std::endl;
  }
  return 0;
}
