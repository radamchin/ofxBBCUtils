
#include "Config.h"

namespace bbc {
    namespace utils {
        
        string Config::data_file_path = "config.xml"; // can be overridden as long as it happens before constructor (instance method)

        Config* Config::instance() { 
            static Config inst; // simplified singleton constructor using static inline var.
            return &inst;
        }

        Config::Config() {
            load_success = load(data_file_path);
            // do other shit?    
        }
                
    }
    
}