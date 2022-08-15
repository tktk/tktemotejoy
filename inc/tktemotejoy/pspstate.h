#ifndef TKTEMOTEJOY_PSPSTATE_H
#define TKTEMOTEJOY_PSPSTATE_H

#include <linux/joystick.h>
#include <functional>

class PspState
{
public:
    using ButtonBits = unsigned int;
    using Axis = unsigned char;

    using WhenDiffButtons = std::function<
        void (
            const ButtonBits &
        )
    >;

    using WhenDiffAxis = std::function<
        void (
            const Axis &
        )
    >;

private:
    ButtonBits  buttonBits;

    Axis    axisX;
    Axis    axisY;

public:
    void diff(
        const PspState &
        , const WhenDiffButtons &
        , const WhenDiffAxis &
        , const WhenDiffAxis &
    ) const;

    void pressUp(
    );

    void pressDown(
    );

    void pressLeft(
    );

    void pressRight(
    );

    void pressCircle(
    );

    void pressCross(
    );

    void pressTriangle(
    );

    void pressSquare(
    );

    void pressTriggerL(
    );

    void pressTriggerR(
    );

    void pressStart(
    );

    void pressSelect(
    );

    void operateAxisX(
        const Axis
    );

    void operateAxisY(
        const Axis
    );
};

#endif  // TKTEMOTEJOY_PSPSTATE_H
