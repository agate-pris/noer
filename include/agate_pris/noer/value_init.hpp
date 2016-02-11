
#ifndef AGATE_PRIS_NOER_VALUE_INIT_HPP
#define AGATE_PRIS_NOER_VALUE_INIT_HPP

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
                // member type
                using value_type = Value;

                // accessor
                Value&       data();
                Value const& data() const;

                // swap
                inline void swap( value_initialized& arg );
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

            // swap
            // ----
            template<typename Value, typename Tag>
            inline void value_initialized<Value, Tag>::swap( value_initialized & arg )
            {
                using std::swap;
                swap( m_data, arg.data() );
            }
        }
        using value_inits::value_initialized;
    }
}

#endif
