//          Copyright Julian van Doorn 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See copy of license at http://www.boost.org/LICENSE_1_0.txt)

#include <hwlib.hpp>
#pragma once


/**
 * @class updating_drawable
 * @author Julian
 * @date 22/06/17
 * @file updating_drawable.hpp
 * @brief hwlib::drawable implementation with a update function
 */


class updating_drawable : public hwlib::drawable {
private:
public:
    /**
     * @brief Creates an updating_drawable on given position
     * @param start Position to draw at
     */
    updating_drawable(hwlib::xy start): hwlib::drawable(start){};

    /**
     * @brief updating_drawable::draw is called every time the window classes requires the image to be drawn
     * @param w hwlib::window to draw to
     */
    virtual void draw(hwlib::window& w) = 0;

    /**
     * @brief Update is called every frame
     */
    virtual void update(){};
};