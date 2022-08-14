#ifndef TKTEMOTEJOY_MAPPING_H
#define TKTEMOTEJOY_MAPPING_H

#include "tktemotejoy/pspstate.h"

#include <linux/joystick.h>
#include <map>
#include <memory>
#include <cstddef>

class Mapping
{
public:
    class HandlerForPspState
    {
    public:
        virtual ~HandlerForPspState(
        ) = 0;

        virtual void operator()(
            const __s16
            , PspState &
        ) const = 0;
    };

    using HandlerForPspStateUnique = std::unique_ptr< HandlerForPspState >;

    using HandlersForPspState = std::map<
        std::size_t
        , HandlerForPspStateUnique
    >;

    class HandlerForChangeMapping
    {
    public:
        virtual ~HandlerForChangeMapping(
        ) = 0;

        virtual std::size_t operator()(
            const __s16
            , std::size_t &
            , const std::size_t
        ) const = 0;
    };

    using HandlerForChangeMappingUnique = std::unique_ptr< HandlerForChangeMapping >;

    using HandlersForChangeMapping = std::map<
        std::size_t
        , HandlerForChangeMappingUnique
    >;

private:
    HandlersForPspState pressButtonHandlersForPspState;
    HandlersForPspState operateAxisHandlersForPspState;

    HandlersForChangeMapping    pressButtonHandlersForChangeMapping;
    HandlersForChangeMapping    operateAxisHandlersForChangeMapping;

public:
    void setPressButtonHandler(
        const HandlersForPspState::key_type
        , HandlersForPspState::mapped_type &&
    );

    void setPressButtonHandler(
        const HandlersForChangeMapping::key_type
        , HandlersForChangeMapping::mapped_type &&
    );

    void setOperateAxisHandler(
        const HandlersForPspState::key_type
        , HandlersForPspState::mapped_type &&
    );

    void setOperateAxisHandler(
        const HandlersForChangeMapping::key_type
        , HandlersForChangeMapping::mapped_type &&
    );

    void pressButton(
        const HandlersForPspState::key_type
        , PspState &
    ) const;

    std::size_t pressButton(
        const HandlersForChangeMapping::key_type
        , std::size_t &
        , const std::size_t
    ) const;

    void operateAxis(
        const HandlersForPspState::key_type
        , const __s16
        , PspState &
    ) const;

    std::size_t operateAxis(
        const HandlersForChangeMapping::key_type
        , const __s16
        , std::size_t &
        , const std::size_t
    ) const;
};

#endif  // TKTEMOTEJOY_MAPPING_H
