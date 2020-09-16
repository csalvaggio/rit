from conans import ConanFile, CMake

class RitConan(ConanFile):
   settings = \
      'os', \
      'compiler', \
      'build_type', \
      'arch'

   requires = \
      'boost/1.73.0', \
      'eigen/3.3.7', \
      'opencv/4.3.0@conan/stable'

   generators = \
      'cmake'

   default_options = \
      {
         'boost:shared': True, 
         'opencv:shared': True
      }

   def imports(self):
      self.copy('*.dll', dst='bin', src='bin') # From bin to bin

   def configure(self):
      if self.settings.os == 'Macos':
         pass
      if self.settings.os == 'Windows':
         pass
      if self.settings.os == 'Linux':
         pass
