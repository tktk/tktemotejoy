#include "tktemotejoy/test.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/joystickstate.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/handler/forpspstate/tobuttons.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisx.h"
#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include <linux/joystick.h>
#include <cstddef>
#include <utility>

namespace {
    class Mappings_joystickStateToPspStateTest : public ::testing::Test
    {
    public:
        void test(
            Mappings &              _mappings
            , const JoystickState & _JOYSTICK_STATE
            , const PspState::Bits  _EXPECTED_BITS
        ) const
        {
            auto    pspState = PspState();

            _mappings.joystickStateToPspState(
                pspState
                , _JOYSTICK_STATE
            );

            const auto  OTHER = PspState();

            auto    calledWhenDiff = false;
            auto    bits = PspState::Bits();

            pspState.diff(
                OTHER
                , [
                    &calledWhenDiff
                    , &bits
                ]
                (
                    const PspState::Bits &  _BITS
                )
                {
                    calledWhenDiff = true;
                    bits = _BITS;
                }
            );

            EXPECT_TRUE( calledWhenDiff );
            EXPECT_EQ( _EXPECTED_BITS, bits );
        }
    };
}

TEST_F(
    Mappings_joystickStateToPspStateTest
    , WithoutChangeMapping
)
{
    auto    mapping = Mapping();

    mapping.setHandler(
        0
        , Mapping::handlerUnique( new ToButtons( 0x000a ) )
    );

    mapping.setHandler(
        1
        , Mapping::handlerUnique( new ToFixedAxisX( 32767 ) )
    );

    mapping.setHandler(
        0
        , Mapping::handlerUnique(
            new ToAxisY(
                0
                , ToAxisYImpl( 100 )
            )
        )
    );

    mapping.setHandler(
        1
        , Mapping::handlerUnique(
            new ToButtonHandlers(
                0
                , ToButtonHandlersImpl(
                    Mapping::handlerUnique( new ToButtons( 0x0c00 ) )
                    , Mapping::handlerUnique( new ToButtons( 0xd000 ) )
                )
            )
        )
    );

    auto    mappingsImpl = Mappings::Impl();
    mappingsImpl.push_back( std::move( mapping ) );

    auto    mappings = Mappings(
        std::move( mappingsImpl )
        , 0
    );

    auto    joystickState = JoystickState(
        10
        , 10
    );

    joystickState.setButtonState(
        0
        , 1
    );

    joystickState.setButtonState(
        1
        , 1
    );

    joystickState.setAxisState(
        0
        , 50
    );

    joystickState.setAxisState(
        1
        , -1
    );

    this->test(
        mappings
        , joystickState
        , 0xbfff0c0a
    );
}

//TODO ShiftMapping
//TODO ToggleMapping
