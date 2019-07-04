#include "Reloaded.h"

/*
 * ----------------------
 * COLOR PORT 1
 * B1: Color bit blue top half
 * G1: Color bit green top half
 * R1: Color bit red top half
 *
 * B1G1R1
 * 0 0 0
 *
 * ----------------------
 * COLOR PORT 2
 * B2: Color bit blue bottom half
 * G2: Color bit green bottom half
 * R2: Color bit red bottom half
 *
 * B2G2R2
 * 0 0 0
 *
 * ----------------------
 * SELECT PORT
 * X: Unused (ground)
 * O: OE pin
 * L: Latch pin
 * T: Clock pin
 * D: D pin
 * C: C pin
 * B: B pin
 * A: A pin
 *
 * O L T D C B A
 * 0 0 0 0 0 0 0
 *
 * ----------------------
 */

void Reloaded::write_implementation(hwlib::xy pos, hwlib::color col) {
    matrix[pos.x][pos.y].r = col.red > 0;
    matrix[pos.x][pos.y].g = col.green > 0;
    matrix[pos.x][pos.y].b = col.blue > 0;
};

void Reloaded::clear() {
    fill();
}

void Reloaded::flush() {}

void Reloaded::begin() {
    select = 0;
    color_port1.write(0b000);
    color_port2.write(0b000);

    // set clock high to init empty
    clock_high();
    latch_low();
    oe_low();
    write_util();
}
void Reloaded::lock(const unsigned int freq) {
    timer(freq);
}

void Reloaded::timer(unsigned int freq) {
    while (true) {
        update();
        hwlib::wait_us(1000000 / freq);
    }
}

void Reloaded::fill(bool r, bool g, bool b) {
    for (int x = 0; x < size.x; ++x) {
        for (int y = 0; y < size.y; ++y) {
            matrix[x][y].r = r;
            matrix[x][y].g = g;
            matrix[x][y].b = b;
        }
    }
}

void Reloaded::update() {
    write_select();
    oe_high();
    clock_high();
    write_util();

    // loop r,g,b leds 64 times for 192 * 2 values total
    for (unsigned int i = 0; i < size_x; ++i) {
        // pulse clock to write color
        clock_low();
        write_util();

        r = matrix[i][current_row].r > 0;
        g = matrix[i][current_row].g > 0;
        b = matrix[i][current_row].b > 0;
        rgb = b << 2 | g << 1 | r;

        if (current_row < 16) {
            color_port1.write(rgb);
        } else {
            color_port2.write(rgb);
        }

        clock_high();
        write_util();
    }

    latch_high();
    oe_low();
    write_util();
    latch_low();
    write_util();

    select += 1;
    if (select > 15) {
        select = 0;
    }
    current_row += 1;
    if (current_row > 31) {
        current_row = 0;
    }
}

void Reloaded::write_util() {
    util_port.write(util);
}

void Reloaded::write_select() {
    select_port.write(select % 16);
}

void Reloaded::clock_low() {
    util ^= 0x001;
}

void Reloaded::clock_high() {
    util |= 0b001;
}

void Reloaded::latch_low() {
    util ^= 0b010;
}

void Reloaded::latch_high() {
    util |= 0b010;
}

void Reloaded::oe_low() {
    util ^= 0b100;
}

void Reloaded::oe_high() {
    util |= 0b100;
}

// set OE, CLK to high
// set A, B, C pins
// for ledcount per row * 2  {
// set clock to low, OE, A, B, C stay the same
// set color
// set clock to high, OE, A, B, C stay the same
// }
//digitalWrite(LAT, HIGH);
//digitalWrite(LAT, LOW);
//digitalWrite(OE, LOW);