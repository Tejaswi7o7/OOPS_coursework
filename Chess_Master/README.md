# The Galactic Chessmaster's Challenge

## Problem Statement
In the year 3045, the Intergalactic Chess Federation (ICF) faces a unique challenge. 
The reigning champion, Grandmaster Zara Nova, has proposed a revolutionary twist to the ancient game: Quantum Chess, played on an n x n board where n can vary from match to match.
In Quantum Chess, each of the n x n square's "quantum state" is represented by a number. Before each match, the board must be prepared following two crucial steps:
1. **Row Stabilization**: Each row of the board must be sorted in ascending or descending order of quantum states, ensuring stable quantum entanglement within rows.
2. **Inversion Calculation**: In this challenge, an inversion refers to the instance where, in the board, a square with a higher (strictly greater) quantum state precedes a square with a lower quantum state. The total inversion value is crucial for determining the match's difficulty level.

Meanwhile, the ICF is also planning the upcoming Galactic Chess Olympics. They face a logistical challenge of pairing players for the opening rounds. The players are spread across the vast Olympic Space Station which is represented as a 2D plane. Each player’s coordinates are available with the ICF. To start the game, the ICF needs to find the pair of players with the closest distance (least Euclidean distance).

## Methods
You can create whatever classes you want.  
You need to create the following methods:  
- `sortRows(Comparator comparator)`: Sorts the matrix row-wise using a custom functor Comparator (ascending or descending - this will be mentioned in the test case).
  - Arguments: A `Comparator` object.
- `countInversions()`: An inversion is the phenomenon where a strictly greater valued element is present at a smaller index in the matrix compared to a greater valued element  
This function countInversions() counts and returns the number of inversions in the matrix. The inversions are counted by flattening the 2D matrix into a 1D array, i.e. the inversions will be counted across the whole matrix.
  - For example, let the matrix be  
    1 3  
    3 2  
  So by flattening it we get the 1d array 1 3 3 2.
    - For index 0, #inversions = 0 (Since element at index 0 is not strictly greater than any of the elements at an index greater than 0).
    - For index 1, #inversions = 1 (Since element at index 1 is strictly greater than the element at index 3).
    - For index 2, #inversions = 1 (Since element at index 2 is strictly greater than the element at index 3).
    - For index 3, #inversions = 0 (Since element at index 3 is not strictly greater than any of the elements at an index greater than 3).  
    Hence total inversions = 2  
    The function countInversions() should return 2 for this matrix.  
- `display()`: Prints the matrix.  
- `closestPair()`: Finds and returns the coordinates of the pair of points with the least Euclidean distance. If the distance between two different pairs are the same, then return the pair with the lesser value of x coordinate. If both distance and x coordinate are same, then return the pair with lesser value of y coordinate.

## Input Format
The following commands will be given as input:
- Create 2D Matrix:
  - Command: `CREATE_2D size`
  - Followed by `size` lines each having `size` integers each denoting the quantum states.
- Sort a Matrix:
  - Command: `SORT_2D ascending`
  - Command: `SORT_2D descending`
- Count Inversions:
  - Command: `INVERSION_2D`
- Display Matrix:
  - Command: `DISPLAY_2D`
- Closest Pair:
  - Command: `CLOSEST_2D num_points`
  - Followed by `num_points` lines each having two space separated integers denoting the coordinates of the players
The input will end with the `END` command.

## Output Format
- The `DISPLAY_2D` command should output the matrix in a row-wise manner. Each row will be printed on a new line with each element of a row being separated by a space “ “.
- The `INVERSION_2D` command will output a single integer on a newline indicating the number of inversions in the matrix.
- The `CLOSEST_2D` command will output four integers on a single line separated by a space “ “. The first two integers denote the coordinates of the first point and the next two integers denote the coordinates of the second point. The points are ordered in the same order as they appear in the input. For example, if the two points are P1 (x1, y1) and P2 (x2, y2) where the point P1 appears before the point P2 in the input, then the output of CLOSEST_2D will be like:  
x1 y1 x2 y2
