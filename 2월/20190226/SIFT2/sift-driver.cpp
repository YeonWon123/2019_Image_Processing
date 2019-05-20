// file:        sift-driver.cpp
// author:      Andrea Vedaldi
// description: SIFT command line utility implementation

// AUTORIGTHS

#include "sift.hpp"

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<limits>

extern "C" {
	/* Declarations for getopt.
	   Copyright (C) 1989-2019 Free Software Foundation, Inc.
	   NOTE: The canonical source of this file is maintained with the GNU C Library.
	   Bugs can be reported to bug-glibc@gnu.org.
	   This program is free software; you can redistribute it and/or modify it
	   under the terms of the GNU General Public License as published by the
	   Free Software Foundation; either version 2, or (at your option) any
	   later version.
	   This program is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	   GNU General Public License for more details.
	   You should have received a copy of the GNU General Public License
	   along with this program; if not, write to the Free Software
	   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301,
	   USA.  */

#ifndef _GETOPT_H
#define _GETOPT_H 1

#ifdef	__cplusplus
	extern "C" {
#endif

		/* For communication from `getopt' to the caller.
		   When `getopt' finds an option that takes an argument,
		   the argument value is returned here.
		   Also, when `ordering' is RETURN_IN_ORDER,
		   each non-option ARGV-element is returned here.  */

		extern char *optarg;

		/* Index in ARGV of the next element to be scanned.
		   This is used for communication to and from the caller
		   and for communication between successive calls to `getopt'.
		   On entry to `getopt', zero means this is the first call; initialize.
		   When `getopt' returns -1, this is the index of the first of the
		   non-option elements that the caller should itself scan.
		   Otherwise, `optind' communicates from one call to the next
		   how much of ARGV has been scanned so far.  */

		extern int optind;

		/* Callers store zero here to inhibit the error message `getopt' prints
		   for unrecognized options.  */

		extern int opterr;

		/* Set to an option character which was unrecognized.  */

		extern int optopt;

		/* Describe the long-named options requested by the application.
		   The LONG_OPTIONS argument to getopt_long or getopt_long_only is a vector
		   of `struct option' terminated by an element containing a name which is
		   zero.
		   The field `has_arg' is:
		   no_argument		(or 0) if the option does not take an argument,
		   required_argument	(or 1) if the option requires an argument,
		   optional_argument 	(or 2) if the option takes an optional argument.
		   If the field `flag' is not NULL, it points to a variable that is set
		   to the value given in the field `val' when the option is found, but
		   left unchanged if the option is not found.
		   To have a long-named option do something other than set an `int' to
		   a compiled-in constant, such as set a value from `optarg', set the
		   option's `flag' field to zero and its `val' field to a nonzero
		   value (the equivalent single-letter option character, if there is
		   one).  For long options that have a zero `flag' field, `getopt'
		   returns the contents of the `val' field.  */

		struct option
		{
#if defined (__STDC__) && __STDC__
			const char *name;
#else
			char *name;
#endif
			/* has_arg can't be an enum because some compilers complain about
			   type mismatches in all the code that assumes it is an int.  */
			int has_arg;
			int *flag;
			int val;
		};

		/* Names for the values of the `has_arg' field of `struct option'.  */

#define	no_argument		0
#define required_argument	1
#define optional_argument	2

#if defined (__STDC__) && __STDC__
/* HAVE_DECL_* is a three-state macro: undefined, 0 or 1.  If it is
   undefined, we haven't run the autoconf check so provide the
   declaration without arguments.  If it is 0, we checked and failed
   to find the declaration so provide a fully prototyped one.  If it
   is 1, we found it so don't provide any declaration at all.  */
#if !HAVE_DECL_GETOPT
#if defined (__GNU_LIBRARY__) || defined (HAVE_DECL_GETOPT)
   /* Many other libraries have conflicting prototypes for getopt, with
	  differences in the consts, in unistd.h.  To avoid compilation
	  errors, only prototype getopt for the GNU C library.  */
		extern int getopt(int argc, char *const *argv, const char *shortopts);
#else
#ifndef __cplusplus
		extern int getopt();
#endif /* __cplusplus */
#endif
#endif /* !HAVE_DECL_GETOPT */

		extern int getopt_long(int argc, char *const *argv, const char *shortopts,
			const struct option *longopts, int *longind);
		extern int getopt_long_only(int argc, char *const *argv,
			const char *shortopts,
			const struct option *longopts, int *longind);

		/* Internal only.  Users should not call this directly.  */
		extern int _getopt_internal(int argc, char *const *argv,
			const char *shortopts,
			const struct option *longopts, int *longind,
			int long_only);
#else /* not __STDC__ */
		extern int getopt();
		extern int getopt_long();
		extern int getopt_long_only();

		extern int _getopt_internal();
#endif /* __STDC__ */

#ifdef	__cplusplus
	}
#endif

#endif /* getopt.h */
}

using namespace std ;

int
main(int argc, char** argv)
{
  int first    = -1 ;
  int octaves  = -1 ;
  int levels   = 3 ;
  int nodescr  = 0 ;
  int noorient = 0 ;
  int savegss  = 0 ;
  int verbose  = 0 ;
  std::string prefix("") ;

  static struct option longopts[] = {
    { "verbose",         no_argument,            NULL,              'v' },
    { "help",            no_argument,            NULL,              'h' },
    { "output",          required_argument,      NULL,              'o' },
    { "first-octave",    required_argument,      NULL,              'f' },
    { "octaves",         required_argument,      NULL,              'O' },
    { "levels",          required_argument,      NULL,              'S' },
    { "no-descriptors",  no_argument,            &nodescr,          1   },
    { "no-orientations", no_argument,            &noorient,         1   },
    { "save-gss",        no_argument,            &savegss,          1   },
    { NULL,              0,                      NULL,              0   }
  };

  int ch ;
  try {
    while ( (ch = getopt_long(argc, argv, "hvo:O:S:", longopts, NULL)) != -1) {
      switch (ch) {

      case '?' :
        VL_THROW("Invalid option '" << argv[optind-1] << "'.") ;
        break;
        
      case ':' :
        VL_THROW("Missing option argument for '" << argv[optind-1] << "'.") ;
        break;
        
      case 'h' :
        std::cout
          << argv[0] << " [--verbose] [--help] [--output OUTPREFIX]" << endl
          << "   [--save-gss] [--no-descriptors] [--no-orientations] " << endl
          << "   [--levels NLEVELS] [--octaves NOCTAVES] [--first-octave FIRSTOCTAVE] " << endl
          << "   IMAGE [IMAGE2 ...]" << endl ;
        return 0 ;

      case 'v' :
        verbose = 1 ;
        break ;
        
      case 'f': // first octave
        {
          std::istringstream iss(optarg) ;
          iss >> first ;
          if( iss.fail() )
            VL_THROW("Invalid argument '" << optarg << "'.") ;
        }
        break ;
        
      case 'O' : // octaves
        {
          std::istringstream iss(optarg) ;
          iss >> octaves ;
          if( iss.fail() )
            VL_THROW("Invalid argument '" << optarg << "'.") ;
          if( octaves < 1 ) {
            VL_THROW("Number of octaves cannot be smaller than one."); 
          }
        }
        break ;
        
      case 'S' : // levels
        {
          std::istringstream iss(optarg) ;
          iss >> levels ;
          if( iss.fail() )
            VL_THROW("Invalid argument '" << optarg << "'.") ;
          if( levels < 1 ) {
            VL_THROW("Number of levels cannot be smaller than one.") ;
          }
        }      
        break ;

      case 'o' : // output
        {
          prefix = std::string(optarg) ;
          break ;
        }
        
      case 0 : // all other options
        break ;
        
      default:
        assert(false) ;
      }
    }
    
    argc -= optind;
    argv += optind;

    if( argc == 0 ) VL_THROW("No input image specfied.") ;
    if( prefix.size() != 0 && argc > 1 ) {
      VL_THROW("--output cannot be used with multiple images.") ;
    }
  }
  catch( VL::Exception const & e ) {
    std::cerr<<"error: "<<e.msg<<std::endl ;
    exit(1) ;
  }  

  while( argc > 0 ) {
    VL::PgmBuffer buffer ;

    std::string name(argv[0]) ;
    
    // get prefix
    if( prefix.size() == 0 ) {
      int i ;
      std::size_t const not_found = std::numeric_limits<std::size_t>::max() - 1 ;
      if(  ( (i = name.rfind(".pgm",not_found)) != not_found ) ||
           ( (i = name.rfind(".PGM",not_found)) != not_found )  ) {
        prefix = std::string(name, 0, i) ;
      } else {
        prefix = name ;
      }
    }

    // ---------------------------------------------------------------
    //                                                  Load PGM image
    // ---------------------------------------------------------------    
    try {          
      ifstream in( name.c_str() ) ; 
      if(! in.good()) VL_THROW("Could not open '"<< name <<"'.") ;      
      extractPgm( in, buffer ) ;
    }    
    catch( VL::Exception const& e ) {
      cerr<<e.msg<<endl ;
      return 1 ;
    }
    
    if( verbose )
      cout << "Loaded PGM image ("
           << buffer.width<<" x "<<buffer.height<<")."
           << endl ;

    // ---------------------------------------------------------------
    //                                            Gaussian scale space
    // ---------------------------------------------------------------    
    if( verbose ) 
      cout << "Computing Gaussian scale space ... " << std::flush ;

    int         O      = octaves ;    
    int const   S      = levels ;
    int const   omin   = first ;
    float const sigman = .5 ;
    float const sigma0 = 1.6 * powf(2.0f, 1.0f / S) ;

    // autoselect of number of octaves?
    if( O < 1 ) {
      O = 
        std::max
        ( int(floor(log2(std::min(buffer.width,buffer.height))) - omin -4),
          1 ) ;
    }
    
    VL::Sift sift( buffer.data, buffer.width, buffer.height, 
                   sigman, sigma0,
                   O, S,
                   omin, -1, S+1 ) ;

    if(verbose) 
      cout << "(" << O << " octaves starting from " << omin <<", "
           << S << " levels) done." << endl ;

    // ---------------------------------------------------------------
    //                                       Save Gaussian scale space
    // ---------------------------------------------------------------    

    if( savegss ) {
      if(verbose) 
        cout << "Saving Gaussian scale space." << endl ;

      for(int o = omin ; o < omin + O ; ++o) {
        for(int s = 0 ; s < S ; ++s ) {

          std::ostringstream suffix ;
          suffix<<'.'<<o<<'.'<<s<<".pgm" ;
          std::string outname = prefix + suffix.str() ;

          if(verbose) 
            cout << "Saving octave " <<o
                 << " level "<<s
                 << " to '"<< outname << "' ... " << std::flush ;
          
          ofstream out( outname.c_str() ) ;          
          VL::insertPgm( out,
                         sift.getLevel(o,s),
                         sift.getOctaveWidth(o),
                         sift.getOctaveHeight(o) ) ;
          
          if(verbose) cout << "done." <<endl ;
        }
      }
    }
    
    // ---------------------------------------------------------------
    //                                                   SIFT detector
    // ---------------------------------------------------------------    
    
    if(verbose) 
      cout << "Running SIFT detector ... " << std::flush ;

    sift.detectKeypoints() ;

    if(verbose) 
      cout << "done (" 
           << sift.keypointsEnd() - sift.keypointsBegin() 
           << " keypoints)." << endl ;

    // ---------------------------------------------------------------
    //                               SIFT orientations and descriptors
    // ---------------------------------------------------------------    

    if( verbose ) {
      if( ! noorient &&   nodescr) cout << "Computing keypoint orientations" ;
      if(   noorient && ! nodescr) cout << "Computing keypoint descriptors" ;
      if( ! noorient && ! nodescr) cout << "Computing orientations and descriptors" ;
      if(   noorient &&   nodescr) cout << "Finalizing" ; 
    }

    {
      std::string outname = prefix + ".key" ;
      ofstream out( outname.c_str() ) ;
      
      if(verbose)
        std::cout << " (saving keypoints to '" << outname << "') ... " 
                  << std::flush ;
      
      for( VL::Sift::KeypointsConstIter iter = sift.keypointsBegin() ;
           iter != sift.keypointsEnd() ;
           ++iter ) {
        
        // detect orientations
        float angles [4] ;
        int nangles ;
        if( ! noorient ) {
          nangles = sift.computeKeypointOrientations(angles, *iter) ;
        } else {
          nangles = 1;
          angles[0] = 0.0f ;
        }
        
        // compute descriptors
        for(int a = 0 ; a < nangles ; ++a) {
          
          out << iter->x << " "
              << iter->y << " "
              << iter->sigma ;
          
          if( ! noorient ) {
            out << " " << angles[a] ;
          }
          
          if( ! nodescr ) {
            float descr [128] ;
            sift.computeKeypointDescriptor(descr, *iter, angles[a]) ;
            for(int i = 0 ; i < 128 ; ++i) {
              out << " " << (int)( 512.0f * descr[i] ) ;
            }
          }

          // next keypoint
          out << endl ;
        } 
      } 
      
        
      if(verbose)
        std::cout << "done." << std::endl ;
    }
    
    argc-- ;
    argv++ ;
  } // next image

  return 0 ;
}
