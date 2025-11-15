// TFT_eSPI User Setup Selection
// Tämä tiedosto valitsee oikean näyttökonfiguraation

#ifdef TDISPLAY
    #include "TDisplay_Setup.h"
#elif defined(TDISPLAY_S3)
    #include "TDisplay_S3_Setup.h"
#elif defined(TPICOC3)
    #include "TPicoC3_Setup.h"
#else
    #error "Määritä laitetyyppi platformio.ini:ssä!"
#endif
