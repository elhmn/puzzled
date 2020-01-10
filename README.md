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

## Run
```
./puzzled -M <M> -N <N> [-d <dictionnary>]
```
OR
use `-l <N>` to limit the amount of crosswords you would like to generate
```
example: ./puzzled -l 1 -M 3 -N 3 [-d <dictionnary>]
crossword generator is running with M = [3] && N = [3] ...

initaliase dictionnary...
dictionnary file line count: 235886
dict {
	dict->ceven:  118695
	dict->wcount: 5272
	dict->maxlen: 4
	dict->minlen: 4
}
dictionnary initialised

bruteforce is running...
Generating every combinations...
15816 combinations generated
Bactracking is running...
Crossword generated:
0-[aani]
1-[asak]
2-[ruin]
3-[aaru]
4-[nias]
5-[akin]


0-[aani..]
1-[..asak]
2-[ru..in]

1 crosswords were genereated
```

## Save your crossword

your grid can be saved in `./gen` folder you can simply us `-o` option
```
./puzzled -o -M <M> -N <N> [-d <dictionnary>]
```

## Test the generated crosswords
```
make testgen
```
clean them with `make cleangen`

## Interactive mode

With `-i` to run in interactive mode
```
./puzzled -i -M <M> -N <N> [-d <dictionnary>]
```

## Test your grid

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

## Usage
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

## Algorithm
I have first implemented a backtracking bruteforce algorithm that prints out every possible solutions and added basic bound functions to prune unecessary branches.

#### 0- Find min and max m and n size for a specific dictionnary
* the longest word in the dictionnary must be greater than `max(m, n)`
* the shortest word in the dictionnary must be lesser than `4 * (min(m, n) - 1)`

#### 1- Initialise a dictionnary :
* get words that has valid characters between `a` and `z` or `A` and `Z`
* lower case valid words
* get words that can fit in the grid with the additionnal empty cell -> whose size is : `len(w) >= max(m - 1, n - 1) * 2`
* create a hash table containing words
* create a hash table of every possible cell alignment on a column to speed up backtracking `has_valid_column` bound function
```
example:
considering this dictionnary:
 abac
 nether
 acinethan

 the hash table will contain:
 ->ab
 ->abac
 ->ne
 ->nether
 ->ac
 ->acine
 ->acneth
 ->aninethan
 ```
 
#### 2- Generate every grid row combination
For a grid of `m` and `n = 4` the possible combination of abac are:
```
0-[abac....]
1-[ab..ac..]
2-[ab....ac]
3-[..ab..ac]
4-[....abac]
5-[..abac..]
```

#### 3- Then run the bactracking
It isn't that explanatory ?
```c
void backtracking(t_dict *dict, char **grid,
		int rc, int cc, int i, unsigned int *gcount) {
	char *tmp = NULL;

	if (i >= rc) {
		if (grid_correct(grid, *dict, rc, cc) >= 0) {
			correct_grid_output(dict, grid, rc, cc, i, gcount);
		}
		return;
	}

	//...few bound functions

	for (int w = 0; w < dict->wcount; w++) {
		//...more few bound functions
		
		for (int comb = 0; dict->comb[w][comb]; comb++) {
			tmp = grid[i];
			grid[i] = dict->comb[w][comb];
			backtracking(dict, grid, rc, cc, i + 1, gcount);
			grid[i] = tmp;
		}
	}
	return ;
}
```

#### 4- Bounding functions
* the backtrack returns when a column is not valid, means that the columns that has been generated are unable to form a word if we add one more row in the grid

let's consider again this hash table:
```
 ->ab
 ->abac
 ->ne
 ->nether
 ->ac
 ->acine
 ->acneth
 ->aninethan

if we have a grid of :

0-[abac....]
1-[ab..ac..]

We check that [abab] , [ac] and [ac] belongs to the above hash table and if one of them
does not belong to it we conclude that that grid is invalid and prune its branch
```

* do not proceed if a word was already placed in the grid

#### 5- Data structures
* `List`: I have implemented a list data structure with some handy functions to manipulate them
```c
typedef struct		s_list
{
	void		*content;
	size_t		content_size;
	struct s_list	*next;

} 			t_list;
```
* `Hash` table: I wrote a very basic hash table that is simple an array of chained list (to deal with collision)
```c
typedef struct		s_hash
{
	t_list		**table;
	size_t		size;
}			t_hash;
```

* `Arrays`: This is my favourite use arrays they are cache friendy and they are awesome

## Conclusion
The initial idea was to build a brute force to make sure that I don't miss any crossword, add more heuristic and then with the generated crossword come up with a more Big O friendly solution. As you can see the bruteforce is not very rich in heuristics at the moment but it might change in the future.
