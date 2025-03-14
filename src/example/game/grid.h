#pragma once
#include "../global.hpp"


const int TILE_SIZE = 32;
const int SCALED_TILE = TILE_SIZE*4;
const int GRID_WIDTH = 480 / TILE_SIZE;  // 15 tiles wide
const int GRID_HEIGHT = 270 / TILE_SIZE; // 8 tiles high
const int SCALED_WIDTH = GRID_WIDTH*4;
const int SCALED_HEIGHT = GRID_HEIGHT*4;

struct Tile {
    int x, y;       // Grid coordinates
    SDL_Rect rect;  // Screen position and size
    bool occupied = false;

    Tile(int gridX, int gridY)
            : x(gridX), y(gridY),
              rect{gridX * SCALED_TILE, gridY * SCALED_TILE, SCALED_TILE, SCALED_TILE} {}
};
class Grid {
public:
    std::vector<std::vector<Tile>> tiles;

    Grid() {
        tiles.resize(GRID_HEIGHT, std::vector<Tile>(GRID_WIDTH, Tile(0, 0)));

        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                tiles[y][x] = Tile(x, y);  // Assign correct coordinates
            }
        }
    }

    Tile& getTile(int x, int y) {
        return tiles[y][x];
    }

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                SDL_RenderDrawRect(renderer, &tiles[y][x].rect);
            }
        }
    }
};
