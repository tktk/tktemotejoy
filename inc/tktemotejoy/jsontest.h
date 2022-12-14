#ifndef TKTEMOTEJOY_JSONTEST_H
#define TKTEMOTEJOY_JSONTEST_H

#include "tktemotejoy/test.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <stdexcept>

template< typename GET_JSON_T >
class GetJsonTest : public ::testing::Test
{
public:
    template< typename EXPECTED_T >
    void test(
        const std::string &     _JSON_STRING
        , const std::string &   _KEY
        , const EXPECTED_T &    _EXPECTED
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        EXPECT_EQ(
            _EXPECTED
            , GET_JSON_T()(
                JSON
                , _KEY
            )
        );
    }

    void testAnyThrow(
        const std::string &     _JSON_STRING
        , const std::string &   _KEY
        , const std::string &   _PARENT_KEY1
        , const std::string &   _PARENT_KEY2
        , const std::string &   _EXPECTED_WHAT
    )
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        try {
            GET_JSON_T()(
                JSON
                , _KEY
                , _PARENT_KEY1
                , _PARENT_KEY2
            );

            ASSERT_FALSE( true );   // ここに到達してはいけない
        } catch( const std::runtime_error & _EX ) {
            EXPECT_STREQ( _EXPECTED_WHAT.c_str(), _EX.what() );
        }
    }

    void testNull(
        const std::string &     _JSON_STRING
        , const std::string &   _KEY
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        EXPECT_EQ(
            nullptr
            , &(
                GET_JSON_T()(
                    JSON
                    , _KEY
                )
            )
        );
    }
};

template< typename GET_JSON_NOT_REQUIRED_T >
class GetJsonNotRequiredTest : public ::testing::Test
{
public:
    template< typename EXPECTED_PTR_T >
    void test(
        const std::string &     _JSON_STRING
        , const std::string &   _KEY
        , const EXPECTED_PTR_T  _EXPECTED_PTR
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        const auto  JSON_PTR = GET_JSON_NOT_REQUIRED_T()(
            JSON
            , _KEY
        );
        if( _EXPECTED_PTR == nullptr ) {
            EXPECT_EQ( _EXPECTED_PTR, JSON_PTR );
        } else {
            ASSERT_NE( nullptr, JSON_PTR );
            EXPECT_EQ( *_EXPECTED_PTR, *JSON_PTR );
        }
    }

    void testAnyThrow(
        const std::string &     _JSON_STRING
        , const std::string &   _KEY
        , const std::string &   _PARENT_KEY1
        , const std::string &   _PARENT_KEY2
        , const std::string &   _EXPECTED_WHAT
    )
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        try {
            GET_JSON_NOT_REQUIRED_T()(
                JSON
                , _KEY
                , _PARENT_KEY1
                , _PARENT_KEY2
            );

            ASSERT_FALSE( true );   // ここに到達してはいけない
        } catch( const std::runtime_error & _EX ) {
            EXPECT_STREQ( _EXPECTED_WHAT.c_str(), _EX.what() );
        }
    }
};

template< typename GET_JSON_WITH_DEFAULT_T >
class GetJsonWithDefaultTest : public ::testing::Test
{
public:
    template< typename EXPECTED_T >
    void test(
        const std::string &     _JSON_STRING
        , const EXPECTED_T &    _DEFAULT
        , const std::string &   _KEY
        , const EXPECTED_T &    _EXPECTED
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        EXPECT_EQ(
            _EXPECTED
            , GET_JSON_WITH_DEFAULT_T()(
                JSON
                , _DEFAULT
                , _KEY
            )
        );
    }

    template< typename EXPECTED_T >
    void testAnyThrow(
        const std::string &     _JSON_STRING
        , const EXPECTED_T &    _DEFAULT
        , const std::string &   _KEY
        , const std::string &   _PARENT_KEY1
        , const std::string &   _PARENT_KEY2
        , const std::string &   _EXPECTED_WHAT
    )
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        try {
            GET_JSON_WITH_DEFAULT_T()(
                JSON
                , _DEFAULT
                , _KEY
                , _PARENT_KEY1
                , _PARENT_KEY2
            );

            ASSERT_FALSE( true );   // ここに到達してはいけない
        } catch( const std::runtime_error & _EX ) {
            EXPECT_STREQ( _EXPECTED_WHAT.c_str(), _EX.what() );
        }
    }
};

#endif  // TKTEMOTEJOY_JSONTEST_H
