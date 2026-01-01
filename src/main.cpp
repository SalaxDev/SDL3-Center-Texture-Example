#include "wcWindow.hpp"

int main(int argc, const char** argv) {
    wcWindow window({800, 600}, "Center Texture") ;
    window.run() ;
    
    return 0 ;
}