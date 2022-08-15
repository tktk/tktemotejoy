#ifndef TKTEMOTEJOY_PSPSTATE_H
#define TKTEMOTEJOY_PSPSTATE_H

#include <functional>

class PspState
{
public:
    using Bits = unsigned int;

    using Axis = unsigned char;

    using WhenDiff = std::function<
        void (
            const Bits &
        )
    >;

private:
    Bits    bits;

    void press(
        const Bits
    );

public:
    void diff(
        const PspState &
        , const WhenDiff &
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
