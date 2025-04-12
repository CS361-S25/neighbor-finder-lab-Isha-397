#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};


class NFAnimator : public emp::web::Animate {
    // emp::web::Canvas canvas{100, 100, "canvas"};

private: 
    emp::web::Canvas canvas{100, 100, "canvas"};
    const int cell_size = 10;
    const int rows = 10;
    const int cols = 10;

public: 
    NFAnimator(){
        doc << canvas;
        // doc << "Hi";
        // canvas.Rect(0, 0, 10, 10, "white", "black");
        DrawGrid();
        FindNeighbors(5,5);
    }

    void DrawGrid() {
        for (int x = 0; x < cols; x++) {
            for (int y = 0; y < rows; y++) {
                int x_pos = x * cell_size;
                int y_pos = y * cell_size;
                canvas.Rect(x_pos, y_pos, cell_size, cell_size, "white", "black");
                // canvas.CenterText(x_pos + 5, y_pos + 5, std::to_string(x) + "," + std::to_string(y), "black", "black");
            }
        }
    }
     void FindNeighbors(int x, int y) {
        int x_pos = x * cell_size;
        int y_pos = y * cell_size;

        // Highlight the selected cell in black
        canvas.Rect(x_pos, y_pos, cell_size, cell_size, "black", "black");

        // Directions: top, bottom, left, right, and diagonals
        const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows) {
                int nx_pos = nx * cell_size;
                int ny_pos = ny * cell_size;
                canvas.Rect(nx_pos, ny_pos, cell_size, cell_size, "red", "black");
            }
        }
    }

    // void Step() override {
    //     // For testing: highlight neighbors of cell (5, 5)
    //     FindNeighbors(5, 5);
    // }

};





NFAnimator animator;

int main() {
    animator.Step();
}