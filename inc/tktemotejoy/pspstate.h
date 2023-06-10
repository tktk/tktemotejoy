#ifndef TKTEMOTEJOY_PSPSTATE_H
#define TKTEMOTEJOY_PSPSTATE_H

#include <functional>

enum {
    PSPSTATE_BITS_DEFAULT = 0x80800000,
};

class PspState final
{
public:
    enum Button
    {
        UP = 0x0010,
        DOWN = 0x0040,
        LEFT = 0x0080,
        RIGHT = 0x0020,

        CIRCLE = 0x2000,
        CROSS = 0x4000,
        TRIANGLE = 0x1000,
        SQUARE = 0x8000,
        TRIGGER_L = 0x0100,
        TRIGGER_R = 0x0200,
        START = 0x0008,
        SELECT = 0x0001,
    };

    using Bits = unsigned int;

    using Buttons = unsigned short;
    using Axis = unsigned char;

    using WhenDiff = std::function<
        void (
            const Bits &
        )
    >;

private:
    Bits    bits;

public:
    PspState(
    );

    void diff(
        const PspState &
        , const WhenDiff &
    ) const;

    void pressButtons(
        const Buttons
    );

    void operateAxisX(
        const Axis
    );

    void operateAxisY(
        const Axis
    );
};

#endif  // TKTEMOTEJOY_PSPSTATE_H
