#include <iostream>
#include <iomanip>

#include "color/color.hpp"

using namespace std;
using namespace color;

int main( int argc, char *argv[] )
 {
  cmy<std::uint8_t>    c1( constant::orange_t{} );
  cmy<std::uint16_t>   c2( constant::orange_t{} );
  cmy<std::uint32_t>   c3( constant::orange_t{} );
  cmy<std::uint64_t>   c4( constant::orange_t{} );
  cmy<float>           c5( constant::orange_t{} );
  cmy<double>          c6( constant::orange_t{} );
  cmy<long double>     c7( constant::orange_t{} );

  cout << c1[0] << ", " << c1[1] << ", " << c1[2] << endl;
  cout << c2[0] << ", " << c2[1] << ", " << c2[2] << endl;
  cout << c3[0] << ", " << c3[1] << ", " << c3[2] << endl;
  cout << c4[0] << ", " << c4[1] << ", " << c4[2] << endl;
  cout << c5[0] << ", " << c5[1] << ", " << c5[2] << endl;
  cout << c6[0] << ", " << c6[1] << ", " << c6[2] << endl;
  cout << c7[0] << ", " << c7[1] << ", " << c7[2] << endl;

  return EXIT_SUCCESS;
 }
