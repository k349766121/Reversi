#include <iostream>
#include <string>
#include <vector>
#include "grid.h"
#include "state.h"
#include "crow.h"
#include "crow/middlewares/cors.h"
using namespace std;

// the front end need a 1D array. Convect to meet the frontend
std::vector<char> convectTo1D(std::vector<std::vector<char>> vec){
  const int n = vec.size();
  std::vector<char> newVec;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      newVec.push_back(vec[i][j]);
    }
  }
  return newVec;
}
int main(int argc, char *argv[]) {
  static Grid g;
  static bool black = true;
  crow::App<crow::CORSHandler> app; 

  CROW_ROUTE(app, "/new/<int>/<int>").methods(crow::HTTPMethod::PUT, crow::HTTPMethod::OPTIONS)
  ([](const crow::request& req, crow::response& res, int n, int dummy) { 
    if (req.method == crow::HTTPMethod::OPTIONS) {
        // Handle preflight request
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "PUT, GET, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.code = 204; // No Content
        res.end();
        return;
    }

    try {
        // Initialize game
        black = true;
        g.init(n);
        g.setPiece(n / 2 - 1, n / 2 - 1, Colour::Black);
        g.setPiece(n / 2 - 1, n / 2, Colour::White);
        g.setPiece(n / 2, n / 2, Colour::Black);
        g.setPiece(n / 2, n / 2 - 1, Colour::White);

        // Prepare JSON response
        crow::json::wvalue result;
        result["result"] = "NA";
        result["display"] = convectTo1D(g.showDisplay());

        // Add CORS Headers
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "PUT, GET, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.code = 200; // Success
        res.write(result.dump());
    } catch (const std::exception& e) {
        // Handle errors
        res.code = 500; // Internal Server Error
        res.write("Error: " + std::string(e.what()));
    }
    res.end();
  });

  CROW_ROUTE(app, "/play/<int>/<int>").methods(crow::HTTPMethod::OPTIONS, crow::HTTPMethod::PUT)
  ([](const crow::request& req, crow::response& res, int r, int c) {
    // Handle preflight (OPTIONS)
    if (req.method == crow::HTTPMethod::OPTIONS) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "OPTIONS, PUT, GET, POST");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        // Typically return 204 for an empty preflight response
        res.code = 204;
        res.end();
        return;
    }
    crow::json::wvalue result;
    try{
      if (black){
        g.setPiece(r,c, Colour::Black);
        
      } else {
        g.setPiece(r,c, Colour::White);
      }
      black = !black;
      result["result"] = "NA";
      result["display"] = convectTo1D(g.showDisplay());
    } catch (const InvalidMove& e) {
      result["result"] = "NA";
      result["display"] = convectTo1D(g.showDisplay());
      res.end();
      return;
    } catch (Colour &c) {
      result["display"] = convectTo1D(g.showDisplay());
      if (c == Colour::Black){
        result["result"] = "Blue wins!";
      } else if (c == Colour::White){
        result["result"] = "Red wins!";
      } else if (c == Colour::NoColour){
        result["result"] = "Tie!";
      }
    }
    // Include CORS header
    res = crow::response(result);
    res.add_header("Access-Control-Allow-Origin", "*");
    res.end();
  });

  app.port(18080).multithreaded().run();
}

