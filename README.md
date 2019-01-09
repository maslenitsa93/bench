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

# Testing

## 2R : 1W

```
$ ./bench
--- MR_SW REMOVE/LOOKUP SIMPLE: ---
Remover (mutex): 1.038245
Searcher (mutex): 1.028261
Searcher (mutex): 1.038889

$ ./bench --shared
--- MR_SW REMOVE/LOOKUP SHARED: ---
Remover (shared mutex): 0.724579
Searcher (shared mutex): 0.725710
Searcher (shared mutex): 0.725963
```

## 2R : 2W

Rewrite it to use mw, build, and run. Result:

```
$ ./bench
--- MR_MW REMOVE/LOOKUP SIMPLE: ---
Remover (mutex): 1.241538
Searcher (mutex): 1.242640
Remover (mutex): 1.242892
Searcher (mutex): 1.235417

$ ./bench --shared
--- MR_MW REMOVE/LOOKUP SHARED: ---
Remover (shared mutex): 1.385841
Remover (shared mutex): 1.386603
Searcher (shared mutex): 1.387726
Searcher (shared mutex): 1.386424
```

### Conclusion

Shared_mutex is useful when readers count is more than writers, and vice-versa. But it is useless if readers count and writers count are equal.
