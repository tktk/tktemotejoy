#ifndef TKTEMOTEJOY_GENERATEHANDLER_GENERATEOPERATEAXISHANDLERFORCHANGEMAPPINGTEST_H
#define TKTEMOTEJOY_GENERATEHANDLER_GENERATEOPERATEAXISHANDLERFORCHANGEMAPPINGTEST_H

#include "tktemotejoy/test.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
#include <cstddef>
#include <string>
#include <utility>

template< typename GENERATE_HANDLER_UNIQUE_T >
class GenerateOperateAxisHandlerForChangeMappingTestTmpl_new : public ::testing::Test
{
public:
    void test(
        const std::string &     _JSON_STRING
        , const MappingNames &  _MAPPING_NAMES
        , const __s32           _VALUE
        , const std::size_t     _MAPPING_INDEX
        , const std::size_t     _EXPECTED_MAPPING_INDEX
        , const std::size_t     _EXPECTED_NEW_MAPPING_INDEX
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()(
            JSON
            , _MAPPING_NAMES
        );
        ASSERT_NE( nullptr, handlerUnique.get() );

        auto    mapping = Mapping(
            0
            , 1
        );

        mapping.setHandler(
            0
            , std::move( handlerUnique )
        );

        auto        mappingIndex = _MAPPING_INDEX;
        const auto  CURRENT_MAPPING_INDEX = mappingIndex;

        EXPECT_EQ(
            _EXPECTED_NEW_MAPPING_INDEX
            , mapping.operateAxis(
                0
                , _VALUE
                , mappingIndex
                , CURRENT_MAPPING_INDEX
            )
        );

        EXPECT_EQ( _EXPECTED_MAPPING_INDEX, mappingIndex );
    }

    void testAnyThrow(
        const std::string &     _JSON_STRING
        , const MappingNames &  _MAPPING_NAMES
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        EXPECT_ANY_THROW(
            GENERATE_HANDLER_UNIQUE_T()(
                JSON
                , _MAPPING_NAMES
            )
        );
    }

    void testNull(
        const std::string &     _JSON_STRING
        , const MappingNames &  _MAPPING_NAMES
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        const auto  HANDLER_UNIQUE = GENERATE_HANDLER_UNIQUE_T()(
            JSON
            , _MAPPING_NAMES
        );
        ASSERT_EQ( nullptr, HANDLER_UNIQUE.get() );
    }
};

template< typename GENERATE_HANDLER_UNIQUE_T >
class GenerateOperateAxisHandlerForChangeMappingTestTmpl : public ::testing::Test
{
public:
    void test(
        const std::string & _JSON_STRING
        , const __s32       _VALUE
        , const std::size_t _MAPPING_INDEX
        , const std::size_t _EXPECTED_MAPPING_INDEX
        , const std::size_t _EXPECTED_NEW_MAPPING_INDEX
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()( JSON );
        ASSERT_NE( nullptr, handlerUnique.get() );

        auto    mapping = Mapping(
            0
            , 1
        );

        mapping.setHandler(
            0
            , std::move( handlerUnique )
        );

        auto        mappingIndex = _MAPPING_INDEX;
        const auto  CURRENT_MAPPING_INDEX = mappingIndex;

        EXPECT_EQ(
            _EXPECTED_NEW_MAPPING_INDEX
            , mapping.operateAxis(
                0
                , _VALUE
                , mappingIndex
                , CURRENT_MAPPING_INDEX
            )
        );

        EXPECT_EQ( _EXPECTED_MAPPING_INDEX, mappingIndex );
    }

    void testAnyThrow(
        const std::string &     _JSON_STRING
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        EXPECT_ANY_THROW( GENERATE_HANDLER_UNIQUE_T()( JSON ) );
    }

    void testNull(
        const std::string &     _JSON_STRING
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        const auto  HANDLER_UNIQUE = GENERATE_HANDLER_UNIQUE_T()( JSON );
        ASSERT_EQ( nullptr, HANDLER_UNIQUE.get() );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_GENERATEOPERATEAXISHANDLERFORCHANGEMAPPINGTEST_H
