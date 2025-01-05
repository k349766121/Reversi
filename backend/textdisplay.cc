#include "textdisplay.h"

// initilaize to all -
TextDisplay::TextDisplay(size_t n) {
    for (size_t i = 0; i < n; i++){
        std::vector<char> pushed;
        // initialize each row
        for (size_t j = 0; j < n; j++){
            pushed.emplace_back('-');
        }
        theDisplay.emplace_back(pushed);
    }
}

// chagne the display
void TextDisplay::notify(Subject<Info, State> &whoNotified){
    size_t r = whoNotified.getInfo().row;
    size_t c = whoNotified.getInfo().col;
    if (whoNotified.getInfo().colour == Colour::Black) {
        theDisplay[r][c] = 'B';
    } else if (whoNotified.getInfo().colour == Colour::White) {
        theDisplay[r][c] = 'W';
    }
}


std::vector<std::vector<char>> TextDisplay::showDisplay(){
    return theDisplay;
}
