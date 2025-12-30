#ifndef WCWINDOW_HPP
#define WCWINDOW_HPP

#include <SDL3/SDL.h>

// Aliases
using uint = unsigned int ;
using cuint = const unsigned int ;
using cint = const int ;
using cfloat = const float ;
using cdouble = const double ;
using cstr = const char * ;
using cstrc = const char * const ;
using cbool = const bool ;
// End Aliases

// Word Center Window Manager
class wcWindow {
private:
    // Window Structure
    struct WindowSize {
        uint width, height ;
        WindowSize(cuint width = {}, cuint height = {}) noexcept ;
    };

    //SDL3 Variables
    SDL_Window *wnd = nullptr ;
    SDL_Renderer *rnd = nullptr ;
    
    // Text Variables
    SDL_Texture *p_textureText = nullptr ;
    SDL_Surface *p_surface = nullptr ;
    SDL_FRect textureTextRect ;
    
    
    // Settings
    cstr title ;
    int framerate ;
    bool bLimitFramerate ;
    bool bIsInited ;
    WindowSize wndSize ;
    
    // Private Functions
    void initSettings() ;
    
    // Render Functions
    void update() ;
    void render() ;
public:
    // Constructor
    wcWindow(const WindowSize windowSize = {}, cstrc title = "Default Title Name", cint framerate = 60, cbool limitFramerate = true) ;
    
    // Destructor
    wcWindow &setFramerateLimit(cint frame, cbool limitFramerate = true) noexcept ;
    wcWindow &setLimitFramerate(cbool limitFramerate) noexcept ;
    wcWindow &setWindowSize(const WindowSize windowSize) noexcept ;
    wcWindow &setWindowTitle(cstrc title) noexcept ;
    
    // Functions
    void run() ;
};

#endif // WCWINDOW_HPP
