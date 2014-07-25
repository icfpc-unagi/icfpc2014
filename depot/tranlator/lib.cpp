#include <memory>
//#include <cassert>
#include <iostream>
#include <string>

#include <glog/logging.h>

struct P;

struct Pair {
  std::shared_ptr<P> car, cdr;

  Pair(){
    car = NULL; cdr = NULL;
  }

  //Pair(int a, int d);
  //Pair(int a, P d);
  //Pair(P a, int d);
  Pair(P a, P d);

  std::string to_string();
};

enum var_type {TYPE_UNDEFINED, TYPE_INT, TYPE_PAIR};

struct P {
  enum var_type type;
  //union {
    int data_int;
    Pair data_Pair;
  //};

  P (const P& v) {
    type = v.type;
    switch (type) {
      case TYPE_UNDEFINED:
	break;
      case TYPE_INT:
	data_int = v.data_int;
	break;
      case TYPE_PAIR:
	data_Pair = v.data_Pair;
	break;
      default:
	LOG(FATAL) << "P: undefined type";
    }
  }

  P () {  // debug
    type = TYPE_UNDEFINED;
  }

  P (int n) {
    type = TYPE_INT;
    data_int = n;
  }

  P (Pair p) {
    type = TYPE_PAIR;
    data_Pair = p;
  }

  P (int a, int d) {
    *this = P(Pair(P(a),P(d)));
  }

  P (int a, P d) {
    *this = P(Pair(P(a),d));
  }

  P (P a, int d) {
    *this = P(Pair(a,P(d)));
  }

  P (P a, P d) {
    *this = P(Pair(a,d));
  }

  int toInt() {
    CHECK(type == TYPE_INT);
    return data_int;
  }

  Pair toPair() {
    CHECK(type == TYPE_PAIR);
    return data_Pair;
  }

  std::string to_string();
};

Pair::Pair(P a, P d) {
  std::shared_ptr<P> car(new P(a));
  std::shared_ptr<P> cdr(new P(d));
  this->car = car;
  this->cdr = cdr;
}

int firstInt(P v) {
  return v.toPair().car->toInt();
}

P firstP(P v) {
  return *v.toPair().car;
}

int secondInt(P v) {
  return v.toPair().cdr->toInt();
}

P secondP(P v) {
  return *v.toPair().cdr;
}

std::string P::to_string() {
  switch (type) {
    case TYPE_UNDEFINED:
      return "(undefined)";
    case TYPE_INT:
      return std::to_string(data_int);
    case TYPE_PAIR:
      return data_Pair.to_string();
    default:
      LOG(FATAL) << "P: undefined type";
  }
}

std::string Pair::to_string() {
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
