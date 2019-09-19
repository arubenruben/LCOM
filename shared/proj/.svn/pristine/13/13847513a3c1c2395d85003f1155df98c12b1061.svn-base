#pragma once
#define MODE 0x114



/** @defgroup vbe1 vbe1
 * @{
 *
 *  Functions to control the graphical mode and to get information from it
 */


/**
 * @brief Alocates the memory for the graphical buffer, setting up the graphical mode used
 * 
 * @param mode we wish to use
 * 
 * @return doest return anything
 */
void *(vg_init)(uint16_t mode);

/**
 * @brief gets information of the mode we are using and passes them to vmi_p 
 *
 *  @param mode we are using
 * @param vmi_p struct with information regarding the mdoe we are using
 * @return Return 0 upon success and non-zero otherwise
 */
int(vbe_get_mode_info_ours)(uint16_t mode, vbe_mode_info_t *vmi_p);

/**
 * @brief returns the horizontal resolution of the graphical mode we are using
 *
 * @return Return a uint16_t that is the horizontal resolution of the mode
 */
uint16_t get_h_res();

/**
 * @brief returns the vertical resolution of the graphical mode we are using
 * 
 * @return Return a uint16_t that is the vertical resolution of the mode
 */
uint16_t get_v_res();

/**
 * @brief returns the number of bits per pixel used in the mode the user is using
 * 
 * @return numbers of bits per pixel
 */
uint32_t get_bits_per_pixel();

/**
 * @brief returns the vram size of the graphical mode we are using
 * 
 * @return returns the vram size
 */
int get_vram_size();

/**
 * @brief returns the pointer to the double buffer 
 * 
 * @return returns the pointer to the double buffer 
 */
char *get_double_buffer();


/**
 * @brief returns the pointer to the video_mem
 * 
 * @return returns the pointer to the video_mem
 */
char *get_video_mem();

/**
 * @brief drwas a rectangle on the screen in a position that the user whishes
 *
 *  @param x , position along the x axis where we want to draw the rectangle
 *  @param y, position along the y axis where we want to draw the rectangle
 *  @param width of the rectangle
 * @param height of the rectangle
 *  @param color of the rectangle
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief drwas a horizontal line on the screen in a position that the user whishes
 *
 *  @param x , position along the x axis where we want to draw the line
 *  @param y, position along the y axis where we want to draw the line
 *  @param lenght of the line
 *  @param color of the line
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief sets the color of a single pixel
 *
 *  @param x , x position of the pixel
 *  @param y, y positon of the pixel
 *  @param color of the pixel
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int(vg_set_pixel)(uint16_t x, uint16_t y, uint32_t color);
