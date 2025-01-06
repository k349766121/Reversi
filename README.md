# Reversi
Reversi
This program is a Reversi game made by Xinhao(Ken) Wang. Uses C++ as the backend and react.js as the frontend. Communicates between the backend and frontend using API. Observer pattern and OOP principles were well considered.
Rules for this game be found at https://en.wikipedia.org/wiki/Reversi. This code version allows players to play any move on the board.

# Acknowledgment
Some starting code in the backend was provided by CS246E, an enriched CS course at the University of Waterloo taught by the Professor Brad Lushman.

# How to start the game
cd backend
./program
cd frontend
npm install
npm run dev

# How to compile
Makefile was available in the backend folder. C++20 standard was used. Library Crow and Asio were used to implement API. If needed to recompile, update the position of crow and asio library in the Makefile before using make. Executable file was 
named as program.
