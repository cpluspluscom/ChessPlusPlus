#if !defined( _DEBUG_LOGGER_H )
#define _DEBUG_LOGGER_H

#if defined _DEBUG

  #include <fstream>

  namespace chesspp
  {
    /////////////////////////////////////////////////////////////////////////////
    // Name: DebugLogFile
    // Desc: A simple class that's used to output debugging information so that 
    //       we can avoid using the console.
    /////////////////////////////////////////////////////////////////////////////
    class DebugLogFile
    {
      public:
        DebugLogFile( const char *FileName = "DebugOutput.txt" );
       ~DebugLogFile( ); 

        void LogMessage( const char *Message );

      private:
        // Disallow copying because we only need a single debug file. Objections?
        DebugLogFile( DebugLogFile & );
        DebugLogFile &operator = ( DebugLogFile & );

        std::ofstream OutFile_;
    };

    inline DebugLogFile::DebugLogFile( const char *FileName )
      : OutFile_( ( FileName ) ? FileName : "DefaultDebugFile.txt" )
    { 
    }

    inline DebugLogFile::~DebugLogFile( )
    {
      OutFile_.close( );
    }

    inline void DebugLogFile::LogMessage( const char *Message )
    {
      if( ( OutFile_.is_open( ) ) && ( Message ) )
      {
        OutFile_ << Message << '\n';
      }
    }
  }

#endif

#endif
