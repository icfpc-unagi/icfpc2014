#!/usr/bin/env ruby
require 'erb'

def d(a)
  return a[$dir_num]
end

if __FILE__ == $0
  if File.extname(ARGV[0]) != '.ghcpp'
    $stderr.puts('Give me .ghcpp')
    abort
  end
  t = open(ARGV[0]).read
  t.gsub!(/^#.*$/, "")

  t.gsub!(/DIRECTIONS \{([^\}]*)\}/m) do |m|
    src = $1
    dst = ""
    [{:dir_name => 'up', :dir_num => 0},
     {:dir_name => 'down', :dir_num => 2},
     {:dir_name => 'right', :dir_num => 1},
     {:dir_name => 'left', :dir_num => 3}
    ].each do |e|
      e.each do |a, b|
        if b.instance_of? String
          eval("$#{a.to_s} = '#{b}'")
        else
          eval("$#{a.to_s} = #{b.to_s}")
        end
      end

      x = ERB.new(src).result(binding)
      e.each do |a, b|
        x.gsub!("<#{a.to_s}>", b.to_s)
      end
      dst += x
    end
    dst
  end

  t.gsub!('<my_x>', 'g')
  t.gsub!('<my_y>', 'h')
  t.gsub!('<enemy_x>', 'e')
  t.gsub!('<enemy_y>', 'f')

  open(ARGV[0].gsub(/\.ghcpp$/, '.ghc'), 'w') do |f|
    f.puts t
  end
end
