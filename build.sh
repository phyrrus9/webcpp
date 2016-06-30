#! /bin/bash
dst=$1
shift
src=""
while test ${#} -gt 0
do
  src="$src $1"
  shift
done
echo "g++ -fPIC $src ./src/core/base.cpp -shared -o obj/$dst -Wl,--no-whole-archive -I./inc"
g++ -fPIC $src ./src/core/base.cpp -shared -o obj/$dst -Wl,--no-whole-archive -I./inc
