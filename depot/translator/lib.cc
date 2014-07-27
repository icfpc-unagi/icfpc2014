#include "translator/lib.h"
#include "util/colors.h"
#include "util/flags.h"

DECLARE_bool(silent);

Pair::Pair(const P& a, const P& d) {
  std::shared_ptr<P> car(new P(a));
  std::shared_ptr<P> cdr(new P(d));
  this->car = car;
  this->cdr = cdr;
}

int toi(const P& v) {
  return v.toInt();
}

P top(int n) {
  P res(n);
  return res;
}

P fst(const P& v) {
  return * v.toPair().car;
}

P snd(const P& v) {
  return * v.toPair().cdr;
}

int atom(const P& v) {
  switch (v.type) {
    case TYPE_INT:
      return 1;
    case TYPE_PAIR:
      return 0;
    default:
      LOG(FATAL) << "atom: undefined type";
  }
}
      
std::string P::to_string() const {
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

std::string Pair::to_string() const {
  std::string ret;
  ret += "(";
  ret += car->to_string();
  ret += ",";
  ret += cdr->to_string();
  ret += ")";
  return ret;
}

void debug(const P& v) {
  if (!FLAGS_silent) {
    if (FLAGS_print_for_test) {
      printf("trace lambdaman: %s\n", v.to_string().c_str());
    }
    std::cerr << "Lambda-Man: " << v.to_string() << (FLAGS_print_color ? "" : "  " CLEARLINEAFTER) << std::endl;
  }
  return;
}

void debug(int n) {
  debug(top(n));
  return;
}
