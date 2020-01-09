# puzzled
Brandwatch 2019 puzzler: Crossword grid generator

* Generate word squares of size M x N cells
* Each cell must contain two letters or no letters
* Each row and column must spell a word
* 50% or more of the cells in each row and column must be filled
* At least one cell in each row and column must be blank
* Don’t repeat words anywhere
* Use uncapitalised words from /usr/share/dict/words
* Any language, output format, etc. is fine


## Install

```
make
```

### Run

```
./puzzled -M <M> -N <N> [-d <dictionnary>]
```


### Test your grid

```
./puzzled -t <test_file_path>
```

The validation uses this format
```
abacay......
......abacus
ac..inetan..
..ne....ther
```

### Usage
```
Usage:
./puzzled -M nRows -N nColumns [-d dictionnaryFilePath]
	Where M > 0 and N > 0

-q to disable grid output, can only be coupled with -t
-i to run in interactive mode
-l set the maximum amount of grid you would like to generate does not work with -i
-o generate a file for each puzzler found and stores them in ./gen folder
-t [testFilePath] to test crossword:
	./puzzled -t [testFilePath]
```

### Algorithm

todo...

## License

MIT.
