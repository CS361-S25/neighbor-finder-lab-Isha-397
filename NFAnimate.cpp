// Include necessary Empirical libraries for web animation, UI, and math utilities
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "emp/math/math.hpp"

// Create a web document that targets the HTML element with id="target"
emp::web::Document doc{"target"};

/**
 * @class NFAnimator
 * @brief Handles drawing a grid of cells, tracking user clicks, 
 *        and highlighting the neighbors of a clicked cell.
 *
 * Inherits from emp::web::Animate to enable animation and frame updates.
 */
class NFAnimator : public emp::web::Animate {
private:
    emp::web::Canvas grid_canvas{100, 100, "canvas"}; ///< Canvas to display the grid
    static constexpr int cell_size = 10;              ///< Pixel size of each individual cell
    static constexpr int num_rows = 10;               ///< Number of rows in the grid
    static constexpr int num_cols = 10;               ///< Number of columns in the grid

    int clicked_x = -1;                               ///< X-coordinate of the clicked cell (grid position)
    int clicked_y = -1;                               ///< Y-coordinate of the clicked cell (grid position)
    std::vector<std::pair<int, int>> clicked_neighbors; ///< List of neighboring cell coordinates around the clicked cell

public:
    /**
     * @brief Constructor for NFAnimator.
     * Initializes the canvas, draws the initial grid, and sets up click event handling.
     */
    NFAnimator() {
        // Attach the canvas to the document
        doc << grid_canvas;
        DrawCells();

        // Set up click behavior: detect clicked cell and update neighbors
        grid_canvas.OnClick([this](int mouse_x, int mouse_y){
            int cell_x = mouse_x / cell_size;
            int cell_y = mouse_y / cell_size;

            clicked_x = cell_x;
            clicked_y = cell_y;

            clicked_neighbors.clear();

            // Define relative positions of the 8 neighbors
            const int offset[8][2] = {
                {-1, -1}, {-1, 0}, {-1, 1},
                {0, -1},          {0, 1},
                {1, -1},  {1, 0}, {1, 1}
            };

            // Calculate wrapped neighbor positions
            for (auto [dx, dy] : offset) {
                int neighbor_x = emp::Mod(cell_x + dx, num_cols);
                int neighbor_y = emp::Mod(cell_y + dy, num_rows);
                clicked_neighbors.emplace_back(neighbor_x, neighbor_y);
            }

            Redraw();
        });
    }

    /**
     * @brief Draw the entire grid of cells on the canvas.
     * Each cell is drawn as a white square with a black border.
     */
    void DrawCells() {
        for (int row = 0; row < num_rows; ++row) {
            for (int col = 0; col < num_cols; ++col) {
                grid_canvas.Rect(
                    col * cell_size,
                    row * cell_size,
                    cell_size,
                    cell_size,
                    "white",
                    "black"
                );
            }
        }
    }

    /**
     * @brief Highlight the clicked cell and its neighbors.
     * The clicked cell is drawn in black, and its 8 neighbors are drawn in red.
     */
    void HighlightNeighbors() {
        if (clicked_x == -1 || clicked_y == -1) return; // No click yet

        // Highlight the clicked cell
        grid_canvas.Rect(
            clicked_x * cell_size,
            clicked_y * cell_size,
            cell_size,
            cell_size,
            "black",
            "black"
        );

        // Highlight each neighboring cell
        for (auto [nx, ny] : clicked_neighbors) {
            grid_canvas.Rect(
                nx * cell_size,
                ny * cell_size,
                cell_size,
                cell_size,
                "red",
                "black"
            );
        }
    }

    /**
     * @brief Redraw the entire canvas: clear the screen,
     * redraw the full grid, and highlight neighbors if applicable.
     */
    void Redraw() {
        grid_canvas.Clear();
        DrawCells();
        HighlightNeighbors();
    }

    /**
     * @brief Animate step function.
     * Called on every animation frame to redraw the canvas.
     */
    void Step() {
        Redraw();
    }
};

// Create a global instance of the animator
NFAnimator animator;

/**
 * @brief Main function.
 * Starts the animation by calling Step once.
 */
int main() {
    animator.Step();
}
