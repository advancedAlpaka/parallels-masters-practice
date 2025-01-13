#### Task 1

Нужно реализовать quicksort. 
От Вас требуется написать последовательную версию алгоритма (seq) и параллельную версию (par). Взять случайный массив из 10^8 элементов и отсортировать. (Усреднить по 5 запускам) Сравнить время работы par на 4 процессах и seq на одном процессе - у Вас должно быть раза в 3 быстрее.  (Если будет медленнее, то выставление баллов оставляется на наше усмотрение.)
Также нужно сопроводить тестами на корректность работы алгоритма.

Нужен код на гитхабе и результаты запусков в README.md. Код, который запускает, тоже должен лежать в репо.

Присылать письмо на почту с темой "CW1. <ФИО>".

Самописный код в main:

Average Sequential Time: 6.59191s
Average Parallel Time: 2.12274s
Speedup: 3.10537x

google/benchmarks:

Unable to determine clock rate from sysctl: hw.cpufrequency: No such file or directory
This does not affect benchmark measurements, only the metadata output.
***WARNING*** Failed to set thread affinity. Estimated CPU frequency may be incorrect.
2025-01-13T03:34:35+03:00
Running /Users/moskvichevv2/C++ projects/parallel-practice/build/benchmarks
Run on (12 X 24 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB
  L1 Instruction 128 KiB
  L2 Unified 4096 KiB (x12)
Load Average: 2.56, 2.52, 2.38
----------------------------------------------------------------------------------------------------------------------
Benchmark                                                            Time             CPU   Iterations UserCounters...
----------------------------------------------------------------------------------------------------------------------
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        6477762583 ns   6470406000 ns            1 HASH_ARRAY=1.73694E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        6456831375 ns   6451973000 ns            1 HASH_ARRAY=6.57281E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        6581184542 ns   6563870000 ns            1 HASH_ARRAY=8.64022E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        6311793625 ns   6307680000 ns            1 HASH_ARRAY=4.73367E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        6613747542 ns   6608469000 ns            1 HASH_ARRAY=9.25566E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_mean   6488263933 ns   6480479600 ns            5 HASH_ARRAY=6.18786E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_median 6477762583 ns   6470406000 ns            5 HASH_ARRAY=6.57281E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_stddev  118975238 ns    116306761 ns            5 HASH_ARRAY=3.06182E IS_GOOD=0 PARLAY_NUM_THREADS=0
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_cv           1.83 %          1.79 %             5 HASH_ARRAY=49.48% IS_GOOD=0.00% PARLAY_NUM_THREADS=0.00%
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5        3238597292 ns   3231769000 ns            1 HASH_ARRAY=7.77194E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5        2113632417 ns   2022893000 ns            1 HASH_ARRAY=14.2701E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5        3357353625 ns   2861635000 ns            1 HASH_ARRAY=8.4541E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5        2061414417 ns   2025759000 ns            1 HASH_ARRAY=17.7471E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5        2069138958 ns   2068104000 ns            1 HASH_ARRAY=10.161E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_mean   2568027342 ns   2442032000 ns            5 HASH_ARRAY=11.6809E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_median 2113632417 ns   2068104000 ns            5 HASH_ARRAY=10.161E IS_GOOD=1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_stddev  667967264 ns    567568073 ns            5 HASH_ARRAY=4.22805E IS_GOOD=0 PARLAY_NUM_THREADS=0
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_cv          26.01 %         23.24 %             5 HASH_ARRAY=36.20% IS_GOOD=0.00% PARLAY_NUM_THREADS=0.00%


![](src/dog.jpg)
#### Task 2

Нужно реализовать параллельный bfs. От Вас требуется написать последовательную версию алгоритма  (seq) и параллельную версию (par). Протестировать надо на кубическом графе со стороной 500 и источником в (0, 0, 0). (Усреднить по 5 запускам) Сравнить время работы par на 4 процессах и seq на одном процессе - у Вас должно быть раза в 3 быстрее.  (Если будет медленнее, то выставление баллов оставляется на моё усмотрение.) Учтите, что Ваш bfs должен работать на любом графе, если Вам дан его список смежности.
Также нужно сопроводить тестами на корректность работы алгоритма.

Нужен код на гитхабе и результаты запусков в README.md. Код, который запускает, тоже должен лежать в репо.

Присылать письмо на почту с темой "CW2. <ФИО>".

Unable to determine clock rate from sysctl: hw.cpufrequency: No such file or directory
This does not affect benchmark measurements, only the metadata output.
***WARNING*** Failed to set thread affinity. Estimated CPU frequency may be incorrect.
2024-12-17T17:37:30+03:00
Running /Users/moskvichevv2/C++ projects/parallel-practice/build/benchmarks
Run on (12 X 24 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB
  L1 Instruction 128 KiB
  L2 Unified 4096 KiB (x12)
Load Average: 3.04, 2.86, 2.80
----------------------------------------------------------------------------------------------------------------------------------------
Benchmark                                                                              Time             CPU   Iterations UserCounters...
----------------------------------------------------------------------------------------------------------------------------------------
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5                          5818396000 ns   5803050000 ns            1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5                          5886361541 ns   5877226000 ns            1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5                          5904583584 ns   5885906000 ns            1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5                          5832444417 ns   5831738000 ns            1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5                          5779963834 ns   5772766000 ns            1 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_mean                     5844349875 ns   5834137200 ns            5 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_median                   5832444417 ns   5831738000 ns            5 PARLAY_NUM_THREADS=4
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_stddev                     50877268 ns     48154044 ns            5 PARLAY_NUM_THREADS=0
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_cv                             0.87 %          0.83 %             5 PARLAY_NUM_THREADS=0.00%
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5                          1089016709 ns    940666000 ns            1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5                           814558209 ns    791085000 ns            1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5                           867072875 ns    843281000 ns            1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5                           957099958 ns    934103000 ns            1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5                           958883792 ns    934464000 ns            1 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_mean                      937326309 ns    888719800 ns            5 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_median                    957099958 ns    934103000 ns            5 PARLAY_NUM_THREADS=4
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_stddev                    104729713 ns     67911363 ns            5 PARLAY_NUM_THREADS=0
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_cv                            11.17 %          7.64 %             5 PARLAY_NUM_THREADS=0.00%
BreadthFirstSearchFixture<SeqAlgo>/SeqBreadthFirstSearchTest/repeats:5        3275239500 ns   3056180000 ns            1 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<SeqAlgo>/SeqBreadthFirstSearchTest/repeats:5        2890298542 ns   2887160000 ns            1 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<SeqAlgo>/SeqBreadthFirstSearchTest/repeats:5        2903163584 ns   2896661000 ns            1 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<SeqAlgo>/SeqBreadthFirstSearchTest/repeats:5        2921548084 ns   2907546000 ns            1 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<SeqAlgo>/SeqBreadthFirstSearchTest/repeats:5        3039745708 ns   2991720000 ns            1 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<SeqAlgo>/SeqBreadthFirstSearchTest/repeats:5_mean   3005999084 ns   2947853400 ns            5 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<SeqAlgo>/SeqBreadthFirstSearchTest/repeats:5_median 2921548084 ns   2907546000 ns            5 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<SeqAlgo>/SeqBreadthFirstSearchTest/repeats:5_stddev  161804638 ns     73464223 ns            5 PARLAY_NUM_THREADS=0
BreadthFirstSearchFixture<SeqAlgo>/SeqBreadthFirstSearchTest/repeats:5_cv           5.38 %          2.49 %             5 PARLAY_NUM_THREADS=0.00%
BreadthFirstSearchFixture<ParAlgo>/ParBreadthFirstSearchTest/repeats:5        2727543042 ns   2670916000 ns            1 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<ParAlgo>/ParBreadthFirstSearchTest/repeats:5        2749808916 ns   2720024000 ns            1 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<ParAlgo>/ParBreadthFirstSearchTest/repeats:5        2816677042 ns   2762475000 ns            1 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<ParAlgo>/ParBreadthFirstSearchTest/repeats:5        2849736875 ns   2817734000 ns            1 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<ParAlgo>/ParBreadthFirstSearchTest/repeats:5        2826667667 ns   2801053000 ns            1 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<ParAlgo>/ParBreadthFirstSearchTest/repeats:5_mean   2794086708 ns   2754440400 ns            5 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<ParAlgo>/ParBreadthFirstSearchTest/repeats:5_median 2816677042 ns   2762475000 ns            5 PARLAY_NUM_THREADS=4
BreadthFirstSearchFixture<ParAlgo>/ParBreadthFirstSearchTest/repeats:5_stddev   52577004 ns     60008714 ns            5 PARLAY_NUM_THREADS=0
BreadthFirstSearchFixture<ParAlgo>/ParBreadthFirstSearchTest/repeats:5_cv           1.88 %          2.18 %             5 PARLAY_NUM_THREADS=0.00%