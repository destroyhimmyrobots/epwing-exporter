## EPWING Exporter

_EPWING Exporter_ is a program that converts dictionaries from EPWING format
to either [XDXF](https://github.com/soshial/xdxf_makedict/blob/master/format_standard/xdxf_description.md)
or HTML5. It is intended for use as the first stage of an ETL process to load
an EPWING dictionary into a full-text search engine.

It preforms a best-effort re-encoding of the dictionary to UTF-8.
However, the conversion may drop invalid characters. It also performs
a per-sub-book deduplication of dictionary entries, but some duplicates
are difficult to detect in the absence of more sophisticated analysis.

After a conversion completes, a file with conversion metrics is generated
in the [YAML](http://yaml.org/) format.

### Acknowledgements

Gaiji tables were adapted from various applications by
[Christopher Brochtrup (CB4960)](https://sourceforge.net/u/cb4960/profile/).

For dictionaries without gaiji tables, gaiji characters are escaped in the output as:

    {{ wide <gaiji-id-number> }}
    {{ narrow <gaiji-id-number> }}

### Usage

The program may be run with the following arguments to export XDXF:

    epwing-exporter
        # The top-level directory of the EPWING dictionary
        -epwing_directory ${epwing_directory}
        # Output file for the rendered XDXF
        -xdxf_file out/output.xml
        # Output file for the conversion metrics report
        -metrics_file out/output.xml.yaml
        # Output file for any warnings or errors during validation
        -tidy_errors_file out/output.xml.err.txt

To export HTML5:

    epwing-exporter -epwing_directory ${epwing_directory}
                    -html5_file out/output.html5
                    -metrics_file out/output.html5.yaml
                    -tidy_errors_file out/output.html5.err.txt

### Building

_EPWING Exporter_ can be built from source on Linux and OSX with CMake.
For example, to build on Linux:

    cd github.com/destroyhimmyrobots/epwing-exporter
    mkdir build
    cd build
    cmake ..
    make
    # cmd/epwing-exporter

Builds have been tested against Clang 6 (OSX & Linux) and GCC 8 (Linux).

### Dependencies

If building on OSX, `libiconv` must be installed with `brew install iconv`.
All other dependencies are built from source and statically linked.

## Documentation

Documentation on the EPWING format is difficult to come by.
The following collection of links was helpful during the development process:

- ftp://ftp.sra.co.jp/pub/misc/eb/
- http://www.rikai.com/library/kanjitables/kanji_codes.euc.shtml
- https://sourceforge.net/u/cb4960/profile/
- https://sourceforge.net/projects/epwing2anki/
- http://rikaisama.sourceforge.net/versions.html
- https://forum.koohii.com/post-141953.html
- https://github.com/lookup2/lookup2/blob/f3b8624e70dee1571ead3972b012e2d9b3762af0/lisp/support-files/support-srd.el
- https://github.com/boazy/rikaisama-eplkup
- https://raw.githubusercontent.com/boazy/rikaisama-eplkup/master
- https://github.com/FooSoft/yomichan-import/blob/master/wadai.go
