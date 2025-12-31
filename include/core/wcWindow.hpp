#ifndef WCWINDOW_HPP
#define WCWINDOW_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "type_aliases.hpp"

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
    SDL_Event evn ;
    
    // Text Variables
    SDL_Texture *p_textureText = nullptr ;
    SDL_Surface *p_surface = nullptr ;
    TTF_Font *p_arialFont = nullptr ;
    SDL_FRect textureTextRect ;
    
    cstr fontPath = "./Data/Fonts" ;
    cstr fontName = "ComicRelief-Regular.ttf" ;
    int nFontSize = 24 ;
    
    
    // Settings
    cstr title ;
    
    int framerate ;
    bool bLimitFramerate ;
    bool bIsInited = false ;
    bool bInitFailed = false ;
    bool bRunning = true ;
    WindowSize wndSize ;
    
    // Private Functions
    bool initSettings() ;
    
    // Render Functions
    void update() ;
    void render() ;
public:
    // Constructor
    wcWindow(const WindowSize windowSize = {}, cstrc title = "Default Title Name", cint framerate = 60, cbool limitFramerate = true) ;
    
    // Destructor
    ~wcWindow() ;
    
    // Setters
    wcWindow &setFramerateLimit(cint frame, cbool limitFramerate = true) noexcept ;
    wcWindow &setLimitFramerate(cbool limitFramerate) noexcept ;
    wcWindow &setWindowSize(const WindowSize windowSize) noexcept ;
    wcWindow &setWindowTitle(cstrc title) noexcept ;
    wcWindow &setFontSize(cint size) noexcept ;
    wcWindow &setFontPath(cstrc fontPath, cstrc fontName) noexcept ;
    
    // Functions
    void init() ; // Initialize SDL3 Settings and variables
    void run() ; 
};

#endif // WCWINDOW_HPP
