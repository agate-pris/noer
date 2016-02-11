
#ifndef AGATE_PRIS_NOER_INITIALIZED_VALUE_HPP
#define AGATE_PRIS_NOER_INITIALIZED_VALUE_HPP

namespace agate_pris
{
    namespace noer
    {
        namespace value_inits
        {
            template< typename Value, typename Tag = void >
            class initialized_value
            {
            };
        }
        using value_inits::initialized_value;
    }
}

#endif
