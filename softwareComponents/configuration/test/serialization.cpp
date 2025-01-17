#include <catch2/catch.hpp>

#include <configuration/serialization.hpp>
#include <iostream>


namespace {

using namespace rofi::configuration;
using namespace rofi::configuration::roficom;
using namespace rofi::configuration::serialization;
using namespace rofi::configuration::matrices;


TEST_CASE( "UniversalModule – Demo" ) {
    ModuleId idCounter = 0;
    Rofibot bot;
    auto& m1 = bot.insert( UniversalModule( idCounter++, 0_deg, 90_deg,   0_deg ) );
    auto& m2 = bot.insert( UniversalModule( idCounter++, 0_deg,  0_deg, 180_deg ) );
    auto con = m2.connectors()[ 1 ];
    connect( m1.connectors()[ 0 ], con, Orientation::South );
    connect< RigidJoint >( m1.bodies()[ 0 ], { 0, 0, 0 }, identity );
    REQUIRE_NOTHROW( bot.prepare() );

    auto j = serialization::toJSON( bot );
    std::string js_str = j.dump( 4 );

    Rofibot botj = serialization::fromJSON< Rofibot >( j );
    auto j_cpy   = serialization::toJSON( botj );
    std::string js_str_cpy = j_cpy.dump( 4 );

    CHECK( j == j_cpy );
    CHECK( js_str == js_str_cpy );

    REQUIRE( bot.modules().size() == botj.modules().size() );
    REQUIRE( bot.roficoms().size() == botj.roficoms().size() );
    REQUIRE( bot.referencePoints().size() == botj.referencePoints().size() );
    REQUIRE_NOTHROW( botj.prepare() );

    for ( auto& m : bot.modules() ) {
        ModuleId id = m.module->getId();
        CHECK( equals( bot.getModulePosition( id ), botj.getModulePosition( id ) ) );
    }
}

TEST_CASE( "Empty" ) {
    SECTION( "toJSON" ) {
        Rofibot bot;
        auto js = toJSON( bot );

        CHECK( js[ "modules" ].size() == 0 );
        CHECK( js[ "spaceJoints" ].size()  == 0 );
        CHECK( js[ "moduleJoints" ].size() == 0 );
    }

    SECTION( "fromJSON" ) {
        auto js = "{ \"modules\" : [], \"spaceJoints\" : [], \"moduleJoints\" : [] }"_json;

        Rofibot bot = fromJSON< Rofibot >( js );

        CHECK( bot.modules().size() == 0 );
        CHECK( bot.roficoms().size() == 0 );
        CHECK( bot.referencePoints().size() == 0 );
        CHECK( bot.validate( SimpleColision() ).first );
    }
}

TEST_CASE( "Pad" ) {
    ModuleId idCounter = 0;
    Rofibot bot;

    SECTION( "Square pad" ) {
        auto& m1 = bot.insert( Pad( idCounter++, 20 ) );
        connect< RigidJoint >( m1.components()[ 0 ], { 0, 0, 0 }, identity );
    }

    SECTION( "Rectangle pad" ) {
        auto& m1 = bot.insert( Pad( idCounter++, 20, 10 ) );
        connect< RigidJoint >( m1.components()[ 0 ], { 0, 0, 0 }, identity );

    }

    SECTION( "Multiple pads" ) {
        auto& m1 = bot.insert( Pad( idCounter++, 23, 11 ) );
        auto& m2 = bot.insert( Pad( idCounter++, 5 ) );
        auto& m3 = bot.insert( Pad( idCounter++, 1, 10 ) );
        connect< RigidJoint >( m2.components()[ 0 ], { 0, 0, 0 }, identity );
    }

    auto j = toJSON( bot );

    Rofibot cpy = fromJSON< Rofibot >( j );

    REQUIRE_NOTHROW( bot.prepare() );
    REQUIRE_NOTHROW( cpy.prepare() );

    CHECK( bot.roficoms().size() == cpy.roficoms().size() );
    CHECK( bot.modules().size()  == idCounter ); // idCounter is equal to number of modules within the bot
    CHECK( bot.modules().size()  == cpy.modules().size()  );
    CHECK( bot.referencePoints().size() == 1 );
    CHECK( bot.referencePoints().size() == cpy.referencePoints().size() );
    CHECK( j == toJSON( cpy ) );
}

TEST_CASE( "UniversalModule" ) {
    ModuleId idCounter = 0;
    Rofibot bot;

    SECTION( "Single Module" ) {
        auto& m1 = bot.insert( UniversalModule( idCounter++, 90_deg, 90_deg, 180_deg ) );
        connect< RigidJoint >( m1.bodies()[ 0 ], { 0, 0, 0 }, identity );
        auto js = toJSON( bot );

        CHECK( js[ "modules" ][ 0 ][ "0" ][ "alpha" ] == 90 );
        CHECK( js[ "modules" ][ 0 ][ "0" ][ "beta" ]  == 90 );
        CHECK( js[ "modules" ][ 0 ][ "0" ][ "gamma" ] == 180 );
    }


    SECTION( "Signle With rotational joint" ) {
        auto& m1 = bot.insert( UniversalModule( idCounter++, 0_deg, 0_deg, 0_rad ) );
        connect< RotationJoint >( m1.bodies()[ 0 ], Vector{ 0, 0, 0 }
                                , identity, Vector{ 1, 0, 0 }, translate( { 0, 0, 1 } )
                                , Angle::deg( 90 ), Angle::deg( 90 ) );
    }

    SECTION( "Multiple Modules" ) {
        auto& m1 = bot.insert( UniversalModule( idCounter++, 0_deg, 0_deg, 90_deg ) );
        auto& m2 = bot.insert( UniversalModule( idCounter++, 90_deg, 0_deg, 180_deg ) );
        auto& m3 = bot.insert( UniversalModule( idCounter++, 35_deg, 0_deg, 90_deg ) );

        connect( m1.components()[ 2 ], m2.components()[ 2 ], Orientation::North );
        connect( m3.components()[ 2 ], m2.components()[ 5 ], Orientation::South );
        connect< RigidJoint >( m1.bodies()[ 0 ], { 0, 0, 0 }, identity );

        auto js = toJSON( bot );
        CHECK( js[ "modules" ][ 0 ][ "0" ][ "alpha" ] == 0  );
        CHECK( js[ "modules" ][ 0 ][ "0" ][ "beta" ]  == 0  );
        CHECK( js[ "modules" ][ 0 ][ "0" ][ "gamma" ] == 90 );

        CHECK( js[ "modules" ][ 1 ][ "1" ][ "alpha" ] == 90  );
        CHECK( js[ "modules" ][ 1 ][ "1" ][ "beta" ]  == 0   );
        CHECK( js[ "modules" ][ 1 ][ "1" ][ "gamma" ] == 180 );

        CHECK( js[ "modules" ][ 2 ][ "2" ][ "alpha" ] == 35 );
        CHECK( js[ "modules" ][ 2 ][ "2" ][ "beta" ]  == 0  );
        CHECK( js[ "modules" ][ 2 ][ "2" ][ "gamma" ] == 90 );
    }

    SECTION( "The other way" ) {
        auto js = "{ \"modules\" : [\
                                      {\
                                        \"66\" : {\
                                                \"type\"  : \"universal\",\
                                                \"alpha\" : 90,\
                                                \"beta\"  : 0,\
                                                \"gamma\" : 180\
                                            }\
                                      },\
                                      {\
                                        \"42\" : {\
                                            \"type\" : \"universal\",\
                                            \"alpha\" : 0,\
                                            \"beta\"  : 90,\
                                            \"gamma\" : 90\
                                            }\
                                      }\
                    ],\
                          \"moduleJoints\" : [\
                                          {\
                                            \"orientation\" : \"East\",\
                                            \"from\" : 66,\
                                            \"fromCon\" : \"A-Z\",\
                                            \"to\" : 42,\
                                            \"toCon\" : \"B-Z\"\
                                          }\
                    ],\
                            \"spaceJoints\" : [\
                                                {\
                                                      \"point\" : { \"x\" : 0\
                                                                  , \"y\" : 0\
                                                                  , \"z\" : 0\
                                                                },\
                                                      \"to\" : 66,\
                                                      \"toComponent\" : 7,\
                                                      \"joint\" : {\
                                                                       \"type\" : \"rigid\",\
                                                                       \"sourceToDestination\" : [\
                                                                                           [ 1, 0, 0, 0 ]\
                                                                                         , [ 0, 1, 0, 0 ]\
                                                                                         , [ 0, 0, 1, 0 ]\
                                                                                         , [ 0, 0, 0, 1 ]\
                                                                                    ]\
                                                                }\
                                                }\
                            ]\
        }"_json;

        bot = fromJSON< Rofibot >( js );

        CHECK( bot.modules().size() == 2 );
        idCounter++; // to count inserted bots
        auto* m = static_cast< UniversalModule* >( bot.getModule( 66 ) );
        CHECK( m->getAlpha().deg() == 90  );
        CHECK( m->getBeta().deg()  == 0   );
        CHECK( m->getGamma().deg() == 180 );

        idCounter++;
        m = static_cast< UniversalModule* >( bot.getModule( 42 ) );
        CHECK( m->getAlpha().deg() == 0  );
        CHECK( m->getBeta().deg()  == 90 );
        CHECK( m->getGamma().deg() == 90 );
    }

    auto j = toJSON( bot );

    Rofibot cpy = fromJSON< Rofibot >( j );

    REQUIRE_NOTHROW( bot.prepare() );
    REQUIRE_NOTHROW( cpy.prepare() );

    CHECK( bot.roficoms().size() == cpy.roficoms().size() );
    CHECK( bot.modules().size()  == idCounter ); // idCounter is equal to number of modules within the bot
    CHECK( bot.modules().size()  == cpy.modules().size()  );
    CHECK( bot.referencePoints().size() == 1 );
    CHECK( bot.referencePoints().size() == cpy.referencePoints().size() );
    CHECK( j == toJSON( cpy ) );
}

TEST_CASE( "UnknownModule" ) {
    ModuleId idCounter = 0;
    Rofibot bot;

    SECTION( "Basic tests" ) {
        auto& m1 = bot.insert( UnknownModule( { Component{ ComponentType::Roficom }
                                              , Component{ ComponentType::Roficom } }
                                              , 2
                                              , { makeComponentJoint< RigidJoint >( 0, 1, identity ) }
                                              , idCounter++ ) );

        auto js = toJSON( bot );

        CHECK( js[ "modules" ].size() == 1 );
        CHECK( js[ "spaceJoints" ].size()  == 0 );
        CHECK( js[ "moduleJoints" ].size() == 0 );

        CHECK( js[ "modules" ][ 0 ][ "0" ][ "components" ].size() == 2 );
        CHECK( js[ "modules" ][ 0 ][ "0" ][ "components" ][ 0 ][ "type" ] == "roficom" );
        CHECK( js[ "modules" ][ 0 ][ "0" ][ "components" ][ 1 ][ "type" ] == "roficom" );
        CHECK( js[ "modules" ][ 0 ][ "0" ][ "joints" ].size() == 1 );
    }
}

TEST_CASE( "Mixin'" ) {
    Rofibot bot;

    SECTION( "pad + UMs" ) {
        auto& pad = bot.insert( Pad( 42, 10, 8 ) );
        auto& um1 = static_cast< UniversalModule& >( bot.insert( UniversalModule( 66, 0_deg, 0_deg, 180_deg ) ) );
        auto& um2 = static_cast< UniversalModule& >( bot.insert( UniversalModule(  0, 0_deg, 0_deg, 0_deg   ) ) );

        connect( pad.components()[ 0 ], um1.getConnector( "A-Z" ), Orientation::North );
        connect( um1.getConnector( "B-Z" ), um2.getConnector( "A+X" ), Orientation::West );

        auto js = toJSON( bot );
        CHECK( js[ "modules" ].size() == 3 );
        CHECK( js[ "moduleJoints" ].size() == 2 );
        CHECK( js == toJSON( fromJSON< Rofibot >( js ) ) );
    }
}

} // namespace
