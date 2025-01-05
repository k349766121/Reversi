#include "grid.h"

Grid::~Grid(){
    delete td;
}

bool Grid::isFull() const {
    return numPiece == size * size;
}

// produce the colour that won the game
Colour Grid::whoWon() const {
    int blackNum = 0;
    int whiteNum = 0;
    // count all the colour
    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < size; j++){
            if ((theGrid[i][j]).getInfo().colour == Colour::Black) {
                blackNum++;
            } else if ((theGrid[i][j]).getInfo().colour == Colour::White) {
                whiteNum++;
            }
        }
    }
    if (blackNum > whiteNum) {
        return Colour::Black;
    } else if (blackNum < whiteNum) {
        return Colour::White;
    } else {
        return Colour::NoColour;
    }
}

void Grid::init(size_t n)  {
    theGrid.clear();
    delete td;
    size = n;
    numPiece = 0;
    td = new TextDisplay{size};
    for (size_t i = 0; i < n; i++){
        std::vector<Cell> pushed;
        // initialize each row
        for (size_t j = 0; j < n; j++){
            pushed.emplace_back(Cell{i, j});
            (pushed[j]).attach(td);
        }
        theGrid.emplace_back(std::move(pushed));
    }
    int cap = n;
    // attach neighbourhood as observer
    for (int i = 0; i < cap; i++){
        for (int j = 0; j < cap; j++){
            
            if (i + 1 < cap && j + 1 < cap) {
                (theGrid[i][j]).attach(&(theGrid[i + 1][j + 1]));
            }

            if (i + 1 < cap && j - 1 >= 0) {
                (theGrid[i][j]).attach(&(theGrid[i + 1][j - 1]));
            }

            if (i + 1 < cap) {
                (theGrid[i][j]).attach(&(theGrid[i + 1][j]));
            }
            if (j + 1 < cap) {
                (theGrid[i][j]).attach(&(theGrid[i][j + 1]));
            }
            if (i - 1 >= 0 && j - 1 >= 0) {
                
                (theGrid[i][j]).attach(&(theGrid[i - 1][j - 1]));
            }

            if (i - 1 >= 0 && j + 1 < cap) {
                (theGrid[i][j]).attach(&(theGrid[i - 1][j + 1]));
            }

            if (i - 1 >= 0) {
                (theGrid[i][j]).attach(&(theGrid[i - 1][j]));
            }
            if (j - 1 >= 0) {
                (theGrid[i][j]).attach(&(theGrid[i][j - 1]));
            }
        }
    }
}


void Grid::setPiece(size_t r, size_t c, Colour colour) {
    if (0 <= r && r < size && 0 <= c && c < size && (theGrid[r][c]).getInfo().colour == Colour::NoColour) {
        // if the positon is empty, increase the count
        numPiece++;
        (theGrid[r][c]).setPiece(colour);
        // notify the cell and surrouning cell

        if (this->isFull()) {
            Colour winner = this->whoWon();
            throw winner;
        }
    } else {
        throw InvalidMove{};
    }
}

std::vector<std::vector<char>> Grid::showDisplay(){
    return td->showDisplay();
}

