#ifndef EPWING_EXPORTER_REPORTER_INTERFACE_H
#define EPWING_EXPORTER_REPORTER_INTERFACE_H

#include <ostream>

#define REPORT(v) #v": " << (v) << '\n'
#define PAD(d) std::string(d * 2, ' ')

namespace epwing {
    class Reporter {
    public:
        void report(std::ostream &os) const {
            this->report(0, os);
        };

    protected:
        virtual void report(int, std::ostream &) const = 0;

        using size_type = std::size_t;
    };
}

#endif // EPWING_EXPORTER_REPORTER_INTERFACE_H
