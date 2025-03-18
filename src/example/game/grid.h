#pragma once
#include "../global.hpp"


const int TILE_SIZE = 32;
const int SCALE_FACTOR = 4;
const int GRID_WIDTH = 480*8 / TILE_SIZE;  // 15*8 tiles wide
const int GRID_HEIGHT = 270*8 / TILE_SIZE; // 8*8 tiles high


struct Tile {
    int x, y;       // Grid coordinates
    SDL_Rect rect;  // Screen position and size
    bool occupied = false;
    ObjectIDs object = ObjectIDs::NONE;
    CharacterIDs character = CharacterIDs::NONE;
    bool isPlayerShipTile = false;
    bool isTop = false;
    bool onGrid = false;
    int walls = 0;
    int doors = 0;
    bool hover = false;
    bool selected = false;
    bool placed = false;
    FloorTileIDs style = FloorTileIDs::NONE;


    SDL_Rect wallRect;


    Tile(int gridX, int gridY, int tileSize)
            : x(gridX), y(gridY),
              rect{(gridX * tileSize)*SCALE_FACTOR, (gridY * tileSize)*SCALE_FACTOR, tileSize*SCALE_FACTOR, tileSize*SCALE_FACTOR},
              wallRect{(gridX * tileSize)*SCALE_FACTOR, (gridY * tileSize)*SCALE_FACTOR, tileSize*SCALE_FACTOR, tileSize*SCALE_FACTOR}{}

    void updateRect(int newX, int newY, int originX, int originY, int newSize) {
        x = newX;
        y = newY;
        rect = {originX + x * newSize, originY + y * newSize, newSize, newSize}; // Update screen position with origin
        wallRect = {originX + x * newSize, originY + y * newSize, newSize, newSize};
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
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                if(tiles[y][x].rect.x >= 0 && tiles[y][x].rect.x <= WINDOWSIZE_X
                && tiles[y][x].rect.y >= -32 && tiles[y][x].rect.y <= WINDOWSIZE_Y) {
                    if(x > 89){
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    }else{SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);}

                    SDL_RenderDrawRect(renderer, &tiles[y][x].rect);

                  //  SDL_RenderDrawRect(renderer, &tiles[y][x].wallUp);
                }
            }
        }
    }
    void hover(SDL_Renderer* renderer) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                if(tiles[y][x].rect.x >= 0 && tiles[y][x].rect.x <= WINDOWSIZE_X
                   && tiles[y][x].rect.y >= -32 && tiles[y][x].rect.y <= WINDOWSIZE_Y) {
                    if(tiles[y][x].hover){
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                        SDL_RenderDrawRect(renderer, &tiles[y][x].rect);
                    }
                    if(tiles[y][x].selected){
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        SDL_RenderDrawRect(renderer, &tiles[y][x].rect);
                    }
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                    //  SDL_RenderDrawRect(renderer, &tiles[y][x].wallUp);
                }
            }
        }
    }
};
