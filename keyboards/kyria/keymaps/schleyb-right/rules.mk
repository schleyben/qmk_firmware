OLED_DRIVER_ENABLE = yes  # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow

MOUSEKEY_ENABLE      = yes     # Mouse keys
AUTO_SHIFT_ENABLE    = yes
DYNAMIC_MACRO_ENABLE = no
EXTRAKEY_ENABLE      = yes

VIA_ENABLE          = no        # Enable VIA
LTO_ENABLE          = yes

SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = mirror

PIMORONI_TRACKBALL_ENABLE = yes

ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    SRC += pimoroni_trackball.c
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
    POINTING_DEVICE_ENABLE := yes
endif


ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
    ifneq ($(strip $(SPLIT_TRANSPORT)), custom)
        SPLIT_TRANSPORT = custom
        QUANTUM_LIB_SRC += transport.c serial.c i2c_master.c i2c_slave.c
        OPT_DEFS += -DCUSTOM_TRANSPORT
        # Unused functions are pruned away, which is why we can add multiple drivers here without bloat.
        ifeq ($(PLATFORM),AVR)
            ifneq ($(NO_I2C),yes)
                QUANTUM_LIB_SRC += i2c_master.c \
                                   i2c_slave.c
            endif
        endif

        SERIAL_DRIVER ?= bitbang
        OPT_DEFS += -DSERIAL_DRIVER_$(strip $(shell echo $(SERIAL_DRIVER) | tr '[:lower:]' '[:upper:]'))
        ifeq ($(strip $(SERIAL_DRIVER)), bitbang)
            QUANTUM_LIB_SRC += serial.c
        else
            QUANTUM_LIB_SRC += serial_$(strip $(SERIAL_DRIVER)).c
        endif
    endif
endif