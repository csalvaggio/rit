# INTRODUCTION
This directory contains an interface-only library to provide CIE reference illuminant and standard observer data in <span style="font-family:Courier">Eigen::VectorXd</span> format.  Reference data is provided on 1 [nm] spacing from 360 to 830 [nm].  Be sure to [interpolate](../../numerical/interpolation/) as necessary to utilize this data properly.

# USAGE
Within this build environment, all one needs to do to utilize these reference data-providing functions is to include the aggregate header file

    #include "imgs/color/color.h"


# EXAMPLES
Here is an example code using this reference data-providing interface to provide some common CIE reference illuminant and standard observer values

    #include "imgs/color/color.h"

    int main() {
      color::CIE cie;

      int illuminant_enum = cie.ReferenceIlluminant::d65;
      int observer_enum = cie.StandardObserver::two_deg;

      Eigen::VectorXd wavelengths = cie.wavelengths();
      cout << "CIE Reference Wavelengths [nm]:" << endl;
      cout << wavelengths << endl;
      cout << endl;

      Eigen::VectorXd illuminant = cie.reference_illuminant(illuminant_enum);
      cout << "CIE Reference Illuminant (D65):" << endl;
      cout << illuminant << endl;
      cout << endl;

      Eigen::VectorXd xbar = cie.xbar(observer_enum);
      cout << "CIE Standard Observer x-bar (2 degree):" << endl;
      cout << xbar << endl;
      Eigen::VectorXd ybar = cie.ybar(observer_enum);
      cout << "CIE Standard Observer y-bar (2 degree):" << endl;
      cout << ybar << endl;
      Eigen::VectorXd zbar = cie.zbar(observer_enum);
      cout << "CIE Standard Observer z-bar (2 degree):" << endl;
      cout << zbar << endl;
      cout << endl;

    }

#ENUMERATIONS

The following enumerations are currently available as part of any <span style="font-family:Courier">color::CIE</span> object:

|Enumeration|Illuminant|
|---|---|
|<span style="font-family:Courier">ReferenceIlluminant::d65</span> |D65|
|<span style="font-family:Courier">ReferenceIlluminant::a</span> |A|


|Enumeration|Standard Observer|
|---|---|
|<span style="font-family:Courier">StandardObserver::two_deg</span> |1931 2-degree|
|<span style="font-family:Courier">StandardObserver::ten_deg</span> |1964 10-degree|

# FUNCTIONS

###### CONSTRUCTOR
Default constructor for the CIE object in the <span style="font-family:Courier">color</span> namespace

    CIE();

###### CIE wavelengths getter

    Eigen::VectorXd wavelengths();

returns a 471-element column vector.

###### CIE reference illuminant getter

    Eigen::VectorXd reference_illuminant(int illuminant enum);

returns a 471-element column vector.

###### CIE standard observer getters

    Eigen::MatrixXd standard_observer(int observer_enum);

returns a 471 rows by 3 column matrix containing the x-bar, y-bar and z-bar observer functions, and

    Eigen::VectorXd xbar(int observer_enum);
    Eigen::VectorXd ybar(int observer_enum);
    Eigen::VectorXd zbar(int observer_enum);

each returns a 471-element column vector.

# REQUIREMENTS
* C++ compiler that supports C++17 dialect/ISO standard

# DEPENDENCIES
* Eigen/Dense
