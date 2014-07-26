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
void debug(P)  // returns undefined value
void debug(int)
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
  Pair(const P& a, const P& d);

  std::string to_string() const;
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

  int toInt() const {
    CHECK(type == TYPE_INT);
    return data_int;
  }

  Pair toPair() const {
    CHECK(type == TYPE_PAIR);
    return data_Pair;
  }

  std::string to_string() const;
};

int toi(const P& v);
P top(int n);
P fst(const P& v);
P snd(const P& v);
int atom(const P& v);
void debug(const P& v);
void debug(int n);

P init(P, P);
P step(P, P);
