#include <hwlib.hpp>
#include "../lib/Reloaded/Reloaded.h"
#include "config.h"
#include "../include/hwlib/library/hwlib-all.hpp"

int main() {
    // wait for terminal
    hwlib::wait_ms(2000);

    hwlib::target::pins red1 = hwlib::target::pins::d22;
    hwlib::target::pins green1 = hwlib::target::pins::d23;
    hwlib::target::pins blue1 = hwlib::target::pins::d24;
    hwlib::target::pins red2 = hwlib::target::pins::d26;
    hwlib::target::pins green2 = hwlib::target::pins::d27;
    hwlib::target::pins blue2 = hwlib::target::pins::d28;
    hwlib::target::pins a = hwlib::target::pins::d32;
    hwlib::target::pins b = hwlib::target::pins::d33;
    hwlib::target::pins c = hwlib::target::pins::d34;
    hwlib::target::pins d = hwlib::target::pins::d35;
    hwlib::target::pins clock = hwlib::target::pins::d38;
    hwlib::target::pins latch = hwlib::target::pins::d39;
    hwlib::target::pins oe = hwlib::target::pins::d40;

    hwlib::circle inner_circle(hwlib::xy(13, 15), 10);
    hwlib::circle outer_circle(hwlib::xy(13, 15), 11);

    Reloaded matrix(hwlib::xy(64,32), hwlib::color(1,0,1), hwlib::color(0,0,0), red1, green1, blue1, red2, green2, blue2, a, b, c, d, clock, latch, oe);

    matrix.begin();
    unsigned int loop_count = 0;
    unsigned int i = 0;
    for (;;) {
        if (i == 100) {
            if (loop_count < 37) {
                inner_circle.start.x += 1;
                outer_circle.start.x += 1;
                loop_count += 1;
            } else if (loop_count < 37 * 2) {
                inner_circle.start.x -= 1;
                outer_circle.start.x -= 1;
                loop_count += 1;
            } else {
                loop_count = 0;
                inner_circle.start.x += 1;
                outer_circle.start.x += 1;
                loop_count += 1;
            }
            i = 0;
        }
        inner_circle.draw(matrix);
        outer_circle.draw(matrix);


        matrix.update();
        matrix.clear();
        ++i;
    }
}