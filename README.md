# Tic-Tac-Toe

- Compiler: CMake

- Required library: OpenGL

- This program is an AI that can play Tic-Tac-Toe on a general m x n board with a moderate win rate against a human player OpenGL API is used to implement the GUI of the game

- To use the program, type: cmake -DCMAKE_BUILD_TYPE="Release" (This only needs to be done once for the first time running the program)

- Then type: make

- The program will be built in /bin. To run the program, type: ./bin/TTT <#Rows> <#Columns> <#toWin> <player1Type> <player2Type> <depth>
  where:
  - #Rows: number of rows
  - #Columns: number of columns
  - #toWin: number of consecutive needed to win the game
  - player1Type, player2Type: could be either "human", "random" (AI will play random moves), or "AI" (AI will play smarter)
  - depth: depth of the minimax tree. Bigger depth = smarter AI = more runtime

- Enter #rows and #columns then hit Enter

- Use left click to let the program run next steps
