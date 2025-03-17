#include "example_game.hpp"

#include <hsnr64/offset.hpp>
#include <hsnr64/palette.hpp>
//#include <tilefont.h>

namespace JanSordid::SDL_Example
{




    void STR_State::Init()
    {
        using std::string;
        Base::Init();

        if (!_font) {
            _font = TTF_OpenFont(BasePath "asset/font/RobotoSlab-Bold.ttf", (int) (fontsize));
            //_font = TTF_OpenFont(BasePath "/src/example/game/Ressources/fonts/KJV1611.otf", (int) (12.0f * _game.scalingFactor()));
            //_font = TTF_OpenFont(BasePath "/src/example/game/Ressources/fonts/IMFeENrm29P.ttf", (int) (fontsize ));
            /// fontsize is used for all text in the game so far
            ///maybe use another _fontBIG for bigger text where needed instead of changing fontsize locally

            TTF_SetFontHinting(_font, TTF_HINTING_LIGHT);
            if (!_font)
                print(stderr, "TTF_OpenFont failed: {}\n", TTF_GetError());
        }

        //texture strings
        //Player Character
        string playerIdlePath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Idol.png";
        string playerIdleFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Idol_Flip.png";
        string playerWalkPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Walk_Cycle.png";
        string playerWalkFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Walk_Cycle_Flip.png";
        string playerDamagePath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Player_Damage-Sheet.png";
        string playerDamageFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Player_Damage_flip-Sheet.png";
        string playerDamageKnockdownPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Player_Damage_Knockout-Sheet.png";
        string playerDamageKnockdownFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Player_Damage_Knockout_flip-Sheet.png";
        string playerKnockdownGetupPath = BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Player_Knockout_JumpUp-Sheet.png";
        string playerKnockdownGetupFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Player_Knockout_JumpUp_Flip-Sheet.png";
        //tiles
        string tileTestingPath = BasePath "/src/example/game/Ressources/Image_assets/tiles/Tiles/Tiles.png";
        string tileStandardPath = BasePath"/src/example/game/Ressources/Image_assets/tiles/Standard_Floor_Tile-Sheet.png";
        string tileCirclePath = BasePath"/src/example/game/Ressources/Image_assets/tiles/Circle-Sheet.png";
        string tileWallsPath = BasePath"/src/example/game/Ressources/Image_assets/tiles/Walls.png";
        string tileDoorsPath = BasePath"/src/example/game/Ressources/Image_assets/tiles/Walls_Blue-Sheet.png";
        //objects
        string objectShotPath = BasePath "/src/example/game/Ressources/Image_assets/items/Shoot-Sheet.png";



        //load textures
        //player
    playerIdleSheet = loadFromFile(playerIdlePath);
    playerIdleSheetFlip = loadFromFile(playerIdleFlipPath);
    playerWalkSheet = loadFromFile(playerWalkPath);
    playerWalkSheetFlip = loadFromFile(playerWalkFlipPath);
    playerDamageSheet = loadFromFile(playerDamagePath);
    playerDamageSheetFlip = loadFromFile(playerDamageFlipPath);
    playerDamageKnockdownSheet = loadFromFile(playerDamageKnockdownPath);
    playerDamageKnockdownSheetFlip = loadFromFile(playerDamageKnockdownFlipPath);
    playerGetUpSheet = loadFromFile(playerKnockdownGetupPath);
    playerGetUpSheetFlip = loadFromFile(playerKnockdownGetupFlipPath);
    //tiles
    tileTest = loadFromFile(tileTestingPath);
    tileStandard = loadFromFile(tileStandardPath);
    tileCircle = loadFromFile(tileCirclePath);
    tilesWalls = loadFromFile(tileWallsPath);
    tilesDoors = loadFromFile(tileDoorsPath);
    //items
    objectShot = loadFromFile(objectShotPath);

    floorTiles.push_back(tileStandard);
    floorTiles.push_back(tileCircle);
    objectSprites.push_back(objectShot);

    playerAnimation = playerIdleSheet;
    grid.updateTileSize(scale);

        mode = Mode::TilePlacer;

/*
        for(int i = 0; i<17;i++){
            clips32.push_back({i*32,0*32,32,32});
        }
        */
        for(int j = 0; j<3;j++) {
            for (int i = 0; i < 17; i++) {
                clips32.push_back({i * 32, j * 32, 32, 32});
            }
        }
        for(int j = 0; j<3;j++) {
            for (int i = 0; i < 17; i++) {
                clips32x4.push_back({i * 32, j * 32, 32, 4});
            }
        }


        if(mode == Mode::Game) {


            gridStartingPoint.x = -(scale * grid.getGridTilesXY().x / 2);
            gridStartingPoint.y = -(scale * grid.getGridTilesXY().y / 2);
            grid.setOrigin(gridStartingPoint.x, gridStartingPoint.y);

            target = grid.getTile(62, 36).rect;


            for (int j = 0; j < 9; j++) {
                for (int i = 0; i < 9; i++) {
                    grid.getTile(62 + i, 36 + j).style = FloorTileStyles::Standard;
                    grid.getTile(62 + i, 36 + j).isTop = true;
                    grid.getTile(62 + i, 36 + j).walls = 1;
                }
            }

            grid.getTile(62, 36).style = FloorTileStyles::Standard;
            grid.getTile(63, 36).style = FloorTileStyles::Standard;
            grid.getTile(64, 36).style = FloorTileStyles::Standard;
            grid.getTile(62, 36).isTop = true;
            grid.getTile(63, 36).isTop = true;
            grid.getTile(64, 36).isTop = true;


            grid.getTile(62, 37).isTop = true;
            grid.getTile(62, 37).style = FloorTileStyles::Standard;



            aManager.addTarget(
                    {target, {62, 36}, 0, EntityType::EnemyType1, EntityAnimations::Aim, EntityAnimations::Fire});

            // pChar.rect = grid.getTile(60,40).rect;
            pChar.updatePosition({60+59, 34+31}, grid.getTile(60+59, 34+31).rect);
        }
        if(mode == Mode::TilePlacer){
            gridStartingPoint.x = 0;
            gridStartingPoint.y = 0;
            grid.setOrigin(gridStartingPoint.x, gridStartingPoint.y);
            startingScale = scale;

        }
    }

    void STR_State::Enter( bool stacking )
    {
        Base::Enter( stacking );

        if( Mix_GetMusicPosition( _music ) <= 0.001 )
            Mix_PlayMusic( _music, -1 );
        else if( Mix_PausedMusic() )
            Mix_ResumeMusic();
    }

    void STR_State::Exit( bool stacking )
    {
        if( !Mix_PausedMusic() )
            Mix_PauseMusic();

        Base::Exit( stacking );
    }

    void STR_State::Destroy()
    {
        // Keep everything loaded/allocated is also an option
        /*
        TTF_CloseFont( font );
        SDL_DestroyTexture( image );
        SDL_DestroyTexture( _blendedText );
        font = nullptr;
        image = nullptr;
        _blendedText = nullptr;
        */
        //destroy all textures
        SDL_DestroyTexture(playerIdleSheet);
        SDL_DestroyTexture(playerIdleSheetFlip);
        SDL_DestroyTexture(playerWalkSheet);
        SDL_DestroyTexture(playerWalkSheetFlip);
        SDL_DestroyTexture(playerDamageSheet);
        SDL_DestroyTexture(playerDamageSheetFlip);
        SDL_DestroyTexture(playerDamageKnockdownSheet);
        SDL_DestroyTexture(playerDamageKnockdownSheetFlip);
        SDL_DestroyTexture(playerGetUpSheet);
        SDL_DestroyTexture(playerGetUpSheetFlip);
        SDL_DestroyTexture(tileTest);
        SDL_DestroyTexture(tileStandard);
        SDL_DestroyTexture(tileCircle);
        SDL_DestroyTexture(tilesWalls);
        SDL_DestroyTexture(tilesDoors);
        SDL_DestroyTexture(objectShot);

        playerIdleSheet = nullptr;
        playerIdleSheetFlip = nullptr;
        playerWalkSheet = nullptr;
        playerWalkSheetFlip = nullptr;
        playerDamageSheet = nullptr;
        playerDamageSheetFlip = nullptr;
        playerDamageKnockdownSheet = nullptr;
        playerDamageKnockdownSheetFlip = nullptr;
        playerGetUpSheet = nullptr;
        playerGetUpSheetFlip= nullptr;
        tileTest = nullptr;
        tileStandard = nullptr;
        tileCircle = nullptr;
        tilesWalls = nullptr;
        tilesDoors = nullptr;
        objectShot = nullptr;

        Base::Destroy();
    }

    bool STR_State::HandleEvent( const Event & event ) {

        mouseState = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if (mode == Mode::Game) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    const Keysym &what_key = event.key.keysym;

                    if (what_key.scancode == SDL_SCANCODE_G && event.key.repeat == 0) {
                        if (showGrid) { showGrid = false; } else { showGrid = true; }
                    } else if (what_key.scancode == SDL_SCANCODE_P && event.key.repeat == 0) {
                        playerSwitchedState = true;
                        count++;
                        if (count >= 12) { count = 0; }
                        tileswitch++;
                        if (tileswitch >= 17) { tileswitch = 0; }

                    } else if (what_key.scancode == SDL_SCANCODE_KP_PLUS && event.key.repeat == 0) {

                        ZoomIn();

                    } else if (what_key.scancode == SDL_SCANCODE_KP_MINUS && event.key.repeat == 0) {
                        ZoomOut();
                    } else if (what_key.scancode == SDL_SCANCODE_RIGHT && event.key.repeat == 0) {
                        CameraMoveBy1Tile(Directions::RIGHT);

                    } else if (what_key.scancode == SDL_SCANCODE_LEFT && event.key.repeat == 0) {
                        CameraMoveBy1Tile(Directions::LEFT);

                    } else if (what_key.scancode == SDL_SCANCODE_UP && event.key.repeat == 0) {
                        CameraMoveBy1Tile(Directions::UP);
                    } else if (what_key.scancode == SDL_SCANCODE_DOWN && event.key.repeat == 0) {
                        CameraMoveBy1Tile(Directions::DOWN);
                    } else {
                        return false; // Not handled
                    }

                    return true; // Confusing control flow: Handled by all but the else case

                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                    //game.SetNextState( 1 );
                    break;

                default:
                    break;
            }

            return false;
        }
        if(mode == Mode::TilePlacer){

            switch (event.type) {
                case SDL_KEYDOWN: {
                    const Keysym &what_key = event.key.keysym;

                    if (what_key.scancode == SDL_SCANCODE_G && event.key.repeat == 0) {

                        if (showGrid) { showGrid = false; } else { showGrid = true; }

                    }
                    else if (what_key.scancode == SDL_SCANCODE_Y && event.key.repeat == 0) {

                        if (tTracker.manageWallsMode  ) { tTracker.manageWallsMode = false; tTracker.manageDoorsMode = true;
                        }
                        else { tTracker.manageWallsMode = true;tTracker.manageDoorsMode = false; }
                    }
                    else if (what_key.scancode == SDL_SCANCODE_U && event.key.repeat == 0) {

                        if (tTracker.manageDoorsMode ) { tTracker.manageDoorsMode = false;tTracker.manageWallsMode = true;
                        }
                        else { tTracker.manageDoorsMode = true; tTracker.manageWallsMode = false;}
                    }
                    else if (what_key.scancode == SDL_SCANCODE_O && event.key.repeat == 0) {

                        if (tTracker.placeObjectMode ) { tTracker.placeObjectMode = false;tTracker.placeTileMode = true;
                        }
                        else { tTracker.placeObjectMode = true; tTracker.placeTileMode = false;
                            tTracker.manageWallsMode = false;tTracker.manageDoorsMode = false;
                            tTracker.ResetWallDoorPlacer(); }
                    }
                    else if (what_key.scancode == SDL_SCANCODE_W && event.key.repeat == 0) {
                        if(tTracker.manageWallsMode ) {
                            if (tTracker.wallUpAdded) {
                                tTracker.selectedWalls= tTracker.selectedWalls - 1;
                                tTracker.wallUpAdded = false;
                            } else {
                                tTracker.selectedWalls= tTracker.selectedWalls + 1;
                                tTracker.wallUpAdded = true;
                                if (tTracker.doorUpAdded) {
                                    tTracker.selectedDoors = tTracker.selectedDoors - 1;
                                    tTracker.doorUpAdded = false;
                                }
                            }
                        }
                        if(tTracker.manageDoorsMode) {
                            if (tTracker.doorUpAdded) {
                                tTracker.selectedDoors= tTracker.selectedDoors - 1;
                                tTracker.doorUpAdded = false;
                            } else {
                                tTracker.selectedDoors= tTracker.selectedDoors + 1;
                                tTracker.doorUpAdded = true;
                                if (tTracker.wallUpAdded) {
                                    tTracker.selectedWalls= tTracker.selectedWalls - 1;
                                    tTracker.wallUpAdded = false;
                                }
                            }
                        }
                    }
                    else if (what_key.scancode == SDL_SCANCODE_D && event.key.repeat == 0) {
                        if(tTracker.manageWallsMode                       ) {
                            if (tTracker.wallRightAdded) {
                                tTracker.selectedWalls= tTracker.selectedWalls - 2;
                                tTracker.wallRightAdded= false;
                            } else {
                                tTracker.selectedWalls= tTracker.selectedWalls + 2;
                                tTracker.wallRightAdded= true;
                                if (tTracker.doorRightAdded) {
                                    tTracker.selectedDoors= tTracker.selectedDoors - 2;
                                    tTracker.doorRightAdded= false;
                                }
                            }
                        }

                        if(tTracker.manageDoorsMode) {
                            if (tTracker.doorRightAdded) {
                                tTracker.selectedDoors= tTracker.selectedDoors - 2;
                                tTracker.doorRightAdded= false;
                            } else {
                                tTracker.selectedDoors= tTracker.selectedDoors + 2;
                                tTracker.doorRightAdded= true;
                                if (tTracker.wallRightAdded) {
                                    tTracker.selectedWalls= tTracker.selectedWalls - 2;
                                    tTracker.wallRightAdded= false;
                                }
                            }
                        }

                    }
                    else if (what_key.scancode == SDL_SCANCODE_S && event.key.repeat == 0) {
                        if(tTracker.manageWallsMode                       ) {
                            if (tTracker.wallDownAdded) {
                                tTracker.selectedWalls= tTracker.selectedWalls - 4;
                                tTracker.wallDownAdded = false;
                            } else {
                                tTracker.selectedWalls= tTracker.selectedWalls + 4;
                                tTracker.wallDownAdded = true;
                                if (tTracker.doorDownAdded) {
                                    tTracker.selectedDoors= tTracker.selectedDoors - 4;
                                    tTracker.doorDownAdded = false;
                                }
                            }
                        }

                        if(tTracker.manageDoorsMode) {
                            if (tTracker.doorDownAdded) {
                                tTracker.selectedDoors= tTracker.selectedDoors - 4;
                                tTracker.doorDownAdded = false;
                            } else {
                                tTracker.selectedDoors= tTracker.selectedDoors + 4;
                                tTracker.doorDownAdded = true;
                                if (tTracker.wallDownAdded) {
                                    tTracker.selectedWalls= tTracker.selectedWalls - 4;
                                    tTracker.wallDownAdded = false;
                                }
                            }
                        }
                    }
                    else if (what_key.scancode == SDL_SCANCODE_A && event.key.repeat == 0) {
                        if (tTracker.manageWallsMode) {
                            if (tTracker.wallLeftAdded) {
                                tTracker.selectedWalls = tTracker.selectedWalls - 8;
                                tTracker.wallLeftAdded = false;
                            } else {
                                tTracker.selectedWalls = tTracker.selectedWalls + 8;
                                tTracker.wallLeftAdded = true;
                                if (tTracker.doorLeftAdded) {
                                    tTracker.selectedDoors = tTracker.selectedDoors - 8;
                                    tTracker.doorLeftAdded = false;
                                }
                            }
                        }
                        if (tTracker.manageDoorsMode) {
                            if (tTracker.doorLeftAdded) {
                                tTracker.selectedDoors = tTracker.selectedDoors - 8;
                                tTracker.doorLeftAdded = false;
                            } else {
                                tTracker.selectedDoors = tTracker.selectedDoors + 8;
                                tTracker.doorLeftAdded = true;
                                    if (tTracker.wallLeftAdded) {
                                        tTracker.selectedWalls = tTracker.selectedWalls - 8;
                                        tTracker.wallLeftAdded = false;
                                    }

                            }
                        }
                    }
                    else if (what_key.scancode == SDL_SCANCODE_RETURN && event.key.repeat == 0) {
                        tTracker.confirm = true;
                    }
                    else if (what_key.scancode == SDL_SCANCODE_KP_PLUS && event.key.repeat == 0) {

                        ZoomIn();

                    }
                    else if (what_key.scancode == SDL_SCANCODE_KP_MINUS && event.key.repeat == 0) {
                        if(scale != startingScale) {
                            ZoomOut();
                        }
                    }
                    else if (what_key.scancode == SDL_SCANCODE_T && event.key.repeat == 0) {
                        if(tTracker.placeTileMode){
                            tTracker.placeTileMode = false;
                        }else{tTracker.placeTileMode = true;}

                    }
                    else if (what_key.scancode == SDL_SCANCODE_RIGHT && event.key.repeat == 0) {
                        CameraMoveBy1Tile(Directions::RIGHT);
                    }
                    else if (what_key.scancode == SDL_SCANCODE_LEFT && event.key.repeat == 0) {
                        CameraMoveBy1Tile(Directions::LEFT);

                    }
                    else if (what_key.scancode == SDL_SCANCODE_UP && event.key.repeat == 0) {
                        CameraMoveBy1Tile(Directions::UP);
                    }
                    else if (what_key.scancode == SDL_SCANCODE_DOWN && event.key.repeat == 0) {
                        CameraMoveBy1Tile(Directions::DOWN);
                    }
                    else {
                        return false; // Not handled
                    }

                    return true; // Confusing control flow: Handled by all but the else case

                    break;
                }

                case SDL_MOUSEMOTION:
                        SDL_Point  temp;
                        temp = mousePosition;
                        for (auto& a: grid.tiles) {
                            for (auto &b: a) {
                                if (SDL_PointInRect(&temp,&b.rect)){
                                    b.hover = true;
                                }else{ b.hover = false;}
                            }
                        }
                        break;
                case SDL_MOUSEBUTTONDOWN:

                    if(tTracker.placeTileMode) {
                        if (event.button.button == (SDL_BUTTON_LEFT)) {
                             temp = mousePosition;
                            for (auto &a: grid.tiles) {
                                for (auto &b: a) {
                                    b.selected = false;
                                    if (SDL_PointInRect(&temp, &b.rect)) {
                                        b.selected = true;
                                        tTracker.currentFloorSprite = b.style;

                                    }
                                }
                            }
                        }
                    }
                    if(tTracker.placeObjectMode) {
                        if (event.button.button == (SDL_BUTTON_LEFT)) {
                            SDL_Point temp = mousePosition;
                            for (auto &a: grid.tiles) {
                                for (auto &b: a) {
                                    b.selected = false;
                                    if (SDL_PointInRect(&temp, &b.rect)) {
                                        b.selected = true;
                                        tTracker.currentObject = b.object;

                                    }
                                }
                            }
                        }
                        if (event.button.button == (SDL_BUTTON_RIGHT)) {
                            SDL_Point temp = mousePosition;
                            for (auto &a: grid.tiles) {
                                for (auto &b: a) {
                                    b.placed = false;
                                    if (SDL_PointInRect(&temp, &b.rect)) {
                                        //last placed tile set to true
                                        b.placed = true;
                                        //update the tiles object
                                        ///TODO objets in space need to be allowed later
                                        if(b.onGrid) {
                                            b.object = tTracker.currentObject;
                                            b.occupied = true;
                                        }

                                    }
                                }
                            }
                        }
                    }
                    if (event.button.button == (SDL_BUTTON_RIGHT)) {
                        if (!tTracker.placeObjectMode) {
                            SDL_Point temp = mousePosition;
                            for (auto &a: grid.tiles) {
                                for (auto &b: a) {
                                    b.placed = false;
                                    if (SDL_PointInRect(&temp, &b.rect)) {
                                        //last placed tile set to true
                                        b.placed = true;
                                        //update the tiles style
                                        b.style = tTracker.currentFloorSprite;
                                        //if NONE selected remove from grid
                                        if (tTracker.currentFloorSprite == FloorTileStyles::NONE) {
                                            b.onGrid = false;
                                            b.object = Objects::NONE;
                                        } else { b.onGrid = true; }

                                        //if not in wall/door mode only replace style of tile
                                        if (tTracker.manageDoorsMode || tTracker.manageWallsMode) {
                                            b.doors = tTracker.selectedDoors;
                                            b.walls = tTracker.selectedWalls;
                                        }

                                    }
                                }
                            }
                        }
                    }break;

                default:
                    break;
            }

            return false;
        }
        return false;
    }

    void STR_State::Update( const u64 frame, const u64 totalMSec, const f32 deltaT ) {

        if (mode == Mode::Game) {


            if (playerSwitchedState) {
                //if animation finished or playerCharacter in idle go to next animation
                if (animationFrame >= 7 || pChar.state == PlayerState::Idle || pChar.state == PlayerState::Idle_Flip) {
                    SwitchPlayerAnimation(static_cast<PlayerState>(count));
                    playerSwitchedState = false;
                    startAnim = 0;
                    phase = 0;
                    animationFrame = 0;

                }
            }
            if (pChar.state == PlayerState::Walk) {
                pChar.rect.x = pChar.rect.x + 4;

            }


            for (auto &a: grid.tiles) {
                for (auto &b: a) {
                    if (b.style != FloorTileStyles::NONE && b.walls == 1) {
                        if (grid.tiles[b.y + 1][b.x].isTop && grid.tiles[b.y + 1][b.x].walls == 1) {
                            grid.tiles[b.y + 1][b.x].isTop = false;
                            b.isTop = true;
                        }
                    }
                }
            }
        }


        if (mode == Mode::TilePlacer) {
            if (tTracker.placeTileMode) {
                int j = 0; // next y pos
                for (auto a: floorTiles) {
                    grid.tiles[j][0].style = static_cast<FloorTileStyles>(j + 1);
                    j++;
                }

            }
            if (tTracker.placeObjectMode) {
                int j = 0; // next y pos
                for (auto a: objectSprites) {
                    grid.tiles[j][0].object = static_cast<Objects>(j + 1);
                    j++;
                }

            }

            //finish selecting modes
            if (tTracker.confirm) {
                tTracker.confirm = false;
                tTracker.manageDoorsMode = false;
                tTracker.manageWallsMode = false;
                tTracker.ResetWallDoorPlacer();
            }
        }
    }

    void STR_State::Render( const u64 frame, const u64 totalMSec, const f32 deltaTNeeded )
    {
        Point windowSize;
        SDL_GetWindowSize( window(), &windowSize.x, &windowSize.y );

        SDL_SetRenderDrawColor(renderer(), 50, 50, 50, 255);

        SDL_RenderClear(renderer());
        if(mode == Mode::TilePlacer) {

            if(tTracker.manageWallsMode           ){
                SDL_SetRenderDrawColor(renderer(), 255, 0, 0, 255);
                SDL_RenderClear(renderer());
                Texture * t = textToTexture("WALL SELECT MODE\n Activate Wall placement with WASD \n Press U to Switch to DOOR Select \n CONFIRM to go back to tile only mode");
                renderText(grid.tiles[0][4].rect,t );
                SDL_DestroyTexture(t);
                t = nullptr;

            }
            if(tTracker.manageDoorsMode){
                SDL_SetRenderDrawColor(renderer(), 0, 255, 0, 255);
                SDL_RenderClear(renderer());
                Texture * t = textToTexture("DOOR SELECT MODE\n Activate DOOR placement with WASD \n Press U to Switch to WALL Select \n CONFIRM to go back to tile only mode");
                renderText(grid.tiles[0][4].rect,t );
                SDL_DestroyTexture(t);
                t = nullptr;
            }
            if(tTracker.placeObjectMode){
                SDL_SetRenderDrawColor(renderer(), 100, 100, 150, 255);
                SDL_RenderClear(renderer());
                Texture * t = textToTexture("OBJECT SELECT MODE\n  Press O to Return to Tile Placer Mode \n Leftclick to Select Rightclickt to place \n");
                renderText(grid.tiles[0][4].rect,t );
                SDL_DestroyTexture(t);
                t = nullptr;
            }
            if (showGrid) {
                grid.render(renderer());
            }

            if (tTracker.placeTileMode) {
                int j = 0; // next y pos
                for (auto a: floorTiles) {
                    for (int i = 0; i < 1; i++) {
                        renderFromSpritesheet(grid.tiles[j][i].rect, a, &clips32[i]);
                    }
                    j++;
                }
            }
            if (tTracker.placeObjectMode) {
                int j = 0; // next y pos
                for (auto a: objectSprites) {
                    for (int i = 0; i < 1; i++) {
                        renderFromSpritesheet(grid.tiles[j][i].rect, a, &clips32[1]);
                    }
                    j++;
                }
            }
                grid.hover(renderer());


            for (auto a: grid.tiles) {
                for (auto b: a) {
                    if (b.style != FloorTileStyles::NONE && b.onGrid) {
                        RenderFloorTile(b.style, b.rect);
                        RenderWalls(b.rect,b.walls);
                        RenderDoors(b.rect,b.doors);
                        RenderObjectSprites(b.object,b.rect);
                    }
                }
            }

            SDL_Rect selectionVisualizer = {mousePosition.x, mousePosition.y, 64, 64};

            renderFromSpritesheet(selectionVisualizer, tilesDoors, &clips32[tTracker.selectedDoors]);
            renderFromSpritesheet(selectionVisualizer, tilesWalls, &clips32[tTracker.selectedWalls]);

            selectionVisualizer.x = selectionVisualizer.x + 64;
            if(!tTracker.placeObjectMode) {
                RenderFloorTile(tTracker.currentFloorSprite, selectionVisualizer);
            }else{
                RenderObjectSprites(tTracker.currentObject, selectionVisualizer);
            }


        }
        if(mode == Mode::Game) {


            for (auto a: grid.tiles) {
                for (auto b: a) {
                    if (b.style != FloorTileStyles::NONE) {
                        renderFromSpritesheet(b.rect, tileStandard, &clips32[tileswitch]);
                    }
                    if (b.isTop && b.walls == 1) {
                        renderFromSpritesheet(grid.tiles[b.y - 1][b.x].rect, tileTest, &clips32[4]);
                    }
                    if (b.walls == 1) {
                        // renderFromSpritesheet(b.wallUp,tileTest,&clips32x4[1]);
                    }

                }
            }
            if (showGrid) {
                grid.render(renderer());
            }


            RenderPlayer();

            AnimateTargets();
        }
    }

    void STR_State::RenderPlayer(){


                if(pChar.state == PlayerState::Grounded || pChar.state == PlayerState::Grounded_Flip) {

                    renderFromSpritesheet(pChar.rect, playerAnimation, &clips32[7]);
                    animationFrame = 7;

                }else{


                    animationFrame = RenderPlayerAnimation(pChar.rect, playerAnimation, clips32);

                }


    }
//Version using a SDL_Rect to pull values from. Added for utility and because everything should have a Rect
    void STR_State::renderFromSpritesheet(Rect values, SDL_Texture *t, SDL_Rect *clip, double angle, SDL_Point *center,
                                               SDL_RendererFlip flip, bool useClipSize) {
        SDL_Rect renderQuad = {values.x, values.y, values.w, values.h};

        if (clip != nullptr && useClipSize) {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        SDL_RenderCopyEx(renderer(), t, clip, &renderQuad, angle, center, flip);
    }

//result should be saved in a texture related to a object within MortalFlawState.
// Surface Width/Height should match playerCharacter width/height otherwise texture needs to be scaled.
    Texture *STR_State::loadFromFile(const std::string &path) {

        Texture *newTexture = nullptr;
        Surface *loadedSurface = IMG_Load(path.c_str());

        if (loadedSurface == nullptr) {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        } else {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

            newTexture = SDL_CreateTextureFromSurface(renderer(), loadedSurface);
            if (!newTexture) {
                printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            }

            SDL_FreeSurface(loadedSurface);
        }

        return newTexture;
    }

//outputs a texture of the input text. Should be saved in a texture *
    Texture *STR_State::textToTexture(const char *text) {

        Point windowSize;
        SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);

        Texture *newTexture = nullptr;

        Surface *surf = TTF_RenderUTF8_Blended_Wrapped(_font, text, white, windowSize.x - 2 * _p.x);
        newTexture = SDL_CreateTextureFromSurface(renderer(), surf);
        if (!newTexture) {
            printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(surf);

        return newTexture;
    }

//renders text and adds a shadow as in intro state
    void STR_State::renderText(Rect values, SDL_Texture *t) {

        u32 fmt;
        int access;
        SDL_QueryTexture(t, &fmt, &access, &_blendedTextSize.x, &_blendedTextSize.y);

        SDL_SetTextureColorMod(t, outlineColor.r, outlineColor.g, outlineColor.b);
        for (const Point &offset: HSNR64::ShadowOffset::Rhombus) {
            const Rect dst_rect = Rect{values.x, values.y + _blendedTextSize.y, _blendedTextSize.x, _blendedTextSize.y} + offset;
            SDL_RenderCopy(renderer(), t, EntireRect, &dst_rect);
        }
        const Color &color = HSNR64::Palette(_colorIndex);
        SDL_SetTextureColorMod(t, color.r, color.g, color.b);
        const Rect dst_rect = {values.x, values.y +_blendedTextSize.y, _blendedTextSize.x, _blendedTextSize.y};
        SDL_RenderCopy(renderer(), t, EntireRect, &dst_rect);

    }
    //renders text and adds a shadow as in intro state, with selectable color index
    void STR_State::renderText(Rect values, SDL_Texture *t, int colorIndex){
        u32 fmt;
        int access;
        SDL_QueryTexture(t, &fmt, &access, &_blendedTextSize.x, &_blendedTextSize.y);

        SDL_SetTextureColorMod(t, outlineColor.r, outlineColor.g, outlineColor.b);
        for (const Point &offset: HSNR64::ShadowOffset::Rhombus) {
            const Rect dst_rect = Rect{values.x, values.y + _blendedTextSize.y, _blendedTextSize.x, _blendedTextSize.y} + offset;
            SDL_RenderCopy(renderer(), t, EntireRect, &dst_rect);
        }
        const Color &color = HSNR64::Palette(colorIndex);
        SDL_SetTextureColorMod(t, color.r, color.g, color.b);
        const Rect dst_rect = {values.x, values.y +_blendedTextSize.y, _blendedTextSize.x, _blendedTextSize.y};
        SDL_RenderCopy(renderer(), t, EntireRect, &dst_rect);

    }

    u64 STR_State::RenderPlayerAnimation(Rect target, SDL_Texture  *t, Vector<SDL_Rect> clips){

        phase = startAnim/4;
        u64 result = phase;
        if(phase == 8){
            renderFromSpritesheet(target,t,&clips[7]);
        }else {
            renderFromSpritesheet(target, t, &clips[phase % 8]);
        }
        startAnim++;


        if(loopAnimation && phase >= 8){
            startAnim = 0;
            phase = 0;
            result = 0;
            animationFrame = 0;
            return 0;
        }
        if(!loopAnimation && phase >= 8){
            SwitchPlayerAnimation(nextState);
            pChar.state = nextState;
            startAnim = 29;
            phase = 7;
            result = 7;
            return 7;
        }
        return result%8;
    }

    void STR_State::AnimateTargets(){
        for(auto &a : aManager.targets){
            a.currentSprite = a.frame/4;
            u64 result = a.currentSprite;
            renderFromSpritesheet(a.getTarget(), GetAnimation(a),&clips32[a.currentSprite]);
            a.frame++;
            if(a.loop && a.currentSprite >= 7){
                a.currentSprite = 0;
                a.frame = 0;
                a.animationFrame = 7;
                result = 0;
            }
            if(!a.loop && a.currentSprite == 8){
                a.currentAnimation = a.nextAnimation;
                a.currentSprite = 0;
                a.frame = 0;
                result = 7;
            }

        }
    }
    SDL_Texture *STR_State::GetAnimation(AnimationTarget &a){
        using enum EntityType;
        using enum EntityAnimations;


        ///TODO add more animations for types
        switch(a.type){
            case EntityType::EnemyType1: switch(a.currentAnimation){
                case EntityAnimations::Idle: a.loop = true; a.nextAnimation = EntityAnimations::Idle; return playerIdleSheet;break;
                case Aim: a.loop = false; a.nextAnimation = Fire; return playerDamageKnockdownSheet;break;
                case Fire: a.loop = false; a.nextAnimation = Idle; return playerGetUpSheet;break;
                default: return playerIdleSheet;break;
            }
            default: return playerIdleSheet;
        }
    }

    void STR_State::SwitchPlayerAnimation(PlayerState sheet){
        using enum PlayerState;
        pChar.state = sheet;




        switch(sheet){
            case Idle: playerAnimation = playerIdleSheet; loopAnimation = true;nextState = Idle;break;
            case Idle_Flip: playerAnimation = playerIdleSheetFlip;loopAnimation = true;nextState = Idle_Flip;break;
            case Walk: playerAnimation = playerWalkSheet;loopAnimation = false;nextState = Idle;break;
            case Walk_Flip: playerAnimation = playerWalkSheetFlip;loopAnimation = false;nextState = Idle_Flip;break;
            case Damage: playerAnimation = playerDamageSheet;loopAnimation = false; nextState = Idle;break;
            case Damage_Flip: playerAnimation = playerDamageSheetFlip;loopAnimation = false;nextState = Idle_Flip;break;
            case KnockdownDamage: playerAnimation = playerDamageKnockdownSheet;loopAnimation = false;knockdown = true; nextState = Grounded;break;
            case KnockdownDamage_Flip: playerAnimation = playerDamageKnockdownSheetFlip;loopAnimation = false; knockdown = true;nextState = Grounded_Flip;break;
            case GetUp: playerAnimation = playerGetUpSheet;loopAnimation = false; knockdown = false;nextState = Idle;break;
            case GetUp_Flip: playerAnimation = playerGetUpSheetFlip;loopAnimation = false; knockdown = false;nextState = Idle_Flip;break;
            case Grounded: playerAnimation = playerDamageKnockdownSheet;loopAnimation = false; knockdown =true; nextState = Grounded;break;
            case Grounded_Flip: playerAnimation = playerDamageKnockdownSheetFlip;loopAnimation = false; knockdown = true; nextState = Grounded_Flip;break;
            default: playerAnimation = playerIdleSheet;loopAnimation = true;break;

        }
    }

    void STR_State::ZoomOut(){
        scale = scale/2;
        gridStartingPoint.x = gridStartingPoint.x/2;
        gridStartingPoint.y = gridStartingPoint.y/2;



        grid.updateTileSize(scale);
        grid.setOrigin(gridStartingPoint.x,gridStartingPoint.y);
        pChar.updatePosition(grid.getTileRect(pChar.gridPosition));
        for(auto &e : aManager.targets){
            e.updatePosition(grid.getTileRect(e.gridPos));
        }
    }
    void STR_State::ZoomIn(){
        scale = scale*2;
        gridStartingPoint.x = gridStartingPoint.x*2;
        gridStartingPoint.y = gridStartingPoint.y*2;

        grid.updateTileSize(scale);
        grid.setOrigin(gridStartingPoint.x,gridStartingPoint.y);
        pChar.updatePosition(grid.getTileRect(pChar.gridPosition));
        for(auto &e : aManager.targets){
            e.updatePosition(grid.getTileRect(e.gridPos));
        }
    }
    void STR_State::CameraMoveBy1Tile(Directions direction){

        switch(direction){
            case Directions::UP: gridStartingPoint.y = gridStartingPoint.y-scale;
                grid.setOrigin(gridStartingPoint.x,gridStartingPoint.y);
                pChar.updatePosition(grid.getTileRect(pChar.gridPosition));
                for(auto &e : aManager.targets){
                    e.updatePosition(grid.getTileRect(e.gridPos));
                }
                break;
            case Directions::RIGHT: gridStartingPoint.x = gridStartingPoint.x+scale;

                grid.setOrigin(gridStartingPoint.x,gridStartingPoint.y);
                // playerRect = grid.getTile(3,3).rect;
                pChar.updatePosition(grid.getTileRect(pChar.gridPosition));
                for(auto &e : aManager.targets){
                    e.updatePosition(grid.getTileRect(e.gridPos));
                }
                break;
            case Directions::DOWN: gridStartingPoint.y = gridStartingPoint.y+scale;
                grid.setOrigin(gridStartingPoint.x,gridStartingPoint.y);
                pChar.updatePosition(grid.getTileRect(pChar.gridPosition));
                for(auto &e : aManager.targets){
                    e.updatePosition(grid.getTileRect(e.gridPos));
                }
                break;
            case Directions::LEFT:  gridStartingPoint.x = gridStartingPoint.x-scale;
                grid.setOrigin(gridStartingPoint.x,gridStartingPoint.y);

                // playerRect = grid.getTile(3,3).rect;
                pChar.updatePosition(grid.getTileRect(pChar.gridPosition));
                for(auto &e : aManager.targets){
                    e.updatePosition(grid.getTileRect(e.gridPos));
                }
                break;
            default: break;

        }
    }

    void STR_State::RenderFloorTile(FloorTileStyles s, SDL_Rect t){
        using enum FloorTileStyles;
        switch(s){
            case NONE:
                break;
            case Standard:
                renderFromSpritesheet(t,tileStandard,&clips32[0]);break;
            case Round:
                renderFromSpritesheet(t,tileCircle,&clips32[0]);break;
        }

    }
    void STR_State::RenderObjectSprites(Objects o, SDL_Rect t){
        using enum Objects;
        switch(o) {
            case Shot:
                renderFromSpritesheet(t, objectShot, &clips32[1]);
                break;

            default:
                break;
        }
    }
    void STR_State::RenderWalls(SDL_Rect t,int walls) {
        renderFromSpritesheet(t, tilesWalls, &clips32[walls]);
    }
    void STR_State::RenderDoors(SDL_Rect t,int doors) {
        renderFromSpritesheet(t, tilesDoors, &clips32[doors]);
    }


/*
//#ifdef IMGUI

    void STR_State::RenderUI( const u64 frame, const u64 totalMSec, const f32 deltaTNeeded )
    {
        // ImGui Demo
        static bool show_demo_window = true;
        ImGui::SetNextWindowCollapsed( true, ImGuiCond_Once );
        ImGui::ShowDemoWindow( &show_demo_window );

        Point windowSize;
        SDL_GetWindowSize( window(), &windowSize.x, &windowSize.y );

        static bool autoUpdate = false;
        static bool drawColorNumber = false;
        //ImGuiIO & io = ImGui::GetIO();
        ImGui::Begin( "Introstate", nullptr, ImGuiWindowFlags_NoFocusOnAppearing );
        if( frame == 0 ) // Do not focus this new window
            ImGui::SetWindowFocus( nullptr );

        if( ImGui::SliderInt( "int", &_p.x, 0, windowSize.x/2 ) && autoUpdate )
            _blendedText = nullptr;

        ImGui::Checkbox( "Auto-Redraw", &autoUpdate );
        ImGui::SameLine();
        ImGui::Checkbox( "Dark Outline", &_isDarkOutline );

        if( ImGui::Button( "Redraw" ) ) // Buttons return true when clicked (most widgets return true when edited/activated)
            _blendedText = nullptr;

        if( ImGui::SliderInt( "color index", &_colorIndex, 0, 63 ) ) {}

        static int charSelect = 65;
        ImGui::Text( "'%c'", (char) charSelect );
        ImGui::SameLine();
        if( ImGui::SliderInt( "charSel", &charSelect, 0, 255 ) ) {}


        TileFont::CharMetric & m = TileFont::char_metrics[charSelect];
        u8  min = 0,
            max = 8;
        ImGui::SliderScalarN( "cavity left", ImGuiDataType_U8, m.left, 8, &min, &max );
        ImGui::SliderScalarN( "cavity right", ImGuiDataType_U8, m.right, 8, &min, &max );


        ImGui::Checkbox( "Draw Color Number", &drawColorNumber );

        ImGui::PushID( "fg color" );
        ImGui::PushStyleVar( ImGuiStyleVar_FrameBorderSize, 1 );
        // CARE: ImU32 as color is 0xAABBGGRR - opposite of what might be expected
        ImGui::PushStyleColor( ImGuiCol_Border, 0xAAFFFFFF );
        constexpr fmt::format_string<int>
                withNumber( "{:02}" ),
                withoutNumber( "  ##{:02}" );
        const fmt::format_string<int> & fmt = drawColorNumber
                                              ? withNumber
                                              : withoutNumber;

        auto needsLinebreak =[]( int i )
        {
            return i == 10 || i == 25 || i == 40 || i == 52;
        };

        for( int i = 0; i < 64; ++i )
        {
            const SDL_Color & color = HSNR64::Palette( i );
            const ImU32 pcol = ToU32( color );
            //const ImU32 pcol = std::bit_cast<ImU32>( hsnr64::Palette[i] );
            //Color color = hsnr64::Palette[i];
            ImGui::PushStyleColor( ImGuiCol_Button, pcol );
            ImGui::PushStyleColor( ImGuiCol_Text, pcol ^ 0x00808080 );
            if( ImGui::Button( format( fmt::runtime( fmt ), i ).c_str() ) )
                _colorIndex = i;
            ImGui::PopStyleColor( 2 );
            //ImGui::ColorButton( format( "color{}", i ).c_str(), *((ImVec4*)&hsnr64::Palette[i]), ImGuiColorEditFlags_Uint8 );
            //if(i%10 != 0)
            if( !needsLinebreak( i ) )
                ImGui::SameLine();
        }
        ImGui::NewLine(); // Undo last SameLine
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        ImGui::PopID();

        if( ImGui::Button( "Open" ) )
        {
            NFD::Window     nw = nativeWindow();
            NFD::UniquePath path;
            const NFD::Result result = NFD::OpenDialog( path, NFD::EmptyFilter, 0, NFD::EmptyDefaultPath, nw );    // Freezes execution of the Game

            if( result == NFD::Result::NFD_OKAY )
                print( "Success! Path is {0}\n", path.get() );
        }
        ImGui::SameLine();
        if( ImGui::Button( "OpenMultiple" ) )
        {
            NFD::Window        nw = nativeWindow();
            NFD::UniquePathSet paths;
            const NFD::Result  result = NFD::OpenDialogMultiple( paths, NFD::EmptyFilter, 0, NFD::EmptyDefaultPath, nw );     // Freezes execution of the Game

            // TODO
            //if( result == NFD_OKAY )
            //	print( "Success! Path is {0}\n", fmt::join( paths.get(), ", " ) );
        }
        ImGui::SameLine();
        if( ImGui::Button( "Save" ) )
        {
            NFD::Window     nw = nativeWindow();
            NFD::UniquePath path;
            const NFD::Result result = NFD::SaveDialog( path, NFD::EmptyFilter, 0, NFD::EmptyDefaultPath, NFD::EmptyDefaultName, nw ); // Freezes execution of the Game
            //	const NFD::Result result = NFD::SaveDialog();   // The same as above

            if( result == NFD::Result::NFD_OKAY )
                print( "Success! Path is {0}\n", path.get() );
        }
        ImGui::SameLine();
        if( ImGui::Button( "PickFolder" ) )
        {
            NFD::Window     nw = nativeWindow();
            NFD::UniquePath path;
            const NFD::Result result = NFD::PickFolder( path, NFD::EmptyDefaultPath, nw );     // Freezes execution of the Game

            if( result == NFD_OKAY )
                print( "Success! Path is {0}\n", path.get() );
        }

        ImGui::End();
    }
*/
//#endif

}