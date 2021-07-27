mkdir -p build

rm -rv build/*

cmake -B build .

cd build && make

cd ..

