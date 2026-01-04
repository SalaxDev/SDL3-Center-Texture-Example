#include "wcWindow.hpp"
#include <cstdio>

#include "msg_helper.hpp"

// Alias Name 
using wcw = wcWindow ;

// Window Structure
wcw::WindowSize::WindowSize(cint width, cint height) noexcept 
    : width(width), height(height) {
}

// Private Functions
bool wcw::initSettings() {
    if (bInitFailed) {
        return false ;
    }
    
    
    // Initialize Section
    // Initialize Window and Renderer
    wnd = SDL_CreateWindow(title, wndSize.width, wndSize.height, SDL_WINDOW_RESIZABLE) ;
    if (!wnd) {
        msg::logerr("Create Window", SDL_GetError()) ;
        return false ;
    }
    
    rnd = SDL_CreateRenderer(wnd, nullptr) ;
    if (!rnd) {
        msg::logerr("Create Renderer", SDL_GetError()) ;
        return false ;
    }
    
    // Allocating Space to link names to one buffer
    const int tempBufferSize = strlen(fontPath) + strlen(fontName) + 2 ;
    char *tempBuffer = new char[tempBufferSize] ;
    snprintf(tempBuffer, tempBufferSize, "%s/%s", fontPath, fontName) ;
    
    
    // Opening Font
    p_comicFont = TTF_OpenFont(tempBuffer, nFontSize) ;
    if (!p_comicFont) {
        msg::logerr("Open Comic font", SDL_GetError()) ;
        return false ;
    }
    
    // Allocating & Creating text
    p_surface = TTF_RenderText_Blended(p_comicFont, displayText, strlen(displayText), textureTextColor) ;
    if (p_surface) {
        textureTextRect.w = p_surface->w ;
        textureTextRect.h = p_surface->h ;
        printf("p_surface: [w: %d] [h: %d]\n", p_surface->w, p_surface->h) ;
        printf("textureTextRect: [w: %f] [h: %f]\n", textureTextRect.w, textureTextRect.h) ;
        p_textureText = SDL_CreateTextureFromSurface(rnd, p_surface) ;
        if (!p_textureText) { // in case of texture text fails
            msg::logerr("Create Texture From Surface", SDL_GetError()) ;
        }
        
        // Cleaning up surface
        SDL_DestroySurface(p_surface) ;
        p_surface = nullptr ;
    } else { // in case of surface text fails
        msg::logerr("Create Surface Texture Text", SDL_GetError()) ;
    }
    
    
    delete[] tempBuffer ;
    tempBuffer = nullptr ; // Cleanup
    
    if (SDL_GetWindowSize(wnd, &wndSize.width, &wndSize.height)) {
        textureTextRect = {
            (wndSize.width - textureTextRect.w) / 2.f,
            (wndSize.height - textureTextRect.h) / 2.f,
            textureTextRect.w, textureTextRect.h
        };
    }
    
    
    // Renderer Settings
    SDL_SetRenderDrawColor(rnd, renderColor.r, renderColor.g, renderColor.b, renderColor.a) ;
    return true ;
}


// Render Functions
void wcw::update() {
    while(SDL_PollEvent(&evn)) {
        // Event Updater
        switch(evn.type) {
            case SDL_EVENT_QUIT: {
                bRunning = false ;
                break ;
            }
            
            // Key Events
            case SDL_EVENT_KEY_DOWN: {
                switch(evn.key.scancode) {
                    case SDL_SCANCODE_ESCAPE: {
                        bRunning = false ;
                        break ;
                    }
                    
                    default: {
                        break ;
                    }
                }
                break ;
            }
            
            // Listening For Window Change event
            case SDL_EVENT_WINDOW_RESIZED: {
                if (SDL_GetWindowSize(wnd, &wndSize.width, &wndSize.height)) {
                    textureTextRect = {
                        (wndSize.width - textureTextRect.w) / 2.f,
                        (wndSize.height - textureTextRect.h) / 2.f,
                        textureTextRect.w, textureTextRect.h
                    };
                } else {
                    msg::logerr("Get Window Size", SDL_GetError()) ;
                }
                break ;
            }
            
            default: {
                break ;
            }
            
        } // End Event Updater
    }
    
}

void wcw::render() {
    SDL_RenderClear(rnd) ;
    
    if (p_textureText) {
        SDL_RenderTexture(rnd, p_textureText, nullptr, &textureTextRect) ;
    }
    
    SDL_RenderPresent(rnd) ;
}


// Constructor
wcw::wcWindow(const WindowSize windowSize, cstrc title, cstrc displayText, cint framerate, cbool limitFramerate)
    : wndSize(windowSize), title(title), displayText(displayText), bLimitFramerate(limitFramerate) {
    setFramerate(framerate) ;
    // SDL3 Video Initialization
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        bInitFailed = true ;
        msg::logerr("Initialize SDL Video", SDL_GetError()) ;
        return ;
    }
    
    // Font Initialization
    if (!TTF_Init()) {
        bInitFailed = true ;
        msg::logerr("Init SDL Font", SDL_GetError()) ;
        return ;
    }
    
    
}


// Destructor
wcw::~wcWindow() {
    if (p_textureText) {
        SDL_DestroyTexture(p_textureText) ;
        p_textureText = nullptr ;
    }
    
    if (p_surface) {
        SDL_DestroySurface(p_surface) ;
    }
    
    if (p_comicFont) {
        TTF_CloseFont(p_comicFont) ;
        p_comicFont = nullptr ;
    }
    
    if (rnd) {
        SDL_DestroyRenderer(rnd) ;
        rnd = nullptr ;
    }
    
    if (wnd) {
        SDL_DestroyWindow(wnd) ;
        wnd = nullptr ;
    }
    
    
    
    TTF_Quit() ;
    SDL_Quit() ;
}

// Setters
wcw &wcw::setFramerate(cint frame, cbool limitFramerate) noexcept {
    if (frame > 0) {
        framerate = frame ;
    } else {
        puts("Framerate Can't be lower or equal to 0\n") ;
    }
    return *this ;
}

wcw &wcw::LimitFramerate(cbool limitFramerate) noexcept {
    bLimitFramerate = limitFramerate ;
    
    return *this ;
}

wcw &wcw::setWindowSize(const WindowSize windowSize) noexcept {
    if (bIsInited) {
        SDL_SetWindowSize(wnd, windowSize.width, windowSize.height) ;
    }
    wndSize = windowSize ;
    return *this ;
}

wcw &wcw::setWindowTitle(cstrc title) noexcept {
    if (!bIsInited) {
        this->title = title ;
    } else {
        if (wnd) {
            SDL_SetWindowTitle(wnd, title) ;
        }
    }
    
    return *this ;
}

wcw &wcw::setFontSize(cint size) noexcept {
    if (size <= 0) {
        puts("Font Size can't be lower than 1!\n") ;
    } else if (size > 200) {
        puts("Font Size can't be upper than 200!\n") ;
    } else {
        nFontSize = size ;
    }
    
    return *this ;
}

wcw &wcw::setFontPath(cstrc fontPath, cstrc fontName) noexcept {
    this->fontPath = fontPath ;
    this->fontName = fontName ;
    return *this ;
}

wcw &wcw::setBackgroundColor(const SDL_Color color) noexcept {
    if (bIsInited && rnd) {
        SDL_SetRenderDrawColor(rnd, color.r, color.g, color.b, color.a) ;
        this->renderColor = color ;
    } else {
        this->renderColor = color ;
    }
    
    return *this ;
}

wcw &wcw::setDisplayText(cstrc text) noexcept {
    displayText = text ;
    return *this ;
}

wcw &wcw::setTextureTextColor(const SDL_Color color) noexcept {
    this->textureTextColor = color ;
    return *this ;
}

// Functions
wcw &wcw::init() {
    if (!initSettings()) {
        bInitFailed = true ;
        return *this ;
    }
    
    bIsInited = true ;
    return *this ;
}

void wcw::run() {
    if (bInitFailed) {
        msg::logerr("Initialize Program", SDL_GetError(), true) ;
        return ;
    }
    
    if (!bIsInited) {
        puts("Class is not inited yet, run init function before running.\n") ;
        return ;
    }
    
    
    while (bRunning) {
        update() ;
        render() ;
    }
}