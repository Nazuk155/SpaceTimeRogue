#include "example_game.hpp"

#include <hsnr64/offset.hpp>
#include <hsnr64/palette.hpp>
//#include <tilefont.h>

namespace JanSordid::SDL_Example
{


///TODO make enemy ship and starting map; add player logic and skills; load player ship after enemy with offsetload;

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
        string playerStabPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Player_Tripple_Attack-Sheet.png";
        string playerStabFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/playerCharacter/Player_Tripple_Attack_Flip-Sheet.png";


        //other characters
        string characterOrcIdlePath = BasePath "/src/example/game/Ressources/Image_assets/entities/enemy/Ork_Idle-Sheet.png";
        string charactersOrcIdleFlipPath = BasePath "/src/example/game/Ressources/Image_assets/entities/enemy/Ork_Idle_flip-Sheet.png";
        string charactersOrcShootPath = BasePath "/src/example/game/Ressources/Image_assets/entities/enemy/Ork_Shoot-Sheet.png";
        string characterOrcShootFlipPath = BasePath "/src/example/game/Ressources/Image_assets/entities/enemy/Ork_Shoot_Flip-Sheet.png";
        string characterOrcWalkPath = BasePath "/src/example/game/Ressources/Image_assets/entities/enemy/Ork_Walk_Cycle-Sheet.png";
        string characterOrcWalkFlipPath = BasePath "/src/example/game/Ressources/Image_assets/entities/enemy/Ork_Walk_Cycle_Flip-Sheet.png";

        string characterTurtleIdlePath = BasePath "/src/example/game/Ressources/Image_assets/entities/turtle/Turtle_Idol-Sheet.png";
        string characterTurtleFloatPath = BasePath "/src/example/game/Ressources/Image_assets/entities/turtle/Turtle_Float-Sheet.png";
        string characterTurtleJumpPath = BasePath "/src/example/game/Ressources/Image_assets/entities/turtle/Turtle_Jump-Sheet.png";
        string characterTurtlePowerPath = BasePath "/src/example/game/Ressources/Image_assets/entities/turtle/Turtle_Power-Sheet.png";

        //tiles
        string tileTestingPath = BasePath "/src/example/game/Ressources/Image_assets/tiles/Tiles/Tiles.png";
        string tileStandardPath = BasePath"/src/example/game/Ressources/Image_assets/tiles/Standard_Floor_Tile-Sheet.png";
        string tileCirclePath = BasePath"/src/example/game/Ressources/Image_assets/tiles/Circle-Sheet.png";
        string tileWallsPath = BasePath"/src/example/game/Ressources/Image_assets/tiles/Walls.png";
        string tileDoorsPath = BasePath"/src/example/game/Ressources/Image_assets/tiles/Walls_Blue-Sheet.png";
        string tileGrassPath = BasePath"/src/example/game/Ressources/Image_assets/tiles/Grass_1.png";
        string tileFloor2Path = BasePath"/src/example/game/Ressources/Image_assets/tiles/Floor_2-Sheet.png";
        string tileTopWallsPath = BasePath"/src/example/game/Ressources/Image_assets/tiles/Walls1.png";

        //objects
        string objectShotPath = BasePath "/src/example/game/Ressources/Image_assets/items/Shoot-Sheet.png";
        string objectPackagePath = BasePath "/src/example/game/Ressources/Image_assets/items/Package_Open.png";

        //backgrounds
        string backgroundSpacePath = BasePath"/src/example/game/Ressources/Image_assets/backgrounds/Space.png";
        string backgroundsGrassPath = BasePath"/src/example/game/Ressources/Image_assets/backgrounds/Grass_Background.png";
        string backgroundsSpaceshipPath = BasePath"/src/example/game/Ressources/Image_assets/backgrounds/Spaceship.png";

        //ui
        string uiHealthbarSheetPath = BasePath"/src/example/game/Ressources/Image_assets/ui/UI-export.png";
        string uiSkillsBackgroundPath = BasePath"/src/example/game/Ressources/Image_assets/ui/Skills_Background_ui.png";
        string uiSpeechBubblePath = BasePath"/src/example/game/Ressources/Image_assets/ui/Speechbubble-Sheet.png";




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
    playerStabSheet = loadFromFile(playerStabPath);
    playerStabSheetFlip = loadFromFile(playerStabFlipPath);

    //other characters
    characterOrcIdleSheet = loadFromFile(characterOrcIdlePath);
    characterOrcIdleSheetFlip = loadFromFile(charactersOrcIdleFlipPath);
    characterOrcShootSheet = loadFromFile(charactersOrcShootPath);
    characterOrcShootSheetFlip = loadFromFile(characterOrcShootFlipPath);
    characterOrkWalkSheet = loadFromFile(characterOrcWalkPath);
    characterOrkWalkSheetFlip = loadFromFile(characterOrcWalkFlipPath);

    ///turtle
    characterTurtleIdleSheet = loadFromFile(characterTurtleIdlePath);
    characterTurtleFloatSheet = loadFromFile(characterTurtleFloatPath);
    characterTurtlePowerSheet = loadFromFile(characterTurtlePowerPath);
    characterTurtleJumpSheet = loadFromFile(characterTurtleJumpPath);

    //tiles
    tileTest = loadFromFile(tileTestingPath);
    tileStandard = loadFromFile(tileStandardPath);
    tileCircle = loadFromFile(tileCirclePath);
    tilesWalls = loadFromFile(tileWallsPath);
    tilesDoors = loadFromFile(tileDoorsPath);
    tileGrassSheet = loadFromFile(tileGrassPath);
    tileFloor2Sheet = loadFromFile(tileFloor2Path);
    tileTopWallsSheet = loadFromFile(tileTopWallsPath);
    //items
    objectShot = loadFromFile(objectShotPath);
    objectPackageOpenSheet = loadFromFile(objectPackagePath);
    //backgrounds
    backgroundSpace = loadFromFile(backgroundSpacePath);
    backgroundsGrass = loadFromFile(backgroundsGrassPath);
    backgroundsSpaceship = loadFromFile(backgroundsSpaceshipPath);
    //ui
    uiHealthbarsSheet = loadFromFile(uiHealthbarSheetPath);
    uiSkillsBackground = loadFromFile(uiSkillsBackgroundPath);
    uiSpeechbubbleSheet = loadFromFile(uiSpeechBubblePath);

    floorTileSprites.push_back(tileStandard);
    floorTileSprites.push_back(tileCircle);
    floorTileSprites.push_back(tileGrassSheet);
    floorTileSprites.push_back(tileTopWallsSheet);
    objectSprites.push_back(objectShot);
    characterSprites.push_back(playerIdleSheet);
    characterSprites.push_back(characterOrcIdleSheet);

    playerAnimation = playerIdleSheet;
    grid.updateTileSize(scale);

    musicManager.init();

        mode = Mode::Showcase;

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
                    grid.getTile(62 + i, 36 + j).style = FloorTileIDs::Standard;
                    grid.getTile(62 + i, 36 + j).isTop = true;
                    grid.getTile(62 + i, 36 + j).walls = 1;
                }
            }

            grid.getTile(62, 36).style = FloorTileIDs::Standard;
            grid.getTile(63, 36).style = FloorTileIDs::Standard;
            grid.getTile(64, 36).style = FloorTileIDs::Standard;
            grid.getTile(62, 36).isTop = true;
            grid.getTile(63, 36).isTop = true;
            grid.getTile(64, 36).isTop = true;


            grid.getTile(62, 37).isTop = true;
            grid.getTile(62, 37).style = FloorTileIDs::Standard;



            aManager.addTarget(
                    {target, {62, 36}, 0, CharacterIDs::PlayerCharacter, CharacterAnimations::Aim, CharacterAnimations::Fire});

            // pChar.rect = grid.getTile(60,40).rect;
            pChar.updatePosition({60+59, 34+31}, grid.getTile(60+59, 34+31).rect);
        }
        if(mode == Mode::TilePlacer){

            gridStartingPoint.x = 0;
            gridStartingPoint.y = 0;
            grid.setOrigin(gridStartingPoint.x, gridStartingPoint.y);
            startingScale = scale;
/*

            gridStartingPoint.x = -(scale * grid.getGridTilesXY().x / 2);
            gridStartingPoint.y = -(scale * grid.getGridTilesXY().y / 2);
            grid.setOrigin(gridStartingPoint.x, gridStartingPoint.y);
            startingScale = scale;
*/
        }
        if(mode == Mode::Showcase){
            scale = scale*8;
            gridStartingPoint.x = 0;
            gridStartingPoint.y = 0;
            grid.updateTileSize(scale);
            grid.setOrigin(gridStartingPoint.x, gridStartingPoint.y);
            startingScale = scale;

            pChar.updatePosition({4,2},grid.getTile(4,2).rect);
            pChar.state = PlayerState::Idle;

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
        //characters
        SDL_DestroyTexture(characterOrcIdleSheet);
        SDL_DestroyTexture(characterOrcIdleSheetFlip);
        SDL_DestroyTexture(characterOrcShootSheet);
        SDL_DestroyTexture(characterOrcShootSheetFlip);
        SDL_DestroyTexture(characterOrkWalkSheet);
        SDL_DestroyTexture(characterOrkWalkSheetFlip);
        SDL_DestroyTexture(playerStabSheet);
        SDL_DestroyTexture(playerStabSheetFlip);

        SDL_DestroyTexture(characterTurtleIdleSheet);
        SDL_DestroyTexture(characterTurtlePowerSheet);
        SDL_DestroyTexture(characterTurtleJumpSheet);
        SDL_DestroyTexture(characterTurtleFloatSheet);


        //tiles
        SDL_DestroyTexture(tileTest);
        SDL_DestroyTexture(tileStandard);
        SDL_DestroyTexture(tileCircle);
        SDL_DestroyTexture(tilesWalls);
        SDL_DestroyTexture(tilesDoors);
        SDL_DestroyTexture(tileGrassSheet);
        SDL_DestroyTexture(tileFloor2Sheet);
        SDL_DestroyTexture(tileTopWallsSheet);
        //objects
        SDL_DestroyTexture(objectShot);
        SDL_DestroyTexture(objectPackageOpenSheet);

        //backgrounds
        SDL_DestroyTexture(backgroundSpace);
        SDL_DestroyTexture(backgroundsGrass);
        SDL_DestroyTexture(backgroundsSpaceship);

        //ui
        SDL_DestroyTexture(uiHealthbarsSheet);
        SDL_DestroyTexture(uiSkillsBackground);
        SDL_DestroyTexture(uiSpeechbubbleSheet);


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
        playerStabSheet = nullptr;
        playerStabSheetFlip = nullptr;

        tileTest = nullptr;
        tileStandard = nullptr;
        tileCircle = nullptr;
        tilesWalls = nullptr;
        tilesDoors = nullptr;
        tileGrassSheet = nullptr;
        tileFloor2Sheet = nullptr;
        tileTopWallsSheet = nullptr;

        objectShot = nullptr;
        objectPackageOpenSheet = nullptr;

        characterOrcIdleSheet = nullptr;
        characterOrcIdleSheetFlip = nullptr;
        characterOrcShootSheet = nullptr;
        characterOrcShootSheetFlip = nullptr;
        characterOrkWalkSheet = nullptr;
        characterOrkWalkSheetFlip = nullptr;

        characterTurtleIdleSheet = nullptr;
        characterTurtleJumpSheet= nullptr;
        characterTurtlePowerSheet= nullptr;
        characterTurtleFloatSheet= nullptr;

        backgroundSpace = nullptr;
        backgroundsGrass = nullptr;
        backgroundsSpaceship = nullptr;

        uiHealthbarsSheet = nullptr;
        uiSkillsBackground = nullptr;
        uiSpeechbubbleSheet = nullptr;


        Base::Destroy();
    }

    bool STR_State::HandleEvent( const Event & event ) {

        mouseState = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if(mode == Mode::Showcase){
            switch (event.type) {
                case SDL_KEYDOWN: {
                    const Keysym &what_key = event.key.keysym;

                    if (what_key.scancode == SDL_SCANCODE_G && event.key.repeat == 0) {
                        if (showGrid) { showGrid = false; } else { showGrid = true; }

                    }
                    else if (what_key.scancode == SDL_SCANCODE_SPACE && event.key.repeat == 0) {

                        advance++;
                        pChar.playedBark = false;

                    }
                    else if (what_key.scancode == SDL_SCANCODE_R && event.key.repeat == 0) {

                        advance = 0;
                        pChar.playedBark = false;
                        pChar.updatePosition({4,2},grid.getTile(4,2).rect);
                        pChar.state = PlayerState::Idle;

                    }
                    else if (what_key.scancode == SDL_SCANCODE_KP_PLUS && event.key.repeat == 0) {

                        musicManager.volume += 10;

                        Mix_VolumeMusic(musicManager.volume);

                    }
                    else if (what_key.scancode == SDL_SCANCODE_KP_MINUS && event.key.repeat == 0) {

                        musicManager.volume = 0;
                        Mix_VolumeMusic(0);

                    }
                    else {
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


        if (mode == Mode::Game) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    const Keysym &what_key = event.key.keysym;

                    if (what_key.scancode == SDL_SCANCODE_G && event.key.repeat == 0) {
                        if (showGrid) { showGrid = false; } else { showGrid = true; }
                    }

                    else if (what_key.scancode == SDL_SCANCODE_P && event.key.repeat == 0) {
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
                    else if (what_key.scancode == SDL_SCANCODE_K && event.key.repeat == 0) {

                        if (tTracker.isPlayerShipTile){
                            tTracker.isPlayerShipTile = false; }else { tTracker.isPlayerShipTile = true; }

                    }
                    else  if (what_key.scancode == SDL_SCANCODE_H && event.key.repeat == 0) {

                        if (tTracker.infoToggle) { tTracker.infoToggle = false; } else { tTracker.infoToggle = true; }

                    }
                    else if (what_key.scancode == SDL_SCANCODE_L && event.key.repeat == 0) {

                        load = true;


                    }
                    else if (what_key.scancode == SDL_SCANCODE_T && event.key.repeat == 0) {
                        if(tTracker.placeTileMode){
                            tTracker.placeTileMode = false;
                        }else{tTracker.placeTileMode = true; tTracker.placeObjectMode = false; tTracker.placeCharacterMode = false;
                            tTracker.manageWallsMode = false;tTracker.manageDoorsMode = false;
                            tTracker.ResetWallDoorPlacer();}

                    }
                    else if (what_key.scancode == SDL_SCANCODE_C && event.key.repeat == 0) {
                        if(tTracker.placeCharacterMode){
                            tTracker.placeCharacterMode = false;
                        }else{
                            tTracker.placeCharacterMode = true;

                            tTracker.placeObjectMode = false; tTracker.placeTileMode = false;
                            tTracker.manageWallsMode = false;tTracker.manageDoorsMode = false;
                            tTracker.ResetWallDoorPlacer();}

                    }
                    else if (what_key.scancode == SDL_SCANCODE_U && event.key.repeat == 0) {

                        if (tTracker.manageWallsMode  ) { tTracker.manageWallsMode = false; tTracker.manageDoorsMode = true;
                        }
                        else { tTracker.manageWallsMode = true;tTracker.manageDoorsMode = false; }
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

                        ///terrible code, rework tTracker Modes into enum to switch between modes with switches later
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
                                            b.character = CharacterIDs::NONE;
                                        }

                                    }
                                }
                            }
                        }
                    }
                    if(tTracker.placeCharacterMode) {
                        if (event.button.button == (SDL_BUTTON_LEFT)) {
                            SDL_Point temp = mousePosition;
                            for (auto &a: grid.tiles) {
                                for (auto &b: a) {
                                    b.selected = false;
                                    if (SDL_PointInRect(&temp, &b.rect)) {
                                        b.selected = true;
                                        tTracker.currentCharacter = b.character;

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
                                            b.character = tTracker.currentCharacter;
                                            b.occupied = true;
                                            b.object = ObjectIDs::NONE;
                                        }

                                    }
                                }
                            }
                        }
                    }
                    if (event.button.button == (SDL_BUTTON_RIGHT)) {
                        if (!tTracker.placeObjectMode && !tTracker.placeCharacterMode) {
                            SDL_Point temp = mousePosition;
                            for (auto &a: grid.tiles) {
                                for (auto &b: a) {
                                    b.placed = false;
                                    if (SDL_PointInRect(&temp, &b.rect)) {
                                        //last placed tile set to true
                                        b.placed = true;
                                        //update the tiles style
                                        b.style = tTracker.currentFloorSprite;
                                        //if placing player ship parts
                                        if(tTracker.isPlayerShipTile){
                                            b.isPlayerShipTile = true;
                                        }
                                        //if NONE selected remove from grid
                                        if (tTracker.currentFloorSprite == FloorTileIDs::NONE) {
                                            b.onGrid = false;
                                            b.object = ObjectIDs::NONE;
                                            b.character = CharacterIDs::NONE;
                                            b.isPlayerShipTile = false;
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

        if(mode == Mode::Showcase){
            if (pChar.state == PlayerState::Walk_Flip) {
                if(pChar.rect.x> grid.getTile(pChar.gridPosition.x-1,pChar.gridPosition.y).rect.x -(pChar.rect.w/2)){
                    pChar.rect.x = pChar.rect.x - 4;
                    Mix_PlayChannel(-1,effectPlayerWalk,0);

                }else{
                    Mix_HaltChannel(-1);
                    SwitchPlayerAnimation(PlayerState::Idle_Flip);
                    advance++;}



            }
            if(advance == 9){
                phase = 0;
                startAnim = 0;
                animationFrame = 0;
            }
            if(advance == 17) {
                if (pChar.state != PlayerState::Grounded_Flip) {
                    SwitchPlayerAnimation(PlayerState::KnockdownDamage_Flip);
                }
            }
                if(advance == 18){
                    if(pChar.state != PlayerState::Idle_Flip) {
                        SwitchPlayerAnimation(PlayerState::GetUp_Flip);

                    }else{advance++;}

            }

        }
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
                    if (b.style != FloorTileIDs::NONE && b.walls == 1) {
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
                for (int i =0;i<=static_cast<int>(FloorTileIDs::Floor2);i++) {
                    grid.tiles[j][0].style = static_cast<FloorTileIDs>(j);
                    j++;
                }

            }
            if (tTracker.placeObjectMode) {
                int j = 0; // next y pos
                for (auto a: objectSprites) {
                    grid.tiles[j][0].object = static_cast<ObjectIDs>(j + 1);
                    j++;
                }

            }
            if (tTracker.placeCharacterMode) {
                int j = 0; // next y pos
                for (auto a: characterSprites) {
                    grid.tiles[j][0].character = static_cast<CharacterIDs>(j + 1);
                    j++;
                }

            }

            //finish selecting modes
            if (tTracker.confirm) {
                SaveMap(grid.tiles);
                //SavePlayerShip(grid.tiles);
                tTracker.confirm = false;
                tTracker.manageDoorsMode = false;
                tTracker.manageWallsMode = false;
                tTracker.ResetWallDoorPlacer();
            }

            if(load) {
               // loadTilemap(testingMap);
                loadOffsetMap(enemyShipOrc,60,34);
                loadOffsetMap(startingShip,60,34);
                load = false;
            }
        }
    }

    void STR_State::Render( const u64 frame, const u64 totalMSec, const f32 deltaTNeeded )
    {
        Point windowSize;
        SDL_GetWindowSize( window(), &windowSize.x, &windowSize.y );

        SDL_SetRenderDrawColor(renderer(), 50, 50, 50, 255);

        SDL_RenderClear(renderer());
        if(mode == Mode::Showcase){
            Texture * emote = nullptr;
           //turtle and package target
            SDL_Rect turtle = grid.getTile(2,2).rect;
            turtle.y = turtle.y - turtle.h/4;
            if(musicManager.volume != 0) {
                Mix_MasterVolume(MIX_MAX_VOLUME);
                Mix_VolumeMusic(1);
            }
            //render emote on this
            SDL_Rect turtleOffset;
            turtleOffset = turtle;
            turtleOffset.x = turtleOffset.x +turtle.w/2;
            turtleOffset.y = turtleOffset.y +turtle.h/4;

            renderFromSpritesheet({0,0,480*4,270*4},backgroundsGrass);
            if(advance <=10){
                renderFromSpritesheet(turtle,objectPackageOpenSheet,&clips32[0]);
            }
            switch(advance){
                case 0:

                    musicManager.changeMusic(bgm::GameOver);
                    SwitchPlayerAnimation(PlayerState::Grounded);
                    break;
                case 1:
                   if(pChar.state == PlayerState::Grounded){
                       SwitchPlayerAnimation(PlayerState::GetUp);
                   }
                    if(pChar.state == PlayerState::Idle){
                        musicManager.changeMusic(bgm::SlowStart);
                        RenderPlayerBubbleText("Good crash!\nOnly lost half the ship!\n  ...",pChar);
                    }

                    break;
                case 2:
                    SwitchPlayerAnimation(PlayerState::Idle);
                    RenderPlayerBubbleText("... which means no cargo container.\n"
                                           "And no fusion reactor.\n"
                                           "Plus, all the packages are gone...",pChar);
                    break;

                case 3:
                    SwitchPlayerAnimation(PlayerState::Idle);
                    RenderPlayerBubbleText("I could mark them lost in transit!\n"
                                           "End my shift early...\n"
                                           "... aaand be stuck here forever! Great!",pChar);
                    break;
                case 4:
                    SwitchPlayerAnimation(PlayerState::Idle_Flip);
                    RenderPlayerBubbleText("Oh, hello there!\n"
                                           "You look big!\n"
                                           "Please be a power source!",pChar);
                    break;
                case 5:
                    SwitchPlayerAnimation(PlayerState::Walk_Flip);

                 //   RenderPlayerBubbleText("Oh, hello there!\n""You look big!\n""Please be a power source!",pChar);
                 break;
                case 6:
                    RenderPlayerBubbleText("Delivery instruction says:\n"
                                           "DELIVERY MANDATORY;\n"
                                           "OR UNIVERSE ENDS",pChar);
                    break;
                case 7:
                    RenderPlayerBubbleText("Yeah right, very funny.\n"
                                           "Threatening the delivery guy.\n"
                                           "Eh, I've read worse ones.",pChar);
                    break;
                case 8:
                    RenderPlayerBubbleText("Marked for *deliver today* as well!\n"
                                           "Might as well mark me fired!\n"
                                           "You better be something good!",pChar);
                    break;
                case 9:
                    RenderPlayerBubbleText("Welp, im out of options.\n"
                                           "Postal secrecy be damned!\n"
                                           "Boxcutter go!!!",pChar);
                    break;
                case 10:
                    musicManager.changeMusic(bgm::NONE);
                    break;
                case 11:
                    //Mix_PlayChannel(-1,effectPackageOpen,0);

                    phase2 = startAnim2/4;

                    renderFromSpritesheet(turtle, objectPackageOpenSheet, &clips32[phase2%12]);
                    if(phase2 == 12){
                        phase2 = 0;
                        startAnim2 = 0;
                        advance++;
                    }
                    startAnim2++;
                    break;
                case 12:
                    musicManager.changeMusic(bgm::NONE);
                    RenderPlayerBubbleText("AAAaaand its a turtle!\n"
                                           "Great! Not helping!\n"
                                           "One package and thats what i get!",pChar);
                    phase2 = startAnim2/4;


                    emote = textToTexture(" :(");

                    turtleOffset = turtle;
                    turtleOffset.x = turtleOffset.x +turtle.w/2;
                    turtleOffset.y = turtleOffset.y +turtle.h/4;
                    renderText(turtleOffset,emote);
                    SDL_DestroyTexture(emote);
                    emote = nullptr;
                    renderFromSpritesheet(turtle, characterTurtleIdleSheet, &clips32[0]);
                    if(phase2 == 8){
                        phase2 = 0;
                        startAnim2 = 0;

                    }
                    startAnim2++; break;

                case 13:
                    musicManager.changeMusic(bgm::NONE);
                    RenderPlayerBubbleText("...\n"
                                           "Im sorry buddy.\n"
                                           "You wanna go home too?",pChar);
                    phase2 = startAnim2/4;


                    emote = textToTexture(" :(");

                    turtleOffset = turtle;
                    turtleOffset.x = turtleOffset.x +turtle.w/2;
                    turtleOffset.y = turtleOffset.y +turtle.h/4;
                    renderText(turtleOffset,emote);
                    SDL_DestroyTexture(emote);
                    emote = nullptr;
                    renderFromSpritesheet(turtle, characterTurtleIdleSheet, &clips32[0]);
                    if(phase2 == 8){
                        phase2 = 0;
                        startAnim2 = 0;

                    }
                    startAnim2++;
                    break;

                    case 14:

                    musicManager.changeMusic(bgm::LongShift);
                    RenderPlayerBubbleText("Yeah thats the spirit! :D\n"
                                           "We can figure this out together!\n"
                                           "Show me what you got, turtle!",pChar);
                    phase2 = startAnim2/4;

                    emote = textToTexture(":D");

                    renderText(turtleOffset,emote);
                    SDL_DestroyTexture(emote);
                    emote = nullptr;
                    renderFromSpritesheet(turtle, characterTurtleIdleSheet, &clips32[phase2%8]);
                    if(phase2 == 8){
                        phase2 = 0;
                        startAnim2 = 0;

                    }
                    startAnim2++;
                    break;
                case 15:
                    musicManager.changeMusic(bgm::LongShift);
                    RenderPlayerBubbleText("WOAH! SPACE TURTLE!\n"
                                           "Nice flip!\n"
                                           "Maybe break the glass next?",pChar);
                    phase2 = startAnim2/4;

                    if(startAnim2== 0){
                        Mix_PlayChannel(-1,effectTurtleJump,0);
                    }
                    emote = textToTexture(":D");

                    renderText(turtleOffset,emote);
                    SDL_DestroyTexture(emote);
                    emote = nullptr;
                    renderFromSpritesheet(turtle, characterTurtleJumpSheet, &clips32[phase2%12]);
                    startAnim2++;
                    if(phase2 == 12){
                        phase2 = 0;
                        startAnim2 = 0;
                        Mix_PlayChannel(-1,effectGlassRinging,0);
                    }

                    break;
                case 16:
                    musicManager.changeMusic(bgm::LongShift);
                    SwitchPlayerAnimation(PlayerState::Damage);
                    RenderPlayerBubbleText("OUCH! OUCH! OUCH!\n"
                                           "STOP SMASHING ME INTO THE GLASS\n"
                                           "ITS NOT BREAKING!!!",pChar);
                    phase2 = startAnim2/4;

                    if(startAnim2== 0){
                        Mix_PlayChannel(-1,effectGravity,0);
                    }
                    emote = textToTexture(">:0");

                    renderText(turtleOffset,emote);
                    SDL_DestroyTexture(emote);
                    emote = nullptr;
                    renderFromSpritesheet(turtle, characterTurtleFloatSheet, &clips32[phase2%16]);
                    startAnim2++;
                    if(phase2 >= 16){
                        phase2 = 0;
                        startAnim2 = 0;
                        Mix_PlayChannel(-1,effectGlassRinging,3);
                    }

                    break;
                case 17:
                    musicManager.changeMusic(bgm::GameOver);

                    Mix_HaltChannel(-1);
                    //knockdown in update
                    RenderPlayerBubbleText(" ...\n"
                                           " ... \n"
                                           " ...",pChar);
                    phase2 = startAnim2/4;

                    if(startAnim2== 0){
                       // Mix_PlayChannel(-1,effectGravity,0);
                    }
                    emote = textToTexture(":O");

                    renderText(turtleOffset,emote);
                    SDL_DestroyTexture(emote);
                    emote = nullptr;
                    renderFromSpritesheet(turtle, characterTurtleIdleSheet, &clips32[0]);
                    startAnim2++;
                    if(phase2 == 12){
                        phase2 = 0;
                        startAnim2 = 0;
                    }

                    break;
                case 18:
                    renderFromSpritesheet(turtle, characterTurtleIdleSheet, &clips32[0]);
                    break;

                case 19:
                    musicManager.changeMusic(bgm::LongShift);

                    RenderPlayerBubbleText("Just kidding! Im fine!\n"
                                           "Just don't do that again! \n"
                                           "So, can you power our ship?",pChar);
                    phase2 = startAnim2/4;

                    if(startAnim2== 0){
                        //Mix_PlayChannel(-1,effectGravity,0);
                    }
                    emote = textToTexture(":D");

                    renderText(turtleOffset,emote);
                    SDL_DestroyTexture(emote);
                    emote = nullptr;
                    renderFromSpritesheet(turtle, characterTurtleIdleSheet, &clips32[phase2%8]);
                    startAnim2++;
                    if(phase2 >= 8){
                        phase2 = 0;
                        startAnim2 = 0;
                    }

                    break;
                case 20:
                    musicManager.changeMusic(bgm::SlowStart);

                    RenderPlayerBubbleText("Looking good!\n"
                                           "Just keep doing that!\n"
                                           "I'll get you on board! :D",pChar);
                    phase2 = startAnim2/4;

                    if(startAnim2 == 0){
                        Mix_PlayChannel(-1,effectGravity,0);
                    }
                    emote = textToTexture(":D");

                    renderText(turtleOffset,emote);
                    SDL_DestroyTexture(emote);
                    emote = nullptr;
                    renderFromSpritesheet(turtle, characterTurtlePowerSheet, &clips32[phase2%12]);
                    startAnim2++;
                    if(phase2 >= 12){
                        phase2 = 0;
                        startAnim2 = 0;
                    }

                    break;
                case 21:
                    Mix_HaltChannel(-1);
                    renderFromSpritesheet({0,0,480*4,270*4},backgroundsSpaceship);
                    break;
                case 22:
                    scale = scale/8;
                    gridStartingPoint.x = 0;
                    gridStartingPoint.y = 0;
                    grid.setOrigin(gridStartingPoint.x, gridStartingPoint.y);
                    startingScale = scale;
                    mode = Mode::TilePlacer;
                    break;

            }



           // Mix_PlayChannel(-1,effectGlassRinging,0);




           if(advance != 10) {
               if (advance == 12) {
                   phase = 0;
               }
               if (advance <= 20){
                   RenderPlayer();
           }


           }else{
               phase = startAnim/4;

               if(phase == 16){
                   SwitchPlayerAnimation(PlayerState::Idle_Flip);
                   phase = 0;
                   startAnim = 0;
                   advance++;
               }else {
                   renderFromSpritesheet(pChar.rect, playerStabSheetFlip, &clips32[phase % 16]);
                   if(phase == 3 || phase == 6 || phase == 12) {
                       renderFromSpritesheet(turtle, objectPackageOpenSheet, &clips32[1]);
                       Mix_PlayChannel(-1,effectPackageOpen,0);
                   }
               }
               startAnim++;

           }

           // AnimateTargets();
           if(showGrid){
               grid.render(renderer());
           }
        }
        if(mode == Mode::TilePlacer) {

            if(tTracker.placeTileMode){
                SDL_SetRenderDrawColor(renderer(), 50, 50, 50, 255);
                SDL_RenderClear(renderer());
                Texture * t = textToTexture("TILE PLACER MODE\n"
                                            "G: Show/Hide Grid \n"
                                            "LEFTMOUSE: Select\n"
                                            "RIGHTMOUSE: Place\n"
                                            "U: Walls MODE\n"
                                            "O: Object MODE\n"
                                            "C: Characters MODE\n"
                                            "H: Hide/Show this Info");
                if(tTracker.infoToggle) {
                    renderText(grid.tiles[0][4].rect, t);
                }
                SDL_DestroyTexture(t);
                t = nullptr;
            }


            if(tTracker.manageWallsMode){
                SDL_SetRenderDrawColor(renderer(), 100, 0, 0, 255);
                SDL_RenderClear(renderer());
                if(tTracker.infoToggle) {
                    Texture *t = textToTexture(
                            "WALL SELECT MODE\n"
                            "G: Show/Hide Grid \n"
                            "LEFTMOUSE: Select\n"
                            "RIGHTMOUSE: Place\n"
                            "Activate Wall placement with WASD\n"
                            "Press U to Switch to DOOR Select\n"
                            "CONFIRM or T: back to tile only mode\n"
                            "H:hide Info ");
                    renderText(grid.tiles[0][4].rect, t);
                    SDL_DestroyTexture(t);
                    t = nullptr;
                }


            }
            if(tTracker.manageDoorsMode){
                SDL_SetRenderDrawColor(renderer(), 0, 100, 0, 255);
                SDL_RenderClear(renderer());
                if(tTracker.infoToggle) {
                    Texture *t = textToTexture(
                            "DOOR SELECT MODE\n"
                            "G: Show/Hide Grid \n"
                            "LEFTMOUSE: Select\n"
                            "RIGHTMOUSE: Place\n"
                            "Activate DOOR placement with WASD \n"
                            "U: Switch to WALL Select \n"
                            "CONFIRM or T: back to tile only mode\n H:hide Info");
                    renderText(grid.tiles[0][4].rect, t);
                    SDL_DestroyTexture(t);
                    t = nullptr;
                }
            }
            if(tTracker.placeObjectMode){
                SDL_SetRenderDrawColor(renderer(), 100, 100, 150, 255);
                SDL_RenderClear(renderer());
                if(tTracker.infoToggle) {
                    Texture *t = textToTexture(
                            "OBJECT SELECT MODE\n"
                            "G: Show/Hide Grid \n"
                            "LEFTMOUSE: Select\n"
                            "RIGHTMOUSE: Place\n"
                            "T:Return to Tile Placer Mode \n"
                            "H:hide Info");
                    renderText(grid.tiles[0][4].rect, t);
                    SDL_DestroyTexture(t);
                    t = nullptr;
                }
            }
            if(tTracker.placeCharacterMode){
                SDL_SetRenderDrawColor(renderer(), 50, 30, 150, 255);
                SDL_RenderClear(renderer());
                if(tTracker.infoToggle) {
                    Texture *t = textToTexture(
                            "CHARACTER SELECT MODE\n"
                            "G:Show/Hide Grid \n"
                            "LEFTMOUSE: Select\n"
                            "RIGHTMOUSE: Place\n"
                            "T:Return to Tile Placer Mode \n"
                            "H:hide Info");
                    renderText(grid.tiles[0][4].rect, t);
                    SDL_DestroyTexture(t);
                    t = nullptr;
                }
            }
            if (showGrid) {
                grid.render(renderer());
            }

            if (tTracker.placeTileMode) {
                int j = 0; // next y pos
                for (int i =0;i<=static_cast<int>(FloorTileIDs::Floor2);i++) {
                    RenderFloorTile(static_cast<FloorTileIDs>(i),grid.tiles[i][0].rect);
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
            if (tTracker.placeCharacterMode) {
                int j = 0; // next y pos
                for (auto a: characterSprites) {
                    for (int i = 0; i < 1; i++) {
                        renderFromSpritesheet(grid.tiles[j][i].rect, a, &clips32[0]);
                    }
                    j++;
                }
            }

            for (auto a: grid.tiles) {
                for (auto b: a) {
                    if (b.style != FloorTileIDs::NONE && b.onGrid) {
                        RenderFloorTile(b.style, b.rect);
                        RenderWalls(b.rect,b.walls);
                        RenderDoors(b.rect,b.doors);
                        RenderObjectSprites(b.object,b.rect);
                        RenderCharacterSprites(b.rect,b.character);
                    }
                }
            }
            grid.hover(renderer());

            SDL_Rect selectionVisualizer = {mousePosition.x, mousePosition.y, 64, 64};

            renderFromSpritesheet(selectionVisualizer, tilesDoors, &clips32[tTracker.selectedDoors]);
            renderFromSpritesheet(selectionVisualizer, tilesWalls, &clips32[tTracker.selectedWalls]);

            selectionVisualizer.x = selectionVisualizer.x + 64;
            if(tTracker.placeObjectMode) {
                RenderObjectSprites(tTracker.currentObject, selectionVisualizer);
            }
            if(tTracker.placeCharacterMode){
                RenderCharacterSprites(selectionVisualizer,tTracker.currentCharacter);
            }
            if(tTracker.placeTileMode){
                RenderFloorTile(tTracker.currentFloorSprite, selectionVisualizer);
            }
            if(tTracker.isPlayerShipTile){
                RenderCharacterSprites( selectionVisualizer,CharacterIDs::PlayerCharacter);
            }


        }
        if(mode == Mode::Game) {


            for (auto a: grid.tiles) {
                for (auto b: a) {
                    if (b.style != FloorTileIDs::NONE) {
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
        using enum CharacterIDs;
        using enum CharacterAnimations;


        ///TODO add more animations for types
        switch(a.type){
            case CharacterIDs::PlayerCharacter: switch(a.currentAnimation){
                case CharacterAnimations::Idle: a.loop = true; a.nextAnimation = CharacterAnimations::Idle; return playerIdleSheet;break;
                case Aim: a.loop = false; a.nextAnimation = Fire; return playerDamageKnockdownSheet;break;
                case Fire: a.loop = false; a.nextAnimation = Idle; return playerGetUpSheet;break;
                default: return playerIdleSheet;break;
            }
                case CharacterIDs::Orc: switch(a.currentAnimation){
                    case CharacterAnimations::Idle: a.loop = true; a.nextAnimation= Idle; return characterOrcIdleSheet;
                    case Aim: break;
                    case Fire: break;
                    //TODO test Player Ship load/save; build enemy and load onto same map
                }
            default: return playerDamageKnockdownSheet;
        }
    }

    void STR_State::SwitchPlayerAnimation(PlayerState sheet){
        using enum PlayerState;
        pChar.state = sheet;




        switch(sheet){
            case Idle: playerAnimation = playerIdleSheet; loopAnimation = true;nextState = Idle;break;
            case Idle_Flip: playerAnimation = playerIdleSheetFlip;loopAnimation = true;nextState = Idle_Flip;break;
            case Walk: playerAnimation = playerWalkSheet;loopAnimation = false;nextState = Idle;break;
            case Walk_Flip: playerAnimation = playerWalkSheetFlip;loopAnimation = true;nextState = Idle_Flip;break;
            case Damage: playerAnimation = playerDamageSheet;loopAnimation = true; nextState = Idle;break;
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

    void STR_State::RenderFloorTile(FloorTileIDs s, SDL_Rect t){
        using enum FloorTileIDs;
        switch(s){
            case NONE:
                break;
            case Standard:
                renderFromSpritesheet(t,tileStandard,&clips32[0]);break;
            case Round:
                renderFromSpritesheet(t,tileCircle,&clips32[0]);break;
            case Grass0:
                renderFromSpritesheet(t,tileGrassSheet,&clips32[0]);break;
            case Grass1:
                renderFromSpritesheet(t,tileGrassSheet,&clips32[1]);break;
            case Grass2:
                renderFromSpritesheet(t,tileGrassSheet,&clips32[2]);break;
            case Grass3:
                renderFromSpritesheet(t,tileGrassSheet,&clips32[3]);break;
            case Grass4:
                renderFromSpritesheet(t,tileGrassSheet,&clips32[4]);break;
            case Grass5:
                renderFromSpritesheet(t,tileGrassSheet,&clips32[5]);break;
            case Grass6:
                renderFromSpritesheet(t,tileGrassSheet,&clips32[6]);break;
            case Grass7:
                renderFromSpritesheet(t,tileGrassSheet,&clips32[7]);break;
            case TopWalls0:
                renderFromSpritesheet(t,tileTopWallsSheet,&clips32[0]);break;
            case TopWalls1:
                renderFromSpritesheet(t,tileTopWallsSheet,&clips32[1]);break;
            case TopWalls2:
                renderFromSpritesheet(t,tileTopWallsSheet,&clips32[2]);break;
            case TopWalls3:
                renderFromSpritesheet(t,tileTopWallsSheet,&clips32[3]);break;
            case TopWalls4:
                renderFromSpritesheet(t,tileTopWallsSheet,&clips32[4]);break;
            case TopWalls5:
                renderFromSpritesheet(t,tileTopWallsSheet,&clips32[5]);break;
            case Floor0:
                renderFromSpritesheet(t,tileFloor2Sheet,&clips32[0]);break;
            case Floor1:
                renderFromSpritesheet(t,tileFloor2Sheet,&clips32[1]);break;
            case Floor2:
                renderFromSpritesheet(t,tileFloor2Sheet,&clips32[2]);break;
            default: break;
        }

    }
    void STR_State::RenderObjectSprites(ObjectIDs o, SDL_Rect t){
        using enum ObjectIDs;
        switch(o) {
            case Shot:
                renderFromSpritesheet(t, objectShot, &clips32[1]);
                break;

            default:
                break;
        }
    }
    void STR_State::RenderCharacterSprites(SDL_Rect t, CharacterIDs c){
        using enum CharacterIDs;
        switch(c) {
            case CharacterIDs::PlayerCharacter:
                renderFromSpritesheet(t, playerIdleSheet, &clips32[0]);
                break;
            case Orc: renderFromSpritesheet(t, characterOrcIdleSheet, &clips32[0]);
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

    Grid STR_State::loadOffsetMap(const std::string& filename, int offsetX, int offsetY) {

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for reading!\n";
            return grid;
        }
        String output = "";
        std::string line;

        int i = 0;

        for (auto &a: grid.tiles) {
            std::getline(file, line);
            if(i != 0) {
                output.append("\n");
            }
            for (auto &b: a) {
                if(b.x >59){
                    break;
                }
                if(b.y >32){
                    break;
                }

                size_t closingPos = line.find(']'); // Find the first closing
                // Extract string before closing
                std::string tileString = (closingPos != std::string::npos) ? line.substr(0, closingPos+1) : line;
                line.erase(0, closingPos + 1);//erase the processed tile from big string

                //get the values from the file
                Vector<int> values = processTileString(tileString);
                output.append(std::to_string(i));
                i++;
                output.append("[");
                for(auto v : values){
                    output.append( std::to_string(v));
                    output.append(",");
                }
                // Remove the last comma if output is not empty
                if (!output.empty()) {
                    output.pop_back();
                }

                output.append( "]");
                int y = b.y + offsetY;
                int x = b.x + offsetX;

                if(values[0] != 0) {
                    grid.tiles[y][x].onGrid = values[0];
                    grid.tiles[y][x].style = static_cast<FloorTileIDs>(values[1]);
                    grid.tiles[y][x].walls = values[2];
                    grid.tiles[y][x].doors = values[3];
                    grid.tiles[y][x].object = static_cast<ObjectIDs>(values[4]);
                    grid.tiles[y][x].character = static_cast<CharacterIDs>(values[5]);
                    if (grid.tiles[y][x].character != CharacterIDs::NONE ||
                        grid.tiles[y][x].object != ObjectIDs::NONE) {
                        grid.tiles[y][x].occupied = true;
                    }
                }

            }
        }
        std::cout << output;
        NFD::Window     nw = nativeWindow();
        NFD::UniquePath path;
        const NFD::Result result = NFD::SaveDialog( path, NFD::EmptyFilter, 0, "/home/max/CLionProjects/SpaceTimeRogue/src/example/game/Tilemaps/", "newFile.txt", nw ); // Freezes execution of the Game
        if (result == NFD::Result::NFD_OKAY) {
            std::ofstream outFile(path.get());  // Create and open the file
            if (outFile) {
                outFile << output;  // Write the string to the file
                outFile.close();
                std::cout << "File saved successfully: " << path.get() << std::endl;
            } else {
                std::cerr << "Error creating file at: " << path.get() << std::endl;
            }
        } else if (result == NFD::Result::NFD_CANCEL) {
            std::cout << "User canceled the save dialog.\n";
        } else {
            std::cerr << "Error opening save dialog.\n";
        }

        return grid;
    }

    Grid STR_State::loadTilemap(const std::string& filename) {

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for reading!\n";
            return grid;
        }
        String output = "";
        std::string line;

        int i = 0;

        for (auto &a: grid.tiles) {
            std::getline(file, line);
            if(i != 0) {
                output.append("\n");
            }
            for (auto &b: a) {
                if(b.x >59){
                    break;
                }
                if(b.y >32){
                    break;
                }

                size_t closingPos = line.find(']'); // Find the first closing
                // Extract string before closing
                std::string tileString = (closingPos != std::string::npos) ? line.substr(0, closingPos+1) : line;
                line.erase(0, closingPos + 1);//erase the processed tile from big string

                //get the values from the file
               Vector<int> values = processTileString(tileString);
                output.append(std::to_string(i));
                i++;
                output.append("[");
               for(auto v : values){
                   output.append( std::to_string(v));
                   output.append(",");
               }
                // Remove the last comma if output is not empty
                if (!output.empty()) {
                    output.pop_back();
                }

                output.append( "]");

               b.onGrid = values[0];
               b.style = static_cast<FloorTileIDs>(values[1]);
               b.walls = values[2];
               b.doors = values[3];
               b.object = static_cast<ObjectIDs>(values[4]);
               b.character = static_cast<CharacterIDs>(values[5]);
               if(b.character != CharacterIDs::NONE || b.object != ObjectIDs::NONE){
                   b.occupied = true;
               }

            }
        }
        std::cout << output;
        NFD::Window     nw = nativeWindow();
        NFD::UniquePath path;
        const NFD::Result result = NFD::SaveDialog( path, NFD::EmptyFilter, 0, "/home/max/CLionProjects/SpaceTimeRogue/src/example/game/Tilemaps/", "newFile.txt", nw ); // Freezes execution of the Game
        if (result == NFD::Result::NFD_OKAY) {
            std::ofstream outFile(path.get());  // Create and open the file
            if (outFile) {
                outFile << output;  // Write the string to the file
                outFile.close();
                std::cout << "File saved successfully: " << path.get() << std::endl;
            } else {
                std::cerr << "Error creating file at: " << path.get() << std::endl;
            }
        } else if (result == NFD::Result::NFD_CANCEL) {
            std::cout << "User canceled the save dialog.\n";
        } else {
            std::cerr << "Error opening save dialog.\n";
        }

        return grid;
    }


    String STR_State::SavePlayerShip(std::vector<std::vector<Tile>>&t){
        String output;
        String temp;
        int i = 0;
        for (auto a : t){
            output.append("\n");
            for(auto b : a){

                if(b.x >59){
                    break;
                }
                if(b.y >32){
                    break;
                }
                output.append(std::to_string(i));
                i++;
                //open tile
                output.append("[");
                //if has tile
                if(!b.onGrid) {
                    output.append("0,0,0,0,0,0]");
                }else {
                    if(b.isPlayerShipTile) {
                        output.append("1,");
                        //save tile style
                        temp = std::to_string(static_cast<int>(b.style));
                        output.append(temp);
                        output.append(",");
                        //save walls
                        temp = std::to_string(b.walls);
                        output.append(temp);
                        output.append(",");
                        //save doors
                        temp = std::to_string(b.doors);
                        output.append(temp);
                        output.append(",");
                        //save object
                        temp = std::to_string(static_cast<int>(b.object));
                        output.append(temp);
                        output.append(",");
                        //save character
                        temp = std::to_string(static_cast<int>(b.character));
                        output.append(temp);
                        output.append("]");
                    }else{output.append("0,0,0,0,0,0]");}

                }

            }
        }
        std::cout << output;
        return output;
    }
    String STR_State::SaveMap(std::vector<std::vector<Tile>>&t){
        String output;
        String temp;
        int i = 0;
        for (auto a : t){
            output.append("\n");
            for(auto b : a){

                if(b.x >59){
                    break;
                }
                if(b.y >32){
                    break;
                }
                output.append(std::to_string(i));
                i++;
                //open tile
                output.append("[");
                //if has tile
                if(!b.onGrid) {
                    output.append("0,0,0,0,0,0]");
                }else {
                    output.append("1,");
                    //save tile style
                    temp = std::to_string(static_cast<int>(b.style));
                    output.append(temp);
                    output.append(",");
                    //save walls
                    temp = std::to_string(b.walls);
                    output.append(temp);
                    output.append(",");
                    //save doors
                    temp = std::to_string(b.doors);
                    output.append(temp);
                    output.append(",");
                    //save object
                    temp = std::to_string(static_cast<int>(b.object));
                    output.append(temp);
                    output.append(",");
                    //save character
                    temp = std::to_string(static_cast<int>(b.character));
                    output.append(temp);
                    output.append("]");

                }

            }
        }
        std::cout << output;
        return output;
    }

    std::vector<int> STR_State::processTileString(std::string str) {
        std::vector<int> values;

        // Remove the first bracket '['
        /*
        if (!str.empty() && str[0] == '[') {
            str.erase(0, 1);
            line.erase(0, closingPos + 1);
        }
         */
        if(!str.empty()){
            size_t openPos = str.find('['); // Find the first comma
            str.erase(0,openPos+1);
        }

        while (!str.empty()) {
            size_t commaPos = str.find(','); // Find the first comma

            // Extract number before the comma (or entire string if no comma)
            std::string numberStr = (commaPos != std::string::npos) ? str.substr(0, commaPos) : str;

            // Convert to integer and store it
            values.push_back(std::stoi(numberStr));

            // Remove the processed number and comma
            if (commaPos != std::string::npos) {
                str.erase(0, commaPos + 1);  // Also removes the comma
            } else {
                //quick fix
                break; // Stop if no more commas
            }
        }

        return values;
    }
    void STR_State::RenderPlayerBubbleText(const String& text,playerCharacter &pChar){
        SDL_Rect playerBubble1 = {(pChar.rect.x+pChar.rect.w/2),pChar.rect.y-pChar.rect.h,pChar.rect.w,pChar.rect.h};
        SDL_Rect playerBubble2 = playerBubble1;
        playerBubble2.x = playerBubble2.x + pChar.rect.w;
        renderFromSpritesheet(playerBubble1,uiSpeechbubbleSheet,&clips32[12]);
        renderFromSpritesheet(playerBubble2,uiSpeechbubbleSheet,&clips32[13]);
        Texture * texture = textToTexture(text.c_str());
        playerBubble1.y = playerBubble1.y;
        playerBubble1.x = playerBubble1.x+40;
        renderText(playerBubble1,
                   texture,20);
        SDL_DestroyTexture(texture);
        texture = nullptr;
        //do bark audio if not played already; reset playedBark when appropriate in player
        if(!pChar.playedBark){
            Mix_PlayChannel(-1,effectPlayerBark,0);
            pChar.playedBark = true;
        }
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