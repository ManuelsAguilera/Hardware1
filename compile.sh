
rm build/Hardware
cmake -S . -B build;
cd build;
make;
cd ..;

./build/Hardware;