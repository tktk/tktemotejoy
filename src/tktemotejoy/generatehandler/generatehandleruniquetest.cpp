#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <memory>

namespace {
    const auto  TYPENAME = std::string( "TYPENAME" );
    const auto  DIFF_TYPENAME = std::string( "DIFF_TYPENAME" );

    using TestHandlerUnique = std::unique_ptr< int >;

    struct TestGanarateHandlerUnique
    {
        TestHandlerUnique operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return TestHandlerUnique( new int( _OBJECT.at( "key" ).get_ref< const Json::number_integer_t & >() ) );
        }
    };

    struct TestGanarateHandlerWithArgsUnique
    {
        TestHandlerUnique operator()(
            const Json::object_t &
            , const int &           _VALUE
        ) const
        {
            return TestHandlerUnique( new int( _VALUE ) );
        }
    };

    struct GetType
    {
        const std::string & operator()(
        ) const
        {
            return TYPENAME;
        }
    };

    struct GetDiffType
    {
        const std::string & operator()(
        ) const
        {
            return DIFF_TYPENAME;
        }
    };

    class GenerateHandlerUniqueTest : public ::testing::Test
    {
    public:
        template< typename GET_TYPE_T >
        void test(
            const std::string & _JSON_STRING
            , const bool        _HANDLER_EXPECTED_NOT_NULL
            , const int         _EXPECTED
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            auto    handlerUnique = generateHandlerUnique<
                TestHandlerUnique
                , GET_TYPE_T
                , TestGanarateHandlerUnique
            >( JSON );

            if( _HANDLER_EXPECTED_NOT_NULL == true ) {
                ASSERT_NE( nullptr, handlerUnique.get() );
                EXPECT_EQ( _EXPECTED, *handlerUnique );
            } else {
                EXPECT_EQ( nullptr, handlerUnique.get() );
            }
        }

        template< typename GET_TYPE_T >
        void testWithArgs(
            const std::string & _JSON_STRING
            , const int         _ARG_VALUE
            , const bool        _HANDLER_EXPECTED_NOT_NULL
            , const int         _EXPECTED
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            auto    handlerUnique = generateHandlerUnique<
                TestHandlerUnique
                , GET_TYPE_T
                , TestGanarateHandlerWithArgsUnique
            >(
                JSON
                , _ARG_VALUE
            );

            if( _HANDLER_EXPECTED_NOT_NULL == true ) {
                ASSERT_NE( nullptr, handlerUnique.get() );
                EXPECT_EQ( _EXPECTED, *handlerUnique );
            } else {
                EXPECT_EQ( nullptr, handlerUnique.get() );
            }
        }

        template< typename GET_TYPE_T >
        void testAnyThrow(
            const std::string & _JSON_STRING
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto  GENERATE_HANDLER_UNIQUE = [
                &JSON
            ]
            {
                generateHandlerUnique<
                    TestHandlerUnique
                    , GET_TYPE_T
                    , TestGanarateHandlerUnique
                >( JSON );
            };

            EXPECT_ANY_THROW( GENERATE_HANDLER_UNIQUE() );
        }
    };
}

TEST_F(
    GenerateHandlerUniqueTest
    , MatchType
)
{
    this->test< GetType >(
        R"({
    "type" : "TYPENAME",
    "key" : 10
})"
        , true
        , 10
    );
}

TEST_F(
    GenerateHandlerUniqueTest
    , WithArgs
)
{
    this->testWithArgs< GetType >(
        R"({
    "type" : "TYPENAME"
})"
        , 10
        , true
        , 10
    );
}

TEST_F(
    GenerateHandlerUniqueTest
    , NotExistsType
)
{
    this->test< GetType >(
        R"({
    "key" : 10
})"
        , false
        , 0
    );
}

TEST_F(
    GenerateHandlerUniqueTest
    , NotMatchType
)
{
    this->test< GetDiffType >(
        R"({
    "type" : "TYPENAME",
    "key" : 10
})"
        , false
        , 0
    );
}

TEST_F(
    GenerateHandlerUniqueTest
    , FailedNotStringType
)
{
    this->testAnyThrow< GetType >(
        R"({
    "type" : [ "TYPENAME" ],
    "key" : 10
})"
    );
}
