/*ckwg +29
 * Copyright 2013-2015 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "token_expander.h"

#include "token_type.h"

#include <boost/regex.hpp>

#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>

namespace kwiver {
namespace vital {

// ----------------------------------------------------------------
/** Constructor.
 *
 *
 */
token_expander::
token_expander()
  : m_logger( kwiver::vital::get_logger( "token_expander" ) )
{  }

token_expander::
~token_expander()
{  }


// ----------------------------------------------------------------
/* Add token type to expander.
 *
 *
 */
bool
token_expander::
add_token_type (kwiver::vital::token_type * tt)
{
  std::string name( tt->token_type_name() );
  result_t res = m_typeList.insert( name, tt );

  return res.second;
}


// ----------------------------------------------------------------
/* Look for tokens to expand.
 *
 * The syntax of the token is "$TYPE{name}".  The \c TYPE string is
 * used to locate the token type object that can provide the desired
 * text.  The \c name string, if present, is passed to the token typ
 * object to specify what result is desired.
 *
 * @param initial_string - string with token specifications embedded
 *
 * @return A string with all token references filled in.
 */
std::string
token_expander::
expand_token( std::string const& initial_string )
{
  std::string new_value;
  static const boost::regex exp( "\\$([a-zA-Z][a-zA-Z0-9_]*)\\{([a-zA-Z0-9_:]+)?\\}" );

  boost::match_results< std::string::const_iterator > what;
  std::string::const_iterator start, end;
  start = initial_string.begin();
  end = initial_string.end();

  // while ( boost::regex_search( new_value, what, exp ) )
  while ( boost::regex_search( start, end, what, exp ) )
  {
    // what[0] - whole match
    // what[1] - token type
    // what[2] - optional name

    // look for the specified token type
    iterator_t ix = m_typeList.find( what[1] );
    if ( ix != m_typeList.end() )
    {
      // lookup token value
      std::string result;
      ix->second->lookup_entry( what[2], result );

      LOG_DEBUG( m_logger, "Substituting: " << "\"" << what.str() << "\" -> \"" << result << "\"" );

      // append everything up to the match
      new_value.append( start, start + what.position() );

      // Append the replacement string
      new_value.append( result );
    }
    else
    {
      // no substitution, copy forward original text
      new_value.append( start, start + what.position() + what.length() );
    }

    // Update matching pointers
    start += what.position() + what.length();

  } // end while

  // copy what's left
  new_value.append( start, end );

  return new_value;
} // expand_token

} } // end namespace
