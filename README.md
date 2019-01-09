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

# Building

```
cmake CMakeLists.txt
make
```

# Testing

## 1W : 2R

$ ./bench --writers=1 --readers=2 --lock-type=mutex
Searcher (mutex): 1.429424
Remover (mutex): 1.429919
Searcher (mutex): 1.429914
$ ./bench --writers=1 --readers=2 --lock-type=mutex
Remover (mutex): 1.083013
Searcher (mutex): 1.083389
Searcher (mutex): 1.076141
$ ./bench --writers=1 --readers=2 --lock-type=mutex
Searcher (mutex): 1.241346
Remover (mutex): 1.251958
Searcher (mutex): 1.249535

$ ./bench --writers=1 --readers=2 --lock-type=shared
Remover (shared mutex): 0.606690
Searcher (shared mutex): 0.615086
Searcher (shared mutex): 0.617768
$ ./bench --writers=1 --readers=2 --lock-type=shared
Remover (shared mutex): 0.873422
Searcher (shared mutex): 0.877647
Searcher (shared mutex): 0.878457
$ ./bench --writers=1 --readers=2 --lock-type=shared
Remover (shared mutex): 0.770776
Searcher (shared mutex): 0.771373
Searcher (shared mutex): 0.772281

$ ./bench --writers=1 --readers=2 --lock-type=spinlock
Remover (spinlock): 1.250998
Searcher (spinlock): 1.250999
Searcher (spinlock): 1.248031
$ ./bench --writers=1 --readers=2 --lock-type=spinlock
Remover (spinlock): 0.626659
Searcher (spinlock): 0.625596
Searcher (spinlock): 0.627504
$ ./bench --writers=1 --readers=2 --lock-type=spinlock
Searcher (spinlock): 0.858754
Remover (spinlock): 0.881929
Searcher (spinlock): 0.882429

## 2W : 2R

$ ./bench --writers=2 --readers=2 --lock-type=mutex
Searcher (mutex): 1.768295
Remover (mutex): 1.832583
Remover (mutex): 1.832627
Searcher (mutex): 1.827451
$ ./bench --writers=2 --readers=2 --lock-type=mutex
Remover (mutex): 1.080834
Searcher (mutex): 1.081330
Searcher (mutex): 1.081761
Remover (mutex): 1.082396
$ ./bench --writers=2 --readers=2 --lock-type=mutex
Remover (mutex): 1.656732
Remover (mutex): 1.657228
Searcher (mutex): 1.657770
Searcher (mutex): 1.657883

$ ./bench --writers=2 --readers=2 --lock-type=shared
Remover (shared mutex): 0.605845
Searcher (shared mutex): 0.607761
Remover (shared mutex): 0.625172
Searcher (shared mutex): 0.617621
$ ./bench --writers=2 --readers=2 --lock-type=shared
Remover (shared mutex): 0.749466
Remover (shared mutex): 0.766117
Searcher (shared mutex): 0.768512
Searcher (shared mutex): 0.768804
$ ./bench --writers=2 --readers=2 --lock-type=shared
Remover (shared mutex): 0.895521
Searcher (shared mutex): 0.909898
Remover (shared mutex): 0.914262
Searcher (shared mutex): 0.912446

$ ./bench --writers=2 --readers=2 --lock-type=spinlock
Searcher (spinlock): 1.873267
Remover (spinlock): 2.013843
Remover (spinlock): 2.014103
Searcher (spinlock): 2.014053
$ ./bench --writers=2 --readers=2 --lock-type=spinlock
Remover (spinlock): 0.986991
Searcher (spinlock): 0.987322
Remover (spinlock): 0.987516
Searcher (spinlock): 0.980255
$ ./bench --writers=2 --readers=2 --lock-type=spinlock
Searcher (spinlock): 1.637800
Remover (spinlock): 1.784516
Searcher (spinlock): 1.784682
Remover (spinlock): 1.784866

## 2W : 1R

$ ./bench --writers=2 --readers=1 --lock-type=mutex
Remover (mutex): 0.694972
Searcher (mutex): 0.696332
Remover (mutex): 0.696437
$ ./bench --writers=2 --readers=1 --lock-type=mutex
Remover (mutex): 1.393337
Remover (mutex): 1.393542
Searcher (mutex): 1.389409
$ ./bench --writers=2 --readers=1 --lock-type=mutex
Searcher (mutex): 1.548567
Remover (mutex): 1.579130
Remover (mutex): 1.579397

$ ./bench --writers=2 --readers=1 --lock-type=shared
Remover (shared mutex): 1.294029
Remover (shared mutex): 1.300796
Searcher (shared mutex): 1.297780
$ ./bench --writers=2 --readers=1 --lock-type=shared
Remover (shared mutex): 1.151370
Searcher (shared mutex): 1.152947
Remover (shared mutex): 1.161742
$ ./bench --writers=2 --readers=1 --lock-type=shared
Remover (shared mutex): 1.031493
Remover (shared mutex): 1.040036
Searcher (shared mutex): 1.048062

$ ./bench --writers=2 --readers=1 --lock-type=spinlock
Remover (spinlock): 0.894309
Searcher (spinlock): 0.892175
Remover (spinlock): 0.894851
$ ./bench --writers=2 --readers=1 --lock-type=spinlock
Searcher (spinlock): 0.967689
Remover (spinlock): 1.205575
Remover (spinlock): 1.205928
$ ./bench --writers=2 --readers=1 --lock-type=spinlock
Remover (spinlock): 0.936322
Searcher (spinlock): 0.932160
Remover (spinlock): 0.937071
```
