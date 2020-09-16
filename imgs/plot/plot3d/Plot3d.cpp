/** Implementation file for three-dimensional plotting
 *
 *  \file imgs/plot/plot3d/Plot3d.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 19 April 2020
 */

#include <iostream>

#include "imgs/plot/plot3d/Params.h"

using namespace std;

namespace plot::plot3d {

void set_common_parameters(string& gp_msg, const plot3d::Params& params) {
  if (params.destination_filename() == "") {
    gp_msg += "set terminal ";
    gp_msg += params.terminal_type();
    gp_msg += " font \"";
    gp_msg += params.font_face();
    gp_msg += ",";
    gp_msg += to_string(params.font_size());
    gp_msg += "\"\n";
  } else {
    string f = params.destination_filename();
    string extension = f.substr(f.length() - 4);
    if (extension == ".eps") {
      gp_msg += "set terminal postscript color ";
      gp_msg += "\"";
      gp_msg += params.font_face();
      gp_msg += "\" ";
      gp_msg += to_string(params.font_size());
      gp_msg += "\n";
      gp_msg += "set output '" + f + "'\n";
    } else if (extension == ".png") {
      gp_msg += "set terminal png "; 
      gp_msg += "font \"";
      gp_msg += params.font_face();
      gp_msg += "\" ";
      gp_msg += to_string(params.font_size());
      gp_msg += "\n";
      gp_msg += "set output '" + f + "'\n";
    } else {                   
      cerr << "*** ERROR *** ";                                                       cerr << "Destination file format not supported, using default terminal "  
              "type"                
           << endl;             
      gp_msg += "set terminal ";       
      gp_msg += params.terminal_type();
      gp_msg += " font \"";        
      gp_msg += params.font_face();
      gp_msg += ",";                          
      gp_msg += to_string(params.font_size());
      gp_msg += "\"\n";             
    }
  }                       
  gp_msg += "unset key\n";
  gp_msg += "set xlabel '" + params.x_label() + "'\n";
  gp_msg += "set ylabel '" + params.y_label() + "'\n";
  gp_msg += "set zlabel '" + params.z_label() + "'\n";
  gp_msg += "set title '" + params.title() + "'\n";
  gp_msg += "set hidden3d\n";
  gp_msg += "set view " + to_string(params.declination()) + ", " +
            to_string(params.azimuth()) + ", " + to_string(params.scale()) +
            ", " + to_string(params.z_scale()) + "\n";
  if (params.x_min() < params.x_max()) {
    gp_msg += "set xrange [" + to_string(params.x_min()) + ":" +
              to_string(params.x_max()) + "]\n";
  }
  if (params.y_min() < params.y_max()) {
    gp_msg += "set yrange [" + to_string(params.y_min()) + ":" +
              to_string(params.y_max()) + "]\n";
  }
  if (params.z_min() < params.z_max()) {
    gp_msg += "set zrange [" + to_string(params.z_min()) + ":" +
              to_string(params.z_max()) + "]\n";
  }
  if (params.x_tics()) {
    gp_msg += "set grid xtics\n";
  }
  if (params.y_tics()) {
    gp_msg += "set grid ytics\n";
  }
  if (params.z_tics()) {
    gp_msg += "set grid ztics\n";
  }
  if (params.mesh()) {
    if (params.mesh_x_size() > 0 && params.mesh_y_size() > 0) {
      gp_msg += "set dgrid3d " + to_string(params.mesh_x_size()) + "," +
                to_string(params.mesh_y_size()) + " splines\n";
    } else if (params.mesh_x_size() > 0 && params.mesh_y_size() == 0) {
      gp_msg += "set dgrid3d " + to_string(params.mesh_x_size()) + "," +
                to_string(params.mesh_x_size()) + " splines\n";
    } else if (params.mesh_x_size() == 0 && params.mesh_y_size() > 0) {
      gp_msg += "set dgrid3d " + to_string(params.mesh_y_size()) + "," +
                to_string(params.mesh_y_size()) + " splines\n";
    } else {
      gp_msg += "set dgrid3d splines\n";
    }
  }
  if (params.palette_mapping()) {
    gp_msg += "set pm3d\n";
  }
}
}
