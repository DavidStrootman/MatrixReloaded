//
// Created by David Strootman on 3-7-2019.
//

#ifndef MATRIXRELOADED_GRAPHICS_DRAWER_H
#define MATRIXRELOADED_GRAPHICS_DRAWER_H

#include <hwlib.hpp>
#include "updating_drawable.h"

class graphics_drawer : public hwlib::window {
private:
    updating_drawable* drawables[128];


public:
    graphics_drawer(hwlib::color foreground, hwlib::xy size, hwlib::color background) : hwlib::window(size, foreground, background) {

    };

    void draw_all();
};


#endif //MATRIXRELOADED_GRAPHICS_DRAWER_H

