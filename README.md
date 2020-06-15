## Building

Whole project can be built using `cmake` in the root directory as follows:
```
mkdir build
cd build
cmake .. && make
```

Old iterative solution can be build also directly using `g++` as follows:
```
cd src
g++ -O2 -Wall -std=c++11 word_matrix_ite.cpp process_ite.cpp -o word_matrix_ite
```

New recursive solution can be build as follows:
```
cd src
g++ -O2 -Wall -std=c++11 word_matrix_rec.cpp process_rec.cpp process.cpp -o word_matrix_rec
```

## Usage
```
./word_matrix_rec path_to_text_file
```

### Example
An example with the included sample data file. Program is built using `g++` version `9.3.0` in Ubuntu 20.04.
```
./word_matrix_rec ../data/text_file_short
```

Program output to console:
```
Input file name: '../data/text_file_short'

Accepted length words (<=10), used as input:
==========
Vanasadama
Trassitee
Samaks
Kuni
Kesklinna
Gonsiori
Mida
Lahkneb
Gonsiori
Keskendume
Ja
Ka
Nii
==========

Too long words (>10), skipped from input:
==========
Lennujaamast
Olemasolevast
==========

Output matrix (10x10):
==========
++++++++++
Mida++++++
Kesklinna+
Trassitee+
SamaksKuni
LahknebNii
GonsioriKa
GonsioriJa
Keskendume
Vanasadama
==========
```
