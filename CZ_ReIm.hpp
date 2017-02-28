#pragma once
#ifndef CZ_ReIm_hpp_17_2_26_957pm
#define CZ_ReIm_hpp_17_2_26_957pm



#include <type_traits>
#include <limits>
#include <cmath>
#include <complex>
#include <iostream>
#include <iomanip>



#ifdef CZ_UseRealHpp
#ifndef CZ_HasRealHpp

#define MPFR_REAL_ENABLE_CONV_OPS
#include "real.hpp"
#define CZ_HasRealHpp

#endif
#endif



namespace CZ
{



template< class Real_ > struct ReIm ;



template< class... T_ >
struct BiggerReal ;

template< class OtherReal_ >
struct BiggerReal< std::complex< OtherReal_ > >
{
    typedef OtherReal_ type ;
} ;

template< class OtherReal_ >
struct BiggerReal< ReIm< OtherReal_ > >
{
    typedef OtherReal_ type ;
} ;

template< class OtherReal_ >
struct BiggerReal< OtherReal_ >
{
    typedef OtherReal_ type ;
} ;

template< class OtherReal_ >
struct BiggerReal< OtherReal_ [2] >
{
    typedef OtherReal_ type ;
} ;

template< class First_ >
struct BiggerReal< First_ , First_ >
{
    typedef typename BiggerReal< First_ >::type type ;
} ;

template< class First_ , class Second_ >
struct BiggerReal< First_ , Second_ >
{
    typedef typename std::conditional<
            (std::numeric_limits< typename BiggerReal< First_ >::type >::digits >= std::numeric_limits< typename BiggerReal< Second_ >::type >::digits) , 
            typename BiggerReal< First_ >::type ,
            typename BiggerReal< Second_ >::type 
    >::type type ;
} ;

template< class First_ , class Second_ , class... Others_ >
struct BiggerReal< First_ , Second_ , Others_... >
{
    typedef typename BiggerReal< typename BiggerReal< First_ >::type , typename BiggerReal< Second_ , Others_... >::type >::type type ;
} ;



template< class Real_ >
inline Real_ real(const ReIm< Real_ > & reIm)
{
    return reIm.reIm[0] ;
}

template< class Real_ >
inline Real_ imag(const ReIm< Real_ > & reIm)
{
    return reIm.reIm[1] ;
}

template< class Real_ >
inline Real_ hypot(const ReIm< Real_ > & reIm)
{
    return std::hypot(reIm.reIm[0] , reIm.reIm[1]) ;
}

template< class Real_ >
inline Real_ abs(const ReIm< Real_ > & reIm)
{
    return std::hypot(reIm.reIm[0] , reIm.reIm[1]) ;
}

template< class Real_ >
inline Real_ norm(const ReIm< Real_ > & reIm)
{
    return ((reIm.reIm[0] * reIm.reIm[0]) + (reIm.reIm[1] * reIm.reIm[1])) ;
}

template< class Real_ >
inline ReIm< Real_ > conj(const ReIm< Real_ > & reIm)
{
    return ReIm< Real_ >(reIm.reIm[0] , - reIm.reIm[1]) ;
}



template< class Real_ , typename std::enable_if< ((!(std::is_array< Real_ >::value)) && (!(std::is_pointer< Real_ >::value))) , int >::type = 0 >
inline Real_ real(const Real_ (& reIm) [2])
{
    return reIm[0] ;
}

template< class Real_ , typename std::enable_if< ((!(std::is_array< Real_ >::value)) && (!(std::is_pointer< Real_ >::value))) , int >::type = 0 >
inline Real_ imag(const Real_ (& reIm) [2])
{
    return reIm[1] ;
}

template< class Real_ , typename std::enable_if< ((!(std::is_array< Real_ >::value)) && (!(std::is_pointer< Real_ >::value))) , int >::type = 0 >
inline Real_ hypot(const Real_ (& reIm) [2])
{
    return std::hypot(reIm[0] , reIm[1]) ;
}

template< class Real_ , typename std::enable_if< ((!(std::is_array< Real_ >::value)) && (!(std::is_pointer< Real_ >::value))) , int >::type = 0 >
inline Real_ abs(const Real_ (& reIm) [2])
{
    return std::hypot(reIm[0] , reIm[1]) ;
}

template< class Real_ , typename std::enable_if< ((!(std::is_array< Real_ >::value)) && (!(std::is_pointer< Real_ >::value))) , int >::type = 0 >
inline Real_ norm(const Real_ (& reIm) [2])
{
    return ((reIm[0] * reIm[0]) + (reIm[1] * reIm[1])) ;
}

template< class Real_ , typename std::enable_if< ((!(std::is_array< Real_ >::value)) && (!(std::is_pointer< Real_ >::value))) , int >::type = 0 >
inline ReIm< Real_ > conj(const Real_ (& reIm) [2])
{
    return ReIm< Real_ >(reIm[0] , - reIm[1]) ;
}



} // end namespace CZ



namespace std
{

using ::CZ::real ;
using ::CZ::imag ;
using ::CZ::hypot ;
using ::CZ::abs ;
using ::CZ::norm ;
using ::CZ::conj ;

template< class T >
struct common_type< CZ::ReIm< T > >
{
    typedef typename std::decay< CZ::ReIm< typename CZ::BiggerReal< typename std::decay< T >::type >::type > >::type type ;
} ;

template< class T , class U >
struct common_type< T , CZ::ReIm< U > >
{
    typedef typename std::decay< CZ::ReIm< typename CZ::BiggerReal< typename std::decay< T >::type , typename std::decay< U >::type >::type > >::type type ;
} ;

template< class T , class U >
struct common_type< CZ::ReIm< T > , U >
{
    typedef typename std::decay< CZ::ReIm< typename CZ::BiggerReal< typename std::decay< T >::type , typename std::decay< U >::type >::type > >::type type ;
} ;

template< class T , class U >
struct common_type< CZ::ReIm< T > , CZ::ReIm< U > >
{
    typedef typename std::decay< CZ::ReIm< typename CZ::BiggerReal< typename std::decay< T >::type , typename std::decay< U >::type >::type > >::type type ;
} ;

} // end namespace std



namespace CZ
{


template< class Real_ >
struct ReIm
{


    typedef Real_                   Real ;
    typedef ReIm< Real >            Complex ;


    Real                            reIm [2] ;


    template< typename Other_ >
    ReIm(const Other_ & in)
    {
        reIm[0] = std::real(in) ;
        reIm[1] = std::imag(in) ;
    }

    template< typename Other_ >
    ReIm(const Other_ && in)
    {
        reIm[0] = std::real(in) ;
        reIm[1] = std::imag(in) ;
    }

    template< typename OtherReal_ >
    ReIm(const OtherReal_ & inReal , const OtherReal_ & inImag)
    {
        reIm[0] = inReal ;
        reIm[1] = inImag ;
    }

    template< typename OtherReal_ >
    ReIm(const OtherReal_ && inReal , const OtherReal_ && inImag)
    {
        reIm[0] = inReal ;
        reIm[1] = inImag ;
    }

    ReIm()
    {
        reIm[0] = 0.0 ;
        reIm[1] = 0.0 ;
    }


    template< typename OtherReal_ >
    inline operator std::complex< OtherReal_ >() const
    {
        return std::complex< OtherReal_ >(OtherReal_(reIm[0]),OtherReal_(reIm[1])) ;
    }

    inline operator Real * ()
    {
        return reIm ;
    }

    inline operator const Real * const () const
    {
        return reIm ;
    }

    inline Real & operator [] (std::size_t ind)
    {
        return reIm[ind] ;
    }

    
    template< typename Other_ >
    bool operator == (const Other_ & other)
    {
        return ((reIm[0] == std::real(other)) && (reIm[1] == std::imag(other))) ;
    }


    template< typename Other_ >
    inline ReIm & operator += (const Other_ & other)
    {
        reIm[0] += std::real(other) ;
        reIm[1] += std::imag(other) ;
        return *this ;
    } 

    template< typename Other_ >
    ReIm< typename BiggerReal< Real , Other_ >::type > operator + (const Other_ & other) const
    {
        ReIm< typename BiggerReal< Real , Other_ >::type > result = *this ;
        result += other ;
        return result ;
    }

    friend ReIm< Real > operator + (ReIm< Real > first , const ReIm< Real > & other)
    {
        first += other ;
        return first ;
    }


    template< typename Other_ >
    inline ReIm & operator -= (const Other_ & other)
    {
        reIm[0] -= std::real(other) ;
        reIm[1] -= std::imag(other) ;
        return *this ;
    } 

    template< typename Other_ >
    ReIm< typename BiggerReal< Real , Other_ >::type > operator - (const Other_ & other) const
    {
        ReIm< typename BiggerReal< Real , Other_ >::type > result = *this ;
        result -= other ;
        return result ;
    }

    friend ReIm< Real > operator - (ReIm< Real > first , const ReIm< Real > & other)
    {
        first -= other ;
        return first ;
    }


    template< typename Other_ >
    inline ReIm & operator *= (const Other_ & other)
    {

        if ((std::real(other) == 1.0) && (std::imag(other) == 0.0))
        {
            return *this ;
        }

        if ((std::real(other) == 0.0) && (std::imag(other) == 0.0))
        {
            reIm[0] = 0.0 ;
            reIm[1] = 0.0 ;
            return *this ;
        }

        if (std::imag(other) == 0.0)
        {
            reIm[0] *= std::real(other) ;
            reIm[1] *= std::real(other) ;
            return *this ;
        }

        if (std::real(other) == 0.0)
        {
            Real tmp = reIm[0] * std::imag(other) ;
            reIm[0] = -(reIm[1] * std::imag(other)) ;
            reIm[1] = tmp ;
            return *this ;
        }
 
        Real tmp [2] { (reIm[0] * std::real(other)) - (reIm[1] * std::imag(other)) , (reIm[0] * std::imag(other)) + (reIm[1] * std::real(other)) } ;
        reIm[0] = tmp[0] ;
        reIm[1] = tmp[1] ;

        return *this ;

    } 

    template< typename Other_ >
    friend ReIm< typename BiggerReal< Real , Other_ >::type > operator * (ReIm< Real > first , const Other_ & other)
    {
        ReIm< typename BiggerReal< Real , Other_ >::type > result = first ;
        result *= other ;
        return result ;
    }

    friend ReIm< Real > operator * (ReIm< Real > first , const ReIm< Real > & other)
    {
        first *= other ;
        return first ;
    }


    template< typename Other_ >
    inline ReIm & operator /= (const Other_ & other)
    {

        if ((std::real(other) == 1.0) && (std::imag(other) == 0.0))
        {
            return *this ;
        }

        if (std::imag(other) == 0.0)
        {
            reIm[0] /= std::real(other) ;
            reIm[1] /= std::real(other) ;
            return *this ;
        }

        if (std::real(other) == 0.0)
        {
            Real tmp = reIm[0] / std::imag(other) ;
            reIm[0] = - (reIm[1] / std::imag(other)) ;
            reIm[1] = - tmp ;
            return *this ;
        }
 
        Real tmp [3] { (reIm[0] * std::real(other)) + (reIm[1] * std::imag(other)) , (-(reIm[0] * std::imag(other))) + (reIm[1] * std::real(other)) , std::norm(other) } ;
        reIm[0] = (tmp[0] / tmp[2]) ;
        reIm[1] = (tmp[1] / tmp[2]) ;

        return *this ;

    } 

    template< typename Other_ >
    ReIm< typename BiggerReal< Real , Other_ >::type > operator / (const Other_ & other) const
    {
        ReIm< typename BiggerReal< Real , Other_ >::type > result = *this ;
        result /= other ;
        return result ;
    }

    friend ReIm< Real > operator / (ReIm< Real > first , const ReIm< Real > & other)
    {
        first /= other ;
        return first ;
    }


} ; // end struct ReIm< Real_ >


template< class Real_ >
std::ostream & operator << (std::ostream & stream , const ReIm< Real_ > & reIm)
{
    std::complex< double > tmp = reIm ;
    stream << tmp ;
    return stream ;
}

template< class Real_ >
std::istream & operator >> (std::istream & stream , ReIm< Real_ > & reIm)
{
    std::complex< double > tmp ;
    stream >> tmp ;
    reIm = tmp ;
    return stream ;
}


} // end namespace CZ


#endif // end include guard ifndef CZ_ReIm_hpp_17_2_26_957pm
