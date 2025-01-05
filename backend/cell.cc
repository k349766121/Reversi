#include "cell.h"


Cell::Cell(size_t r, size_t c): r{r}, c{c} {}

void Cell::setPiece(Colour colour) {
    this->colour = colour;
    // newPiece, direction doesn't matter
    setState(State{StateType::NewPiece, colour, Direction::E});
    notifyObservers();
}

void Cell::toggle(){
    if (colour == Colour::Black) {
        colour = Colour::White;
    } else if (colour == Colour::White) {
        colour = Colour::Black;
    }
}

// getDirection consumes two cells and produce the direction of the message
Direction getDirection(Subject<Info, State> &from, Subject<Info, State> &self) {
    auto fromRow = from.getInfo().row;
    auto fromCol = from.getInfo().col;
    auto selfRow = self.getInfo().row;
    auto selfCol = self.getInfo().col;
    if (fromRow > selfRow) {
        if (fromCol > selfCol) {
            return Direction::NW;
        } else if (fromCol < selfCol) {
            return Direction::NE;
        } else {
            return Direction::N;
        }
    } else if (selfRow > fromRow) {
        if (fromCol > selfCol) {
            return Direction::SW;
        } else if (fromCol < selfCol) {
            return Direction::SE;
        } else {
            return Direction::S;
        }
    } else {
        if (fromCol > selfCol) {
            return Direction::W;
        } else if (fromCol < selfCol) {
            return Direction::E;
        } else {
            throw "notified self";
        }
    }
}

// reversedDirection takes in a Direction and reverse it
Direction reversedDirection(Direction dir) {
    if (dir == Direction::NW) {
        return Direction::SE;
    } if (dir == Direction::N) {
        return Direction::S;
    } if (dir == Direction::NE) {
        return Direction::SW;
    } if (dir == Direction::W) {
        return Direction::E;
    } if (dir == Direction::E) {
        return Direction::W;
    } if (dir == Direction::SW) {
        return Direction::NE;
    } if (dir == Direction::S) {
        return Direction::N;
    } if (dir == Direction::SE) {
        return Direction::NW;
    } else {
        throw "typeError";
    }
}

void Cell::notify(Subject<Info, State> &whoFrom) {
    // no colour, nothing changed

    if (colour != Colour::NoColour) {
        auto otherState = whoFrom.getState();
        // get notification from a new piece
        if (otherState.type == StateType::NewPiece) {
            if (colour == otherState.colour) {
                // new piece is the same colour
                return;
            } else {
                // different colour, keep the notification since I might be changed
                this->setState(State{StateType::Relay, otherState.colour, getDirection(whoFrom, *this)});
            }
        } else if (getDirection(whoFrom, *this) != otherState.direction) {
            // the information is not for my line
            return;
        } else if (otherState.type == StateType::Relay) {
            if (colour == otherState.colour) {
                this->setState(State{StateType::Reply, otherState.colour, reversedDirection(otherState.direction)});
                
            } else {
                // different colour
                this->setState(otherState);
            } 
        } else if (otherState.type == StateType::Reply) {
            if (colour == otherState.colour) {
                if ((this->getState()).type == StateType::NewPiece) {
                    return;
                }
                this->setState(otherState);
                
            } else {
                // different colour
                toggle();
                this->setState(otherState);
            } 
        }
        notifyObservers();
    }
}



Info Cell::getInfo() const {
    return Info{r, c, colour};
}
