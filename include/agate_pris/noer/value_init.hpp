
#ifndef AGATE_PRIS_NOER_VALUE_INIT_HPP
#define AGATE_PRIS_NOER_VALUE_INIT_HPP

#include <utility>

namespace agate_pris
{
    namespace noer
    {
        namespace value_inits
        {
            template< typename Value, typename Tag = void >
            class value_initialized
            {
                private:
                Value m_data;

                public:
                // type
                using value_type = Value;

                // constructor
                value_initialized();

                // accessor
                Value&       data();
                Value const& data() const;

                // swap
                inline void swap( value_initialized& arg );

                // conversion
                inline operator value_type const& () const;
                inline operator value_type&       ();
            };

            // accessor
            // --------
            template< typename Value, typename Tag = void >
            Value& value_initialized< Value, Tag >::data()
            {
                return m_data;
            }

            template< typename Value, typename Tag = void >
            Value const& value_initialized< Value, Tag >::data() const
            {
                return m_data;
            }

            template< typename Value, typename Tag = void >
            Value& get( value_initialized< Value, Tag >& v )
            {
                return v.data();
            }

            template< typename Value, typename Tag = void >
            Value const& get( value_initialized< Value, Tag > const& v )
            {
                return v.data();
            }

            // swap
            // ----
            template<typename Value, typename Tag>
            inline void value_initialized<Value, Tag>::swap( value_initialized & arg )
            {
                using std::swap;
                swap( m_data, arg.data() );
            }

            template< typename Value, typename Tag >
            inline void swap( value_initialized< Value, Tag >& lhs, value_initialized< Value, Tag >& rhs )
            {
                lhs.swap( rhs );
            }

            // conversion
            // ----------
            template< typename Value, typename Tag >
            inline value_initialized< Value, Tag >::operator value_type const&() const
            {
                return m_data;
            }

            template<typename Value, typename Tag>
            inline value_initialized<Value, Tag>::operator value_type&( )
            {
                return m_data;
            }
        }
        using value_inits::value_initialized;
        using value_inits::get;
        using value_inits::swap;
    }
}

#endif
