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
        string playerIdlePath =  BasePath "/src/example/game/Ressources/Image_assets/entities/player/Idol.png";
        string playerIdleFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/player/Idol_Flip.png";
        string playerWalkPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/player/Walk_Cycle.png";
        string playerWalkFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/player/Walk_Cycle_Flip.png";
        string playerDamagePath =  BasePath "/src/example/game/Ressources/Image_assets/entities/player/Player_Damage-Sheet.png";
        string playerDamageFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/player/Player_Damage_flip-Sheet.png";
        string playerDamageKnockdownPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/player/Player_Damage_Knockout-Sheet.png";
        string playerDamageKnockdownFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/player/Player_Damage_Knockout_flip-Sheet.png";
        string playerKnockdownGetupPath = BasePath "/src/example/game/Ressources/Image_assets/entities/player/Player_Knockout_JumpUp-Sheet.png";
        string playerKnockdownGetupFlipPath =  BasePath "/src/example/game/Ressources/Image_assets/entities/player/Player_Knockout_JumpUp_Flip-Sheet.png";



        //load textures
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


    playerAnimation = playerIdleSheet;
    target = grid.getTile(7,3).rect;
    aManager.addTarget({target,0,EntityType::EnemyType1,EntityAnimations::Aim,EntityAnimations::Fire});


        for(int i = 0; i<8;i++){
            clips32.push_back({i*32,0,32,32});
        }


        playerRect = grid.getTile(3,3).rect;
       // playerRect.y = playerRect.y - playerRect.h/4;
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

        Base::Destroy();
    }

    bool STR_State::HandleEvent( const Event & event )
    {
        switch( event.type )
        {
            case SDL_KEYDOWN:
            {
                const Keysym & what_key = event.key.keysym;

                if( what_key.scancode == SDL_SCANCODE_G && event.key.repeat == 0 )
                {
                    if(showGrid){showGrid = false;}else{showGrid = true;}
                }
                else if( what_key.scancode == SDL_SCANCODE_P && event.key.repeat == 0 )
                {
                    playerSwitchedState = true;
                    count++;
                    if(count >= 12){count = 0;}

                }
                else if( what_key.scancode == SDL_SCANCODE_D && event.key.repeat == 0 )
                {
                    SwitchPlayerAnimation(PlayerState::Walk);
                }
                else if( what_key.scancode == SDL_SCANCODE_F4 && event.key.repeat == 0 )
                {
                    _textmode = (_textmode + 1) % 2;
                }
                else if( what_key.scancode == SDL_SCANCODE_F9 )
                {
                    // crash/shutdown, since State #6 does not exist
                    _game.ReplaceState( MyGS::Invalid );
                }
                else if( what_key.scancode == SDL_SCANCODE_ESCAPE )
                {
                    _game.ReplaceState( MyGS::Intro );
                }
                else
                {
                    return false; // Not handled
                }

                return true; // Confusing control flow: Handled by all but the else case

                break;
            }

            case SDL_MOUSEBUTTONDOWN:
                //game.SetNextState( 1 );
                break;

            default: break;
        }

        return false;
    }

    void STR_State::Update( const u64 frame, const u64 totalMSec, const f32 deltaT )
    {


        if(playerSwitchedState) {
            if (animationFrame >= 7 || state == PlayerState::Idle || state == PlayerState::Idle_Flip) {
                SwitchPlayerAnimation(static_cast<PlayerState>(count));
                playerSwitchedState = false;
                startAnim = 0;
                phase = 0;
                animationFrame = 0;

            }
        }
        if(state == PlayerState::Walk) {
            playerRect.x = playerRect.x + 4;

        }

    }

    void STR_State::Render( const u64 frame, const u64 totalMSec, const f32 deltaTNeeded )
    {
        Point windowSize;
        SDL_GetWindowSize( window(), &windowSize.x, &windowSize.y );

        SDL_SetRenderDrawColor(renderer(), 0, 0, 255, 255);

        SDL_RenderClear(renderer());

        if(showGrid) {
            grid.render(renderer());
        }



        RenderPlayer();

        AnimateTargets();

    }

    void STR_State::RenderPlayer(){


                if(state == PlayerState::Grounded || state == PlayerState::Grounded_Flip) {

                    renderFromSpritesheet(playerRect, playerAnimation, &clips32[7]);
                    animationFrame = 7;

                }else{


                    animationFrame = RenderPlayerAnimation(playerRect, playerAnimation, clips32);

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
// Surface Width/Height should match player width/height otherwise texture needs to be scaled.
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
            state = nextState;
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
        state = sheet;




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