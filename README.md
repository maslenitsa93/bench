# Dependencies installing

```
cd ~
git clone https://github.com/google/benchmark.git
cd benchmark
git clone https://github.com/google/googletest.git
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=RELEASE
make
sudo make install
```

# Installing

```
cd ~
git clone https://github.com/maslenitsa93/bench
cd bench
```

# Building and running

```
cmake CMakeLists.txt
make
./bench
```
