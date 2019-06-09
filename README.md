# premultiply_alpha

```
macOS 10.14.5
MacBook Pro (15-inch, 2017)
Intel(R) Core(TM) i7-7920HQ CPU @ 3.10GHz


Run on (8 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32K (x4)
  L1 Instruction 32K (x4)
  L2 Unified 262K (x4)
  L3 Unified 8388K (x1)
Load Average: 1.24, 1.60, 1.68
-----------------------------------------------------------------------------
Benchmark                   Time             CPU   Iterations UserCounters...
-----------------------------------------------------------------------------
v1_plain_mean         1189884 ns      1189573 ns         1000 itr=840.865/s
v1_plain_median       1184059 ns      1183786 ns         1000 itr=844.747/s
v1_plain_stddev         20575 ns        20166 ns         1000 itr=13.4227/s

v1_simd_x86_mean       297866 ns       297784 ns         1000 itr=3.3616k/s
v1_simd_x86_median     294995 ns       294927 ns         1000 itr=3.39067k/s
v1_simd_x86_stddev       9863 ns         9794 ns         1000 itr=105.51/s

v2_plain_mean          323541 ns       323451 ns         1000 itr=3.09678k/s  Thanks Dot and Beached (discord #include)
v2_plain_median        318932 ns       318855 ns         1000 itr=3.13623k/s  Thanks Dot and Beached (discord #include)
v2_plain_stddev         13598 ns        13542 ns         1000 itr=122.588/s   Thanks Dot and Beached (discord #include)

v3_simd_x86_mean       264323 ns       264247 ns         1000 itr=3.79233k/s  Thanks Peter Cordes (stackoverflow)
v3_simd_x86_median     260641 ns       260560 ns         1000 itr=3.83788k/s  Thanks Peter Cordes (stackoverflow)
v3_simd_x86_stddev      12466 ns        12422 ns         1000 itr=170.36/s    Thanks Peter Cordes (stackoverflow)

v4_simd_x86_mean       266174 ns       266109 ns         1000 itr=3.76502k/s  Thanks chtz (stackoverflow)
v4_simd_x86_median     262940 ns       262916 ns         1000 itr=3.8035k/s   Thanks chtz (stackoverflow)
v4_simd_x86_stddev      11993 ns        11962 ns         1000 itr=159.906/s   Thanks chtz (stackoverflow)
```
