#include "exporter.h"

#include "../src/epwing/deduplicator.h"
#include "../src/epwing/container.h"
#include "../src/epwing/converter_html5.h"
#include "../src/epwing/converter_xdxf.h"
#include "../src/epwing/dictionary.h"
#include "../src/epwing/exception.h"
#include "../src/epwing/library.h"
#include "../src/epwing/iconv.h"
#include "../src/epwing/book.h"
#include "../src/epwing/reporter_book.h"
#include "../src/epwing/reporter_container.h"
#include "../src/epwing/reporter_deduplicator.h"
#include "../src/epwing/reporter_sub_book.h"
#include "../src/epwing/reporter_hit_list.h"
#include "../src/epwing/reporter_word_code.h"
#include "../src/epwing/path.h"
#include "../src/epwing/printer_html5.h"
#include "../src/epwing/printer_xdxf.h"
#include "../src/epwing/container_factory.h"
#include "../src/format/path.h"
#include "../src/format/tidy.h"

extern "C" {
#include "../src/epwing/hooks.h"
}

DEFINE_string(epwing_directory, "", "top-level directory of EPWING dictionary");
DEFINE_string(exporter_errors_file, "", "output file for exporter errors");
DEFINE_string(tidy_errors_file, "", "output file for libtidy errors");
DEFINE_string(html5_file, "", "output file for html5 format");
DEFINE_string(metrics_file, "", "output file for exporter metrics");
DEFINE_string(xdxf_file, "", "output file for xdxf format");

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

// Search word inputs to control the behavior of eb_set_word.
// https://en.wikipedia.org/wiki/JIS_X_0208
// https://en.wiktionary.org/wiki/Index:Japanese_kanji_by_JIS_X_0208_kuten_code
// ftp://www.unicode.org/Public/MAPPINGS/OBSOLETE/EASTASIA/JIS/JIS0208.TXT
// http://ash.jp/code/unitbl21.htm

static gsl::czstring<> search_word_alphabet = "\x23\x61";   // u8"A";
static gsl::czstring<> search_word_kana = "\x24\x21";       // u8"あ";
static gsl::czstring<> search_word_other = "\xCE\xED";      // u8"零";

epwing::WordCodeReporter
run_search_word(epwing::Book &book,
                epwing::Deduplicator &deduplicator,
                epwing::Converter &converter,
                const epwing::ContainerFactory &container_factory,
                const epwing::Dictionary &dictionary,
                EB_Subbook_Code subbook_code,
                std::string_view search_word) {
    epwing::HitListReporter hit_list_reporter;
    epwing::ContainerReporter container_reporter;
    auto container = container_factory.get_instance(subbook_code, dictionary, container_reporter);

    try {
        book.search_word(search_word);
    } catch (epwing::LibraryError &e) {
        if (e.code() != EB_ERR_NO_SUCH_SEARCH) throw;
        return {container_reporter, hit_list_reporter};
    }

    converter.search_start(subbook_code);

    for (auto hit_list = book.hit_list(); !hit_list.empty(); hit_list = book.hit_list()) {
        for (auto &hit : hit_list) {
            ++hit_list_reporter.hits;

            auto hit_head_position = hit.heading;
            auto hit_text_position = hit.text;

            // http://www.mistys-internet.website/eb/doc/eb-08.html#unify-duplicated-entries

            book.seek_text(hit_head_position);
            auto heading = book.read_heading(nullptr, container);

            if (deduplicator.is_duplicate(hit, heading)) {
                ++hit_list_reporter.duplicates;
                continue;
            }

            converter.search_article_start(subbook_code);

            if (hit_head_position == hit_text_position) {
                ++hit_list_reporter.headings_skipped;
            } else {
                converter.search_article_heading(subbook_code, hit_head_position, heading);
            }

            book.seek_text(hit_text_position);
            auto text = book.read_text(nullptr, container);
            converter.search_article_text(subbook_code, hit_text_position, text);
            converter.search_article_stop();
        }
    }

    converter.search_stop();

    return {container_reporter, hit_list_reporter};
}

epwing::ContainerReporter
run_text(epwing::Book &book,
         epwing::Converter &converter,
         const epwing::ContainerFactory &container_factory,
         const epwing::Dictionary &dictionary,
         EB_Subbook_Code subbook_code) {
    EB_Position_Struct text_position{};
    epwing::ContainerReporter container_reporter;

    try {
        text_position = book.text();
    } catch (epwing::LibraryError &e) {
        if (e.code() != EB_ERR_NO_SUCH_SEARCH) throw;
        return container_reporter;
    }

    book.seek_text(text_position);

    auto container = container_factory.get_instance(subbook_code, dictionary, container_reporter);
    converter.text_start(subbook_code, text_position);
    while (!book.is_text_stopped() && book.get_error_code() != EB_ERR_END_OF_CONTENT) {
        auto text = book.read_text(nullptr, container);
        converter.text_article(subbook_code, text);
        book.forward_text();
    }
    converter.text_stop();

    return container_reporter;
}

const std::string
run_title(epwing::Book &book) {
    auto title_iconv = epwing::IConv::from_character_code(book.get_character_code());
    auto subbook_title = book.subbook_title();
    return title_iconv.to_utf8(subbook_title);
}

epwing::SubBookReporter
run_sub_book(epwing::Book &book,
             epwing::Converter &converter,
             const epwing::ContainerFactory &container_factory,
             const epwing::Dictionary &dictionary,
             EB_Subbook_Code subbook_code) {
    epwing::DeduplicatorReporter deduplicator_reporter;
    epwing::Deduplicator deduplicator{deduplicator_reporter};

    book.set_subbook(subbook_code);

    converter.subbook_start(subbook_code);

    const auto title_utf8 = run_title(book);

    converter.subbook_title(subbook_code, title_utf8);

    auto textcr = run_text(book, converter, container_factory, dictionary, subbook_code);

    auto awcr = run_search_word(book, deduplicator, converter, container_factory,
                                dictionary, subbook_code, search_word_alphabet);

    auto kwcr = run_search_word(book, deduplicator, converter, container_factory,
                                dictionary, subbook_code, search_word_kana);

    auto owcr = run_search_word(book, deduplicator, converter, container_factory,
                                dictionary, subbook_code, search_word_other);

    converter.subbook_stop();

    return {textcr, awcr, kwcr, owcr};
}

epwing::BookReporter
run_book(epwing::Book &book,
         const epwing::ContainerFactory &container_factory,
         epwing::Converter &converter,
         const epwing::Dictionary &dictionary,
         epwing::GaijiReporter &gaiji_reporter) {
    converter.book_start();

    std::vector<epwing::SubBookReporter> sub_book_reporters;
    for (auto const &subbook_code : book.subbook_list()) {
        auto sub_book_reporter = run_sub_book(book, converter, container_factory, dictionary, subbook_code);
        sub_book_reporters.push_back(std::move(sub_book_reporter));
    }

    converter.book_stop();

    return {gaiji_reporter, sub_book_reporters};
}

void
run_report(const epwing::path &metrics_file, const epwing::BookReporter &book_reporter) {
    if (metrics_file.empty() || metrics_file == "-") {
        book_reporter.report(std::cerr);
    } else {
        epwing::path report_file{FLAGS_metrics_file};
        std::ofstream report_stream{report_file};
        book_reporter.report(report_stream);
    }
}

void
run_export_xml(const epwing::path &output_file,
               const epwing::path &metrics_file,
               const epwing::ContainerFactory &container_factory,
               epwing::Book &book,
               const epwing::Dictionary &dictionary,
               epwing::GaijiReporter &gaiji_reporter) {
    std::ofstream os{output_file};
    epwing::XDXFConverter converter{dictionary.lang_from(), dictionary.lang_to(), os};
    auto book_reporter = run_book(book, container_factory, converter, dictionary, gaiji_reporter);
    run_report(metrics_file, book_reporter);
}

void
run_export_html(const epwing::path &output_file,
                const epwing::path &metrics_file,
                const epwing::ContainerFactory &container_factory,
                epwing::Book &book,
                const epwing::Dictionary &dictionary,
                epwing::GaijiReporter &gaiji_reporter) {
    std::ofstream os{output_file};
    epwing::HTML5Converter converter{os};
    auto book_reporter = run_book(book, container_factory, converter, dictionary, gaiji_reporter);
    run_report(metrics_file, book_reporter);
}

int
run_tidy(format::Tidy &tidy) {
    if (tidy.format(); tidy.report() != format::TidyResult::ok)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int
main(int argc, char *argv[]) try {
    std::ios_base::sync_with_stdio(false);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    gflags::SetUsageMessage("Converts EPWING dictionaries to HTML5 or XDXF format."s);

    epwing::path input_directory{FLAGS_epwing_directory};
    epwing::path metrics_file{FLAGS_metrics_file};
    epwing::path exporter_errors_file{FLAGS_exporter_errors_file};
    format::path tidy_errors_file{FLAGS_tidy_errors_file};

    epwing::Library library;

    epwing::Book book{input_directory};
    book.set_hooks(TEXT_HOOKS);

    book.set_subbook(0);
    const auto title_utf8 = run_title(book);
    epwing::GaijiReporter gaiji_reporter{};
    auto dictionary = epwing::Dictionary::from_sub_book_title(title_utf8, gaiji_reporter);

    auto iconv_euc_jp = epwing::IConv::FromEucJp();
    auto iconv_gb2312 = epwing::IConv::FromGb2312();
    auto iconv_iso8859_1 = epwing::IConv::FromISO8859_1();

    if (!FLAGS_html5_file.empty()) {
        epwing::path input_output_file{FLAGS_html5_file};
        epwing::HTML5ContainerFactory container_factory{iconv_euc_jp, iconv_gb2312, iconv_iso8859_1};
        run_export_html(input_output_file, metrics_file, container_factory, book, dictionary, gaiji_reporter);

        auto tidy = format::Tidy::html(input_output_file, tidy_errors_file);
        return run_tidy(tidy);
    } else if (!FLAGS_xdxf_file.empty()) {
        epwing::path input_output_file{FLAGS_xdxf_file};
        epwing::XDXFContainerFactory container_factory{iconv_euc_jp, iconv_gb2312, iconv_iso8859_1};
        run_export_xml(input_output_file, metrics_file, container_factory, book, dictionary, gaiji_reporter);

        auto tidy = format::Tidy::xml(input_output_file, tidy_errors_file);
        return run_tidy(tidy);
    } else {
        gflags::ShowUsageWithFlags(argv[0]);
        return EXIT_FAILURE;
    }
} catch (const std::exception &e) {
    std::cerr << __func__ << ": unhandled exception: "s << e.what()
              << '\n';
    return EXIT_FAILURE;
} catch (...) {
    std::cerr << __func__ << ": unhandled exception\n"s;
    return EXIT_FAILURE;
}
