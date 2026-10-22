MCU = RP2040
BOARD = GENERIC_RP_RP2040
BOOTLOADER = rp2040

ENCODER_MAP_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = ssd1306

# This first version reserves all available XIAO RP2040 GPIO for the
# 12-key matrix, one encoder, and the I2C OLED. RGB LEDs are not enabled.
