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
        int width, height ;
        WindowSize(cint width = {}, cint height = {}) noexcept ;
    };

    //SDL3 Variables
    SDL_Window *wnd = nullptr ;
    SDL_Renderer *rnd = nullptr ;
    SDL_Event evn ;
    
    // Text Variables
    SDL_Texture *p_textureText = nullptr ;
    SDL_Surface *p_surface = nullptr ;
    TTF_Font *p_comicFont = nullptr ;
    SDL_FRect textureTextRect ;
    SDL_Color textureTextColor {} ;
    
    cstr fontPath = "./Data/Fonts" ;
    cstr fontName = "ComicRelief-Regular.ttf" ;
    int nFontSize = 24 ;
    
    
    // Settings
    cstr title ;
    cstr displayText ;
    
    int framerate ;
    bool bLimitFramerate ;
    bool bIsInited = false ;
    bool bInitFailed = false ;
    bool bRunning = true ;
    WindowSize wndSize ;
    
    SDL_Color renderColor {60, 60, 60, 255} ;
    
    // Private Functions
    bool initSettings() ;
    
    // Render Functions
    void update() ;
    void render() ;
public:
    // Constructor
    wcWindow(const WindowSize windowSize = {}, cstrc title = "Default Title Name", cstrc displayText = "Hello, World!", cint framerate = 60, cbool limitFramerate = true) ;
    
    // Destructor
    ~wcWindow() ;
    
    // Setters
    wcWindow &setFramerate(cint frame, cbool limitFramerate = true) noexcept ;
    wcWindow &LimitFramerate(cbool limitFramerate) noexcept ;
    wcWindow &setWindowSize(const WindowSize windowSize) noexcept ;
    wcWindow &setWindowTitle(cstrc title) noexcept ;
    wcWindow &setFontSize(cint size) noexcept ;
    wcWindow &setFontPath(cstrc fontPath, cstrc fontName) noexcept ;
    wcWindow &setBackgroundColor(const SDL_Color color) noexcept ;
    wcWindow &setDisplayText(cstrc text) noexcept ;
    wcWindow &setTextureTextColor(const SDL_Color color) noexcept ;
    
    // Functions
    wcWindow &init() ; // Initialize SDL3 Settings and variables
    void run() ; 
};

#endif // WCWINDOW_HPP
