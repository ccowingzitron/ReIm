#include <limits>
#include <iostream>
#include <iomanip>
#include <locale>
#include <string>
#include <complex>



#include "CZ_ReIm.hpp"



int main(int argc , char * argv [])
{

    typename std::common_type< CZ::ReIm< float > >::type crf(3.4,5.7) ;
    typename std::common_type< float , CZ::ReIm< double > >::type cfrd = 2.9 ;
    typename std::common_type< CZ::ReIm< float > , double >::type crdf = cfrd ;
    typename std::common_type< std::complex< float > , double , CZ::ReIm< double > >::type ccfdrd = crdf ;
    typename std::common_type< CZ::ReIm< double > , std::complex< float > , double >::type crdcfd = ccfdrd ;
    typename std::common_type< CZ::ReIm< double > , std::complex< float > , CZ::ReIm< float > >::type crdcfrf = ccfdrd ;

    float f = 0.5f ;
    float f2 [2] {1.5f,2.5f} ;
    std::complex< float > f3(3.5f,4.5f) ;
    std::complex< float > f4(0.295f,1793987.2f) ;

    double d = 5.5 ;
    double d2 [2] {6.5,7.5} ;
    std::complex< double > d3(3.5,4.5) ;
    std::complex< double > d7(0.295,1793987.2) ;


    CZ::ReIm< float > rf = f ;
    CZ::ReIm< float > rf2 = f2 ;
    CZ::ReIm< float > rf3 = f3 ;
    CZ::ReIm< float > rf4 = f4 ;

    auto rd = rf - d ;
    auto rd2 = rf2 * d2 ;
    auto rd3 = rf3 / d3 ;

    double d4 = std::real(rd3) ;
    double d5 [2] {rd3[0],rd3[1]} ;
    std::complex< double > d6 = rd3 ;

    std::cout << d4 << " == " << std::real(d5) << " == " << std::real(d6) << std::endl ;

    std::cout << (f3 * rf3) << std::endl ;

    std::cout << "(" << f3 << " + " << f4 << ") - (" << rf3 << " + " << rf4 << ") = " << ((f3 + f4) - (rf3 + rf4)) << std::endl ;
    std::cout << "(" << f3 << " - " << f4 << ") - (" << rf3 << " - " << rf4 << ") = " << ((f3 - f4) - (rf3 - rf4)) << std::endl ;
    std::cout << "(" << f3 << " * " << f4 << ") - (" << rf3 << " * " << rf4 << ") = " << ((f3 * f4) - (rf3 * rf4)) << std::endl ;
    std::cout << "(" << f3 << " / " << f4 << ") - (" << rf3 << " / " << rf4 << ") = " << ((f3 / f4) - (rf3 / rf4)) << std::endl ;


    std::cout << rf << " - " << d << " = " << rd << std::endl ;
    std::cout << rf2 << " * (" << d2[0] << "," << d2[1] << ") = " << rd2 << std::endl ;
    std::cout << rf3 << " / " << d3 << " = " << rd3 << std::endl ;
    std::cout << "std::norm(" << rd3 << " + std::conj(" << rf3 << ") = " << std::norm(rd3 + std::conj(rf3)) << std::endl ;

    CZ::ReIm< double > testLayout [2] ;
    std::size_t first , second , size ;
    first = (std::size_t) static_cast< void * >(testLayout) ;
    second = (std::size_t) static_cast< void * >(testLayout + 1) ;
    size = (std::size_t) sizeof(testLayout[0]) ;
    std::cout << "testLayout is CZ::ReIm< double > [2] ; (testLayout + 1) - testLayout = " << (second - first) << " and sizeof(testLayout[0]) = " << size << std::endl ;

#ifdef CZ_HasRealHpp

    CZ::ReIm< mpfr::real< 54 > > rm3 = d3 ;
    CZ::ReIm< mpfr::real< 54 > > rm4 = d7 ;

    std::cout << "(" << d3 << " + " << d7 << ") - (" << rm3 << " + " << rm4 << ") = " << (d3 + d7) << " - " << (rm3 + rm4) << " = " << ((d3 + d7) - (rm3 + rm4)) << std::endl ;
    std::cout << "(" << d3 << " - " << d7 << ") - (" << rm3 << " - " << rm4 << ") = " << (d3 - d7) << " - " << (rm3 - rm4) << " = " << ((d3 - d7) - (rm3 - rm4)) << std::endl ;
    std::cout << "(" << d3 << " * " << d7 << ") - (" << rm3 << " * " << rm4 << ") = " << (d3 * d7) << " - " << (rm3 * rm4) << " = " << ((d3 * d7) - (rm3 * rm4)) << std::endl ;
    std::cout << "(" << d3 << " / " << d7 << ") - (" << rm3 << " / " << rm4 << ") = " << (d3 / d7) << " - " << (rm3 / rm4) << " = " << ((d3 / d7) - (rm3 / rm4)) << std::endl ;

    CZ::ReIm< mpfr::real< 4096 > > testLayoutMpfr [2] ;
    first = (std::size_t) static_cast< void * >(testLayoutMpfr) ;
    second = (std::size_t) static_cast< void * >(testLayoutMpfr + 1) ;
    size = (std::size_t) sizeof(testLayoutMpfr[0]) ;
    std::cout << "testLayoutMpfr is CZ::ReIm< mpfr::real< 4096 > > [2] ; (testLayout + 1) - testLayout = " << (second - first) << " and sizeof(testLayout[0]) = " << size << std::endl ;

#endif

    return 0 ;

}
