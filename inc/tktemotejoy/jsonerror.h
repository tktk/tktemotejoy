#ifndef TKTEMOTEJOY_JSONERROR_H
#define TKTEMOTEJOY_JSONERROR_H

#include <stdexcept>
#include <string>

template< typename ARG_T >
void jsonError(
    std::ostringstream &    _oStringStream
    , const ARG_T &         _ARG
)
{
    _oStringStream << _ARG;
}

template<
    typename ARG_T
    , typename ... ARGS_T
>
void jsonError(
    std::ostringstream &    _oStringStream
    , const ARG_T &         _ARG
    , const ARGS_T & ...    _ARGS
)
{
    _oStringStream << _ARG << '.';

    jsonError(
        _oStringStream
        , _ARGS ...
    );
}

template< typename ... ARGS_T >
std::runtime_error jsonError(
    const std::string &     _WHAT
    , const ARGS_T & ...    _ARGS
)
{
    auto    oStringStream = std::ostringstream();

    jsonError(
        oStringStream
        , _ARGS ...
    );

    oStringStream << _WHAT;

    return std::runtime_error( oStringStream.str() );
}

template< typename ... ARGS_T >
std::runtime_error jsonIsNotExists(
    const ARGS_T & ...  _ARGS
)
{
    return jsonError(
        "が存在しない"
        , _ARGS ...
    );
}

template< typename ... ARGS_T >
std::runtime_error jsonIsNotInteger(
    const ARGS_T & ...  _ARGS
)
{
    return jsonError(
        "の値が整数ではない"
        , _ARGS ...
    );
}

template< typename ... ARGS_T >
std::runtime_error jsonIsNotUnsigned(
    const ARGS_T & ...  _ARGS
)
{
    return jsonError(
        "の値が符号なし整数ではない"
        , _ARGS ...
    );
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
