#!/usr/bin/env ruby
require 'erb'
require 'fileutils'

$n  # n = 2^k
$k  # k = log_2 n
$o  # output

################################################################################
# get_array
################################################################################
def ga_label(l, r, op)
  if r - l == 1
    return sprintf("$get_array%d$_end_%s", $n, op.downcase)
  else
    return sprintf("$get_array%d$_%d_%d", $n, l, r)
  end
end

def ga_rec(l, r, op)
  if r - l > 1
    $o.printf("%s:\n", ga_label(l, r, op)) if op != ""
    m = (l + r) / 2
    $o.printf("  %s\n", op) if op != ""
    $o.printf("  LDC %d\n", m)
    $o.printf("  LD 0 1\n");
    $o.printf("  CGT\n")
    $o.printf("  TSEL %s %s\n", ga_label(l, m, "CAR"), ga_label(m, r, "CDR"))
    ga_rec(l, m, "CAR")
    ga_rec(m, r, "CDR")
  end
end

def ga()
  $o.printf("$get_array%d:\n", $n)
  $o.printf("  LD 0 0\n");
  ga_rec(0, $n, "")
  $o.printf("%s:\n", ga_label(0, 1, "CAR"))
  $o.printf("  CAR\n")
  $o.printf("  RTN\n")
  $o.printf("%s:\n", ga_label(0, 1, "CDR"))
  $o.printf("  CDR\n")
  $o.printf("  RTN\n")
end

################################################################################
# set_array
################################################################################
def sa_label(l, r)
  return sprintf("$set_array%d$_%d_%d", $n, l, r)
end

def sa_rec2(l, r, i, d)
  if r - l == 1 && l == i
    $o.printf("  LD 1 2\n")
  elsif l <= i && i < r
    m = (l + r) / 2
    sa_rec2(l, m, i, d + 1)
    sa_rec2(m, r, i, d + 1)
    $o.printf("  CONS\n")
  else
    $o.printf("  LD 0 %d\n", d - 1)
  end
end

def sa_rec(l, r, d, op)
  $o.printf("%s:\n", sa_label(l, r))
  if op == 0
    $o.printf("  ST 1 0\n")
    $o.printf("  LD 1 0\n")
    $o.printf("  CDR\n")
    $o.printf("  ST 0 %d\n", d - 1)
    if r - l > 1
      $o.printf("  LD 1 0\n")
      $o.printf("  CAR\n")
    end
  elsif op == 1
    $o.printf("  ST 1 0\n")
    $o.printf("  LD 1 0\n")
    $o.printf("  CAR\n")
    $o.printf("  ST 0 %d\n", d - 1)
    if r - l > 1
      $o.printf("  LD 1 0\n")
      $o.printf("  CDR\n")
    end
  else
    $o.printf("  LD 1 0\n")
  end

  if r - l == 1
    sa_rec2(0, $n, l, 0)
    $o.printf("  RTN\n")
  else
    m = (l + r) / 2

    $o.printf("  LDC %d\n", m)
    $o.printf("  LD 1 1\n")
    $o.printf("  CGT\n")
    $o.printf("  TSEL %s %s\n", sa_label(l, m), sa_label(m, r))
    sa_rec(l, m, d + 1, 0)
    sa_rec(m, r, d + 1, 1)
  end
end

def sa()
  $o.printf("$set_array%d:\n", $n)
  $k.times do
    $o.printf("  LDC 0\n")
  end
  $o.printf("  LDF %s\n", sa_label(0, $n))
  $o.printf("  AP %d\n", $k)
  $o.printf("  RTN\n")

  sa_rec(0, $n, 0, 2);
end

################################################################################
# set_array2d
################################################################################
def sa2d_label(l, r)
  return sprintf("$set_array2d%d$_%d_%d", $n, l, r)
end

def sa2d_rec2(l, r, i, d)
  if r - l == 1 && l == i
    $o.printf("  LD 1 0\n")
  elsif l <= i && i < r
    m = (l + r) / 2
    sa2d_rec2(l, m, i, d + 1)
    sa2d_rec2(m, r, i, d + 1)
    $o.printf("  CONS\n")
  else
    $o.printf("  LD 0 %d\n", d - 1)
  end
end

def sa2d_rec(l, r, d, op)
  $o.printf("%s:\n", sa2d_label(l, r))
  if op == 0
    $o.printf("  ST 1 0\n")
    $o.printf("  LD 1 0\n")
    $o.printf("  CDR\n")
    $o.printf("  ST 0 %d\n", d - 1)
    $o.printf("  LD 1 0\n")
    $o.printf("  CAR\n")
  elsif op == 1
    $o.printf("  ST 1 0\n")
    $o.printf("  LD 1 0\n")
    $o.printf("  CAR\n")
    $o.printf("  ST 0 %d\n", d - 1)
    $o.printf("  LD 1 0\n")
    $o.printf("  CDR\n")
  else
    $o.printf("  LD 1 0\n")
  end

  if r - l == 1
    $o.printf("  LD 1 2\n")
    $o.printf("  LD 1 3\n")
    $o.printf("  LDF $set_array%d\n", $n)
    $o.printf("  AP 3\n");
    $o.printf("  ST 1 0\n")
    sa2d_rec2(0, $n, l, 0)
    $o.printf("  RTN\n")
  else
    m = (l + r) / 2
    $o.printf("  LDC %d\n", m)
    $o.printf("  LD 1 1\n")
    $o.printf("  CGT\n")
    $o.printf("  TSEL %s %s\n", sa2d_label(l, m), sa2d_label(m, r))
    sa2d_rec(l, m, d + 1, 0)
    sa2d_rec(m, r, d + 1, 1)
  end
end

def sa2d()
  $o.printf("$set_array2d%d:\n", $n)
  $k.times do
    $o.printf("  LDC 0\n")
  end
  $o.printf("  LDF %s\n", sa2d_label(0, $n))
  $o.printf("  AP %d\n", $k)
  $o.printf("  RTN\n")

  sa2d_rec(0, $n, 0, 2);
end


################################################################################
# Entry point
################################################################################

if __FILE__ == $0
  n = $n = ARGV[0].to_i
  throw "n > 0 && n = 2^k" if $n == 0 || ($n & ($n - 1)) != 0
  $k = (Math.log($n) / Math.log(2)).to_i
  p [$n, $k]

  # Generate array#{n}.gcc
  $o = open("array#{n}.gcc", "w")
  ga()
  sa()
  sa2d()

  # Generate array#{n}.cpp
  erb = ERB.new(open(File.join(File.dirname($0), 'template.cpp')).read)
  open("array#{$n}.cpp", "w").puts(erb.result(binding))

  # Generate array#{n}.h
  erb = ERB.new(open(File.join(File.dirname($0), 'template.h')).read)
  open("array#{$n}.h", "w").puts(erb.result(binding))

  # Generate array#{n}_translator.cpp
  erb = ERB.new(open(File.join(File.dirname($0), 'template_translator.cpp')).read)
  open("array#{$n}_translator.cpp", "w").puts(erb.result(binding))

  # Generate array#{n}_translator.cpp
  FileUtils.mkdir_p('test')
  erb = ERB.new(open(File.join(File.dirname($0), 'template_test.cpp')).read)
  open("test/array#{$n}_test.cpp", "w").puts(erb.result(binding))
end
