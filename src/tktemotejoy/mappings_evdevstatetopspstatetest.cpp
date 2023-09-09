#include "tktemotejoy/test.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/evdevstate.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/handler/forpspstate/tobuttons.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisx.h"
#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include "tktemotejoy/handler/forchangemapping/shiftmapping.h"
#include "tktemotejoy/handler/forchangemapping/togglemapping.h"
#include "tktemotejoy/handler/forchangemapping/tobuttonhandlers.h"
#include <cstddef>
#include <functional>
#include <utility>

namespace {
    Mapping generateMapping(
        const std::function< void ( Mapping & ) > & _INITIALIZE_PROC
    )
    {
        auto    mapping = Mapping(
            10
            , 10
        );

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
                        , Mapping::handlerUnique( new ToFixedAxisX( 0xff ) )
                    );

                    _mapping.setHandler(
                        2
                        , Mapping::handlerUnique( new ToggleMapping( 1 ) )
                    );

                    _mapping.setHandler(
                        0
                        , Mapping::handlerUnique(
                            new ToAxisY_old(
                                -100
                                , 100
                                , 0
                                , ToAxisYImpl_old( 100 )
                            )
                        )
                    );

                    _mapping.setHandler(
                        1
                        , Mapping::handlerUnique(
                            new ToButtonHandlersForPspState(
                                -100
                                , 100
                                , 0
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
                                -100
                                , 100
                                , 0
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

    EvdevState generateEvdevState(
    )
    {
        auto    evdevState = EvdevState(
            10
            , 10
        );

        evdevState.setButtonState(
            0
            , 1
        );

        evdevState.setButtonState(
            1
            , 1
        );

        evdevState.setAxisState(
            0
            , 50
        );

        evdevState.setAxisState(
            1
            , -1
        );

        return evdevState;
    }

    class Mappings_evdevStateToPspStateTest : public ::testing::Test
    {
    public:
        void test(
            Mappings &              _mappings
            , const EvdevState &    _EVDEV_STATE
            , const PspState::Bits  _EXPECTED_BITS
        ) const
        {
            auto    pspState = PspState();

            _mappings.evdevStateToPspState(
                pspState
                , _EVDEV_STATE
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
    Mappings_evdevStateToPspStateTest
    , WithoutChangeMapping
)
{
    auto    mappings = generateMappings();

    auto    evdevState = generateEvdevState();

    this->test(
        mappings
        , evdevState
        , 0xc0ff00ba
    );
}

TEST_F(
    Mappings_evdevStateToPspStateTest
    , ChangeMapping
)
{
    auto    mappings = generateMappings();

    auto    evdevState1 = generateEvdevState();

    evdevState1.setButtonState(
        2
        , 1
    );

    this->test(
        mappings
        , evdevState1
        , 0xc0ff00ba
    );

    const auto  EVDEV_STATE2 = generateEvdevState();

    this->test(
        mappings
        , EVDEV_STATE2
        , 0x8080d000
    );
}
