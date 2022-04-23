Emulating a mill game for AIs to play against each other.

## Mill-board
The board is fitted in a 28 byte object but requires bitshifting to modify.  
(24 bytes for all the existing positions + gamestate flags)  
The small board-size might be good for brute-force approaches.

## May implement these "AI" approaches
- brute-force best tactics
- usage of decision trees

## how to build
Corresponding CmakeLists can be found in tests and src.  
  
go into build/ and execute   
`cmake ../src/` for chaching app  
`cmake ../tests/` for caching tests  
then run `make`
