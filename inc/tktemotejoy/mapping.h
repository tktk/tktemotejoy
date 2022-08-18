#ifndef TKTEMOTEJOY_MAPPING_H
#define TKTEMOTEJOY_MAPPING_H

#include "tktemotejoy/pspstate.h"

#include <linux/joystick.h>
#include <map>
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

    using PressButtonHandlersForPspState = std::map<
        std::size_t
        , PressButtonHandlerForPspStateUnique
    >;

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

    using OperateAxisHandlersForPspState = std::map<
        std::size_t
        , OperateAxisHandlerForPspStateUnique
    >;

    class PressButtonHandlerForChangeMapping
    {
    public:
        virtual ~PressButtonHandlerForChangeMapping(
        ) = 0;

        virtual std::size_t operator()(
            std::size_t &
        ) const = 0;
    };

    using PressButtonHandlerForChangeMappingUnique = std::unique_ptr< PressButtonHandlerForChangeMapping >;

    using PressButtonHandlersForChangeMapping = std::map<
        std::size_t
        , PressButtonHandlerForChangeMappingUnique
    >;

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
    PressButtonHandlersForPspState  pressButtonHandlersForPspState;
    OperateAxisHandlersForPspState  operateAxisHandlersForPspState;

    PressButtonHandlersForChangeMapping pressButtonHandlersForChangeMapping;
    OperateAxisHandlersForChangeMapping operateAxisHandlersForChangeMapping;

public:
    void setHandler(
        const PressButtonHandlersForPspState::key_type
        , PressButtonHandlersForPspState::mapped_type &&
    );

    void setHandler(
        const PressButtonHandlersForChangeMapping::key_type
        , PressButtonHandlersForChangeMapping::mapped_type &&
    );

    void setHandler(
        const OperateAxisHandlersForPspState::key_type
        , OperateAxisHandlersForPspState::mapped_type &&
    );

    void setHandler(
        const OperateAxisHandlersForChangeMapping::key_type
        , OperateAxisHandlersForChangeMapping::mapped_type &&
    );

    void pressButton(
        const PressButtonHandlersForPspState::key_type
        , PspState &
    ) const;

    std::size_t pressButton(
        const PressButtonHandlersForChangeMapping::key_type
        , std::size_t &
        , const std::size_t
    ) const;

    void operateAxis(
        const OperateAxisHandlersForPspState::key_type
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
