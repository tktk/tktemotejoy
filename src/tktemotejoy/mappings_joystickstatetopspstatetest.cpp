#include "tktemotejoy/test.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/joystickstate.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/handler/forpspstate/tobuttons.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisx.h"
#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include "tktemotejoy/handler/forchangemapping/shiftmapping.h"
#include "tktemotejoy/handler/forchangemapping/togglemapping.h"
#include "tktemotejoy/handler/forchangemapping/tobuttonhandlers.h"
#include <linux/joystick.h>
#include <cstddef>
#include <functional>
#include <utility>

namespace {
    Mapping generateMapping(
        const std::function< void ( Mapping & ) > & _INITIALIZE_PROC
    )
    {
        auto    mapping = Mapping();

        _INITIALIZE_PROC( mapping );

        return mapping;
    }

    Mappings generateMappings(
    )
    {
        auto    mappingsImpl = Mappings::Impl();

        mappingsImpl.emplace_back(
            generateMapping(
                [](
                    Mapping &   _mapping
                )
                {
                    _mapping.setHandler(
                        0
                        , Mapping::handlerUnique( new ToButtons( 0x000a ) )
                    );

                    _mapping.setHandler(
                        1
                        , Mapping::handlerUnique( new ToFixedAxisX( 32767 ) )
                    );

                    _mapping.setHandler(
                        2
                        , Mapping::handlerUnique( new ToggleMapping( 1 ) )
                    );

                    _mapping.setHandler(
                        0
                        , Mapping::handlerUnique(
                            new ToAxisY(
                                0
                                , ToAxisYImpl( 100 )
                            )
                        )
                    );

                    _mapping.setHandler(
                        1
                        , Mapping::handlerUnique(
                            new ToButtonHandlersForPspState(
                                0
                                , ToButtonHandlersForPspStateImpl(
                                    Mapping::handlerUnique( new ToButtons( 0x00b0 ) )
                                    , Mapping::handlerUnique( new ToButtons( 0x0c00 ) )
                                )
                            )
                        )
                    );
                }
            )
        );

        mappingsImpl.emplace_back(
            generateMapping(
                [](
                    Mapping &   _mapping
                )
                {
                    _mapping.setHandler(
                        0
                        , Mapping::handlerUnique( new ToButtons( 0xd000 ) )
                    );

                    _mapping.setHandler(
                        2
                        , Mapping::handlerUnique(
                            new ToButtonHandlersForChangeMapping(
                                0
                                , ToButtonHandlersForChangeMappingImpl(
                                    Mapping::handlerUnique( new ShiftMapping( 2 ) )
                                    , Mapping::handlerUnique( new ShiftMapping( 3 ) )
                                )
                            )
                        )
                    );
                }
            )
        );

        mappingsImpl.emplace_back(
            generateMapping(
                [](
                    Mapping &   _mapping
                )
                {
                    _mapping.setHandler(
                        0
                        , Mapping::handlerUnique( new ToButtons( 0xe000 ) )
                    );
                }
            )
        );


        return Mappings(
            std::move( mappingsImpl )
            , 0
        );
    }

    JoystickState generateJoystickState(
    )
    {
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

        return joystickState;
    }

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
    auto    mappings = generateMappings();

    auto    joystickState = generateJoystickState();

    this->test(
        mappings
        , joystickState
        , 0xbfff00ba
    );
}

TEST_F(
    Mappings_joystickStateToPspStateTest
    , ChangeMapping
)
{
    auto    mappings = generateMappings();

    auto    joystickState1 = generateJoystickState();

    joystickState1.setButtonState(
        2
        , 1
    );

    this->test(
        mappings
        , joystickState1
        , 0xbfff00ba
    );

    const auto  JOYSTICK_STATE2 = generateJoystickState();

    this->test(
        mappings
        , JOYSTICK_STATE2
        , 0x8080d000
    );
}
