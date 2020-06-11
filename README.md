## Building

Project can be built using `cmake` in the root directory as follows:
```
mkdir build
cd build
cmake .. && make
```

It can be build also directly using `g++` as follows:
```
cd src
g++ -O2 -Wall *.cpp -o word_matrix
```

## Usage
```
./word_matrix path_to_text_file
```
