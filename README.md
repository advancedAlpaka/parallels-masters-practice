#### Task 1

Нужно реализовать quicksort. 
От Вас требуется написать последовательную версию алгоритма (seq) и параллельную версию (par). Взять случайный массив из 10^8 элементов и отсортировать. (Усреднить по 5 запускам) Сравнить время работы par на 4 процессах и seq на одном процессе - у Вас должно быть раза в 3 быстрее.  (Если будет медленнее, то выставление баллов оставляется на наше усмотрение.)
Также нужно сопроводить тестами на корректность работы алгоритма.

Нужен код на гитхабе и результаты запусков в README.md. Код, который запускает, тоже должен лежать в репо.

Присылать письмо на почту с темой "CW1. <ФИО>".

Unable to determine clock rate from sysctl: hw.cpufrequency: No such file or directory
This does not affect benchmark measurements, only the metadata output.
***WARNING*** Failed to set thread affinity. Estimated CPU frequency may be incorrect.
2024-12-02T00:18:01+03:00
Running /Users/moskvichevv2/C++ projects/parallel-practice/build/benchmarks
Run on (12 X 24 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB
  L1 Instruction 128 KiB
  L2 Unified 4096 KiB (x12)
Load Average: 2.93, 2.69, 2.71
------------------------------------------------------------------------------------------------------
Benchmark                                                            Time             CPU   Iterations
------------------------------------------------------------------------------------------------------
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        5894792875 ns   5893800000 ns            1
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        5844059334 ns   5843819000 ns            1
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        5947158958 ns   5937879000 ns            1
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        5949460584 ns   5891203000 ns            1
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        5869227959 ns   5869196000 ns            1
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_mean   5900939942 ns   5887179400 ns            5
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_median 5894792875 ns   5891203000 ns            5
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_stddev   46822244 ns     34763480 ns            5
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_cv           0.79 %          0.59 %             5
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5        1376923375 ns   1173046000 ns            1
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5        1328761750 ns   1239729000 ns            1
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5        1274299500 ns   1167121000 ns            1
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5        1326980250 ns   1265817000 ns            1
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5        1316089625 ns   1258586000 ns            1
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_mean   1324610900 ns   1220859800 ns            5
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_median 1326980250 ns   1239729000 ns            5
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_stddev   36617235 ns     47366868 ns            5
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_cv           2.76 %          3.88 %             5


Судя по бенчам, запущенным в последний момент, разрыв примерно в 4-5 раз.
А это традиционная булочкака в домашке:

![](src/dog.jpg)
#### Task 2

Нужно реализовать параллельный bfs. От Вас требуется написать последовательную версию алгоритма  (seq) и параллельную версию (par). Протестировать надо на кубическом графе со стороной 500 и источником в (0, 0, 0). (Усреднить по 5 запускам) Сравнить время работы par на 4 процессах и seq на одном процессе - у Вас должно быть раза в 3 быстрее.  (Если будет медленнее, то выставление баллов оставляется на моё усмотрение.) Учтите, что Ваш bfs должен работать на любом графе, если Вам дан его список смежности.
Также нужно сопроводить тестами на корректность работы алгоритма.

Нужен код на гитхабе и результаты запусков в README.md. Код, который запускает, тоже должен лежать в репо.

Присылать письмо на почту с темой "CW2. <ФИО>".