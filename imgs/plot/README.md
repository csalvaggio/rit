# INTRODUCTION
This directory contains general-purpose plotting tools built upon the the GNUplot streaming interface library.

# USAGE
Within this build environment, all one needs to do to utilize these functions is to include this local library

    #include "imgs/plot/plot.h"


and be sure to include <span style="font-family:Courier">rit::plot</span> in the <span style="font-family:Courier">target\_link\_libraries</span> directive in your project's <span style="font-family:Courier">CMakeLists.txt</span> file.

##### From the command line (not recommended):
To compile code using the provided plotting functions based on the
gnuplot streaming library, use the following command on the CIS servers.

    g++ -Isrc/cpp/rit -I/usr/local/include/opencv4 -I/usr/include/eigen3 -lboost_iostreams -lopencv_core -o <your binary name> <your source name>.cpp src/cpp/rit/imgs/plot/plot2d/Plot2d.cpp src/cpp/rit/imgs/plot/plot2d/Params.cpp src/cpp/rit/imgs/plot/plot3d/Plot3d.cpp src/cpp/rit/imgs/plot/plot3d/Params.cpp
    

This command assumes the recommended directory structure has been followed, namely

    src
    └── cpp
       └── rit
           └── imgs
               ├── plot
               │   ├── plot2d
               │   │   ├── Params.cpp
               │   │   ├── Params.h
               │   │   ├── Plot2d.cpp
               │   │   └── Plot2d.h
               │   ├── plot3d
               │   │   ├── Params.cpp
               │   │   ├── Params.h
               │   │   ├── Plot3d.cpp
               │   │   └── Plot3d.h
               │   └── plot.h
               └── third_party
                   └── gnuplot-iostream.h

# EXAMPLES
Here is an example code illustrating how graph single and multiple plots using both <span style="font-family:Courier">std::vector</span> and <span style="font-family:Courier">cv::Mat</span> data types.

    #include <vector>

    #include <opencv2/core.hpp>

    #include "imgs/plot/plot.h"

    using namespace std;

    int main() {
      plot::plot2d::Params params;
      params.set_x_label("x");
      params.set_y_label("y");
      params.set_linestyle(params.LINES + params.POINTS);
    
      // Vector
      std::vector<double> x;
      std::vector<double> y;
      for (int i = 0; i <= 50; i++) {
        x.push_back((double)i);
        y.push_back((double)i * 50);
      }
      plot::plot2d::Plot2d(x, y, params);
    
      // Vector of Vectors
      std::vector<double> x1;
      std::vector<double> y1;
      for (int i = 0; i <= 50; i++) {
       x1.push_back((double)i);
        y1.push_back((double)i * 50);
      }
      std::vector<double> x2;
      std::vector<double> y2;
      for (int i = 0; i <= 50; i=i+10) {
        x2.push_back((double)i);
        y2.push_back((double)i * (double)i);
      }
      std::vector< std::vector<double> > xs;
      xs.push_back(x1);
      xs.push_back(x2);
      std::vector< std::vector<double> > ys;
      ys.push_back(y1);
      ys.push_back(y2);
      plot::plot2d::Plot2d(xs, ys, params);

      // Single vector in a cv::Mat_<double>
      cv::Mat_<double> xm = cv::Mat_<double>::zeros(1, 51);
      cv::Mat_<double> ym = cv::Mat_<double>::zeros(1, 51);
      for (int i = 0; i <= 50; i++) {
        xm(0, i) = i;
        ym(0, i) = i * 50;
      }
      plot::plot2d::Plot2d(xm, ym, params);

      // Multiple vectors in a cv::Mat_<double>
      cv::Mat_<double> xms;
      cv::Mat_<double> yms;
      xms = cv::Mat_<double>::zeros(2, 51);
      yms = cv::Mat_<double>::zeros(2, 51);
      for (int i = 0; i <= 50; i++) {
        xms(0, i) = i;
        yms(0, i) = i * 50;
        xms(1, i) = i;
        yms(1, i) = i * i;
      }
      plot::plot2d::Plot2d(xms, yms, params);

      params.Print();

      return EXIT_SUCCESS;

# FUNCTIONS
### For setting plot parameters

###### Constructors for the plot parameters object

    Params();

With plot labels

    Params(std::string x_label, std::string y_label);
    Params(std::string x_label, std::string y_label, std::string z_label);

###### Destructor for the plot parameters object

    ~Params();

###### Accessor and mutator for the terminal_type member

    std::string terminal_type() const;
    void set_terminal_type(std::string terminal_type);

The ``terminal_type`` may be any valid terminal for your Gnuplot installation.  A list of the valid terminal types may be obtained by issuing ``gnuplot -e "set terminal"`` on the command line.

###### Accessor and mutator for the font_face member

    std::string font_face() const;
    void set_font_face(std::string font_face);

###### Accessor and mutator for the font_size member

    int font_size() const;
    void set_font_size(int font_size);

###### Accessor and mutator for the x\_label member

    std::string x_label() const;
    void set_x_label(std::string x_label);

###### Accessor and mutator for the y\_label member

    std::string y_label() const;
    void set_y_label(std::string y_label);

###### Accessor and mutator for the z\_label member

    std::string z_label() const;
    void set_z_label(std::string z_label);

###### Accessor and mutator for the title member

    std::string title() const;
    void set_title(std::string title);

###### Accessor and mutator for the x\_min and x\_max members

    double x_min() const;
    void set_x_min(double x_min);
    double x_max() const;
    void set_x_max(double x_max);

###### Accessor and mutator for the y\_min and y\_max members

    double y_min() const;
    void set_y_min(double y_min);
    double y_max() const;
    void set_y_max(double y_max);

###### Accessor and mutator for the z\_min and z\_max members

    double z_min() const;
    void set_z_min(double z_min);
    double z_max() const;
    void set_z_max(double z_max);

###### Accessor and mutator for the x\_tics, y\_tics, and z\_tics members

    bool x_tics() const;
    void set_x_tics(bool x_tics);
    bool y_tics() const;
    void set_y_tics(bool y_tics);
    bool z_tics() const;
    void set_z_tics(bool z_tics);

###### Accessor and mutator for the linestyle member

    int linestyle() const;
    int linestyle(size_t series_idx) const;
    void set_linestyle(int linestyle);
    void set_linestyle(size_t series_idx, int linestyle);

where linestyle can take on <span style="font-family:Courier">\<object\>.POINTS</span>, <span style="font-family:Courier">\<object\>.LINES</span>, or the sum <span style="font-family:Courier">\<object>.LINES + \<object\>.POINTS</span>.

###### Accessor and mutator for the mesh member (plot3d only)
    bool mesh() const;
    void set_mesh(bool mesh);

###### Accessor and mutator for the mesh\_x\_size and mesh\_y\_size members (plot3d only)
    int mesh_x_size() const;
    void set_mesh_x_size(int mesh_x_size);
    int mesh_y_size() const;
    void set_mesh_y_size(int mesh_y_size);

if not specified, the default is 10 x 10.

###### Accessor and mutator for the palette\_mapping member (plot3d only)
    bool palette_mapping() const;
    void set_palette_mapping(bool palette_mapping);

###### Accessor and mutator for the declination and azimuth members (plot3d only)
    int declination() const;
    void set_declination(int declination);
    int azimuth() const;
    void set_azimuth(int azimuth);

###### Accessor and mutator for the scale and scale\_z members (plot3d only)
    double scale() const;
    void set_scale(double scale);
    double z_scale() const;
    void set_z_scale(double z_scale);

###### Accessor and mutator for the xvline member (plot2d only)

    double xvline() const;
    void set_xvline(double xvline);

###### Accessor and mutator for the destination filename member

    std::string destination_filename() const;
    void set_destination_filename(std::string dst_filename);

###### Print function to carry out a diagnostic dump of object values

    void Print() const;

### Convenience functions for plotting (plot::plot2d)

    /** Convenience function for plotting two-dimensional vector data
     *
     *  \param[in] x independent variable vector of type T1
     *  \param[in] y dependent variable vector of type T2
     *  \param[in] p plot parameters object of type plot2d::Params
     */
    template <class T1, class T2>
    void Plot2d(const std::vector<T1>& x, const std::vector<T2>& y,
                const plot2d::Params& params);
<br/>

    /** Convenience function for plotting multiple two-dimensional vector data
     *
     *  \param[in] x independent variable vector of vectors of type T1
     *  \param[in] y dependent variable vector of vectors of type T2
     *  \param[in] p plot parameters object of type plot2d::Params
     */
    template <class T1, class T2>
    void Plot2d(const std::vector<std::vector<T1> >& x,
                const std::vector<std::vector<T2> >& y,
                const plot2d::Params& params);
<br/>

    /** Convenience function for plotting two-dimensional vector data stored
     *  in the row(s) of cv::Mat_
     *
     *  \param[in] x independent variable cv::Mat_ with 1 or multiple rows
     *  \param[in] y dependent variable cv::Mat_ with 1 or multiple rows
     *  \param[in] p plot parameters object of type plot2d::Params
     */
    template <class T1, class T2>
    void Plot2d(const cv::Mat_<T1> x, const cv::Mat_<T2> y,
                const plot2d::Params params);
<br/>

    /** Convenience function for plotting two-dimensional vector data stored
     *  in the column(s) of Eigen::Matrix (or Eigen::Vector)
     *
     *  \param[in] x
     *     independent variable Eigen::Matrix with 1 or multiple columns
     *  \param[in] y
     *     dependent variable Eigen::Matrix with 1 or multiple columns
     *  \param[in] params
     *     plot parameters object of type plot2d::Params
     */
    template <class T1, class T2, int rows, int cols, int options, int max_rows,
              int max_cols>
    void Plot2d(const Eigen::Matrix<T1, rows, cols, options, max_rows, max_cols> x,
                const Eigen::Matrix<T2, rows, cols, options, max_rows, max_cols> y,
                const plot2d::Params params);
<br/>

    /** Convenience function for plotting two-dimensional data described by the
     *  provided function over the interval [x_min, x_max] as defined in the
     *  provided parameters
     *
     *  \param[in] f
     *     function you would like to plot (prototype cannot be ambiguous)
     *  \param[in] params
     *     plot parameters object of type plot2d::Params
     *  \param[in] n
     *     the number of points at which to define the discrete representation of
     *     the function [default is 100]
     */
    template <class CALLABLE>
    void Plot2d(const CALLABLE f, plot::plot2d::Params params,
                size_t n = 100);

### Convenience functions for plotting (plot::plot3d)

    /** Convenience function for plotting three-dimensional vector data
     *
     *  \param[in] x
     *     independent variable vector of type T1
     *  \param[in] y
     *     independent variable vector of type T2
     *  \param[in] z
     *     dependent variable vector of type T3
     *  \param[in] params
     *     plot parameters object of type plot3d::Params
     */
    template <class T1, class T2, class T3>
    void Plot3d(const std::vector<T1>& x, const std::vector<T2>& y,
                const std::vector<T3>& z, const plot3d::Params& params);
<br/>

    /** Convenience function for plotting multiple three-dimensional vector data
     *
     *  \param[in] x
     *     independent variable vector of vectors of type T1
     *  \param[in] y
     *     independent variable vector of vectors of type T2
     *  \param[in] z
     *     dependent variable vector of vectors of type T3
     *  \param[in] params
     *     plot parameters object of type plot3d::Params
     */
    template <class T1, class T2, class T3>
    void Plot3d(const std::vector<std::vector<T1> >& x,
                const std::vector<std::vector<T2> >& y,
                const std::vector<std::vector<T3> >& z,
                const plot3d::Params& params);
<br/>

    /** Convenience function for plotting three-dimensional vector data stored
     *  in the row(s) of cv::Mat_
     *
     *  \param[in] x
     *     independent variable cv::Mat_ with 1 or multiple rows
     *  \param[in] y
     *     independent variable cv::Mat_ with 1 or multiple rows
     *  \param[in] z
     *     dependent variable cv::Mat_ with 1 or multiple rows
     *  \param[in] params
     *     plot parameters object of type plot3d::Params
     */
    template <class T1, class T2, class T3>
    void Plot3d(const cv::Mat_<T1> x, const cv::Mat_<T2> y, const cv::Mat_<T3> z,
                const plot3d::Params params);
<br/>

    /** Convenience function for plotting a cv::Mat_ as a three-dimensional 
     *  surface plot (index values used to label the x and y axes)
     *
     *  \param[in] z
     *     dependent variable cv::Mat_ (single channel)
     *  \param[in] params
     *     plot parameters object of type plot3d::Params
     */
    template <class T1>
    void Plot3d(const cv::Mat_<T1> z, const plot3d::Params params);
<br/>

    /** Convenience function for plotting three-dimensional vector data stored
     *  in the column(s) of Eigen::Matrix (or Eigen::Vector)
     *
     *  \param[in] x
     *     independent variable Eigen::Matrix with 1 or multiple columns
     *  \param[in] y
     *     independent variable Eigen::Matrix with 1 or multiple columns
     *  \param[in] z
     *     dependent variable Eigen::Matrix with 1 or multiple columns
     *  \param[in] params
     *     plot parameters object of type plot3d::Params
     */
    template <class T1, class T2, class T3, int rows, int cols, int options,
              int max_rows, int max_cols>
    void Plot3d(const Eigen::Matrix<T1, rows, cols, options, max_rows, max_cols> x,
                const Eigen::Matrix<T2, rows, cols, options, max_rows, max_cols> y,
                const Eigen::Matrix<T3, rows, cols, options, max_rows, max_cols> z,
                const plot3d::Params params);
<br/>

    /** Convenience function for plotting three-dimensional data described by the
     *  provided function over the interval [x_min, x_max] and [y_min, y_max]
     *  as defined in the provided parameters
     *
     *  \param[in] f
     *     function you would like to plot (prototype cannot be ambiguous)
     *  \param[in] params
     *     plot parameters object of type plot3d::Params
     *  \param[in] nx
     *     the number of points in x at which to define the discrete
     *     representation of the function [default is 100]
     *  \param[in] ny
     *     the number of points in y at which to define the discrete
     *     representation of the function [default is 100]
     */
    template <class CALLABLE>
    void Plot3d(const CALLABLE f, plot::plot3d::Params params, size_t nx = 100,
                size_t ny = 100) {

# REQUIREMENTS
* C++ compiler that supports C++17 dialect/ISO standard
* Gnuplot installed on your system and present in your path

# DEPENDENCIES
* Boost.Iostreams
* OpenCV Core

