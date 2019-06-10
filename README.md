# premultiply_alpha

macOS 10.14.5
MacBook Pro (15-inch, 2017)
Intel(R) Core(TM) i7-7920HQ CPU @ 3.10GHz

```
Run on (8 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32K (x4)
  L1 Instruction 32K (x4)
  L2 Unified 262K (x4)
  L3 Unified 8388K (x1)
Load Average: 1.32, 1.46, 1.36
-----------------------------------------------------------------------------
Benchmark                   Time             CPU   Iterations UserCounters...
-----------------------------------------------------------------------------
v1_plain_mean         1196208 ns      1195879 ns          100 itr=836.322/s
v1_plain_median       1193821 ns      1193583 ns          100 itr=837.814/s
v1_plain_stddev         14524 ns        14333 ns          100 itr=9.86728/s

v1_simd_x86_mean       300903 ns       300829 ns          100 itr=3.32659k/s
v1_simd_x86_median     300238 ns       300102 ns          100 itr=3.3322k/s
v1_simd_x86_stddev       8375 ns         8367 ns          100 itr=88.9029/s

Thanks Dot and Beached (discord #include)
v2_plain_mean          321179 ns       321102 ns          100 itr=3.11552k/s
v2_plain_median        319993 ns       319963 ns          100 itr=3.12537k/s
v2_plain_stddev          6499 ns         6485 ns          100 itr=61.8953/s

Thanks Peter Cordes (stackoverflow)
v3_simd_x86_mean       260714 ns       260654 ns          100 itr=3.83899k/s
v3_simd_x86_median     259644 ns       259613 ns          100 itr=3.85188k/s
v3_simd_x86_stddev       6800 ns         6785 ns          100 itr=96.3051/s

Thanks chtz (stackoverflow)
v4_simd_x86_mean       263912 ns       263844 ns          100 itr=3.79343k/s
v4_simd_x86_median     262171 ns       262134 ns          100 itr=3.81484k/s
v4_simd_x86_stddev       8038 ns         8012 ns          100 itr=110.046/s


v5_plain_mean           96073 ns        96049 ns          100 itr=10.4147k/s
v5_plain_median         95793 ns        95776 ns          100 itr=10.441k/s
v5_plain_stddev          1752 ns         1745 ns          100 itr=186.012/s
```
