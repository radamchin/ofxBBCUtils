//
//  AsteroidsLineFont.h
//
//  Created by Adam Hinshaw on 12/6/22.
//

#ifndef AsteroidsLineFont_h
#define AsteroidsLineFont_h

// TODO: Work out method to just get it as points so can be made into stars, and then they know what points the will link too.
//  - a custom linked list, where a point knows its next point?
//  - debug draw by drawign points and lines with arrow head on end.

// Based on: https://github.com/osresearch/vst/blob/master/teensyv/asteroids_font.c

typedef struct {
   uint8_t points[8]; // 4 bits x, 4 bits y
} asteroids_char_t;

#define FONT_UP 0xFE
#define FONT_LAST 0xFF

#define P(x,y) ((((x) & 0xF) << 4) | (((y) & 0xF) << 0))

//------------------------------------------------------------------
const asteroids_char_t asteroids_font[] = {
    ['0' - 0x20] = { P(8,0), P(0,0), P(0,12), P(8,12), P(8,0), P(0,12), FONT_LAST },
   //['0' - 0x20] = { P(0,0), P(8,0), P(8,12), P(0,12), P(0,0), P(8,12), FONT_LAST },
    ['1' - 0x20] = { P(4,12), P(4,0), P(3,2), FONT_LAST },
   //['1' - 0x20] = { P(4,0), P(4,12), P(3,10), FONT_LAST },
    ['2' - 0x20] = { P(0,0), P(8,0), P(8,5), P(0,7), P(0,12), P(8,12), FONT_LAST },
   //['2' - 0x20] = { P(0,12), P(8,12), P(8,7), P(0,5), P(0,0), P(8,0), FONT_LAST },
    ['3' - 0x20] = { P(0,12), P(8,12), P(8,0), P(0,0), FONT_UP, P(0,6), P(8,6), FONT_LAST },
    ['4' - 0x20] = { P(0,0), P(0,6), P(8,6), FONT_UP, P(8,12), P(8,0), FONT_LAST },
    //['4' - 0x20] = { P(0,12), P(0,6), P(8,6), FONT_UP, P(8,12), P(8,0), FONT_LAST },
    ['5' - 0x20] = { P(0,12), P(8,12), P(8,7), P(0,5), P(0,0), P(8,0), FONT_LAST },
   //['5' - 0x20] = { P(0,0), P(8,0), P(8,6), P(0,7), P(0,12), P(8,12), FONT_LAST },
    ['6' - 0x20] = { P(0,0), P(0,12), P(8,12), P(8,7), P(0,5), FONT_LAST },
   // ['6' - 0x20] = { P(0,12), P(0,0), P(8,0), P(8,5), P(0,7), FONT_LAST },
    ['7' - 0x20] = { P(0,0), P(8,0), P(8,6), P(6,12), FONT_LAST },
   // ['7' - 0x20] = { P(0,12), P(8,12), P(8,6), P(4,0), FONT_LAST },
    ['8' - 0x20] = { P(0,0), P(8,0), P(8,12), P(0,12), P(0,0), FONT_UP, P(0,6), P(8,6), },
    ['9' - 0x20] = { P(8,12), P(8,0), P(0,0), P(0,5), P(8,7), FONT_LAST },
    //['9' - 0x20] = { P(8,0), P(8,12), P(0,12), P(0,7), P(8,5), FONT_LAST },
    [' ' - 0x20] = { FONT_LAST },
    ['.' - 0x20] = { P(3,12), P(4,12), FONT_LAST },
    //['.' - 0x20] = { P(3,0), P(4,0), FONT_LAST },
    [',' - 0x20] = { P(2,12), P(4,10), FONT_LAST },
   // [',' - 0x20] = { P(2,0), P(4,2), FONT_LAST },
    ['-' - 0x20] = { P(2,6), P(6,6), FONT_LAST },
    ['+' - 0x20] = { P(1,6), P(7,6), FONT_UP, P(4,9), P(4,3), FONT_LAST },
    ['!' - 0x20] = { P(4,12), P(3,10), P(5,10), P(4,12), FONT_UP, P(4,0), P(4,8), FONT_LAST },
  //  ['!' - 0x20] = { P(4,0), P(3,2), P(5,2), P(4,0), FONT_UP, P(4,4), P(4,12), FONT_LAST },
    ['#' - 0x20] = { P(0,4), P(8,4), P(6,2), P(6,10), P(8,8), P(0,8), P(2,10), P(2,2) },
    ['^' - 0x20] = { P(2,6), P(4,0), P(6,6), FONT_LAST },
    //['^' - 0x20] = { P(2,6), P(4,12), P(6,6), FONT_LAST },
    ['=' - 0x20] = { P(1,4), P(7,4), FONT_UP, P(1,8), P(7,8), FONT_LAST },
    ['*' - 0x20] = { P(0,10), P(4,1), P(8,10), P(0,4), P(8,4), P(0,10), FONT_LAST },
    //['*' - 0x20] = { P(0,0), P(4,12), P(8,0), P(0,8), P(8,8), P(0,0), FONT_LAST },
    ['_' - 0x20] = { P(0,12), P(8,12), FONT_LAST },
    // ['_' - 0x20] = { P(0,0), P(8,0), FONT_LAST },
    ['\\' - 0x20] = { P(0,0), P(8,12), FONT_LAST },
    ['/' - 0x20] = { P(0,12), P(8,0), FONT_LAST },
    ['@' - 0x20] = { P(8,8), P(4,12), P(0,8), P(0,4), P(4,0), P(8,4), P(4,8), P(2,6) },
    //['@' - 0x20] = { P(8,4), P(4,0), P(0,4), P(0,8), P(4,12), P(8,8), P(4,4), P(3,6) },
    ['$' - 0x20] = { P(6,2), P(2,6), P(6,10), FONT_UP, P(4,12), P(4,0), FONT_LAST },
    ['&' - 0x20] = { P(8,12), P(2,0), P(8,3), P(0,8), P(4,12), P(8,8), FONT_LAST },
    //['&' - 0x20] = { P(8,0), P(4,12), P(8,8), P(0,4), P(4,0), P(8,4), FONT_LAST },
    ['[' - 0x20] = { P(6,0), P(2,0), P(2,12), P(6,12), FONT_LAST },
    [']' - 0x20] = { P(2,0), P(6,0), P(6,12), P(2,12), FONT_LAST },
    ['(' - 0x20] = { P(6,0), P(2,4), P(2,8), P(6,12), FONT_LAST },
    [')' - 0x20] = { P(2,0), P(6,4), P(6,8), P(2,12), FONT_LAST },
    ['{' - 0x20] = { P(6,0), P(4,2), P(4,10), P(6,12), FONT_UP, P(2,6), P(4,6), FONT_LAST },
    ['}' - 0x20] = { P(4,0), P(6,2), P(6,10), P(4,12), FONT_UP, P(6,6), P(8,6), FONT_LAST },
    ['%' - 0x20] = { P(0,12), P(8,0), FONT_UP, P(2,2), P(2,4), FONT_UP, P(6,8), P(6,10) },
    // ['%' - 0x20] = { P(0,0), P(8,12), FONT_UP, P(2,10), P(2,8), FONT_UP, P(6,4), P(6,2) },
    ['<' - 0x20] = { P(6,2), P(2,6), P(6,10), FONT_LAST },
    ['>' - 0x20] = { P(2,2), P(6,6), P(2,10), FONT_LAST },
    //['<' - 0x20] = { P(6,0), P(2,6), P(6,12), FONT_LAST },
    //['>' - 0x20] = { P(2,0), P(6,6), P(2,12), FONT_LAST },
    ['|' - 0x20] = { P(4,0), P(4,5), FONT_UP, P(4,6), P(4,12), FONT_LAST },
    [':' - 0x20] = { P(4,9), P(4,7), FONT_UP, P(4,5), P(4,3), FONT_LAST },
    [';' - 0x20] = { P(4,3), P(4,5), FONT_UP, P(4,7), P(1,10), FONT_LAST },
    //[';' - 0x20] = { P(4,9), P(4,7), FONT_UP, P(4,5), P(1,2), FONT_LAST },
    ['"' - 0x20] = { P(2,1), P(2,5), FONT_UP, P(6,1), P(6,5), FONT_LAST },
    //['"' - 0x20] = { P(2,10), P(2,6), FONT_UP, P(6,10), P(6,6), FONT_LAST },
    ['\'' - 0x20] = { P(2,6), P(6,2), FONT_LAST },
    //['\'' - 0x20] = { P(2,6), P(6,10), FONT_LAST },
    ['`' - 0x20] = { P(2,1), P(6,5), FONT_LAST },
    //['`' - 0x20] = { P(2,10), P(6,6), FONT_LAST },
    ['~' - 0x20] = { P(0,7), P(2,5), P(6,7), P(8,5), FONT_LAST },
    //['~' - 0x20] = { P(0,4), P(2,8), P(6,4), P(8,8), FONT_LAST },
    ['?' - 0x20] = { P(0,4), P(4,0), P(8,4), P(4,8), FONT_UP, P(4,11), P(4,12), FONT_LAST },
    //['?' - 0x20] = { P(0,8), P(4,12), P(8,8), P(4,4), FONT_UP, P(4,1), P(4,0), FONT_LAST },
    ['A' - 0x20] = { P(0,12), P(0,4), P(4,0), P(8,4), P(8,12), FONT_UP, P(0,8), P(8,8) },
    // ['A' - 0x20] = { P(0,0), P(0,8), P(4,12), P(8,8), P(8,0), FONT_UP, P(0,4), P(8,4) },
    ['B' - 0x20] = { P(0,0), P(0,12), P(4,12), P(8,10), P(4,6), P(8,2), P(4,0), P(0,0) },
    ['C' - 0x20] = { P(8,0), P(0,0), P(0,12), P(8,12), FONT_LAST },
    ['D' - 0x20] = { P(0,0), P(0,12), P(4,12), P(8,8), P(8,4), P(4,0), P(0,0), FONT_LAST },
    ['E' - 0x20] = { P(8,0), P(0,0), P(0,12), P(8,12), FONT_UP, P(0,6), P(6,6), FONT_LAST },
    ['F' - 0x20] = { P(0,12), P(0,0), P(8,0), FONT_UP, P(0,6), P(6,6), FONT_LAST },
    //['F' - 0x20] = { P(0,0), P(0,12), P(8,12), FONT_UP, P(0,6), P(6,6), FONT_LAST },
    ['G' - 0x20] = { P(6,6), P(8,8), P(8,12), P(0,12), P(0,0), P(8,0), FONT_LAST },
    // ['G' - 0x20] = { P(6,6), P(8,4), P(8,0), P(0,0), P(0,12), P(8,12), FONT_LAST },
    ['H' - 0x20] = { P(0,0), P(0,12), FONT_UP, P(0,6), P(8,6), FONT_UP, P(8,12), P(8,0) },
    ['I' - 0x20] = { P(0,0), P(8,0), FONT_UP, P(4,0), P(4,12), FONT_UP, P(0,12), P(8,12) },
    ['J' - 0x20] = { P(0,8), P(4,12), P(8,12), P(8,0), FONT_LAST },
    // ['J' - 0x20] = { P(0,4), P(4,0), P(8,0), P(8,12), FONT_LAST },
    ['K' - 0x20] = { P(0,0), P(0,12), FONT_UP, P(8,0), P(0,6), P(6,12), FONT_LAST },
    // ['K' - 0x20] = { P(0,0), P(0,12), FONT_UP, P(8,12), P(0,6), P(6,0), FONT_LAST },
    ['L' - 0x20] = { P(8,12), P(0,12), P(0,0), FONT_LAST },
    //   ['L' - 0x20] = { P(8,0), P(0,0), P(0,12), FONT_LAST },
    ['M' - 0x20] = { P(0,12), P(0,0), P(4,6), P(8,0), P(8,12), FONT_LAST },
    //['M' - 0x20] = { P(0,0), P(0,12), P(4,8), P(8,12), P(8,0), FONT_LAST },
    ['N' - 0x20] = { P(0,12), P(0,0), P(8,12), P(8,0), FONT_LAST },
    // ['N' - 0x20] = { P(0,0),  P(0,12), P(8,0), P(8,12), FONT_LAST },
    ['O' - 0x20] = { P(0,0), P(0,12), P(8,12), P(8,0), P(0,0), FONT_LAST },
    ['P' - 0x20] = { P(0,12), P(0,0), P(8,0), P(8,5), P(0,7), FONT_LAST },
    // ['P' - 0x20] = { P(0,0), P(0,12), P(8,12), P(8,6), P(0,5), FONT_LAST },
    ['Q' - 0x20] = { P(0,12), P(0,0), P(8,0), P(8,8), P(0,12), FONT_UP, P(4,8), P(8,12) },
    // ['Q' - 0x20] = { P(0,0), P(0,12), P(8,12), P(8,4), P(0,0), FONT_UP, P(4,4), P(8,0) },
    ['R' - 0x20] = { P(0,12), P(0,0), P(8,0), P(8,5), P(0,7), FONT_UP, P(4,6), P(8,12) },
    // ['R' - 0x20] = { P(0,0), P(0,12), P(8,12), P(8,6), P(0,5), FONT_UP, P(4,5), P(8,0) },
    ['S' - 0x20] = { P(8,2), P(6,0), P(0,0), P(0,5), P(8,7), P(8,12), P(2,12), P(0,10) },
    // ['S' - 0x20] = { P(0,2), P(2,0), P(8,0), P(8,5), P(0,7), P(0,12), P(6,12), P(8,10) },
    ['T' - 0x20] = { P(0,0), P(8,0), FONT_UP, P(4,12), P(4,0), FONT_LAST },
    // ['T' - 0x20] = { P(0,12), P(8,12), FONT_UP, P(4,12), P(4,0), FONT_LAST },
    ['U' - 0x20] = { P(0,0), P(0,10), P(4,12), P(8,10), P(8,0), FONT_LAST },
    // ['U' - 0x20] = { P(0,12), P(0,2), P(4,0), P(8,2), P(8,12), FONT_LAST },
    ['V' - 0x20] = { P(0,0), P(4,12), P(8,0), FONT_LAST },
    // ['V' - 0x20] = { P(0,12), P(4,0), P(8,12), FONT_LAST },
    ['W' - 0x20] = { P(0,0), P(2,12), P(4,8), P(6,12), P(8,0), FONT_LAST },
    //['W' - 0x20] = { P(0,12), P(2,0), P(4,4), P(6,0), P(8,12), FONT_LAST },
    ['X' - 0x20] = { P(0,0), P(8,12), FONT_UP, P(0,12), P(8,0), FONT_LAST },
    ['Y' - 0x20] = { P(0,0), P(4,6), P(8,0), FONT_UP, P(4,6), P(4,12), FONT_LAST },
    // ['Y' - 0x20] = { P(0,12), P(4,6), P(8,12), FONT_UP, P(4,6), P(4,0), FONT_LAST },
    ['Z' - 0x20] = { P(0,0), P(8,0), P(0,12), P(8,12), FONT_UP, P(2,6), P(6,6), FONT_LAST },
    //['Z' - 0x20] = { P(0,12), P(8,12), P(0,0), P(8,0), FONT_UP, P(2,6), P(6,6), FONT_LAST },
};

//------------------------------------------------------------------
class AsteroidsLineFont {
        
public:
    
    ofPath path;
   
    //------------------------------------------------------------------
    int draw_character( char c, int x, int y, int size, ofPath & pth ) {
        
        // Asteroids font only has upper case
        if ('a' <= c && c <= 'z') c -= 'a' - 'A';

        const uint8_t * const pts = asteroids_font[c - ' '].points;
        int next_moveto = 1;

        for(int i = 0 ; i < 8 ; i++) {
            uint8_t delta = pts[i];
            if (delta == FONT_LAST)
                break;
            if (delta == FONT_UP) {
                next_moveto = 1;
                continue;
            }

            unsigned dx = ((delta >> 4) & 0xF) * size;
            unsigned dy = ((delta >> 0) & 0xF) * size;

            if (next_moveto) {
                pth.moveTo(x + dx, y + dy);
            } else {
                pth.lineTo(x + dx, y + dy);
            }

            next_moveto = 0;
        }

        return 12 * size;
    }
    
    //------------------------------------------------------------------
    void draw_string( const std::string & s, int x = 0, int y = 0, int size = 12 ) {
        draw_string(s.c_str(), x, y, size);
    }
    
    //------------------------------------------------------------------
     void draw_string( const char * s, int x = 0, int y = 0, int size = 12 ) {
        
        path.clear();
        path.setMode(ofPath::COMMANDS);
        path.setStrokeColor( ofColor::limeGreen );
        path.setFilled(false);
        path.setStrokeWidth(2);
        // path.setMode(ofPath::POLYLINES);
        // path.newSubPath();
        
        while(*s) {
            char c = *s++;
            x += draw_character(c, x, y, size, path);
        }
        
        path.draw();
    }
    
    
    //------------------------------------------------------------------
    ofPath getPoints( const std::string & ss, int x = 0, int y = 0, int size = 12, ofPath * p = nullptr ) {
        
        if(p == nullptr) {
            p = new ofPath;
        }
    
        p->setMode(ofPath::POLYLINES);
        
        const char * s = ss.c_str();
        while(*s) {
              char c = *s++;
              x += draw_character(c, x, y, size, *p);
        }
        
        return *p;
    }
    
    
};

#endif /* AsteroidsLineFont_h */
