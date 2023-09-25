rm -r build
mkdir build
# cd build
# /snap/bin/cmake ../
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="/home/lpa1/Halide-install" -S . -B build
cmake --build ./build

# cd ..