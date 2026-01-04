#include "wcWindow.hpp"

int main(int argc, const char** argv) {
    wcWindow window({800, 600}, "Center Texture") ;
    window.setFramerate(144)
    .setTextureTextColor({200, 200, 200, 255})
    .init().run() ;
    
    return 0 ;
}