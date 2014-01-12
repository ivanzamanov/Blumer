
set verbose off

b main.cpp:26
command 1
  p i
  continue
end

b DAWG.cpp:90
b DAWG.cpp:66

run data/smaller.txt

#quit
