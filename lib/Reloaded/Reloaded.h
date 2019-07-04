//#include "../hwlib/library/hwlib.hpp"
#include <hwlib.hpp>
#include <stdint-gcc.h>
#include "pixel.h"
#include "graphics_drawer.h"

using namespace hwlib;
class Reloaded : public hwlib::window {
private:
    unsigned int size_x;
    unsigned int size_y;
    pixel matrix[64][32];
    port_out_from_pins_t color_port1;
    port_out_from_pins_t color_port2;
    port_out_from_pins_t util_port;
    port_out_from_pins_t select_port;

    uint8_t current_row = 0;

    virtual void write_implementation(hwlib::xy pos, hwlib::color col);

    void clock_low(), clock_high();
    void latch_low(), latch_high();
    void oe_low(), oe_high();
    void write_util(), write_select();
    void timer(unsigned int freq);

    bool r, g, b;
    uint_fast8_t rgb;

    updating_drawable* drawables[128];

public:
    unsigned int util;
    unsigned int select;
    virtual void flush();
    void fill(bool r = false, bool g = false, bool b = false);
    virtual void clear();

    void lock(unsigned int freq);

    Reloaded(hwlib::xy size, hwlib::color foreground, hwlib::color background,
             target::pins red1,   target::pins green1,      target::pins blue1,
             target::pins red2,   target::pins green2,      target::pins blue2,
             target::pins a,      target::pins b,           target::pins c,   target::pins d,
             target::pins clock,  target::pins latch,       target::pins oe)
        : hwlib::window(size, foreground, background), size_x(size.x), size_y(size.y), matrix{{},{}}, util(0), select(0)
    {
        auto red_pin1 = target::pin_out(red1);
        auto green_pin1 = target::pin_out(green1);
        auto blue_pin1 = target::pin_out(blue1);
        auto red_pin2 = target::pin_out(red2);
        auto green_pin2 = target::pin_out(green2);
        auto blue_pin2 = target::pin_out(blue2);

        color_port1 = port_out_from(red_pin1, green_pin1, blue_pin1);
        color_port2 = port_out_from(red_pin2, green_pin2, blue_pin2);

        auto a_pin = target::pin_out(a);
        auto b_pin = target::pin_out(b);
        auto c_pin = target::pin_out(c);
        auto d_pin = target::pin_out(d);
        auto clock_pin = target::pin_out(clock);
        auto latch_pin = target::pin_out(latch);
        auto oe_pin = target::pin_out(oe);

        util_port = port_out_from(clock_pin, latch_pin, oe_pin);
        select_port = port_out_from(a_pin, b_pin, c_pin, d_pin);
    };



    void begin();

    void drawPixel(unsigned int x, unsigned int y, bool r = false, bool g = false, bool b = false);
    void update();
};