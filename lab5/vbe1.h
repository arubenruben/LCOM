#pragma once


typedef struct {
	char VbeSignature[4];
	uint16_t VbeVersion;
	phys_bytes OemStringPtr;
	uint8_t Capabilities[4];
	phys_bytes VideoModePtr;
	uint16_t TotalMemory;

	uint16_t OemSoftwareRev;
	phys_bytes OemVendorNamePtr;
	phys_bytes OemProductNamePtr;
	phys_bytes OemProductRevPtr;
	uint8_t Reserved[222];

	uint8_t OemData[256];

} __attribute__((packed)) vbe_ctrl_info_t;


int(vg_set_pixel)(uint16_t x, uint16_t y, uint32_t color);

uint32_t(returncolor)(uint8_t row, uint8_t col, uint32_t first, uint8_t step, uint8_t no_rectangles);

int(draw_xpm)(uint16_t x, uint16_t y, const char *xpm[]);

int(erase_xpm)(uint16_t x, uint16_t y, const char *xpm[]);

uint16_t get_h_res();
uint16_t get_v_res();
uint8_t get_bits_per_pixel();
uint8_t get_red_mask_size();
uint8_t get_green_mask_size();
uint8_t get_blue_mask_size();
uint8_t get_blue_field_position();
uint8_t get_red_field_position();
uint8_t get_green_field_position();

void *(vg_init)(uint16_t mode);
int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int(vbe_get_mode_info_ours)(uint16_t mode, vbe_mode_info_t *vmi_p);
int(vbe_get_ctrl_info)(vbe_ctrl_info_t *struct2);
