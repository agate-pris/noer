
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
            };
        }
        using value_inits::value_initialized;
    }
}

#endif
