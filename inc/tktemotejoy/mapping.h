#ifndef TKTEMOTEJOY_MAPPING_H
#define TKTEMOTEJOY_MAPPING_H

#include "tktemotejoy/pspstate.h"

#include <linux/joystick.h>
#include <vector>
#include <map>  //REMOVEME
#include <memory>
#include <cstddef>

class Mapping final
{
public:
    class PressButtonHandlerForPspState
    {
    public:
        virtual ~PressButtonHandlerForPspState(
        ) = 0;

        virtual void operator()(
            PspState &
        ) const = 0;
    };

    using PressButtonHandlerForPspStateUnique = std::unique_ptr< PressButtonHandlerForPspState >;

    using PressButtonHandlersForPspState = std::vector< PressButtonHandlerForPspStateUnique >;

    class OperateAxisHandlerForPspState
    {
    public:
        virtual ~OperateAxisHandlerForPspState(
        ) = 0;

        virtual void operator()(
            const __s16
            , PspState &
        ) const = 0;
    };

    using OperateAxisHandlerForPspStateUnique = std::unique_ptr< OperateAxisHandlerForPspState >;

    using OperateAxisHandlersForPspState = std::vector< OperateAxisHandlerForPspStateUnique >;

    class PressButtonHandlerForChangeMapping
    {
    public:
        virtual ~PressButtonHandlerForChangeMapping(
        ) = 0;

        virtual std::size_t operator()(
            std::size_t &
            , const std::size_t
        ) const = 0;
    };

    using PressButtonHandlerForChangeMappingUnique = std::unique_ptr< PressButtonHandlerForChangeMapping >;

    using PressButtonHandlersForChangeMapping = std::vector< PressButtonHandlerForChangeMappingUnique >;

    class OperateAxisHandlerForChangeMapping
    {
    public:
        virtual ~OperateAxisHandlerForChangeMapping(
        ) = 0;

        virtual std::size_t operator()(
            const __s16
            , std::size_t &
            , const std::size_t
        ) const = 0;
    };

    using OperateAxisHandlerForChangeMappingUnique = std::unique_ptr< OperateAxisHandlerForChangeMapping >;

    using OperateAxisHandlersForChangeMapping = std::map<
        std::size_t
        , OperateAxisHandlerForChangeMappingUnique
    >;

    inline static auto handlerUnique(
        PressButtonHandlerForPspState * _handler
    )
    {
        return PressButtonHandlerForPspStateUnique( _handler );
    }

    inline static auto handlerUnique(
        OperateAxisHandlerForPspState * _handler
    )
    {
        return OperateAxisHandlerForPspStateUnique( _handler );
    }

    inline static auto handlerUnique(
        PressButtonHandlerForChangeMapping *    _handler
    )
    {
        return PressButtonHandlerForChangeMappingUnique( _handler );
    }

    inline static auto handlerUnique(
        OperateAxisHandlerForChangeMapping *    _handler
    )
    {
        return OperateAxisHandlerForChangeMappingUnique( _handler );
    }

private:
    PressButtonHandlersForPspState      pressButtonHandlersForPspState;
    PressButtonHandlersForChangeMapping pressButtonHandlersForChangeMapping;
    OperateAxisHandlersForPspState      operateAxisHandlersForPspState;
    OperateAxisHandlersForChangeMapping operateAxisHandlersForChangeMapping;

public:
    Mapping(
        //TODO ボタン数、軸数を指定する
    );

    void setHandler(
        const PressButtonHandlersForPspState::size_type
        , PressButtonHandlersForPspState::value_type &&
    );

    void setHandler(
        const PressButtonHandlersForChangeMapping::size_type
        , PressButtonHandlersForChangeMapping::value_type &&
    );

    void setHandler(
        const OperateAxisHandlersForPspState::size_type
        , OperateAxisHandlersForPspState::value_type &&
    );

    void setHandler(
        const OperateAxisHandlersForChangeMapping::key_type
        , OperateAxisHandlersForChangeMapping::mapped_type &&
    );

    void pressButton(
        const PressButtonHandlersForPspState::size_type
        , PspState &
    ) const;

    std::size_t pressButton(
        const PressButtonHandlersForChangeMapping::size_type
        , std::size_t &
        , const std::size_t
    ) const;

    void operateAxis(
        const OperateAxisHandlersForPspState::size_type
        , const __s16
        , PspState &
    ) const;

    std::size_t operateAxis(
        const OperateAxisHandlersForChangeMapping::key_type
        , const __s16
        , std::size_t &
        , const std::size_t
    ) const;
};

#endif  // TKTEMOTEJOY_MAPPING_H
