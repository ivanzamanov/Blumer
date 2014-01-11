
set verbose off

b hash.h:65
ignore 1 100
command 1
  print size
  print cap
#  continue
end

run data/words-prepped.txt

#quit
