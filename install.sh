mkdir build

rm -rv build/*

cmake -B build .

cd build && make

cd ..

