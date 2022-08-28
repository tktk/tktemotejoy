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
};

#endif  // TKTEMOTEJOY_JSONTEST_H
