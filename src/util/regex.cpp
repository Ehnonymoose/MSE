//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) 2001 - 2012 Twan van Laarhoven and Sean Hunt             |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/regex.hpp>
#include <util/error.hpp>

#if USE_BOOST_REGEX
// ----------------------------------------------------------------------------- : Regex : boost

void Regex::assign(const String& code) {
	// compile string
	try {
		regex.assign(code.begin(),code.end());
	} catch (const boost::regex_error& e) {
		/// TODO: be more precise
		throw ScriptError(String::Format(_("Error while compiling regular expression: '%s'\nAt position: %d\n%s"),
		                  code.c_str(), e.position(), String(e.what(), IF_UNICODE(wxConvUTF8,String::npos)).c_str()));
	}
}

void Regex::replace_all(String* input, const String& format) {
	std::wstring wsFormat = format.ToStdWstring();
	std::wstring wsInput = input->ToStdWstring();

	std::wstring output;
	regex_replace(insert_iterator<std::wstring>(output, output.end()),
	              wsInput.begin(), wsInput.end(), regex, wsFormat, boost::format_sed);
	*input = wxString(output);
}

#else // USE_BOOST_REGEX
// ----------------------------------------------------------------------------- : Regex : wx

void Regex::assign(const String& code) {
	// compile string
	if (!regex.Compile(code, wxRE_ADVANCED)) {
		throw ScriptError(_("Error while compiling regular expression: '") + code + _("'"));
	}
	assert(regex.IsValid());
}

#endif // USE_BOOST_REGEX
// ----------------------------------------------------------------------------- : Regex : common
