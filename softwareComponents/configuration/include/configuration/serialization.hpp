#include <configuration/rofibot.hpp>
#include <configuration/universalModule.hpp>
#include <configuration/pad.hpp>
#include <configuration/unknownModule.hpp>

#include <nlohmann/json.hpp>

namespace rofi::configuration::serialization {

    inline std::string componentTypeToString( ComponentType c ) {
        switch ( c ) {
            case ComponentType::Roficom:
                return "roficom";
            case ComponentType::UmBody:
                return "UM body";
            case ComponentType::UmShoe:
                return "UM shoe";
            default:
                assert( false && "Unknown component type" );
        }
    }

    inline ComponentType stringToComponentType( const std::string& str ) {
        if ( str == "roficom" )
            return ComponentType::Roficom;
        else if ( str == "UM body" )
            return ComponentType::UmBody;
        else if ( str == "UM shoe" )
            return ComponentType::UmShoe;
        else
            assert( false && "String does not represent a component type" );
    }

    template< typename M >
    M fromJSON( const nlohmann::json& j, ModuleId id );

    template< typename M >
    M fromJSON( const nlohmann::json& j ) {
        assert( j.is_object() && ++j.begin() == j.end() && "json is not a single object" );

        return fromJSON< M >( j.begin().value(), stoi( j.begin().key() ) );
    }

    inline nlohmann::json matrixToJSON( const Matrix& m ) {
        nlohmann::json j = nlohmann::json::array();
        for ( int i = 0; i < 4; i++ )
            j[ i ] = { m( i, 0 ), m( i, 1 ), m( i, 2 ), m( i, 3 ) };

        return j;
    }

    inline Matrix matrixFromJSON( const nlohmann::json& js ) {
        Matrix m;
        for ( int i = 0; i < 4; i++ ) {
            for ( int j = 0; j < 4; j++ ) {
                m( i, j ) = js[ i ][ j ];
            }
        }
        return m;
    }

    inline nlohmann::json jointToJSON( Joint& j ) {
        nlohmann::json res;
        res[ "positions" ] = nlohmann::json::array();
        for ( auto& p : j.positions() )
            res[ "positions" ].push_back( p );

        atoms::visit( j,
            [ &res ]( RigidJoint& rj ) {
                res[ "type" ] = "rigid";
                res[ "sourceToDestination" ] = matrixToJSON( rj.sourceToDest() );
            },
            [ &res ]( RotationJoint& rj ) {
                res[ "type" ] = "rotational";
                res[ "limits" ][ "min" ] = Angle::rad( rj.jointLimits()[ 0 ].first  ).deg();
                res[ "limits" ][ "max" ] = Angle::rad( rj.jointLimits()[ 0 ].second ).deg();;
                res[ "preMatrix" ]  = matrixToJSON( rj.pre() );
                res[ "postMatrix" ] = matrixToJSON( rj.post() );
                res[ "axis" ] = rj.axis();
            }
        );
        return res;
    }

    inline void onUMTranslateDocs( nlohmann::json& j, ModuleType t, int component ) {
        if ( t == ModuleType::Universal && component < 6 )
            j = std::move( UniversalModule::translateComponent( component ) );
        else
            j = component;
    }

    inline nlohmann::json toJSON( const UniversalModule& m ) {
        using namespace nlohmann;
        json j;
        j[ "type"  ] = "universal";
        j[ "alpha" ] = m.getAlpha().deg();
        j[ "beta"  ] = m.getBeta().deg();
        j[ "gamma" ] = m.getGamma().deg();

        return { { std::to_string( m.getId() ), j } };
    }

    template<>
    inline UniversalModule fromJSON( const nlohmann::json& j, ModuleId id ) {
        assert( j[ "type" ] == "universal" );

        Angle alpha = Angle::deg( j[ "alpha" ] );
        Angle beta  = Angle::deg( j[ "beta"  ] );
        Angle gamma = Angle::deg( j[ "gamma" ] );

        return UniversalModule( id, alpha, beta, gamma );
    } 

    inline nlohmann::json toJSON( const Pad& m ) {
        using namespace nlohmann;
        json j;
        j[ "type"   ] = "pad";
        j[ "width"  ] = m.width;
        j[ "height" ] = m.height;

        return { { std::to_string( m.getId() ), j } };
    }

    template<>
    inline Pad fromJSON( const nlohmann::json& j, ModuleId id ) {
        assert( j[ "type" ] == "pad" );
        
        int width  = j[ "width" ];
        int height = j[ "height" ];
        return Pad( id, width, height );
    }

    inline nlohmann::json toJSON( const UnknownModule& m ) {
        using namespace nlohmann;
        json j;

        j[ "type" ] = nullptr;
        
        for ( const auto& c : m.components() ) {
            json js;
            js[ "in"  ] = c.inJoints;
            js[ "out" ] = c.outJoints;
            if ( c.parent )
                js[ "parent" ] = c.parent->getId();
            else
                js[ "parent" ] = nullptr;
            js[ "type" ] = componentTypeToString( c.type );

            j[ "components" ].push_back( js );
        }

        for ( auto& jt : m.joints() ) {
            json js;
            js[ "from" ] = jt.sourceComponent;
            js[ "to"   ] = jt.destinationComponent;
            js[ "joint" ] = jointToJSON( *jt.joint );
            j[ "joints" ].push_back( js );   
        }

        return { { std::to_string( m.getId() ), j } };
    }

    template<>
    inline UnknownModule fromJSON( const nlohmann::json& j, ModuleId id ) {
        assert( j[ "type" ] && "type is not null" );

        std::vector< Component > components;
        std::vector< ComponentJoint > joints;

        for ( const auto& c : j[ "components" ] ) {
            std::vector< int > inJoints  = c[ "in" ];
            std::vector< int > outJoints = c[ "out" ];
            // TODO: Is it necessary to set parrent?
            Module* parent  = nullptr;
            ComponentType t = stringToComponentType( c[ "type" ] );
            components.push_back( Component( t, std::move( inJoints ), std::move( outJoints ) ) );
        }

        for ( const auto& js : j[ "joints" ] ) {
            int source = js[ "from" ];
            int destination = js[ "destination" ];
            Matrix m;
            for ( int i = 0; i < 4; i++ ) {
                m[ i ] = js[ "sourceToDestination" ][ i ];
            }
            if ( js[ "joint"][ "type" ] == "rigid" ) {
                joints.push_back( makeComponentJoint< RigidJoint >( source, destination, m ) );
            } else if ( js[ "joint" ][ "type" ] == "rotational" ) {
                Vector axis;
                for ( int i = 0; i < 4; i++ )
                    axis[ i ] = js[ "joint" ][ "axis" ][ i ];

                joints.push_back( makeComponentJoint< RotationJoint >( source, destination
                                                                     , matrixFromJSON( js[ "joint" ][ "preMatrix" ] )
                                                                     , axis
                                                                     , matrixFromJSON( js[ "joint" ][ "postMatrix" ] )
                                                                     , Angle::deg( js[ "joint" ][ "min" ] )
                                                                     , Angle::deg( js[ "joint" ][ "max" ] ) ) );
            } else {
                assert( false && "Unknown module was given an unknown ComponentJoint" );
            }
        }

        return UnknownModule( components, 0, joints, id, std::nullopt );
    }

    inline nlohmann::json toJSON( const Rofibot& bot ) {
        using namespace nlohmann;
        json res;
        res[ "modules" ] = json::array();
        res[ "moduleJoints" ] = json::array();
        res[ "spaceJoints"   ] = json::array();

        for ( const auto& m : bot.modules() ) {
            json j;
            switch ( m.module->type ) {
                case ModuleType::Universal:
                    j = toJSON( static_cast< const UniversalModule& >( *m.module ) );
                    break;
                case ModuleType::Pad:
                    j = toJSON( static_cast< const Pad& >( *m.module ) );
                    break;
                case ModuleType::Unknown:
                    j = toJSON( static_cast< const UnknownModule& >( *m.module ) );
                    break;
                case ModuleType::Cube:
                default:
                    assert( false && "Unknown type of a module" );
            }

            res[ "modules" ].push_back( j );
        }

        for ( const RoficomJoint& rj : bot.roficoms() ) {
            json j;
            j[ "from" ] = rj.sourceModule;
            j[ "to"   ] = rj.destModule;
            onUMTranslateDocs( j[ "fromCon" ], bot.getModule( rj.sourceModule )->type, rj.sourceConnector );
            onUMTranslateDocs( j[ "toCon" ]  , bot.getModule( rj.destModule )->type  , rj.destConnector );
            j[ "orientation" ] = orientationToString( rj.orientation );
            res[ "moduleJoints" ].push_back( j );
        }

        for ( const SpaceJoint& sj : bot.referencePoints() ) {
            json j;
            j[ "to" ] = sj.destModule;
            onUMTranslateDocs( j[ "toComponent" ], bot.getModule( sj.destModule )->type, sj.destComponent );
            j[ "point" ][ "x" ] = sj.refPoint[ 0 ];
            j[ "point" ][ "y" ] = sj.refPoint[ 1 ];
            j[ "point" ][ "z" ] = sj.refPoint[ 2 ];
            assert( sj.joint.get() && "joint is nullptr" );
            j[ "joint" ] = jointToJSON( *sj.joint );
            res[ "spaceJoints" ].push_back( j );
        }

        return res;
    }

    template<>
    inline Rofibot fromJSON( const nlohmann::json& j ) {
        Rofibot bot;

        for ( int i = 0; i < j[ "modules" ].size(); i++ ) {
            std::string id = j[ "modules" ][ i ].begin().key(); // great...
            auto& jm = j[ "modules" ][ i ];

            if ( jm[ id ][ "type" ] == "universal" )
                bot.insert( fromJSON< UniversalModule >( jm ) );
            else if ( jm[ id ][ "type" ] == "pad" )
                bot.insert( fromJSON< Pad >( jm ) );
            else if ( jm[ id ][ "type" ] == "unknown" )
                bot.insert( fromJSON< UnknownModule >( jm ) );
            else
                assert( false && "Unknown type of a module" );
        }

        for ( const auto& jj : j[ "moduleJoints" ] ) {
            roficom::Orientation o = roficom::stringToOrientation( jj[ "orientation" ] );
            ModuleId sourceModule = jj[ "from" ];
            ModuleId destinationModule = jj[ "to" ];
            int sourceConnector = bot.getModule( sourceModule )->type == ModuleType::Universal
                                  ? UniversalModule::translateComponent( jj[ "fromCon" ].get< std::string >() )
                                  : jj[ "fromCon" ].get< int >();
            int destinationConnector = bot.getModule( destinationModule )->type == ModuleType::Universal
                                       ? UniversalModule::translateComponent( jj[ "toCon" ].get< std::string >() )
                                       : jj[ "toCon" ].get< int >();

            connect( bot.getModule( sourceModule )->connectors()[ sourceConnector ]
                   , bot.getModule( destinationModule )->connectors()[ destinationConnector ]
                   , o );
        }

        for ( const auto& sj : j[ "spaceJoints" ] ) {
            int destinationModule = sj[ "to" ];
            int destinationComponent =
                bot.getModule( destinationModule )->type == ModuleType::Universal && !sj[ "toComponent" ].is_number()
                        ? UniversalModule::translateComponent( sj[ "toComponent" ].get< std::string >() )
                        : sj[ "toComponent" ].get< int >();

            Vector fixedPoint = { sj[ "point" ][ "x" ], sj[ "point" ][ "y" ], sj[ "point" ][ "z" ] };
            if ( sj[ "joint" ][ "type" ] == "rigid" ) {
                connect< RigidJoint >( bot.getModule( destinationModule )->components()[ destinationComponent ]
                                     , fixedPoint, matrixFromJSON( sj[ "joint" ][ "sourceToDestination" ] ) );
            } else if ( sj[ "joint" ][ "type" ] == "rotational" ) {
                auto& jj = sj[ "joint" ];
                std::vector< float > positions = jj[ "positions" ];

                bot.setSpaceJointPosition(
                    connect< RotationJoint >( bot.getModule( destinationModule )->components()[ destinationComponent ]
                                            , fixedPoint
                                            , matrixFromJSON( jj[ "preMatrix" ] )
                                            , Vector{ jj[ "axis" ][ 0 ]
                                                    , jj[ "axis" ][ 1 ]
                                                    , jj[ "axis" ][ 2 ] }
                                            , matrixFromJSON( jj[ "postMatrix" ] )
                                            , Angle::deg( jj[ "limits" ][ "min" ] )
                                            , Angle::deg( jj[ "limits" ][ "max" ] )
                    ), positions
                );
            } else {
                assert( false && "Unknown joint type" );
            }
        }

        return bot;
    }

} // namespace rofi::configuration
