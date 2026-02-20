/*
 * Design Snake Game
 * 
 * Design a Snake game that is played on a device with screen size height x width. Play the game online if you are not familiar with the game.
 * 
 * The snake is initially positioned at the top left corner (0, 0) with a length of 1 unit.
 * You are given an array food where food[i] = (ri, ci) is the row and column position of a piece of food that the snake can eat. When a snake eats a piece of food, its length and the game's score both increase by 1.
 * Each piece of food appears one by one on the screen. For example, the second piece of food will not appear until the first piece of food was eaten by the snake.
 * 
 * If a piece of food appears on top of the snake, the game is over.
 * 
 * Design a SnakeGame class:
 * 
 * SnakeGame(int width, int height, int[][] food) Initializes the object with a screen of size height x width and the positions of the food.
 * int move(String direction) Returns the score of the game after applying one direction move by the snake. If the game is over, return -1.
 * 
 * Example 1:
 * Input
 * ["SnakeGame", "move", "move", "move", "move", "move", "move"]
 * [[3, 2, [[1, 2], [0, 1]]], ["R"], ["D"], ["R"], ["U"], ["L"], ["U"]]
 * Output
 * [null, 0, 0, 1, 1, 2, -1]
 * 
 * Explanation
 * SnakeGame snakeGame = new SnakeGame(3, 2, [[1, 2], [0, 1]]);
 * snakeGame.move("R"); // return 0
 * snakeGame.move("D"); // return 0
 * snakeGame.move("R"); // return 1, snake eats the first piece of food. The second piece of food appears at (0, 1).
 * snakeGame.move("U"); // return 1
 * snakeGame.move("L"); // return 2, snake eats the second food. No more food appears.
 * snakeGame.move("U"); // return -1, game over because snake collides with border
 * 
 */
#include <vector>
#include <deque>
#include <unordered_set>
#include <string>

using namespace std;

class SnakeGame {
private:
    int width, height;
    vector<pair<int, int>> foodList;
    int foodIdx;
    deque<pair<int, int>> snake;
    unordered_set<int> body;   // key = row * width + col
    int score;

public:
    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height 
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second at [1,0]. */
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        this->width = width;
        this->height = height;
        for (auto& f : food) {
            foodList.emplace_back(f[0], f[1]);
        }
        foodIdx = 0;
        snake.push_back({0, 0});
        body.insert(0);  // (0,0) -> key = 0*width + 0 = 0
        score = 0;
    }
    
    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
        @return The game's score after the move. Return -1 if game over.
        Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {
        // Get current head position
        auto [headRow, headCol] = snake.front();
        int newRow = headRow, newCol = headCol;

        // Compute new head
        if (direction == "U") newRow--;
        else if (direction == "D") newRow++;
        else if (direction == "L") newCol--;
        else if (direction == "R") newCol++;
        else return -1; // invalid direction, but problem guarantees valid input

        // Check boundary collision
        if (newRow < 0 || newRow >= height || newCol < 0 || newCol >= width) {
            return -1;
        }

        // Determine if next food is at the new head
        bool eat = false;
        if (foodIdx < foodList.size() && foodList[foodIdx].first == newRow && foodList[foodIdx].second == newCol) {
            eat = true;
        }

        if (eat) {
            // Check if new head collides with current body (including tail)
            int newKey = newRow * width + newCol;
            if (body.count(newKey)) {
                return -1; // collided with itself
            }
            // Add new head
            snake.push_front({newRow, newCol});
            body.insert(newKey);
            // Consume food
            foodIdx++;
            score++;
            // Tail remains, so body already contains old head and tail
        } else {
            // Remove tail first
            auto [tailRow, tailCol] = snake.back();
            int tailKey = tailRow * width + tailCol;
            body.erase(tailKey);
            snake.pop_back();

            // Now check if new head collides with remaining body
            int newKey = newRow * width + newCol;
            if (body.count(newKey)) {
                return -1;
            }
            // Add new head
            snake.push_front({newRow, newCol});
            body.insert(newKey);
        }

        return score;
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */