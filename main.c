#include <stdio.h>
#include "pico/stdlib.h"

#include "onewire.h"
#include "ds18b20.h"

#define ONEWIRE_GPIO        15
#define ONEWIRE_MAXDEVS     10

int main()
{
    stdio_init_all();

    // create an instance of the OneWire library
    puts("initialising library");
    onewire_t ow_bus;
    for(int pio_num = 0; pio_num < NUM_PIOS; pio_num += 1) {
        ow_bus = onewire_init(pio_num, ONEWIRE_GPIO);
        if (ow_bus) {
            break;
        }
    }
    if (ow_bus) {
        // scan bus (takes about 15ms per connected device)
        puts("scanning bus");
        onewire_id_t id_list[ONEWIRE_MAXDEVS];
        int num_devices = onewire_bus_scan(ow_bus, id_list, sizeof(id_list), OW_SEARCH_ROM);
        if (num_devices >= 0) {
            // display device ids
            printf("found %d device%s\n", num_devices, (num_devices == 1) ? "": "s");
            for (int i = 0; i < num_devices; i += 1) {
                printf("\t% 2d: family 0x%02x serial 0x%012llx crc 0x%02x ", i, id_list[i].family, id_list[i].serial, id_list[i].crc);
                puts(onewire_check_crc(&id_list[i]) ? "(pass)": "(fail)");
            }
            while (num_devices > 0) {
                // start temperature measurement on all devices
                ds18b20_start_convert_all(ow_bus);
                while (ds18b20_is_busy(ow_bus)) {
                    sleep_ms(10);
                }
                // display readings
                float t;
                putchar ('\n');
                for (int i = 0; i < num_devices; i += 1) {
                    t = ds18b20_fetch_temperature(ow_bus, id_list[i]);
                    printf ("\t% 2d: %f", i, t);
                }
            }
        } else {
            puts("bus scan error");         // bus_scan() returned < 0
        }
    } else {
        puts("couldn't install driver");    // init() returned NULL
    }

    puts("\nfinished");
    while(true) {
        tight_loop_contents;
    };
}