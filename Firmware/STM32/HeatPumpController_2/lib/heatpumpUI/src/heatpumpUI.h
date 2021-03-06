#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>

#include <DebouncedInput.h>
#include <CountDown.h>
struct FAN_MODE
{
    enum Type
    {
        AUTO, 
        CONT
    };
    Type t_;
    FAN_MODE(Type t) : t_(t) {}
    operator Type () const {return t_;}
    
    bool operator==(const FAN_MODE& other) const
    {
        return t_ == other.t_;
    }
private:
   //prevent automatic conversion for any other built-in types such as bool, int, etc
   template<typename T>
    operator T () const;
};

struct PUMP_MODE
{
    enum Type
    {
        COLD, 
        HOT
    };
    Type t_;
    PUMP_MODE(Type t) : t_(t) {}
    operator Type () const {return t_;}

    bool operator==(const PUMP_MODE& other) const
    {
        return t_ == other.t_;
    }
private:
   //prevent automatic conversion for any other built-in types such as bool, int, etc
   template<typename T>
    operator T () const;
};

struct CONFIGURED_ROOM
{
    enum Type
    {
        BEDROOM, 
        LIVING_ROOM, 
        OFFICE  
    };
    Type t_;
    CONFIGURED_ROOM(Type t) : t_(t) {}
    operator Type () const {return t_;}

    bool operator==(const CONFIGURED_ROOM& other) const
    {
        return t_ == other.t_;
    }
private:
   //prevent automatic conversion for any other built-in types such as bool, int, etc
   template<typename T>
    operator T () const;
};


struct FAN_SPEED
{
    enum Type
    {
        SPEED_1,
        SPEED_2,
        SPEED_3
    };
    Type t_;
    FAN_SPEED(Type t) : t_(t) {}
    operator Type () const {return t_;}

    bool operator==(const FAN_SPEED& other) const
    {
        return t_ == other.t_;
    }
private:
   //prevent automatic conversion for any other built-in types such as bool, int, etc
   template<typename T>
    operator T () const;
};

struct MENU_SELECTED
{
    enum Type
    {
        NONE,
        TEMPERATURE,
        FAN,
        FAN_SPEED,
        COLD_HOT,
        ROOM,
        LAST
    };
    Type t_;
    MENU_SELECTED(Type t) : t_(t) {}
    operator Type () const {return t_;}

    bool operator==(const MENU_SELECTED& other) const
    {
        return t_ == other.t_;
    }
};



struct HeatPumpStatus
{
    bool compressorON;
    bool fanOn;
    float temperature;
    HeatPumpStatus()
    {
        fanOn = false;
        compressorON = false;
        temperature = 25.45;
    }
};

struct HeatPumpConfig
{
    bool arconON;
    float temperature;
    FAN_MODE fan_mode;
    FAN_SPEED fan_speed;
    PUMP_MODE mode;
    CONFIGURED_ROOM room;

    HeatPumpConfig() : fan_mode(FAN_MODE::AUTO), fan_speed(FAN_SPEED::SPEED_1), mode(PUMP_MODE::COLD), room(CONFIGURED_ROOM::BEDROOM)
    {
        arconON = false;
        temperature = 25.45;
        //fan_mode = FAN_MODE::AUTO;
        //fan_speed = FAN_SPEED::SPPED_1;
        //mode = PUMP_MODE::COLD;
        //room = CONFIGURED_ROOM::BEDROOM;
    }

    bool operator==(const HeatPumpConfig& other) const
    {
        return arconON == other.arconON &&
            temperature == other.temperature &&
            fan_mode == other.fan_mode &&
            fan_speed == other.fan_speed &&
            mode == other.mode &&
            room == other.room;
               
    }
};

struct Buttons
{
    bool on_off;
    bool up;
    bool down;
    bool select;
    Buttons(){
        on_off = false;
        up = false;
        down = false;
        select = false;
    }

    bool operator==(const Buttons& other) const
    {
        return on_off == other.on_off &&
               up == other.up &&
               down == other.down &&
               select == other.select;
    }
};

#define    FONT_MAIN_TEMP    u8g2_font_inr24_mr
#define    FONT_DECIMAL_TEMP u8g2_font_inr16_mr
#define    FONT_DEGREE_TEXT u8g2_font_ncenR08_tf
#define    FONT_DEGREE_SYMBOL u8g2_font_6x12_t_symbols

#define    FONT_GENERAL_10PIXEL   u8g2_font_crox2tb_tr

class heatpumpUI{
public:
    heatpumpUI();

    void begin(U8G2_ST7920_128X64_F_SW_SPI* display);

    void DrawMainScreen();

    void run();

    HeatPumpConfig getConfig();

private:
    U8G2_ST7920_128X64_F_SW_SPI* display_;
    HeatPumpConfig currentConfig;
    HeatPumpConfig lastReeadConfig;
    HeatPumpConfig runningConfig;
    MENU_SELECTED selectedMenu;
    HeatPumpStatus currentStatus;
    Buttons pressedButtons;
    Buttons pressedButtons2;
    bool redraw;
    bool editingTemp;

    unsigned long timeControl;


    //Drawing Menus
    void DrawCurrentTemperature();
    void DrawConfigTemperature();
    void DrawAROn_Off();
    void DrawCompOn_Off();
    void DrawFanOn_Off();
    void DrawFanSpeedConfig();
    void DrawFanModeConfig();
    void DrawModeConfig();
    void DrawRoomConfig();
    void DrawGrid();

    bool shouldShow();

    void resetPressedButtons();
    void HandleActions();
    void HandleButtons();   

};

