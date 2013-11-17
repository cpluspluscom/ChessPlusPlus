/* png_split.cpp
 * 2013 Carl Schwope
 *
 * This progam takes a 480x160 png file name as an argument and splits
 * it into 16 well named 80x80 pngs.
 *
 * Before running the program, make sure that everything is backed up,
 * because it will overwrite existing files.
 *
 * A common error will be that the white and black folders do not exist
 * It is up to you to make them
 *
 * to compile make sure to set the include path to png++ and link to libpng
 * g++ png_split.cpp -o png_split -lpng
*/

#include <png++/image.hpp>
#include <png++/error.hpp>
#include <iostream>

// The file names to create.  This will overwrite exsiting files.
const char* file_names[] = {
  "white/pawn.png",
  "white/rook.png",
  "white/knight.png",
  "white/bishop.png",
  "white/queen.png",
  "white/king.png",
  "black/pawn.png",
  "black/rook.png",
  "black/knight.png",
  "black/bishop.png",
  "black/queen.png",
  "black/king.png"
};

// To keep track of which image to write
const size_t image_count = sizeof( file_names ) / sizeof( file_names[0] );
size_t current_image_id = 0;

// create an 80x80 png given the original png and x,y offsets
void process_image( const png::image< png::rgba_pixel >& image,
                    const size_t off_x, const size_t off_y )
{
  png::image< png::rgba_pixel > output( 80,80 );

  for ( size_t i = off_y; i < off_y + 80; ++i )
    for ( size_t j = off_x; j < off_x + 80; ++j )
      output.set_pixel( j - off_x , i - off_y , png::rgba_pixel( image[i][j] ));

  if ( current_image_id >= image_count )
    throw png::error("The current_image_id is out of range");

  output.write( file_names[ current_image_id++]  );
}

// load the file and do the thing
int main( int argc, char* argv[] )
{
  if ( argc != 2 )
  {
    std::cout << "Please supply a file name\n";
    return 1;
  }

  try
  {
    png::image< png::rgba_pixel > image(argv[1]);

    for ( size_t i = 0; i < image.get_height() ; i += 80 )
      for ( size_t j = 0; j < image.get_width() ; j += 80 )
        process_image( image, j, i );
  }
  catch ( const png::error& er )
  {
    std::cout << "error: ";
    std::cout << er.what() << std::endl;
  }
  catch ( const png::std_error& er )
  {
    std::cout << "std_error: ";
    std::cout << er.what() << std::endl;
  }

  return 0;
}
