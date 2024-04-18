# premultiply_alpha

This repository is the result of this stackoverflow [discussion](https://stackoverflow.com/questions/56430849/how-to-make-premultiplied-alpha-function-faster-using-simd-instructions)

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
-----------------------------------------------------------------------------
Benchmark                   Time             CPU   Iterations UserCounters...
-----------------------------------------------------------------------------
v1_plain_mean         1191838 ns      1191535 ns          100 itr=839.288/s
v1_plain_median       1190866 ns      1190561 ns          100 itr=839.94/s
v1_plain_stddev          7815 ns         7710 ns          100 itr=5.40717/s

v1_simd_x86_mean       298872 ns       298807 ns          100 itr=3.34875k/s
v1_simd_x86_median     297684 ns       297651 ns          100 itr=3.35964k/s
v1_simd_x86_stddev       7702 ns         7691 ns          100 itr=82.7262/s

Thanks Dot and Beached (discord #include)
v2_plain_mean          321272 ns       321196 ns          100 itr=3.11473k/s
v2_plain_median        319833 ns       319793 ns          100 itr=3.12702k/s
v2_plain_stddev          6852 ns         6852 ns          100 itr=64.7511/s

Thanks Peter Cordes (stackoverflow)
v3_simd_x86_mean       246987 ns       246922 ns          100 itr=4.05231k/s
v3_simd_x86_median     246261 ns       246144 ns          100 itr=4.06266k/s
v3_simd_x86_stddev       6229 ns         6223 ns          100 itr=98.4511/s

Thanks chtz (stackoverflow)
v4_simd_x86_mean       267407 ns       267345 ns          100 itr=3.74625k/s
v4_simd_x86_median     264589 ns       264554 ns          100 itr=3.77995k/s
v4_simd_x86_stddev      10928 ns        10918 ns          100 itr=142.704/s

Thanks Peter Cordes and chtz (stackoverflow) for AVX2
v5_simd_x86_mean       158276 ns       158233 ns          100 itr=6.32177k/s
v5_simd_x86_median     157741 ns       157717 ns          100 itr=6.34048k/s
v5_simd_x86_stddev       2827 ns         2818 ns          100 itr=111.288/s

v6_simd_mean           250780 ns       250717 ns          100 itr=3.99056k/s
v6_simd_median         250211 ns       250160 ns          100 itr=3.99744k/s
v6_simd_stddev           5714 ns         5700 ns          100 itr=88.9239/s
```
