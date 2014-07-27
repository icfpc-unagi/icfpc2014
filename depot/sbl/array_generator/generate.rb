#!/usr/bin/env ruby
require 'erb'

$o

def label(l, r, op)
  if r - l == 1
    return sprintf("$get_array%d_end_%s", $n, op.downcase)
  else
    return sprintf("$get_array%d_%d_%d", $n, l, r)
  end
end

def rec(l, r, op)
  if r - l > 1
    $o.printf("%s:\n", label(l, r, op)) if op != ""
    m = (l + r) / 2
    $o.printf("  %s\n", op) if op != ""
    $o.printf("  LDC %d\n", m)
    $o.printf("  LD 0 1\n");
    $o.printf("  CGT\n")
    $o.printf("  TSEL %s %s\n", label(l, m, "CAR"), label(m, r, "CDR"))
    rec(l, m, "CAR")
    rec(m, r, "CDR")
  end
end

if __FILE__ == $0
  n = $n = ARGV[0].to_i
  throw "n > 0 && n = 2^k" if $n == 0 || ($n & ($n - 1)) != 0

  # Generate array#{n}.gcc
  $o = open("array#{n}.gcc", "w")
  $o.printf("$get_array%d:\n", $n)
  $o.printf("  LD 0 0\n");
  rec(0, $n, "")
  $o.printf("%s:\n", label(0, 1, "CAR"))
  $o.printf("  CAR\n")
  $o.printf("  RTN\n")
  $o.printf("%s:\n", label(0, 1, "CDR"))
  $o.printf("  CDR\n")
  $o.printf("  RTN\n")

  # Generate array#{n}.cpp
  erb = ERB.new(open(File.join(File.dirname($0), 'template.cpp')).read)
  open("array#{$n}.cpp", "w").puts(erb.result(binding))

  # Generate array#{n}.h
  erb = ERB.new(open(File.join(File.dirname($0), 'template.h')).read)
  open("array#{$n}.h", "w").puts(erb.result(binding))
end
