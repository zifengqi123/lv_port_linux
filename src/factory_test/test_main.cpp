#include "test_main.h"
#include <stdio.h>
#include <stdarg.h>

// export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
smartwin::smartwin_devices* _devices = smartwin::smartwin_devices::getInstance("/dev/ttyS1", 460800);

static char msg[2048] = {0};

void safe_sprintf(const char *format, ...) {
    memset(msg, 0, 2048);

    va_list args;
    va_start(args, format);
    vsnprintf(msg, 2048, format, args);
    va_end(args);

    printf("%s", msg);

    sw_notice_ui_show(msg);
}


std::string vect2str(std::vector<uint8_t> buf) {
    std::string str = "";
    for(int i = 0; i < buf.size(); i++) {
        char tmp[4] = {0};
        sprintf(tmp, "%02X ", buf[i]);
        str += tmp;
    }  
    return str;
}

std::vector<uint8_t> str2vect(std::string str) {
    std::vector<uint8_t> buf;
    for(int i = 0; i < str.size(); i += 2) {
        char tmp[3] = {0};
        tmp[0] = str[i];
        tmp[1] = str[i+1];
        buf.push_back((uint8_t)strtol(tmp, NULL, 16));
    }
    return buf;
}



void test_version()
{
    sw_notice_ui_init(lv_screen_active());
    

    std::vector<uint8_t> version;
    int ret = 0;
    // ret =_devices->get_system_version(SDK_VERSION_TYPE_HARDWARE, version);
    // if (ret != 0) {
    //     printf("ERROR: get_system_version ret: %d\n", ret);
    //     return;
    // }
    // printf("get_system_version ret: %d, 硬件(内部版本号): %s\n", ret, std::string(version.begin(), version.end()).c_str());

    // ret = _devices->get_system_version(SDK_VERSION_TYPE_BOOT, version);
    // if (ret != 0) {
    //     printf("ERROR: get_system_version ret: %d\n", ret);
    //     return;
    // }
    // printf("get_system_version ret: %d, Boot 版本号: %s\n", ret, std::string(version.begin(), version.end()).c_str());

    // ret = _devices->get_system_version(SDK_VERSION_TYPE_KERNEL, version);
    // if (ret != 0) {
    //     printf("ERROR: get_system_version ret: %d\n", ret);
    //     return;
    // }
    // printf("get_system_version ret: %d, 内核版本号: %s\n", ret, std::string(version.begin(), version.end()).c_str());

    ret = _devices->get_system_version(SDK_VERSION_TYPE_SYSTEM, version);
    if (ret != 0) {
        safe_sprintf("ERROR: get_system_version ret: %d\n", ret);
        return;
    }
    safe_sprintf("get_system_version ret: %d, version: %s\n", ret, std::string(version.begin(), version.end()).c_str());

    // ret = _devices->get_system_version(SDK_VERSION_TYPE_LIBRARY, version);
    // if (ret != 0) {
    //     printf("ERROR: get_system_version ret: %d\n", ret);
    //     return;
    // }
    // printf("get_system_version ret: %d, 底层库版本: %s\n", ret, std::string(version.begin(), version.end()).c_str());

    // ret = _devices->get_system_version(SDK_VERSION_TYPE_SDK, version);
    // if (ret != 0) {
    //     printf("ERROR: get_system_version ret: %d\n", ret);
    //     return;
    // }
    // printf("get_system_version ret: %d, SDK 版本号: %s\n", ret, std::string(version.begin(), version.end()).c_str());


    // std::vector<uint8_t> serial_number = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30};
    // std::vector<uint8_t> custom_serial_number = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x31};
    // ret = _devices->set_terminal_serial_number(serial_number, custom_serial_number);
    // if (ret != 0) {
    //     printf("ERROR: set_terminal_serial_number ret: %d\n", ret);
    //     return;
    // }
    // printf("set_terminal_serial_number ret: %d\n", ret);

    // sleep(3);

    // ret = _devices->get_hardware_serial_number(version);
    // if (ret != 0) {
    //     printf("ERROR: get_hardware_serial_number ret: %d\n", ret);
    //     return;
    // }
    // printf("get_hardware_serial_number ret: %d, serial_number: %s\n", ret, std::string(version.begin(), version.end()).c_str());

    // ret = _devices->get_customer_serial_number(version);
    // if (ret != 0) {
    //     printf("ERROR: get_customer_serial_number ret: %d\n", ret);
    //     return;
    // }
    // printf("get_customer_serial_number ret: %d, customer_serial_number: %s\n", ret, std::string(version.begin(), version.end()).c_str());

    uint8_t model = 0;
    ret = _devices->get_device_model(model);
    if (ret != 0) {
        safe_sprintf("ERROR: get_device_model ret: %d\n", ret);
        return;
    }
    safe_sprintf("get_device_model ret: %d, device_model: %d\n", ret, model);

    ret = _devices->get_chip_serial_number(version);
    if (ret != 0) {
        safe_sprintf("ERROR: get_chip_serial_number ret: %d\n", ret);
        return;
    }
    safe_sprintf("get_chip_serial_number ret: %d, chip_serial_number: %s\n", ret, std::string(version.begin(), version.end()).c_str());

    sw_notice_ui_end();
}



void test_beep()
{
    sw_notice_ui_init(lv_screen_active());
    
    int ret = _devices->beep(SDK_BEEP_ABNORMAL);
    if (ret != 0) {
        safe_sprintf("ERROR: beep ret: %d\n", ret);
        return;
    }
    safe_sprintf("beep ret: %d\n", ret);

    ret = _devices->beep_frequency(1000, 1000);
    if (ret != 0) {
        safe_sprintf("ERROR: beep_frequency ret: %d\n", ret);
        return;
    }
    safe_sprintf("beep_frequency ret: %d\n", ret);

    ret = _devices->beep(SDK_BEEP_NORMAL);
    if (ret != 0) {
        safe_sprintf("ERROR: beep ret: %d\n", ret);
        return;
    }
    safe_sprintf("beep ret: %d\n", ret);

    sw_notice_ui_end();
}

void test_led()
{
    sw_notice_ui_init(lv_screen_active());
    

    int ret = _devices->led_on(0x0F);
    if (ret != 0) {
        safe_sprintf("ERROR: led_on ret: %d\n", ret);
        return;
    }
    safe_sprintf("led_on ret: %d\n", ret);
    sleep(1);
    ret = _devices->led_off(0x0F);
    if (ret != 0) {
        safe_sprintf("ERROR: led_off ret: %d\n", ret);
        return;
    }
    safe_sprintf("led_off ret: %d\n", ret);
    sleep(1);
    ret = _devices->led_flash(0x0F, 1000);
    if (ret != 0) {
        safe_sprintf("ERROR: led_flash ret: %d\n", ret);
        return;
    }
    safe_sprintf("led_flash ret: %d\n", ret);
    sleep(1);
    ret = _devices->led_off(0x0F);
    if (ret != 0) {
        safe_sprintf("ERROR: led_off ret: %d\n", ret);
        return;
    }
    safe_sprintf("led_off ret: %d\n", ret);

    sw_notice_ui_end();
}


void test_keyboard()
{
    sw_notice_ui_init(lv_screen_active());
    

    int ret = _devices->keyboard_open();
    if (ret != 0) {
        safe_sprintf("ERROR: keyboard_open ret: %d\n", ret);
        return;
    }
    ret = _devices->keyboard_set_sound(1);
    if (ret != 0) {
        safe_sprintf("ERROR: keyboard_set_sound ret: %d\n", ret);
        return;
    }
    safe_sprintf("keyboard_set_sound ret: %d\n", ret);
    ret = _devices->keyboard_set_backlight(1);
    if (ret != 0) {
        safe_sprintf("ERROR: keyboard_set_backlight ret: %d\n", ret);
        return;
    }
    safe_sprintf("keyboard_set_backlight ret: %d\n", ret);

    sleep(1);

    ret = _devices->keyboard_clear_cache();
    if (ret != 0) {
        safe_sprintf("ERROR: keyboard_clear_cache ret: %d\n", ret);
        return;
    }
    safe_sprintf("keyboard_clear_cache ret: %d\n", ret);

    int cnt = 10;

    safe_sprintf("keyboard_get_input start, input key\n");
    while(cnt > 0) {
        uint8_t key = 0;
        ret = _devices->keyboard_get_input(key);
        if (ret == 0) {
            safe_sprintf("keyboard_get_input ret: %d, key: %d\n", ret, key);
            cnt--;
            break;
        }
        lv_timer_handler();
        usleep(10 * 1000);
    }

    // ret = _devices->keyboard_set_sound(0);
    // if (ret != 0) {
    //     safe_sprintf("ERROR: keyboard_set_sound ret: %d\n", ret);
    //     return;
    // }
    // safe_sprintf("keyboard_set_sound ret: %d\n", ret);
    // ret = _devices->keyboard_set_backlight(0);
    // if (ret != 0) {
    //     safe_sprintf("ERROR: keyboard_set_backlight ret: %d\n", ret);
    //     return;
    // }

    safe_sprintf("keyboard test end\n");
    // ret = _devices->keyboard_close();
    // if (ret != 0) {
    //     safe_sprintf("ERROR: keyboard_close ret: %d\n", ret);
    //     return;
    // }
    // safe_sprintf("keyboard_close ret: %d\n", ret);

    sw_notice_ui_end();
}


void test_tp()
{
    sw_notice_ui_init(lv_screen_active());
    

    int ret = _devices->tp_check_support();
    if (ret != 0) {
        safe_sprintf("ERROR: tp_check_support ret: %d\n", ret);
        return;
    }
    safe_sprintf("tp_check_support ret: %d\n", ret);    
    ret = _devices->tp_set_parameter(0, 0, 319, 239, 20);
    if (ret != 0) {
        safe_sprintf("ERROR: tp_set_parameter ret: %d\n", ret);
        return;
    }
    safe_sprintf("tp_set_parameter ret: %d\n", ret);  

    ret = _devices->tp_open();
    if (ret != 0) {
        safe_sprintf("ERROR: tp_open ret: %d\n", ret);
        return;
    }
    safe_sprintf("tp_open ret: %d\n", ret);

    sleep(1);
    uint32_t x = 0;
    uint32_t y = 0;
    int cnt = 100;
    safe_sprintf("tp_get_touch_coordinate start, get 100 cnt\n");
    while (cnt > 0) {
        ret = _devices->tp_get_touch_coordinate(x, y);
        if (ret == 0) {
            safe_sprintf("tp_get_touch_coordinate ret: %d, x: %d, y: %d\n", ret, x, y);
            cnt--;
        }
        lv_timer_handler();
        usleep(10 * 1000);
    }
    safe_sprintf("tp_get_touch_coordinate end\n");

    ret = _devices->tp_close();
    if (ret != 0) {
        safe_sprintf("ERROR: tp_close ret: %d\n", ret);
        return;
    }
    safe_sprintf("tp_close ret: %d\n", ret);

    sw_notice_ui_end();
}


void test_magnetic_stripe_card()
{
    sw_notice_ui_init(lv_screen_active());
    

    int ret = _devices->magnetic_stripe_card_open();
    if (ret != 0) {
        safe_sprintf("ERROR: magnetic_stripe_card_open ret: %d\n", ret);
        return;
    }
    safe_sprintf("magnetic_stripe_card_open ret: %d\n", ret);

    ret = _devices->magnetic_stripe_card_clear_data();
    if (ret != 0) {
        safe_sprintf("ERROR: magnetic_stripe_card_clear_data ret: %d\n", ret);
        return;
    }
    // safe_sprintf("magnetic_stripe_card_clear_data ret: %d\n", ret);

    int cnt = 3000;
    while (cnt > 0)
    {
        ret = _devices->magnetic_stripe_card_check();
        if (ret == 0) {
            safe_sprintf("magnetic_stripe_card_check ret: %d\n", ret);
            break;
        }
        lv_timer_handler();
        usleep(10 * 1000);
        cnt--;
    }
    if (cnt <= 0) {
        safe_sprintf("ERROR: magnetic_stripe_card_check timeout\n");
        return;
    }

    std::vector<uint8_t> tk1;
    std::vector<uint8_t> tk2;
    std::vector<uint8_t> tk3;
    ret = _devices->magnetic_stripe_card_read_data(tk1, tk2, tk3);
    if (ret != 0) {
        safe_sprintf("ERROR: magnetic_stripe_card_read_data ret: %d\n", ret);
        return;
    }
    safe_sprintf("magnetic_stripe_card_read_data ret: %d\n", ret);
    // safe_sprintf("tk1: ln: %d, %s\n", tk1.size(), std::string(tk1.begin(), tk1.end()).c_str());
    // safe_sprintf("tk2: ln: %d, %s\n", tk2.size(), std::string(tk2.begin(), tk2.end()).c_str());
    // safe_sprintf("tk3: ln: %d, %s\n", tk3.size(), std::string(tk3.begin(), tk3.end()).c_str());

    std::vector<uint8_t> card_number;
    std::vector<uint8_t> valid_date;
    std::vector<uint8_t> card_holder_name;
    std::vector<uint8_t> service_code;
    ret = _devices->magnetic_stripe_card_format_data(tk1, tk2, tk3, card_number, valid_date, card_holder_name, service_code);
    if (ret != 0) {
        safe_sprintf("ERROR: magnetic_stripe_card_format_data ret: %d\n", ret);
        return;
    }
    safe_sprintf("magnetic_stripe_card_format_data ret: %d\n", ret);
    safe_sprintf("card_number: ln: %d, %s\n", card_number.size(), std::string(card_number.begin(), card_number.end()).c_str());
    safe_sprintf("valid_date: ln: %d, %s\n", valid_date.size(), std::string(valid_date.begin(), valid_date.end()).c_str());
    safe_sprintf("card_holder_name: ln: %d, %s\n", card_holder_name.size(), std::string(card_holder_name.begin(), card_holder_name.end()).c_str());
    safe_sprintf("service_code: ln: %d, %s\n", service_code.size(), std::string(service_code.begin(), service_code.end()).c_str());


    ret = _devices->magnetic_stripe_card_close();
    if (ret != 0) {
        safe_sprintf("ERROR: magnetic_stripe_card_close ret: %d\n", ret);
        return;
    }
    // safe_sprintf("magnetic_stripe_card_close ret: %d\n", ret);

    sw_notice_ui_end();
}

void test_ic()
{
    sw_notice_ui_init(lv_screen_active());
    

    int ret = _devices->ic_card_open(0, 0);
    if (ret != 0) {
        safe_sprintf("ERROR: ic_card_open ret: %d\n", ret);
        return;
    }
    safe_sprintf("ic_card_open ret: %d\n", ret);

    while (true) {
        ret = _devices->ic_card_check_status(0, 0);
        if (ret == 0) {
            safe_sprintf("ic_card_check_status ret: %d\n", ret);
            break;
        } 
        lv_timer_handler();
        usleep(10 * 1000);
    }

    std::vector<uint8_t> data;
    ret = _devices->ic_card_reset(0, 0, data);
    if (ret != 0) {
        safe_sprintf("ERROR: ic_card_reset ret: %d\n", ret);
        return;
    }
    safe_sprintf("ic_card_reset ret: %d\n", ret);
    safe_sprintf("data: %s\n", vect2str(data).c_str());

    ret = _devices->ic_card_check_status(0, 0);
    if (ret != 0) {
        safe_sprintf("ic_card_check_status ret: %d\n", ret);
        return;
    } 

    char * sapdu = "00A404000E315041592E5359532E444446303100";

    std::vector<uint8_t> apdu_command = str2vect(sapdu);
    std::vector<uint8_t> card_return_data;
    ret = _devices->ic_card_send_apdu_command(SDK_CARD_SEAT_STANDARD, apdu_command, card_return_data);
    if (ret != 0) {
        safe_sprintf("ERROR: ic_card_send_apdu_command ret: %d\n", ret);
        return;
    }
    safe_sprintf("ic_card_send_apdu_command %s ret: %d\n", sapdu, ret);
    safe_sprintf("card_return_data: %s\n", vect2str(card_return_data).c_str());

    ret = _devices->ic_card_power_off(0, 0);
    if (ret != 0) {
        safe_sprintf("ERROR: ic_card_power_off ret: %d\n", ret);
        return;
    }
    safe_sprintf("ic_card_power_off ret: %d\n", ret);

    sw_notice_ui_end();
}

void test_icc()
{
    sw_notice_ui_init(lv_screen_active());
    

    int ret = _devices->icc_open_module();
    if (ret != 0) {
        safe_sprintf("ERROR: icc_open_module ret: %d\n", ret);
        return;
    }
    safe_sprintf("icc_open_module ret: %d\n", ret);

    uint8_t card_type = 0;
    std::vector<uint8_t> serial_number;
    std::vector<uint8_t> cid;
    std::vector<uint8_t> card_response_info;

    int cnt = 1000;
    while (cnt > 0) {
        ret = _devices->icc_search_card_activation(SDK_ICC_TYPE_A, card_type, serial_number, cid, card_response_info);
        if (ret == 0) {
            safe_sprintf("icc_search_card_activation ret: %d\n", ret);
            break;
        }
        lv_timer_handler();
        usleep(10 * 1000);
        cnt--;
    }
    
    if (cnt <= 0) {
        safe_sprintf("ERROR: icc_search_card_activation timeout\n");
        return;
    }

    char * sapdu = "00A404000E325041592E5359532E444446303100";

    std::vector<uint8_t> apdu_command = str2vect(sapdu);

    std::vector<uint8_t> card_return_data;
    ret = _devices->icc_send_apdu_command(apdu_command, card_return_data);
    if (ret != 0) {
        safe_sprintf("ERROR: icc_send_apdu_command ret: %d\n", ret);
        return;
    }
    safe_sprintf("icc_send_apdu_command %s ret: %d\n", sapdu, ret);
    safe_sprintf("card_return_data: %s\n", vect2str(card_return_data).c_str());
    ret = _devices->icc_close_module();
    if (ret != 0) {
        safe_sprintf("ERROR: icc_close_module ret: %d\n", ret);
        return;
    }

    sw_notice_ui_end();
}


void test_mifare_card()
{
    sw_notice_ui_init(lv_screen_active());
    

    std::vector<uint8_t> uid;
    std::vector<uint8_t> auth_key = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

    int ret = _devices->ic_card_open(SDK_CARD_TYPE_MEMORY, SDK_CARD_SEAT_SAM1);
    if (ret != 0) {
        safe_sprintf("ERROR: ic_card_open ret: %d\n", ret);
        return;
    }
    safe_sprintf("ic_card_open ret: %d\n", ret);

    ret = _devices->ic_card_reset(SDK_CARD_TYPE_MEMORY, SDK_CARD_SEAT_SAM1, uid);
    if (ret != 0) {
        safe_sprintf("ERROR: ic_card_reset ret: %d\n", ret);
        return;
    }
    safe_sprintf("ic_card_reset ret: %d\n", ret);

    ret = _devices->mifare_card_authentication(0, SDK_KEY_TYPE_A, uid, auth_key);
    if (ret != 0) {
        safe_sprintf("ERROR: mifare_card_authentication ret: %d\n", ret);
        return;
    }
    safe_sprintf("mifare_card_authentication ret: %d\n", ret);
    
    std::vector<uint8_t> response_data;
    ret = _devices->mifare_card_operation(SDK_MIFARE_CARD_OPERATION_READ, 0, 0, {}, response_data);
    if (ret != 0) {
        safe_sprintf("ERROR: mifare_card_operation ret: %d\n", ret);
        return;
    }
    safe_sprintf("mifare_card_operation ret: %d\n", ret);
    safe_sprintf("response_data: %s\n", vect2str(response_data).c_str());

    ret = _devices->ic_card_close(SDK_CARD_TYPE_MEMORY, SDK_CARD_SEAT_SAM1);
    if (ret != 0) {
        safe_sprintf("ERROR: ic_card_close ret: %d\n", ret);
        return;
    }
    safe_sprintf("ic_card_close ret: %d\n", ret);

    sw_notice_ui_end();
}

void test_search_card()
{
    sw_notice_ui_init(lv_screen_active());
    

    int ret = _devices->ic_card_open(SDK_CARD_TYPE_CPU, SDK_CARD_SEAT_STANDARD);
    if (ret != 0) {
        safe_sprintf("ERROR: ic_card_open ret: %d\n", ret);
        return;
    }
    ret = _devices->magnetic_stripe_card_open();
    if (ret != 0) {
        safe_sprintf("ERROR: magnetic_stripe_card_open ret: %d\n", ret);
        return;
    }
    ret = _devices->icc_open_module();
    if (ret != 0) {
        safe_sprintf("ERROR: icc_open_module ret: %d\n", ret);
        return;
    }

    ret = _devices->search_card_start(SDK_SWIPE_CARD_HAND | SDK_SWIPE_CARD_ICC | SDK_SWIPE_CARD_RF | SDK_SWIPE_CARD_MAG, 
        10000);
    if (ret != 0) {
        safe_sprintf("ERROR: search_card_start ret: %d\n", ret);
        return;
    }
    safe_sprintf("search_card_start ret: %d\n", ret);
    int cnt = 6000;
    while (cnt > 0) {
        uint8_t type = 0;
        uint8_t key = 0;
        ret = _devices->search_card_get_status(type, key);
        if (ret == 0) {
            safe_sprintf("search_card_get_status ret: %d, type: %d, key: %d\n", ret, type, key);
            break;
        }
        lv_timer_handler();
        usleep(10 * 1000);
        cnt--;
    }
    
    ret = _devices->search_card_stop();
    if (ret != 0) {
        safe_sprintf("ERROR: search_card_stop ret: %d\n", ret);
        return;
    }
    safe_sprintf("search_card_stop ret: %d\n", ret);

    sw_notice_ui_end();
}

void test_scan()
{
    sw_notice_ui_init(lv_screen_active());
    

    int ret = _devices->scan_open();
    if (ret != 0) {
        safe_sprintf("ERROR: scan_open ret: %d\n", ret);
        return;
    }
    safe_sprintf("scan_open ret: %d\n", ret);

    sleep(1);

    std::vector<uint8_t> data;
    ret = _devices->scan_read_data(10000, data);
    if (ret != 0) {
        safe_sprintf("ERROR: scan_read_data ret: %d\n", ret);
        return;
    }
    safe_sprintf("scan_read_data ret: %d\n", ret);
    safe_sprintf("data: %s\n", vect2str(data).c_str());

    ret = _devices->scan_close();
    if (ret != 0) {
        safe_sprintf("ERROR: scan_close ret: %d\n", ret);
        return;
    }
    safe_sprintf("scan_close ret: %d\n", ret);

    sw_notice_ui_end();
}

void test_printer()
{
    int ret = _devices->printer_open();
    if (ret != 0) {
        safe_sprintf("ERROR: printer_open ret: %d\n", ret);
        return;
    }
    safe_sprintf("printer_open ret: %d\n", ret);

    ret = _devices->printer_query_status();

    if (ret != 0) {
        safe_sprintf("ERROR: printer_query_status ret: %d\n", ret);
        return;
    }
    safe_sprintf("printer_query_status ret: %d\n", ret);

    ret = _devices->printer_set_gray(60);
    if (ret != 0) {
        safe_sprintf("ERROR: printer_set_gray ret: %d\n", ret);
        return;
    }
    safe_sprintf("printer_set_gray ret: %d\n", ret);

    ret = _devices->printer_paper_feed(100);
    if (ret != 0) {
        safe_sprintf("ERROR: printer_paper_feed ret: %d\n", ret);
        return;
    }
    std::vector<uint8_t> bitmap_data = {0x42, 0x4D, 0xB6, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x04, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 
    0x40, 0x01, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0C, 0x00, 0x00, 0x13, 0x0B, 0x00, 0x00, 0x13, 0x0B, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (size_t i = 0; i < 1024 + 3200; i++)
    {
        bitmap_data.push_back(0x00);
    }
    
    ret = _devices->printer_print_bitmap_data(1, bitmap_data, 320, 240, SDK_PRINT_ALIGN_CENTER);
    if (ret != 0) {
        safe_sprintf("ERROR: printer_print_bitmap_data ret: %d\n", ret);
        return;
    }
    safe_sprintf("printer_print_bitmap_data ret: %d\n", ret);

    ret = _devices->printer_paper_feed(100);
    if (ret != 0) {
        safe_sprintf("ERROR: printer_paper_feed ret: %d\n", ret);
        return;
    }
    safe_sprintf("printer_paper_feed ret: %d\n", ret);


    ret = _devices->printer_close();
    if (ret != 0) {
        safe_sprintf("ERROR: printer_close ret: %d\n", ret);
        return;
    }
    safe_sprintf("printer_close ret: %d\n", ret);

    sw_notice_ui_end();
}


void test_keypad()
{
    sw_notice_ui_init(lv_screen_active());
    

    int ret = _devices->keypad_open();
    if (ret != 0) {
        safe_sprintf("ERROR: keypad_open ret: %d\n", ret);
        return;
    }
    safe_sprintf("keypad_open ret: %d\n", ret);

    std::vector<uint8_t> data;
    ret = _devices->keypad_get_random_number(8, data);
    if (ret != 0) {
        safe_sprintf("ERROR: keypad_get_random_number ret: %d\n", ret);
        return;
    }
    safe_sprintf("keypad_get_random_number ret: %d\n", ret);
    safe_sprintf("data: %s\n", vect2str(data).c_str());

    ret = _devices->keypad_close();
    if (ret != 0) {
        safe_sprintf("ERROR: keypad_close ret: %d\n", ret);
        return;
    }
    safe_sprintf("keypad_close ret: %d\n", ret);


    sw_notice_ui_end();
}


static lv_point_t  last_pt;
static lv_layer_t  layer;

static lv_obj_t * canvas = NULL;
static bool is_draw = false;
static lv_obj_t * tp_obj;
static pthread_mutex_t tp_show_mutex;
static bool tp_flag = false;

void* draw_thread(void* arg) {
    while (tp_flag) {
        pthread_mutex_lock(&tp_show_mutex);
        // 执行绘制逻辑
        lv_canvas_finish_layer(canvas, &layer);
        pthread_mutex_unlock(&tp_show_mutex);
        usleep(10*1000);  // 控制绘制频率
    }
    return NULL;
}

static void event_cb_ck(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = (lv_obj_t*)lv_event_get_target(e);

    lv_point_t point;

    switch (code)
    {
    case LV_EVENT_PRESSED:
        is_draw = true;
        lv_indev_get_point(lv_indev_active(), &point);
        LV_LOG_USER("LV_EVENT_PRESSED: %d, %d", point.x, point.y);
    
        last_pt.x = point.x;
        last_pt.y = point.y;

        if(!canvas) {
            LV_DRAW_BUF_DEFINE_STATIC(buf_draw_buf_1, 320, 240, LV_COLOR_FORMAT_RGB565);
            LV_DRAW_BUF_INIT_STATIC(buf_draw_buf_1);
        
        
            /*Create a canvas and initialize its palette*/
            
            canvas = lv_canvas_create(lv_screen_active());
            lv_canvas_set_draw_buf(canvas, &buf_draw_buf_1);
            lv_canvas_fill_bg(canvas, lv_color_hex3(0xccc), LV_OPA_COVER);
            lv_obj_center(canvas);
    
            lv_canvas_init_layer(canvas, &layer);

            pthread_t draw_thread_id;
            tp_flag = true;
            pthread_create(&draw_thread_id, NULL, draw_thread, NULL);

        }

        break;
    case LV_EVENT_RELEASED:
        LV_LOG_USER("LV_EVENT_RELEASED");
        is_draw = false;
        break;
    case LV_EVENT_PRESSING:
        if(is_draw) {

            lv_indev_get_point(lv_indev_active(), &point);
            LV_LOG_USER("LV_EVENT_PRESSING: %d, %d", point.x, point.y);

            if(last_pt.x != point.x || last_pt.y != point.y) {
                lv_draw_line_dsc_t t;
                lv_draw_line_dsc_init(&t);
                t.color = lv_palette_main(LV_PALETTE_RED);
                t.width = 2;
                t.p1.x = last_pt.x;
                t.p1.y = last_pt.y;
                t.p2.x = point.x;
                t.p2.y = point.y;
                lv_draw_line(&layer, &t);
                // lv_canvas_finish_layer(canvas, &layer);

                // lv_canvas_draw_line(canvas, last_pt.x, last_pt.y, point.x, point.y, &t);


                last_pt.x = point.x;
                last_pt.y = point.y;
            }
        }
        break;
    default:
        break;
    }

}


void test_tp_del()
{
    if(tp_obj) {
        lv_obj_add_flag(tp_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_del(tp_obj);
        tp_obj = NULL;
        lv_obj_del(canvas);
        canvas = NULL;

        status_ui_show();
        sw_menu_ui_show();
    }
}

static void event_cb1_key(lv_event_t * e)
{
    uint32_t key = lv_indev_get_key(lv_indev_active());
    LV_LOG_USER("key input: %x", key);

    lv_obj_t * obj = lv_event_get_target_obj(e);

    if(key == LV_KEY_ESC) {
        LV_LOG_USER("key LV_KEY_ESC. to del.");
        tp_flag = false;

        lv_obj_remove_event(tp_obj, LV_EVENT_ALL);
        lv_obj_remove_event(tp_obj, LV_EVENT_KEY);
        test_tp_del();
    }
    
}
void sw_test_tp()
{
    status_ui_hide();
    sw_menu_ui_hide();

    pthread_mutex_init(&tp_show_mutex, NULL);

    LV_LOG_USER("sw_test_tp. s..");
    tp_obj =  lv_obj_create(lv_screen_active());
    lv_obj_set_size(tp_obj, 320, 240);
    lv_obj_set_pos(tp_obj, 0, 0);

    lv_obj_set_style_radius(tp_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(tp_obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(tp_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(tp_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(tp_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(tp_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(tp_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(tp_obj, lv_color_hex(MENU_ITEM_UNSELECT_BG_COLOR), LV_PART_MAIN|LV_STATE_DEFAULT);

    LV_LOG_USER("sw_test_tp. 1..");
    lv_group_add_obj(lv_group_get_default(), tp_obj);
    LV_LOG_USER("sw_test_tp. 2..");
    lv_obj_add_event_cb(tp_obj, event_cb_ck, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(tp_obj, event_cb1_key, LV_EVENT_KEY, NULL);
    LV_LOG_USER("sw_test_tp. 3..");

    tp_flag = true;
    LV_LOG_USER("sw_test_tp. e..");
}


menu_item_t mt[10] = {
    {STR_test_version, test_version},
    {STR_test_beep, test_beep},
    {STR_test_mag_card, test_magnetic_stripe_card},
    {STR_test_ic, test_ic},
    {STR_test_rf, test_icc},
    {STR_test_mifare_card, test_mifare_card},
    {STR_test_search_card, test_search_card},
    {STR_test_printer, test_printer},
    {STR_test_keypad, test_keypad},
    {STR_test_tp, sw_test_tp}
    
};


static float t = 0;

static void get_statusinfo(status_info_t * info)
{
    info->battery_per = t;
    info->is_battery_charge = (int)(t*10)%2 ? true : false;
    info->is_print_err = (int)(t*10)%2 ? true : false;
    info->signal_level = ((int)(t*10)) % 6;
    info->signal_type = "4G";
    info->has_wifi = (int)(t*10)%2 ? true : false;
    info->is_wifi_connect = (int)(t*10)%2 ? true : false;
    info->time_stamp = time(NULL);
    
    t += 0.1;
    if(t > 1.1) {
        t = 0;
    }
}

void test_status_bar()
{
    status_ui_init(lv_screen_active(), get_statusinfo);
    status_ui_show();
}

void test_menu_ft() 
{
    test_status_bar();
    sw_menu_ui_init(lv_screen_active(), mt, 10);
}
