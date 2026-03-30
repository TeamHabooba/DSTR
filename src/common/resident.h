#include "./aliases.h"
#include "./cpp_version.h"
#include "./strings.h"
#include "./enums.h"
#include "./time.h"


namespace dstr {


  // Resident ID type
  struct rid_t {
    char cityLetter;
    u16 id;
  };

    
  class Resident {
    rid_t id_;
    ModeOfTransport transport_;
    int age_;
    int dailyDistance_;
    float carbonEmissionFactor_;
    int averageDayPerMonth_;

  public:

  };
} // namespace dstr
