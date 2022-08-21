#ifndef TKTEMOTEJOY_JSONERROR_H
#define TKTEMOTEJOY_JSONERROR_H

#include <stdexcept>
#include <string>

template< typename ... ARGS_T >
std::runtime_error jsonError(
    const std::string &     _WHAT
    , const ARGS_T & ...    _ARGS
)
{
    //TODO
    return std::runtime_error( "TODO" );
}

template< typename ... ARGS_T >
std::runtime_error jsonIsNotExists(
    const ARGS_T & ...  _ARGS
)
{
    //TODO
    return std::runtime_error( "TODO" );
/*
    return jsonError(
        "存在しない"
        , _ARGS ...
    );
*/
}

template< typename ... ARGS_T >
std::runtime_error jsonIsNotUnsigned(
    const ARGS_T & ...  _ARGS
)
{
    //TODO
    return std::runtime_error( "TODO" );
/*
    return jsonError(
        "符号なし整数ではない"
        , _ARGS ...
    );
*/
}

template< typename ... ARGS_T >
std::runtime_error jsonIsNotString(
    const ARGS_T & ...  _ARGS
)
{
    //TODO
    return std::runtime_error( "TODO" );
/*
    return jsonError(
        "文字列ではない"
        , _ARGS ...
    );
*/
}

template< typename ... ARGS_T >
std::runtime_error jsonIsNotArray(
    const ARGS_T & ...  _ARGS
)
{
    //TODO
    return std::runtime_error( "TODO" );
/*
    return jsonError(
        "配列ではない"
        , _ARGS ...
    );
*/
}

template< typename ... ARGS_T >
std::runtime_error jsonIsNotObject(
    const ARGS_T & ...  _ARGS
)
{
    //TODO
    return std::runtime_error( "TODO" );
/*
    return jsonError(
        "オブジェクトではない"
        , _ARGS ...
    );
*/
}

#endif  // TKTEMOTEJOY_JSONERROR_H
