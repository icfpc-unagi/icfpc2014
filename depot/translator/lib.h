/*
P P(int, int)
P P(int, P)
P P(P, int)
P P(P, P)
int toi(P)
P top(int)
P fst(P)
P snd(P)
int atom(P)
P debug(P)  // returns undefined value
P debug(int)
*/
#pragma once

#include <memory>
//#include <cassert>
#include <iostream>
#include <string>

#include <glog/logging.h>

struct P;

struct Pair {
  std::shared_ptr<P> car, cdr;

  Pair() {}

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

inline int toi(P v) {
  return v.toInt();
}

inline P top(int n) {
  P res(n);
  return res;
}

inline P fst(P v) {
  return * v.toPair().car;
}

inline P snd(P v) {
  return * v.toPair().cdr;
}

inline int atom(P v) {
  switch (v.type) {
    case TYPE_INT:
      return 1;
    case TYPE_PAIR:
      return 0;
    default:
      LOG(FATAL) << "atom: undefined type";
  }
}
      
inline std::string P::to_string() {
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

inline std::string Pair::to_string() {
  std::string ret;
  ret += "(";
  ret += car->to_string();
  ret += ",";
  ret += cdr->to_string();
  ret += ")";
  return ret;
}

inline P debug(P v) {
  P undef;
  std::cerr << v.to_string() << std::endl;
  return undef;
}

inline P debug(int n) {
  return debug(top(n));
}

P init(P, P);
P step(P, P);
