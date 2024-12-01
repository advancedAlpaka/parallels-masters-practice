#### Task 1

Нужно реализовать quicksort. 
От Вас требуется написать последовательную версию алгоритма (seq) и параллельную версию (par). Взять случайный массив из 10^8 элементов и отсортировать. (Усреднить по 5 запускам) Сравнить время работы par на 4 процессах и seq на одном процессе - у Вас должно быть раза в 3 быстрее.  (Если будет медленнее, то выставление баллов оставляется на наше усмотрение.)
Также нужно сопроводить тестами на корректность работы алгоритма.

Нужен код на гитхабе и результаты запусков в README.md. Код, который запускает, тоже должен лежать в репо.

Присылать письмо на почту с темой "CW1. <ФИО>".

Unable to determine clock rate from sysctl: hw.cpufrequency: No such file or directory
This does not affect benchmark measurements, only the metadata output.
***WARNING*** Failed to set thread affinity. Estimated CPU frequency may be incorrect.
2024-12-01T23:52:25+03:00
Running /Users/moskvichevv2/C++ projects/parallel-practice/build/benchmarks
Run on (12 X 24 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB
  L1 Instruction 128 KiB
  L2 Unified 4096 KiB (x12)
Load Average: 2.94, 2.96, 2.99
------------------------------------------------------------------------------------------------------
Benchmark                                                            Time             CPU   Iterations
------------------------------------------------------------------------------------------------------
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        5835410375 ns   5835407000 ns            1
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        5854772541 ns   5854746000 ns            1
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        5950985166 ns   5944680000 ns            1
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        6954374125 ns   6924880000 ns            1
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5        6027221000 ns   6013424000 ns            1
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_mean   6124552641 ns   6114627400 ns            5
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_median 5950985166 ns   5944680000 ns            5
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_stddev  470262524 ns    458567306 ns            5
QuicksortFixture<SeqAlgo>/SeqQuicksortTest/repeats:5_cv           7.68 %          7.50 %             5
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5         580611083 ns    552828000 ns            1
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5         557394708 ns    485745000 ns            1
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5         554448125 ns    519445000 ns            1
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5         589491708 ns    577678000 ns            1
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5         557931250 ns    543144000 ns            1
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_mean    567975375 ns    535768000 ns            5
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_median  557931250 ns    543144000 ns            5
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_stddev   15956465 ns     34894978 ns            5
QuicksortFixture<ParAlgo>/ParQuicksortTest/repeats:5_cv           2.81 %          6.51 %             5
zsh: segmentation fault  "/Users/moskvichevv2/C++ projects/parallel-practice/build/benchmarks"


Судя по бенчам, запущенным в последний момент, разрыв примерно в 10 раз.
А это традиционная булочкака в домашке:

![](src/dog.jpg)
#### Task 2

Нужно реализовать параллельный bfs. От Вас требуется написать последовательную версию алгоритма  (seq) и параллельную версию (par). Протестировать надо на кубическом графе со стороной 500 и источником в (0, 0, 0). (Усреднить по 5 запускам) Сравнить время работы par на 4 процессах и seq на одном процессе - у Вас должно быть раза в 3 быстрее.  (Если будет медленнее, то выставление баллов оставляется на моё усмотрение.) Учтите, что Ваш bfs должен работать на любом графе, если Вам дан его список смежности.
Также нужно сопроводить тестами на корректность работы алгоритма.

Нужен код на гитхабе и результаты запусков в README.md. Код, который запускает, тоже должен лежать в репо.

Присылать письмо на почту с темой "CW2. <ФИО>".