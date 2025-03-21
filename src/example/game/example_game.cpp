#include "example_game.hpp"

namespace JanSordid::SDL_Example
{
	constexpr bool doBenchmark = false;

    // scalingFactor:
    //  -1.0f (or unspecified) for autoscaling,
    //   1.0f for "no" scaling,
    //  integer floating point values for pixel perfect scaling
	MyGame::MyGame()
		: Base( "Example SDL Game", -1.0f, Point { 480*4, 270 *4}, !doBenchmark )
	//	: Base( "Example SDL Game", 1.0f, Point { 1280, 960 }, !doBenchmark )
	{

		AddStates<

                /* IntroState,
                 PlasmaState,
                 SortState,
                 CameraState,
                 ShooterState,
              */
            STR_State>( *this );

		// Set initial State
		PushState( MyGS::Intro );

		IfNotFinal
			SetPerfDrawMode( PerformanceDrawMode::Title );
	}

	bool MyGame::HandleEvent( const Event & event )
	{
		// Global Keybindings, will be checked before the ones in GameState
		if( Base::HandleEvent( event ) )
			return true;

		/*switch( event.type )
		{
			case SDL_KEYDOWN:
			{
				const Keysym & what_key = event.key.keysym;

				if( what_key.scancode == SDL_SCANCODE_1 )
				{
					// Both Game and GameState can change the State,
					// but it will only be changed after the current frame
					ReplaceState( MyGS::Intro );
					return true;
				}
				else if( what_key.scancode == SDL_SCANCODE_2 )
				{
					ReplaceState( MyGS::Plasma );
					return true;
				}
				else if( what_key.scancode == SDL_SCANCODE_3 )
				{
					ReplaceState( MyGS::Ball );
					return true;
				}
				else if( what_key.scancode == SDL_SCANCODE_4 )
				{
					ReplaceState( MyGS::Parallax );
					return true;
				}
				else if( what_key.scancode == SDL_SCANCODE_5 )
				{
					ReplaceState( MyGS::Shooter );
					return true;
				}
				else if( what_key.scancode == SDL_SCANCODE_6 )
				{
					return false;
				}
				else if( what_key.scancode == SDL_SCANCODE_7 )
				{
					ReplaceState( MyGS::Invalid );
					return true;
				}
				break;
			}

			default:
				break;
		}
		 */

		return false;
	}
}

int main( int argc, char * argv [] )
{
	using namespace JanSordid;

	try
	{
		std::ios_base::sync_with_stdio( false );

		SDL_Example::MyGame game;
		return game.Run();
	}
	catch( ... )
	{
		Core::print( "Non-SDL Exception has occurred!\n" );

		// put a breakpoint in this line, to prevent the shell from closing
		return 667;
	}
}
