//
// Created by David Strootman on 3-7-2019.
//

#include "graphics_drawer.h"

void graphics_drawer::draw_all()
{
    // loop over the size of drawables / the size of arbitrary pointer in drawables
    for (unsigned int i = 0; i < sizeof(drawables)/sizeof(drawables[i]); ++i) {
        drawables[i]->update();
        drawables[i]->draw(*this);
    }
}
