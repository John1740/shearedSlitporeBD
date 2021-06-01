mkdir build

rm -rv build/*

cmake -j 6 -B build .

cd build && make

cd ..

