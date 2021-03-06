// __BEGIN_LICENSE__
//  Copyright (c) 2006-2013, United States Government as represented by the
//  Administrator of the National Aeronautics and Space Administration. All
//  rights reserved.
//
//  The NASA Vision Workbench is licensed under the Apache License,
//  Version 2.0 (the "License"); you may not use this file except in
//  compliance with the License. You may obtain a copy of the License at
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// __END_LICENSE__


/// \KML
///
/// Provides support for writing Google Earth KMLs. At the moment the
/// focus is support for placemarks.
///
#ifndef __VW_FILEIO_KML_H__
#define __VW_FILEIO_KML_H__

// STL
#include <string>
#include <fstream>
#include <stack>

// Vision Workbench
#include <vw/Math/Vector.h>
#include <vw/Math/Quaternion.h>

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/fstream.hpp>

namespace vw {

  // TabCount:
  // Used to keep track of tabbing in KML File
  struct TabCount {
    int count;
  };

  std::ostream& operator<<( std::ostream& os, TabCount const& tab);

  // KMLFile:
  // Class wrapper for KML file.
  class KMLFile {
    boost::filesystem::ofstream m_output_file;
    TabCount m_tab;
    std::string m_filename;   // Output filename
    std::string m_name;       // What the file refers to itself as
    std::string m_directory;  // Directory location (used for trees)
    std::stack<std::string> m_bracket_names;
  public:
    KMLFile( std::string filename,
             std::string name,
             std::string directory="" );
    ~KMLFile(); // Closes file out

    // Access internal
    std::string filename() const { return m_filename; }
    std::string name() const { return m_name; }
    std::string directory() const { return m_directory; }

    // Lower Level Writing Functions
    void open_bracket( std::string name );
    void close_bracket();
    void close_brackets( int );
    void close_all_brackets();

    // Low Level Functions
    void enter_folder( std::string name="",
                       std::string description="" );
    void exit_folder();
    void append_placemark( double lon, double lat,
                           std::string name="",
                           std::string description="",
                           std::string style="",
                           double altitude=0,
                           bool extrude=false );
    void append_model( std::string path_to_model,
                       double lon, double lat,
                       vw::Quaternion<double> pose,
                       std::string name,
                       std::string description,
                       double altitude,
                       double scale );
    void append_latlonaltbox( float north,
                              float south,
                              float east,
                              float west );
    void append_lod( float min, float max );
    void append_style( std::string id, std::string color_hex,
                       float scale, std::string image_url );
    void append_stylemap( std::string id,
                          std::string style_normal,
                          std::string style_highlight );
    void append_network( std::string link,
                         double north, double south,
                         double east, double west );

    void close_kml(); // If it seems the file wasn't finished, try this.
  protected:
    void open_kml();

  };

  // High Level Tools!
  // Not Existing Yet!
}

#endif//__VW_FILEIO_KML_H__
