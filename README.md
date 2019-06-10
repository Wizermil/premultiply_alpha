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
-----------------------------------------------------------------------------
Benchmark                   Time             CPU   Iterations UserCounters...
-----------------------------------------------------------------------------
v1_plain_mean         1197390 ns      1197014 ns          100 itr=835.516/s
v1_plain_median       1193932 ns      1193557 ns          100 itr=837.832/s
v1_plain_stddev         13772 ns        13562 ns          100 itr=9.3182/s

v1_simd_x86_mean       301928 ns       301826 ns          100 itr=3.31563k/s
v1_simd_x86_median     300827 ns       300759 ns          100 itr=3.32492k/s
v1_simd_x86_stddev       8375 ns         8335 ns          100 itr=89.898/s

Thanks Dot and Beached (discord #include)
v2_plain_mean          322754 ns       322692 ns          100 itr=3.10078k/s
v2_plain_median        320691 ns       320615 ns          100 itr=3.11901k/s
v2_plain_stddev          8015 ns         8007 ns          100 itr=75.2172/s

Thanks Peter Cordes (stackoverflow)
v3_simd_x86_mean       246171 ns       246107 ns          100 itr=4.06517k/s
v3_simd_x86_median     245191 ns       245167 ns          100 itr=4.07885k/s
v3_simd_x86_stddev       5423 ns         5406 ns          100 itr=87.13/s

Thanks chtz (stackoverflow)
v4_simd_x86_mean       262580 ns       262495 ns          100 itr=3.81245k/s
v4_simd_x86_median     260326 ns       260258 ns          100 itr=3.84234k/s
v4_simd_x86_stddev       7447 ns         7382 ns          100 itr=102.565/s

Thanks Peter Cordes and chtz (stackoverflow) for AVX2
v5_simd_x86_mean       158456 ns       158409 ns          100 itr=6.31411k/s
v5_simd_x86_median     158248 ns       158165 ns          100 itr=6.3225k/s
v5_simd_x86_stddev       2340 ns         2329 ns          100 itr=92.1406/s
```
