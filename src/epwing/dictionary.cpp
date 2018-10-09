#include <sstream>

#include "dictionary.h"
#include "gaiji/empty.h"
#include "gaiji/eplkup_chujiten.h"
#include "gaiji/eplkup_daijirin.h"
#include "gaiji/eplkup_daijisen.h"
#include "gaiji/eplkup_genius.h"
#include "gaiji/eplkup_kojien.h"
#include "gaiji/eplkup_meikyojj.h"
#include "gaiji/eplkup_meikyou.h"
#include "gaiji/eplkup_snmkg99.h"
#include "gaiji/eplkup_wadai5.h"
#include "exception.h"

using namespace std::literals::string_literals;

epwing::Dictionary::Dictionary(const DictionaryMetadata &metadata,
                               const epwing::gaiji::LookupTable &narrow_entries,
                               const epwing::gaiji::LookupTable &wide_entries,
                               epwing::GaijiReporter &reporter)
    : metadata{metadata}, reporter{reporter}, narrow_entries{narrow_entries}, wide_entries{wide_entries} {}

const epwing::Dictionary
epwing::Dictionary::from_sub_book_title(std::string_view title, GaijiReporter &reporter) {
//    if (title == titles::chujiten)
//      return Dictionary{gaiji::eplkup::chujiten::narrow(), gaiji::eplkup::chujiten::wide(), reporter};

    if (title == metadata::daijirin.sub_book_title)
        return Dictionary{metadata::daijirin,
                          gaiji::eplkup::daijirin::narrow(),
                          gaiji::eplkup::daijirin::wide(),
                          reporter};

    if (title == metadata::daijisen.sub_book_title)
        return Dictionary{metadata::daijisen,
                          gaiji::eplkup::daijisen::narrow(),
                          gaiji::eplkup::daijisen::wide(),
                          reporter};

    if (title == metadata::genius.sub_book_title)
        return Dictionary{metadata::genius,
                          gaiji::eplkup::genius::narrow(),
                          gaiji::eplkup::genius::wide(),
                          reporter};

    if (title == metadata::kojien_sub_book0.sub_book_title)
        return Dictionary{metadata::kojien_sub_book0,
                          gaiji::eplkup::kojien::narrow(),
                          gaiji::eplkup::kojien::wide(),
                          reporter};

    if (title == metadata::meikyojj.sub_book_title)
        return Dictionary{metadata::meikyojj,
                          gaiji::eplkup::meikyojj::narrow(),
                          gaiji::eplkup::meikyojj::wide(),
                          reporter};

//  if (title == metadata::meikyou.sub_book_title)
//      return Dictionary{gaiji::eplkup::meikyou::narrow(), gaiji::eplkup::meikyou::wide(), reporter};

    if (title == metadata::snmkg99.sub_book_title)
        return Dictionary{metadata::snmkg99,
                          gaiji::eplkup::snmkg99::narrow(),
                          gaiji::eplkup::snmkg99::wide(),
                          reporter};

    if (title == metadata::wadai5.sub_book_title)
        return Dictionary{metadata::wadai5,
                          gaiji::eplkup::wadai5::narrow(),
                          gaiji::eplkup::wadai5::wide(),
                          reporter};

    return Dictionary{DictionaryMetadata{std::string{title}, ""s, ""s},
                      gaiji::empty::narrow(),
                      gaiji::empty::wide(),
                      reporter};
}

const std::string epwing::Dictionary::narrow_utf8_replacement(unsigned int gaiji_code) const {
    if (auto it = narrow_entries.find(gaiji_code); it != narrow_entries.end()) {
        ++reporter.narrow_found;
        return it->second;
    }

    ++reporter.narrow_missed;
    std::ostringstream os;
    os << "{{ gaiji "s << gaiji_code << " }}"s;
    return os.str();
}

const std::string epwing::Dictionary::wide_utf8_replacement(unsigned int gaiji_code) const {
    if (auto it = wide_entries.find(gaiji_code); it != wide_entries.end()) {
        ++reporter.wide_found;
        return it->second;
    }

    ++reporter.wide_missed;
    std::ostringstream os;
    os << "{{ wide "s << gaiji_code << " }}"s;
    return os.str();
}

const std::string epwing::Dictionary::lang_from() const {
    return metadata.lang_from;
}

const std::string epwing::Dictionary::lang_to() const {
    return metadata.lang_to;
}
