#pragma once
#include "../global.hpp"


const int TILE_SIZE = 32;
const int SCALE_FACTOR = 4;
const int GRID_WIDTH = 480*8 / TILE_SIZE;  // 15 tiles wide
const int GRID_HEIGHT = 270*8 / TILE_SIZE; // 8 tiles high


struct Tile {
    int x, y;       // Grid coordinates
    SDL_Rect rect;  // Screen position and size
    bool occupied = false;

    Tile(int gridX, int gridY, int tileSize)
            : x(gridX), y(gridY),
              rect{(gridX * tileSize)*SCALE_FACTOR, (gridY * tileSize)*SCALE_FACTOR, tileSize*SCALE_FACTOR, tileSize*SCALE_FACTOR} {}

    void updateRect(int newX, int newY, int originX, int originY, int newSize) {
        x = newX;
        y = newY;
        rect = {originX + x * newSize, originY + y * newSize, newSize, newSize}; // Update screen position with origin
    }
};
class Grid {
public:
    int tileSize = 32;
    int originX, originY; // Origin point for the grid
    std::vector<std::vector<Tile>> tiles;

    explicit Grid(int initialTileSize = 32, int startX = 0, int startY = 0)
            : tileSize(initialTileSize), originX(startX), originY(startY) {
        tiles.resize(GRID_HEIGHT, std::vector<Tile>(GRID_WIDTH, Tile(0, 0, tileSize)));
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                tiles[y][x] = Tile(x, y, tileSize);
                tiles[y][x].updateRect(x, y, tileSize, originX, originY);
            }
        }
    }

    void setOrigin(int newX, int newY) {
        originX = newX;
        originY = newY;
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                tiles[y][x].updateRect(x, y, originX, originY, tileSize);
            }
        }
    }
    SDL_Point getGridTilesXY(){
        return {GRID_WIDTH,GRID_HEIGHT};
    }

    Tile& getTile(int x, int y) {
        return tiles[y][x];
    }
    Tile& getTile(SDL_Point p) {
        return tiles[p.y][p.x];
    }
    SDL_Rect getTileRect(SDL_Point p) {
        return getTile(p).rect;
    }
    void updateTileSize(int newTileSize) {
        tileSize = newTileSize;
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                tiles[y][x].updateRect(x, y,originX,originY, newTileSize);
            }
        }
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
