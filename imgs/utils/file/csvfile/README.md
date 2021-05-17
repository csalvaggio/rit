# INTRODUCTION
This directory contains an interface file defining a class for reading data from a comma-separated value (CSV) file, returning column label to a C++ <span style="font-family:Courier">std::string</span> and/or column data to a C++ <span style="font-family:Courier">std::vector</span>.

# USAGE
Within this build environment, all one needs to do to utilize this class is to include the aggregate header file for the project utilities

    #include "imgs/utils/utils.h"


and be sure to include <span style="font-family:Courier">    rit::utils\_file\_csvfile</span> in the <span style="font-family:Courier">target\_link\_libraries</span> directive in your project's <span style="font-family:Courier">CMakeLists.txt</span> file.


# EXAMPLES
Here is an example code snippet to read column labels and data from a CSV file, placing the data in a <span style="font-family:Courier">std::vector\<double\></span>

    std::string filename = "your filename";
    std::size_t header_lines = 1;
    std::size_t label_line = 1;

    utils::CsvFile f;
    f.set_filename(filename);
    f.set_header_lines(header_lines);
    f.set_label_line(label_line);

    std::size_t column = 1;
    auto label = f.get_label(column);
    auto standard_vector = f.get_column<double>(column);

If it was desired to have the data in an <span style="font-family:Courier">Eigen::VectorXd</span>, the following could be used for conversion

    Eigen::Map<Eigen::VectorXd> eigen_vector(standard_vector.data(),
                                             standard_vector.size());

The same could be done to place the data in a <span style="font-family:Courier">cv::Mat</span> column vector

    cv::Mat cv_vector(standard_vector.size(), 1, CV_64FC1);
    std::memcpy(cv_vector.data, standard_vector.data(),
                standard_vector.size() * sizeof(double));

# FUNCTIONS

###### Constructors for the CSV file object

    CsvFile();

With parameters

    CsvFile(std::string filename, std::size_t header_lines = 0,
            std::size_t label_line = 0) {

where <span style="font-family:Courier">header\_lines</span> indicates the number of header lines that appear prior to the line that the data begins on [default is 0], and <span style="font-family:Courier">label\_line</span> indicates, if any, the line on which the labels are found [default is 0].

###### Accessor and mutator for the filename member

    std::string filename() const;
    void set_filename(std::string filename);

###### Accessor and mutator for the header_lines member

    std::size_t header_lines() const;
    void set_header_lines(std::size_t header_lines);

###### Accessor and mutator for the label_line member

    std::size_t label_line() const;
    void set_label_line(std::size_t label_line);

###### Return data from desired column

    template <typename T1>
    std::vector<T1> get_column(std::size_t column) const;
 
Valid template data types for vector are <span style="font-family:Courier">int</span>, <span style="font-family:Courier">long</span>, <span style="font-family:Courier">unsigned long</span>, <span style="font-family:Courier">long long</span>, <span style="font-family:Courier">unsigned long long</span>, <span style="font-family:Courier">float</span>, <span style="font-family:Courier">double</span>, and <span style="font-family:Courier">long double</span>. 
 
###### Return label/title from desired column
    std::string get_label(std::size_t column) const;

# REQUIREMENTS
* C++ compiler that supports C++17 dialect/ISO standard

# DEPENDENCIES
* OpenCV Core (only for converting to <span style="font-family:Courier">cv::Mat</span>)
* Eigen/Dense (only for converting to <span style="font-family:Courier">Eigen::VectorXd</span>)

