//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/version.hpp>
#include <util/reflect.hpp>
#include <config.hpp>

// ----------------------------------------------------------------------------- : Version

UInt Version::toNumber() const { return version; }

String Version::toString() const {
  if (version > 20000000) {
    // major > 2000, the version is a date, use ISO notation
    return String::Format(_("%04d-%02d-%02d"),
          (version / 10000)      ,
          (version / 100)   % 100,
          (version / 1)     % 100);
  } else {
    return String::Format(_("%d.%d.%d"),
          (version / 10000)      ,
          (version / 100)   % 100,
          (version / 1)     % 100);
  }
}

Version Version::fromString(const String& version) {
  UInt major = 0, minor = 0, build = 0;
  if (wxSscanf(version, _("%u.%u.%u"), &major, &minor, &build)<=1)  // a.b.c style
      wxSscanf(version, _("%u-%u-%u"), &major, &minor, &build);  // date style
  return Version(major * 10000 + minor * 100 + build);
}


template <> void Reader::handle(Version& v) {
  v = Version::fromString(getValue());
}
template <> void Writer::handle(const Version& v) {
  handle(v.toString());
}
template <> void GetDefaultMember::handle(const Version& v) {
  handle(v.toNumber());
}

// ----------------------------------------------------------------------------- : Versions

// NOTE: Don't use leading zeroes, they mean octal
const Version app_version  = 10000 * MSE_VERSION_MAJOR + 100 * MSE_VERSION_MINOR + MSE_VERSION_PATCH;

#if defined UNOFFICIAL_BUILD
const Char* version_suffix = _(" (Unofficial)");
#elif defined UNICODE
const Char* version_suffix = _("");
#else
const Char* version_suffix = _(" (ascii build)");
#endif

/// Which version of MSE are the files we write out compatible with?
/*  The saved files will have these version numbers attached.
 *  They should be updated whenever a change breaks backwards compatability.
 *
 *  Changes:
 *     0.2.0 : start of version numbering practice
 *     0.2.2 : _("include file")
 *     0.2.6 : fix in settings loading
 *     0.2.7 : new tag system, different style of close tags
 *     0.3.0 : port of code to C++
 *     0.3.1 : new keyword system, some new style options
 *     0.3.2 : package dependencies
 *     0.3.3 : keywor
 d separator before/after
 *     0.3.4 : html export; choice rendering based on scripted 'image'
 *     0.3.5 : word lists, symbol font 'as text'
 *     0.3.6 : free rotation, rotation behaviour changed.
 *     0.3.7 : scripting language changes (@ operator, stricter type conversion).
 *     0.3.8 : - check_spelling function
 *             - tag_contents function fixed
 *             - alignment:justify behavior changed
 *             - more scriptable fields.
 *             - store time created,modified for cards -> changes set and clipboard format
 *     0.3.9 : bugfix release mostly, a few new script functions
 *     2.0.0 : bugfix release mostly, added error console
 *     2.0.2 : store game and stylesheet version numbers
 */
const Version file_version_locale          = 20002; // 2.0.2
const Version file_version_set             = 20002; // 2.0.2
const Version file_version_game            =   308; // 0.3.8
const Version file_version_stylesheet      =   308; // 0.3.8
const Version file_version_symbol_font     =   306; // 0.3.6
const Version file_version_export_template =   307; // 0.3.7
const Version file_version_installer       =   307; // 0.3.7
const Version file_version_symbol          =   305; // 0.3.5
const Version file_version_clipboard       = 20002; // 2.0.2
const Version file_version_script          =   307; // 0.3.7
