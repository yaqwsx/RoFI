#pragma once

#include <cassert>
#include <concepts>
#include <functional>
#include <string>
#include <variant>


namespace atoms
{
template < typename T, typename E >
class [[nodiscard]] Result;

namespace detail
{
    template < typename T >
    struct is_result : std::false_type {};
    template < typename T, typename E >
    struct is_result< Result< T, E > > : std::true_type {};
    template < typename T >
    constexpr bool is_result_v = is_result< T >::value;

} // namespace detail

/**
 * \brief A type that holds either a value or an error.
 *
 * The usecase is similar to that of `std::optional` except
 * it can hold additional info about the failure.
 *
 * The `Result` class template is designed to be an almost drop-in replacement
 * for `std::optional` except the construction.
 */
template < typename T, typename E = std::string >
class [[nodiscard]] Result {
public:
    using value_type = T;
    using error_type = E;

    /// Constructing static member functions

    /**
     * \brief Constructs the contained value by the copy constructor.
     */
    static constexpr Result value( const value_type & val )
    {
        return emplace_value( val );
    }
    /**
     * \brief Constructs the contained value by the move constructor.
     */
    static constexpr Result value( value_type && val )
    {
        return emplace_value( std::move( val ) );
    }
    /**
     * \brief Constructs the contained value in-place.
     */
    static constexpr Result emplace_value( auto &&... args )
    {
        return Result( std::in_place_index_t< 0 >{}, std::forward< decltype( args ) >( args )... );
    }

    /**
     * \brief Constructs the contained error by the copy constructor.
     */
    static constexpr Result error( const error_type & err )
    {
        return emplace_error( err );
    }
    /**
     * \brief Constructs the contained error by the move constructor.
     */
    static constexpr Result error( error_type && err )
    {
        return emplace_error( std::move( err ) );
    }
    /**
     * \brief Constructs the contained error in-place.
     */
    static constexpr Result emplace_error( auto &&... args )
    {
        return Result( std::in_place_index_t< 1 >{}, std::forward< decltype( args ) >( args )... );
    }

    /// Observers

    /**
     * \brief Checks whether `*this` contains a value.
     *
     * \retval true if `*this` contains a value.
     * \retval false if `*this` contains an error.
     */
    constexpr bool has_value() const noexcept
    {
        return _data.index() == 0;
    }
    /**
     * \brief Checks whether `*this` contains a value.
     *
     * \retval true if `*this` contains a value.
     * \retval false if `*this` contains an error.
     */
    constexpr operator bool() const noexcept
    {
        return has_value();
    }

    /// Accessors

    /**
     * \brief Accesses the contained value.
     *
     * \returns Pointer to the contained value.
     */
    constexpr value_type * operator->() noexcept
    {
        assert( has_value() );
        return &assume_value();
    }
    /**
     * \brief Accesses the contained value.
     *
     * \returns Pointer to the contained value.
     */
    constexpr const value_type * operator->() const noexcept
    {
        assert( has_value() );
        return &assume_value();
    }
    /**
     * \brief Accesses the contained value.
     *
     * \returns Reference to the contained value.
     */
    constexpr value_type & operator*() & noexcept
    {
        assert( has_value() );
        return assume_value();
    }
    /**
     * \brief Accesses the contained value.
     *
     * \returns Reference to the contained value.
     */
    constexpr const value_type & operator*() const & noexcept
    {
        assert( has_value() );
        return assume_value();
    }
    /**
     * \brief Accesses the contained value.
     *
     * \returns Reference to the contained value.
     */
    constexpr value_type && operator*() && noexcept
    {
        assert( has_value() );
        return std::move( assume_value() );
    }

    /**
     * \brief Assume that the result contains a value.
     *
     * \returns Reference to the contained value.
     */
    constexpr value_type & assume_value() & noexcept
    {
        assert( has_value() );
        return *std::get_if< 0 >( &_data );
    }
    /**
     * \brief Assume that the result contains a value.
     *
     * \returns Reference to the contained value.
     */
    constexpr const value_type & assume_value() const & noexcept
    {
        assert( has_value() );
        return *std::get_if< 0 >( &_data );
    }
    /**
     * \brief Assume that the result contains a value.
     *
     * \returns Reference to the contained value.
     */
    constexpr value_type && assume_value() && noexcept
    {
        return std::move( assume_value() );
    }

    /**
     * \brief Assume that the result contains an error.
     *
     * \returns Reference to the contained error.
     */
    constexpr error_type & assume_error() & noexcept
    {
        assert( !has_value() );
        return *std::get_if< 1 >( &_data );
    }
    /**
     * \brief Assume that the result contains an error.
     *
     * \returns Reference to the contained error.
     */
    constexpr const error_type & assume_error() const & noexcept
    {
        assert( !has_value() );
        return *std::get_if< 1 >( &_data );
    }
    /**
     * \brief Assume that the result contains an error.
     *
     * \returns Reference to the contained error.
     */
    constexpr error_type && assume_error() && noexcept
    {
        return std::move( assume_error() );
    }

    /// Monadic operations
    ///
    /// Inspired by and designed to be compatible with
    /// monadic operations of `std::optional` from C++23.

    /**
     * \brief Returns the result of invocation of \p f on the contained value if it exists.
     * Otherwise, returns the contained error in the return type.
     *
     * The return type must be a specialization of `Result` with the same error type.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The result of \p f or the contained error.
     */
    template < std::invocable< value_type & > F >
        requires( std::is_copy_constructible_v< error_type > )
    constexpr auto and_then( F && f ) &
    {
        using ResultT = std::remove_cvref_t< std::invoke_result_t< F, value_type & > >;
        static_assert( detail::is_result_v< ResultT >, "F must return a result" );
        static_assert( std::is_same_v< error_type, typename ResultT::error_type >,
                       "error types must be the same" );

        return has_value() ? std::invoke( std::forward< F >( f ), assume_value() )
                           : ResultT::error( assume_error() );
    }
    /**
     * \brief Returns the result of invocation of \p f on the contained value if it exists.
     * Otherwise, returns the contained error in the return type.
     *
     * The return type must be a specialization of `Result` with the same error type.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The result of \p f or the contained error.
     */
    template < std::invocable< const value_type & > F >
        requires( std::is_copy_constructible_v< error_type > )
    constexpr auto and_then( F && f ) const &
    {
        using ResultT = std::remove_cvref_t< std::invoke_result_t< F, const value_type & > >;
        static_assert( detail::is_result_v< ResultT >, "F must return a result" );
        static_assert( std::is_same_v< error_type, typename ResultT::error_type >,
                       "error types must be the same" );

        return has_value() ? std::invoke( std::forward< F >( f ), assume_value() )
                           : ResultT::error( assume_error() );
    }
    /**
     * \brief Returns the result of invocation of \p f on the contained value if it exists.
     * Otherwise, returns the contained error in the return type.
     *
     * The return type must be a specialization of `Result` with the same error type.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The result of \p f or the contained error.
     */
    template < std::invocable< value_type && > F >
        requires( std::is_move_constructible_v< error_type > )
    constexpr auto and_then( F && f ) &&
    {
        using ResultT = std::remove_cvref_t< std::invoke_result_t< F, value_type && > >;
        static_assert( detail::is_result_v< ResultT >, "F must return a result" );
        static_assert( std::is_same_v< error_type, typename ResultT::error_type >,
                       "error types must be the same" );

        return has_value() ? std::invoke( std::forward< F >( f ), std::move( assume_value() ) )
                           : ResultT::error( std::move( assume_error() ) );
    }

    /**
     * \brief Returns the contained value in the return type if it contains a value.
     * Otherwise, returns the result of invocation of \p f on the contained error.
     *
     * The return type must be a specialization of `Result` with the same value type.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The contained value or the result of \p f .
     */
    template < std::invocable< error_type & > F >
        requires( std::is_copy_constructible_v< value_type > )
    constexpr auto or_else( F && f ) &
    {
        using ResultT = std::remove_cvref_t< std::invoke_result_t< F, error_type & > >;
        static_assert( detail::is_result_v< ResultT >, "F must return a result" );
        static_assert( std::is_same_v< value_type, typename ResultT::value_type >,
                       "value types must be the same" );

        return has_value() ? ResultT::value( assume_value() )
                           : std::invoke( std::forward< F >( f ), assume_error() );
    }
    /**
     * \brief Returns the contained value in the return type if it contains a value.
     * Otherwise, returns the result of invocation of \p f on the contained error.
     *
     * The return type must be a specialization of `Result` with the same value type.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The contained value or the result of \p f .
     */
    template < std::invocable< const error_type & > F >
        requires( std::is_copy_constructible_v< value_type > )
    constexpr auto or_else( F && f ) const &
    {
        using ResultT = std::remove_cvref_t< std::invoke_result_t< F, const error_type & > >;
        static_assert( detail::is_result_v< ResultT >, "F must return a result" );
        static_assert( std::is_same_v< value_type, typename ResultT::value_type >,
                       "value types must be the same" );

        return has_value() ? ResultT::value( assume_value() )
                           : std::invoke( std::forward< F >( f ), assume_error() );
    }
    /**
     * \brief Returns the contained value in the return type if it contains a value.
     * Otherwise, returns the result of invocation of \p f on the contained error.
     *
     * The return type must be a specialization of `Result` with the same value type.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The contained value or the result of \p f .
     */
    template < std::invocable< error_type && > F >
        requires( std::is_move_constructible_v< value_type > )
    constexpr auto or_else( F && f ) &&
    {
        using ResultT = std::remove_cvref_t< std::invoke_result_t< F, error_type && > >;
        static_assert( detail::is_result_v< ResultT >, "F must return a result" );
        static_assert( std::is_same_v< value_type, typename ResultT::value_type >,
                       "value types must be the same" );

        return has_value() ? ResultT::value( std::move( assume_value() ) )
                           : std::invoke( std::forward< F >( f ), std::move( assume_error() ) );
    }

    /**
     * \brief Returns the contained value in the return type if it contains a value.
     * Otherwise, returns the result of \p f .
     *
     * The return type must be a specialization of `Result` with the same value type.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The contained value or the result of \p f .
     */
    template < std::invocable<> F >
        requires( std::is_copy_constructible< value_type >::value
                  && !std::is_invocable< F, error_type & >::value
                  && !std::is_invocable< F, const error_type & >::value
                  && !std::is_invocable< F, error_type && >::value )
    constexpr auto or_else( F && f ) const
    {
        using ResultT = std::remove_cvref_t< std::invoke_result_t< F > >;
        static_assert( detail::is_result_v< ResultT >, "F must return a result" );
        static_assert( std::is_same_v< value_type, typename ResultT::value_type >,
                       "value types must be the same" );

        return has_value() ? ResultT::value( assume_value() )
                           : std::invoke( std::forward< F >( f ) );
    }
    /**
     * \brief Returns the contained value in the return type if it contains a value.
     * Otherwise, returns the result of \p f .
     *
     * The return type must be a specialization of `Result` with the same value type.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The contained value or the result of \p f .
     */
    template < std::invocable<> F >
        requires( std::is_move_constructible< value_type >::value
                  && !std::is_invocable< F, error_type & >::value
                  && !std::is_invocable< F, const error_type & >::value
                  && !std::is_invocable< F, error_type && >::value )
    constexpr auto or_else( F && f ) &&
    {
        using ResultT = std::remove_cvref_t< std::invoke_result_t< F > >;
        static_assert( detail::is_result_v< ResultT >, "F must return a result" );
        static_assert( std::is_same_v< value_type, typename ResultT::value_type >,
                       "value types must be the same" );

        return has_value() ? ResultT::value( std::move( assume_value() ) )
                           : std::invoke( std::forward< F >( f ) );
    }

    /// Transform operations

    /**
     * \brief Returns `Result` with the result of invocation of \p f
     * on the contained value as the new value if it exists.
     * Otherwise, returns the contained error in the return type.
     *
     * The return type of \p f will be the value type of the returned `Result`.
     *
     * \param f a suitable function or Callable object that returns the new value type
     *
     * \returns The result of \p f or the contained error.
     */
    template < std::invocable< value_type & > F >
    constexpr auto transform( F && f ) &
    {
        using ValueT = std::remove_cvref_t< std::invoke_result_t< F, value_type & > >;
        using ResultT = Result< ValueT, error_type >;
        return has_value() ? ResultT::value( std::invoke( std::forward< F >( f ), assume_value() ) )
                           : ResultT::error( assume_error() );
    }
    /**
     * \brief Returns `Result` with the result of invocation of \p f
     * on the contained value as the new value if it exists.
     * Otherwise, returns the contained error in the return type.
     *
     * The return type of \p f will be the value type of the returned `Result`.
     *
     * \param f a suitable function or Callable object that returns the new value type
     *
     * \returns The result of \p f or the contained error.
     */
    template < std::invocable< const value_type & > F >
    constexpr auto transform( F && f ) const &
    {
        using ValueT = std::remove_cvref_t< std::invoke_result_t< F, const value_type & > >;
        using ResultT = Result< ValueT, error_type >;
        return has_value() ? ResultT::value( std::invoke( std::forward< F >( f ), assume_value() ) )
                           : ResultT::error( assume_error() );
    }
    /**
     * \brief Returns `Result` with the result of invocation of \p f
     * on the contained value as the new value if it exists.
     * Otherwise, returns the contained error in the return type.
     *
     * The return type of \p f will be the value type of the returned `Result`.
     *
     * \param f a suitable function or Callable object that returns the new value type
     *
     * \returns The result of \p f or the contained error.
     */
    template < std::invocable< value_type && > F >
    constexpr auto transform( F && f ) &&
    {
        using ValueT = std::remove_cvref_t< std::invoke_result_t< F, value_type && > >;
        using ResultT = Result< ValueT, error_type >;
        return has_value() ? ResultT::value(
                       std::invoke( std::forward< F >( f ), std::move( assume_value() ) ) )
                           : ResultT::error( std::move( assume_error() ) );
    }

    /**
     * \brief Returns the contained value in the return type if it contains a value.
     * Otherwise, returns `Result` with the result of invocation of \p f
     * on the contained error as the new error.
     *
     * The return type of \p f will be the error type of the returned `Result`.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The contained value or the result of \p f .
     */
    template < std::invocable< error_type & > F >
    constexpr auto transform_error( F && f ) &
    {
        using ErrorT = std::remove_cvref_t< std::invoke_result_t< F, error_type & > >;
        using ResultT = Result< value_type, ErrorT >;
        return has_value()
                     ? ResultT::value( assume_value() )
                     : ResultT::error( std::invoke( std::forward< F >( f ), assume_error() ) );
    }
    /**
     * \brief Returns the contained value in the return type if it contains a value.
     * Otherwise, returns `Result` with the result of invocation of \p f
     * on the contained error as the new error.
     *
     * The return type of \p f will be the error type of the returned `Result`.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The contained value or the result of \p f .
     */
    template < std::invocable< const error_type & > F >
    constexpr auto transform_error( F && f ) const &
    {
        using ErrorT = std::remove_cvref_t< std::invoke_result_t< F, const error_type & > >;
        using ResultT = Result< value_type, ErrorT >;
        return has_value()
                     ? ResultT::value( assume_value() )
                     : ResultT::error( std::invoke( std::forward< F >( f ), assume_error() ) );
    }
    /**
     * \brief Returns the contained value in the return type if it contains a value.
     * Otherwise, returns `Result` with the result of invocation of \p f
     * on the contained error as the new error.
     *
     * The return type of \p f will be the error type of the returned `Result`.
     *
     * \param f a suitable function or Callable object that returns a `Result`
     *
     * \returns The contained value or the result of \p f .
     */
    template < std::invocable< error_type && > F >
    constexpr auto transform_error( F && f ) &&
    {
        using ErrorT = std::remove_cvref_t< std::invoke_result_t< F, error_type && > >;
        using ResultT = Result< value_type, ErrorT >;
        return has_value() ? ResultT::value( std::move( assume_value() ) )
                           : ResultT::error( std::invoke( std::forward< F >( f ),
                                                          std::move( assume_error() ) ) );
    }

    /// Comparison operator

    /**
     * \brief Checks equality of two results.
     *
     * \param other result to check equality against
     *
     * \returns whether both `*this` and \p other contain value and the values
     * are equal or both contain error and the errors are equal.
     */
    bool operator==( const Result & other ) const = default;

private:
    using data_type = std::variant< value_type, error_type >;

    template < size_t I, typename... Args >
    explicit constexpr Result( std::in_place_index_t< I > i, Args &&... args )
            : _data( i, std::forward< Args >( args )... )
    {}

    data_type _data;
};

} // namespace atoms
